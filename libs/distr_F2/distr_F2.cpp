/*
 * File: distr_F2.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 11-Jun-2016 17:22:04
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "distr_F2.h"
#include "libs/commons/emxutil.h"

/* Function Definitions */

/*
 * 由概率密度函数求分布函数
 * ff的第一行和第一列是概率密度函数ff的坐标轴
 * Arguments    : const emxArray_real_T *ff
 *                emxArray_real_T *FF
 * Return Type  : void
 */
void distr_F2(const emxArray_real_T *ff, emxArray_real_T *FF)
{
  int i0;
  int loop_ub;
  int ii;
  int ll;
  int jj;
  i0 = FF->size[0] * FF->size[1];
  FF->size[0] = ff->size[0];
  FF->size[1] = ff->size[1];
  emxEnsureCapacity((emxArray__common *)FF, i0, (int)sizeof(double));
  loop_ub = ff->size[0] * ff->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    FF->data[i0] = 0.0;
  }

  /* 概率分布函数初始设定 */
  loop_ub = ff->size[0] - 1;
  for (i0 = 0; i0 <= loop_ub; i0++) {
    FF->data[i0] = ff->data[i0];
  }

  loop_ub = ff->size[1] - 1;
  for (i0 = 0; i0 <= loop_ub; i0++) {
    FF->data[FF->size[0] * i0] = ff->data[ff->size[0] * i0];
  }

  for (ii = 1; ii - 1 <= ff->size[0] - 2; ii++) {
    for (ll = 0; ll <= ff->size[1] - 2; ll++) {
      for (jj = 0; jj <= ll; jj++) {
        FF->data[ii + FF->size[0] * (ll + 1)] += ff->data[ii + ff->size[0] * (jj
          + 1)];
      }
    }
  }
}

/*
 * File trailer for distr_F2.c
 *
 * [EOF]
 */
