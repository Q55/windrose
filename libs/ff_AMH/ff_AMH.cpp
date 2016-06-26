/*
 * File: ff_AMH.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 11-Jun-2016 17:23:23
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "ff_AMH.h"
#include "libs/commons/emxutil.h"

/* Function Declarations */
static double erfenfa_sita_AMH(double R);
static double rt_powd_snf(double u0, double u1);

/* Function Definitions */

/*
 * 目前尚不能求出所有的根
 * a、b为区间左右端点值，tol是精度，k为计算次数，x为使用k次二分法得到的小区间[ak，bk]的中点值，y(x)为x的函数值，wuca=|ak-bk|/2。
 * Arguments    : double R
 * Return Type  : double
 */
static double erfenfa_sita_AMH(double R)
{
  double x;
  double root;
  double step;
  boolean_T exitg1;
  int i1;
  int a1;
  double b_a1;
  double b1;
  double c1;
  double a;
  double ya;
  double yb;
  double yc;
  int exitg2;
  root = 0.0;

  /*  k=1; */
  step = 1.9999999000000002;
  x = 9.99999999E+8;
  exitg1 = false;
  while ((!exitg1) && (root == 0.0)) {
    i1 = (int)((0.89999990000000007 + (step - -1.0)) / step);
    for (a1 = 0; a1 < i1; a1++) {
      b_a1 = -1.0 + (double)a1 * step;
      b1 = b_a1 + step;
      c1 = (b_a1 + b1) / 2.0;
      a = 1.0 - 1.0 / b_a1;
      ya = ((1.0 - 2.0 / (3.0 * b_a1)) - 0.66666666666666663 * (a * a) * log(1.0
             - b_a1)) - R;
      a = 1.0 - 1.0 / b1;
      yb = ((1.0 - 2.0 / (3.0 * b1)) - 0.66666666666666663 * (a * a) * log(1.0 -
             b1)) - R;
      a = 1.0 - 1.0 / c1;
      yc = ((1.0 - 2.0 / (3.0 * c1)) - 0.66666666666666663 * (a * a) * log(1.0 -
             c1)) - R;

      /* 程序中调用的fun_AMH.m 为函数 */
      do {
        exitg2 = 0;
        if (fabs(b1 - b_a1) > 1.0E-6) {
          /*      k=k+1; */
          if (ya * yc < 0.0) {
            b1 = c1;
            c1 = (b_a1 + c1) / 2.0;
            a = 1.0 - 1.0 / b_a1;
            ya = ((1.0 - 2.0 / (3.0 * b_a1)) - 0.66666666666666663 * (a * a) *
                  log(1.0 - b_a1)) - R;
            a = 1.0 - 1.0 / b1;
            yb = ((1.0 - 2.0 / (3.0 * b1)) - 0.66666666666666663 * (a * a) * log
                  (1.0 - b1)) - R;
            a = 1.0 - 1.0 / c1;
            yc = ((1.0 - 2.0 / (3.0 * c1)) - 0.66666666666666663 * (a * a) * log
                  (1.0 - c1)) - R;
          } else if (yc * yb < 0.0) {
            b_a1 = c1;
            c1 = (c1 + b1) / 2.0;
            a = 1.0 - 1.0 / b_a1;
            ya = ((1.0 - 2.0 / (3.0 * b_a1)) - 0.66666666666666663 * (a * a) *
                  log(1.0 - b_a1)) - R;
            a = 1.0 - 1.0 / b1;
            yb = ((1.0 - 2.0 / (3.0 * b1)) - 0.66666666666666663 * (a * a) * log
                  (1.0 - b1)) - R;
            a = 1.0 - 1.0 / c1;
            yc = ((1.0 - 2.0 / (3.0 * c1)) - 0.66666666666666663 * (a * a) * log
                  (1.0 - c1)) - R;
          } else {
            if (ya == 0.0) {
              root++;
              x = b_a1;

              /* (1,root) */
              /*                     wuca(1,root)=fun_AMH(x(1,root),R); */
              /*                     yx(1,root)=fun_AMH(x(1,root),R); */
            } else if (yb == 0.0) {
              root++;
              x = b1;

              /* (1,root) */
              /*                     wuca(1,root)=fun_AMH(x(1,root),R); */
              /*                     yx(1,root)=fun_AMH(x(1,root),R); */
            } else {
              if (yc == 0.0) {
                root++;
                x = c1;

                /* (1,root) */
                /*                     wuca(1,root)=fun_AMH(x(1,root),R); */
                /*                     yx(1,root)=fun_AMH(x(1,root),R);  */
              }
            }

            exitg2 = 1;
          }
        } else {
          exitg2 = 1;
        }
      } while (exitg2 == 0);

      if (fabs(b_a1 - b1) < 1.0E-6) {
        root++;
        x = (b_a1 + b1) / 2.0;

        /* (1,root) */
        /*       wuca(1,root)=abs(b1-a1)/2; */
        /*       yx(1,root)=fun_AMH(x(1,root),R); */
      }
    }

    step /= 2.0;
    if (step < 0.1) {
      exitg1 = true;
    }
  }

  if (root == 0.0) {
    /*      disp('注意：[a,b]区间内没有根,请重新调整区间端点a和b. 999999999表示无根') */
    x = 9.99999999E+8;

    /*      wuca=999999999; */
    /*      yx=999999999; */
  }

  return x;
}

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
 * 利用AMH Couple函数模拟二维最大熵函数
 *  R：肯德尔系数
 * ff1,ff2表示概率密度函数
 * FF1,FF2表示分布函数
 * AMH Copula
 * Arguments    : const emxArray_real_T *ff1
 *                const emxArray_real_T *FF1
 *                const emxArray_real_T *ff2
 *                const emxArray_real_T *FF2
 *                double R
 *                emxArray_real_T *b_ff_AMH
 * Return Type  : void
 */
void ff_AMH(const emxArray_real_T *ff1, const emxArray_real_T *FF1, const
            emxArray_real_T *ff2, const emxArray_real_T *FF2, double R,
            emxArray_real_T *b_ff_AMH)
{
  double sita_AMH;
  int i0;
  int loop_ub;
  unsigned int kk;
  int ii;
  boolean_T exitg1;
  unsigned int ll;
  int jj;
  boolean_T exitg2;
  double a;
  sita_AMH = erfenfa_sita_AMH(R);
  i0 = b_ff_AMH->size[0] * b_ff_AMH->size[1];
  b_ff_AMH->size[0] = ff1->size[0];
  b_ff_AMH->size[1] = ff2->size[0];
  emxEnsureCapacity((emxArray__common *)b_ff_AMH, i0, (int)sizeof(double));
  loop_ub = ff1->size[0] * ff2->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_ff_AMH->data[i0] = 0.0;
  }

  /* 概率密度函数初始设定 */
  if (sita_AMH != 9.99999999E+8) {
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
              b_ff_AMH->data[((int)kk + b_ff_AMH->size[0] * ((int)ll - 1)) - 1] =
                0.0;
            } else {
              a = 1.0 - sita_AMH * (1.0 - FF1->data[(int)kk - 1]) * (1.0 -
                FF2->data[(int)ll - 1]);

              /* copula函数的分子项 */
              /* copula函数的分母项 */
              b_ff_AMH->data[((int)kk + b_ff_AMH->size[0] * ((int)ll - 1)) - 1] =
                ff1->data[ii] * ff2->data[jj] * (((1.0 - sita_AMH) + 2.0 *
                FF2->data[(int)ll - 1] * sita_AMH) * (a * a) - 2.0 * FF2->data
                [(int)ll - 1] * sita_AMH * (1.0 - FF1->data[(int)kk - 1]) *
                ((1.0 - sita_AMH) + FF2->data[(int)ll - 1] * sita_AMH) * (1.0 -
                sita_AMH * (1.0 - FF1->data[(int)kk - 1]) * (1.0 - FF2->data
                [(int)ll - 1]))) / rt_powd_snf(1.0 - sita_AMH * (1.0 - FF1->
                data[(int)kk - 1]) * (1.0 - FF2->data[(int)ll - 1]), 4.0);
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
 * File trailer for ff_AMH.c
 *
 * [EOF]
 */
