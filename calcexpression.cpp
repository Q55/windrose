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
    //qDebug()<<"index of "<<var_name<<" = "<<index;
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
    bool have_dot = false;
    for (int i = 0; i < str.length(); ++i) {
        if (!this->isNum(str[i]) && str[i] != '.')
            return false;
        if (str[i] == '.')
        {
            if(have_dot)
                return false;
            have_dot = true;
        }
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

bool CalcExpression::isArithmeticOperator(const QChar &c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CalcExpression::isParenthesis(const QChar &c)
{
    if (c == '(' || c == ')')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CalcExpression::isAlpha(const QChar &c)
{
    if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//*******************************************************************
// return value:
//0 : is a valid expression
//-1: bracket is not matched
//-2: variable is not valid
//-3: variable is too more
//-4: operator is not valid
//-5: others: expression is not valid.
//*********************************************************************
int CalcExpression::isExpression(const QString &str) {
    int  parenthesis_flag = 0;
    bool have_variable = false;
    bool is_operator = true;
    qDebug() << str.size();
    for (int i = 0; i < str.size(); i++) {

        const QChar curChar = str[i];
        QString metadata;
        while (i < str.size() && str[i] == ' ')
        {
            ++i;
        }
        if (i == str.size())
            break;
//        int j = i;

        if ( isAlpha(curChar) && is_operator)
        {
            if (!is_operator)
            {
                return ERR_EXPRE_INVALID;
            }
            if (have_variable)
            {
                return ERR_VARIABLE_MORE;
            }
            have_variable = true;
            is_operator = false;
            continue;
        }
        if ( isParenthesis( curChar ) )
        {

            if (curChar == '(') parenthesis_flag++;
            if (curChar == ')') parenthesis_flag--;
            if (parenthesis_flag < 0) {
                qDebug() << "bracket not matched.";
                return ERR_BRACKET;
            }
            qDebug() << parenthesis_flag;
            continue;
        }

        if ( isArithmeticOperator(curChar) )
        {
            if (is_operator)
            {
                return ERR_EXPRE_INVALID;
            }
            is_operator = true;
            continue;
        }

        if (!is_operator)
        {
            return ERR_EXPRE_INVALID;
        }

        while (i < str.size() && !isArithmeticOperator( str[i] ) && !isParenthesis( str[i] ) && str[i] != ' ')
        {
            metadata += str[i];
            ++i;
        }
        --i;
        if (!isStrNum(metadata))
        {
            return ERR_DATA_INVALID;
        }

        is_operator = false;
//        const QChar nextChar = str[i + 1];

//        if (curChar == '.' && !isNum(nextChar) || (!isNum(ch) && nextChar == '.')) {
//            qDebug()<<"not digit around '.'";
//            return false;
//        }
//        if (isOperator(curChar) && !isNum(nextChar) && nextChar != '(' || curChar == '(' && !isNum(nextChar) && nextChar !='(') {
//            qDebug()<<"not digit around 'operator'";
//            return false;
//        }
//        if (isNum(curChar) && !isOperator(nextChar) && nextChar != '.' && nextChar != ')' && !isNum(nextChar)) {
//            qDebug()<<"not operator after digit";
//            return false;
//        }

    }
    if (parenthesis_flag != 0) {
        qDebug() << "enter!";
        qDebug() <<"bracket not matched.";
        return ERR_BRACKET;
    }
    if (have_variable == false)
    {
        return ERR_NO_VARIABLE;
    }
    if (is_operator)
    {
        return ERR_EXPRE_INVALID;
    }
    return 0;
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


