#include "calcexpression.h"
#include <QDebug>

CalcExpression::CalcExpression()
{

}

CalcExpression::CalcExpression(QString var_name, QString expression) {
    this->var_name = var_name;
    QVector<QString> infix_v;
//    if (!this->isExpression(expression)) {
//        qDebug()<<"Not a Valid Expression!";
//        exit(-1);
//    }
    infix_v = this->resolveExpression(expression);
    postfix_v = this->infixToPostfix(infix_v);
}

double CalcExpression::calcExpr(double input) {
    QVector<QString> expr_v = postfix_v;
    int index = expr_v.indexOf(this->var_name);
    qDebug()<<"index of "<<var_name<<" = "<<index;
    if (index < 0 || index > expr_v.size() - 1)
        return input;
    expr_v[index] = QString::number(input);
    return this->getPostfixResult(expr_v);
}

bool CalcExpression::isNum(const QChar &ch) {
    if (ch <= '9' && ch >='0')
        return true;
    else
        return false;
}

bool CalcExpression::isStrNum(const QString & str) {
    if (str.length() == 0)
        return false;
    if (str[0] == '.' || str[str.length() - 1] == '.')
        return false;
    if (str.length() > 1) {
        if (str[0] == '0' && str[1] != '.')
            return false;
    }
    for (int i = 0; i < str.length(); ++i) {
        if (!this->isNum(str[i]) && str[i] != '.')
            return false;
    }
    return true;
}

bool CalcExpression::isOperator(const QChar &ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=')
        return true;
    else
        return false;
}

bool CalcExpression::isStrOperator(const QString &str) {
    if (str == "+" || str == "-" || str == "*" || str == "/"
            || str == "(" || str == ")")
        return true;
    else
        return false;
}

bool CalcExpression::isExpression(const QString &str) {
    int flag = 0;
    for (int i = 0; i < str.length() - 1; i++) {
        const QChar ch = str[i];
        const QChar chb = str[i + 1];
        if (ch == '.' && !isNum(chb) || (!isNum(ch) && chb == '.')) {
            qDebug()<<"not digit around '.'";
            return false;
        }
        if (isOperator(ch) && !isNum(chb) && chb != '(' || ch == '(' && !isNum(chb) && chb !='(') {
            qDebug()<<"not digit around 'operator'";
            return false;
        }
        if (isNum(ch) && !isOperator(chb) && chb != '.' && chb != ')' && !isNum(chb)) {
            qDebug()<<"not operator after digit";
            return false;
        }
        if (ch == '(') flag++;
        if (ch == ')') flag--;
    }
    if (flag != 0) {
        qDebug() <<"bracket not matched.";
        return false;
    }
    return true;
}

QVector<QString> CalcExpression::resolveExpression(const QString& expr) {
    QVector<QString> infix_v;
    QString temp = "";
    for (int i = 0; i < expr.length(); ++i) {
        const QChar ch = expr[i];
        if (isNum(ch) || ch == '.')
            temp += ch;
        else if (isOperator(ch) || ch == ')') {
            if (temp != "") {
                infix_v.push_back(temp);
                temp = "";
            }
            temp.append(ch);
            infix_v.push_back(temp);
            temp = "";
        } else if (ch == '(') {
            temp.append(ch);
            infix_v.push_back(temp);
            temp = "";
        } else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            temp.append(ch);
            infix_v.push_back(temp);
            temp = "";
        }
        if (i == expr.length() - 1)
            infix_v.push_back(temp);
    }
    return infix_v;
}

bool CalcExpression::priorOperator(const QString &o1, const QString &o2) {
    if ((o1 == "*" || o1 == "/") && (o2 == "+" || o2 == "-") || o2 == "(" )
        return true;
    else if ((o1 == "+" || o1 == "-") && (o2 == "*" || o2 == "/"))
        return false;
    else if ((o1 == "*" || o1 == "/") && (o2 == "*" || o2 == "/"))
        return true;
    else if ((o1 == "+" || o1 == "-") && (o2 == "+" || o2 == "-"))
        return true;
    else
        return false;
}

QVector<QString> CalcExpression::infixToPostfix(QVector<QString>& infix_v) {
    QStack<QString> s_stack;
    QVector<QString> postfix_v;
    for (int i = 0; i < infix_v.size(); ++i) {
        const QString str = infix_v[i];
        if (isStrNum(str) || str == "a")
            postfix_v.push_back(str);
        else if (isStrOperator(str) && s_stack.empty())
            s_stack.push(str);
        else if (isStrOperator(str) && !s_stack.empty()) {
            QString last = s_stack.top();
            if (priorOperator(str, last) || str == "(")
                s_stack.push(str);
            else if (!priorOperator(str, last) && str != ")") {
                while (!s_stack.empty()) {
                    QString pop = s_stack.top();
                    postfix_v.push_back(pop);
                    s_stack.pop();
                }
                s_stack.push(str);
            } else if (str == ")") {
                while (!s_stack.empty()) {
                    QString pop = s_stack.top();
                    if (pop != "(") {
                        postfix_v.push_back(pop);
                        s_stack.pop();
                    } else
                        s_stack.pop();
                    if (pop == "(")
                        break;
                }
            }
        }
    }
    while (!s_stack.empty()) {
        postfix_v.push_back(s_stack.top());
        s_stack.pop();
    }
    return postfix_v;
}

double CalcExpression::getCountResult(QString op, double num1, double num2) {
    if (op == "+") return num1 + num2;
    else if (op == "-") return num1 - num2;
    else if (op == "*") return num1 * num2;
    else if (op == "/") return num1 / num2;
    else return 0.0;
}

 double CalcExpression::getPostfixResult(QVector<QString> &postfix_v){
     QStack<QString> e_stack;
     QString temp = "";
     for (int i = 0; i < postfix_v.size(); ++i) {
         QString str = postfix_v[i];
         if (isStrNum(str))
             e_stack.push(str);
         else if (isStrOperator(str)) {
             double n2 = e_stack.top().toDouble();
             e_stack.pop();
             double n1 = e_stack.top().toDouble();
             e_stack.pop();
             double sum = getCountResult(str, n1, n2);
             temp += QString::number(sum);
             e_stack.push(temp);
             temp = "";
         }
     }
     return e_stack.top().toDouble();
 }


