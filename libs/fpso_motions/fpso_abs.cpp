/*
 * File: abs.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "FPSO_MOTIONS.h"
#include "fpso_abs.h"
#include "libs/commons/emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const double x_data[]
 *                const int x_size[1]
 *                double y_data[]
 *                int y_size[1]
 * Return Type  : void
 */
void fpso_b_abs(const double x_data[], const int x_size[1], double y_data[], int
           y_size[1])
{
  int k;
  y_size[0] = (short)x_size[0];
  for (k = 0; k + 1 <= x_size[0]; k++) {
    y_data[k] = fabs(x_data[k]);
  }
}

/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void c_abs(const emxArray_real_T *x, emxArray_real_T *y)
{
  int k;
  k = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = x->size[1];
  emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(double));
  for (k = 0; k + 1 <= x->size[1]; k++) {
    y->data[k] = fabs(x->data[k]);
  }
}

/*
 * File trailer for abs.c
 *
 * [EOF]
 */
