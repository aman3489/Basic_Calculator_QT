#include "CalculatorController.h"

CalculatorController::CalculatorController(CalculatorModel *model, CalculatorView *view)
    : QObject(view), model(model), view(view){
    connect(view, &CalculatorView::buttonClicked, this, &CalculatorController::handleButtonClicked);
}

void CalculatorController::handleButtonClicked(const QString &text){
    if(text == "C"){
        currentExpression.clear();
        view->display->clear();
    }

    else if(text == "<"){
        if(!currentExpression.isEmpty()){
            currentExpression.chop(1);
            view->display->setText(currentExpression);
        }
    }

    else if(text == "="){
        QString result = model->evaluateExpression(currentExpression);
        view->display->setText(result);
        currentExpression.clear();
    }
    else {
        currentExpression.append(text);
        view->display->setText(currentExpression);
    }
}
