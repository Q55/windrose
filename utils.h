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
    static QVector<double> cycleMax(QVector<double> data, int window_size);
    static double interConsis(QVector<double> data);

};

#endif // UTILS_H
