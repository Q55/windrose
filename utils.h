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
    static QVector<double> calcDirAvg(QVector<double> data, int freq, int internal_time);

    static double qtFilters(QVector<double> data, double fs, QVector<double>& l_data, QVector<double>& w_data);

    static QVector<double> rangeCheck(QVector<double> data, double max, double min, double process_type);

    static QVector<double> timeCont(QVector<double> data, int freq, double time_row, double time_step, double process_type);

    static QVector<double> rangeCont(QVector<double> data, double gsd, double time_step, double process_type);

    static QVector<double> interConsis(QVector<double> data, QString var_name, QString expression, double process_type);

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

    static QVector<double> getQVectorFromFile(QString filename, int ignore_rows, int rd_rows, int col_index);
};

#endif // UTILS_H
