/*
 * File: exp.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "FPSO_MOTIONS.h"
#include "exp.h"

/* Function Definitions */

/*
 * Arguments    : double x_data[]
 *                int x_size[2]
 * Return Type  : void
 */
void b_exp(double x_data[], int x_size[2])
{
  int nx;
  int k;
  nx = x_size[1];
  for (k = 0; k + 1 <= nx; k++) {
    x_data[k] = exp(x_data[k]);
  }
}

/*
 * File trailer for exp.c
 *
 * [EOF]
 */
