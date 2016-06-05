/*
 * File: polyfit.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 20-May-2016 11:10:10
 */

/* Include Files */
#include "rt_nonfinite.h"
//#include "cycle_max.h"
#include "polyfit.h"
#include "xgeqp3.h"

/* Function Definitions */

/*
 * Arguments    : const double x[11]
 *                const double y[11]
 *                double p[2]
 * Return Type  : void
 */
void polyfit(const double x[11], const double y[11], double p[2])
{
  double V[22];
  int k;
  int jpvt[2];
  double tau[2];
  double p1[2];
  double B[11];
  int j;
  double wj;
  for (k = 0; k < 11; k++) {
    V[11 + k] = 1.0;
    V[k] = x[k];
  }

  xgeqp3(V, tau, jpvt);
  for (k = 0; k < 2; k++) {
    p1[k] = 0.0;
  }

  memcpy(&B[0], &y[0], 11U * sizeof(double));
  for (j = 0; j < 2; j++) {
    if (tau[j] != 0.0) {
      wj = B[j];
      for (k = j + 1; k + 1 < 12; k++) {
        wj += V[k + 11 * j] * B[k];
      }

      wj *= tau[j];
      if (wj != 0.0) {
        B[j] -= wj;
        for (k = j + 1; k + 1 < 12; k++) {
          B[k] -= V[k + 11 * j] * wj;
        }
      }
    }
  }

  for (k = 0; k < 2; k++) {
    p1[jpvt[k] - 1] = B[k];
  }

  for (j = 1; j >= 0; j += -1) {
    p1[jpvt[j] - 1] /= V[j + 11 * j];
    k = 1;
    while (k <= j) {
      p1[jpvt[0] - 1] -= p1[jpvt[1] - 1] * V[11];
      k = 2;
    }
  }

  for (k = 0; k < 2; k++) {
    p[k] = p1[k];
  }
}

/*
 * File trailer for polyfit.c
 *
 * [EOF]
 */
