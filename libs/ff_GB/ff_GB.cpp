/*
 * File: ff_GB.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 11-Jun-2016 17:26:48
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "ff_GB.h"
#include "libs/commons/emxutil.h"

/* Function Declarations */
static double fun_GB(double sita_GB, double R);

/* Function Definitions */

/*
 * fun=@(x) exp(-2.*x./sita_GB)./x;
 *  format long
 * Arguments    : double sita_GB
 *                double R
 * Return Type  : double
 */
static double fun_GB(double sita_GB, double R)
{
  double interg;
  double ii;
  interg = 0.0;
  for (ii = 1.0; exp(-2.0 * ii / sita_GB) / ii * 1.0E-8 > 1.0E-11; ii += 1.0E-8)
  {
    interg += exp(-2.0 * ii / sita_GB) / ii * 1.0E-8;
  }

  return (1.0 - exp(2.0 / sita_GB) * interg) - R;
}

/*
 * 利用Gumbel_Barnett Copula函数模拟二维最大熵函数
 *  R：肯德尔系数
 * ff1,ff2表示概率密度函数
 * FF1,FF2表示分布函数
 * Gumbel_Barnett Copula
 * Arguments    : const emxArray_real_T *ff1
 *                const emxArray_real_T *FF1
 *                const emxArray_real_T *ff2
 *                const emxArray_real_T *FF2
 *                double R
 *                emxArray_real_T *b_ff_GB
 * Return Type  : void
 */
void ff_GB(const emxArray_real_T *ff1, const emxArray_real_T *FF1, const
           emxArray_real_T *ff2, const emxArray_real_T *FF2, double R,
           emxArray_real_T *b_ff_GB)
{
  double root;
  double step;
  double sita_GB;
  boolean_T exitg3;
  int i0;
  int a1;
  double b_a1;
  double b1;
  double c1;
  double ya;
  double yb;
  double yc;
  int exitg4;
  int loop_ub;
  unsigned int kk;
  int ii;
  boolean_T exitg1;
  unsigned int ll;
  int jj;
  boolean_T exitg2;

  /* 目前尚不能求出所有的根 */
  /* a、b为区间左右端点值，tol是精度，k为计算次数，x为使用k次二分法得到的小区间[ak，bk]的中点值，y(x)为x的函数值，wuca=|ak-bk|/2。 */
  root = 0.0;

  /*  k=1; */
  step = 0.99;
  sita_GB = 9.99999999E+8;
  exitg3 = false;
  while ((!exitg3) && (root == 0.0)) {
    i0 = (int)((0.9 + (step - 0.01)) / step);
    for (a1 = 0; a1 < i0; a1++) {
      b_a1 = 0.01 + (double)a1 * step;
      b1 = b_a1 + step;
      c1 = (b_a1 + b1) / 2.0;
      ya = fun_GB(b_a1, R);
      yb = fun_GB(b1, R);
      yc = fun_GB(c1, R);

      /* 程序中调用的fun_GB.m 为函数 */
      do {
        exitg4 = 0;
        if (fabs(b1 - b_a1) > 1.0E-6) {
          /*      k=k+1; */
          if (ya * yc < 0.0) {
            b1 = c1;
            c1 = (b_a1 + c1) / 2.0;
            ya = fun_GB(b_a1, R);
            yb = fun_GB(b1, R);
            yc = fun_GB(c1, R);
          } else if (yc * yb < 0.0) {
            b_a1 = c1;
            c1 = (c1 + b1) / 2.0;
            ya = fun_GB(b_a1, R);
            yb = fun_GB(b1, R);
            yc = fun_GB(c1, R);
          } else {
            if (ya == 0.0) {
              root++;
              sita_GB = b_a1;

              /* (1,root) */
              /*                     wuca(1,root)=fun_GB(x(1,root),R); */
              /*                     yx(1,root)=fun_GB(x(1,root),R); */
            } else if (yb == 0.0) {
              root++;
              sita_GB = b1;

              /* (1,root) */
              /*                     wuca(1,root)=fun_GB(x(1,root),R); */
              /*                     yx(1,root)=fun_GB(x(1,root),R); */
            } else {
              if (yc == 0.0) {
                root++;
                sita_GB = c1;

                /* (1,root) */
                /*                     wuca(1,root)=fun_GB(x(1,root),R); */
                /*                     yx(1,root)=fun_GB(x(1,root),R);  */
              }
            }

            exitg4 = 1;
          }
        } else {
          exitg4 = 1;
        }
      } while (exitg4 == 0);

      if (fabs(b_a1 - b1) < 1.0E-6) {
        root++;
        sita_GB = (b_a1 + b1) / 2.0;

        /* (1,root) */
        /*       wuca(1,root)=abs(b1-a1)/2; */
        /*       yx(1,root)=fun_GB(x(1,root),R); */
      }
    }

    step /= 2.0;
    if (step < 0.1) {
      exitg3 = true;
    }
  }

  if (root == 0.0) {
    /*      disp('注意：[a,b]区间内没有根,请重新调整区间端点a和b. 999999999表示无根') */
    sita_GB = 9.99999999E+8;

    /*      wuca=999999999; */
    /*      yx=999999999; */
  }

  i0 = b_ff_GB->size[0] * b_ff_GB->size[1];
  b_ff_GB->size[0] = ff1->size[0];
  b_ff_GB->size[1] = ff2->size[0];
  emxEnsureCapacity((emxArray__common *)b_ff_GB, i0, (int)sizeof(double));
  loop_ub = ff1->size[0] * ff2->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_ff_GB->data[i0] = 0.0;
  }

  /* 概率密度函数初始设定 */
  if (sita_GB != 9.99999999E+8) {
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
            if ((FF1->data[(int)kk - 1] == 0.0) || (FF2->data[(int)ll - 1] ==
                 0.0)) {
              b_ff_GB->data[((int)kk + b_ff_GB->size[0] * ((int)ll - 1)) - 1] =
                0.0;
            } else {
              /* copula函数的分子项 */
              b_ff_GB->data[((int)kk + b_ff_GB->size[0] * ((int)ll - 1)) - 1] =
                ff1->data[ii] * ff2->data[jj] * (((1.0 - sita_GB * log(FF1->
                data[(int)kk - 1])) * (1.0 - sita_GB * log(FF2->data[(int)ll - 1]))
                - sita_GB) * exp(-sita_GB * log(FF1->data[(int)kk - 1]) * log
                                 (FF2->data[(int)ll - 1])));
            }

            jj++;
          }
        }

        ii++;
      }
    }
  }
}

/*
 * File trailer for ff_GB.c
 *
 * [EOF]
 */
