/*
 * File: sortIdx.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "FPSO_MOTIONS.h"
#include "sortIdx.h"

/* Function Definitions */

/*
 * Arguments    : const double x[1248]
 *                int idx[1248]
 * Return Type  : void
 */
void sortIdx(const double x[1248], int idx[1248])
{
  int iwork[1248];
  int k;
  boolean_T p;
  int i;
  int i2;
  int j;
  int pEnd;
  int b_p;
  int q;
  int qEnd;
  int kEnd;
  for (k = 0; k <= 1247; k += 2) {
    if ((x[k] <= x[k + 1]) || rtIsNaN(x[k + 1])) {
      p = true;
    } else {
      p = false;
    }

    if (p) {
      idx[k] = k + 1;
      idx[k + 1] = k + 2;
    } else {
      idx[k] = k + 2;
      idx[k + 1] = k + 1;
    }
  }

  i = 2;
  while (i < 1248) {
    i2 = i << 1;
    j = 1;
    for (pEnd = 1 + i; pEnd < 1249; pEnd = qEnd + i) {
      b_p = j;
      q = pEnd - 1;
      qEnd = j + i2;
      if (qEnd > 1249) {
        qEnd = 1249;
      }

      k = 0;
      kEnd = qEnd - j;
      while (k + 1 <= kEnd) {
        if ((x[idx[b_p - 1] - 1] <= x[idx[q] - 1]) || rtIsNaN(x[idx[q] - 1])) {
          p = true;
        } else {
          p = false;
        }

        if (p) {
          iwork[k] = idx[b_p - 1];
          b_p++;
          if (b_p == pEnd) {
            while (q + 1 < qEnd) {
              k++;
              iwork[k] = idx[q];
              q++;
            }
          }
        } else {
          iwork[k] = idx[q];
          q++;
          if (q + 1 == qEnd) {
            while (b_p < pEnd) {
              k++;
              iwork[k] = idx[b_p - 1];
              b_p++;
            }
          }
        }

        k++;
      }

      for (k = 0; k + 1 <= kEnd; k++) {
        idx[(j + k) - 1] = iwork[k];
      }

      j = qEnd;
    }

    i = i2;
  }
}

/*
 * File trailer for sortIdx.c
 *
 * [EOF]
 */
