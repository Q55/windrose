/*
 * File: filters_initialize.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 01-Jun-2016 09:36:33
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "filters.h"
#include "filters_initialize.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void filters_initialize(void)
{
  rt_InitInfAndNaN(8U);
}

/*
 * File trailer for filters_initialize.c
 *
 * [EOF]
 */
