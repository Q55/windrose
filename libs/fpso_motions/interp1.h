/*
 * File: interp1.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

#ifndef __INTERP1_H__
#define __INTERP1_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "libs/commons/rt_nonfinite.h"
#include "libs/commons/rtwtypes.h"
#include "libs/commons/types.h"

/* Function Declarations */
extern double b_interp1(const double varargin_1[9], const double varargin_2[9],
  double varargin_3);
extern void c_interp1(const double varargin_1[28], const double varargin_2[28],
                      const emxArray_real_T *varargin_3, emxArray_real_T *Vq);
extern void d_interp1(const emxArray_real_T *varargin_1, const emxArray_real_T
                      *varargin_2, const emxArray_real_T *varargin_3,
                      emxArray_real_T *Vq);
extern void e_interp1(const double varargin_1_data[], const int varargin_1_size
                      [2], const double varargin_2_data[], const int
                      varargin_2_size[2], const double varargin_3_data[], const
                      int varargin_3_size[2], double Vq_data[], int Vq_size[2]);
extern void f_interp1(const double varargin_1_data[], const int varargin_1_size
                      [2], const double varargin_2_data[], const int
                      varargin_2_size[1], const double varargin_3_data[], const
                      int varargin_3_size[2], double Vq_data[], int Vq_size[2]);
extern double g_interp1(const emxArray_real_T *varargin_1, const emxArray_real_T
  *varargin_2, double varargin_3);
extern double interp1(double varargin_3);

#endif

/*
 * File trailer for interp1.h
 *
 * [EOF]
 */
