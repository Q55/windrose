/*
 * File: sum.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "FPSO_MOTIONS.h"
#include "fpso_sum.h"

/* Function Definitions */

/*
 * Arguments    : const double x[18]
 * Return Type  : double
 */
double fpso_sum(const double x[18])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 17; k++) {
    y += x[k + 1];
  }

  return y;
}

/*
 * File trailer for sum.c
 *
 * [EOF]
 */
