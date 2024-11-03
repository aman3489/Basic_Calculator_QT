#ifndef CALCULATORCONTROLLER_H
#define CALCULATORCONTROLLER_H

#include <QObject>
#include "CalculatorModel.h"
#include "CalculatorView.h"

class CalculatorController : public QObject {
    Q_OBJECT

public:
    CalculatorController(CalculatorModel *model, CalculatorView *view);

private slots:
    void handleButtonClicked(const QString& text);

private:
    CalculatorModel *model;
    CalculatorView *view;
    QString currentExpression;
};

#endif // CALCULATORCONTROLLER_H
