/*
 * File: mpower.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "FPSO_MOTIONS.h"
#include "mpower.h"
#include "libs/commons/emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *a
 *                emxArray_real_T *c
 * Return Type  : void
 */
void mpower(const emxArray_real_T *a, emxArray_real_T *c)
{
  int i7;
  double b_a;
  int loop_ub;
  i7 = c->size[0] * c->size[1];
  c->size[0] = 1;
  c->size[1] = a->size[1];
  emxEnsureCapacity((emxArray__common *)c, i7, (int)sizeof(double));
  b_a = a->data[0];
  loop_ub = a->size[0] * a->size[1];
  for (i7 = 0; i7 < loop_ub; i7++) {
    c->data[i7] = b_a * a->data[i7];
  }
}

/*
 * File trailer for mpower.c
 *
 * [EOF]
 */
