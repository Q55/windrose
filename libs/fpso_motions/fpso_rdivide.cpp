/*
 * File: rdivide.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "FPSO_MOTIONS.h"
#include "fpso_rdivide.h"

/* Function Definitions */

/*
 * Arguments    : const double x_data[]
 *                const int x_size[2]
 *                const double y_data[]
 *                double z_data[]
 *                int z_size[2]
 * Return Type  : void
 */
void b_rdivide(const double x_data[], const int x_size[2], const double y_data[],
               double z_data[], int z_size[2])
{
  int loop_ub;
  int i4;
  z_size[0] = 1;
  z_size[1] = x_size[1];
  loop_ub = x_size[0] * x_size[1];
  for (i4 = 0; i4 < loop_ub; i4++) {
    z_data[i4] = x_data[i4] / y_data[i4];
  }
}

/*
 * Arguments    : const double x_data[]
 *                const int x_size[2]
 *                double y
 *                double z_data[]
 *                int z_size[2]
 * Return Type  : void
 */
void c_rdivide(const double x_data[], const int x_size[2], double y, double
               z_data[], int z_size[2])
{
  int loop_ub;
  int i5;
  z_size[0] = x_size[0];
  z_size[1] = 6;
  loop_ub = x_size[0] * x_size[1];
  for (i5 = 0; i5 < loop_ub; i5++) {
    z_data[i5] = x_data[i5] / y;
  }
}

/*
 * Arguments    : const double x_data[]
 *                const int x_size[2]
 *                double y
 *                double z_data[]
 *                int z_size[2]
 * Return Type  : void
 */
void d_rdivide(const double x_data[], const int x_size[2], double y, double
               z_data[], int z_size[2])
{
  int loop_ub;
  int i6;
  z_size[0] = x_size[0];
  z_size[1] = 3;
  loop_ub = x_size[0] * x_size[1];
  for (i6 = 0; i6 < loop_ub; i6++) {
    z_data[i6] = x_data[i6] / y;
  }
}

/*
 * Arguments    : double x
 *                const double y[18]
 *                double z[18]
 * Return Type  : void
 */
void fpso_rdivide(double x, const double y[18], double z[18])
{
  int i3;
  for (i3 = 0; i3 < 18; i3++) {
    z[i3] = x / y[i3];
  }
}

/*
 * File trailer for rdivide.c
 *
 * [EOF]
 */
