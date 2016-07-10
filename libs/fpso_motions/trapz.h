/*
 * File: trapz.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

#ifndef __TRAPZ_H__
#define __TRAPZ_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "libs/commons/rt_nonfinite.h"
#include "libs/commons/rtwtypes.h"
#include "libs/commons/types.h"

/* Function Declarations */
extern double b_trapz(const double x_data[], const int x_size[2], const double
                      y[32]);
extern double c_trapz(const double x_data[], const int x_size[2], const double
                      y_data[], const int y_size[2]);
extern double trapz(const double x_data[], const int x_size[2], const double
                    y_data[], const int y_size[1]);

#endif

/*
 * File trailer for trapz.h
 *
 * [EOF]
 */
