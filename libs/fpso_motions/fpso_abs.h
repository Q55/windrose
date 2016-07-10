/*
 * File: abs.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

#ifndef __ABS_H__
#define __ABS_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "libs/commons/rt_nonfinite.h"
#include "libs/commons/rtwtypes.h"
#include "libs/commons/types.h"

/* Function Declarations */
extern void fpso_b_abs(const double x_data[], const int x_size[1], double y_data[],
                  int y_size[1]);
extern void c_abs(const emxArray_real_T *x, emxArray_real_T *y);

#endif

/*
 * File trailer for abs.h
 *
 * [EOF]
 */
