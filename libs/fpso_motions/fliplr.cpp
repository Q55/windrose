/*
 * File: fliplr.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "FPSO_MOTIONS.h"
#include "fliplr.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_real_T *x
 * Return Type  : void
 */
void fliplr(emxArray_real_T *x)
{
  int n;
  int nd2;
  int b_j1;
  int j2;
  double xtmp;
  n = x->size[1] - 1;
  nd2 = x->size[1] >> 1;
  for (b_j1 = 0; b_j1 + 1 <= nd2; b_j1++) {
    j2 = n - b_j1;
    xtmp = x->data[b_j1];
    x->data[b_j1] = x->data[j2];
    x->data[j2] = xtmp;
  }
}

/*
 * File trailer for fliplr.c
 *
 * [EOF]
 */
