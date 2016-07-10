/*
 * File: rdivide.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

#ifndef __RDIVIDE_H__
#define __RDIVIDE_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "libs/commons/rt_nonfinite.h"
#include "libs/commons/rtwtypes.h"
#include "libs/commons/types.h"

/* Function Declarations */
extern void b_rdivide(const double x_data[], const int x_size[2], const double
                      y_data[], double z_data[], int z_size[2]);
extern void c_rdivide(const double x_data[], const int x_size[2], double y,
                      double z_data[], int z_size[2]);
extern void d_rdivide(const double x_data[], const int x_size[2], double y,
                      double z_data[], int z_size[2]);
extern void fpso_rdivide(double x, const double y[18], double z[18]);

#endif

/*
 * File trailer for rdivide.h
 *
 * [EOF]
 */
