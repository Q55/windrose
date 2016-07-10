/*
 * File: trapz.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "FPSO_MOTIONS.h"
#include "trapz.h"

/* Function Definitions */

/*
 * Arguments    : const double x_data[]
 *                const int x_size[2]
 *                const double y[32]
 * Return Type  : double
 */
double b_trapz(const double x_data[], const int x_size[2], const double y[32])
{
  double z;
  int ix;
  int iy;
  double b_x_data[1248];
  double ylast;
  int k;
  ix = x_size[0] * x_size[1];
  for (iy = 0; iy < ix; iy++) {
    b_x_data[iy] = x_data[iy];
  }

  for (ix = 0; ix < 31; ix++) {
    b_x_data[ix] = b_x_data[ix + 1] - b_x_data[ix];
  }

  z = 0.0;
  ix = -1;
  iy = 0;
  ylast = y[0];
  for (k = 0; k < 31; k++) {
    iy++;
    if (x_size[1] == 0) {
      z += (ylast + y[iy]) / 2.0;
    } else {
      ix++;
      z += b_x_data[ix] * ((ylast + y[iy]) / 2.0);
    }

    ylast = y[iy];
  }

  return z;
}

/*
 * Arguments    : const double x_data[]
 *                const int x_size[2]
 *                const double y_data[]
 *                const int y_size[2]
 * Return Type  : double
 */
double c_trapz(const double x_data[], const int x_size[2], const double y_data[],
               const int y_size[2])
{
  double z;
  int iy;
  int ix;
  double b_x_data[1248];
  int vlen;
  double ylast;
  int k;
  iy = x_size[0] * x_size[1];
  for (ix = 0; ix < iy; ix++) {
    b_x_data[ix] = x_data[ix];
  }

  vlen = y_size[1] - 1;
  for (iy = 1; iy <= vlen; iy++) {
    b_x_data[iy - 1] = b_x_data[iy] - b_x_data[iy - 1];
  }

  if (y_size[1] == 0) {
    z = 0.0;
  } else {
    z = 0.0;
    ix = -1;
    iy = 0;
    ylast = y_data[0];
    for (k = 0; k < vlen; k++) {
      iy++;
      if (x_size[1] == 0) {
        z += (ylast + y_data[iy]) / 2.0;
      } else {
        ix++;
        z += b_x_data[ix] * ((ylast + y_data[iy]) / 2.0);
      }

      ylast = y_data[iy];
    }
  }

  return z;
}

/*
 * Arguments    : const double x_data[]
 *                const int x_size[2]
 *                const double y_data[]
 *                const int y_size[1]
 * Return Type  : double
 */
double trapz(const double x_data[], const int x_size[2], const double y_data[],
             const int y_size[1])
{
  double z;
  int iy;
  int ix;
  double b_x_data[1248];
  int vlen;
  double ylast;
  int k;
  iy = x_size[0] * x_size[1];
  for (ix = 0; ix < iy; ix++) {
    b_x_data[ix] = x_data[ix];
  }

  vlen = y_size[0] - 1;
  for (iy = 1; iy <= vlen; iy++) {
    b_x_data[iy - 1] = b_x_data[iy] - b_x_data[iy - 1];
  }

  if (y_size[0] == 0) {
    z = 0.0;
  } else {
    z = 0.0;
    ix = -1;
    iy = 0;
    ylast = y_data[0];
    for (k = 0; k < vlen; k++) {
      iy++;
      if (x_size[1] == 0) {
        z += (ylast + y_data[iy]) / 2.0;
      } else {
        ix++;
        z += b_x_data[ix] * ((ylast + y_data[iy]) / 2.0);
      }

      ylast = y_data[iy];
    }
  }

  return z;
}

/*
 * File trailer for trapz.c
 *
 * [EOF]
 */
