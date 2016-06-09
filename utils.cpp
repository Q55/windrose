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
    qDebug()<<data.size()<<result.size();
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
QVector<double> Utils::rangeCheck(QVector<double> data, double max, double min, int process_type) {
    QVector<double> result;
    emxArray_real_T *deal_data, *b_max, *b_min, *check_list;
    double check = 0.0;
    if (process_type == 0) // 标注--0   插值--1
        check = 1.0;

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
QVector<double> Utils::rangeCont(QVector<double> data, double gsd, double time_step, int process_type) {
    QVector<double> result;
    emxArray_real_T *deal_data, *array_gsd, *check_list;
    double check = 2.0;
    if (process_type == 0) // 标注--0   插值--1
        check = 1.0;

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
QVector<double> Utils::timeCont(QVector<double> data, int freq, double time_row, double time_step, int process_type) {

    QVector<double> result;
    QVector<double> time_col;
    for (int i = 0; i < data.size(); ++i)
        time_col.push_back(1 / freq * i);
//    time_col.clear();
//    time_col = {1,5,6,10,11,12,13,18,19,20};

    emxArray_real_T *deal_data, *out;
    double check = 2.0;
    if (process_type == 0) // 标注--0   插值--1
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
QVector<double> Utils::interConsis(QVector<double> data, QString expression, int process_type) {
    QVector<double> ref_data, result;
    ref_data = {1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 5};

    emxArray_real_T *data1, *data2, *out;
    double type = 2.0;
    if (process_type == 0) // 标注--0   插值--1
        type = 1.0;

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
    qDebug()<<result.size();
    for (int i = 0; i < result.size(); i++)
        qDebug()<<result.at(i);

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
QVector<double> Utils::cycleMax(QVector<double> data, int freq, int internal_time)
{
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
    qDebug()<<result.size();
    return result;
}
