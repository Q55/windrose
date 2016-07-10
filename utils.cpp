#include "utils.h"
#include "math.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"
#include "libs/commons/rt_nonfinite.h"
#include "libs/commons/rtwtypes.h"
#include "libs/commons/types.h"
#include "libs/cycle_max/cycle_max.h"
#include "libs/commons/emxAPI.h"
#include "libs/cycle_max/cycle_max_terminate.h"
#include "libs/cycle_max/cycle_max_initialize.h"
#include "libs/range_check/range_check.h"
#include "libs/range_check/range_check_initialize.h"
#include "libs/range_check/range_check_terminate.h"
#include "libs/range_cont/range_cont.h"
#include "libs/range_cont/range_cont_initialize.h"
#include "libs/range_cont/range_cont_terminate.h"
#include "libs/filters/filters.h"
#include "libs/filters/filters_initialize.h"
#include "libs/filters/filters_terminate.h"
#include "libs/commons/emxAPI.h"
#include "libs/time_cont/time_cont.h"
#include "libs/time_cont/time_cont_initialize.h"
#include "libs/time_cont/time_cont_terminate.h"
#include "libs/inter_consis/inter_consis.h"
#include "libs/inter_consis/inter_consis_initialize.h"
#include "libs/inter_consis/inter_consis_terminate.h"
#include "libs/correlation/correlation.h"
#include "libs/correlation/correlation_initialize.h"
#include "libs/correlation/correlation_terminate.h"
#include "libs/weightedfit/weightedfit.h"
#include "libs/weightedfit/weightedfit_initialize.h"
#include "libs/weightedfit/weightedfit_terminate.h"
#include "libs/spectral/spectral.h"
#include "libs/spectral/spectral_initialize.h"
#include "libs/spectral/spectral_terminate.h"
#include "libs/enpost/enpost.h"
#include "libs/enpost/enpost_initialize.h"
#include "libs/enpost/enpost_terminate.h"
#include "libs/1D_max_entropy1/max_shang_one.h"
#include "libs/1D_max_entropy1/max_shang_one_initialize.h"
#include "libs/1D_max_entropy1/max_shang_one_terminate.h"
#include "libs/kendall/Kendall_initialize.h"
#include "libs/kendall/Kendall.h"
#include "libs/kendall/Kendall_terminate.h"
#include "libs/stats_1d/Statistics_1d.h"
#include "libs/stats_1d/Statistics_1d_initialize.h"
#include "libs/stats_1d/Statistics_1d_terminate.h"
#include "libs/stats_2d/Statistics_2d.h"
#include "libs/stats_2d/Statistics_2d_initialize.h"
#include "libs/stats_2d/Statistics_2d_terminate.h"
#include "libs/distr_F1/distr_F1.h"
#include "libs/distr_F1/distr_F1_initialize.h"
#include "libs/distr_F1/distr_F1_terminate.h"
#include "libs/distr_F2/distr_F2.h"
#include "libs/distr_F2/distr_F2_initialize.h"
#include "libs/distr_F2/distr_F2_terminate.h"
#include "libs/ff_AMH/ff_AMH.h"
#include "libs/ff_AMH/ff_AMH_initialize.h"
#include "libs/ff_AMH/ff_AMH_terminate.h"
#include "libs/ff_Gum/ff_Gum.h"
#include "libs/ff_Gum/ff_Gum_initialize.h"
#include "libs/ff_Gum/ff_Gum_terminate.h"
#include "libs/ff_Cla/ff_Cla.h"
#include "libs/ff_Cla/ff_Cla_initialize.h"
#include "libs/ff_Cla/ff_Cla_terminate.h"
#include "libs/ff_Fra/ff_Fra.h"
#include "libs/ff_Fra/ff_Fra_initialize.h"
#include "libs/ff_Fra/ff_Fra_terminate.h"
#include "libs/ff_GB/ff_GB.h"
#include "libs/ff_GB/ff_GB_initialize.h"
#include "libs/ff_GB/ff_GB_terminate.h"
#include "libs/diraverage/diraverage.h"
#include "libs/diraverage/diraverage_initialize.h"
#include "libs/diraverage/diraverage_terminate.h"
#include "libs/fpso_motions/FPSO_MOTIONS_initialize.h"
#include "libs/fpso_motions/FPSO_MOTIONS.h"
#include "libs/fpso_motions/FPSO_MOTIONS_terminate.h"
#include <QFile>
#include <QDebug>

Utils::Utils() {}

QVector<double> Utils::calcMax(QVector<double> data, int freq, int internal_time) {
    QVector<double> result;
    int window_size = freq * internal_time;
    for (int i = 0; i < data.size(); i = i + window_size) {
        double max_val = 0;
        for (int j = i; j < i + window_size && j < data.size(); j++) {
            if (max_val < data[j])
                max_val = data[j];
        }
        result.push_back(max_val);
    }
    //qDebug()<<data.size()<<result.size();
    return result;
}

QVector<double> Utils::calcMin(QVector<double> data, int freq, int internal_time) {
    QVector<double> result;
    int window_size = freq * internal_time;
    for (int i = 0; i < data.size(); i = i + window_size) {
        double min_val = 0;
        for (int j = i; j < i + window_size && j < data.size(); j++) {
            if (min_val > data[j])
                min_val = data[j];
        }
        result.push_back(min_val);
    }
    return result;
}

QVector<double> Utils::calcAvg(QVector<double> data, int freq, int internal_time) {
    QVector<double> result;
    int window_size = freq * internal_time;
    if (window_size <= 0) return result;
    for (int i = 0; i < data.size(); i = i + window_size) {
        double sum = 0;
        for (int j = i; j < i + window_size && j < data.size(); j++) {
            sum += data[j];
        }
        double avg = sum / window_size;
        result.push_back(avg);
    }
    return result;
}

QVector<double> Utils::calcDirAvg(QVector<double> data, int freq, int internal_time) {
    QVector<double> result;
    int window_size = freq * internal_time;
    if (window_size <= 0) return result;
    QVector<double> period_data;
    for (int i = 0; i < data.size(); i = i + window_size) {
        period_data.clear();
        for (int j = i; j < i + window_size && j < data.size(); j++) {
            period_data.push_back(data[j]);
        }

        diraverage_initialize();
        static int iv0[1] = { period_data.size() };
        emxArray_real_T *data1 = emxCreateND_real_T(1, iv0);
        for (int j = 0; j < period_data.size(); j++)
            data1->data[j] = period_data[j];

        double avg = diraverage(data1);
        result.push_back(avg);

        emxDestroyArray_real_T(data1);
        diraverage_terminate();
    }
    return result;
}

QVector<double> Utils::rangeCheck(QVector<double> data, double max, double min, double process_type) {
    QVector<double> result;
    emxArray_real_T *deal_data, *b_max, *b_min, *check_list;
    double check = 2.0;
    if (process_type == 0.0) // 标注--0   插值--1
        check = 1.0;
    else if (process_type == 1.0)
        check = 2.0;

    range_check_initialize();

    // prepare for deal_data
    static int iv0[1] = { data.size() };
    deal_data = emxCreateND_real_T(1, iv0);
    for (int i = 0; i < deal_data->size[0U]; i++) {
        deal_data->data[i] = data[i];
    }
    // prepare for b_max
    static int iv1[2] = {1, 1};
    b_max = emxCreateND_real_T(2, iv1);
    for (int i = 0; i < b_max->size[1U]; i++)
        b_max->data[b_max->size[0] * i] = max;
    // prepare for b_min
    b_min = emxCreateND_real_T(2, iv1);
    for (int i = 0; i < b_min->size[1U]; i++)
        b_min->data[b_min->size[0] * i] = min;
    // prepare for check list
    check_list = emxCreateND_real_T(2, iv1);
    for (int i = 0; i < check_list->size[1U]; i++)
        check_list->data[check_list->size[0] * i] = check;

    // call range_check() function.
    range_check(deal_data, b_max, b_min, check_list, check);

    // output the result.
    for (int i = 0; i < deal_data->size[0U]; i++){
        result.push_back(deal_data->data[i]);
    }

    emxDestroyArray_real_T(deal_data);
    emxDestroyArray_real_T(b_max);
    emxDestroyArray_real_T(b_min);
    emxDestroyArray_real_T(check_list);
    range_check_terminate();

    return result;
}

QVector<double> Utils::rangeCont(QVector<double> data, double gsd, double time_step, double process_type) {
    QVector<double> result;
    emxArray_real_T *deal_data, *array_gsd, *check_list;
    double check = 2.0;
    if (process_type == 0.0) // 标注--0   插值--1
        check = 1.0;
    else if (process_type == 1.0)
        check = 2.0;

    range_cont_initialize();

    // prepare for deal_data
    static int iv0[1] = { data.size() };
    deal_data = emxCreateND_real_T(1, iv0);
    for (int j = 0; j < deal_data->size[0U]; j++) {
        deal_data->data[j] = data[j];
    }

    // prepare for array_gsd
    static int iv1[1] = {1};
    array_gsd = emxCreateND_real_T(1, iv1);
    for (int j = 0; j < array_gsd->size[0U]; j++) {
        array_gsd->data[j] = gsd;
    }

    // prepare for check_list
    check_list = emxCreateND_real_T(1, iv1);
    for (int j = 0; j < check_list->size[0U]; j++) {
        check_list->data[j] = 1;
    }

    // call range_cont() function.
    range_cont(deal_data, array_gsd, time_step, check_list, check);

    // output the result.
    for (int i = 0; i < deal_data->size[0U]; i++) {
        result.push_back(deal_data->data[i]);
    }

    emxDestroyArray_real_T(deal_data);
    emxDestroyArray_real_T(array_gsd);
    emxDestroyArray_real_T(check_list);
    range_cont_terminate();

    return result;
}

QVector<double> Utils::timeCont(QVector<double> data, int freq, double time_row, double time_step, double process_type) {

    //QVector<double> data = {1,5,6,10,11,12,13,18,19,20};
    QVector<double> result;
    QVector<double> time_col;
    for (int i = 0; i < data.size(); ++i)
        time_col.push_back(1 / freq * i);
//    time_col.clear();
//    time_col = {1,5,6,10,11,12,13,18,19,20};
    double check = 2.0;
    if (process_type == 0.0) // 标注--0   插值--1
        check = 1.0;

    time_cont_initialize();

    int size = data.size() * 2;
    double temp[size];
    for (int i = 0; i < time_col.size(); ++i)
        temp[i] = time_col.at(i);
    int k = time_col.size();
    for (int i = 0; i < data.size(); ++i)
        temp[k++] = data.at(i);

    emxArray_real_T *deal_data =emxCreateWrapper_real_T(temp, data.size(), 2), *out; // (row, col)
    emxInitArray_real_T(&out, 2);

    // call time_cont() function.
    time_cont(deal_data, time_row, time_step, check, out);

    // output the result.
    for (int i = 0; i < out->size[0U]; i++) {
        result.push_back(out->data[i]);
    }

    emxDestroyArray_real_T(deal_data);
    emxDestroyArray_real_T(out);
    time_cont_terminate();

    return result;
}

QVector<double> Utils::interConsis(QVector<double> data, QString var_name, QString expression, double process_type) {
    QVector<double> ref_data, result;
    if(expression != "") {
        CalcExpression ce(var_name, expression);
        for (int i = 0; i < data.size(); ++i) {
            double refval = ce.calcExpr(data[i]);
            ref_data.push_back(refval);
        }
    } else {
        ref_data = data;
    }

    emxArray_real_T *data1, *data2, *out;
    double type = 1.0;
    if (process_type == 0.0)
        type = 1.0; // greater than
    else if (process_type == 1.0)
        type = 2.0; // less than
    else if (process_type == 2.0)
        type = 3.0; // equal

    inter_consis_initialize();

    // prepare for deal_data
    static int iv0[1] = {data.size()};
    data1 = emxCreateND_real_T(1, iv0);
    for (int i = 0; i < data1->size[0U]; i++) {
        data1->data[i] = data[i];
    }
    static int iv1[1] = {ref_data.size()};
    data2 = emxCreateND_real_T(1, iv1);
    for (int i = 0; i < data2->size[0U]; i++) {
        data2->data[i] = ref_data[i];
    }

    emxInitArray_real_T(&out, 2);

    // call inter_consis() function.
    inter_consis(data1, data2, type, out);

    // output the result.
    for (int i = 0; i < out->size[0U]; i++) {
        result.push_back(out->data[i]);
    }

    emxDestroyArray_real_T(data1);
    emxDestroyArray_real_T(data2);
    emxDestroyArray_real_T(out);
    time_cont_terminate();

    return result;
}

double Utils::qtFilters(QVector<double> data, double fs, QVector<double>& l_data, QVector<double>& w_data) {
    double m_data = 0;

    filters_initialize();
    emxArray_real_T *deal_data, *deal_ldata, *deal_wdata;

    // prepare for deal_data
    static int iv0[1] = { data.size() };
    deal_data = emxCreateND_real_T(1, iv0);
    for (int j = 0; j < deal_data->size[0U]; j++) {
        deal_data->data[j] = data[j];
    }

    emxInitArray_real_T(&deal_ldata, 1);
    emxInitArray_real_T(&deal_wdata, 1);

    filters(fs, deal_data, &m_data, deal_ldata, deal_wdata);

    l_data.clear();
    for (int i = 0; i < deal_ldata->size[0U]; i++) {
        l_data.push_back(deal_ldata->data[i]);
    }

    w_data.clear();
    for (int i = 0; i < deal_wdata->size[0U]; i++) {
        w_data.push_back(deal_wdata->data[i]);
    }

    emxDestroyArray_real_T(deal_data);
    emxDestroyArray_real_T(deal_ldata);
    emxDestroyArray_real_T(deal_wdata);
    filters_terminate();

    return m_data;
}

double Utils::qtCorrelation(QVector<double> in_data1, QVector<double> in_data2, QVector<double> &out_data1, QVector<double> &out_data2) {
    double index = 0.0;
    emxArray_real_T *x, *y, *a, *b;

    correlation_initialize();
    emxInitArray_real_T(&b, 2);
    emxInitArray_real_T(&a, 1);

    static int iv0[1] = { in_data1.size() };
    x = emxCreateND_real_T(1, iv0);
    for (int j = 0; j < x->size[0U]; j++)
        x->data[j] = in_data1[j];

    static int iv1[1] = { in_data2.size() };
    y = emxCreateND_real_T(1, iv1);
    for (int j = 0; j < y->size[0U]; j++)
        y->data[j] = in_data2[j];

    correlation(x, y, b, a, &index);

    for (int i = 0; i < a->size[0]; ++i) {
        out_data1.push_back(a->data[i]);
    }
    for (int i = 0; i < b->size[1]; ++i) {
        out_data2.push_back(b->data[i]);
    }

    emxDestroyArray_real_T(x);
    emxDestroyArray_real_T(y);
    emxDestroyArray_real_T(a);
    emxDestroyArray_real_T(b);

    correlation_terminate();

    return index;
}

void Utils::weightedFit(QVector<double> in_data1, QVector<double> in_data2, double &a, double &b) { // sample output not matched.

    weightedfit_initialize();
//    QVector<double> temp_data1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
//    QVector<double> temp_data2 = {2.421800555,4.836975886,6.93269427,
//                                  8.178788109,
//                                  10.10850616,
//                                  12.87113558,
//                                  14.05064164,
//                                  16.90660753,
//                                  18.08114827,
//                                  20.29035001,
//                                  22.41293223,
//                                  24.32627721,
//                                  26.38830093};
//    qDebug()<<temp_data1<<temp_data2;

    int size = in_data1.size() * 2;
    double temp[size];
    for (int i = 0; i < in_data1.size(); ++i)
        temp[i] = in_data1.at(i);
    int k = in_data1.size();
    for (int i = 0; i < in_data2.size(); ++i)
        temp[k++] = in_data2.at(i);

//    for (int i = 0; i < size; ++i)
//        qDebug()<<temp[i];

    emxArray_real_T *data =emxCreateWrapper_real_T(temp, in_data1.size(), 2); // (row, col)

    weightedfit(data, &a, &b);

    //qDebug()<<a<<","<<b;

    emxDestroyArray_real_T(data);

    time_cont_terminate();
}

void Utils::qtSpectral(QVector<double> in_data, double freq, QVector<double> &f, QVector<double> &YY) {
    spectral_initialize();

    emxArray_real_T *data, *out_f, *out_YY;
    emxInitArray_real_T(&out_f, 2);
    emxInitArray_real_T(&out_YY, 1);

    static int iv0[1] = { in_data.size() };
    data = emxCreateND_real_T(1, iv0);
    for (int j = 0; j < data->size[0U]; j++)
        data->data[j] = in_data[j];

    spectral(freq, data, out_f, out_YY);

    for(int i = 0; i < out_f->size[1]; ++i) {
        f.push_back(out_f->data[i]);
    }

    for (int i = 0; i < out_YY->size[0]; ++i) {
        YY.push_back(out_YY->data[i]);
    }

    emxDestroyArray_real_T(data);
    emxDestroyArray_real_T(out_f);
    emxDestroyArray_real_T(out_YY);
    spectral_terminate();
}

double Utils::qtCycleMax(QVector<double> in_data, double resol, double obs_time, double regression_cycle) { // sample output not matched.

    double result = 0.0;

    cycle_max_initialize();
    emxArray_real_T *data;

    static int iv0[1] = {in_data.size()};
    data = emxCreateND_real_T(1, iv0);
    for (int j = 0; j < in_data.size(); j++)
        data->data[j] = in_data[j];

    //result = cycle_max(data, 0.1, 0.5, 100);
    result = cycle_max(data, resol, obs_time, regression_cycle);

    emxDestroyArray_real_T(data);
    cycle_max_terminate();

    return result;
}

void Utils::qtEnpost(double lat, double lon, double roll, double pitch, double heading, double altitude,
                     double &spmx, double &spmy, double &spmz, double &aftx, double &afty, double &aftz) {
    emxArray_real_T *in_lat, *in_lon, *in_roll, *in_pitch, *in_heading, *in_altitude;

    enpost_initialize();

    static int iv1[1] = {1};
    in_lat = emxCreateND_real_T(1, iv1);
    for (int j = 0; j < in_lat->size[0U]; j++)
        in_lat->data[j] = lat;

    in_lon = emxCreateND_real_T(1, iv1);
    for (int j = 0; j < in_lon->size[0U]; j++)
        in_lon->data[j] = lon;

    in_roll = emxCreateND_real_T(1, iv1);
    for (int j = 0; j < in_roll->size[0U]; j++)
        in_roll->data[j] = roll;

    in_pitch = emxCreateND_real_T(1, iv1);
    for (int j = 0; j < in_pitch->size[0U]; j++)
        in_pitch->data[j] = pitch;

    in_heading = emxCreateND_real_T(1, iv1);
    for (int j = 0; j < in_heading->size[0U]; j++)
        in_heading->data[j] = heading;

    in_altitude = emxCreateND_real_T(1, iv1);
    for (int j = 0; j < in_altitude->size[0U]; j++)
        in_altitude->data[j] = altitude;

    enpost(in_lat, in_lon, in_roll, in_pitch, in_heading, in_altitude,
           &spmx, &spmy, &spmz, &aftx, &afty, &aftz);

    emxDestroyArray_real_T(in_lat);
    emxDestroyArray_real_T(in_lon);
    emxDestroyArray_real_T(in_roll);
    emxDestroyArray_real_T(in_pitch);
    emxDestroyArray_real_T(in_heading);
    emxDestroyArray_real_T(in_altitude);

    enpost_terminate();
}

void Utils::qt1DMaxEntropy(QVector<double> in_data, double limit_min, double a0_resol, double est_kesi_min, double est_kesi_max,
                           double kesi_resol, double wh_sample, double wh_max, QVector<double> &yy1, QVector<double> &yy2) {
    // sample output not totally matched.
    emxArray_real_T *data, *out_yy;
    max_shang_one_initialize();

    static int iv0[1] = {in_data.size()};
    data = emxCreateND_real_T(1, iv0);
    for (int j = 0; j < data->size[0U]; j++)
        data->data[j] = in_data[j];

    emxInitArray_real_T(&out_yy, 2);

    max_shang_one(data, limit_min, a0_resol, est_kesi_min, est_kesi_max, kesi_resol, wh_sample, wh_max, out_yy);

    for (int i = 0; i < out_yy->size[0] * out_yy->size[1]; ++i)
        qDebug()<<out_yy->data[i];


    for (int i = 0; i < out_yy->size[0]; ++i)
        yy1.push_back(out_yy->data[i]);

    for (int i = 0; i < out_yy->size[0]; ++i)
        yy2.push_back(out_yy->data[i + out_yy->size[0]]);

    emxDestroyArray_real_T(out_yy);
    emxDestroyArray_real_T(data);
    max_shang_one_terminate();
}

double Utils::qtKendall(QVector<double> in_data1, QVector<double> in_data2, double limit_min1, double limit_min2) {
    double result = 0.0;
    emxArray_real_T *data1, *data2;

    Kendall_initialize();

    static int iv0[1] = { in_data1.size() };
    data1 = emxCreateND_real_T(1, iv0);
    for (int j = 0; j < data1->size[0U]; j++)
        data1->data[j] = in_data1[j];

    static int iv1[1] = { in_data2.size() };
    data2 = emxCreateND_real_T(1, iv1);
    for (int j = 0; j < data2->size[0U]; j++)
        data2->data[j] = in_data2[j];

    result = Kendall(data1, data2, limit_min1, limit_min2);

    emxDestroyArray_real_T(data1);
    emxDestroyArray_real_T(data2);

    Kendall_terminate();
    return result;
}

void Utils::qtStats1D(QVector<double> in_data1, double step, QVector<double> &yy1, QVector<double> &yy2) {
    emxArray_real_T *data, *out_yy;
    Statistics_1d_initialize();

    static int iv0[1] = {in_data1.size()};
    data = emxCreateND_real_T(1, iv0);
    for (int j = 0; j < data->size[0U]; j++)
        data->data[j] = in_data1[j];

    emxInitArray_real_T(&out_yy, 2);

    Statistics_1d(data, step, out_yy);

    for (int i = 0; i < out_yy->size[0]; ++i)
        yy1.push_back(out_yy->data[i]);

    for (int i = 0; i < out_yy->size[0]; ++i) {
        yy2.push_back(out_yy->data[out_yy->size[0] + i]);
    }

    emxDestroyArray_real_T(out_yy);
    emxDestroyArray_real_T(data);
    Statistics_1d_terminate();
}

void Utils::qtStats2D(QVector<double> in_data1, QVector<double> in_data2, double limit_min1, double limit_min2, double step1, double step2, QVector<QVector<double> > &out) {
    emxArray_real_T *data1, *data2, *out_yy;

    Statistics_2d_initialize();

    emxInitArray_real_T(&out_yy, 2);

    static int iv0[1] = { in_data1.size() };
    data1 = emxCreateND_real_T(1, iv0);
    for (int j = 0; j < data1->size[0U]; j++)
        data1->data[j] = in_data1[j];

    static int iv1[1] = { in_data2.size() };
    data2 = emxCreateND_real_T(1, iv1);
    for (int j = 0; j < data2->size[0U]; j++)
        data2->data[j] = in_data2[j];

    Statistics_2d(data1, data2, limit_min1, limit_min2, step1, step2, out_yy);

    out.resize(out_yy->size[0]); // 34
    for (int i = 0; i < out.size(); ++i)
        out[i].resize(out_yy->size[1]);

    for (int i = 0; i < out_yy->size[1]; ++i) { // 42
        for (int j = 0; j < out_yy->size[0]; ++j) { //34
            out[j][i] = out_yy->data[i * out_yy->size[0] + j];
        }
    }

    emxDestroyArray_real_T(data1);
    emxDestroyArray_real_T(data2);
    emxDestroyArray_real_T(out_yy);
    Statistics_2d_terminate();
}

void Utils::qtDistrF1(QVector<double> in_data1, QVector<double> in_data2, QVector<double> &out_FF1, QVector<double> &out_FF2) {
    distr_F1_initialize();
    double temp[in_data1.size() + in_data2.size()];
    for (int i = 0; i < in_data1.size(); ++i)
        temp[i] = in_data1.at(i);
    for (int i = 0; i < in_data2.size(); ++i)
        temp[i + in_data1.size()] = in_data2.at(i);

    emxArray_real_T *in_data =emxCreateWrapper_real_T(temp, in_data1.size(), 2);

    emxArray_real_T *out_yy;
    emxInitArray_real_T(&out_yy, 2);

    distr_F1(in_data, out_yy);

    for (int i = 0; i < out_yy->size[0]; ++i)
        out_FF1.push_back(out_yy->data[i]);

    for (int i = 0; i < out_yy->size[0]; ++i)
        out_FF2.push_back(out_yy->data[i + out_yy->size[0]]);

    emxDestroyArray_real_T(in_data);
    emxDestroyArray_real_T(out_yy);
    distr_F1_terminate();
}

void Utils::qtDistrF2(QVector<QVector<double> > in_ff, QVector<QVector<double> > &out_FF) {

    int col = 0, row = in_ff.size();
    for (int i = 0; i < row; ++i) {
        col = in_ff.at(i).size();
        break;
    }

    for (int i = 0; i < row; ++i) {
        if (in_ff.at(i).size() != col) {
            qDebug()<<"distr_F2: 输入非矩阵";
            exit(-1);
        }
    }

    distr_F2_initialize();

    int size = row * col;
    double temp[size];

    int k = 0;
    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            temp[k++] = in_ff.at(j).at(i);
        }
    }

    emxArray_real_T *in_data =emxCreateWrapper_real_T(temp, row, col), *out;
    emxInitArray_real_T(&out, 2);

    distr_F2(in_data, out);

    out_FF.resize(out->size[0]); // 34
    for (int i = 0; i < out_FF.size(); ++i)
        out_FF[i].resize(out->size[1]);

    for (int i = 0; i < out->size[1]; ++i) { // 42
        for (int j = 0; j < out->size[0]; ++j) { //34
            out_FF[j][i] = out->data[i * out->size[0] + j];
        }
    }

    emxDestroyArray_real_T(in_data);
    emxDestroyArray_real_T(out);
    distr_F2_terminate();
}

void Utils::qt2DMaxEntropy(QVector<double> ff1, QVector<double> FF1, QVector<double> ff2, QVector<double> FF2, double R, int type,
                           QVector<QVector<double> > &out) {
    emxArray_real_T *in_ff1, *in_ff2, *in_FF1, *in_FF2, *out_yy;

    switch (type) {
    case 0: ff_AMH_initialize(); break;
    case 1: ff_Cla_initialize(); break;
    case 2: ff_Fra_initialize(); break;
    case 3: ff_GB_initialize(); break;
    case 4: ff_Gum_initialize(); break;
    default: return;
    }

    emxInitArray_real_T(&out_yy, 2);

    static int iv0[1] = { ff1.size() };
    in_ff1 = emxCreateND_real_T(1, iv0);
    for (int j = 0; j < in_ff1->size[0U]; j++)
        in_ff1->data[j] = ff1[j];

    static int iv1[1] = { FF1.size() };
    in_FF1 = emxCreateND_real_T(1, iv1);
    for (int j = 0; j < in_FF1->size[0U]; j++)
        in_FF1->data[j] = FF1[j];

    static int iv2[1] = { ff2.size() };
    in_ff2 = emxCreateND_real_T(1, iv2);
    for (int j = 0; j < in_ff2->size[0U]; j++)
        in_ff2->data[j] = ff2[j];

    static int iv3[1] = { FF2.size() };
    in_FF2 = emxCreateND_real_T(1, iv3);
    for (int j = 0; j < in_FF2->size[0U]; j++)
        in_FF2->data[j] = FF2[j];

    switch (type) {
    case 0: ff_AMH(in_ff1, in_FF1, in_ff2, in_FF2, R, out_yy); break;
    case 1: ff_Cla(in_ff1, in_FF1, in_ff2, in_FF2, R, out_yy); break;
    case 2: ff_Fra(in_ff1, in_FF1, in_ff2, in_FF2, R, out_yy); break;
    case 3: ff_GB(in_ff1, in_FF1, in_ff2, in_FF2, R, out_yy); break;
    case 4: ff_Gum(in_ff1, in_FF1, in_ff2, in_FF2, R, out_yy); break;
    default: return;
    }

    out.resize(out_yy->size[0]);
    for (int i = 0; i < out.size(); ++i)
        out[i].resize(out_yy->size[1]);

    for (int i = 0; i < out_yy->size[1]; ++i) {
        for (int j = 0; j < out_yy->size[0]; ++j) {
            out[j][i] = out_yy->data[i * out_yy->size[0] + j];
        }
    }

    emxDestroyArray_real_T(in_ff1);
    emxDestroyArray_real_T(in_FF1);
    emxDestroyArray_real_T(in_ff2);
    emxDestroyArray_real_T(in_FF2);
    emxDestroyArray_real_T(out_yy);

    switch (type) {
    case 0: ff_AMH_terminate(); break;
    case 1: ff_Cla_terminate(); break;
    case 2: ff_Fra_terminate(); break;
    case 3: ff_GB_terminate(); break;
    case 4: ff_Gum_terminate(); break;
    default: return;
    }
}

QVector<double> Utils::getQVectorFromFile(QString filename, int ignore_rows, int rd_rows, int col_index) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Open File ERROR!";
        exit(-1);
    }

    QVector<double> rd_vec_data;
    QTextStream in(&file);
    int i = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (++i <= ignore_rows) continue;
        QStringList list = line.split(",");
        if (list.size() < col_index) {
            qDebug()<<"col_index is too large";
            exit(-1);
        }
        rd_vec_data.push_back(list.at(col_index - 1).toDouble());
        if (rd_vec_data.size() == rd_rows) {
            return rd_vec_data;
        }
    }

    return rd_vec_data;
}

void Utils::qtFPSOMotions(double Hs, double Tp, double dir_wave, double Vw, double dir_win,  // input
                          double Vc, double dir_cur, double draft_aft, double draft_bow,  // input
                          double &heading, double &statoffset, double &maxoffset_ind, double &clearance, // output
                          double &maxTx, double &maxTe, double &Sf, double st_xforce[24], double st_tension[24],
                          double st_sf[24], double st_offset[24], double st_clearance[24], double st_roll[24],
                          double st_pitch[24]) {

    FPSO_MOTIONS_initialize();

    FPSO_MOTIONS(Hs, Tp, dir_wave, Vw, dir_win, Vc, dir_cur, draft_aft, draft_bow, &heading, &statoffset, &maxoffset_ind, &clearance,
                 &maxTx, &maxTe, &Sf, st_xforce, st_tension, st_sf, st_offset, st_clearance, st_roll, st_pitch);

    FPSO_MOTIONS_terminate();
}

