/*
 * File: range_check.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 09-May-2016 16:10:52
 */

#ifndef __RANGE_CHECK_H__
#define __RANGE_CHECK_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "libs/commons/rt_nonfinite.h"
#include "libs/commons/rtwtypes.h"
#include "libs/commons/types.h"

/* Function Declarations */
extern void range_check(emxArray_real_T *data, const emxArray_real_T *b_max,
  const emxArray_real_T *b_min, const emxArray_real_T *check_list, double check);

#endif

/*
 * File trailer for range_check.h
 *
 * [EOF]
 */
