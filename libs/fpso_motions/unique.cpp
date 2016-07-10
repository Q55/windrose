/*
 * File: unique.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "FPSO_MOTIONS.h"
#include "unique.h"

/* Function Definitions */

/*
 * Arguments    : int *nMInf
 *                int *nFinite
 *                int *nPInf
 *                int *nNaN
 * Return Type  : void
 */
void count_nonfinites(int *nMInf, int *nFinite, int *nPInf, int *nNaN)
{
  *nMInf = 0;
  *nNaN = 0;
  *nPInf = 0;
  *nFinite = 1248;
}

/*
 * File trailer for unique.c
 *
 * [EOF]
 */
