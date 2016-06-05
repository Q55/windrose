/*
 * File: ifft.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 01-Jun-2016 09:36:33
 */

/* Include Files */
#include "rt_nonfinite.h"
//#include "filters.h"
#include "ifft.h"
#include "emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *x
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void ifft(const emxArray_creal_T *x, emxArray_creal_T *y)
{
  int n1;
  int sz_idx_0;
  int ju;
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
  n1 = x->size[0];
  sz_idx_0 = x->size[0];
  ju = y->size[0];
  y->size[0] = sz_idx_0;
  emxEnsureCapacity((emxArray__common *)y, ju, (int)sizeof(creal_T));
  if (x->size[0] == 0) {
  } else {
    minval = x->size[0] - 1;
    sz_idx_0 = x->size[0] - minval;
    if (1 >= sz_idx_0) {
      ixDelta = 1;
    } else {
      ixDelta = sz_idx_0;
    }

    emxInit_real_T1(&costab1q, 2);
    ju = x->size[0];
    nRowsD2 = ju / 2;
    nRowsD4 = nRowsD2 / 2;
    lastChan = x->size[0] * (div_s32(x->size[0], x->size[0]) - 1);
    e = 6.2831853071795862 / (double)x->size[0];
    ju = costab1q->size[0] * costab1q->size[1];
    costab1q->size[0] = 1;
    costab1q->size[1] = nRowsD4 + 1;
    emxEnsureCapacity((emxArray__common *)costab1q, ju, (int)sizeof(double));
    costab1q->data[0] = 1.0;
    sz_idx_0 = nRowsD4 / 2;
    for (k = 1; k <= sz_idx_0; k++) {
      costab1q->data[k] = cos(e * (double)k);
    }

    for (k = sz_idx_0 + 1; k < nRowsD4; k++) {
      costab1q->data[k] = sin(e * (double)(nRowsD4 - k));
    }

    emxInit_real_T1(&costab, 2);
    emxInit_real_T1(&sintab, 2);
    costab1q->data[nRowsD4] = 0.0;
    n = costab1q->size[1] - 1;
    sz_idx_0 = (costab1q->size[1] - 1) << 1;
    ju = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = sz_idx_0 + 1;
    emxEnsureCapacity((emxArray__common *)costab, ju, (int)sizeof(double));
    ju = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = sz_idx_0 + 1;
    emxEnsureCapacity((emxArray__common *)sintab, ju, (int)sizeof(double));
    costab->data[0] = 1.0;
    sintab->data[0] = 0.0;
    for (k = 1; k <= n; k++) {
      costab->data[k] = costab1q->data[k];
      sintab->data[k] = costab1q->data[n - k];
    }

    for (k = costab1q->size[1]; k <= sz_idx_0; k++) {
      costab->data[k] = -costab1q->data[sz_idx_0 - k];
      sintab->data[k] = costab1q->data[k - n];
    }

    emxFree_real_T(&costab1q);
    ix = 0;
    chanStart = 0;
    while ((n1 > 0) && (chanStart <= lastChan)) {
      ju = 0;
      sz_idx_0 = chanStart;
      for (i = 1; i <= minval; i++) {
        y->data[sz_idx_0] = x->data[ix];
        n = n1;
        tst = true;
        while (tst) {
          n >>= 1;
          ju ^= n;
          tst = ((ju & n) == 0);
        }

        sz_idx_0 = chanStart + ju;
        ix++;
      }

      y->data[sz_idx_0] = x->data[ix];
      ix += ixDelta;
      sz_idx_0 = (chanStart + n1) - 2;
      if (n1 > 1) {
        for (i = chanStart; i <= sz_idx_0; i += 2) {
          temp_re = y->data[i + 1].re;
          temp_im = y->data[i + 1].im;
          y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
          y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
          y->data[i].re += temp_re;
          y->data[i].im += temp_im;
        }
      }

      sz_idx_0 = 2;
      ju = 4;
      k = nRowsD4;
      n = 1 + ((nRowsD4 - 1) << 2);
      while (k > 0) {
        i = chanStart;
        ihi = chanStart + n;
        while (i < ihi) {
          temp_re = y->data[i + sz_idx_0].re;
          temp_im = y->data[i + sz_idx_0].im;
          y->data[i + sz_idx_0].re = y->data[i].re - temp_re;
          y->data[i + sz_idx_0].im = y->data[i].im - temp_im;
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
            temp_re = e * y->data[i + sz_idx_0].re - twid_im * y->data[i +
              sz_idx_0].im;
            temp_im = e * y->data[i + sz_idx_0].im + twid_im * y->data[i +
              sz_idx_0].re;
            y->data[i + sz_idx_0].re = y->data[i].re - temp_re;
            y->data[i + sz_idx_0].im = y->data[i].im - temp_im;
            y->data[i].re += temp_re;
            y->data[i].im += temp_im;
            i += ju;
          }

          istart++;
        }

        k /= 2;
        sz_idx_0 = ju;
        ju <<= 1;
        n -= sz_idx_0;
      }

      chanStart += n1;
    }

    emxFree_real_T(&sintab);
    emxFree_real_T(&costab);
    if (y->size[0] > 1) {
      e = 1.0 / (double)y->size[0];
      ju = y->size[0];
      emxEnsureCapacity((emxArray__common *)y, ju, (int)sizeof(creal_T));
      sz_idx_0 = y->size[0];
      for (ju = 0; ju < sz_idx_0; ju++) {
        y->data[ju].re *= e;
        y->data[ju].im *= e;
      }
    }
  }
}

/*
 * File trailer for ifft.c
 *
 * [EOF]
 */
