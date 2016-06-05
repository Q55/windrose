/*
 * File: fft.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 01-Jun-2016 09:36:33
 */

/* Include Files */
#include "rt_nonfinite.h"
//#include "filters.h"
#include "fft.h"
#include "emxutil.h"
#include "ifft.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                double varargin_1
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void fft(const emxArray_real_T *x, double varargin_1, emxArray_creal_T *y)
{
  int ju;
  int nd2;
  int minval;
  int ixDelta;
  emxArray_real_T *costab1q;
  int nRowsD2;
  int nRowsD4;
  int lastChan;
  double e;
  int k;
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  int n;
  int ix;
  int chanStart;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  int ihi;
  int istart;
  int j;
  double twid_im;
  ju = y->size[0];
  y->size[0] = (int)varargin_1;
  emxEnsureCapacity((emxArray__common *)y, ju, (int)sizeof(creal_T));
  if ((int)varargin_1 > x->size[0]) {
    nd2 = y->size[0];
    ju = y->size[0];
    y->size[0] = nd2;
    emxEnsureCapacity((emxArray__common *)y, ju, (int)sizeof(creal_T));
    for (ju = 0; ju < nd2; ju++) {
      y->data[ju].re = 0.0;
      y->data[ju].im = 0.0;
    }
  }

  if (x->size[0] == 0) {
  } else {
    if (x->size[0] <= (int)varargin_1) {
      minval = x->size[0];
    } else {
      minval = (int)varargin_1;
    }

    nd2 = (x->size[0] - minval) + 1;
    if (1 >= nd2) {
      ixDelta = 1;
    } else {
      ixDelta = nd2;
    }

    emxInit_real_T1(&costab1q, 2);
    ju = (int)varargin_1;
    nRowsD2 = ju / 2;
    nRowsD4 = nRowsD2 / 2;
    lastChan = (int)varargin_1 * (div_s32(x->size[0], x->size[0]) - 1);
    e = 6.2831853071795862 / (double)(int)varargin_1;
    ju = costab1q->size[0] * costab1q->size[1];
    costab1q->size[0] = 1;
    costab1q->size[1] = nRowsD4 + 1;
    emxEnsureCapacity((emxArray__common *)costab1q, ju, (int)sizeof(double));
    costab1q->data[0] = 1.0;
    nd2 = nRowsD4 / 2;
    for (k = 1; k <= nd2; k++) {
      costab1q->data[k] = cos(e * (double)k);
    }

    for (k = nd2 + 1; k < nRowsD4; k++) {
      costab1q->data[k] = sin(e * (double)(nRowsD4 - k));
    }

    emxInit_real_T1(&costab, 2);
    emxInit_real_T1(&sintab, 2);
    costab1q->data[nRowsD4] = 0.0;
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    ju = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity((emxArray__common *)costab, ju, (int)sizeof(double));
    ju = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity((emxArray__common *)sintab, ju, (int)sizeof(double));
    costab->data[0] = 1.0;
    sintab->data[0] = 0.0;
    for (k = 1; k <= n; k++) {
      costab->data[k] = costab1q->data[k];
      sintab->data[k] = -costab1q->data[n - k];
    }

    for (k = costab1q->size[1]; k <= nd2; k++) {
      costab->data[k] = -costab1q->data[nd2 - k];
      sintab->data[k] = -costab1q->data[k - n];
    }

    emxFree_real_T(&costab1q);
    ix = 0;
    chanStart = 0;
    while (((int)varargin_1 > 0) && (chanStart <= lastChan)) {
      ju = 0;
      nd2 = chanStart;
      for (i = 1; i < minval; i++) {
        y->data[nd2].re = x->data[ix];
        y->data[nd2].im = 0.0;
        n = (int)varargin_1;
        tst = true;
        while (tst) {
          n >>= 1;
          ju ^= n;
          tst = ((ju & n) == 0);
        }

        nd2 = chanStart + ju;
        ix++;
      }

      y->data[nd2].re = x->data[ix];
      y->data[nd2].im = 0.0;
      ix += ixDelta;
      nd2 = (chanStart + (int)varargin_1) - 2;
      if ((int)varargin_1 > 1) {
        for (i = chanStart; i <= nd2; i += 2) {
          temp_re = y->data[i + 1].re;
          temp_im = y->data[i + 1].im;
          y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
          y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
          y->data[i].re += temp_re;
          y->data[i].im += temp_im;
        }
      }

      nd2 = 2;
      ju = 4;
      k = nRowsD4;
      n = 1 + ((nRowsD4 - 1) << 2);
      while (k > 0) {
        i = chanStart;
        ihi = chanStart + n;
        while (i < ihi) {
          temp_re = y->data[i + nd2].re;
          temp_im = y->data[i + nd2].im;
          y->data[i + nd2].re = y->data[i].re - temp_re;
          y->data[i + nd2].im = y->data[i].im - temp_im;
          y->data[i].re += temp_re;
          y->data[i].im += temp_im;
          i += ju;
        }

        istart = chanStart + 1;
        for (j = k; j < nRowsD2; j += k) {
          e = costab->data[j];
          twid_im = sintab->data[j];
          i = istart;
          ihi = istart + n;
          while (i < ihi) {
            temp_re = e * y->data[i + nd2].re - twid_im * y->data[i + nd2].im;
            temp_im = e * y->data[i + nd2].im + twid_im * y->data[i + nd2].re;
            y->data[i + nd2].re = y->data[i].re - temp_re;
            y->data[i + nd2].im = y->data[i].im - temp_im;
            y->data[i].re += temp_re;
            y->data[i].im += temp_im;
            i += ju;
          }

          istart++;
        }

        k /= 2;
        nd2 = ju;
        ju <<= 1;
        n -= nd2;
      }

      chanStart += (int)varargin_1;
    }

    emxFree_real_T(&sintab);
    emxFree_real_T(&costab);
  }
}

/*
 * File trailer for fft.c
 *
 * [EOF]
 */
