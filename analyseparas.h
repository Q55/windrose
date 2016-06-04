#ifndef ANALYSEPARAS_H
#define ANALYSEPARAS_H
#include <QString>

class AnalyseParas
{
public:
    AnalyseParas();
    AnalyseParas(int fre, int time_interval, QString analyse_type, QString filter_type) {
        this->frequency = fre;
        this->time_interval = time_interval;
        this->analyse_type = analyse_type;
        this->filter_type = filter_type;
    }
    ~AnalyseParas(){}

public:
    int frequency;
    int time_interval;
    QString analyse_type;
    QString filter_type;
};

#endif // ANALYSEPARAS_H
