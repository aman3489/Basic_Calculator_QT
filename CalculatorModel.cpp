#include "CalculatorModel.h"
#include <QStack>
#include <QDebug>

CalculatorModel::CalculatorModel(){}

bool CalculatorModel::isOperator(QChar op){
    return op == '+' || op == '-' || op == '*' || op == '/';
}

int CalculatorModel::checkPriority(QChar op){
    if(op == '*' || op == '/') return 1;
    else return 0;
}

float CalculatorModel::calculate(float num1, float num2, QChar op){
    switch (op.unicode()) {
    case '+': return num1 + num2;
    case '-': return num1 - num2;
    case '*': return num1 * num2;
    case '/':
        try{
            if(num2 == 0) throw num2;
            else return num1 / num2;
        }
        catch(int num){
            return std::numeric_limits<float>::quiet_NaN();
        }

    default:
        qWarning() <<"Unknown operator!";
        return std::numeric_limits<float>::quiet_NaN();
    }
}

QString CalculatorModel::toPostFix(const QString &exp, std::queue<float> &numberQueue){
    QStack<QChar> operatorStack;
    QString postfix;
    int length = exp.length();

    for (int i = 0; i < length; i++) {
        if (isOperator(exp[i])) {
            while (!operatorStack.isEmpty() && checkPriority(exp[i]) <= checkPriority(operatorStack.top())) {
                postfix.append(operatorStack.pop());
            }
            operatorStack.push(exp[i]);
        } else {
            QString number;
            while (i < length && !isOperator(exp[i])) {
                number.append(exp[i]);
                i++;
            }
            i--;  // Adjust for loop increment
            numberQueue.push(number.toFloat());
            postfix.append('N');
        }
    }

    while (!operatorStack.isEmpty()) {
        postfix.append(operatorStack.pop());
    }

    return postfix;
}

float CalculatorModel::evaluatePostFix(std::queue<float>& numberQueue, const QString& postfix) {
    QStack<float> evaluationStack;

    for (int i = 0; i < postfix.length(); i++) {
        if (isOperator(postfix[i])) {
            if (evaluationStack.size() < 2) {
                qWarning() << "Wrong expression! Not enough operands.";
                return -1;
            }
            float num1 = evaluationStack.pop();
            float num2 = evaluationStack.pop();
            evaluationStack.push(calculate(num2, num1, postfix[i]));
        } else {
            if (numberQueue.empty()) {
                qWarning() << "Wrong expression! Not enough numbers.";
                return -1;
            }
            evaluationStack.push(numberQueue.front());
            numberQueue.pop();
        }
    }

    if (evaluationStack.size() != 1) {
        qWarning() << "Wrong expression! The stack does not contain exactly one result.";
        return -1;
    }

    return evaluationStack.top();
}


QString CalculatorModel::evaluateExpression(const QString& expression) {
    std::queue<float> numberQueue;
    QString postfix = toPostFix(expression, numberQueue);
    float result = evaluatePostFix(numberQueue, postfix);
    return QString::number(result);
}
