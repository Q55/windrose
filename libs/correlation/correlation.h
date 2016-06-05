/*
 * File: correlation.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 12-May-2016 15:49:24
 */

#ifndef __CORRELATION_H__
#define __CORRELATION_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "libs/commons/rtwtypes.h"
#include "libs/commons/types.h"

/* Function Declarations */
extern void correlation(const emxArray_real_T *x, const emxArray_real_T *y,
  emxArray_real_T *b, emxArray_real_T *a, double *b_index);

#endif

/*
 * File trailer for correlation.h
 *
 * [EOF]
 */
