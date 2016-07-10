/*
 * File: power.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "FPSO_MOTIONS.h"
#include "fpso_power.h"
#include "FPSO_MOTIONS_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : const double a[18]
 *                double y[18]
 * Return Type  : void
 */
void b_power(const double a[18], double y[18])
{
  int k;
  for (k = 0; k < 18; k++) {
    y[k] = rt_powd_snf(a[k], 3.561);
  }
}

/*
 * Arguments    : const double a[18]
 *                double y[18]
 * Return Type  : void
 */
void c_power(const double a[18], double y[18])
{
  int k;
  for (k = 0; k < 18; k++) {
    y[k] = a[k] * a[k];
  }
}

/*
 * Arguments    : const double a_data[]
 *                const int a_size[2]
 *                double y_data[]
 *                int y_size[2]
 * Return Type  : void
 */
void d_power(const double a_data[], const int a_size[2], double y_data[], int
             y_size[2])
{
  int k;
  y_size[0] = 1;
  y_size[1] = (short)a_size[1];
  for (k = 0; k + 1 <= a_size[1]; k++) {
    y_data[k] = a_data[k] * a_data[k];
  }
}

/*
 * Arguments    : const double a_data[]
 *                const int a_size[2]
 *                double y_data[]
 *                int y_size[2]
 * Return Type  : void
 */
void e_power(const double a_data[], const int a_size[2], double y_data[], int
             y_size[2])
{
  int k;
  y_size[0] = 1;
  y_size[1] = (short)a_size[1];
  for (k = 0; k + 1 <= a_size[1]; k++) {
    y_data[k] = rt_powd_snf(a_data[k], -5.0);
  }
}

/*
 * Arguments    : const double a_data[]
 *                const int a_size[2]
 *                double y_data[]
 *                int y_size[2]
 * Return Type  : void
 */
void f_power(const double a_data[], const int a_size[2], double y_data[], int
             y_size[2])
{
  int k;
  y_size[0] = 1;
  y_size[1] = (short)a_size[1];
  for (k = 0; k + 1 <= a_size[1]; k++) {
    y_data[k] = rt_powd_snf(a_data[k], -4.0);
  }
}

/*
 * Arguments    : const double b_data[]
 *                const int b_size[2]
 *                double y_data[]
 *                int y_size[2]
 * Return Type  : void
 */
void g_power(const double b_data[], const int b_size[2], double y_data[], int
             y_size[2])
{
  int k;
  y_size[0] = 1;
  y_size[1] = (short)b_size[1];
  for (k = 0; k + 1 <= b_size[1]; k++) {
    y_data[k] = rt_powd_snf(3.0, b_data[k]);
  }
}

/*
 * Arguments    : const double a[32]
 *                double y[32]
 * Return Type  : void
 */
void h_power(const double a[32], double y[32])
{
  int k;
  for (k = 0; k < 32; k++) {
    y[k] = rt_powd_snf(a[k], 2.0);
  }
}

/*
 * Arguments    : const double a[4]
 *                double y[4]
 * Return Type  : void
 */
void i_power(const double a[4], double y[4])
{
  int k;
  for (k = 0; k < 4; k++) {
    y[k] = rt_powd_snf(a[k], 2.0);
  }
}

/*
 * Arguments    : const double a[18]
 *                double y[18]
 * Return Type  : void
 */
void fpso_power(const double a[18], double y[18])
{
  int k;
  for (k = 0; k < 18; k++) {
    y[k] = rt_powd_snf(a[k], 0.468);
  }
}

/*
 * File trailer for power.c
 *
 * [EOF]
 */
