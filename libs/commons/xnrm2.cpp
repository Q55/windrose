/*
 * File: xnrm2.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 20-May-2016 11:10:10
 */

/* Include Files */
#include "rt_nonfinite.h"
//#include "cycle_max.h"
#include "xnrm2.h"

/* Function Definitions */

/*
 * Arguments    : int n
 *                const double x[22]
 *                int ix0
 * Return Type  : double
 */
double xnrm2(int n, const double x[22], int ix0)
{
  double y;
  double scale;
  int kend;
  int k;
  double absxk;
  double t;
  y = 0.0;
  if (n < 1) {
  } else if (n == 1) {
    y = fabs(x[ix0 - 1]);
  } else {
    scale = 2.2250738585072014E-308;
    kend = (ix0 + n) - 1;
    for (k = ix0; k <= kend; k++) {
      absxk = fabs(x[k - 1]);
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
