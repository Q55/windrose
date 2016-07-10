/*
 * File: sortrows.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "FPSO_MOTIONS.h"
#include "sortrows.h"
#include "fpso_sortLE.h"

/* Function Declarations */
static void apply_row_permutation(double y[24], const int idx[12]);

/* Function Definitions */

/*
 * Arguments    : double y[24]
 *                const int idx[12]
 * Return Type  : void
 */
static void apply_row_permutation(double y[24], const int idx[12])
{
  int j;
  double ycol[12];
  int i;
  for (j = 0; j < 2; j++) {
    for (i = 0; i < 12; i++) {
      ycol[i] = y[(idx[i] + 12 * j) - 1];
    }

    memcpy(&y[j * 12], &ycol[0], 12U * sizeof(double));
  }
}

/*
 * Arguments    : double y[24]
 * Return Type  : void
 */
void b_sortrows(double y[24])
{
  int iwork[12];
  int idx[12];
  int k;
  int i;
  int i2;
  int j;
  int pEnd;
  int p;
  int q;
  int qEnd;
  int kEnd;
  for (k = 0; k <= 11; k += 2) {
    if (b_sortLE(y, k + 1, k + 2)) {
      idx[k] = k + 1;
      idx[k + 1] = k + 2;
    } else {
      idx[k] = k + 2;
      idx[k + 1] = k + 1;
    }
  }

  i = 2;
  while (i < 12) {
    i2 = i << 1;
    j = 1;
    for (pEnd = 1 + i; pEnd < 13; pEnd = qEnd + i) {
      p = j;
      q = pEnd;
      qEnd = j + i2;
      if (qEnd > 13) {
        qEnd = 13;
      }

      k = 0;
      kEnd = qEnd - j;
      while (k + 1 <= kEnd) {
        if (b_sortLE(y, idx[p - 1], idx[q - 1])) {
          iwork[k] = idx[p - 1];
          p++;
          if (p == pEnd) {
            while (q < qEnd) {
              k++;
              iwork[k] = idx[q - 1];
              q++;
            }
          }
        } else {
          iwork[k] = idx[q - 1];
          q++;
          if (q == qEnd) {
            while (p < pEnd) {
              k++;
              iwork[k] = idx[p - 1];
              p++;
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

  apply_row_permutation(y, idx);
}

/*
 * Arguments    : double y[24]
 * Return Type  : void
 */
void sortrows(double y[24])
{
  int iwork[12];
  int idx[12];
  int k;
  int i;
  int i2;
  int j;
  int pEnd;
  int p;
  int q;
  int qEnd;
  int kEnd;
  for (k = 0; k <= 11; k += 2) {
    if (fpso_sortLE(y, k + 1, k + 2)) {
      idx[k] = k + 1;
      idx[k + 1] = k + 2;
    } else {
      idx[k] = k + 2;
      idx[k + 1] = k + 1;
    }
  }

  i = 2;
  while (i < 12) {
    i2 = i << 1;
    j = 1;
    for (pEnd = 1 + i; pEnd < 13; pEnd = qEnd + i) {
      p = j;
      q = pEnd;
      qEnd = j + i2;
      if (qEnd > 13) {
        qEnd = 13;
      }

      k = 0;
      kEnd = qEnd - j;
      while (k + 1 <= kEnd) {
        if (fpso_sortLE(y, idx[p - 1], idx[q - 1])) {
          iwork[k] = idx[p - 1];
          p++;
          if (p == pEnd) {
            while (q < qEnd) {
              k++;
              iwork[k] = idx[q - 1];
              q++;
            }
          }
        } else {
          iwork[k] = idx[q - 1];
          q++;
          if (q == qEnd) {
            while (p < pEnd) {
              k++;
              iwork[k] = idx[p - 1];
              p++;
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

  apply_row_permutation(y, idx);
}

/*
 * File trailer for sortrows.c
 *
 * [EOF]
 */
