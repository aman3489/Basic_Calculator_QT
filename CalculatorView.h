#ifndef CALCULATORVIEW_H
#define CALCULATORVIEW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QKeyEvent>

class CalculatorView: public QWidget{
    Q_OBJECT

public:
    explicit CalculatorView(QWidget *parent = nullptr);

    QLineEdit* display;
    QPushButton* createButton(const QString& text);

signals:
    void buttonClicked(const QString& text);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QPushButton *clearButton;
    QPushButton *backSpaceButton;
};

#endif // CALCULATORVIEW_H
