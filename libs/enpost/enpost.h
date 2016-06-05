/*
 * File: enpost.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 13-May-2016 08:54:51
 */

#ifndef __ENPOST_H__
#define __ENPOST_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "libs/commons/rt_nonfinite.h"
#include "libs/commons/rtwtypes.h"
#include "libs/commons/types.h"

/* Function Declarations */
extern void enpost(const emxArray_real_T *Lat, const emxArray_real_T *Lon,
                   emxArray_real_T *roll, emxArray_real_T *pitch, const
                   emxArray_real_T *heading, const emxArray_real_T *altitude,
                   double *spmx, double *spmy, double *spmz, double *Aftx,
                   double *Afty, double *Aftz);

#endif

/*
 * File trailer for enpost.h
 *
 * [EOF]
 */
