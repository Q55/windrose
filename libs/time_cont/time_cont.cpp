/*
 * File: time_cont.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 20-May-2016 15:36:01
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "time_cont.h"
#include "libs/commons/emxutil.h"
#include "libs/commons/diff.h"

/* Function Declarations */
static double rt_roundd_snf(double u);

/* Function Definitions */

/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * 时间连续性筛查(已验证)
 * time_row表示第几列是时间列
 * Arguments    : const emxArray_real_T *data
 *                double time_row
 *                double time_step
 *                double check
 *                emxArray_real_T *data_out
 * Return Type  : void
 */
void time_cont(const emxArray_real_T *data, double time_row, double time_step,
               double check, emxArray_real_T *data_out)
{
  double delta1;
  int i0;
  int nx;
  emxArray_real_T *b_data;
  emxArray_real_T *flag_tc;
  emxArray_boolean_T *x;
  emxArray_int32_T *ii;
  int idx;
  int b_ii;
  boolean_T exitg1;
  boolean_T guard1 = false;
  emxArray_real_T *r0;
  int jj;
  emxArray_real_T *data_temp;
  double kk;
  double ll;
  int i1;
  double space;
  double d1;
  double delta2;
  delta1 = rt_roundd_snf((data->data[(data->size[0] + data->size[0] * ((int)
    time_row - 1)) - 1] - data->data[data->size[0] * ((int)time_row - 1)]) /
    time_step);
  i0 = data_out->size[0] * data_out->size[1];
  data_out->size[0] = (int)(delta1 + 1.0);
  data_out->size[1] = data->size[1];
  emxEnsureCapacity((emxArray__common *)data_out, i0, (int)sizeof(double));
  nx = (int)(delta1 + 1.0) * data->size[1];
  for (i0 = 0; i0 < nx; i0++) {
    data_out->data[i0] = 0.0;
  }

  emxInit_real_T(&b_data, 1);

  /* 存储数据空数组 */
  delta1 = time_step / 1000.0;
  nx = data->size[0];
  i0 = b_data->size[0];
  b_data->size[0] = nx;
  emxEnsureCapacity((emxArray__common *)b_data, i0, (int)sizeof(double));
  for (i0 = 0; i0 < nx; i0++) {
    b_data->data[i0] = data->data[i0 + data->size[0] * ((int)time_row - 1)];
  }

  emxInit_real_T(&flag_tc, 1);
  emxInit_boolean_T(&x, 1);
  diff(b_data, flag_tc);
  i0 = x->size[0];
  x->size[0] = flag_tc->size[0];
  emxEnsureCapacity((emxArray__common *)x, i0, (int)sizeof(boolean_T));
  nx = flag_tc->size[0];
  emxFree_real_T(&b_data);
  for (i0 = 0; i0 < nx; i0++) {
    x->data[i0] = (flag_tc->data[i0] - time_step > delta1);
  }

  emxInit_int32_T(&ii, 1);
  nx = x->size[0];
  idx = 0;
  i0 = ii->size[0];
  ii->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)ii, i0, (int)sizeof(int));
  b_ii = 1;
  exitg1 = false;
  while ((!exitg1) && (b_ii <= nx)) {
    guard1 = false;
    if (x->data[b_ii - 1]) {
      idx++;
      ii->data[idx - 1] = b_ii;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      b_ii++;
    }
  }

  if (x->size[0] == 1) {
    if (idx == 0) {
      i0 = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)ii, i0, (int)sizeof(int));
    }
  } else {
    i0 = ii->size[0];
    if (1 > idx) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = idx;
    }

    emxEnsureCapacity((emxArray__common *)ii, i0, (int)sizeof(int));
  }

  emxFree_boolean_T(&x);
  i0 = flag_tc->size[0];
  flag_tc->size[0] = ii->size[0];
  emxEnsureCapacity((emxArray__common *)flag_tc, i0, (int)sizeof(double));
  nx = ii->size[0];
  for (i0 = 0; i0 < nx; i0++) {
    flag_tc->data[i0] = ii->data[i0];
  }

  emxFree_int32_T(&ii);

  /* 查找时间不连续的位置 */
  if (!(flag_tc->size[0] == 0)) {
    emxInit_real_T(&r0, 1);
    i0 = r0->size[0];
    r0->size[0] = 1 + flag_tc->size[0];
    emxEnsureCapacity((emxArray__common *)r0, i0, (int)sizeof(double));
    r0->data[0] = 0.0;
    nx = flag_tc->size[0];
    for (i0 = 0; i0 < nx; i0++) {
      r0->data[i0 + 1] = flag_tc->data[i0];
    }

    i0 = flag_tc->size[0];
    flag_tc->size[0] = r0->size[0];
    emxEnsureCapacity((emxArray__common *)flag_tc, i0, (int)sizeof(double));
    nx = r0->size[0];
    for (i0 = 0; i0 < nx; i0++) {
      flag_tc->data[i0] = r0->data[i0];
    }

    emxFree_real_T(&r0);
    jj = 0;
    emxInit_real_T1(&data_temp, 2);
    while (jj <= data->size[1] - 1) {
      kk = 1.0;
      for (b_ii = 1; b_ii - 1 <= flag_tc->size[0] - 2; b_ii++) {
        ll = flag_tc->data[b_ii] - flag_tc->data[b_ii - 1];
        if (flag_tc->data[b_ii - 1] + 1.0 > flag_tc->data[b_ii]) {
          i0 = 1;
          idx = 0;
        } else {
          i0 = (int)(flag_tc->data[b_ii - 1] + 1.0);
          idx = (int)flag_tc->data[b_ii];
        }

        if (kk > (kk + ll) - 1.0) {
          i1 = 0;
        } else {
          i1 = (int)kk - 1;
        }

        nx = idx - i0;
        for (idx = 0; idx <= nx; idx++) {
          data_out->data[(i1 + idx) + data_out->size[0] * jj] = data->data[((i0
            + idx) + data->size[0] * jj) - 1];
        }

        kk += ll;
        space = rt_roundd_snf((data->data[((int)(flag_tc->data[b_ii] + 1.0) +
          data->size[0] * ((int)time_row - 1)) - 1] - data->data[((int)
          flag_tc->data[b_ii] + data->size[0] * ((int)time_row - 1)) - 1]) /
                              time_step);
        if (check == 1.0) {
          delta1 = space + 1.0;
          if (space + 1.0 < 0.0) {
            delta1 = 0.0;
          }

          i0 = data_temp->size[0] * data_temp->size[1];
          data_temp->size[0] = 1;
          data_temp->size[1] = (int)floor(delta1);
          emxEnsureCapacity((emxArray__common *)data_temp, i0, (int)sizeof
                            (double));
          if (data_temp->size[1] >= 1) {
            data_temp->data[data_temp->size[1] - 1] = -99.0;
            if (data_temp->size[1] >= 2) {
              data_temp->data[0] = -99.0;
              if (data_temp->size[1] >= 3) {
                i0 = data_temp->size[1];
                for (nx = 0; nx <= i0 - 3; nx++) {
                  data_temp->data[nx + 1] = -99.0;
                }
              }
            }
          }
        } else {
          d1 = data->data[((int)flag_tc->data[b_ii] + data->size[0] * jj) - 1];
          delta1 = space + 1.0;
          if (space + 1.0 < 0.0) {
            delta1 = 0.0;
          }

          i0 = data_temp->size[0] * data_temp->size[1];
          data_temp->size[0] = 1;
          data_temp->size[1] = (int)floor(delta1);
          emxEnsureCapacity((emxArray__common *)data_temp, i0, (int)sizeof
                            (double));
          if (data_temp->size[1] >= 1) {
            data_temp->data[data_temp->size[1] - 1] = data->data[((int)
              (flag_tc->data[b_ii] + 1.0) + data->size[0] * jj) - 1];
            if (data_temp->size[1] >= 2) {
              data_temp->data[0] = data->data[((int)flag_tc->data[b_ii] +
                data->size[0] * jj) - 1];
              if (data_temp->size[1] >= 3) {
                if (((data->data[((int)flag_tc->data[b_ii] + data->size[0] * jj)
                      - 1] < 0.0) != (data->data[((int)(flag_tc->data[b_ii] +
                        1.0) + data->size[0] * jj) - 1] < 0.0)) && ((fabs
                      (data->data[((int)flag_tc->data[b_ii] + data->size[0] * jj)
                       - 1]) > 8.9884656743115785E+307) || (fabs(data->data
                       [((int)(flag_tc->data[b_ii] + 1.0) + data->size[0] * jj)
                       - 1]) > 8.9884656743115785E+307))) {
                  delta1 = data->data[((int)flag_tc->data[b_ii] + data->size[0] *
                                       jj) - 1] / ((double)data_temp->size[1] -
                    1.0);
                  delta2 = data->data[((int)(flag_tc->data[b_ii] + 1.0) +
                                       data->size[0] * jj) - 1] / ((double)
                    data_temp->size[1] - 1.0);
                  i0 = data_temp->size[1];
                  for (nx = 0; nx <= i0 - 3; nx++) {
                    data_temp->data[1 + nx] = (d1 + delta2 * (1.0 + (double)nx))
                      - delta1 * (1.0 + (double)nx);
                  }
                } else {
                  delta1 = (data->data[((int)(flag_tc->data[b_ii] + 1.0) +
                                        data->size[0] * jj) - 1] - data->data
                            [((int)flag_tc->data[b_ii] + data->size[0] * jj) - 1])
                    / ((double)data_temp->size[1] - 1.0);
                  i0 = data_temp->size[1];
                  for (nx = 0; nx <= i0 - 3; nx++) {
                    data_temp->data[1 + nx] = d1 + (1.0 + (double)nx) * delta1;
                  }
                }
              }
            }
          }
        }

        if (2 > data_temp->size[1] - 1) {
          i0 = 0;
          idx = 0;
        } else {
          i0 = 1;
          idx = data_temp->size[1] - 1;
        }

        if (kk > (kk + space) - 2.0) {
          i1 = 0;
        } else {
          i1 = (int)kk - 1;
        }

        nx = (idx - i0) - 1;
        for (idx = 0; idx <= nx; idx++) {
          data_out->data[(i1 + idx) + data_out->size[0] * jj] = data_temp->
            data[i0 + idx];
        }

        kk = (kk + space) - 1.0;
      }

      if (flag_tc->data[flag_tc->size[0] - 1] + 1.0 > data->size[0]) {
        i0 = 1;
        idx = 0;
      } else {
        i0 = (int)(flag_tc->data[flag_tc->size[0] - 1] + 1.0);
        idx = data->size[0];
      }

      if (kk > data_out->size[0]) {
        i1 = 0;
      } else {
        i1 = (int)kk - 1;
      }

      nx = idx - i0;
      for (idx = 0; idx <= nx; idx++) {
        data_out->data[(i1 + idx) + data_out->size[0] * jj] = data->data[((i0 +
          idx) + data->size[0] * jj) - 1];
      }

      jj++;
    }

    emxFree_real_T(&data_temp);
  } else {
    i0 = data_out->size[0] * data_out->size[1];
    data_out->size[0] = data->size[0];
    data_out->size[1] = data->size[1];
    emxEnsureCapacity((emxArray__common *)data_out, i0, (int)sizeof(double));
    nx = data->size[0] * data->size[1];
    for (i0 = 0; i0 < nx; i0++) {
      data_out->data[i0] = data->data[i0];
    }
  }

  emxFree_real_T(&flag_tc);
}

/*
 * File trailer for time_cont.c
 *
 * [EOF]
 */
