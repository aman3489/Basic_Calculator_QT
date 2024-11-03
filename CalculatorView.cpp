#include "CalculatorView.h"
#include <QKeyEvent>

CalculatorView::CalculatorView(QWidget *parent) : QWidget(parent){
    setFocusPolicy(Qt::StrongFocus);
    display = new QLineEdit(this);
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignLeft);

    QGridLayout *layout = new QGridLayout(this);


    // Set a larger minimum height for the display
    display->setMinimumHeight(100);  // Adjust this value as needed

    // Adjust the size policy to allow vertical expansion
    display->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(display, 0, 0, 1, 4);

    QString buttons[4][4] = {
        { "7", "8", "9", "/" },
        { "4", "5", "6", "*" },
        { "1", "2", "3", "-" },
        { "0", ".", "=", "+" }
    };

    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
            QPushButton *button = createButton(buttons[i][j]);
            layout->addWidget(button, i+1, j);
            connect(button, &QPushButton::clicked, this, [=](){
                emit buttonClicked(button->text());
            });
        }
    }

    // Add the "Clear" button below the keypad
    clearButton = createButton("C");
    layout->addWidget(clearButton, 5, 0, 1, 2);  // Span across the entire width of the grid
    connect(clearButton, &QPushButton::clicked, this, [=]() {
        emit buttonClicked("C");  // Emit a signal with "C" when the clear button is clicked
    });

    backSpaceButton = createButton("<-");
    layout->addWidget(backSpaceButton, 5, 3, 1, 2);
    connect(backSpaceButton, &QPushButton::clicked, this, [=]() {
        emit buttonClicked("<");
    });

    layout->setSpacing(10);
    layout->setContentsMargins(10, 10, 10, 10);

    setLayout(layout);
    setMinimumSize(200, 300);
    setMaximumSize(300, 450);

}

QPushButton* CalculatorView::createButton(const QString &text){
    QPushButton *button = new QPushButton(text, this);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button->setMinimumSize(30, 30);
    button->setMaximumSize(50, 50);
    return button;
}

void CalculatorView::keyPressEvent(QKeyEvent *event){
    QString keyText = event->text();

    // Check if the key pressed corresponds to any button on the calculator
    if (keyText == "0" || keyText == "1" || keyText == "2" || keyText == "3" ||
        keyText == "4" || keyText == "5" || keyText == "6" || keyText == "7" ||
        keyText == "8" || keyText == "9" || keyText == "+" || keyText == "-" ||
        keyText == "*" || keyText == "/" || keyText == "." || keyText == "=") {

        emit buttonClicked(keyText);  // Emit the buttonClicked signal
    }

    else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        emit buttonClicked("=");
    }

    else if (event->key() == Qt::Key_Backspace){
        emit buttonClicked("<");
    }

    else if (keyText == "C"){
        emit buttonClicked("C");
    }

    else QWidget::keyPressEvent(event);
}
