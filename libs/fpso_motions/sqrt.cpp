/*
 * File: sqrt.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "FPSO_MOTIONS.h"
#include "sqrt.h"

/* Function Definitions */

/*
 * Arguments    : double x[18]
 * Return Type  : void
 */
void b_sqrt(double x[18])
{
  int k;
  for (k = 0; k < 18; k++) {
    x[k] = sqrt(x[k]);
  }
}

/*
 * Arguments    : emxArray_real_T *x
 * Return Type  : void
 */
void c_sqrt(emxArray_real_T *x)
{
  int nx;
  int k;
  nx = x->size[1];
  for (k = 0; k + 1 <= nx; k++) {
    x->data[k] = sqrt(x->data[k]);
  }
}

/*
 * Arguments    : double x[4]
 * Return Type  : void
 */
void d_sqrt(double x[4])
{
  int k;
  for (k = 0; k < 4; k++) {
    x[k] = sqrt(x[k]);
  }
}

/*
 * File trailer for sqrt.c
 *
 * [EOF]
 */
