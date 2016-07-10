/*
 * File: qrsolve.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "FPSO_MOTIONS.h"
#include "qrsolve.h"
#include "libs/commons/emxutil.h"
#include "fpso_xgeqp3.h"

/* Function Declarations */
static int rankFromQR(const emxArray_real_T *A);

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *A
 * Return Type  : int
 */
static int rankFromQR(const emxArray_real_T *A)
{
  int r;
  int minmn;
  int maxmn;
  double tol;
  r = 0;
  if (A->size[0] < 1) {
    minmn = 0;
    maxmn = 1;
  } else {
    minmn = 1;
    maxmn = A->size[0];
  }

  if (minmn > 0) {
    tol = (double)maxmn * fabs(A->data[0]) * 2.2204460492503131E-16;
    while ((r < 1) && (fabs(A->data[0]) >= tol)) {
      r = 1;
    }
  }

  return r;
}

/*
 * Arguments    : const emxArray_real_T *A
 *                const emxArray_real_T *B
 * Return Type  : double
 */
double qrsolve(const emxArray_real_T *A, const emxArray_real_T *B)
{
  double Y;
  emxArray_real_T *b_A;
  int jpvt;
  int m;
  emxArray_real_T *b_B;
  int tau_size[1];
  double tau_data[1];
  int rankR;
  int mn;
  double wj;
  emxInit_real_T1(&b_A, 1);
  jpvt = b_A->size[0];
  b_A->size[0] = A->size[0];
  emxEnsureCapacity((emxArray__common *)b_A, jpvt, (int)sizeof(double));
  m = A->size[0];
  for (jpvt = 0; jpvt < m; jpvt++) {
    b_A->data[jpvt] = A->data[jpvt];
  }

  emxInit_real_T1(&b_B, 1);
  fpso_xgeqp3(b_A, tau_data, tau_size, &jpvt);
  rankR = rankFromQR(b_A);
  Y = 0.0;
  jpvt = b_B->size[0];
  b_B->size[0] = B->size[0];
  emxEnsureCapacity((emxArray__common *)b_B, jpvt, (int)sizeof(double));
  m = B->size[0];
  for (jpvt = 0; jpvt < m; jpvt++) {
    b_B->data[jpvt] = B->data[jpvt];
  }

  m = b_A->size[0];
  mn = !(b_A->size[0] < 1);
  jpvt = 1;
  while (jpvt <= mn) {
    if (tau_data[0] != 0.0) {
      wj = b_B->data[0];
      for (jpvt = 1; jpvt + 1 <= m; jpvt++) {
        wj += b_A->data[jpvt] * b_B->data[jpvt];
      }

      wj *= tau_data[0];
      if (wj != 0.0) {
        b_B->data[0] -= wj;
        for (jpvt = 1; jpvt + 1 <= m; jpvt++) {
          b_B->data[jpvt] -= b_A->data[jpvt] * wj;
        }
      }
    }

    jpvt = 2;
  }

  jpvt = 1;
  while (jpvt <= rankR) {
    Y = b_B->data[0];
    jpvt = 2;
  }

  emxFree_real_T(&b_B);
  while (rankR > 0) {
    Y /= b_A->data[0];
    rankR = 0;
  }

  emxFree_real_T(&b_A);
  return Y;
}

/*
 * File trailer for qrsolve.c
 *
 * [EOF]
 */
