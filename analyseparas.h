#ifndef ANALYSEPARAS_H
#define ANALYSEPARAS_H
#include <QString>
#include <QDate>

class AnalyseParas
{
public:

    enum Pre_AnalyseType
    {
        NONEANALYSE,
        MAXVALUE,
        MINVALUE,
        AVERAGEVALUE
    };

    enum Pre_FilterType
    {
        NONEFILTER,
        LOWERPASSFILTER
    };
    AnalyseParas() {

        this->frequency = 1;
        this->time_interval = 1;
        this->analyse_type = 0;
        this->filter_type = 0;

        this->range_filter = false;
        this->max = 0.0;
        this->min = 0.0;
        this->range_filter_check_type = 1.0;//FIXME 06-07

        this->time_cont = false;
        this->time_cont_time_step = 1.0;//FIXME 06-07
        this->time_cont_check_type = 1.0;//FIXME 06-07

        this->data_cont = false;
        this->data_cont_gsd = 0.0; //FIXME 06-07
        this->data_cont_time_step = 1.0;//FIXME 06-07
        this->data_cont_check_type = 1.0; //FIXME 06-07

        this->consist_check = false;
        this->expression = "";
        this->consist_check_type = 1.0;//FIXME 06-07
        //this->process_type = 0;

        //精确到日期还是小时
        this->start_time.setDate(QDate(2000,1,1));
        this->start_time.setTime(QTime(0,0,0));
        this->end_time.setDate(QDate(2016,6,1));
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
    int analyse_type;
    int filter_type;

    bool range_filter;
    double max;
    double min;
    double range_filter_check_type;

    bool time_cont;
    double time_cont_time_step;
    double time_cont_check_type;

    bool data_cont;
    double data_cont_gsd;
    double data_cont_time_step;
    double data_cont_check_type;

    bool consist_check;
    QString expression;
    double consist_check_type;

//    int process_type;

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
        qDebug() << "time_cont_time_step" << time_cont_time_step;
        qDebug() << "time_cont_check_type" << time_cont_check_type;
        qDebug() << "data_cont:" << data_cont;
        qDebug() << "data_cont_time_step" << data_cont_time_step;
        qDebug() << "data_cont_gsd" << data_cont_gsd;
        qDebug() << "data_cont_check_type" << data_cont_check_type;
        qDebug() << "consist_check:" << consist_check;
        qDebug() << "expression" << expression;
        qDebug() << "consist_check_type" << consist_check_type;
//        qDebug() << "process_type:" << process_type;
        qDebug() << "start_time:" << start_time;
        qDebug() << "end_time:" << end_time;
    }
};

#endif // ANALYSEPARAS_H
