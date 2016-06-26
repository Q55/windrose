/*
 * File: sortLE.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 12-Jun-2016 14:50:57
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "Kendall.h"
#include "sortLE.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *v
 *                int irow1
 *                int irow2
 * Return Type  : boolean_T
 */
boolean_T sortLE(const emxArray_real_T *v, int irow1, int irow2)
{
  boolean_T p;
  boolean_T b0;
  p = true;
  if ((v->data[irow1 - 1] == v->data[irow2 - 1]) || (rtIsNaN(v->data[irow1 - 1])
       && rtIsNaN(v->data[irow2 - 1]))) {
    b0 = true;
  } else {
    b0 = false;
  }

  if (!b0) {
    if ((v->data[irow1 - 1] <= v->data[irow2 - 1]) || rtIsNaN(v->data[irow2 - 1]))
    {
      p = true;
    } else {
      p = false;
    }
  }

  return p;
}

/*
 * File trailer for sortLE.c
 *
 * [EOF]
 */
