/*
 * File: cos.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 13-May-2016 08:54:51
 */

/* Include Files */
#include "rt_nonfinite.h"
//#include "enpost.h"
#include "cos.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_real_T *x
 * Return Type  : void
 */
void b_cos(emxArray_real_T *x)
{
  int nx;
  int k;
  nx = x->size[0];
  for (k = 0; k + 1 <= nx; k++) {
    x->data[k] = cos(x->data[k]);
  }
}

/*
 * File trailer for cos.c
 *
 * [EOF]
 */
