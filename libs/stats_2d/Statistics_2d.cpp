/*
 * File: Statistics_2d.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 11-Jun-2016 17:32:02
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "Statistics_2d.h"
#include "libs/commons/emxutil.h"
#include "Statistics_2d_sum.h"

/* Function Definitions */

/*
 * 对数据进行一维统计
 * data1,data2均为一列数据
 * 数据预处理，剔除不合格数据
 * Arguments    : const emxArray_real_T *data1
 *                const emxArray_real_T *data2
 *                double limit_min1
 *                double limit_min2
 *                double step1
 *                double step2
 *                emxArray_real_T *yy
 * Return Type  : void
 */
void Statistics_2d(const emxArray_real_T *data1, const emxArray_real_T *data2,
                   double limit_min1, double limit_min2, double step1, double
                   step2, emxArray_real_T *yy)
{
  int row;
  emxArray_real_T *sample1;
  int i0;
  int loop_ub;
  unsigned int mm;
  int ii;
  int n;
  emxArray_real_T *sample;
  int i1;
  int ixstart;
  double cdiff;
  int ix;
  boolean_T exitg2;
  double mtmp;
  boolean_T exitg1;
  double x;
  double ndbl;
  emxArray_int32_T *b_ii;
  int i2;
  double anew;
  double apnd;
  double absa;
  double absb;
  emxArray_real_T *b_x;
  int k;
  int i3;
  int i4;
  int i5;
  emxArray_real_T *b_yy;
  int i6;
  int b_loop_ub;
  emxArray_real_T *c_yy;
  if (data1->size[0] <= data2->size[0]) {
    row = data1->size[0];
  } else {
    row = data2->size[0];
  }

  emxInit_real_T(&sample1, 2);
  i0 = sample1->size[0] * sample1->size[1];
  sample1->size[0] = row;
  sample1->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)sample1, i0, (int)sizeof(double));
  loop_ub = row << 1;
  for (i0 = 0; i0 < loop_ub; i0++) {
    sample1->data[i0] = 0.0;
  }

  mm = 0U;
  for (ii = 0; ii < row; ii++) {
    if ((data1->data[ii] < limit_min1) || (data2->data[ii] < limit_min2) ||
        rtIsNaN(data1->data[ii]) || rtIsNaN(data2->data[ii])) {
    } else {
      mm++;
      sample1->data[(int)mm - 1] = data1->data[ii];
      sample1->data[((int)mm + sample1->size[0]) - 1] = data2->data[ii];
    }
  }

  if (1 > (int)mm) {
    n = 0;
  } else {
    n = (int)mm;
  }

  emxInit_real_T(&sample, 2);
  i0 = sample->size[0] * sample->size[1];
  sample->size[0] = n;
  sample->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)sample, i0, (int)sizeof(double));
  for (i0 = 0; i0 < 2; i0++) {
    for (i1 = 0; i1 < n; i1++) {
      sample->data[i1 + sample->size[0] * i0] = sample1->data[i1 + sample1->
        size[0] * i0];
    }
  }

  /* 对合格数据进行统计 */
  ixstart = 1;
  cdiff = sample->data[0];
  if (n > 1) {
    if (rtIsNaN(cdiff)) {
      ix = 2;
      exitg2 = false;
      while ((!exitg2) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(sample->data[ix - 1])) {
          cdiff = sample->data[ix - 1];
          exitg2 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < n) {
      while (ixstart + 1 <= n) {
        if (sample->data[ixstart] > cdiff) {
          cdiff = sample->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  ixstart = 1;
  mtmp = sample->data[sample->size[0]];
  if (n > 1) {
    if (rtIsNaN(mtmp)) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(sample->data[(ix + sample->size[0]) - 1])) {
          mtmp = sample->data[(ix + sample->size[0]) - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < n) {
      while (ixstart + 1 <= n) {
        if (sample->data[ixstart + sample->size[0]] > mtmp) {
          mtmp = sample->data[ixstart + sample->size[0]];
        }

        ixstart++;
      }
    }
  }

  emxFree_real_T(&sample);
  x = ceil(cdiff / step1);
  ndbl = ceil(mtmp / step2);
  i0 = yy->size[0] * yy->size[1];
  yy->size[0] = (int)(x + 1.0);
  yy->size[1] = (int)(ndbl + 1.0);
  emxEnsureCapacity((emxArray__common *)yy, i0, (int)sizeof(double));
  loop_ub = (int)(x + 1.0) * (int)(ndbl + 1.0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    yy->data[i0] = 0.0;
  }

  if (2 > (int)(x + 1.0)) {
    i0 = 0;
    i1 = 0;
  } else {
    i0 = 1;
    i1 = (int)(x + 1.0);
  }

  emxInit_int32_T(&b_ii, 1);
  i2 = b_ii->size[0];
  b_ii->size[0] = i1 - i0;
  emxEnsureCapacity((emxArray__common *)b_ii, i2, (int)sizeof(int));
  loop_ub = i1 - i0;
  for (i1 = 0; i1 < loop_ub; i1++) {
    b_ii->data[i1] = i0 + i1;
  }

  x = cdiff + step1;
  if (rtIsNaN(step1) || rtIsNaN(step1) || rtIsNaN(x)) {
    ix = 1;
    anew = rtNaN;
    apnd = x;
  } else if ((step1 == 0.0) || ((step1 < x) && (step1 < 0.0)) || ((x < step1) &&
              (step1 > 0.0))) {
    ix = 0;
    anew = step1;
    apnd = x;
  } else if (rtIsInf(step1) || rtIsInf(x)) {
    ix = 1;
    anew = rtNaN;
    apnd = x;
  } else if (rtIsInf(step1)) {
    ix = 1;
    anew = step1;
    apnd = x;
  } else {
    anew = step1;
    ndbl = floor((x - step1) / step1 + 0.5);
    apnd = step1 + ndbl * step1;
    if (step1 > 0.0) {
      cdiff = apnd - x;
    } else {
      cdiff = x - apnd;
    }

    absa = fabs(step1);
    absb = fabs(x);
    if ((absa >= absb) || rtIsNaN(absb)) {
      absb = absa;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
      ndbl++;
      apnd = x;
    } else if (cdiff > 0.0) {
      apnd = step1 + (ndbl - 1.0) * step1;
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      ix = (int)ndbl;
    } else {
      ix = 0;
    }
  }

  emxInit_real_T(&b_x, 2);
  i0 = b_x->size[0] * b_x->size[1];
  b_x->size[0] = 1;
  b_x->size[1] = ix;
  emxEnsureCapacity((emxArray__common *)b_x, i0, (int)sizeof(double));
  if (ix > 0) {
    b_x->data[0] = anew;
    if (ix > 1) {
      b_x->data[ix - 1] = apnd;
      i0 = ix - 1;
      ixstart = i0 / 2;
      for (k = 1; k < ixstart; k++) {
        cdiff = (double)k * step1;
        b_x->data[k] = anew + cdiff;
        b_x->data[(ix - k) - 1] = apnd - cdiff;
      }

      if (ixstart << 1 == ix - 1) {
        b_x->data[ixstart] = (anew + apnd) / 2.0;
      } else {
        cdiff = (double)ixstart * step1;
        b_x->data[ixstart] = anew + cdiff;
        b_x->data[ixstart + 1] = apnd - cdiff;
      }
    }
  }

  ixstart = b_ii->size[0];
  for (i0 = 0; i0 < ixstart; i0++) {
    yy->data[b_ii->data[i0]] = b_x->data[i0];
  }

  emxFree_int32_T(&b_ii);
  if (2 > yy->size[1]) {
    i0 = 0;
  } else {
    i0 = 1;
  }

  x = mtmp + step2;
  if (rtIsNaN(step2) || rtIsNaN(step2) || rtIsNaN(x)) {
    ix = 1;
    anew = rtNaN;
    apnd = x;
  } else if ((step2 == 0.0) || ((step2 < x) && (step2 < 0.0)) || ((x < step2) &&
              (step2 > 0.0))) {
    ix = 0;
    anew = step2;
    apnd = x;
  } else if (rtIsInf(step2) || rtIsInf(x)) {
    ix = 1;
    anew = rtNaN;
    apnd = x;
  } else if (rtIsInf(step2)) {
    ix = 1;
    anew = step2;
    apnd = x;
  } else {
    anew = step2;
    ndbl = floor((x - step2) / step2 + 0.5);
    apnd = step2 + ndbl * step2;
    if (step2 > 0.0) {
      cdiff = apnd - x;
    } else {
      cdiff = x - apnd;
    }

    absa = fabs(step2);
    absb = fabs(x);
    if ((absa >= absb) || rtIsNaN(absb)) {
      absb = absa;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
      ndbl++;
      apnd = x;
    } else if (cdiff > 0.0) {
      apnd = step2 + (ndbl - 1.0) * step2;
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      ix = (int)ndbl;
    } else {
      ix = 0;
    }
  }

  i1 = b_x->size[0] * b_x->size[1];
  b_x->size[0] = 1;
  b_x->size[1] = ix;
  emxEnsureCapacity((emxArray__common *)b_x, i1, (int)sizeof(double));
  if (ix > 0) {
    b_x->data[0] = anew;
    if (ix > 1) {
      b_x->data[ix - 1] = apnd;
      i1 = ix - 1;
      ixstart = i1 / 2;
      for (k = 1; k < ixstart; k++) {
        cdiff = (double)k * step2;
        b_x->data[k] = anew + cdiff;
        b_x->data[(ix - k) - 1] = apnd - cdiff;
      }

      if (ixstart << 1 == ix - 1) {
        b_x->data[ixstart] = (anew + apnd) / 2.0;
      } else {
        cdiff = (double)ixstart * step2;
        b_x->data[ixstart] = anew + cdiff;
        b_x->data[ixstart + 1] = apnd - cdiff;
      }
    }
  }

  loop_ub = b_x->size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    yy->data[yy->size[0] * (i0 + i1)] = b_x->data[b_x->size[0] * i1];
  }

  for (ix = 0; ix < n; ix++) {
    x = floor(sample1->data[ix] / step1);
    ndbl = floor(sample1->data[ix + sample1->size[0]] / step2);
    yy->data[((int)(x + 2.0) + yy->size[0] * ((int)(ndbl + 2.0) - 1)) - 1]++;
  }

  emxFree_real_T(&sample1);
  if (2 > yy->size[0]) {
    i0 = 0;
    i1 = 0;
  } else {
    i0 = 1;
    i1 = yy->size[0];
  }

  if (2 > yy->size[1]) {
    i2 = 0;
    i3 = 0;
  } else {
    i2 = 1;
    i3 = yy->size[1];
  }

  if (2 > yy->size[0]) {
    ixstart = 0;
    ix = 0;
  } else {
    ixstart = 1;
    ix = yy->size[0];
  }

  if (2 > yy->size[1]) {
    k = 0;
    n = 0;
  } else {
    k = 1;
    n = yy->size[1];
  }

  if (2 > yy->size[0]) {
    i4 = 0;
  } else {
    i4 = 1;
  }

  if (2 > yy->size[1]) {
    i5 = 0;
  } else {
    i5 = 1;
  }

  emxInit_real_T(&b_yy, 2);
  i6 = b_yy->size[0] * b_yy->size[1];
  b_yy->size[0] = ix - ixstart;
  b_yy->size[1] = n - k;
  emxEnsureCapacity((emxArray__common *)b_yy, i6, (int)sizeof(double));
  loop_ub = n - k;
  for (n = 0; n < loop_ub; n++) {
    b_loop_ub = ix - ixstart;
    for (i6 = 0; i6 < b_loop_ub; i6++) {
      b_yy->data[i6 + b_yy->size[0] * n] = yy->data[(ixstart + i6) + yy->size[0]
        * (k + n)];
    }
  }

  stats2DSum(b_yy, b_x);
  emxFree_real_T(&b_yy);
  if (b_x->size[1] == 0) {
    cdiff = 0.0;
  } else {
    cdiff = b_x->data[0];
    for (k = 2; k <= b_x->size[1]; k++) {
      cdiff += b_x->data[k - 1];
    }
  }

  emxFree_real_T(&b_x);
  emxInit_real_T(&c_yy, 2);
  ixstart = c_yy->size[0] * c_yy->size[1];
  c_yy->size[0] = i1 - i0;
  c_yy->size[1] = i3 - i2;
  emxEnsureCapacity((emxArray__common *)c_yy, ixstart, (int)sizeof(double));
  loop_ub = i3 - i2;
  for (i3 = 0; i3 < loop_ub; i3++) {
    b_loop_ub = i1 - i0;
    for (ixstart = 0; ixstart < b_loop_ub; ixstart++) {
      c_yy->data[ixstart + c_yy->size[0] * i3] = yy->data[(i0 + ixstart) +
        yy->size[0] * (i2 + i3)] / cdiff;
    }
  }

  loop_ub = c_yy->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_loop_ub = c_yy->size[0];
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      yy->data[(i4 + i1) + yy->size[0] * (i5 + i0)] = c_yy->data[i1 + c_yy->
        size[0] * i0];
    }
  }

  emxFree_real_T(&c_yy);
}

/*
 * File trailer for Statistics_2d.c
 *
 * [EOF]
 */
