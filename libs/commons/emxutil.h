/*
 * File: inter_consis_emxutil.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 20-May-2016 13:53:15
 */

#ifndef __INTER_CONSIS_EMXUTIL_H__
#define __INTER_CONSIS_EMXUTIL_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "types.h"

/* Function Declarations */
extern void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, int
  elementSize);
extern void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);
extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxFree_creal_T(emxArray_creal_T **pEmxArray);
extern void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int numDimensions);
extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);
extern void emxInit_int32_T1(emxArray_int32_T **pEmxArray, int numDimensions);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);
extern void emxInit_real_T1(emxArray_real_T **pEmxArray, int numDimensions);
extern void emxInit_creal_T(emxArray_creal_T **pEmxArray, int numDimensions);
extern int div_s32(int numerator, int denominator);

#endif

/*
 * File trailer for inter_consis_emxutil.h
 *
 * [EOF]
 */
