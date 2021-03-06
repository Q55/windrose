/*
 * File: fix.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 11-Jun-2016 17:29:56
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "fix.h"

/* Function Definitions */

/*
 * Arguments    : double *x
 * Return Type  : void
 */
void b_fix(double *x)
{
  if (*x < 0.0) {
    *x = ceil(*x);
  } else {
    *x = floor(*x);
  }
}

/*
 * File trailer for fix.c
 *
 * [EOF]
 */
