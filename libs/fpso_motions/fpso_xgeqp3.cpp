/*
 * File: xgeqp3.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "FPSO_MOTIONS.h"
#include "fpso_xgeqp3.h"
#include "xzlarfg.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_real_T *A
 *                double tau_data[]
 *                int tau_size[1]
 *                int *jpvt
 * Return Type  : void
 */
void fpso_xgeqp3(emxArray_real_T *A, double tau_data[], int tau_size[1], int *jpvt)
{
  int m;
  int mn;
  int i;
  double atmp;
  double d3;
  m = A->size[0];
  if (A->size[0] <= 1) {
    mn = A->size[0];
  } else {
    mn = 1;
  }

  tau_size[0] = mn;
  if (A->size[0] == 0) {
  } else {
    i = 1;
    while (i <= mn) {
      if (1 < m) {
        atmp = A->data[0];
        d3 = xzlarfg(m, &atmp, A);
        tau_data[0] = d3;
        A->data[0] = atmp;
      } else {
        tau_data[0] = 0.0;
      }

      i = 2;
    }
  }

  *jpvt = 1;
}

/*
 * File trailer for xgeqp3.c
 *
 * [EOF]
 */
