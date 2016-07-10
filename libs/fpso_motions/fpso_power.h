/*
 * File: power.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

#ifndef __POWER_H__
#define __POWER_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "libs/commons/rt_nonfinite.h"
#include "libs/commons/rtwtypes.h"
#include "libs/commons/types.h"

/* Function Declarations */
extern void b_power(const double a[18], double y[18]);
extern void c_power(const double a[18], double y[18]);
extern void d_power(const double a_data[], const int a_size[2], double y_data[],
                    int y_size[2]);
extern void e_power(const double a_data[], const int a_size[2], double y_data[],
                    int y_size[2]);
extern void f_power(const double a_data[], const int a_size[2], double y_data[],
                    int y_size[2]);
extern void g_power(const double b_data[], const int b_size[2], double y_data[],
                    int y_size[2]);
extern void h_power(const double a[32], double y[32]);
extern void i_power(const double a[4], double y[4]);
extern void fpso_power(const double a[18], double y[18]);

#endif

/*
 * File trailer for power.h
 *
 * [EOF]
 */
