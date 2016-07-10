/*
 * File: mrdivide.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "FPSO_MOTIONS.h"
#include "mrdivide.h"
#include "libs/commons/emxutil.h"
#include "qrsolve.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_real_T *A
 *                const emxArray_real_T *B
 * Return Type  : void
 */
void b_mrdivide(emxArray_real_T *A, const emxArray_real_T *B)
{
  emxArray_real_T *b_B;
  emxArray_real_T *b_A;
  int i8;
  int loop_ub;
  double d2;
  emxInit_real_T1(&b_B, 1);
  emxInit_real_T1(&b_A, 1);
  if ((A->size[1] == 0) || (B->size[1] == 0)) {
    i8 = A->size[0] * A->size[1];
    A->size[0] = 1;
    A->size[1] = 1;
    emxEnsureCapacity((emxArray__common *)A, i8, (int)sizeof(double));
    A->data[0] = 0.0;
  } else if (1 == B->size[1]) {
    if (A->size[1] == 0) {
    } else {
      A->data[0] *= 1.0 / B->data[0];
    }
  } else {
    i8 = b_B->size[0];
    b_B->size[0] = B->size[1];
    emxEnsureCapacity((emxArray__common *)b_B, i8, (int)sizeof(double));
    loop_ub = B->size[1];
    for (i8 = 0; i8 < loop_ub; i8++) {
      b_B->data[i8] = B->data[B->size[0] * i8];
    }

    i8 = b_A->size[0];
    b_A->size[0] = A->size[1];
    emxEnsureCapacity((emxArray__common *)b_A, i8, (int)sizeof(double));
    loop_ub = A->size[1];
    for (i8 = 0; i8 < loop_ub; i8++) {
      b_A->data[i8] = A->data[A->size[0] * i8];
    }

    d2 = qrsolve(b_B, b_A);
    i8 = A->size[0] * A->size[1];
    A->size[0] = 1;
    A->size[1] = 1;
    emxEnsureCapacity((emxArray__common *)A, i8, (int)sizeof(double));
    A->data[0] = d2;
  }

  emxFree_real_T(&b_A);
  emxFree_real_T(&b_B);
}

/*
 * Arguments    : double A
 *                const emxArray_real_T *B
 * Return Type  : double
 */
double mrdivide(double A, const emxArray_real_T *B)
{
  return 1.0 / B->data[0] * A;
}

/*
 * File trailer for mrdivide.c
 *
 * [EOF]
 */
