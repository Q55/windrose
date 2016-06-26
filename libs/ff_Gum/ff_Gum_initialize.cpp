/*
 * File: ff_Gum_initialize.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 11-Jun-2016 17:27:47
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "ff_Gum.h"
#include "ff_Gum_initialize.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void ff_Gum_initialize(void)
{
  rt_InitInfAndNaN(8U);
}

/*
 * File trailer for ff_Gum_initialize.c
 *
 * [EOF]
 */
