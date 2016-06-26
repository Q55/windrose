/*
 * File: ff_GB_initialize.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 11-Jun-2016 17:26:48
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "ff_GB.h"
#include "ff_GB_initialize.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void ff_GB_initialize(void)
{
  rt_InitInfAndNaN(8U);
}

/*
 * File trailer for ff_GB_initialize.c
 *
 * [EOF]
 */
