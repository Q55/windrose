#ifndef ANALYSEPARAS_H
#define ANALYSEPARAS_H
#include <QString>
#include <QDate>

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
    QString db_name;
    QString tb_name;
    QString col_name;

    int frequency;
    int time_interval;
    QString analyse_type;
    QString filter_type;

    bool range_filter;
    double max;
    double min;
    bool time_cont;
    bool data_cont;
    bool consist_check;
    QString process_type;

    QDate start_time;
    QDate end_time;
};

#endif // ANALYSEPARAS_H
