/*
 * File: flipud.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "FPSO_MOTIONS.h"
#include "flipud.h"

/* Function Definitions */

/*
 * Arguments    : double x_data[]
 *                int x_size[2]
 * Return Type  : void
 */
void b_flipud(double x_data[], int x_size[2])
{
  int m;
  int md2;
  int j;
  int i;
  double xtmp;
  m = x_size[0];
  md2 = x_size[0] >> 1;
  for (j = 0; j < 3; j++) {
    for (i = 1; i <= md2; i++) {
      xtmp = x_data[(i + x_size[0] * j) - 1];
      x_data[(i + x_size[0] * j) - 1] = x_data[(m - i) + x_size[0] * j];
      x_data[(m - i) + x_size[0] * j] = xtmp;
    }
  }
}

/*
 * Arguments    : double x_data[]
 *                int x_size[2]
 * Return Type  : void
 */
void flipud(double x_data[], int x_size[2])
{
  int m;
  int md2;
  int j;
  int i;
  double xtmp;
  m = x_size[0];
  md2 = x_size[0] >> 1;
  for (j = 0; j < 6; j++) {
    for (i = 1; i <= md2; i++) {
      xtmp = x_data[(i + x_size[0] * j) - 1];
      x_data[(i + x_size[0] * j) - 1] = x_data[(m - i) + x_size[0] * j];
      x_data[(m - i) + x_size[0] * j] = xtmp;
    }
  }
}

/*
 * File trailer for flipud.c
 *
 * [EOF]
 */
