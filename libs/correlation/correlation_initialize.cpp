/*
 * File: correlation_initialize.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 12-May-2016 15:49:24
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "correlation.h"
#include "correlation_initialize.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void correlation_initialize(void)
{
  rt_InitInfAndNaN(8U);
}

/*
 * File trailer for correlation_initialize.c
 *
 * [EOF]
 */
