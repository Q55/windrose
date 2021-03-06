/*
 * File: sum.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 11-Jun-2016 17:32:02
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "Statistics_2d.h"
#include "Statistics_2d_sum.h"
#include "libs/commons/emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void stats2DSum(const emxArray_real_T *x, emxArray_real_T *y)
{
  int ixstart;
  int k;
  int ix;
  int iy;
  int i;
  double s;
  ixstart = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = x->size[1];
  emxEnsureCapacity((emxArray__common *)y, ixstart, (int)sizeof(double));
  if ((x->size[0] == 0) || (x->size[1] == 0)) {
    ixstart = y->size[0] * y->size[1];
    y->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)y, ixstart, (int)sizeof(double));
    k = y->size[1];
    for (ixstart = 0; ixstart < k; ixstart++) {
      y->data[y->size[0] * ixstart] = 0.0;
    }
  } else {
    ix = -1;
    iy = -1;
    for (i = 1; i <= x->size[1]; i++) {
      ixstart = ix + 1;
      ix++;
      s = x->data[ixstart];
      for (k = 2; k <= x->size[0]; k++) {
        ix++;
        s += x->data[ix];
      }

      iy++;
      y->data[iy] = s;
    }
  }
}

/*
 * File trailer for sum.c
 *
 * [EOF]
 */
