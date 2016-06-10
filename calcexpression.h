#ifndef CALCEXPRESSION_H
#define CALCEXPRESSION_H

#include <QString>
#include <QStack>

class CalcExpression
{
public:
    CalcExpression();
    CalcExpression(QString var_name, QString expression);
    double calcExpr(double input); // data

private:
    bool isNum(const QChar &ch);
    bool isStrNum(const QString &str);
    bool isOperator(const QChar &ch);
    bool isStrOperator(const QString &str);
    bool isExpression(const QString &str);

    QVector<QString> resolveExpression(const QString& expr);
    bool priorOperator(const QString &o1, const QString &o2);
    QVector<QString> infixToPostfix(QVector<QString>& infix_v);

    double getCountResult(QString op, double num1, double num2);
    double getPostfixResult(QVector<QString> &postfix_v);

private:
    QVector<QString> postfix_v;
    QString var_name;

};

#endif // CALCEXPRESSION_H
