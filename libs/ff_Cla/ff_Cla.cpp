/*
 * File: ff_Cla.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 11-Jun-2016 17:24:35
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "ff_Cla.h"
#include "libs/commons/emxutil.h"

/* Function Declarations */
static double rt_powd_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d0;
  double d1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d0 = fabs(u0);
    d1 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d0 == 1.0) {
        y = rtNaN;
      } else if (d0 > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/*
 * 利用Clayton Couple函数模拟二维最大熵函数
 *  R：肯德尔系数
 * ff1,ff2表示概率密度函数
 * FF1,FF2表示分布函数
 * Arguments    : const emxArray_real_T *ff1
 *                const emxArray_real_T *FF1
 *                const emxArray_real_T *ff2
 *                const emxArray_real_T *FF2
 *                double R
 *                emxArray_real_T *b_ff_Cla
 * Return Type  : void
 */
void ff_Cla(const emxArray_real_T *ff1, const emxArray_real_T *FF1, const
            emxArray_real_T *ff2, const emxArray_real_T *FF2, double R,
            emxArray_real_T *b_ff_Cla)
{
  double sita_Cla;
  int i0;
  int loop_ub;
  unsigned int kk;
  int ii;
  boolean_T exitg1;
  unsigned int ll;
  int jj;
  boolean_T exitg2;
  sita_Cla = 2.0 * R / (1.0 - R);
  i0 = b_ff_Cla->size[0] * b_ff_Cla->size[1];
  b_ff_Cla->size[0] = ff1->size[0];
  b_ff_Cla->size[1] = ff2->size[0];
  emxEnsureCapacity((emxArray__common *)b_ff_Cla, i0, (int)sizeof(double));
  loop_ub = ff1->size[0] * ff2->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_ff_Cla->data[i0] = 0.0;
  }

  /* 概率密度函数初始设定 */
  kk = 0U;
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= ff1->size[0] - 1)) {
    kk++;
    if (FF1->data[(int)kk - 1] >= 1.0) {
      exitg1 = true;
    } else {
      ll = 0U;
      jj = 0;
      exitg2 = false;
      while ((!exitg2) && (jj <= ff2->size[0] - 1)) {
        ll++;
        if (FF2->data[(int)ll - 1] >= 1.0) {
          exitg2 = true;
        } else {
          if ((FF1->data[(int)kk - 1] == 0.0) || (FF2->data[(int)ll - 1] == 0.0))
          {
            b_ff_Cla->data[((int)kk + b_ff_Cla->size[0] * ((int)ll - 1)) - 1] =
              0.0;
          } else {
            /* copula函数的分子项 */
            b_ff_Cla->data[((int)kk + b_ff_Cla->size[0] * ((int)ll - 1)) - 1] =
              ff1->data[ii] * ff2->data[jj] * ((1.0 + sita_Cla) * rt_powd_snf
              (FF1->data[(int)kk - 1] * FF2->data[(int)ll - 1], -sita_Cla - 1.0)
              * rt_powd_snf((rt_powd_snf(FF1->data[(int)kk - 1], -sita_Cla) +
                             rt_powd_snf(FF2->data[(int)ll - 1], -sita_Cla)) -
                            1.0, -2.0 - 1.0 / sita_Cla));
          }

          jj++;
        }
      }

      ii++;
    }
  }
}

/*
 * File trailer for ff_Cla.c
 *
 * [EOF]
 */
