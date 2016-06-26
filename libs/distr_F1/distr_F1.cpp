/*
 * File: distr_F1.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 11-Jun-2016 17:20:58
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "distr_F1.h"
#include "libs/commons/emxutil.h"

/* Function Definitions */

/*
 * 由概率密度函数求分布函数
 * Arguments    : const emxArray_real_T *ff
 *                emxArray_real_T *FF
 * Return Type  : void
 */
void distr_F1(const emxArray_real_T *ff, emxArray_real_T *FF)
{
  int i0;
  int loop_ub;
  int ii;
  int jj;
  i0 = FF->size[0] * FF->size[1];
  FF->size[0] = ff->size[0];
  FF->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)FF, i0, (int)sizeof(double));
  loop_ub = ff->size[0] << 1;
  for (i0 = 0; i0 < loop_ub; i0++) {
    FF->data[i0] = 0.0;
  }

  /* 概率分布函数初始设定 */
  for (ii = 0; ii < ff->size[0]; ii++) {
    for (jj = 0; jj <= ii; jj++) {
      FF->data[ii + FF->size[0]] += ff->data[jj + ff->size[0]];
      FF->data[ii] = ff->data[ii];
    }
  }
}

/*
 * File trailer for distr_F1.c
 *
 * [EOF]
 */
