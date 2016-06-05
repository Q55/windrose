/*
 * File: filters.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 01-Jun-2016 09:36:33
 */

#ifndef __FILTERS_H__
#define __FILTERS_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "libs/commons/rt_nonfinite.h"
#include "libs/commons/rtwtypes.h"
#include "libs/commons/types.h"

/* Function Declarations */
extern void filters(double Fs, const emxArray_real_T *data, double *Mdata,
                    emxArray_real_T *Ldata, emxArray_real_T *Wdata);

#endif

/*
 * File trailer for filters.h
 *
 * [EOF]
 */
