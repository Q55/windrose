/*
 * File: xnrm2.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "FPSO_MOTIONS.h"
#include "fpso_xnrm2.h"

/* Function Definitions */

/*
 * Arguments    : int n
 *                const emxArray_real_T *x
 * Return Type  : double
 */
double fpso_xnrm2(int n, const emxArray_real_T *x)
{
  double y;
  double scale;
  int k;
  double absxk;
  double t;
  y = 0.0;
  if (n < 1) {
  } else if (n == 1) {
    y = fabs(x->data[1]);
  } else {
    scale = 2.2250738585072014E-308;
    for (k = 2; k <= n + 1; k++) {
      absxk = fabs(x->data[k - 1]);
      if (absxk > scale) {
        t = scale / absxk;
        y = 1.0 + y * t * t;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }
    }

    y = scale * sqrt(y);
  }

  return y;
}

/*
 * File trailer for xnrm2.c
 *
 * [EOF]
 */
