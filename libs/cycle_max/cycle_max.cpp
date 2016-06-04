/*
 * File: cycle_max.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 20-May-2016 11:10:10
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "cycle_max.h"
#include "sum.h"
#include "cycle_max_emxutil.h"
#include "polyfit.h"

/* Function Definitions */

/*
 * obs_time工况观测周期以小时为单位
 * Arguments    : const emxArray_real_T *data
 *                double est_max
 *                double resol
 *                double obs_time
 *                double Regression_cycle
 * Return Type  : double
 */
double cycle_max(const emxArray_real_T *data, double est_max, double resol,
                 double obs_time, double Regression_cycle)
{
  double cyclemax;
  emxArray_real_T *Ws_No;
  double ndbl;
  int i0;
  int nm1d2;
  emxArray_int32_T *ii;
  int n;
  double anew;
  double apnd;
  double cdiff;
  double absa;
  double absb;
  emxArray_real_T *r0;
  int idx;
  emxArray_boolean_T *x;
  unsigned int m;
  boolean_T exitg1;
  boolean_T guard1 = false;
  emxArray_real_T *W_No;
  emxArray_real_T *H;
  emxArray_real_T *b_W_No;
  emxArray_real_T *PH;
  double N;
  emxArray_real_T *PH_ln;
  emxArray_real_T *H_ln;
  int nn;
  emxArray_real_T *c_W_No;
  double aa;
  double bb;
  double b_H_ln[11];
  double b_PH_ln[11];
  double n_line[2];
  emxInit_real_T(&Ws_No, 2);
  ndbl = est_max / resol;
  i0 = Ws_No->size[0] * Ws_No->size[1];
  Ws_No->size[0] = (int)ndbl;
  Ws_No->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)Ws_No, i0, (int)sizeof(double));
  nm1d2 = (int)ndbl << 1;
  for (i0 = 0; i0 < nm1d2; i0++) {
    Ws_No->data[i0] = 0.0;
  }

  emxInit_int32_T(&ii, 1);
  nm1d2 = (int)ndbl;
  i0 = ii->size[0];
  ii->size[0] = (int)ndbl;
  emxEnsureCapacity((emxArray__common *)ii, i0, (int)sizeof(int));
  for (i0 = 0; i0 < nm1d2; i0++) {
    ii->data[i0] = i0;
  }

  if (rtIsNaN(resol) || rtIsNaN(resol) || rtIsNaN(est_max)) {
    n = 1;
    anew = rtNaN;
    apnd = est_max;
  } else if ((resol == 0.0) || ((resol < est_max) && (resol < 0.0)) || ((est_max
    < resol) && (resol > 0.0))) {
    n = 0;
    anew = resol;
    apnd = est_max;
  } else if (rtIsInf(resol) || rtIsInf(est_max)) {
    n = 1;
    anew = rtNaN;
    apnd = est_max;
  } else if (rtIsInf(resol)) {
    n = 1;
    anew = resol;
    apnd = est_max;
  } else {
    anew = resol;
    ndbl = floor((est_max - resol) / resol + 0.5);
    apnd = resol + ndbl * resol;
    if (resol > 0.0) {
      cdiff = apnd - est_max;
    } else {
      cdiff = est_max - apnd;
    }

    absa = fabs(resol);
    absb = fabs(est_max);
    if ((absa >= absb) || rtIsNaN(absb)) {
      absb = absa;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
      ndbl++;
      apnd = est_max;
    } else if (cdiff > 0.0) {
      apnd = resol + (ndbl - 1.0) * resol;
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      n = (int)ndbl;
    } else {
      n = 0;
    }
  }

  emxInit_real_T(&r0, 2);
  i0 = r0->size[0] * r0->size[1];
  r0->size[0] = 1;
  r0->size[1] = n;
  emxEnsureCapacity((emxArray__common *)r0, i0, (int)sizeof(double));
  if (n > 0) {
    r0->data[0] = anew;
    if (n > 1) {
      r0->data[n - 1] = apnd;
      i0 = n - 1;
      nm1d2 = i0 / 2;
      for (idx = 1; idx < nm1d2; idx++) {
        ndbl = (double)idx * resol;
        r0->data[idx] = anew + ndbl;
        r0->data[(n - idx) - 1] = apnd - ndbl;
      }

      if (nm1d2 << 1 == n - 1) {
        r0->data[nm1d2] = (anew + apnd) / 2.0;
      } else {
        ndbl = (double)nm1d2 * resol;
        r0->data[nm1d2] = anew + ndbl;
        r0->data[nm1d2 + 1] = apnd - ndbl;
      }
    }
  }

  nm1d2 = ii->size[0];
  for (i0 = 0; i0 < nm1d2; i0++) {
    Ws_No->data[ii->data[i0]] = r0->data[i0];
  }

  emxFree_real_T(&r0);
  for (n = 0; n < data->size[0]; n++) {
    ndbl = floor(data->data[n] / resol);
    Ws_No->data[((int)(ndbl + 1.0) + Ws_No->size[0]) - 1]++;
  }

  emxInit_boolean_T(&x, 1);
  m = 1U;
  nm1d2 = Ws_No->size[0];
  i0 = x->size[0];
  x->size[0] = nm1d2;
  emxEnsureCapacity((emxArray__common *)x, i0, (int)sizeof(boolean_T));
  for (i0 = 0; i0 < nm1d2; i0++) {
    x->data[i0] = (Ws_No->data[i0 + Ws_No->size[0]] == 0.0);
  }

  nm1d2 = x->size[0];
  idx = 0;
  i0 = ii->size[0];
  ii->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)ii, i0, (int)sizeof(int));
  n = 1;
  exitg1 = false;
  while ((!exitg1) && (n <= nm1d2)) {
    guard1 = false;
    if (x->data[n - 1]) {
      idx++;
      ii->data[idx - 1] = n;
      if (idx >= nm1d2) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      n++;
    }
  }

  if (x->size[0] == 1) {
    if (idx == 0) {
      i0 = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)ii, i0, (int)sizeof(int));
    }
  } else {
    i0 = ii->size[0];
    if (1 > idx) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = idx;
    }

    emxEnsureCapacity((emxArray__common *)ii, i0, (int)sizeof(int));
  }

  emxFree_boolean_T(&x);
  emxInit_real_T(&W_No, 2);
  nm1d2 = ii->size[0];
  ndbl = est_max / resol;
  i0 = W_No->size[0] * W_No->size[1];
  W_No->size[0] = (int)(ndbl - (double)nm1d2);
  W_No->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)W_No, i0, (int)sizeof(double));
  nm1d2 = (int)(ndbl - (double)nm1d2) << 1;
  emxFree_int32_T(&ii);
  for (i0 = 0; i0 < nm1d2; i0++) {
    W_No->data[i0] = 0.0;
  }

  ndbl = est_max / resol;
  for (n = 0; n < (int)ndbl; n++) {
    if (Ws_No->data[n + Ws_No->size[0]] == 0.0) {
    } else {
      W_No->data[(int)m - 1] = Ws_No->data[n];
      W_No->data[((int)m + W_No->size[0]) - 1] = Ws_No->data[n + Ws_No->size[0]];
      m++;
    }
  }

  emxFree_real_T(&Ws_No);
  emxInit_real_T1(&H, 1);
  nm1d2 = W_No->size[0];
  i0 = H->size[0];
  H->size[0] = nm1d2;
  emxEnsureCapacity((emxArray__common *)H, i0, (int)sizeof(double));
  for (i0 = 0; i0 < nm1d2; i0++) {
    H->data[i0] = W_No->data[i0];
  }

  emxInit_real_T1(&b_W_No, 1);
  nm1d2 = W_No->size[0];
  i0 = b_W_No->size[0];
  b_W_No->size[0] = nm1d2;
  emxEnsureCapacity((emxArray__common *)b_W_No, i0, (int)sizeof(double));
  for (i0 = 0; i0 < nm1d2; i0++) {
    b_W_No->data[i0] = W_No->data[i0 + W_No->size[0]];
  }

  emxInit_real_T1(&PH, 1);
  N = sum(b_W_No);
  nm1d2 = W_No->size[0];

  /* PH为对应有义波高Hs的出现概率 */
  i0 = PH->size[0];
  PH->size[0] = nm1d2 - 1;
  emxEnsureCapacity((emxArray__common *)PH, i0, (int)sizeof(double));
  emxFree_real_T(&b_W_No);
  for (i0 = 0; i0 <= nm1d2 - 2; i0++) {
    PH->data[i0] = 0.0;
  }

  emxInit_real_T1(&PH_ln, 1);
  i0 = PH_ln->size[0];
  PH_ln->size[0] = nm1d2 - 1;
  emxEnsureCapacity((emxArray__common *)PH_ln, i0, (int)sizeof(double));
  for (i0 = 0; i0 <= nm1d2 - 2; i0++) {
    PH_ln->data[i0] = 0.0;
  }

  emxInit_real_T1(&H_ln, 1);

  /* PH_ln为对应有义波高出现概率的对数形式 */
  nn = 0;
  i0 = H_ln->size[0];
  H_ln->size[0] = nm1d2 - 1;
  emxEnsureCapacity((emxArray__common *)H_ln, i0, (int)sizeof(double));
  for (i0 = 0; i0 <= nm1d2 - 2; i0++) {
    H_ln->data[i0] = 0.0;
  }

  n = 0;
  emxInit_real_T1(&c_W_No, 1);
  while (n <= nm1d2 - 2) {
    i0 = c_W_No->size[0];
    c_W_No->size[0] = n + 1;
    emxEnsureCapacity((emxArray__common *)c_W_No, i0, (int)sizeof(double));
    for (i0 = 0; i0 <= n; i0++) {
      c_W_No->data[i0] = W_No->data[i0 + W_No->size[0]];
    }

    ndbl = sum(c_W_No);
    PH->data[n] = ndbl / N;
    aa = log(H->data[n]);

    /* 有义波高Hs的对数形式 */
    bb = log(-log(1.0 - PH->data[n]));
    if ((fabs(aa) == rtInf) || rtIsNaN(aa) || (fabs(bb) == rtInf) || rtIsNaN(bb))
    {
    } else {
      H_ln->data[nn] = aa;
      PH_ln->data[nn] = bb;
      nn++;
    }

    n++;
  }

  emxFree_real_T(&c_W_No);
  emxFree_real_T(&PH);
  emxFree_real_T(&H);
  emxFree_real_T(&W_No);

  /*  alpha=(PH_ln(end-1,1)-PH_ln(end-6,1))/(H_ln(end-1,1)-H_ln(end-6,1)); */
  /*  belta=PH_ln(end-1,1)-alpha*H_ln(end-1,1); */
  /* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
  nm1d2 = H_ln->size[0] - 11;
  for (i0 = 0; i0 < 11; i0++) {
    b_H_ln[i0] = H_ln->data[i0 + nm1d2];
  }

  emxFree_real_T(&H_ln);
  nm1d2 = PH_ln->size[0] - 11;
  for (i0 = 0; i0 < 11; i0++) {
    b_PH_ln[i0] = PH_ln->data[i0 + nm1d2];
  }

  emxFree_real_T(&PH_ln);
  polyfit(b_H_ln, b_PH_ln, n_line);

  /* 直线拟合添加到程序中替换alpha，belta */
  /* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
  cyclemax = exp((log(-log(1.0 - (1.0 - 1.0 / (Regression_cycle * (24.0 /
    obs_time) * 365.0)))) - n_line[1]) / n_line[0]);

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* 图形验证部分 */
  return cyclemax;
}

/*
 * File trailer for cycle_max.c
 *
 * [EOF]
 */
