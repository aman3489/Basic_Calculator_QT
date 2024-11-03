#ifndef CALCULATORMODEL_H
#define CALCULATORMODEL_H

#include <QString>
#include <stack>
#include <queue>

class CalculatorModel{
public:
    CalculatorModel();
    QString evaluateExpression(const QString& expression);

private:
    bool isOperator(QChar op);
    int checkPriority(QChar op);
    float calculate(float num1, float num2, QChar op);
    QString toPostFix(const QString& exp, std::queue<float>& numberQueue);
    float evaluatePostFix(std::queue<float>& numberQueue, const QString& postfix);
};

#endif // CALCULATORMODEL_H
