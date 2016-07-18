#ifndef CALCEXPRESSION_H
#define CALCEXPRESSION_H

#include <QString>
#include <QStack>
//*******************************************************************
// isExpression()
// return value:
//0 : is a valid expression
//-1: bracket is not matched
//-2: variable is not valid
//-3: variable is too more
//-4: operator is not valid
//-5: have no variable
//-6: others: expression is not valid.
//*******************************************************************
#define ERR_BRACKET  -1
#define ERR_DATA_INVALID -2
#define ERR_VARIABLE_MORE -3
#define ERR_OPERATOR_INVALID -4
#define ERR_NO_VARIABLE -5
#define ERR_EXPRE_INVALID -6

class CalcExpression
{
public:
    CalcExpression();
    CalcExpression(QString var_name, QString expression);
    double calcExpr(double input); // data

public:
    bool isNum(const QChar &ch);
    bool isStrNum(const QString &str);
    bool isOperator(const QChar &ch);
    bool isArithmeticOperator(const QChar &c);
    bool isParenthesis(const QChar &c);
    bool isAlpha(const QChar &c);
    bool isStrOperator(const QString &str);
    int  isExpression(const QString &str);

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
