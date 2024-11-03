#include <QApplication>
#include "CalculatorModel.h"
#include "CalculatorView.h"
#include "CalculatorController.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    CalculatorModel model;
    CalculatorView view;
    CalculatorController controller(&model, &view);

    app.setStyleSheet("QWidget { background-color: #1e1e1e; }"  // Dark gray background for the entire app
                      "QLineEdit { background-color: #333; color: white; font-size: 20px; }"  // Display
                      "QPushButton { background-color: #555; color: white; font-size: 18px; border: 1px solid #666; border-radius: 5px; padding: 10px; }"
                      "QPushButton:pressed { background-color: #777; }"  // Button pressed state
                      "QPushButton:focus { border: 2px solid #888; }");  // Button focus state


    view.setWindowTitle("Calculator");
    view.show();

    return app.exec();
}
