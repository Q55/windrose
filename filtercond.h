#ifndef FILTERCOND_H
#define FILTERCOND_H
#include <QString>

class FilterCond
{
public:
    FilterCond();
    FilterCond (bool range_filter, double max, double min, bool time_cont, bool data_cont, bool consist_check, QString process_type) {
        this->range_filter = range_filter;
        this->max = max;
        this->min = min;
        this->time_cont = time_cont;
        this->data_cont = data_cont;
        this->consist_check = consist_check;
        this->process_type = process_type;
    }

public:
    bool range_filter;
    double max;
    double min;
    bool time_cont;
    bool data_cont;
    bool consist_check;
    QString process_type;
};

#endif // FILTERCOND_H
