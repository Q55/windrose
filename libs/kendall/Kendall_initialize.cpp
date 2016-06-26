/*
 * File: Kendall_initialize.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 12-Jun-2016 14:50:57
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "Kendall.h"
#include "Kendall_initialize.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void Kendall_initialize(void)
{
  rt_InitInfAndNaN(8U);
}

/*
 * File trailer for Kendall_initialize.c
 *
 * [EOF]
 */
