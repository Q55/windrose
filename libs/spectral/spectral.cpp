/*
 * File: spectral.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 13-May-2016 08:43:37
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "spectral.h"
#include "libs/commons/emxutil.h"
#include "libs/commons/fft.h"

/* Function Declarations */
static double rt_hypotd_snf(double u0, double u1);
static double rt_powd_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_hypotd_snf(double u0, double u1)
{
  double y;
  double a;
  double b;
  a = fabs(u0);
  b = fabs(u1);
  if (a < b) {
    a /= b;
    y = b * sqrt(a * a + 1.0);
  } else if (a > b) {
    b /= a;
    y = a * sqrt(b * b + 1.0);
  } else if (rtIsNaN(b)) {
    y = b;
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
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
 * Fs -  Sampling frequency
 * Arguments    : double Fs
 *                emxArray_real_T *data
 *                emxArray_real_T *f
 *                emxArray_real_T *YY
 * Return Type  : void
 */
void spectral(double Fs, emxArray_real_T *data, emxArray_real_T *f,
              emxArray_real_T *YY)
{
  emxArray_boolean_T *b;
  int nxin;
  int k0;
  int nrowx;
  int nxout;
  int k;
  emxArray_real_T *b_data;
  int eint;
  double fdbl;
  double delta1;
  emxArray_creal_T *Y;
  double NFFT;
  emxArray_creal_T *x;
  emxInit_boolean_T(&b, 1);
  nxin = b->size[0];
  b->size[0] = data->size[0];
  emxEnsureCapacity((emxArray__common *)b, nxin, (int)sizeof(boolean_T));
  k0 = data->size[0];
  for (nxin = 0; nxin < k0; nxin++) {
    b->data[nxin] = rtIsNaN(data->data[nxin]);
  }

  nxin = data->size[0];
  nrowx = data->size[0];
  nxout = 0;
  for (k = 1; k <= b->size[0]; k++) {
    nxout += b->data[k - 1];
  }

  nxout = data->size[0] - nxout;
  k0 = -1;
  for (k = 1; k <= nxin; k++) {
    if ((k > b->size[0]) || (!b->data[k - 1])) {
      k0++;
      data->data[k0] = data->data[k - 1];
    }
  }

  emxFree_boolean_T(&b);
  if (nrowx != 1) {
    if (1 > nxout) {
      k0 = 0;
    } else {
      k0 = nxout;
    }

    emxInit_real_T(&b_data, 1);
    nxin = b_data->size[0];
    b_data->size[0] = k0;
    emxEnsureCapacity((emxArray__common *)b_data, nxin, (int)sizeof(double));
    for (nxin = 0; nxin < k0; nxin++) {
      b_data->data[nxin] = data->data[nxin];
    }

    nxin = data->size[0];
    data->size[0] = b_data->size[0];
    emxEnsureCapacity((emxArray__common *)data, nxin, (int)sizeof(double));
    k0 = b_data->size[0];
    for (nxin = 0; nxin < k0; nxin++) {
      data->data[nxin] = b_data->data[nxin];
    }

    emxFree_real_T(&b_data);
  } else {
    nxin = data->size[0];
    if (1 > nxout) {
      data->size[0] = 0;
    } else {
      data->size[0] = nxout;
    }

    emxEnsureCapacity((emxArray__common *)data, nxin, (int)sizeof(double));
  }

  fdbl = frexp(data->size[0], &eint);
  delta1 = eint;
  if (fdbl == 0.5) {
    delta1 = (double)eint - 1.0;
  }

  emxInit_creal_T(&Y, 1);
  NFFT = rt_powd_snf(2.0, delta1);

  /*  Next power of 2 from length of y */
  fft(data, NFFT, Y);
  nxout = data->size[0];
  nxin = Y->size[0];
  emxEnsureCapacity((emxArray__common *)Y, nxin, (int)sizeof(creal_T));
  k0 = Y->size[0];
  for (nxin = 0; nxin < k0; nxin++) {
    fdbl = Y->data[nxin].re;
    delta1 = Y->data[nxin].im;
    if (delta1 == 0.0) {
      Y->data[nxin].re = fdbl / (double)nxout;
      Y->data[nxin].im = 0.0;
    } else if (fdbl == 0.0) {
      Y->data[nxin].re = 0.0;
      Y->data[nxin].im = delta1 / (double)nxout;
    } else {
      Y->data[nxin].re = fdbl / (double)nxout;
      Y->data[nxin].im = delta1 / (double)nxout;
    }
  }

  fdbl = Fs / 2.0;
  nxin = f->size[0] * f->size[1];
  f->size[0] = 1;
  f->size[1] = (int)floor(NFFT / 2.0 + 1.0);
  emxEnsureCapacity((emxArray__common *)f, nxin, (int)sizeof(double));
  f->data[f->size[1] - 1] = 1.0;
  if (f->size[1] >= 2) {
    f->data[0] = 0.0;
    if (f->size[1] >= 3) {
      delta1 = 1.0 / ((double)f->size[1] - 1.0);
      nxin = f->size[1];
      for (k = 0; k <= nxin - 3; k++) {
        f->data[1 + k] = (1.0 + (double)k) * delta1;
      }
    }
  }

  nxin = f->size[0] * f->size[1];
  f->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)f, nxin, (int)sizeof(double));
  nxout = f->size[0];
  k0 = f->size[1];
  k0 *= nxout;
  for (nxin = 0; nxin < k0; nxin++) {
    f->data[nxin] *= fdbl;
  }

  emxInit_creal_T(&x, 1);
  fdbl = NFFT / 2.0 + 1.0;
  k0 = (int)(NFFT / 2.0 + 1.0);
  nxin = x->size[0];
  x->size[0] = k0;
  emxEnsureCapacity((emxArray__common *)x, nxin, (int)sizeof(creal_T));
  for (nxin = 0; nxin < k0; nxin++) {
    x->data[nxin] = Y->data[nxin];
  }

  emxFree_creal_T(&Y);
  nxin = YY->size[0];
  YY->size[0] = (int)fdbl;
  emxEnsureCapacity((emxArray__common *)YY, nxin, (int)sizeof(double));
  for (k = 0; k + 1 <= (int)fdbl; k++) {
    YY->data[k] = rt_hypotd_snf(x->data[k].re, x->data[k].im);
  }

  emxFree_creal_T(&x);
  nxin = YY->size[0];
  emxEnsureCapacity((emxArray__common *)YY, nxin, (int)sizeof(double));
  k0 = YY->size[0];
  for (nxin = 0; nxin < k0; nxin++) {
    YY->data[nxin] *= 2.0;
  }

  /*  figure; */
  /*  plot(f,2*abs(Y(1:NFFT/2+1))); */
  /*  L = length(data);                                                 % Length of signal */
  /*  NFFT = 2^nextpow2(L); */
  /*  f = Fs/2*linspace(0,1,NFFT/2+1); */
  /*  figure(1) */
  /*  Y = fft(data,NFFT)/L; */
  /*  % Plot single-sided amplitude spectrum. */
  /*  plot(f,2*abs(Y(1:NFFT/2+1)))                                        % 船首向信号谱分析 */
  /*  set(gca,'xlim',[0.005 0.5],'ylimmode','auto');  */
  /*  title('艏向快速傅里叶变换'); */
  /*  xlabel('频率/Hz'); */
  /*  ylabel('功率'); */
  /*  box off */
}

/*
 * File trailer for spectral.c
 *
 * [EOF]
 */
