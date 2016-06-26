/*
 * File: Statistics_1d.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 11-Jun-2016 17:31:01
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "Statistics_1d.h"
#include "libs/commons/emxutil.h"

/* Function Definitions */

/*
 * 对数据进行一维统计
 * data1为一列数据
 * Arguments    : const emxArray_real_T *data1
 *                double step
 *                emxArray_real_T *yy
 * Return Type  : void
 */
void Statistics_1d(const emxArray_real_T *data1, double step, emxArray_real_T
                   *yy)
{
  int ixstart;
  int n;
  double ndbl;
  int ix;
  boolean_T exitg2;
  double x;
  int i0;
  emxArray_int32_T *r0;
  double anew;
  double apnd;
  double cdiff;
  double absa;
  double absb;
  emxArray_real_T *r1;
  emxArray_real_T *b_yy;
  int exitg1;
  emxArray_real_T *c_yy;
  ixstart = 1;
  n = data1->size[0];
  ndbl = data1->data[0];
  if (data1->size[0] > 1) {
    if (rtIsNaN(data1->data[0])) {
      ix = 2;
      exitg2 = false;
      while ((!exitg2) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(data1->data[ix - 1])) {
          ndbl = data1->data[ix - 1];
          exitg2 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < data1->size[0]) {
      while (ixstart + 1 <= n) {
        if (data1->data[ixstart] > ndbl) {
          ndbl = data1->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  x = ceil(ndbl / step);
  i0 = yy->size[0] * yy->size[1];
  yy->size[0] = (int)x;
  yy->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)yy, i0, (int)sizeof(double));
  ixstart = (int)x << 1;
  for (i0 = 0; i0 < ixstart; i0++) {
    yy->data[i0] = 0.0;
  }

  emxInit_int32_T(&r0, 1);
  ixstart = (int)x;
  i0 = r0->size[0];
  r0->size[0] = (int)x;
  emxEnsureCapacity((emxArray__common *)r0, i0, (int)sizeof(int));
  for (i0 = 0; i0 < ixstart; i0++) {
    r0->data[i0] = i0;
  }

  x = ndbl + step;
  if (rtIsNaN(step) || rtIsNaN(step) || rtIsNaN(x)) {
    n = 1;
    anew = rtNaN;
    apnd = x;
  } else if ((step == 0.0) || ((step < x) && (step < 0.0)) || ((x < step) &&
              (step > 0.0))) {
    n = 0;
    anew = step;
    apnd = x;
  } else if (rtIsInf(step) || rtIsInf(x)) {
    n = 1;
    anew = rtNaN;
    apnd = x;
  } else if (rtIsInf(step)) {
    n = 1;
    anew = step;
    apnd = x;
  } else {
    anew = step;
    ndbl = floor((x - step) / step + 0.5);
    apnd = step + ndbl * step;
    if (step > 0.0) {
      cdiff = apnd - x;
    } else {
      cdiff = x - apnd;
    }

    absa = fabs(step);
    absb = fabs(x);
    if ((absa >= absb) || rtIsNaN(absb)) {
      absb = absa;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
      ndbl++;
      apnd = x;
    } else if (cdiff > 0.0) {
      apnd = step + (ndbl - 1.0) * step;
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      n = (int)ndbl;
    } else {
      n = 0;
    }
  }

  emxInit_real_T(&r1, 2);
  i0 = r1->size[0] * r1->size[1];
  r1->size[0] = 1;
  r1->size[1] = n;
  emxEnsureCapacity((emxArray__common *)r1, i0, (int)sizeof(double));
  if (n > 0) {
    r1->data[0] = anew;
    if (n > 1) {
      r1->data[n - 1] = apnd;
      i0 = n - 1;
      ixstart = i0 / 2;
      for (ix = 1; ix < ixstart; ix++) {
        ndbl = (double)ix * step;
        r1->data[ix] = anew + ndbl;
        r1->data[(n - ix) - 1] = apnd - ndbl;
      }

      if (ixstart << 1 == n - 1) {
        r1->data[ixstart] = (anew + apnd) / 2.0;
      } else {
        ndbl = (double)ixstart * step;
        r1->data[ixstart] = anew + ndbl;
        r1->data[ixstart + 1] = apnd - ndbl;
      }
    }
  }

  ixstart = r0->size[0];
  for (i0 = 0; i0 < ixstart; i0++) {
    yy->data[r0->data[i0]] = r1->data[i0];
  }

  emxFree_real_T(&r1);
  emxFree_int32_T(&r0);
  for (n = 0; n < data1->size[0]; n++) {
    x = floor(data1->data[n] / step);
    yy->data[((int)(x + 1.0) + yy->size[0]) - 1]++;
  }

  emxInit_real_T1(&b_yy, 1);
  ndbl = step / 2.0;
  ixstart = yy->size[0];
  i0 = b_yy->size[0];
  b_yy->size[0] = ixstart;
  emxEnsureCapacity((emxArray__common *)b_yy, i0, (int)sizeof(double));
  for (i0 = 0; i0 < ixstart; i0++) {
    b_yy->data[i0] = yy->data[i0] - ndbl;
  }

  ixstart = b_yy->size[0];
  for (i0 = 0; i0 < ixstart; i0++) {
    yy->data[i0] = b_yy->data[i0];
  }

  emxFree_real_T(&b_yy);
  i0 = yy->size[0];
  if (i0 == 0) {
    ndbl = 0.0;
  } else {
    ndbl = yy->data[yy->size[0]];
    ix = 2;
    do {
      exitg1 = 0;
      i0 = yy->size[0];
      if (ix <= i0) {
        ndbl += yy->data[(ix + yy->size[0]) - 1];
        ix++;
      } else {
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  emxInit_real_T1(&c_yy, 1);
  ixstart = yy->size[0];
  i0 = c_yy->size[0];
  c_yy->size[0] = ixstart;
  emxEnsureCapacity((emxArray__common *)c_yy, i0, (int)sizeof(double));
  for (i0 = 0; i0 < ixstart; i0++) {
    c_yy->data[i0] = yy->data[i0 + yy->size[0]] / ndbl;
  }

  ixstart = c_yy->size[0];
  for (i0 = 0; i0 < ixstart; i0++) {
    yy->data[i0 + yy->size[0]] = c_yy->data[i0];
  }

  emxFree_real_T(&c_yy);
}

/*
 * File trailer for Statistics_1d.c
 *
 * [EOF]
 */
