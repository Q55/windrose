/*
 * File: spectral.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 13-May-2016 08:43:37
 */

#ifndef __SPECTRAL_H__
#define __SPECTRAL_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "libs/commons/rt_nonfinite.h"
#include "libs/commons/rtwtypes.h"
#include "libs/commons/types.h"

/* Function Declarations */
extern void spectral(double Fs, emxArray_real_T *data, emxArray_real_T *f,
                     emxArray_real_T *YY);

#endif

/*
 * File trailer for spectral.h
 *
 * [EOF]
 */
