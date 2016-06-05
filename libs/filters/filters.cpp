/*
 * File: filters.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 01-Jun-2016 09:36:33
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "filters.h"
#include "libs/commons/emxutil.h"
#include "libs/commons/ifft.h"
#include "libs/commons/fft.h"

/* Function Declarations */
static double rt_powd_snf(double u0, double u1);
static double rt_roundd_snf(double u);

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
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * Fs, sampling frequency, 1Hz for FPSO motion
 *  data, process data, FPSO motions ,mooring tensions typical
 *  Mdata, mean data
 *  Ldata, low frequency data
 *  Wdata, wave frequency data
 * Arguments    : double Fs
 *                const emxArray_real_T *data
 *                double *Mdata
 *                emxArray_real_T *Ldata
 *                emxArray_real_T *Wdata
 * Return Type  : void
 */
void filters(double Fs, const emxArray_real_T *data, double *Mdata,
             emxArray_real_T *Ldata, emxArray_real_T *Wdata)
{
  double dt;
  double fdbl;
  int k;
  emxArray_real_T *xx;
  int i0;
  int eint;
  double p;
  emxArray_creal_T *xf;
  double nfft;
  double n;
  double n2;
  emxArray_int32_T *r0;
  emxArray_creal_T *ixf;
  double nn;
  double nn2;
  dt = 1.0 / Fs;

  /*  mean data */
  if (data->size[0] == 0) {
    fdbl = 0.0;
  } else {
    fdbl = data->data[0];
    for (k = 2; k <= data->size[0]; k++) {
      fdbl += data->data[k - 1];
    }
  }

  emxInit_real_T(&xx, 1);
  *Mdata = fdbl / (double)data->size[0];
  i0 = xx->size[0];
  xx->size[0] = data->size[0];
  emxEnsureCapacity((emxArray__common *)xx, i0, (int)sizeof(double));
  k = data->size[0];
  for (i0 = 0; i0 < k; i0++) {
    xx->data[i0] = data->data[i0] - *Mdata;
  }

  /*  fft parameter */
  fdbl = frexp(data->size[0], &eint);
  p = eint;
  if (fdbl == 0.5) {
    p = (double)eint - 1.0;
  }

  emxInit_creal_T(&xf, 1);
  nfft = rt_powd_snf(2.0, p);

  /*  lowpass */
  fft(xx, nfft, xf);
  n = rt_roundd_snf(0.033333333333333333 * nfft * dt);
  n2 = nfft - n;
  if (n > n2) {
    i0 = 0;
    eint = 0;
  } else {
    i0 = (int)n - 1;
    eint = (int)n2;
  }

  emxInit_int32_T(&r0, 2);
  k = r0->size[0] * r0->size[1];
  r0->size[0] = 1;
  r0->size[1] = eint - i0;
  emxEnsureCapacity((emxArray__common *)r0, k, (int)sizeof(int));
  k = eint - i0;
  for (eint = 0; eint < k; eint++) {
    r0->data[r0->size[0] * eint] = i0 + eint;
  }

  k = r0->size[0] * r0->size[1];
  for (i0 = 0; i0 < k; i0++) {
    xf->data[r0->data[i0]].re = 0.0;
    xf->data[r0->data[i0]].im = 0.0;
  }

  emxInit_creal_T(&ixf, 1);
  ifft(xf, ixf);
  if (1 > data->size[0]) {
    k = 0;
  } else {
    k = data->size[0];
  }

  i0 = Ldata->size[0];
  Ldata->size[0] = k;
  emxEnsureCapacity((emxArray__common *)Ldata, i0, (int)sizeof(double));
  for (i0 = 0; i0 < k; i0++) {
    Ldata->data[i0] = ixf->data[i0].re;
  }

  /*  wavepass */
  fft(xx, nfft, xf);
  nn = rt_roundd_snf(0.033333333333333333 * nfft * dt);
  nn2 = nfft - nn;
  emxFree_real_T(&xx);
  if (1.0 > nn) {
    k = 0;
  } else {
    k = (int)nn;
  }

  i0 = r0->size[0] * r0->size[1];
  r0->size[0] = 1;
  r0->size[1] = k;
  emxEnsureCapacity((emxArray__common *)r0, i0, (int)sizeof(int));
  for (i0 = 0; i0 < k; i0++) {
    r0->data[r0->size[0] * i0] = i0;
  }

  k = r0->size[0] * r0->size[1];
  for (i0 = 0; i0 < k; i0++) {
    xf->data[r0->data[i0]].re = 0.0;
    xf->data[r0->data[i0]].im = 0.0;
  }

  if (nn2 > nfft) {
    i0 = 0;
    eint = 0;
  } else {
    i0 = (int)nn2 - 1;
    eint = (int)nfft;
  }

  k = r0->size[0] * r0->size[1];
  r0->size[0] = 1;
  r0->size[1] = eint - i0;
  emxEnsureCapacity((emxArray__common *)r0, k, (int)sizeof(int));
  k = eint - i0;
  for (eint = 0; eint < k; eint++) {
    r0->data[r0->size[0] * eint] = i0 + eint;
  }

  k = r0->size[0] * r0->size[1];
  for (i0 = 0; i0 < k; i0++) {
    xf->data[r0->data[i0]].re = 0.0;
    xf->data[r0->data[i0]].im = 0.0;
  }

  emxFree_int32_T(&r0);
  ifft(xf, ixf);
  emxFree_creal_T(&xf);
  if (1 > data->size[0]) {
    k = 0;
  } else {
    k = data->size[0];
  }

  i0 = Wdata->size[0];
  Wdata->size[0] = k;
  emxEnsureCapacity((emxArray__common *)Wdata, i0, (int)sizeof(double));
  for (i0 = 0; i0 < k; i0++) {
    Wdata->data[i0] = ixf->data[i0].re;
  }

  emxFree_creal_T(&ixf);
}

/*
 * File trailer for filters.c
 *
 * [EOF]
 */
