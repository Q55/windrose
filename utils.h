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
    static QVector<double> calcPreFormula(QVector<double> data, QString formula);

    static QVector<double> calcMax(QVector<double> data, int freq, int internal_time);
    static QVector<double> calcMin(QVector<double> data, int freq, int internal_time);
    static QVector<double> calcAvg(QVector<double> data, int freq, int internal_time);

    //void filters(double Fs, const emxArray_real_T *data, double *Mdata,
    //             emxArray_real_T *Ldata, emxArray_real_T *Wdata)
    static double qtFilters(QVector<double> data, double fs, QVector<double>& l_data, QVector<double>& w_data);

    //void range_check(emxArray_real_T *data, const emxArray_real_T *b_max,
    //                 const emxArray_real_T *b_min, const emxArray_real_T *check_list, double check)
    static QVector<double> rangeCheck(QVector<double> data, double max, double min, int process_type);

    //void time_cont(const emxArray_real_T *data, double time_row, double time_step,
    //               double check, emxArray_real_T *data_out)
    static QVector<double> timeCont(QVector<double> data, int freq, double time_row, double time_step, int process_type);

    //void range_cont(emxArray_real_T *data, const emxArray_real_T *gsd, double
    //                time_step, const emxArray_real_T *check_list, double check)
    static QVector<double> rangeCont(QVector<double> data, double gsd, double time_step, int process_type);

    //void inter_consis(emxArray_real_T *data1, const emxArray_real_T *data2, double
    //                  type, emxArray_real_T *data)
    static QVector<double> interConsis(QVector<double> data, QString expression, int process_type);

    //double cycle_max(const emxArray_real_T *data, double est_max, double resol,
    //                 double obs_time, double Regression_cycle)
    static QVector<double> cycleMax(QVector<double> data, int freq, int internal_time);

};

#endif // UTILS_H
