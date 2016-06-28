/*
 * File: max_shang_one.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 11-Jun-2016 17:29:56
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "max_shang_one.h"
#include "libs/commons/mod.h"
#include "libs/commons/fix.h"
#include "libs/commons/abs.h"
#include "libs/commons/gamma.h"
#include "libs/commons/emxutil.h"

/* Function Declarations */
static void aapowerbb(double aa, double bb, double result[1000]);
static void b_aapowerbb(double bb, double result[1000]);
static double erfenfa(double a, double b, double tol, double a0, const
                      emxArray_real_T *sample, double jj);
static double fun(double x, double a0, const emxArray_real_T *sample, double jj);
static double fun_A(double x, double a0, const emxArray_real_T *sample, double
                    jj);
static double fun_beta(double x, double a0, double A, const emxArray_real_T
  *sample, double jj);
static double fun_gamma(double x, double a0, double beta, const emxArray_real_T *
  sample);
static double fun_k(double x, double a0, double beta, double A, const
                    emxArray_real_T *sample);
static void larnum_divi(double aa[1000], double bb[1000], double cc[1000]);
static void larnum_format(double aa, double AA[1000]);
static void larnum_minus(double aa[1000], double bb[1000]);
static void larnum_multi(const double aa[1000], const double bb[1000], double
  result[1000]);
static void larnum_plus(const double aa[1000], const double bb[1000], double cc
  [1000]);
static double larnum_vs(double aa[1000], double bb[1000]);
static double rt_powd_snf(double u0, double u1);

/* Function Definitions */

/*
 * 用于计算大数的乘方运算
 * aa,bb军正常输入
 * Arguments    : double aa
 *                double bb
 *                double result[1000]
 * Return Type  : void
 */
static void aapowerbb(double aa, double bb, double result[1000])
{
  double BB;
  double ii;
  double b_result[1000];
  double dv3[1000];
  double c_result[1000];
  double dv4[1000];
  memset(&result[0], 0, 1000U * sizeof(double));
  if (aa != 0.0) {
    result[0] = 1.0;

    /* 先计算整数次 */
    if (bb < 0.0) {
      BB = ceil(bb);
    } else {
      BB = floor(bb);
    }

    ii = 0.0;
    while (BB > 0.0) {
      BB--;
      ii++;
      memcpy(&b_result[0], &result[0], 1000U * sizeof(double));
      larnum_format(aa, dv3);
      larnum_multi(b_result, dv3, result);
    }

    if (bb - ii != 0.0) {
      memcpy(&c_result[0], &result[0], 1000U * sizeof(double));
      larnum_format(rt_powd_snf(aa, bb - ii), dv4);
      larnum_multi(c_result, dv4, result);
    }
  }
}

/*
 * 用于计算大数的乘方运算
 * aa,bb军正常输入
 * Arguments    : double bb
 *                double result[1000]
 * Return Type  : void
 */
static void b_aapowerbb(double bb, double result[1000])
{
  double BB;
  double ii;
  double b_result[1000];
  double dv9[1000];
  double c_result[1000];
  double dv10[1000];
  memset(&result[0], 0, 1000U * sizeof(double));
  result[0] = 1.0;

  /* 先计算整数次 */
  if (bb < 0.0) {
    BB = ceil(bb);
  } else {
    BB = floor(bb);
  }

  ii = 0.0;
  while (BB > 0.0) {
    BB--;
    ii++;
    memcpy(&b_result[0], &result[0], 1000U * sizeof(double));
    larnum_format(2.7183, dv9);
    larnum_multi(b_result, dv9, result);
  }

  if (bb - ii != 0.0) {
    memcpy(&c_result[0], &result[0], 1000U * sizeof(double));
    larnum_format(rt_powd_snf(2.7183, bb - ii), dv10);
    larnum_multi(c_result, dv10, result);
  }
}

/*
 * 目前尚不能求出所有的根
 * a、b为区间左右端点值，tol是精度，k为计算次数，x为使用k次二分法得到的小区间[ak，bk]的中点值，y(x)为x的函数值，wuca=|ak-bk|/2。
 *     x=erfenfa(est_kesi_min,est_kesi_max,kesi_resol,a0,data,jj);
 * Arguments    : double a
 *                double b
 *                double tol
 *                double a0
 *                const emxArray_real_T *sample
 *                double jj
 * Return Type  : double
 */
static double erfenfa(double a, double b, double tol, double a0, const
                      emxArray_real_T *sample, double jj)
{
  double x;
  double root;
  double step;
  boolean_T exitg1;
  int i2;
  int a1;
  boolean_T exitg2;
  double b_a1;
  double b1;
  double c1;
  double ya;
  double yb;
  double yc;
  int exitg3;
  root = 0.0;

  /*  k=1; */
  step = b - a;
  x = 9.9999999E+7;
  exitg1 = false;
  while ((!exitg1) && (root == 0.0)) {
    i2 = (int)(((b - 0.1) + (step - a)) / step);
    a1 = 0;
    exitg2 = false;
    while ((!exitg2) && (a1 <= i2 - 1)) {
      b_a1 = a + (double)a1 * step;
      b1 = b_a1 + step;
      c1 = (b_a1 + b1) / 2.0;
      ya = fun(b_a1, a0, sample, jj);
      yb = fun(b1, a0, sample, jj);
      yc = fun(c1, a0, sample, jj);

      /* 程序中调用的fun.m 为函数 */
      do {
        exitg3 = 0;
        if (fabs(b1 - b_a1) > tol) {
          /*      k=k+1; */
          if (ya * yc < 0.0) {
            b1 = c1;
            c1 = (b_a1 + c1) / 2.0;
            ya = fun(b_a1, a0, sample, jj);
            yb = fun(b1, a0, sample, jj);
            yc = fun(c1, a0, sample, jj);
          } else if (yc * yb < 0.0) {
            b_a1 = c1;
            c1 = (c1 + b1) / 2.0;
            ya = fun(b_a1, a0, sample, jj);
            yb = fun(b1, a0, sample, jj);
            yc = fun(c1, a0, sample, jj);
          } else {
            if (ya == 0.0) {
              root++;
              x = b_a1;

              /* (1,root) */
              /*                     wuca=fun(x,a0,sample,jj);%(1,root) */
              /*                     yx=fun(x,a0,sample,jj);%(1,root) */
            } else if (yb == 0.0) {
              root++;
              x = b1;

              /* (1,root) */
              /*                     wuca=fun(x,a0,sample,jj);%(1,root) */
              /*                     yx=fun(x,a0,sample,jj);%(1,root) */
            } else if (yc == 0.0) {
              root++;
              x = c1;

              /* (1,root) */
              /*                     wuca=fun(x,a0,sample,jj);%(1,root) */
              /*                     yx=fun(x,a0,sample,jj); %(1,root) */
            } else {
              x = rtNaN;
            }

            exitg3 = 1;
          }
        } else {
          exitg3 = 1;
        }
      } while (exitg3 == 0);

      if (fabs(b_a1 - b1) < tol) {
        root++;
        x = (b_a1 + b1) / 2.0;

        /* (1,root) */
        /*                 wuca=abs(b1-a1)/2;%(1,root) */
        /*                 yx=fun(x,a0,sample,jj);%(1,root) */
        exitg2 = true;
      } else {
        a1++;
      }
    }

    step /= 2.0;
    if (step < 0.1) {
      exitg1 = true;
    }
  }

  if (root == 0.0) {
    x = 9.99999999E+8;

    /*      wuca=999999999; */
    /*      yx=999999999; */
  }

  return x;
}

/*
 * 该函数用来求解就是求解kesi的方程
 * Arguments    : double x
 *                double a0
 *                const emxArray_real_T *sample
 *                double jj
 * Return Type  : double
 */
static double fun(double x, double a0, const emxArray_real_T *sample, double jj)
{
  double b_y1;
  double A;
  double beta;
  double temp_ln;
  int ii;
  double k;
  double s;
  double xdmy;
  double xdmln;
  int xinc;
  double tt;
  double tst;
  double ta;
  double tk;
  int b_k;
  boolean_T exitg1;
  static const double dv1[22] = { 1.0, -0.5, 0.16666666666666666,
    -0.033333333333333333, 0.023809523809523808, -0.033333333333333333,
    0.07575757575757576, -0.2531135531135531, 1.1666666666666667,
    -7.0921568627450977, 54.971177944862156, -529.12424242424242,
    6192.123188405797, -86580.253113553117, 1.4255171666666667E+6,
    -2.7298231067816094E+7, 6.015808739006424E+8, -1.5116315767092157E+10,
    4.2961464306116669E+11, -1.3711655205088332E+13, 4.8833231897359319E+14,
    -1.9296579341940068E+16 };

  double trm;
  A = fun_A(x, a0, sample, jj);
  beta = fun_beta(x, a0, A, sample, jj);
  temp_ln = 0.0;
  for (ii = 0; ii < sample->size[0]; ii++) {
    temp_ln += log(sample->data[ii] - a0);

    /* mark:temp_ln=temp_ln+log(cur{ii,5}*100-a0); */
  }

  k = beta * A;
  if (rtIsNaN(k)) {
    s = rtNaN;
  } else if (k == 0.0) {
    s = rtInf;
  } else if (rtIsInf(k)) {
    s = rtMinusInf;
  } else if (k < 2.2204460492503131E-16) {
    s = 1.0 / k;
  } else {
    xdmy = k;
    xdmln = log(k);
    xinc = 0;
    if (k < 9.0) {
      xinc = 9 - (int)floor(k);
      xdmy = k + (9.0 - floor(k));
      xdmln = log(xdmy);
    }

    tt = 0.5 / xdmy;
    tst = 2.2204460492503131E-16 * tt;
    xdmy = 1.0 / (xdmy * xdmy);
    ta = 0.5 * xdmy;
    s = ta / 6.0;
    if (s >= tst) {
      tk = 2.0;
      b_k = 0;
      exitg1 = false;
      while ((!exitg1) && (b_k < 19)) {
        ta = ta * ((tk + 1.0) / (tk + 1.0)) * (tk / (tk + 2.0)) * xdmy;
        trm = ta * dv1[b_k + 3];
        if (fabs(trm) < tst) {
          exitg1 = true;
        } else {
          s += trm;
          tk += 2.0;
          b_k++;
        }
      }
    }

    s = (s + tt) * exp(-(0.0 * xdmln));
    if (xinc > 0) {
      for (b_k = 0; b_k < xinc; b_k++) {
        s += 1.0 / (k + (double)((xinc - b_k) - 1));
      }

      s -= xdmln;
    } else {
      s -= xdmln;
    }
  }

  b_y1 = (log(beta) - (-s)) + x * temp_ln / (jj - 1.0);

  /* y1=log(beta)-fdigamma(beta*A)+ln;20160306gai */
  return b_y1;
}

/*
 * Arguments    : double x
 *                double a0
 *                const emxArray_real_T *sample
 *                double jj
 * Return Type  : double
 */
static double fun_A(double x, double a0, const emxArray_real_T *sample, double
                    jj)
{
  double temp_A;
  int ii;
  temp_A = 0.0;
  for (ii = 0; ii < sample->size[0]; ii++) {
    temp_A += rt_powd_snf(sample->data[ii] - a0, x);

    /* mark:temp_A=temp_A+(cur{ii,5}-a0)^x; */
  }

  return temp_A / (jj - 1.0);
}

/*
 * Arguments    : double x
 *                double a0
 *                double A
 *                const emxArray_real_T *sample
 *                double jj
 * Return Type  : double
 */
static double fun_beta(double x, double a0, double A, const emxArray_real_T
  *sample, double jj)
{
  double temp_beta;
  int ii;
  temp_beta = 0.0;

  /*  row=0; */
  for (ii = 0; ii < sample->size[0]; ii++) {
    temp_beta += (rt_powd_snf(sample->data[ii] - a0, x) - A) * log(sample->
      data[ii] - a0);

    /* mark:temp_beta=temp_beta+(((cur{ii,5}-a0)^x-A)*log(cur{ii,5}-a0)); */
  }

  return (jj - 1.0) / (x * temp_beta);
}

/*
 * Arguments    : double x
 *                double a0
 *                double beta
 *                const emxArray_real_T *sample
 * Return Type  : double
 */
static double fun_gamma(double x, double a0, double beta, const emxArray_real_T *
  sample)
{
  double temp_A;
  double temp_B;
  int ii;
  temp_A = 0.0;
  temp_B = 0.0;
  for (ii = 0; ii < sample->size[0]; ii++) {
    temp_A += rt_powd_snf(sample->data[ii] - a0, x - 1.0);

    /* mark:temp_A=temp_A+(cur{ii,5}-a0)^(x-1); */
    temp_B += 1.0 / (sample->data[ii] - a0);

    /* mark:temp_B=temp_B+1/(cur{ii,5}-a0); */
  }

  return x * beta * temp_A / temp_B;
}

/*
 * Arguments    : double x
 *                double a0
 *                double beta
 *                double A
 *                const emxArray_real_T *sample
 * Return Type  : double
 */
static double fun_k(double x, double a0, double beta, double A, const
                    emxArray_real_T *sample)
{
  double temp_A;
  double temp_B;
  int ii;
  temp_A = 0.0;
  temp_B = 0.0;
  for (ii = 0; ii < sample->size[0]; ii++) {
    temp_A += rt_powd_snf(sample->data[ii] - a0, x - 1.0);

    /* mark:temp_A=temp_A+(cur{ii,5}-a0)^(x-1); */
    temp_B += 1.0 / (sample->data[ii] - a0);

    /* mark:temp_B=temp_B+1/(cur{ii,5}-a0); */
  }

  return fabs((x * beta * temp_A / temp_B + 1.0) - x * beta * A);
}

/*
 * 用于存储于数组中的大数相除
 * Arguments    : double aa[1000]
 *                double bb[1000]
 *                double cc[1000]
 * Return Type  : void
 */
static void larnum_divi(double aa[1000], double bb[1000], double cc[1000])
{
  int idx;
  short ii_data[1000];
  int ii;
  boolean_T exitg5;
  boolean_T guard3 = false;
  int loop_ub;
  int i3;
  short aa_notzero_data[1000];
  boolean_T exitg4;
  boolean_T guard2 = false;
  int ii_size_idx_0;
  short bb_notzero_data[1000];
  int len_aa;
  int len_bb;
  double dd[1000];
  int mm;
  int row;
  int row_c;
  boolean_T exitg1;
  boolean_T exitg3;
  boolean_T guard1 = false;
  double ff;
  double b_dd[1000];
  double b_bb[1000];
  boolean_T exitg2;
  double b_ii;
  double dv5[1000];
  double ee[1000];
  double c_dd[1000];
  double b_ee[1000];
  double d_dd[1000];
  double dv6[1000];
  double dv7[1000];
  double dv8[1000];
  idx = 0;
  ii = 1;
  exitg5 = false;
  while ((!exitg5) && (ii < 1001)) {
    guard3 = false;
    if (aa[ii - 1] != 0.0) {
      idx++;
      ii_data[idx - 1] = (short)ii;
      if (idx >= 1000) {
        exitg5 = true;
      } else {
        guard3 = true;
      }
    } else {
      guard3 = true;
    }

    if (guard3) {
      ii++;
    }
  }

  if (1 > idx) {
    loop_ub = 0;
  } else {
    loop_ub = idx;
  }

  for (i3 = 0; i3 < loop_ub; i3++) {
    aa_notzero_data[i3] = ii_data[i3];
  }

  idx = 0;
  ii = 1;
  exitg4 = false;
  while ((!exitg4) && (ii < 1001)) {
    guard2 = false;
    if (bb[ii - 1] != 0.0) {
      idx++;
      ii_data[idx - 1] = (short)ii;
      if (idx >= 1000) {
        exitg4 = true;
      } else {
        guard2 = true;
      }
    } else {
      guard2 = true;
    }

    if (guard2) {
      ii++;
    }
  }

  if (1 > idx) {
    ii_size_idx_0 = 0;
  } else {
    ii_size_idx_0 = idx;
  }

  if (1 > idx) {
    ii = 0;
  } else {
    ii = idx;
  }

  for (i3 = 0; i3 < ii; i3++) {
    bb_notzero_data[i3] = ii_data[i3];
  }

  if (!(loop_ub == 0)) {
    if (aa_notzero_data[loop_ub - 1] + 1 > 1000) {
      i3 = 0;
      idx = 0;
    } else {
      i3 = aa_notzero_data[loop_ub - 1];
      idx = 1000;
    }

    ii = idx - i3;
    for (idx = 0; idx < ii; idx++) {
      aa[i3 + idx] = 0.0;
    }

    /* 扩充aa序列 */
    len_aa = aa_notzero_data[loop_ub - 1];
  } else {
    memset(&aa[0], 0, 1000U * sizeof(double));
    len_aa = 0;
  }

  if (!(ii_size_idx_0 == 0)) {
    if (bb_notzero_data[ii_size_idx_0 - 1] + 1 > 1000) {
      i3 = 0;
      idx = 0;
    } else {
      i3 = bb_notzero_data[ii_size_idx_0 - 1];
      idx = 1000;
    }

    loop_ub = idx - i3;
    for (idx = 0; idx < loop_ub; idx++) {
      bb[i3 + idx] = 0.0;
    }

    /* 扩充aa序列 */
    len_bb = bb_notzero_data[ii_size_idx_0 - 1];
  } else {
    memset(&bb[0], 0, 1000U * sizeof(double));
    len_bb = 0;
  }

  /* 预定结果存储空间 */
  for (ii = 0; ii < 1000; ii++) {
    cc[ii] = 0.0;
    dd[ii] = 0.0;
  }

  mm = 0;
  row = (len_aa - len_bb) + 1;
  if (row < 1) {
    memcpy(&dd[0], &aa[0], 1000U * sizeof(double));
    row_c = 1;
  } else {
    i3 = (len_aa - len_bb) + 1;
    if (i3 > len_aa) {
      i3 = 1;
      idx = 0;
    } else {
      idx = len_aa;
    }

    loop_ub = idx - i3;
    for (idx = 0; idx <= loop_ub; idx++) {
      dd[idx] = aa[(i3 + idx) - 1];
    }

    row_c = row;
  }

  exitg1 = false;
  while ((!exitg1) && (mm > -10)) {
    idx = 0;
    ii = 1;
    exitg3 = false;
    while ((!exitg3) && (ii < 1001)) {
      guard1 = false;
      if (dd[ii - 1] >= 1.0E-10) {
        idx++;
        ii_data[idx - 1] = (short)ii;
        if (idx >= 1000) {
          exitg3 = true;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        ii++;
      }
    }

    if (1 > idx) {
      ii_size_idx_0 = 0;
    } else {
      ii_size_idx_0 = idx;
    }

    if (1 > idx) {
      loop_ub = 0;
    } else {
      loop_ub = idx;
    }

    for (i3 = 0; i3 < loop_ub; i3++) {
      aa_notzero_data[i3] = ii_data[i3];
    }

    if (ii_size_idx_0 == 0) {
      exitg1 = true;
    } else {
      if (aa_notzero_data[ii_size_idx_0 - 1] > len_bb) {
        ff = ceil((dd[len_bb] * 10.0 + dd[len_bb - 1]) / bb[len_bb - 1]);
      } else {
        memcpy(&b_dd[0], &dd[0], 1000U * sizeof(double));
        memcpy(&b_bb[0], &bb[0], 1000U * sizeof(double));
        if (larnum_vs(b_dd, b_bb) >= 0.0) {
          ff = 1.0;
        } else {
          ff = 0.0;
        }
      }

      ii = 0;
      exitg2 = false;
      while ((!exitg2) && (ii <= (int)-(-1.0 - ff) - 1)) {
        b_ii = ff + -(double)ii;
        larnum_format(b_ii, dv5);
        larnum_multi(dv5, bb, ee);
        memcpy(&c_dd[0], &dd[0], 1000U * sizeof(double));
        memcpy(&b_ee[0], &ee[0], 1000U * sizeof(double));
        if (larnum_vs(c_dd, b_ee) >= 0.0) {
          if (mm >= 0) {
            cc[row_c - 1] += b_ii;
          } else {
            cc[row_c - 1] += b_ii * rt_powd_snf(10.0, mm);
          }

          larnum_minus(dd, ee);
          exitg2 = true;
        } else {
          ii++;
        }
      }

      if (row_c == 1) {
        memcpy(&d_dd[0], &dd[0], 1000U * sizeof(double));
        larnum_format(10.0, dv6);
        larnum_multi(d_dd, dv6, dd);
        mm--;
      } else {
        row_c--;
        larnum_format(10.0, dv7);
        larnum_multi(dd, dv7, ee);
        larnum_format(aa[row_c - 1], dv8);
        larnum_plus(ee, dv8, dd);
      }
    }
  }
}

/*
 * 将数据转换为大数存储格式
 * Arguments    : double aa
 *                double AA[1000]
 * Return Type  : void
 */
static void larnum_format(double aa, double AA[1000])
{
  int ii;
  double y;
  double b_y;
  memset(&AA[0], 0, 1000U * sizeof(double));
  AA[0] = aa;
  for (ii = 0; ii < 999; ii++) {
    y = AA[ii] / 10.0;
    if (y < 0.0) {
      b_y = ceil(y);
    } else {
      b_y = floor(y);
    }

    AA[1 + ii] += b_y;
    AA[ii] -= floor(AA[ii] / 10.0) * 10.0;
  }
}

/*
 * 用于存储于数组中的大数相减
 * Arguments    : double aa[1000]
 *                double bb[1000]
 * Return Type  : void
 */
static void larnum_minus(double aa[1000], double bb[1000])
{
  int idx;
  short ii_data[1000];
  int ii;
  boolean_T exitg2;
  boolean_T guard2 = false;
  int loop_ub;
  short aa_notzero_data[1000];
  boolean_T exitg1;
  boolean_T guard1 = false;
  int b_loop_ub;
  int ii_size_idx_0;
  short bb_notzero_data[1000];
  int c_loop_ub;
  int kk;
  idx = 0;
  ii = 1;
  exitg2 = false;
  while ((!exitg2) && (ii < 1001)) {
    guard2 = false;
    if (aa[ii - 1] != 0.0) {
      idx++;
      ii_data[idx - 1] = (short)ii;
      if (idx >= 1000) {
        exitg2 = true;
      } else {
        guard2 = true;
      }
    } else {
      guard2 = true;
    }

    if (guard2) {
      ii++;
    }
  }

  if (1 > idx) {
    loop_ub = 0;
  } else {
    loop_ub = idx;
  }

  for (idx = 0; idx < loop_ub; idx++) {
    aa_notzero_data[idx] = ii_data[idx];
  }

  idx = 0;
  ii = 1;
  exitg1 = false;
  while ((!exitg1) && (ii < 1001)) {
    guard1 = false;
    if (bb[ii - 1] != 0.0) {
      idx++;
      ii_data[idx - 1] = (short)ii;
      if (idx >= 1000) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      ii++;
    }
  }

  if (1 > idx) {
    b_loop_ub = 0;
  } else {
    b_loop_ub = idx;
  }

  if (1 > idx) {
    ii_size_idx_0 = 0;
  } else {
    ii_size_idx_0 = idx;
  }

  for (idx = 0; idx < b_loop_ub; idx++) {
    bb_notzero_data[idx] = ii_data[idx];
  }

  if (!(loop_ub == 0)) {
    if (aa_notzero_data[loop_ub - 1] + 1 > 1000) {
      idx = 0;
      ii = 0;
    } else {
      idx = aa_notzero_data[loop_ub - 1];
      ii = 1000;
    }

    c_loop_ub = ii - idx;
    for (ii = 0; ii < c_loop_ub; ii++) {
      aa[idx + ii] = 0.0;
    }

    /* 扩充aa序列 */
  } else {
    for (idx = 0; idx < 1000; idx++) {
      aa[idx] = 0.0;
    }
  }

  if (!(ii_size_idx_0 == 0)) {
    if (bb_notzero_data[ii_size_idx_0 - 1] + 1 > 1000) {
      idx = 0;
      ii = 0;
    } else {
      idx = bb_notzero_data[ii_size_idx_0 - 1];
      ii = 1000;
    }

    c_loop_ub = ii - idx;
    for (ii = 0; ii < c_loop_ub; ii++) {
      bb[idx + ii] = 0.0;
    }

    /* 扩充aa序列 */
  } else {
    memset(&bb[0], 0, 1000U * sizeof(double));
  }

  /*  cc=zeros(10000,1);%预定结果存储空间 */
  if (loop_ub == 0) {
    for (idx = 0; idx < 1000; idx++) {
      aa[idx] = -bb[idx];
    }
  } else if (ii_size_idx_0 == 0) {
  } else {
    for (ii = 0; ii < bb_notzero_data[b_loop_ub - 1]; ii++) {
      /* 减掉一个 */
      aa[ii] -= bb[ii];
    }

    for (kk = 0; kk < aa_notzero_data[loop_ub - 1]; kk++) {
      if (aa[kk] < 0.0) {
        aa[kk + 1]--;
        aa[kk] += 10.0;
      }
    }
  }
}

/*
 * 用于存储于数组中的大数相乘
 * Arguments    : const double aa[1000]
 *                const double bb[1000]
 *                double result[1000]
 * Return Type  : void
 */
static void larnum_multi(const double aa[1000], const double bb[1000], double
  result[1000])
{
  static double cc[2000000];
  double dv2[1000];
  boolean_T x[1000];
  int idx;
  short ii_data[1000];
  int ii;
  boolean_T exitg2;
  boolean_T guard2 = false;
  int loop_ub;
  short aa_notzero_data[1000];
  boolean_T exitg1;
  boolean_T guard1 = false;
  int b_loop_ub;
  int ii_size_idx_0;
  short bb_notzero_data[1000];
  double rr;
  int b_ii;
  int jj;
  double d0;
  double mm;
  int b_mm;
  int kk;
  double b_jj;
  memset(&cc[0], 0, 2000000U * sizeof(double));
  b_abs(aa, dv2);
  for (idx = 0; idx < 1000; idx++) {
    x[idx] = (dv2[idx] >= 1.0E-10);
  }

  idx = 0;
  ii = 1;
  exitg2 = false;
  while ((!exitg2) && (ii < 1001)) {
    guard2 = false;
    if (x[ii - 1]) {
      idx++;
      ii_data[idx - 1] = (short)ii;
      if (idx >= 1000) {
        exitg2 = true;
      } else {
        guard2 = true;
      }
    } else {
      guard2 = true;
    }

    if (guard2) {
      ii++;
    }
  }

  if (1 > idx) {
    loop_ub = 0;
  } else {
    loop_ub = idx;
  }

  for (idx = 0; idx < loop_ub; idx++) {
    aa_notzero_data[idx] = ii_data[idx];
  }

  b_abs(bb, dv2);
  for (idx = 0; idx < 1000; idx++) {
    x[idx] = (dv2[idx] >= 1.0E-10);
  }

  idx = 0;
  ii = 1;
  exitg1 = false;
  while ((!exitg1) && (ii < 1001)) {
    guard1 = false;
    if (x[ii - 1]) {
      idx++;
      ii_data[idx - 1] = (short)ii;
      if (idx >= 1000) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      ii++;
    }
  }

  if (1 > idx) {
    b_loop_ub = 0;
  } else {
    b_loop_ub = idx;
  }

  if (1 > idx) {
    ii_size_idx_0 = 0;
  } else {
    ii_size_idx_0 = idx;
  }

  for (idx = 0; idx < b_loop_ub; idx++) {
    bb_notzero_data[idx] = ii_data[idx];
  }

  if ((!(loop_ub == 0)) && (!(ii_size_idx_0 == 0))) {
    /* 类似于乘法运算中对应项相乘 */
    rr = 0.0;
    ii = 1;
    for (b_ii = 0; b_ii < aa_notzero_data[loop_ub - 1]; b_ii++) {
      ii = 1 + b_ii;

      /* len_aa */
      /*      if ii>len_aa */
      /*              break */
      /*      end */
      for (jj = 0; jj < bb_notzero_data[b_loop_ub - 1]; jj++) {
        /* len_bb */
        /*          if jj>len_bb */
        /*              break */
        /*          end */
        cc[((int)((1.0 + (double)jj) + rr) + 1000 * b_ii) - 1] = aa[b_ii] *
          bb[jj];
      }

      rr++;
    }

    /* 将各个列的数相加 */
    d0 = (double)bb_notzero_data[ii_size_idx_0 - 1] + rr;
    mm = 1.0;
    for (b_mm = 0; b_mm < (int)d0; b_mm++) {
      mm = 1.0 + (double)b_mm;

      /* jj+rr-1 */
      /*      if mm>len_bb+rr-1 */
      /*              break */
      /*      end */
      for (kk = 0; kk <= ii - 2; kk++) {
        cc[b_mm] += cc[b_mm + 1000 * (kk + 1)];
      }

      /*  result(mm,1)=sum(cc(mm,:)); */
    }

    for (jj = 0; jj < (int)mm; jj++) {
      d0 = cc[jj] / 10.0;
      b_fix(&d0);
      cc[(int)((1.0 + (double)jj) + 1.0) - 1] += d0;
      cc[jj] = b_mod(cc[jj], 10.0);
    }

    for (jj = 0; jj < (int)-(2.0 + (-1.0 - mm)); jj++) {
      b_jj = mm + -(double)jj;
      cc[(int)(b_jj - 1.0) - 1] += b_mod(cc[(int)b_jj - 1], 1.0) * 10.0;
      b_fix(&cc[(int)b_jj - 1]);
    }

    for (jj = 0; jj < (int)mm; jj++) {
      d0 = cc[jj] / 10.0;
      b_fix(&d0);
      cc[(int)((1.0 + (double)jj) + 1.0) - 1] += d0;
      cc[jj] = b_mod(cc[jj], 10.0);
    }

    /*  cc(:,2:20000)=[]; */
  }

  memcpy(&result[0], &cc[0], 1000U * sizeof(double));
}

/*
 * 用于存储于数组中的大数相加
 * Arguments    : const double aa[1000]
 *                const double bb[1000]
 *                double cc[1000]
 * Return Type  : void
 */
static void larnum_plus(const double aa[1000], const double bb[1000], double cc
  [1000])
{
  int idx;
  short ii_data[1000];
  int ii;
  boolean_T exitg2;
  boolean_T guard2 = false;
  int loop_ub;
  int i5;
  short aa_notzero_data[1000];
  boolean_T exitg1;
  boolean_T guard1 = false;
  int ii_size_idx_0;
  short bb_notzero_data[1000];
  int jj;
  double d1;
  memset(&cc[0], 0, 1000U * sizeof(double));
  idx = 0;
  ii = 1;
  exitg2 = false;
  while ((!exitg2) && (ii < 1001)) {
    guard2 = false;
    if (aa[ii - 1] != 0.0) {
      idx++;
      ii_data[idx - 1] = (short)ii;
      if (idx >= 1000) {
        exitg2 = true;
      } else {
        guard2 = true;
      }
    } else {
      guard2 = true;
    }

    if (guard2) {
      ii++;
    }
  }

  if (1 > idx) {
    loop_ub = 0;
  } else {
    loop_ub = idx;
  }

  for (i5 = 0; i5 < loop_ub; i5++) {
    aa_notzero_data[i5] = ii_data[i5];
  }

  idx = 0;
  ii = 1;
  exitg1 = false;
  while ((!exitg1) && (ii < 1001)) {
    guard1 = false;
    if (bb[ii - 1] != 0.0) {
      idx++;
      ii_data[idx - 1] = (short)ii;
      if (idx >= 1000) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      ii++;
    }
  }

  if (1 > idx) {
    ii_size_idx_0 = 0;
  } else {
    ii_size_idx_0 = idx;
  }

  if (1 > idx) {
    idx = 0;
  }

  for (i5 = 0; i5 < idx; i5++) {
    bb_notzero_data[i5] = ii_data[i5];
  }

  if (loop_ub == 0) {
    memcpy(&cc[0], &bb[0], 1000U * sizeof(double));
  } else if (ii_size_idx_0 == 0) {
    memcpy(&cc[0], &aa[0], 1000U * sizeof(double));
  } else {
    if (aa_notzero_data[loop_ub - 1] >= bb_notzero_data[ii_size_idx_0 - 1]) {
      i5 = aa_notzero_data[loop_ub - 1];
    } else {
      i5 = bb_notzero_data[ii_size_idx_0 - 1];
    }

    for (ii = 0; ii < i5; ii++) {
      cc[ii] = aa[ii] + bb[ii];
    }

    if (aa_notzero_data[loop_ub - 1] >= bb_notzero_data[ii_size_idx_0 - 1]) {
      i5 = aa_notzero_data[loop_ub - 1];
    } else {
      i5 = bb_notzero_data[ii_size_idx_0 - 1];
    }

    for (jj = 0; jj < i5; jj++) {
      d1 = cc[jj] / 10.0;
      b_fix(&d1);
      cc[jj + 1] += d1;
      cc[jj] = b_mod(cc[jj], 10.0);
    }
  }
}

/*
 * 用于存储于数组中的大数比较大小，aa>bb输出1，aa=bb输出0，aa<bb输出-1；
 * aa,bb均为正数
 * Arguments    : double aa[1000]
 *                double bb[1000]
 * Return Type  : double
 */
static double larnum_vs(double aa[1000], double bb[1000])
{
  double cc;
  int idx;
  short ii_data[1000];
  int ii;
  boolean_T exitg3;
  boolean_T guard3 = false;
  int loop_ub;
  short aa_notzero_data[1000];
  boolean_T exitg2;
  boolean_T guard2 = false;
  int ii_size_idx_0;
  short bb_notzero_data[1000];
  int i4;
  int len_aa;
  int len_bb;
  double test[1000];
  boolean_T exitg1;
  boolean_T guard1 = false;
  idx = 0;
  ii = 1;
  exitg3 = false;
  while ((!exitg3) && (ii < 1001)) {
    guard3 = false;
    if (aa[ii - 1] != 0.0) {
      idx++;
      ii_data[idx - 1] = (short)ii;
      if (idx >= 1000) {
        exitg3 = true;
      } else {
        guard3 = true;
      }
    } else {
      guard3 = true;
    }

    if (guard3) {
      ii++;
    }
  }

  if (1 > idx) {
    loop_ub = 0;
  } else {
    loop_ub = idx;
  }

  for (idx = 0; idx < loop_ub; idx++) {
    aa_notzero_data[idx] = ii_data[idx];
  }

  idx = 0;
  ii = 1;
  exitg2 = false;
  while ((!exitg2) && (ii < 1001)) {
    guard2 = false;
    if (bb[ii - 1] != 0.0) {
      idx++;
      ii_data[idx - 1] = (short)ii;
      if (idx >= 1000) {
        exitg2 = true;
      } else {
        guard2 = true;
      }
    } else {
      guard2 = true;
    }

    if (guard2) {
      ii++;
    }
  }

  if (1 > idx) {
    ii_size_idx_0 = 0;
  } else {
    ii_size_idx_0 = idx;
  }

  if (1 > idx) {
    ii = 0;
  } else {
    ii = idx;
  }

  for (idx = 0; idx < ii; idx++) {
    bb_notzero_data[idx] = ii_data[idx];
  }

  if (!(loop_ub == 0)) {
    if (aa_notzero_data[loop_ub - 1] + 1 > 1000) {
      idx = 0;
      i4 = 0;
    } else {
      idx = aa_notzero_data[loop_ub - 1];
      i4 = 1000;
    }

    ii = i4 - idx;
    for (i4 = 0; i4 < ii; i4++) {
      aa[idx + i4] = 0.0;
    }

    /* 扩充aa序列 */
    len_aa = aa_notzero_data[loop_ub - 1];
  } else {
    memset(&aa[0], 0, 1000U * sizeof(double));
    len_aa = 0;
  }

  if (!(ii_size_idx_0 == 0)) {
    if (bb_notzero_data[ii_size_idx_0 - 1] + 1 > 1000) {
      idx = 0;
      i4 = 0;
    } else {
      idx = bb_notzero_data[ii_size_idx_0 - 1];
      i4 = 1000;
    }

    loop_ub = i4 - idx;
    for (i4 = 0; i4 < loop_ub; i4++) {
      bb[idx + i4] = 0.0;
    }

    /* 扩充aa序列 */
    len_bb = bb_notzero_data[ii_size_idx_0 - 1];
  } else {
    memset(&bb[0], 0, 1000U * sizeof(double));
    len_bb = 0;
  }

  if (len_aa > len_bb) {
    cc = 1.0;
  } else if (len_aa < len_bb) {
    cc = -1.0;
  } else {
    for (ii = 0; ii < 1000; ii++) {
      test[ii] = aa[ii] - bb[ii];
    }

    idx = 0;
    ii = 1;
    exitg1 = false;
    while ((!exitg1) && (ii < 1001)) {
      guard1 = false;
      if (test[ii - 1] != 0.0) {
        idx++;
        ii_data[idx - 1] = (short)ii;
        if (idx >= 1000) {
          exitg1 = true;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        ii++;
      }
    }

    if (1 > idx) {
      ii_size_idx_0 = 0;
    } else {
      ii_size_idx_0 = idx;
    }

    if (1 > idx) {
      loop_ub = 0;
    } else {
      loop_ub = idx;
    }

    for (idx = 0; idx < loop_ub; idx++) {
      aa_notzero_data[idx] = ii_data[idx];
    }

    if (ii_size_idx_0 == 0) {
      cc = 0.0;
    } else if (test[aa_notzero_data[ii_size_idx_0 - 1] - 1] > 0.0) {
      cc = 1.0;
    } else {
      cc = -1.0;
    }
  }

  return cc;
}

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d2;
  double d3;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d2 = fabs(u0);
    d3 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d2 == 1.0) {
        y = rtNaN;
      } else if (d2 > 1.0) {
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
    } else if (d3 == 0.0) {
      y = 1.0;
    } else if (d3 == 1.0) {
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
 * 至此主要执行求样本中的最小值min_samp
 * 首先假设a0已知，0=<a0=<x(1)，根据假定的a0求出对应的keci
 * Arguments    : const emxArray_real_T *data1
 *                double limit_min
 *                double a0_resol
 *                double est_kesi_min
 *                double est_kesi_max
 *                double kesi_resol
 *                double wh_sample
 *                double wh_max
 *                emxArray_real_T *yy
 * Return Type  : void
 */
void max_shang_one(const emxArray_real_T *data1, double limit_min, double
                   a0_resol, double est_kesi_min, double est_kesi_max, double
                   kesi_resol, double wh_sample, double wh_max, emxArray_real_T *
                   yy)
{
  emxArray_real_T *sample1;
  int i0;
  int n;
  unsigned int mm;
  int ii;
  emxArray_real_T *data;
  int ixstart;
  double kd;
  int idx;
  boolean_T exitg4;
  emxArray_real_T *a0_row;
  double rr;
  emxArray_real_T *x_row;
  unsigned int nn;
  unsigned int jj;
  double anew;
  double apnd;
  double ndbl;
  double cdiff;
  double absa;
  double absb;
  emxArray_real_T *a0_dou;
  int a0_ii;
  emxArray_real_T *x_kesi;
  unsigned int ll;
  emxArray_real_T *a0_corret;
  emxArray_real_T *KK;
  int kk;
  int itmp;
  boolean_T exitg3;
  emxArray_int32_T *r0;
  int ll_yy;
  emxArray_real_T *xx_cor;
  emxArray_boolean_T *x;
  emxArray_int32_T *b_ii;
  int i1;
  boolean_T exitg2;
  boolean_T guard2 = false;
  int xx_ii;
  double aa;
  double index_row;
  double result_aa[1000];
  int tt;
  double b_result_aa[1000];
  double dv0[1000];
  double result_bb[1000];
  double result_cc[1000];
  short ii_data[1000];
  boolean_T exitg1;
  boolean_T guard1 = false;
  short ff_notzero_data[1000];
  double gg;
  int c_ii;
  emxInit_real_T(&sample1, 1);
  i0 = sample1->size[0];
  sample1->size[0] = data1->size[0];
  emxEnsureCapacity((emxArray__common *)sample1, i0, (int)sizeof(double));
  n = data1->size[0];
  for (i0 = 0; i0 < n; i0++) {
    sample1->data[i0] = 0.0;
  }

  mm = 0U;
  for (ii = 0; ii < (int)((double)data1->size[0] + 0.5); ii++) {
    /* %% */
    if (data1->data[ii] < limit_min) {
    } else {
      mm++;
      sample1->data[(int)mm - 1] = data1->data[ii];
    }
  }

  if (1 > (int)mm) {
    n = 0;
  } else {
    n = (int)mm;
  }

  emxInit_real_T(&data, 1);
  i0 = data->size[0];
  data->size[0] = n;
  emxEnsureCapacity((emxArray__common *)data, i0, (int)sizeof(double));
  for (i0 = 0; i0 < n; i0++) {
    data->data[i0] = sample1->data[i0];
  }

  ixstart = 1;
  kd = sample1->data[0];
  if (n > 1) {
    if (rtIsNaN(kd)) {
      idx = 2;
      exitg4 = false;
      while ((!exitg4) && (idx <= n)) {
        ixstart = idx;
        if (!rtIsNaN(sample1->data[idx - 1])) {
          kd = sample1->data[idx - 1];
          exitg4 = true;
        } else {
          idx++;
        }
      }
    }

    if (ixstart < n) {
      while (ixstart + 1 <= n) {
        if (sample1->data[ixstart] < kd) {
          kd = sample1->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  emxInit_real_T(&a0_row, 1);
  rr = ceil(kd / a0_resol);

  /* 假设a0的精度为0.01，rr表示a0的所有取值mark:rr=floor(min_samp/0.01); */
  i0 = a0_row->size[0];
  a0_row->size[0] = (int)rr;
  emxEnsureCapacity((emxArray__common *)a0_row, i0, (int)sizeof(double));
  ixstart = (int)rr;
  for (i0 = 0; i0 < ixstart; i0++) {
    a0_row->data[i0] = 0.0;
  }

  emxInit_real_T(&x_row, 1);

  /* 用于记录a0 */
  /*  k_row=zeros(rr,1); */
  i0 = x_row->size[0];
  x_row->size[0] = (int)rr;
  emxEnsureCapacity((emxArray__common *)x_row, i0, (int)sizeof(double));
  ixstart = (int)rr;
  for (i0 = 0; i0 < ixstart; i0++) {
    x_row->data[i0] = 0.0;
  }

  /* 用于记录求得的keci */
  /*  wuca_row=zeros(rr,1);%用于记录数值计算求得的根，与真实根的差距 */
  /*  yx_row=zeros(rr,1);%数值根对应的计算结果 */
  nn = 0U;
  jj = n + 1U;
  kd -= a0_resol / 2.0;
  if (rtIsNaN(a0_resol) || rtIsNaN(a0_resol) || rtIsNaN(kd)) {
    n = 1;
    anew = rtNaN;
    apnd = kd;
  } else if ((a0_resol == 0.0) || ((a0_resol < kd) && (a0_resol < 0.0)) || ((kd <
    a0_resol) && (a0_resol > 0.0))) {
    n = 0;
    anew = a0_resol;
    apnd = kd;
  } else if (rtIsInf(a0_resol) || rtIsInf(kd)) {
    n = 1;
    anew = rtNaN;
    apnd = kd;
  } else if (rtIsInf(a0_resol)) {
    n = 1;
    anew = a0_resol;
    apnd = kd;
  } else {
    anew = a0_resol;
    ndbl = floor((kd - a0_resol) / a0_resol + 0.5);
    apnd = a0_resol + ndbl * a0_resol;
    if (a0_resol > 0.0) {
      cdiff = apnd - kd;
    } else {
      cdiff = kd - apnd;
    }

    absa = fabs(a0_resol);
    absb = fabs(kd);
    if ((absa >= absb) || rtIsNaN(absb)) {
      absb = absa;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
      ndbl++;
      apnd = kd;
    } else if (cdiff > 0.0) {
      apnd = a0_resol + (ndbl - 1.0) * a0_resol;
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      n = (int)ndbl;
    } else {
      n = 0;
    }
  }

  emxInit_real_T1(&a0_dou, 2);
  i0 = a0_dou->size[0] * a0_dou->size[1];
  a0_dou->size[0] = 1;
  a0_dou->size[1] = n;
  emxEnsureCapacity((emxArray__common *)a0_dou, i0, (int)sizeof(double));
  if (n > 0) {
    a0_dou->data[0] = anew;
    if (n > 1) {
      a0_dou->data[n - 1] = apnd;
      i0 = n - 1;
      ixstart = i0 / 2;
      for (idx = 1; idx < ixstart; idx++) {
        kd = (double)idx * a0_resol;
        a0_dou->data[idx] = anew + kd;
        a0_dou->data[(n - idx) - 1] = apnd - kd;
      }

      if (ixstart << 1 == n - 1) {
        a0_dou->data[ixstart] = (anew + apnd) / 2.0;
      } else {
        kd = (double)ixstart * a0_resol;
        a0_dou->data[ixstart] = anew + kd;
        a0_dou->data[ixstart + 1] = apnd - kd;
      }
    }
  }

  /* %%% */
  for (a0_ii = 0; a0_ii < a0_dou->size[1]; a0_ii++) {
    /* %%%mark:for a0=0.01:0.01:min_samp */
    kd = erfenfa(est_kesi_min, est_kesi_max, kesi_resol, a0_dou->data[a0_ii],
                 data, jj);

    /* 利用数值方法求keci,初步定义keci的取值范围为0.001~20 */
    nn++;
    a0_row->data[(int)nn - 1] = a0_dou->data[a0_ii];

    /* 用于记录a0 */
    x_row->data[(int)nn - 1] = kd;

    /* 用于记录求得的keci */
    /*      wuca_row(nn,1)=wuca;%用于记录数值计算求得的根，与真实根的差距 */
    /*      yx_row(nn,1)=yx;%数值根对应的计算结果 */
  }

  emxInit_real_T(&x_kesi, 1);
  ll = 0U;
  i0 = x_kesi->size[0];
  x_kesi->size[0] = x_row->size[0];
  emxEnsureCapacity((emxArray__common *)x_kesi, i0, (int)sizeof(double));
  n = x_row->size[0];
  for (i0 = 0; i0 < n; i0++) {
    x_kesi->data[i0] = 0.0;
  }

  emxInit_real_T(&a0_corret, 1);
  i0 = a0_corret->size[0];
  a0_corret->size[0] = x_row->size[0];
  emxEnsureCapacity((emxArray__common *)a0_corret, i0, (int)sizeof(double));
  n = x_row->size[0];
  for (i0 = 0; i0 < n; i0++) {
    a0_corret->data[i0] = 0.0;
  }

  for (ii = 0; ii < x_row->size[0]; ii++) {
    /* %%(nn+0.5) */
    if (x_row->data[ii] == 9.99999999E+8) {
      /* 跳过无根情况 */
    } else {
      ll++;
      x_kesi->data[(int)ll - 1] = x_row->data[ii];

      /* 保留可用的根 */
      a0_corret->data[(int)ll - 1] = a0_row->data[ii];

      /* 保留对应可用根的a0     */
    }
  }

  i0 = sample1->size[0];
  sample1->size[0] = x_kesi->size[0];
  emxEnsureCapacity((emxArray__common *)sample1, i0, (int)sizeof(double));
  n = x_kesi->size[0];
  for (i0 = 0; i0 < n; i0++) {
    sample1->data[i0] = 0.0;
  }

  i0 = a0_row->size[0];
  a0_row->size[0] = x_kesi->size[0];
  emxEnsureCapacity((emxArray__common *)a0_row, i0, (int)sizeof(double));
  n = x_kesi->size[0];
  for (i0 = 0; i0 < n; i0++) {
    a0_row->data[i0] = 0.0;
  }

  i0 = x_row->size[0];
  x_row->size[0] = x_kesi->size[0];
  emxEnsureCapacity((emxArray__common *)x_row, i0, (int)sizeof(double));
  n = x_kesi->size[0];
  for (i0 = 0; i0 < n; i0++) {
    x_row->data[i0] = 0.0;
  }

  emxInit_real_T(&KK, 1);
  i0 = KK->size[0];
  KK->size[0] = x_kesi->size[0];
  emxEnsureCapacity((emxArray__common *)KK, i0, (int)sizeof(double));
  n = x_kesi->size[0];
  for (i0 = 0; i0 < n; i0++) {
    KK->data[i0] = 0.0;
  }

  for (kk = 0; kk < x_kesi->size[0]; kk++) {
    /* %% */
    sample1->data[kk] = fun_A(x_kesi->data[kk], a0_corret->data[kk], data, jj);

    /* 计算A */
    a0_row->data[kk] = fun_beta(x_kesi->data[kk], a0_corret->data[kk],
      sample1->data[kk], data, jj);

    /* 计算beta */
    x_row->data[kk] = fun_gamma(x_kesi->data[kk], a0_corret->data[kk],
      a0_row->data[kk], data);

    /* 计算gama */
    KK->data[kk] = fun_k(x_kesi->data[kk], a0_corret->data[kk], a0_row->data[kk],
                         sample1->data[kk], data);

    /* 计算K，利用K值最小的参数，进行一维最大熵函数的计算 */
  }

  emxFree_real_T(&data);
  emxFree_real_T(&sample1);
  ixstart = 1;
  n = KK->size[0];
  kd = KK->data[0];
  itmp = 0;
  if (KK->size[0] > 1) {
    if (rtIsNaN(KK->data[0])) {
      idx = 1;
      exitg3 = false;
      while ((!exitg3) && (idx + 1 <= n)) {
        ixstart = idx + 1;
        if (!rtIsNaN(KK->data[idx])) {
          kd = KK->data[idx];
          itmp = idx;
          exitg3 = true;
        } else {
          idx++;
        }
      }
    }

    if (ixstart < KK->size[0]) {
      while (ixstart + 1 <= n) {
        if (KK->data[ixstart] < kd) {
          kd = KK->data[ixstart];
          itmp = ixstart;
        }

        ixstart++;
      }
    }
  }

  emxFree_real_T(&KK);

  /*  jj=0; */
  /*  wh_sample=0.1; */
  /*  test=0; */
  kd = ceil(wh_max / wh_sample);
  i0 = yy->size[0] * yy->size[1];
  yy->size[0] = (int)kd;
  yy->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)yy, i0, (int)sizeof(double));
  n = (int)kd << 1;
  for (i0 = 0; i0 < n; i0++) {
    yy->data[i0] = 0.0;
  }

  emxInit_int32_T(&r0, 1);
  n = (int)kd;
  i0 = r0->size[0];
  r0->size[0] = (int)kd;
  emxEnsureCapacity((emxArray__common *)r0, i0, (int)sizeof(int));
  for (i0 = 0; i0 < n; i0++) {
    r0->data[i0] = i0;
  }

  kd = wh_max + wh_sample / 2.0;
  if (rtIsNaN(wh_sample) || rtIsNaN(wh_sample) || rtIsNaN(kd)) {
    n = 1;
    anew = rtNaN;
    apnd = kd;
  } else if ((wh_sample == 0.0) || ((wh_sample < kd) && (wh_sample < 0.0)) ||
             ((kd < wh_sample) && (wh_sample > 0.0))) {
    n = 0;
    anew = wh_sample;
    apnd = kd;
  } else if (rtIsInf(wh_sample) || rtIsInf(kd)) {
    n = 1;
    anew = rtNaN;
    apnd = kd;
  } else if (rtIsInf(wh_sample)) {
    n = 1;
    anew = wh_sample;
    apnd = kd;
  } else {
    anew = wh_sample;
    ndbl = floor((kd - wh_sample) / wh_sample + 0.5);
    apnd = wh_sample + ndbl * wh_sample;
    if (wh_sample > 0.0) {
      cdiff = apnd - kd;
    } else {
      cdiff = kd - apnd;
    }

    absa = fabs(wh_sample);
    absb = fabs(kd);
    if ((absa >= absb) || rtIsNaN(absb)) {
      absb = absa;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
      ndbl++;
      apnd = kd;
    } else if (cdiff > 0.0) {
      apnd = wh_sample + (ndbl - 1.0) * wh_sample;
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      n = (int)ndbl;
    } else {
      n = 0;
    }
  }

  i0 = a0_dou->size[0] * a0_dou->size[1];
  a0_dou->size[0] = 1;
  a0_dou->size[1] = n;
  emxEnsureCapacity((emxArray__common *)a0_dou, i0, (int)sizeof(double));
  if (n > 0) {
    a0_dou->data[0] = anew;
    if (n > 1) {
      a0_dou->data[n - 1] = apnd;
      i0 = n - 1;
      ixstart = i0 / 2;
      for (idx = 1; idx < ixstart; idx++) {
        kd = (double)idx * wh_sample;
        a0_dou->data[idx] = anew + kd;
        a0_dou->data[(n - idx) - 1] = apnd - kd;
      }

      if (ixstart << 1 == n - 1) {
        a0_dou->data[ixstart] = (anew + apnd) / 2.0;
      } else {
        kd = (double)ixstart * wh_sample;
        a0_dou->data[ixstart] = anew + kd;
        a0_dou->data[ixstart + 1] = apnd - kd;
      }
    }
  }

  ixstart = r0->size[0];
  for (i0 = 0; i0 < ixstart; i0++) {
    yy->data[r0->data[i0] + yy->size[0]] = a0_dou->data[i0];
  }

  emxFree_int32_T(&r0);
  i0 = yy->size[0];
  ll_yy = 0;
  emxInit_real_T1(&xx_cor, 2);
  emxInit_boolean_T(&x, 2);
  emxInit_int32_T1(&b_ii, 2);
  while (ll_yy <= i0 - 1) {
    /* %% */
    anew = yy->data[ll_yy + yy->size[0]] - wh_sample;
    if (rtIsNaN(anew) || rtIsNaN(yy->data[ll_yy + yy->size[0]] - 0.005)) {
      n = 1;
      anew = rtNaN;
      apnd = yy->data[ll_yy + yy->size[0]] - 0.005;
    } else if (yy->data[ll_yy + yy->size[0]] - 0.005 < anew) {
      n = 0;
      apnd = yy->data[ll_yy + yy->size[0]] - 0.005;
    } else if (rtIsInf(anew) || rtIsInf(yy->data[ll_yy + yy->size[0]] - 0.005))
    {
      n = 1;
      anew = rtNaN;
      apnd = yy->data[ll_yy + yy->size[0]] - 0.005;
    } else {
      ndbl = floor(((yy->data[ll_yy + yy->size[0]] - 0.005) - anew) / 0.01 + 0.5);
      apnd = anew + ndbl * 0.01;
      cdiff = apnd - (yy->data[ll_yy + yy->size[0]] - 0.005);
      absa = fabs(anew);
      absb = fabs(yy->data[ll_yy + yy->size[0]] - 0.005);
      if ((absa >= absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = yy->data[ll_yy + yy->size[0]] - 0.005;
      } else if (cdiff > 0.0) {
        apnd = anew + (ndbl - 1.0) * 0.01;
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        n = (int)ndbl;
      } else {
        n = 0;
      }
    }

    i1 = a0_dou->size[0] * a0_dou->size[1];
    a0_dou->size[0] = 1;
    a0_dou->size[1] = n;
    emxEnsureCapacity((emxArray__common *)a0_dou, i1, (int)sizeof(double));
    if (n > 0) {
      a0_dou->data[0] = anew;
      if (n > 1) {
        a0_dou->data[n - 1] = apnd;
        i1 = n - 1;
        ixstart = i1 / 2;
        for (idx = 1; idx < ixstart; idx++) {
          kd = (double)idx * 0.01;
          a0_dou->data[idx] = anew + kd;
          a0_dou->data[(n - idx) - 1] = apnd - kd;
        }

        if (ixstart << 1 == n - 1) {
          a0_dou->data[ixstart] = (anew + apnd) / 2.0;
        } else {
          kd = (double)ixstart * 0.01;
          a0_dou->data[ixstart] = anew + kd;
          a0_dou->data[ixstart + 1] = apnd - kd;
        }
      }
    }

    i1 = x->size[0] * x->size[1];
    x->size[0] = 1;
    x->size[1] = a0_dou->size[1];
    emxEnsureCapacity((emxArray__common *)x, i1, (int)sizeof(boolean_T));
    n = a0_dou->size[0] * a0_dou->size[1];
    for (i1 = 0; i1 < n; i1++) {
      x->data[i1] = (a0_dou->data[i1] >= limit_min);
    }

    ixstart = x->size[1];
    idx = 0;
    i1 = b_ii->size[0] * b_ii->size[1];
    b_ii->size[0] = 1;
    b_ii->size[1] = x->size[1];
    emxEnsureCapacity((emxArray__common *)b_ii, i1, (int)sizeof(int));
    ii = 1;
    exitg2 = false;
    while ((!exitg2) && (ii <= ixstart)) {
      guard2 = false;
      if (x->data[ii - 1]) {
        idx++;
        b_ii->data[idx - 1] = ii;
        if (idx >= ixstart) {
          exitg2 = true;
        } else {
          guard2 = true;
        }
      } else {
        guard2 = true;
      }

      if (guard2) {
        ii++;
      }
    }

    if (x->size[1] == 1) {
      if (idx == 0) {
        i1 = b_ii->size[0] * b_ii->size[1];
        b_ii->size[0] = 1;
        b_ii->size[1] = 0;
        emxEnsureCapacity((emxArray__common *)b_ii, i1, (int)sizeof(int));
      }
    } else {
      i1 = b_ii->size[0] * b_ii->size[1];
      if (1 > idx) {
        b_ii->size[1] = 0;
      } else {
        b_ii->size[1] = idx;
      }

      emxEnsureCapacity((emxArray__common *)b_ii, i1, (int)sizeof(int));
    }

    i1 = xx_cor->size[0] * xx_cor->size[1];
    xx_cor->size[0] = 1;
    xx_cor->size[1] = b_ii->size[1];
    emxEnsureCapacity((emxArray__common *)xx_cor, i1, (int)sizeof(double));
    n = b_ii->size[0] * b_ii->size[1];
    for (i1 = 0; i1 < n; i1++) {
      xx_cor->data[i1] = b_ii->data[i1];
    }

    if (!(xx_cor->size[1] == 0)) {
      for (xx_ii = 0; xx_ii < xx_cor->size[1]; xx_ii++) {
        /* %% */
        /* 该函数用来求解就是求解kesi的方程 */
        /*  function y1=fun_shang(x,kesi,a0,r,beta) */
        /*  %该函数用来求解就是求解kesi的方程 */
        /*   y1=kesi*(beta^((r+1)/kesi))*(1/gamma((r+1)/kesi))*abs((x-a0)^r)*(exp(-1*beta*abs((x-a0)^kesi))); */
        /*  end */
        aa = (x_row->data[itmp] + 1.0) / x_kesi->data[itmp];
        index_row = b_mod(aa, 1.0);
        if (index_row == 0.0) {
          index_row = 1.0;
        }

        kd = index_row;
        b_gamma(&kd);
        larnum_format(kd, result_aa);
        for (tt = 0; tt < (int)-(1.0E-20 + (-1.0 - (aa - 1.0))); tt++) {
          memcpy(&b_result_aa[0], &result_aa[0], 1000U * sizeof(double));
          larnum_format((aa - 1.0) + -(double)tt, dv0);
          larnum_multi(b_result_aa, dv0, result_aa);
        }

        /*  aa_notzero=find(result_aa~=0); */
        /*  gg=0; */
        /*  for ii=aa_notzero(length(aa_notzero)):-1:1 */
        /*      gg=gg+result_aa(ii,1)*10^(ii-1); */
        /*  end */
        /*  y1=gg; */
        aapowerbb(a0_row->data[itmp], aa, result_bb);
        larnum_divi(result_bb, result_aa, result_cc);
        b_aapowerbb(a0_row->data[itmp] * fabs(rt_powd_snf(a0_dou->data[(int)
          xx_cor->data[xx_ii] - 1] - a0_corret->data[itmp], x_kesi->data[itmp])),
                    result_bb);
        larnum_divi(result_cc, result_bb, result_aa);
        idx = 0;
        ii = 1;
        exitg1 = false;
        while ((!exitg1) && (ii < 1001)) {
          guard1 = false;
          if (result_aa[ii - 1] >= 1.0E-10) {
            idx++;
            ii_data[idx - 1] = (short)ii;
            if (idx >= 1000) {
              exitg1 = true;
            } else {
              guard1 = true;
            }
          } else {
            guard1 = true;
          }

          if (guard1) {
            ii++;
          }
        }

        if (1 > idx) {
          ixstart = 0;
        } else {
          ixstart = idx;
        }

        if (1 > idx) {
          n = 0;
        } else {
          n = idx;
        }

        for (i1 = 0; i1 < n; i1++) {
          ff_notzero_data[i1] = ii_data[i1];
        }

        if (ixstart == 0) {
          gg = 0.0;
        } else {
          gg = 0.0;
          i1 = ff_notzero_data[ixstart - 1];
          for (ii = 0; ii < i1; ii++) {
            c_ii = i1 - ii;
            if (c_ii - 1 == 0) {
              gg += result_aa[c_ii - 1];
            } else {
              gg += result_aa[c_ii - 1] * rt_powd_snf(10.0, (double)c_ii - 1.0);
            }
          }
        }

        yy->data[ll_yy] += x_kesi->data[itmp] * fabs(rt_powd_snf(a0_dou->data
          [(int)xx_cor->data[xx_ii] - 1] - a0_corret->data[itmp], x_row->
          data[itmp])) * gg;

        /* 一维最大熵函数已验证正确 */
      }
    }

    ll_yy++;
  }

  emxFree_int32_T(&b_ii);
  emxFree_boolean_T(&x);
  emxFree_real_T(&xx_cor);
  emxFree_real_T(&a0_corret);
  emxFree_real_T(&x_kesi);
  emxFree_real_T(&a0_dou);
  emxFree_real_T(&x_row);
  emxFree_real_T(&a0_row);

  /*  plot(yy(:,2),yy(:,1)) */
}

/*
 * File trailer for max_shang_one.c
 *
 * [EOF]
 */
