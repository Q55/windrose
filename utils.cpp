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
#include <QDebug>

Utils::Utils()
{
}

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

//void range_check(emxArray_real_T *data, const emxArray_real_T *b_max,
//                 const emxArray_real_T *b_min, const emxArray_real_T *check_list, double check)
QVector<double> Utils::rangeCheck(QVector<double> data, double max, double min, double process_type) {
    QVector<double> result;
    emxArray_real_T *deal_data, *b_max, *b_min, *check_list;
    double check = 2.0;
    if (process_type == 0.0) // 标注--0   插值--1
        check = 1.0;
    else if (process_type == 1.0)
        check = 2.0;

    qDebug()<<"range check type = "<<process_type;
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

//void range_cont(emxArray_real_T *data, const emxArray_real_T *gsd, double
//                time_step, const emxArray_real_T *check_list, double check)
QVector<double> Utils::rangeCont(QVector<double> data, double gsd, double time_step, double process_type) {
    QVector<double> result;
    emxArray_real_T *deal_data, *array_gsd, *check_list;
    double check = 2.0;
    if (process_type == 0.0) // 标注--0   插值--1
        check = 1.0;
    else if (process_type == 1.0)
        check = 2.0;

    qDebug()<<"range cont type = "<<process_type;

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

//void time_cont(const emxArray_real_T *data, double time_row, double time_step,
//               double check, emxArray_real_T *data_out)
QVector<double> Utils::timeCont(QVector<double> data, int freq, double time_row, double time_step, double process_type) {

    //QVector<double> data = {1,5,6,10,11,12,13,18,19,20};
    QVector<double> result;
    QVector<double> time_col;
    for (int i = 0; i < data.size(); ++i)
        time_col.push_back(1 / freq * i);
    //time_col.clear();
    //time_col = {1,5,6,10,11,12,13,18,19,20};
    qDebug()<<"time cont type = "<<process_type;
    emxArray_real_T *deal_data, *out;
    double check = 2.0;
    if (process_type == 0.0) // 标注--0   插值--1
        check = 1.0;

    time_cont_initialize();

    // prepare for deal_data
    static int iv0[2] = {data.size(), data.size() };
    deal_data = emxCreateND_real_T(2, iv0);
    for (int i = 0; i < deal_data->size[0U]; i++) {
        deal_data->data[i] = time_col[i];
    }
    for (int j = 0; j < deal_data->size[1U]; j++) {
        deal_data->data[deal_data->size[0] + j] = data[j];
    }

    emxInitArray_real_T(&out, 2);

    // call time_cont() function.
    time_cont(deal_data, time_row, time_step, check, out);

    // output the result.
    for (int i = 0; i < out->size[0U]; i++) {
        result.push_back(out->data[i]);
    }
    qDebug()<<result.size();
    for (int i = 0; i < result.size(); i++)
        qDebug()<<result.at(i);

    emxDestroyArray_real_T(deal_data);
    emxDestroyArray_real_T(out);
    time_cont_terminate();

    return result;
}

//void inter_consis(emxArray_real_T *data1, const emxArray_real_T *data2, double
//                  type, emxArray_real_T *data)
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

    qDebug()<<"inter consis type = "<<process_type;
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
//    qDebug()<<result.size();
//    for (int i = 0; i < result.size(); i++)
//        qDebug()<<result.at(i);

    emxDestroyArray_real_T(data1);
    emxDestroyArray_real_T(data2);
    emxDestroyArray_real_T(out);
    time_cont_terminate();

    return result;

}

//void filters(double Fs, const emxArray_real_T *data, double *Mdata,
//             emxArray_real_T *Ldata, emxArray_real_T *Wdata)
double Utils::qtFilters(QVector<double> data, double fs, QVector<double>& l_data, QVector<double>& w_data) {
    double m_data = 0;
    emxArray_real_T *deal_data, *deal_ldata, *deal_wdata;

    filters_initialize();

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


//double cycle_max(const emxArray_real_T *data, double est_max, double resol,
//                 double obs_time, double Regression_cycle)
QVector<double> Utils::cycleMax(QVector<double> data, int freq, int internal_time) {
    QVector<double> result;
    int window_size = freq * internal_time;
    for (int i = 0; i < data.size(); i = i + window_size) {
        cycle_max_initialize();
        emxArray_real_T *input_data;
        static int iv0[1] = { window_size };
        input_data = emxCreateND_real_T(1, iv0);
        int k = i;
        for (int j = 0; j < input_data->size[0U]; j++) {
            input_data->data[j] = data[k++];
        }
        double retval = cycle_max(input_data, 4, 0.1, 0.5, 100);
        emxDestroyArray_real_T(input_data);
        cycle_max_terminate();
        result.push_back(retval);
    }
    //qDebug()<<result.size();
    return result;
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
        //qDebug()<<a->data[i];
        out_data1.push_back(a->data[i]);
    }
    //qDebug()<<"index = "<<index;
    for (int i = 0; i < b->size[1]; ++i) {
        //qDebug()<<b->data[i];
        out_data2.push_back(b->data[i]);
    }

    emxDestroyArray_real_T(x);
    emxDestroyArray_real_T(y);
    emxDestroyArray_real_T(a);
    emxDestroyArray_real_T(b);

    correlation_terminate();

    return index;
}

void Utils::weightedFit(QVector<double> in_data1, QVector<double> in_data2, double &a, double &b) {

    emxArray_real_T *data;

    weightedfit_initialize();

    // prepare for deal_data
    static int iv0[2] = {in_data1.size(), in_data2.size() };
    data = emxCreateND_real_T(2, iv0);
    for (int i = 0; i < data->size[0U]; i++) {
        data->data[i] = in_data1[i];
    }
    for (int j = 0; j < data->size[1U]; j++) {
        data->data[data->size[0] + j] = in_data2[j];
    }

    weightedfit(data, &a, &b);

    qDebug()<<"a = "<<a<<", b = "<<b;

    emxDestroyArray_real_T(data);

    time_cont_terminate();
}

void Utils::qtSpectral(QVector<double> in_data, double freq, QVector<double> &f, QVector<double> &YY) {
    emxArray_real_T *data, *out_f, *out_YY;

    spectral_initialize();

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

    qDebug()<<"data size = "<<in_data.size();
    qDebug()<<"f size0 = "<<out_f->size[0];
    qDebug()<<"f size1 = "<<out_f->size[1];
    qDebug()<<"YY size = "<<out_YY->size[0];

    emxDestroyArray_real_T(data);
    emxDestroyArray_real_T(out_f);
    emxDestroyArray_real_T(out_YY);
    spectral_terminate();

}

double Utils::qtCycleMax(QVector<double> in_data, double est_max, double resol, double obs_time, double regression_cycle) {

    //qDebug()<<"in data size = "<<in_data.size();
    double result = 0.0;
    emxArray_real_T *data;

    cycle_max_initialize();

    static int iv0[1] = {in_data.size()};
    data = emxCreateND_real_T(1, iv0);
    for (int j = 0; j < data->size[0U]; j++)
        data->data[j] = in_data[j];

    result = cycle_max(data, est_max, resol, obs_time, regression_cycle);

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
//    qDebug()<<"limit_min = "<<limit_min<<", a0_resol = "<<a0_resol<<", est_kesi_min = "<<est_kesi_min;
//    qDebug()<<"est_kesi_max = "<<est_kesi_max<<", kesi_resol = "<<kesi_resol<<", wh_sample = "<<wh_sample<<", wh_max = "<<wh_max;
//    qDebug()<<"input data size = "<<in_data.size();
    emxArray_real_T *data, *out_yy;
    max_shang_one_initialize();

    static int iv0[1] = {in_data.size()};
    data = emxCreateND_real_T(1, iv0);
    for (int j = 0; j < data->size[0U]; j++)
        data->data[j] = in_data[j];

    emxInitArray_real_T(&out_yy, 2);

    qDebug()<<"11111111";

    max_shang_one(data, limit_min, a0_resol, est_kesi_min, est_kesi_max, kesi_resol, wh_sample, wh_max, out_yy);

    qDebug()<<"in data size = "<<in_data.size();
    qDebug()<<"out data size0 = "<<out_yy->size[0];
    qDebug()<<"out data size1 = "<<out_yy->size[1];

    for (int i = 0; i < out_yy->size[0]; ++i)
        yy1.push_back(out_yy->data[i]);

    for (int i = 0; i < out_yy->size[1]; ++i)
        yy2.push_back(out_yy->data[i]);

    emxDestroyArray_real_T(out_yy);
    emxDestroyArray_real_T(data);
    max_shang_one_terminate();
}


