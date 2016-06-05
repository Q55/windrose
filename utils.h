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

    static double calcVariance(QVector<double> & data);

    //void range_check(emxArray_real_T *data, const emxArray_real_T *b_max,
    //                 const emxArray_real_T *b_min, const emxArray_real_T *check_list, double check)
    static QVector<double> rangeCheck(QVector<double> data, double max, double min, QString process_type);

    //double cycle_max(const emxArray_real_T *data, double est_max, double resol,
    //                 double obs_time, double Regression_cycle)
    static QVector<double> cycleMax(QVector<double> data, int freq, int internal_time);

    //void range_cont(emxArray_real_T *data, const emxArray_real_T *gsd, double
    //                time_step, const emxArray_real_T *check_list, double check)
    static QVector<double> rangeCont(QVector<double> data, double gsd, double time_step, QString process_type);

    //void filters(double Fs, const emxArray_real_T *data, double *Mdata,
    //             emxArray_real_T *Ldata, emxArray_real_T *Wdata)
    static double qtFilters(QVector<double> data, double fs, QVector<double>& l_data, QVector<double>& w_data);

    static double interConsis(QVector<double> data);


};

#endif // UTILS_H
