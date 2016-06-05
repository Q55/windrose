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
#include <QDebug>

Utils::Utils()
{
}

QVector<double> Utils::cycleMax(QVector<double> data, int window_size)
{
    QVector<double> result;
    for (int i = 0; i < data.size(); i = i + window_size) {
        cycle_max_initialize();
        emxArray_real_T *input_data;
        static int iv0[1] = { window_size };
        input_data = emxCreateND_real_T(1, iv0);
        for (int j = 0; j < input_data->size[0U]; j++) {
            input_data->data[j] = data[i];
        }
        double retval = cycle_max(input_data, 4, 0.1, 0.5, 100);
        emxDestroyArray_real_T(input_data);
        cycle_max_terminate();
        result.push_back(retval);
    }
    qDebug()<<result.size();
    return result;
}

double Utils::interConsis(QVector<double> data)
{
    //call the function inter_consis.c.
    //initial the data by QVector<double> data
    //TODO:
    double ret;
    return ret;
}
