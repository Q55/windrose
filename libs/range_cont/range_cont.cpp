/*
 * File: range_cont.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 13-May-2016 16:13:46
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "range_cont.h"
#include "libs/commons/emxutil.h"

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
 * gsd表示各个变量的总体方差
 * Arguments    : emxArray_real_T *data
 *                const emxArray_real_T *gsd
 *                double time_step
 *                const emxArray_real_T *check_list
 *                double check
 * Return Type  : void
 */
void range_cont(emxArray_real_T *data, const emxArray_real_T *gsd, double
                time_step, const emxArray_real_T *check_list, double check)
{
  double time_step_hour;
  double data_num;
  emxArray_real_T *std_t3;
  emxArray_real_T *pre_check;
  emxArray_real_T *limit_up;
  emxArray_real_T *limit_down;
  emxArray_boolean_T *x;
  emxArray_int32_T *ii;
  int i0;
  int loop_ub;
  int b_ii;
  int jj;
  double kk;
  int b_kk;
  double ndbl;
  int i1;
  int i2;
  int nm1d2;
  int nx;
  int idx;
  boolean_T exitg6;
  boolean_T guard6 = false;
  double b;
  boolean_T exitg5;
  boolean_T guard5 = false;
  int k;
  boolean_T exitg4;
  boolean_T guard4 = false;
  emxArray_int32_T *r0;
  emxArray_real_T *r1;
  boolean_T exitg3;
  boolean_T guard3 = false;
  double step;
  double anew;
  double apnd;
  double cdiff;
  double absa;
  double absb;
  boolean_T exitg2;
  boolean_T guard2 = false;
  boolean_T exitg1;
  boolean_T guard1 = false;
  time_step_hour = time_step * 24.0;

  /* 单位：秒，换算为小时单位步长 */
  data_num = rt_roundd_snf(1.0 / time_step);

  /* 每次取数据的数量，一天数据量 */
  emxInit_real_T(&std_t3, 1);
  emxInit_real_T(&pre_check, 1);
  emxInit_real_T(&limit_up, 1);
  emxInit_real_T(&limit_down, 1);
  emxInit_boolean_T(&x, 1);
  emxInit_int32_T1(&ii, 1);
  if (check == 1.0) {
    /* 标记 */
    i0 = std_t3->size[0];
    std_t3->size[0] = (int)data_num;
    emxEnsureCapacity((emxArray__common *)std_t3, i0, (int)sizeof(double));
    loop_ub = (int)data_num;
    for (i0 = 0; i0 < loop_ub; i0++) {
      std_t3->data[i0] = 0.0;
    }

    for (b_ii = 0; b_ii < check_list->size[0]; b_ii++) {
      for (jj = 0; jj < (int)data_num; jj++) {
        /* 计算极限范围 */
        std_t3->data[jj] = 1.7399999999999998 * gsd->data[b_ii] * sqrt
          (time_step_hour * (1.0 + (double)jj));
      }

      i0 = data->size[0];
      if (i0 > data_num) {
        /* 处理长数据 */
        i0 = data->size[0];
        i0 = (int)(((double)i0 + (data_num - data_num)) / data_num);
        kk = data_num;
        for (b_kk = 0; b_kk < i0; b_kk++) {
          kk = data_num + (double)b_kk * data_num;
          ndbl = data->data[(int)((kk - data_num) + 1.0) - 1];
          i1 = limit_up->size[0];
          limit_up->size[0] = std_t3->size[0];
          emxEnsureCapacity((emxArray__common *)limit_up, i1, (int)sizeof(double));
          loop_ub = std_t3->size[0];
          for (i1 = 0; i1 < loop_ub; i1++) {
            limit_up->data[i1] = ndbl + std_t3->data[i1];
          }

          ndbl = data->data[(int)((kk - data_num) + 1.0) - 1];
          i1 = limit_down->size[0];
          limit_down->size[0] = std_t3->size[0];
          emxEnsureCapacity((emxArray__common *)limit_down, i1, (int)sizeof
                            (double));
          loop_ub = std_t3->size[0];
          for (i1 = 0; i1 < loop_ub; i1++) {
            limit_down->data[i1] = ndbl - std_t3->data[i1];
          }

          ndbl = (kk - data_num) + 1.0;
          if (ndbl > kk) {
            i1 = 0;
            i2 = 0;
          } else {
            i1 = (int)ndbl - 1;
            i2 = (int)kk;
          }

          nm1d2 = pre_check->size[0];
          pre_check->size[0] = i2 - i1;
          emxEnsureCapacity((emxArray__common *)pre_check, nm1d2, (int)sizeof
                            (double));
          loop_ub = i2 - i1;
          for (i2 = 0; i2 < loop_ub; i2++) {
            pre_check->data[i2] = data->data[i1 + i2];
          }

          i1 = x->size[0];
          x->size[0] = pre_check->size[0];
          emxEnsureCapacity((emxArray__common *)x, i1, (int)sizeof(boolean_T));
          loop_ub = pre_check->size[0];
          for (i1 = 0; i1 < loop_ub; i1++) {
            x->data[i1] = ((pre_check->data[i1] - limit_up->data[i1] > 0.0) ||
                           (pre_check->data[i1] - limit_down->data[i1] < 0.0));
          }

          nx = x->size[0];
          idx = 0;
          i1 = ii->size[0];
          ii->size[0] = x->size[0];
          emxEnsureCapacity((emxArray__common *)ii, i1, (int)sizeof(int));
          nm1d2 = 1;
          exitg6 = false;
          while ((!exitg6) && (nm1d2 <= nx)) {
            guard6 = false;
            if (x->data[nm1d2 - 1]) {
              idx++;
              ii->data[idx - 1] = nm1d2;
              if (idx >= nx) {
                exitg6 = true;
              } else {
                guard6 = true;
              }
            } else {
              guard6 = true;
            }

            if (guard6) {
              nm1d2++;
            }
          }

          if (x->size[0] == 1) {
            if (idx == 0) {
              i1 = ii->size[0];
              ii->size[0] = 0;
              emxEnsureCapacity((emxArray__common *)ii, i1, (int)sizeof(int));
            }
          } else {
            i1 = ii->size[0];
            if (1 > idx) {
              ii->size[0] = 0;
            } else {
              ii->size[0] = idx;
            }

            emxEnsureCapacity((emxArray__common *)ii, i1, (int)sizeof(int));
          }

          loop_ub = ii->size[0];
          for (i1 = 0; i1 < loop_ub; i1++) {
            pre_check->data[ii->data[i1] - 1] = -99.0;
          }

          ndbl = (kk - data_num) + 1.0;
          if (ndbl > kk) {
            i1 = 0;
          } else {
            i1 = (int)ndbl - 1;
          }

          loop_ub = pre_check->size[0];
          for (i2 = 0; i2 < loop_ub; i2++) {
            data->data[i1 + i2] = pre_check->data[i2];
          }
        }

        i0 = data->size[0];
        if ((double)i0 - kk == 0.0) {
        } else {
          if (kk + 1.0 > data->size[0]) {
            i0 = 0;
            i1 = 0;
          } else {
            i0 = (int)(kk + 1.0) - 1;
            i1 = data->size[0];
          }

          i2 = limit_down->size[0];
          limit_down->size[0] = i1 - i0;
          emxEnsureCapacity((emxArray__common *)limit_down, i2, (int)sizeof
                            (double));
          loop_ub = i1 - i0;
          for (i1 = 0; i1 < loop_ub; i1++) {
            limit_down->data[i1] = data->data[i0 + i1];
          }

          ndbl = data->data[(int)(kk + 1.0) - 1];
          b = data->data[(int)(kk + 1.0) - 1];
          i0 = x->size[0];
          x->size[0] = limit_down->size[0];
          emxEnsureCapacity((emxArray__common *)x, i0, (int)sizeof(boolean_T));
          loop_ub = limit_down->size[0];
          for (i0 = 0; i0 < loop_ub; i0++) {
            x->data[i0] = ((limit_down->data[i0] - (ndbl + std_t3->data[i0]) >
                            0.0) || (limit_down->data[i0] - (b - std_t3->data[i0])
              < 0.0));
          }

          nx = x->size[0];
          idx = 0;
          i0 = ii->size[0];
          ii->size[0] = x->size[0];
          emxEnsureCapacity((emxArray__common *)ii, i0, (int)sizeof(int));
          nm1d2 = 1;
          exitg5 = false;
          while ((!exitg5) && (nm1d2 <= nx)) {
            guard5 = false;
            if (x->data[nm1d2 - 1]) {
              idx++;
              ii->data[idx - 1] = nm1d2;
              if (idx >= nx) {
                exitg5 = true;
              } else {
                guard5 = true;
              }
            } else {
              guard5 = true;
            }

            if (guard5) {
              nm1d2++;
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

          loop_ub = ii->size[0];
          for (i0 = 0; i0 < loop_ub; i0++) {
            limit_down->data[ii->data[i0] - 1] = -99.0;
          }

          k = data->size[0];
          if (kk + 1.0 > k) {
            i0 = 0;
          } else {
            i0 = (int)(kk + 1.0) - 1;
          }

          loop_ub = limit_down->size[0];
          for (i1 = 0; i1 < loop_ub; i1++) {
            data->data[i0 + i1] = limit_down->data[i1];
          }
        }
      } else {
        /* 处理短数据 */
        ndbl = data->data[0];
        i0 = limit_up->size[0];
        limit_up->size[0] = std_t3->size[0];
        emxEnsureCapacity((emxArray__common *)limit_up, i0, (int)sizeof(double));
        loop_ub = std_t3->size[0];
        for (i0 = 0; i0 < loop_ub; i0++) {
          limit_up->data[i0] = ndbl + std_t3->data[i0];
        }

        ndbl = data->data[0];
        i0 = limit_down->size[0];
        limit_down->size[0] = std_t3->size[0];
        emxEnsureCapacity((emxArray__common *)limit_down, i0, (int)sizeof(double));
        loop_ub = std_t3->size[0];
        for (i0 = 0; i0 < loop_ub; i0++) {
          limit_down->data[i0] = ndbl - std_t3->data[i0];
        }

        k = data->size[0];
        if (1 > k) {
          loop_ub = 0;
        } else {
          loop_ub = k;
        }

        i0 = pre_check->size[0];
        pre_check->size[0] = loop_ub;
        emxEnsureCapacity((emxArray__common *)pre_check, i0, (int)sizeof(double));
        for (i0 = 0; i0 < loop_ub; i0++) {
          pre_check->data[i0] = data->data[i0];
        }

        i0 = x->size[0];
        x->size[0] = pre_check->size[0];
        emxEnsureCapacity((emxArray__common *)x, i0, (int)sizeof(boolean_T));
        loop_ub = pre_check->size[0];
        for (i0 = 0; i0 < loop_ub; i0++) {
          x->data[i0] = ((pre_check->data[i0] - limit_up->data[i0] > 0.0) ||
                         (pre_check->data[i0] - limit_down->data[i0] < 0.0));
        }

        nx = x->size[0];
        idx = 0;
        i0 = ii->size[0];
        ii->size[0] = x->size[0];
        emxEnsureCapacity((emxArray__common *)ii, i0, (int)sizeof(int));
        nm1d2 = 1;
        exitg4 = false;
        while ((!exitg4) && (nm1d2 <= nx)) {
          guard4 = false;
          if (x->data[nm1d2 - 1]) {
            idx++;
            ii->data[idx - 1] = nm1d2;
            if (idx >= nx) {
              exitg4 = true;
            } else {
              guard4 = true;
            }
          } else {
            guard4 = true;
          }

          if (guard4) {
            nm1d2++;
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

        loop_ub = ii->size[0];
        for (i0 = 0; i0 < loop_ub; i0++) {
          pre_check->data[ii->data[i0] - 1] = -99.0;
        }

        loop_ub = pre_check->size[0];
        for (i0 = 0; i0 < loop_ub; i0++) {
          data->data[i0] = pre_check->data[i0];
        }
      }
    }
  } else {
    /* 自动补位 */
    b_ii = 0;
    emxInit_int32_T(&r0, 2);
    emxInit_real_T1(&r1, 2);
    while (b_ii <= check_list->size[0] - 1) {
      i0 = std_t3->size[0];
      std_t3->size[0] = (int)data_num;
      emxEnsureCapacity((emxArray__common *)std_t3, i0, (int)sizeof(double));
      loop_ub = (int)data_num;
      for (i0 = 0; i0 < loop_ub; i0++) {
        std_t3->data[i0] = 0.0;
      }

      for (jj = 0; jj < (int)data_num; jj++) {
        std_t3->data[jj] = 1.7399999999999998 * gsd->data[b_ii] * sqrt
          (time_step_hour * (1.0 + (double)jj));
      }

      i0 = data->size[0];
      if (i0 > data_num) {
        /* 处理长数据 */
        i0 = data->size[0];
        i0 = (int)(((double)i0 + (data_num - data_num)) / data_num);
        kk = data_num;
        for (b_kk = 0; b_kk < i0; b_kk++) {
          kk = data_num + (double)b_kk * data_num;
          ndbl = data->data[(int)((kk - data_num) + 1.0) - 1];
          i1 = limit_up->size[0];
          limit_up->size[0] = std_t3->size[0];
          emxEnsureCapacity((emxArray__common *)limit_up, i1, (int)sizeof(double));
          loop_ub = std_t3->size[0];
          for (i1 = 0; i1 < loop_ub; i1++) {
            limit_up->data[i1] = ndbl + std_t3->data[i1];
          }

          ndbl = data->data[(int)((kk - data_num) + 1.0) - 1];
          i1 = limit_down->size[0];
          limit_down->size[0] = std_t3->size[0];
          emxEnsureCapacity((emxArray__common *)limit_down, i1, (int)sizeof
                            (double));
          loop_ub = std_t3->size[0];
          for (i1 = 0; i1 < loop_ub; i1++) {
            limit_down->data[i1] = ndbl - std_t3->data[i1];
          }

          ndbl = (kk - data_num) + 1.0;
          if (ndbl > kk) {
            i1 = 0;
            i2 = 0;
          } else {
            i1 = (int)ndbl - 1;
            i2 = (int)kk;
          }

          nm1d2 = pre_check->size[0];
          pre_check->size[0] = i2 - i1;
          emxEnsureCapacity((emxArray__common *)pre_check, nm1d2, (int)sizeof
                            (double));
          loop_ub = i2 - i1;
          for (nm1d2 = 0; nm1d2 < loop_ub; nm1d2++) {
            pre_check->data[nm1d2] = data->data[i1 + nm1d2];
          }

          nm1d2 = x->size[0];
          x->size[0] = pre_check->size[0];
          emxEnsureCapacity((emxArray__common *)x, nm1d2, (int)sizeof(boolean_T));
          loop_ub = pre_check->size[0];
          for (nm1d2 = 0; nm1d2 < loop_ub; nm1d2++) {
            x->data[nm1d2] = ((pre_check->data[nm1d2] - limit_up->data[nm1d2] <
                               0.0) && (pre_check->data[nm1d2] -
              limit_down->data[nm1d2] > 0.0));
          }

          nx = x->size[0];
          idx = 0;
          nm1d2 = ii->size[0];
          ii->size[0] = x->size[0];
          emxEnsureCapacity((emxArray__common *)ii, nm1d2, (int)sizeof(int));
          nm1d2 = 1;
          exitg3 = false;
          while ((!exitg3) && (nm1d2 <= nx)) {
            guard3 = false;
            if (x->data[nm1d2 - 1]) {
              idx++;
              ii->data[idx - 1] = nm1d2;
              if (idx >= nx) {
                exitg3 = true;
              } else {
                guard3 = true;
              }
            } else {
              guard3 = true;
            }

            if (guard3) {
              nm1d2++;
            }
          }

          if (x->size[0] == 1) {
            if (idx == 0) {
              nm1d2 = ii->size[0];
              ii->size[0] = 0;
              emxEnsureCapacity((emxArray__common *)ii, nm1d2, (int)sizeof(int));
            }
          } else {
            nm1d2 = ii->size[0];
            if (1 > idx) {
              ii->size[0] = 0;
            } else {
              ii->size[0] = idx;
            }

            emxEnsureCapacity((emxArray__common *)ii, nm1d2, (int)sizeof(int));
          }

          nm1d2 = limit_up->size[0];
          limit_up->size[0] = ii->size[0];
          emxEnsureCapacity((emxArray__common *)limit_up, nm1d2, (int)sizeof
                            (double));
          loop_ub = ii->size[0];
          for (nm1d2 = 0; nm1d2 < loop_ub; nm1d2++) {
            limit_up->data[nm1d2] = ii->data[nm1d2];
          }

          if (!(limit_up->size[0] == 0)) {
            if (i2 - i1 > (int)limit_up->data[limit_up->size[0] - 1]) {
              k = i2 - i1;
              if (limit_up->data[limit_up->size[0] - 1] + 1.0 > k) {
                i2 = 0;
                k = 0;
              } else {
                i2 = (int)(limit_up->data[limit_up->size[0] - 1] + 1.0) - 1;
              }

              nm1d2 = r0->size[0] * r0->size[1];
              r0->size[0] = 1;
              r0->size[1] = k - i2;
              emxEnsureCapacity((emxArray__common *)r0, nm1d2, (int)sizeof(int));
              loop_ub = k - i2;
              for (nm1d2 = 0; nm1d2 < loop_ub; nm1d2++) {
                r0->data[r0->size[0] * nm1d2] = i2 + nm1d2;
              }

              loop_ub = r0->size[0] * r0->size[1];
              for (i2 = 0; i2 < loop_ub; i2++) {
                pre_check->data[r0->data[i2]] = data->data[(i1 + (int)
                  limit_up->data[limit_up->size[0] - 1]) - 1];
              }

              /* 不符合的数全部按照最后一个正确的数补齐 */
            }

            for (jj = 0; jj <= limit_up->size[0] - 2; jj++) {
              if (limit_up->data[1 + jj] - limit_up->data[jj] != 1.0) {
                step = (pre_check->data[(int)limit_up->data[1 + jj] - 1] -
                        pre_check->data[(int)limit_up->data[jj] - 1]) /
                  (limit_up->data[1 + jj] - limit_up->data[jj]);
                if (step == 0.0) {
                  if (limit_up->data[jj] + 1.0 > limit_up->data[1 + jj] - 1.0) {
                    i1 = 0;
                    i2 = 0;
                  } else {
                    i1 = (int)(limit_up->data[jj] + 1.0) - 1;
                    i2 = (int)(limit_up->data[1 + jj] - 1.0);
                  }

                  nm1d2 = r0->size[0] * r0->size[1];
                  r0->size[0] = 1;
                  r0->size[1] = i2 - i1;
                  emxEnsureCapacity((emxArray__common *)r0, nm1d2, (int)sizeof
                                    (int));
                  loop_ub = i2 - i1;
                  for (i2 = 0; i2 < loop_ub; i2++) {
                    r0->data[r0->size[0] * i2] = i1 + i2;
                  }

                  ndbl = pre_check->data[(int)limit_up->data[jj] - 1];
                  loop_ub = r0->size[0] * r0->size[1];
                  for (i1 = 0; i1 < loop_ub; i1++) {
                    pre_check->data[r0->data[i1]] = ndbl;
                  }
                } else {
                  if (limit_up->data[jj] + 1.0 > limit_up->data[1 + jj] - 1.0) {
                    i1 = 0;
                  } else {
                    i1 = (int)(limit_up->data[jj] + 1.0) - 1;
                  }

                  anew = pre_check->data[(int)limit_up->data[jj] - 1] + step;
                  b = pre_check->data[(int)limit_up->data[1 + jj] - 1] - step;
                  if (rtIsNaN(anew) || rtIsNaN(step) || rtIsNaN(b)) {
                    nx = 1;
                    anew = rtNaN;
                    apnd = b;
                  } else if ((step == 0.0) || ((anew < b) && (step < 0.0)) ||
                             ((b < anew) && (step > 0.0))) {
                    nx = 0;
                    apnd = b;
                  } else if (rtIsInf(anew) || rtIsInf(b)) {
                    nx = 1;
                    anew = rtNaN;
                    apnd = b;
                  } else if (rtIsInf(step)) {
                    nx = 1;
                    apnd = b;
                  } else {
                    ndbl = floor((b - anew) / step + 0.5);
                    apnd = anew + ndbl * step;
                    if (step > 0.0) {
                      cdiff = apnd - b;
                    } else {
                      cdiff = b - apnd;
                    }

                    absa = fabs(anew);
                    absb = fabs(b);
                    if ((absa >= absb) || rtIsNaN(absb)) {
                      absb = absa;
                    }

                    if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
                      ndbl++;
                      apnd = b;
                    } else if (cdiff > 0.0) {
                      apnd = anew + (ndbl - 1.0) * step;
                    } else {
                      ndbl++;
                    }

                    if (ndbl >= 0.0) {
                      nx = (int)ndbl;
                    } else {
                      nx = 0;
                    }
                  }

                  i2 = r1->size[0] * r1->size[1];
                  r1->size[0] = 1;
                  r1->size[1] = nx;
                  emxEnsureCapacity((emxArray__common *)r1, i2, (int)sizeof
                                    (double));
                  if (nx > 0) {
                    r1->data[0] = anew;
                    if (nx > 1) {
                      r1->data[nx - 1] = apnd;
                      i2 = nx - 1;
                      nm1d2 = i2 / 2;
                      for (k = 1; k < nm1d2; k++) {
                        ndbl = (double)k * step;
                        r1->data[k] = anew + ndbl;
                        r1->data[(nx - k) - 1] = apnd - ndbl;
                      }

                      if (nm1d2 << 1 == nx - 1) {
                        r1->data[nm1d2] = (anew + apnd) / 2.0;
                      } else {
                        ndbl = (double)nm1d2 * step;
                        r1->data[nm1d2] = anew + ndbl;
                        r1->data[nm1d2 + 1] = apnd - ndbl;
                      }
                    }
                  }

                  loop_ub = r1->size[1];
                  for (i2 = 0; i2 < loop_ub; i2++) {
                    pre_check->data[i1 + i2] = r1->data[r1->size[0] * i2];
                  }
                }
              }
            }
          }

          ndbl = (kk - data_num) + 1.0;
          if (ndbl > kk) {
            i1 = 0;
          } else {
            i1 = (int)ndbl - 1;
          }

          loop_ub = pre_check->size[0];
          for (i2 = 0; i2 < loop_ub; i2++) {
            data->data[i1 + i2] = pre_check->data[i2];
          }
        }

        i0 = data->size[0];
        if ((double)i0 - kk == 0.0) {
        } else {
          k = data->size[0];
          if (kk + 1.0 > k) {
            i0 = 0;
            k = 0;
          } else {
            i0 = (int)(kk + 1.0) - 1;
          }

          i1 = limit_down->size[0];
          limit_down->size[0] = k - i0;
          emxEnsureCapacity((emxArray__common *)limit_down, i1, (int)sizeof
                            (double));
          loop_ub = k - i0;
          for (i1 = 0; i1 < loop_ub; i1++) {
            limit_down->data[i1] = data->data[i0 + i1];
          }

          ndbl = data->data[(int)(kk + 1.0) - 1];
          b = data->data[(int)(kk + 1.0) - 1];
          i1 = x->size[0];
          x->size[0] = limit_down->size[0];
          emxEnsureCapacity((emxArray__common *)x, i1, (int)sizeof(boolean_T));
          loop_ub = limit_down->size[0];
          for (i1 = 0; i1 < loop_ub; i1++) {
            x->data[i1] = ((limit_down->data[i1] - (ndbl + std_t3->data[i1]) <
                            0.0) && (limit_down->data[i1] - (b - std_t3->data[i1])
              > 0.0));
          }

          nx = x->size[0];
          idx = 0;
          i1 = ii->size[0];
          ii->size[0] = x->size[0];
          emxEnsureCapacity((emxArray__common *)ii, i1, (int)sizeof(int));
          nm1d2 = 1;
          exitg2 = false;
          while ((!exitg2) && (nm1d2 <= nx)) {
            guard2 = false;
            if (x->data[nm1d2 - 1]) {
              idx++;
              ii->data[idx - 1] = nm1d2;
              if (idx >= nx) {
                exitg2 = true;
              } else {
                guard2 = true;
              }
            } else {
              guard2 = true;
            }

            if (guard2) {
              nm1d2++;
            }
          }

          if (x->size[0] == 1) {
            if (idx == 0) {
              i1 = ii->size[0];
              ii->size[0] = 0;
              emxEnsureCapacity((emxArray__common *)ii, i1, (int)sizeof(int));
            }
          } else {
            i1 = ii->size[0];
            if (1 > idx) {
              ii->size[0] = 0;
            } else {
              ii->size[0] = idx;
            }

            emxEnsureCapacity((emxArray__common *)ii, i1, (int)sizeof(int));
          }

          i1 = limit_up->size[0];
          limit_up->size[0] = ii->size[0];
          emxEnsureCapacity((emxArray__common *)limit_up, i1, (int)sizeof(double));
          loop_ub = ii->size[0];
          for (i1 = 0; i1 < loop_ub; i1++) {
            limit_up->data[i1] = ii->data[i1];
          }

          if (!(limit_up->size[0] == 0)) {
            if (k - i0 > (int)limit_up->data[limit_up->size[0] - 1]) {
              k -= i0;
              if (limit_up->data[limit_up->size[0] - 1] + 1.0 > k) {
                i1 = 0;
                k = 0;
              } else {
                i1 = (int)(limit_up->data[limit_up->size[0] - 1] + 1.0) - 1;
              }

              i2 = r0->size[0] * r0->size[1];
              r0->size[0] = 1;
              r0->size[1] = k - i1;
              emxEnsureCapacity((emxArray__common *)r0, i2, (int)sizeof(int));
              loop_ub = k - i1;
              for (i2 = 0; i2 < loop_ub; i2++) {
                r0->data[r0->size[0] * i2] = i1 + i2;
              }

              loop_ub = r0->size[0] * r0->size[1];
              for (i1 = 0; i1 < loop_ub; i1++) {
                limit_down->data[r0->data[i1]] = data->data[(i0 + (int)
                  limit_up->data[limit_up->size[0] - 1]) - 1];
              }

              /* 不符合的数全部按照最后一个正确的数补齐 */
            }

            for (jj = 0; jj <= limit_up->size[0] - 2; jj++) {
              if (limit_up->data[1 + jj] - limit_up->data[jj] != 1.0) {
                step = (limit_up->data[(int)limit_up->data[1 + jj] - 1] -
                        limit_up->data[(int)limit_up->data[jj] - 1]) /
                  (limit_up->data[1 + jj] - limit_up->data[jj]);
                if (step == 0.0) {
                  if (limit_up->data[jj] + 1.0 > limit_up->data[1 + jj] - 1.0) {
                    i0 = 0;
                    i1 = 0;
                  } else {
                    i0 = (int)(limit_up->data[jj] + 1.0) - 1;
                    i1 = (int)(limit_up->data[1 + jj] - 1.0);
                  }

                  i2 = r0->size[0] * r0->size[1];
                  r0->size[0] = 1;
                  r0->size[1] = i1 - i0;
                  emxEnsureCapacity((emxArray__common *)r0, i2, (int)sizeof(int));
                  loop_ub = i1 - i0;
                  for (i1 = 0; i1 < loop_ub; i1++) {
                    r0->data[r0->size[0] * i1] = i0 + i1;
                  }

                  ndbl = limit_down->data[(int)limit_up->data[jj] - 1];
                  loop_ub = r0->size[0] * r0->size[1];
                  for (i0 = 0; i0 < loop_ub; i0++) {
                    limit_down->data[r0->data[i0]] = ndbl;
                  }
                } else {
                  if (limit_up->data[jj] + 1.0 > limit_up->data[1 + jj] - 1.0) {
                    i0 = 0;
                  } else {
                    i0 = (int)(limit_up->data[jj] + 1.0) - 1;
                  }

                  anew = limit_down->data[(int)limit_up->data[jj] - 1] + step;
                  b = limit_down->data[(int)limit_up->data[1 + jj] - 1] - step;
                  if (rtIsNaN(anew) || rtIsNaN(step) || rtIsNaN(b)) {
                    nx = 1;
                    anew = rtNaN;
                    apnd = b;
                  } else if ((step == 0.0) || ((anew < b) && (step < 0.0)) ||
                             ((b < anew) && (step > 0.0))) {
                    nx = 0;
                    apnd = b;
                  } else if (rtIsInf(anew) || rtIsInf(b)) {
                    nx = 1;
                    anew = rtNaN;
                    apnd = b;
                  } else if (rtIsInf(step)) {
                    nx = 1;
                    apnd = b;
                  } else {
                    ndbl = floor((b - anew) / step + 0.5);
                    apnd = anew + ndbl * step;
                    if (step > 0.0) {
                      cdiff = apnd - b;
                    } else {
                      cdiff = b - apnd;
                    }

                    absa = fabs(anew);
                    absb = fabs(b);
                    if ((absa >= absb) || rtIsNaN(absb)) {
                      absb = absa;
                    }

                    if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
                      ndbl++;
                      apnd = b;
                    } else if (cdiff > 0.0) {
                      apnd = anew + (ndbl - 1.0) * step;
                    } else {
                      ndbl++;
                    }

                    if (ndbl >= 0.0) {
                      nx = (int)ndbl;
                    } else {
                      nx = 0;
                    }
                  }

                  i1 = r1->size[0] * r1->size[1];
                  r1->size[0] = 1;
                  r1->size[1] = nx;
                  emxEnsureCapacity((emxArray__common *)r1, i1, (int)sizeof
                                    (double));
                  if (nx > 0) {
                    r1->data[0] = anew;
                    if (nx > 1) {
                      r1->data[nx - 1] = apnd;
                      i1 = nx - 1;
                      nm1d2 = i1 / 2;
                      for (k = 1; k < nm1d2; k++) {
                        ndbl = (double)k * step;
                        r1->data[k] = anew + ndbl;
                        r1->data[(nx - k) - 1] = apnd - ndbl;
                      }

                      if (nm1d2 << 1 == nx - 1) {
                        r1->data[nm1d2] = (anew + apnd) / 2.0;
                      } else {
                        ndbl = (double)nm1d2 * step;
                        r1->data[nm1d2] = anew + ndbl;
                        r1->data[nm1d2 + 1] = apnd - ndbl;
                      }
                    }
                  }

                  loop_ub = r1->size[1];
                  for (i1 = 0; i1 < loop_ub; i1++) {
                    limit_down->data[i0 + i1] = r1->data[r1->size[0] * i1];
                  }
                }
              }
            }
          }

          k = data->size[0];
          if (kk + 1.0 > k) {
            i0 = 0;
          } else {
            i0 = (int)(kk + 1.0) - 1;
          }

          loop_ub = limit_down->size[0];
          for (i1 = 0; i1 < loop_ub; i1++) {
            data->data[i0 + i1] = limit_down->data[i1];
          }
        }
      } else {
        /* 处理短数据 */
        ndbl = data->data[0];
        i0 = limit_up->size[0];
        limit_up->size[0] = std_t3->size[0];
        emxEnsureCapacity((emxArray__common *)limit_up, i0, (int)sizeof(double));
        loop_ub = std_t3->size[0];
        for (i0 = 0; i0 < loop_ub; i0++) {
          limit_up->data[i0] = ndbl + std_t3->data[i0];
        }

        ndbl = data->data[0];
        i0 = limit_down->size[0];
        limit_down->size[0] = std_t3->size[0];
        emxEnsureCapacity((emxArray__common *)limit_down, i0, (int)sizeof(double));
        loop_ub = std_t3->size[0];
        for (i0 = 0; i0 < loop_ub; i0++) {
          limit_down->data[i0] = ndbl - std_t3->data[i0];
        }

        k = data->size[0];
        if (1 > k) {
          loop_ub = 0;
        } else {
          loop_ub = k;
        }

        i0 = pre_check->size[0];
        pre_check->size[0] = loop_ub;
        emxEnsureCapacity((emxArray__common *)pre_check, i0, (int)sizeof(double));
        for (i0 = 0; i0 < loop_ub; i0++) {
          pre_check->data[i0] = data->data[i0];
        }

        i0 = x->size[0];
        x->size[0] = pre_check->size[0];
        emxEnsureCapacity((emxArray__common *)x, i0, (int)sizeof(boolean_T));
        nm1d2 = pre_check->size[0];
        for (i0 = 0; i0 < nm1d2; i0++) {
          x->data[i0] = ((pre_check->data[i0] - limit_up->data[i0] < 0.0) &&
                         (pre_check->data[i0] - limit_down->data[i0] > 0.0));
        }

        nx = x->size[0];
        idx = 0;
        i0 = ii->size[0];
        ii->size[0] = x->size[0];
        emxEnsureCapacity((emxArray__common *)ii, i0, (int)sizeof(int));
        nm1d2 = 1;
        exitg1 = false;
        while ((!exitg1) && (nm1d2 <= nx)) {
          guard1 = false;
          if (x->data[nm1d2 - 1]) {
            idx++;
            ii->data[idx - 1] = nm1d2;
            if (idx >= nx) {
              exitg1 = true;
            } else {
              guard1 = true;
            }
          } else {
            guard1 = true;
          }

          if (guard1) {
            nm1d2++;
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

        i0 = limit_up->size[0];
        limit_up->size[0] = ii->size[0];
        emxEnsureCapacity((emxArray__common *)limit_up, i0, (int)sizeof(double));
        nm1d2 = ii->size[0];
        for (i0 = 0; i0 < nm1d2; i0++) {
          limit_up->data[i0] = ii->data[i0];
        }

        if (!(limit_up->size[0] == 0)) {
          if (loop_ub > (int)limit_up->data[limit_up->size[0] - 1]) {
            if (limit_up->data[limit_up->size[0] - 1] + 1.0 > loop_ub) {
              i0 = 0;
              loop_ub = 0;
            } else {
              i0 = (int)(limit_up->data[limit_up->size[0] - 1] + 1.0) - 1;
            }

            i1 = r0->size[0] * r0->size[1];
            r0->size[0] = 1;
            r0->size[1] = loop_ub - i0;
            emxEnsureCapacity((emxArray__common *)r0, i1, (int)sizeof(int));
            loop_ub -= i0;
            for (i1 = 0; i1 < loop_ub; i1++) {
              r0->data[r0->size[0] * i1] = i0 + i1;
            }

            loop_ub = r0->size[0] * r0->size[1];
            for (i0 = 0; i0 < loop_ub; i0++) {
              pre_check->data[r0->data[i0]] = data->data[(int)limit_up->
                data[limit_up->size[0] - 1] - 1];
            }

            /* 不符合的数全部按照最后一个正确的数补齐 */
          }

          for (jj = 0; jj <= limit_up->size[0] - 2; jj++) {
            if (limit_up->data[1 + jj] - limit_up->data[jj] != 1.0) {
              step = (pre_check->data[(int)limit_up->data[1 + jj] - 1] -
                      pre_check->data[(int)limit_up->data[jj] - 1]) /
                (limit_up->data[1 + jj] - limit_up->data[jj]);
              if (step == 0.0) {
                if (limit_up->data[jj] + 1.0 > limit_up->data[1 + jj] - 1.0) {
                  i0 = 0;
                  i1 = 0;
                } else {
                  i0 = (int)(limit_up->data[jj] + 1.0) - 1;
                  i1 = (int)(limit_up->data[1 + jj] - 1.0);
                }

                i2 = r0->size[0] * r0->size[1];
                r0->size[0] = 1;
                r0->size[1] = i1 - i0;
                emxEnsureCapacity((emxArray__common *)r0, i2, (int)sizeof(int));
                loop_ub = i1 - i0;
                for (i1 = 0; i1 < loop_ub; i1++) {
                  r0->data[r0->size[0] * i1] = i0 + i1;
                }

                ndbl = pre_check->data[(int)limit_up->data[jj] - 1];
                loop_ub = r0->size[0] * r0->size[1];
                for (i0 = 0; i0 < loop_ub; i0++) {
                  pre_check->data[r0->data[i0]] = ndbl;
                }
              } else {
                if (limit_up->data[jj] + 1.0 > limit_up->data[1 + jj] - 1.0) {
                  i0 = 0;
                } else {
                  i0 = (int)(limit_up->data[jj] + 1.0) - 1;
                }

                anew = pre_check->data[(int)limit_up->data[jj] - 1] + step;
                b = pre_check->data[(int)limit_up->data[1 + jj] - 1] - step;
                if (rtIsNaN(anew) || rtIsNaN(step) || rtIsNaN(b)) {
                  nx = 1;
                  anew = rtNaN;
                  apnd = b;
                } else if ((step == 0.0) || ((anew < b) && (step < 0.0)) || ((b <
                  anew) && (step > 0.0))) {
                  nx = 0;
                  apnd = b;
                } else if (rtIsInf(anew) || rtIsInf(b)) {
                  nx = 1;
                  anew = rtNaN;
                  apnd = b;
                } else if (rtIsInf(step)) {
                  nx = 1;
                  apnd = b;
                } else {
                  ndbl = floor((b - anew) / step + 0.5);
                  apnd = anew + ndbl * step;
                  if (step > 0.0) {
                    cdiff = apnd - b;
                  } else {
                    cdiff = b - apnd;
                  }

                  absa = fabs(anew);
                  absb = fabs(b);
                  if ((absa >= absb) || rtIsNaN(absb)) {
                    absb = absa;
                  }

                  if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
                    ndbl++;
                    apnd = b;
                  } else if (cdiff > 0.0) {
                    apnd = anew + (ndbl - 1.0) * step;
                  } else {
                    ndbl++;
                  }

                  if (ndbl >= 0.0) {
                    nx = (int)ndbl;
                  } else {
                    nx = 0;
                  }
                }

                i1 = r1->size[0] * r1->size[1];
                r1->size[0] = 1;
                r1->size[1] = nx;
                emxEnsureCapacity((emxArray__common *)r1, i1, (int)sizeof(double));
                if (nx > 0) {
                  r1->data[0] = anew;
                  if (nx > 1) {
                    r1->data[nx - 1] = apnd;
                    i1 = nx - 1;
                    nm1d2 = i1 / 2;
                    for (k = 1; k < nm1d2; k++) {
                      ndbl = (double)k * step;
                      r1->data[k] = anew + ndbl;
                      r1->data[(nx - k) - 1] = apnd - ndbl;
                    }

                    if (nm1d2 << 1 == nx - 1) {
                      r1->data[nm1d2] = (anew + apnd) / 2.0;
                    } else {
                      ndbl = (double)nm1d2 * step;
                      r1->data[nm1d2] = anew + ndbl;
                      r1->data[nm1d2 + 1] = apnd - ndbl;
                    }
                  }
                }

                loop_ub = r1->size[1];
                for (i1 = 0; i1 < loop_ub; i1++) {
                  pre_check->data[i0 + i1] = r1->data[r1->size[0] * i1];
                }
              }
            }
          }
        }

        loop_ub = pre_check->size[0];
        for (i0 = 0; i0 < loop_ub; i0++) {
          data->data[i0] = pre_check->data[i0];
        }
      }

      b_ii++;
    }

    emxFree_real_T(&r1);
    emxFree_int32_T(&r0);
  }

  emxFree_int32_T(&ii);
  emxFree_boolean_T(&x);
  emxFree_real_T(&limit_down);
  emxFree_real_T(&limit_up);
  emxFree_real_T(&pre_check);
  emxFree_real_T(&std_t3);
}

/*
 * File trailer for range_cont.c
 *
 * [EOF]
 */
