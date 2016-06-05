#ifndef ANALYSEPARAS_H
#define ANALYSEPARAS_H
#include <QString>
#include <QDate>

class AnalyseParas
{
public:
    AnalyseParas() {

        this->frequency = 1;
        this->time_interval = 1;
        this->analyse_type = "";
        this->filter_type = "";

        this->range_filter = false;
        this->max = 0.0;
        this->min = 0.0;
        this->time_cont = false;
        this->data_cont = false;
        this->consist_check = false;
        this->process_type = "";

        //精确到日期还是小时
        this->start_time.setDate(QDate(2000,1,1));
        this->start_time.setTime(QTime(0,0,0));
        this->end_time.setDate(QDate(2000,1,1));
        this->end_time.setTime(QTime(0,0,0));
    }

    /*
    AnalyseParas(int fre, int time_interval, QString analyse_type, QString filter_type) {
        this->frequency = fre;
        this->time_interval = time_interval;
        this->analyse_type = analyse_type;
        this->filter_type = filter_type;
    }
    */
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

    QDateTime start_time;
    QDateTime end_time;

    //For Test
    void printfConfigInfo() {
        qDebug() << "db_name:" << db_name;
        qDebug() << "tb_name:" << tb_name;
        qDebug() << "col_name:" << col_name;
        qDebug() << "frequency:" << frequency;
        qDebug() << "time_interval:" << time_interval;
        qDebug() << "analyse_type:" << analyse_type;
        qDebug() << "filter_type:" << filter_type;
        qDebug() << "range_filter:" << range_filter;
        qDebug() << "max:" << max;
        qDebug() << "min:" << min;
        qDebug() << "time_cont:" << time_cont;
        qDebug() << "data_cont:" << data_cont;
        qDebug() << "consist_check:" << consist_check;
        qDebug() << "process_type:" << process_type;
        qDebug() << "start_time:" << start_time;
        qDebug() << "end_time:" << end_time;
    }
};

#endif // ANALYSEPARAS_H
