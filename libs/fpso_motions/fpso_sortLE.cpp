/*
 * File: sortLE.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "FPSO_MOTIONS.h"
#include "fpso_sortLE.h"

/* Function Definitions */

/*
 * Arguments    : const double v[24]
 *                int irow1
 *                int irow2
 * Return Type  : boolean_T
 */
boolean_T b_sortLE(const double v[24], int irow1, int irow2)
{
  boolean_T p;
  boolean_T b1;
  p = true;
  if ((v[irow1 + 11] == v[irow2 + 11]) || (rtIsNaN(v[irow1 + 11]) && rtIsNaN
       (v[irow2 + 11]))) {
    b1 = true;
  } else {
    b1 = false;
  }

  if (!b1) {
    if ((v[irow1 + 11] >= v[irow2 + 11]) || rtIsNaN(v[irow1 + 11])) {
      p = true;
    } else {
      p = false;
    }
  }

  return p;
}

/*
 * Arguments    : const double v[24]
 *                int irow1
 *                int irow2
 * Return Type  : boolean_T
 */
boolean_T fpso_sortLE(const double v[24], int irow1, int irow2)
{
  boolean_T p;
  boolean_T b0;
  p = true;
  if ((v[irow1 + 11] == v[irow2 + 11]) || (rtIsNaN(v[irow1 + 11]) && rtIsNaN
       (v[irow2 + 11]))) {
    b0 = true;
  } else {
    b0 = false;
  }

  if (!b0) {
    if ((v[irow1 + 11] <= v[irow2 + 11]) || rtIsNaN(v[irow2 + 11])) {
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
