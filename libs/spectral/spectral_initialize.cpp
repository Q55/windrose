/*
 * File: spectral_initialize.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 13-May-2016 08:43:37
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "spectral.h"
#include "spectral_initialize.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void spectral_initialize(void)
{
  rt_InitInfAndNaN(8U);
}

/*
 * File trailer for spectral_initialize.c
 *
 * [EOF]
 */
