/*
 * File: range_check.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 09-May-2016 16:10:52
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "range_check.h"
#include "libs/commons/emxutil.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_real_T *data
 *                const emxArray_real_T *b_max
 *                const emxArray_real_T *b_min
 *                const emxArray_real_T *check_list
 *                double check
 * Return Type  : void
 */
void range_check(emxArray_real_T *data, const emxArray_real_T *b_max, const
                 emxArray_real_T *b_min, const emxArray_real_T *check_list,
                 double check)
{
  int jj;
  emxArray_real_T *data_fc;
  emxArray_real_T *flag_fc;
  emxArray_int32_T *r0;
  emxArray_real_T *r1;
  emxArray_boolean_T *x;
  emxArray_int32_T *ii;
  int nx;
  int i0;
  boolean_T guard1 = false;
  double ndbl;
  double c_max;
  int idx;
  int b_ii;
  boolean_T exitg2;
  boolean_T guard2 = false;
  boolean_T exitg1;
  boolean_T b_guard1 = false;
  double step;
  double anew;
  int n;
  double apnd;
  double cdiff;
  double absa;
  double absb;
  jj = 0;
  emxInit_real_T1(&data_fc, 1);
  emxInit_real_T1(&flag_fc, 1);
  emxInit_int32_T(&r0, 2);
  emxInit_real_T(&r1, 2);
  emxInit_boolean_T(&x, 1);
  emxInit_int32_T1(&ii, 1);
  while (jj <= check_list->size[1] - 1) {
    nx = data->size[0];
    i0 = data_fc->size[0];
    data_fc->size[0] = nx;
    emxEnsureCapacity((emxArray__common *)data_fc, i0, (int)sizeof(double));
    for (i0 = 0; i0 < nx; i0++) {
      data_fc->data[i0] = data->data[i0 + data->size[0] * jj];
    }

    guard1 = false;
    if (check == 1.0) {
      /* 错误数据执行标记 */
      ndbl = b_min->data[jj];
      c_max = b_max->data[jj];
      i0 = x->size[0];
      x->size[0] = data_fc->size[0];
      emxEnsureCapacity((emxArray__common *)x, i0, (int)sizeof(boolean_T));
      nx = data_fc->size[0];
      for (i0 = 0; i0 < nx; i0++) {
        x->data[i0] = ((data_fc->data[i0] < ndbl) || (data_fc->data[i0] > c_max));
      }

      nx = x->size[0];
      idx = 0;
      i0 = ii->size[0];
      ii->size[0] = x->size[0];
      emxEnsureCapacity((emxArray__common *)ii, i0, (int)sizeof(int));
      b_ii = 1;
      exitg2 = false;
      while ((!exitg2) && (b_ii <= nx)) {
        guard2 = false;
        if (x->data[b_ii - 1]) {
          idx++;
          ii->data[idx - 1] = b_ii;
          if (idx >= nx) {
            exitg2 = true;
          } else {
            guard2 = true;
          }
        } else {
          guard2 = true;
        }

        if (guard2) {
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

      i0 = flag_fc->size[0];
      flag_fc->size[0] = ii->size[0];
      emxEnsureCapacity((emxArray__common *)flag_fc, i0, (int)sizeof(double));
      nx = ii->size[0];
      for (i0 = 0; i0 < nx; i0++) {
        flag_fc->data[i0] = ii->data[i0];
      }

      /* 错误数据位置 */
      if (flag_fc->size[0] == 0) {
      } else {
        i0 = ii->size[0];
        ii->size[0] = flag_fc->size[0];
        emxEnsureCapacity((emxArray__common *)ii, i0, (int)sizeof(int));
        nx = flag_fc->size[0];
        for (i0 = 0; i0 < nx; i0++) {
          ii->data[i0] = (int)flag_fc->data[i0];
        }

        nx = ii->size[0];
        for (i0 = 0; i0 < nx; i0++) {
          data_fc->data[ii->data[i0] - 1] = -9.0;
        }

        /* 标记 */
        guard1 = true;
      }
    } else {
      /* 错误数据进行插值，线性插值 */
      ndbl = b_min->data[jj];
      c_max = b_max->data[jj];
      i0 = x->size[0];
      x->size[0] = data_fc->size[0];
      emxEnsureCapacity((emxArray__common *)x, i0, (int)sizeof(boolean_T));
      nx = data_fc->size[0];
      for (i0 = 0; i0 < nx; i0++) {
        x->data[i0] = ((data_fc->data[i0] > ndbl) && (data_fc->data[i0] < c_max));
      }

      nx = x->size[0];
      idx = 0;
      i0 = ii->size[0];
      ii->size[0] = x->size[0];
      emxEnsureCapacity((emxArray__common *)ii, i0, (int)sizeof(int));
      b_ii = 1;
      exitg1 = false;
      while ((!exitg1) && (b_ii <= nx)) {
        b_guard1 = false;
        if (x->data[b_ii - 1]) {
          idx++;
          ii->data[idx - 1] = b_ii;
          if (idx >= nx) {
            exitg1 = true;
          } else {
            b_guard1 = true;
          }
        } else {
          b_guard1 = true;
        }

        if (b_guard1) {
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

      i0 = flag_fc->size[0];
      flag_fc->size[0] = ii->size[0];
      emxEnsureCapacity((emxArray__common *)flag_fc, i0, (int)sizeof(double));
      nx = ii->size[0];
      for (i0 = 0; i0 < nx; i0++) {
        flag_fc->data[i0] = ii->data[i0];
      }

      /* 标记正确的值 */
      if (flag_fc->size[0] == 0) {
      } else {
        i0 = data->size[0];
        if (i0 > (int)flag_fc->data[flag_fc->size[0] - 1]) {
          nx = data->size[0];
          if (flag_fc->data[flag_fc->size[0] - 1] + 1.0 > nx) {
            i0 = 0;
            nx = 0;
          } else {
            i0 = (int)(flag_fc->data[flag_fc->size[0] - 1] + 1.0) - 1;
          }

          idx = r0->size[0] * r0->size[1];
          r0->size[0] = 1;
          r0->size[1] = nx - i0;
          emxEnsureCapacity((emxArray__common *)r0, idx, (int)sizeof(int));
          nx -= i0;
          for (idx = 0; idx < nx; idx++) {
            r0->data[r0->size[0] * idx] = i0 + idx;
          }

          nx = r0->size[0] * r0->size[1];
          for (i0 = 0; i0 < nx; i0++) {
            data_fc->data[r0->data[i0]] = data->data[((int)flag_fc->data
              [flag_fc->size[0] - 1] + data->size[0] * jj) - 1];
          }

          /* 不符合的数全部按照最后一个正确的数补齐 */
        }

        if (flag_fc->data[0] != 1.0) {
          if (1.0 > flag_fc->data[0] - 1.0) {
            nx = 0;
          } else {
            nx = (int)(flag_fc->data[0] - 1.0);
          }

          i0 = r0->size[0] * r0->size[1];
          r0->size[0] = 1;
          r0->size[1] = nx;
          emxEnsureCapacity((emxArray__common *)r0, i0, (int)sizeof(int));
          for (i0 = 0; i0 < nx; i0++) {
            r0->data[r0->size[0] * i0] = i0;
          }

          ndbl = data_fc->data[(int)flag_fc->data[0] - 1];
          nx = r0->size[0] * r0->size[1];
          for (i0 = 0; i0 < nx; i0++) {
            data_fc->data[r0->data[i0]] = ndbl;
          }

          /* 不符合的数全部按照最后一个正确的数补齐 */
        }

        for (b_ii = 0; b_ii <= flag_fc->size[0] - 2; b_ii++) {
          /* 遍历正确数据，查找错误数据 */
          if (flag_fc->data[1 + b_ii] - flag_fc->data[b_ii] != 1.0) {
            step = (data_fc->data[(int)flag_fc->data[1 + b_ii] - 1] -
                    data_fc->data[(int)flag_fc->data[b_ii] - 1]) /
              (flag_fc->data[1 + b_ii] - flag_fc->data[b_ii]);
            if (step == 0.0) {
              if (flag_fc->data[b_ii] + 1.0 > flag_fc->data[1 + b_ii] - 1.0) {
                i0 = 0;
                idx = 0;
              } else {
                i0 = (int)(flag_fc->data[b_ii] + 1.0) - 1;
                idx = (int)(flag_fc->data[1 + b_ii] - 1.0);
              }

              nx = r0->size[0] * r0->size[1];
              r0->size[0] = 1;
              r0->size[1] = idx - i0;
              emxEnsureCapacity((emxArray__common *)r0, nx, (int)sizeof(int));
              nx = idx - i0;
              for (idx = 0; idx < nx; idx++) {
                r0->data[r0->size[0] * idx] = i0 + idx;
              }

              ndbl = data_fc->data[(int)flag_fc->data[b_ii] - 1];
              nx = r0->size[0] * r0->size[1];
              for (i0 = 0; i0 < nx; i0++) {
                data_fc->data[r0->data[i0]] = ndbl;
              }
            } else {
              if (flag_fc->data[b_ii] + 1.0 > flag_fc->data[1 + b_ii] - 1.0) {
                i0 = 0;
              } else {
                i0 = (int)(flag_fc->data[b_ii] + 1.0) - 1;
              }

              anew = data_fc->data[(int)flag_fc->data[b_ii] - 1] + step;
              c_max = data_fc->data[(int)flag_fc->data[1 + b_ii] - 1] - step;
              if (rtIsNaN(anew) || rtIsNaN(step) || rtIsNaN(c_max)) {
                n = 1;
                anew = rtNaN;
                apnd = c_max;
              } else if ((step == 0.0) || ((anew < c_max) && (step < 0.0)) ||
                         ((c_max < anew) && (step > 0.0))) {
                n = 0;
                apnd = c_max;
              } else if (rtIsInf(anew) || rtIsInf(c_max)) {
                n = 1;
                anew = rtNaN;
                apnd = c_max;
              } else if (rtIsInf(step)) {
                n = 1;
                apnd = c_max;
              } else {
                ndbl = floor((c_max - anew) / step + 0.5);
                apnd = anew + ndbl * step;
                if (step > 0.0) {
                  cdiff = apnd - c_max;
                } else {
                  cdiff = c_max - apnd;
                }

                absa = fabs(anew);
                absb = fabs(c_max);
                if ((absa >= absb) || rtIsNaN(absb)) {
                  absb = absa;
                }

                if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
                  ndbl++;
                  apnd = c_max;
                } else if (cdiff > 0.0) {
                  apnd = anew + (ndbl - 1.0) * step;
                } else {
                  ndbl++;
                }

                if (ndbl >= 0.0) {
                  n = (int)ndbl;
                } else {
                  n = 0;
                }
              }

              idx = r1->size[0] * r1->size[1];
              r1->size[0] = 1;
              r1->size[1] = n;
              emxEnsureCapacity((emxArray__common *)r1, idx, (int)sizeof(double));
              if (n > 0) {
                r1->data[0] = anew;
                if (n > 1) {
                  r1->data[n - 1] = apnd;
                  idx = n - 1;
                  nx = idx / 2;
                  for (idx = 1; idx < nx; idx++) {
                    ndbl = (double)idx * step;
                    r1->data[idx] = anew + ndbl;
                    r1->data[(n - idx) - 1] = apnd - ndbl;
                  }

                  if (nx << 1 == n - 1) {
                    r1->data[nx] = (anew + apnd) / 2.0;
                  } else {
                    ndbl = (double)nx * step;
                    r1->data[nx] = anew + ndbl;
                    r1->data[nx + 1] = apnd - ndbl;
                  }
                }
              }

              nx = r1->size[1];
              for (idx = 0; idx < nx; idx++) {
                data_fc->data[i0 + idx] = r1->data[r1->size[0] * idx];
              }
            }
          }
        }

        guard1 = true;
      }
    }

    if (guard1) {
      nx = data_fc->size[0];
      for (i0 = 0; i0 < nx; i0++) {
        data->data[i0 + data->size[0] * jj] = data_fc->data[i0];
      }
    }

    jj++;
  }

  emxFree_int32_T(&ii);
  emxFree_boolean_T(&x);
  emxFree_real_T(&r1);
  emxFree_int32_T(&r0);
  emxFree_real_T(&flag_fc);
  emxFree_real_T(&data_fc);
}

/*
 * File trailer for range_check.c
 *
 * [EOF]
 */
