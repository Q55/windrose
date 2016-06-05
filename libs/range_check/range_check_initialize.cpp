/*
 * File: range_check_initialize.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 09-May-2016 16:10:52
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "range_check.h"
#include "range_check_initialize.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void range_check_initialize(void)
{
  rt_InitInfAndNaN(8U);
}

/*
 * File trailer for range_check_initialize.c
 *
 * [EOF]
 */
