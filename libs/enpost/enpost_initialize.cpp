/*
 * File: enpost_initialize.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 13-May-2016 08:54:51
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "enpost.h"
#include "enpost_initialize.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void enpost_initialize(void)
{
  rt_InitInfAndNaN(8U);
}

/*
 * File trailer for enpost_initialize.c
 *
 * [EOF]
 */
