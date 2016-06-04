#include "utils.h"
#include "math.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"
#include "libs/cycle_max/rt_nonfinite.h"
#include "libs/cycle_max/rtwtypes.h"
#include "libs/cycle_max/cycle_max_types.h"
#include "libs/cycle_max/cycle_max.h"
#include "libs/cycle_max/cycle_max_emxAPI.h"
#include "libs/cycle_max/cycle_max_terminate.h"
#include "libs/cycle_max/cycle_max_initialize.h"
#include <QDebug>

Utils::Utils()
{
}

double Utils::cycleMax(QVector<double> data)
{
    //call the function cycle_max.c.
    //initial the data by QVector<double> data
    //TODO:
    double ret;
    cycle_max_initialize();
    emxArray_real_T *mdata;
    int size = 8256;
    static int iv0[1] = { size };
    mdata = emxCreateND_real_T(1, iv0);
    for (int i = 0; i < mdata->size[0U]; i++) {
        mdata->data[i] = 1.2+i;
    }
    ret = cycle_max(mdata, 4, 0.1, 0.5, 100);
    emxDestroyArray_real_T(mdata);
    cycle_max_terminate();
    qDebug()<<ret;
    return ret;
}

double Utils::interConsis(QVector<double> data)
{
    //call the function inter_consis.c.
    //initial the data by QVector<double> data
    //TODO:
    double ret;
    return ret;
}
