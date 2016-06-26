#ifndef UTILS_H
#define UTILS_H

#include <QVector>
#include <QStringList>
#include <QString>
#include "calcexpression.h"

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
    static QVector<double> rangeCheck(QVector<double> data, double max, double min, double process_type);

    //void time_cont(const emxArray_real_T *data, double time_row, double time_step,
    //               double check, emxArray_real_T *data_out)
    static QVector<double> timeCont(QVector<double> data, int freq, double time_row, double time_step, double process_type);

    //void range_cont(emxArray_real_T *data, const emxArray_real_T *gsd, double
    //                time_step, const emxArray_real_T *check_list, double check)
    static QVector<double> rangeCont(QVector<double> data, double gsd, double time_step, double process_type);

    //void inter_consis(emxArray_real_T *data1, const emxArray_real_T *data2, double
    //                  type, emxArray_real_T *data)
    static QVector<double> interConsis(QVector<double> data, QString var_name, QString expression, double process_type);

    //double cycle_max(const emxArray_real_T *data, double est_max, double resol,
    //                 double obs_time, double Regression_cycle)
    static QVector<double> cycleMax(QVector<double> data, int freq, int internal_time);

    static double qtCorrelation(QVector<double> in_data1, QVector<double> in_data2, QVector<double> &out_a, QVector<double> &out_b);

    static void weightedFit(QVector<double> in_data1, QVector<double> in_data2, double &a, double &b);

    static void qtSpectral(QVector<double> in_data, double freq, QVector<double> &f, QVector<double> &yy);

    static double qtCycleMax(QVector<double> in_data, double est_max, double resol, double obs_time, double regression_cycle);

    static void qtEnpost(double lat, double lon, double roll, double pitch, double heading, double altitude,
                         double &spmx, double &spmy, double &spmz, double &aftx, double &afty, double &aftz);

    static void qt1DMaxEntropy(QVector<double> in_data, double limit_min, double a0_resol, double est_kesi_min, double est_kesi_max,
                               double kesi_resol, double wh_sample, double wh_max, QVector<double> &yy1, QVector<double> &yy2);

    // for 2-D Max Entropy
    static double qtKendall(QVector<double> in_data1, QVector<double> in_data2, double limit_min1, double limit_min2);
    static void qtStats1D(QVector<double> in_data1, double step, QVector<double> &yy1, QVector<double> &yy2);
    static void qtStats2D(QVector<double> in_data1, QVector<double> in_data2, double limit_min1, double limit_min2, double step1,
                          double step2, QVector<QVector<double> > &out);
    static void qtDistrF1(QVector<double> in_data1, QVector<double> in_data2, QVector<double> &out_FF1, QVector<double> &out_FF2);
    static void qtDistrF2(QVector<QVector<double> > in_ff, QVector<QVector<double> > &out_FF);
    static void qt2DMaxEntropy(QVector<double> ff1, QVector<double> FF1, QVector<double> ff2, QVector<double> FF2, double R, int type,
                               QVector<QVector<double> > &out);
    //static void qtFFGum(QVector<double> ff1, QVector<double> FF1, QVector<double> ff2, QVector<double> FF2, double R, QVector<QVector<double> > &out);

};

#endif // UTILS_H
