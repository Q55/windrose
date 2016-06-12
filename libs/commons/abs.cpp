/*
 * File: abs.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jun-2016 15:17:02
 */

/* Include Files */
#include "rt_nonfinite.h"
//#include "max_shang_one.h"
#include "abs.h"

/* Function Definitions */

/*
 * Arguments    : const double x[1000]
 *                double y[1000]
 * Return Type  : void
 */
void b_abs(const double x[1000], double y[1000])
{
  int k;
  for (k = 0; k < 1000; k++) {
    y[k] = fabs(x[k]);
  }
}

/*
 * File trailer for abs.c
 *
 * [EOF]
 */
