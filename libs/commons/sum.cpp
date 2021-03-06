/*
 * File: sum.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 30-Jun-2016 18:34:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "sum.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 * Return Type  : double
 */
double sum(const emxArray_real_T *x)
{
  double y;
  int k;
  if (x->size[0] == 0) {
    y = 0.0;
  } else {
    y = x->data[0];
    for (k = 2; k <= x->size[0]; k++) {
      y += x->data[k - 1];
    }
  }

  return y;
}

/*
 * File trailer for sum.c
 *
 * [EOF]
 */
