/*
 * File: power.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 13-May-2016 08:54:51
 */

/* Include Files */
#include "rt_nonfinite.h"
//#include "enpost.h"
#include "power.h"
#include "emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *a
 *                emxArray_real_T *y
 * Return Type  : void
 */
void power(const emxArray_real_T *a, emxArray_real_T *y)
{
  unsigned int a_idx_0;
  int k;
  a_idx_0 = (unsigned int)a->size[0];
  k = y->size[0];
  y->size[0] = (int)a_idx_0;
  emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(double));
  for (k = 0; k + 1 <= a->size[0]; k++) {
    y->data[k] = a->data[k] * a->data[k];
  }
}

/*
 * File trailer for power.c
 *
 * [EOF]
 */
