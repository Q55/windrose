/*
 * File: time_cont_initialize.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 20-May-2016 15:36:01
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "time_cont.h"
#include "time_cont_initialize.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void time_cont_initialize(void)
{
  rt_InitInfAndNaN(8U);
}

/*
 * File trailer for time_cont_initialize.c
 *
 * [EOF]
 */
