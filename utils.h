#ifndef UTILS_H
#define UTILS_H

#include <QVector>
#include <QStringList>
#include <QString>

class Utils
{
public:
    Utils();
    ~Utils();


    //FIXME:whether the input parameter type is reference
    static double cycleMax(QVector<double> data);
    static double interConsis(QVector<double> data);

};

#endif // UTILS_H
