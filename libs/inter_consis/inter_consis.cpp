/*
 * File: inter_consis.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 20-May-2016 13:53:15
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "inter_consis.h"
#include "libs/commons/emxutil.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_real_T *data1
 *                const emxArray_real_T *data2
 *                double type
 *                emxArray_real_T *data
 * Return Type  : void
 */
void inter_consis(emxArray_real_T *data1, const emxArray_real_T *data2, double
                  type, emxArray_real_T *data)
{
  emxArray_real_T *flag_yc;
  emxArray_int32_T *r0;
  emxArray_real_T *r1;
  emxArray_boolean_T *x;
  emxArray_int32_T *ii;
  int i0;
  int nm1d2;
  int nx;
  int idx;
  boolean_T exitg3;
  boolean_T guard3 = false;
  double kd;
  int kk;
  double step;
  double anew;
  double apnd;
  double ndbl;
  double cdiff;
  double absa;
  double absb;
  boolean_T exitg2;
  boolean_T guard2 = false;
  boolean_T exitg1;
  boolean_T guard1 = false;
  emxInit_real_T(&flag_yc, 1);
  emxInit_int32_T(&r0, 2);
  emxInit_real_T1(&r1, 2);
  emxInit_boolean_T(&x, 1);
  emxInit_int32_T1(&ii, 1);
  switch ((int)type) {
   case 1:
    i0 = x->size[0];
    x->size[0] = data1->size[0];
    emxEnsureCapacity((emxArray__common *)x, i0, (int)sizeof(boolean_T));
    nm1d2 = data1->size[0];
    for (i0 = 0; i0 < nm1d2; i0++) {
      x->data[i0] = (data1->data[i0] - data2->data[i0] > 0.0);
    }

    nx = x->size[0];
    idx = 0;
    i0 = ii->size[0];
    ii->size[0] = x->size[0];
    emxEnsureCapacity((emxArray__common *)ii, i0, (int)sizeof(int));
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

    i0 = flag_yc->size[0];
    flag_yc->size[0] = ii->size[0];
    emxEnsureCapacity((emxArray__common *)flag_yc, i0, (int)sizeof(double));
    nm1d2 = ii->size[0];
    for (i0 = 0; i0 < nm1d2; i0++) {
      flag_yc->data[i0] = ii->data[i0];
    }

    /* 标记正确的值,注意书写格式 */
    if (!(flag_yc->size[0] == 0)) {
      if (flag_yc->data[0] != 1.0) {
        if (1.0 > flag_yc->data[0]) {
          nm1d2 = 0;
        } else {
          nm1d2 = (int)flag_yc->data[0];
        }

        i0 = r0->size[0] * r0->size[1];
        r0->size[0] = 1;
        r0->size[1] = nm1d2;
        emxEnsureCapacity((emxArray__common *)r0, i0, (int)sizeof(int));
        for (i0 = 0; i0 < nm1d2; i0++) {
          r0->data[r0->size[0] * i0] = i0;
        }

        kd = data1->data[(int)flag_yc->data[0] - 1];
        nm1d2 = r0->size[0] * r0->size[1];
        for (i0 = 0; i0 < nm1d2; i0++) {
          data1->data[r0->data[i0]] = kd;
        }
      }

      if (data1->size[0] > (int)flag_yc->data[flag_yc->size[0] - 1]) {
        if (flag_yc->data[flag_yc->size[0] - 1] + 1.0 > data1->size[0]) {
          i0 = 0;
          nx = 0;
        } else {
          i0 = (int)(flag_yc->data[flag_yc->size[0] - 1] + 1.0) - 1;
          nx = data1->size[0];
        }

        nm1d2 = r0->size[0] * r0->size[1];
        r0->size[0] = 1;
        r0->size[1] = nx - i0;
        emxEnsureCapacity((emxArray__common *)r0, nm1d2, (int)sizeof(int));
        nm1d2 = nx - i0;
        for (nx = 0; nx < nm1d2; nx++) {
          r0->data[r0->size[0] * nx] = i0 + nx;
        }

        kd = data1->data[(int)flag_yc->data[flag_yc->size[0] - 1] - 1];
        nm1d2 = r0->size[0] * r0->size[1];
        for (i0 = 0; i0 < nm1d2; i0++) {
          data1->data[r0->data[i0]] = kd;
        }

        /* 不符合的数全部按照最后一个正确的数补齐 */
      }

      for (kk = 0; kk <= flag_yc->size[0] - 2; kk++) {
        /* 遍历正确数据，查找错误数据 */
        if (flag_yc->data[1 + kk] - flag_yc->data[kk] != 1.0) {
          step = (data1->data[(int)flag_yc->data[1 + kk] - 1] - data1->data[(int)
                  flag_yc->data[kk] - 1]) / (flag_yc->data[1 + kk] -
            flag_yc->data[kk]);
          if (step == 0.0) {
            if (flag_yc->data[kk] + 1.0 > flag_yc->data[1 + kk] - 1.0) {
              i0 = 0;
              nx = 0;
            } else {
              i0 = (int)(flag_yc->data[kk] + 1.0) - 1;
              nx = (int)(flag_yc->data[1 + kk] - 1.0);
            }

            nm1d2 = r0->size[0] * r0->size[1];
            r0->size[0] = 1;
            r0->size[1] = nx - i0;
            emxEnsureCapacity((emxArray__common *)r0, nm1d2, (int)sizeof(int));
            nm1d2 = nx - i0;
            for (nx = 0; nx < nm1d2; nx++) {
              r0->data[r0->size[0] * nx] = i0 + nx;
            }

            kd = data1->data[(int)flag_yc->data[kk] - 1];
            nm1d2 = r0->size[0] * r0->size[1];
            for (i0 = 0; i0 < nm1d2; i0++) {
              data1->data[r0->data[i0]] = kd;
            }
          } else {
            if (flag_yc->data[kk] + 1.0 > flag_yc->data[1 + kk] - 1.0) {
              i0 = 0;
            } else {
              i0 = (int)(flag_yc->data[kk] + 1.0) - 1;
            }

            anew = data1->data[(int)flag_yc->data[kk] - 1] + step;
            kd = data1->data[(int)flag_yc->data[1 + kk] - 1] - step;
            if (rtIsNaN(anew) || rtIsNaN(step) || rtIsNaN(kd)) {
              idx = 1;
              anew = rtNaN;
              apnd = kd;
            } else if ((step == 0.0) || ((anew < kd) && (step < 0.0)) || ((kd <
                         anew) && (step > 0.0))) {
              idx = 0;
              apnd = kd;
            } else if (rtIsInf(anew) || rtIsInf(kd)) {
              idx = 1;
              anew = rtNaN;
              apnd = kd;
            } else if (rtIsInf(step)) {
              idx = 1;
              apnd = kd;
            } else {
              ndbl = floor((kd - anew) / step + 0.5);
              apnd = anew + ndbl * step;
              if (step > 0.0) {
                cdiff = apnd - kd;
              } else {
                cdiff = kd - apnd;
              }

              absa = fabs(anew);
              absb = fabs(kd);
              if ((absa >= absb) || rtIsNaN(absb)) {
                absb = absa;
              }

              if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
                ndbl++;
                apnd = kd;
              } else if (cdiff > 0.0) {
                apnd = anew + (ndbl - 1.0) * step;
              } else {
                ndbl++;
              }

              if (ndbl >= 0.0) {
                idx = (int)ndbl;
              } else {
                idx = 0;
              }
            }

            nx = r1->size[0] * r1->size[1];
            r1->size[0] = 1;
            r1->size[1] = idx;
            emxEnsureCapacity((emxArray__common *)r1, nx, (int)sizeof(double));
            if (idx > 0) {
              r1->data[0] = anew;
              if (idx > 1) {
                r1->data[idx - 1] = apnd;
                nx = idx - 1;
                nm1d2 = nx / 2;
                for (nx = 1; nx < nm1d2; nx++) {
                  kd = (double)nx * step;
                  r1->data[nx] = anew + kd;
                  r1->data[(idx - nx) - 1] = apnd - kd;
                }

                if (nm1d2 << 1 == idx - 1) {
                  r1->data[nm1d2] = (anew + apnd) / 2.0;
                } else {
                  kd = (double)nm1d2 * step;
                  r1->data[nm1d2] = anew + kd;
                  r1->data[nm1d2 + 1] = apnd - kd;
                }
              }
            }

            nm1d2 = r1->size[1];
            for (nx = 0; nx < nm1d2; nx++) {
              data1->data[i0 + nx] = r1->data[r1->size[0] * nx];
            }
          }
        }
      }
    } else {
      nm1d2 = data1->size[0];
      i0 = data1->size[0];
      data1->size[0] = nm1d2;
      emxEnsureCapacity((emxArray__common *)data1, i0, (int)sizeof(double));
      for (i0 = 0; i0 < nm1d2; i0++) {
        data1->data[i0] = 0.0;
      }
    }
    break;

   case 2:
    i0 = x->size[0];
    x->size[0] = data1->size[0];
    emxEnsureCapacity((emxArray__common *)x, i0, (int)sizeof(boolean_T));
    nm1d2 = data1->size[0];
    for (i0 = 0; i0 < nm1d2; i0++) {
      x->data[i0] = (data1->data[i0] - data2->data[i0] < 0.0);
    }

    nx = x->size[0];
    idx = 0;
    i0 = ii->size[0];
    ii->size[0] = x->size[0];
    emxEnsureCapacity((emxArray__common *)ii, i0, (int)sizeof(int));
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

    i0 = flag_yc->size[0];
    flag_yc->size[0] = ii->size[0];
    emxEnsureCapacity((emxArray__common *)flag_yc, i0, (int)sizeof(double));
    nm1d2 = ii->size[0];
    for (i0 = 0; i0 < nm1d2; i0++) {
      flag_yc->data[i0] = ii->data[i0];
    }

    /* 标记正确的值,注意书写格式 */
    if (!(flag_yc->size[0] == 0)) {
      if (flag_yc->data[0] != 1.0) {
        if (1.0 > flag_yc->data[0]) {
          nm1d2 = 0;
        } else {
          nm1d2 = (int)flag_yc->data[0];
        }

        i0 = r0->size[0] * r0->size[1];
        r0->size[0] = 1;
        r0->size[1] = nm1d2;
        emxEnsureCapacity((emxArray__common *)r0, i0, (int)sizeof(int));
        for (i0 = 0; i0 < nm1d2; i0++) {
          r0->data[r0->size[0] * i0] = i0;
        }

        kd = data1->data[(int)flag_yc->data[0] - 1];
        nm1d2 = r0->size[0] * r0->size[1];
        for (i0 = 0; i0 < nm1d2; i0++) {
          data1->data[r0->data[i0]] = kd;
        }
      }

      if (data1->size[0] > (int)flag_yc->data[flag_yc->size[0] - 1]) {
        if (flag_yc->data[flag_yc->size[0] - 1] + 1.0 > data1->size[0]) {
          i0 = 0;
          nx = 0;
        } else {
          i0 = (int)(flag_yc->data[flag_yc->size[0] - 1] + 1.0) - 1;
          nx = data1->size[0];
        }

        nm1d2 = r0->size[0] * r0->size[1];
        r0->size[0] = 1;
        r0->size[1] = nx - i0;
        emxEnsureCapacity((emxArray__common *)r0, nm1d2, (int)sizeof(int));
        nm1d2 = nx - i0;
        for (nx = 0; nx < nm1d2; nx++) {
          r0->data[r0->size[0] * nx] = i0 + nx;
        }

        kd = data1->data[(int)flag_yc->data[flag_yc->size[0] - 1] - 1];
        nm1d2 = r0->size[0] * r0->size[1];
        for (i0 = 0; i0 < nm1d2; i0++) {
          data1->data[r0->data[i0]] = kd;
        }

        /* 不符合的数全部按照最后一个正确的数补齐 */
      }

      for (kk = 0; kk <= flag_yc->size[0] - 2; kk++) {
        /*  */
        if (flag_yc->data[1 + kk] - flag_yc->data[kk] != 1.0) {
          step = (data1->data[(int)flag_yc->data[1 + kk] - 1] - data1->data[(int)
                  flag_yc->data[kk] - 1]) / (flag_yc->data[1 + kk] -
            flag_yc->data[kk]);
          if (step == 0.0) {
            if (flag_yc->data[kk] + 1.0 > flag_yc->data[1 + kk] - 1.0) {
              i0 = 0;
              nx = 0;
            } else {
              i0 = (int)(flag_yc->data[kk] + 1.0) - 1;
              nx = (int)(flag_yc->data[1 + kk] - 1.0);
            }

            nm1d2 = r0->size[0] * r0->size[1];
            r0->size[0] = 1;
            r0->size[1] = nx - i0;
            emxEnsureCapacity((emxArray__common *)r0, nm1d2, (int)sizeof(int));
            nm1d2 = nx - i0;
            for (nx = 0; nx < nm1d2; nx++) {
              r0->data[r0->size[0] * nx] = i0 + nx;
            }

            kd = data1->data[(int)flag_yc->data[kk] - 1];
            nm1d2 = r0->size[0] * r0->size[1];
            for (i0 = 0; i0 < nm1d2; i0++) {
              data1->data[r0->data[i0]] = kd;
            }
          } else {
            if (flag_yc->data[kk] + 1.0 > flag_yc->data[1 + kk] - 1.0) {
              i0 = 0;
            } else {
              i0 = (int)(flag_yc->data[kk] + 1.0) - 1;
            }

            anew = data1->data[(int)flag_yc->data[kk] - 1] + step;
            kd = data1->data[(int)flag_yc->data[1 + kk] - 1] - step;
            if (rtIsNaN(anew) || rtIsNaN(step) || rtIsNaN(kd)) {
              idx = 1;
              anew = rtNaN;
              apnd = kd;
            } else if ((step == 0.0) || ((anew < kd) && (step < 0.0)) || ((kd <
                         anew) && (step > 0.0))) {
              idx = 0;
              apnd = kd;
            } else if (rtIsInf(anew) || rtIsInf(kd)) {
              idx = 1;
              anew = rtNaN;
              apnd = kd;
            } else if (rtIsInf(step)) {
              idx = 1;
              apnd = kd;
            } else {
              ndbl = floor((kd - anew) / step + 0.5);
              apnd = anew + ndbl * step;
              if (step > 0.0) {
                cdiff = apnd - kd;
              } else {
                cdiff = kd - apnd;
              }

              absa = fabs(anew);
              absb = fabs(kd);
              if ((absa >= absb) || rtIsNaN(absb)) {
                absb = absa;
              }

              if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
                ndbl++;
                apnd = kd;
              } else if (cdiff > 0.0) {
                apnd = anew + (ndbl - 1.0) * step;
              } else {
                ndbl++;
              }

              if (ndbl >= 0.0) {
                idx = (int)ndbl;
              } else {
                idx = 0;
              }
            }

            nx = r1->size[0] * r1->size[1];
            r1->size[0] = 1;
            r1->size[1] = idx;
            emxEnsureCapacity((emxArray__common *)r1, nx, (int)sizeof(double));
            if (idx > 0) {
              r1->data[0] = anew;
              if (idx > 1) {
                r1->data[idx - 1] = apnd;
                nx = idx - 1;
                nm1d2 = nx / 2;
                for (nx = 1; nx < nm1d2; nx++) {
                  kd = (double)nx * step;
                  r1->data[nx] = anew + kd;
                  r1->data[(idx - nx) - 1] = apnd - kd;
                }

                if (nm1d2 << 1 == idx - 1) {
                  r1->data[nm1d2] = (anew + apnd) / 2.0;
                } else {
                  kd = (double)nm1d2 * step;
                  r1->data[nm1d2] = anew + kd;
                  r1->data[nm1d2 + 1] = apnd - kd;
                }
              }
            }

            nm1d2 = r1->size[1];
            for (nx = 0; nx < nm1d2; nx++) {
              data1->data[i0 + nx] = r1->data[r1->size[0] * nx];
            }
          }
        }
      }
    } else {
      nm1d2 = data1->size[0];
      i0 = data1->size[0];
      data1->size[0] = nm1d2;
      emxEnsureCapacity((emxArray__common *)data1, i0, (int)sizeof(double));
      for (i0 = 0; i0 < nm1d2; i0++) {
        data1->data[i0] = 0.0;
      }
    }
    break;

   case 3:
    i0 = x->size[0];
    x->size[0] = data1->size[0];
    emxEnsureCapacity((emxArray__common *)x, i0, (int)sizeof(boolean_T));
    nm1d2 = data1->size[0];
    for (i0 = 0; i0 < nm1d2; i0++) {
      x->data[i0] = (data1->data[i0] - data2->data[i0] == 0.0);
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

    i0 = flag_yc->size[0];
    flag_yc->size[0] = ii->size[0];
    emxEnsureCapacity((emxArray__common *)flag_yc, i0, (int)sizeof(double));
    nm1d2 = ii->size[0];
    for (i0 = 0; i0 < nm1d2; i0++) {
      flag_yc->data[i0] = ii->data[i0];
    }

    /* 标记正确的值,注意书写格式 */
    if (!(flag_yc->size[0] == 0)) {
      if (flag_yc->data[0] != 1.0) {
        if (1.0 > flag_yc->data[0]) {
          nm1d2 = 0;
        } else {
          nm1d2 = (int)flag_yc->data[0];
        }

        i0 = r0->size[0] * r0->size[1];
        r0->size[0] = 1;
        r0->size[1] = nm1d2;
        emxEnsureCapacity((emxArray__common *)r0, i0, (int)sizeof(int));
        for (i0 = 0; i0 < nm1d2; i0++) {
          r0->data[r0->size[0] * i0] = i0;
        }

        kd = data1->data[(int)flag_yc->data[0] - 1];
        nm1d2 = r0->size[0] * r0->size[1];
        for (i0 = 0; i0 < nm1d2; i0++) {
          data1->data[r0->data[i0]] = kd;
        }
      }

      if (data1->size[0] > (int)flag_yc->data[flag_yc->size[0] - 1]) {
        if (flag_yc->data[flag_yc->size[0] - 1] + 1.0 > data1->size[0]) {
          i0 = 0;
          nx = 0;
        } else {
          i0 = (int)(flag_yc->data[flag_yc->size[0] - 1] + 1.0) - 1;
          nx = data1->size[0];
        }

        nm1d2 = r0->size[0] * r0->size[1];
        r0->size[0] = 1;
        r0->size[1] = nx - i0;
        emxEnsureCapacity((emxArray__common *)r0, nm1d2, (int)sizeof(int));
        nm1d2 = nx - i0;
        for (nx = 0; nx < nm1d2; nx++) {
          r0->data[r0->size[0] * nx] = i0 + nx;
        }

        kd = data1->data[(int)flag_yc->data[flag_yc->size[0] - 1] - 1];
        nm1d2 = r0->size[0] * r0->size[1];
        for (i0 = 0; i0 < nm1d2; i0++) {
          data1->data[r0->data[i0]] = kd;
        }

        /* 不符合的数全部按照最后一个正确的数补齐 */
      }

      for (kk = 0; kk <= flag_yc->size[0] - 2; kk++) {
        /*  */
        if (flag_yc->data[1 + kk] - flag_yc->data[kk] != 1.0) {
          step = (data1->data[(int)flag_yc->data[1 + kk] - 1] - data1->data[(int)
                  flag_yc->data[kk] - 1]) / (flag_yc->data[1 + kk] -
            flag_yc->data[kk]);
          if (step == 0.0) {
            if (flag_yc->data[kk] + 1.0 > flag_yc->data[1 + kk] - 1.0) {
              i0 = 0;
              nx = 0;
            } else {
              i0 = (int)(flag_yc->data[kk] + 1.0) - 1;
              nx = (int)(flag_yc->data[1 + kk] - 1.0);
            }

            nm1d2 = r0->size[0] * r0->size[1];
            r0->size[0] = 1;
            r0->size[1] = nx - i0;
            emxEnsureCapacity((emxArray__common *)r0, nm1d2, (int)sizeof(int));
            nm1d2 = nx - i0;
            for (nx = 0; nx < nm1d2; nx++) {
              r0->data[r0->size[0] * nx] = i0 + nx;
            }

            kd = data1->data[(int)flag_yc->data[kk] - 1];
            nm1d2 = r0->size[0] * r0->size[1];
            for (i0 = 0; i0 < nm1d2; i0++) {
              data1->data[r0->data[i0]] = kd;
            }
          } else {
            if (flag_yc->data[kk] + 1.0 > flag_yc->data[1 + kk] - 1.0) {
              i0 = 0;
            } else {
              i0 = (int)(flag_yc->data[kk] + 1.0) - 1;
            }

            anew = data1->data[(int)flag_yc->data[kk] - 1] + step;
            kd = data1->data[(int)flag_yc->data[1 + kk] - 1] - step;
            if (rtIsNaN(anew) || rtIsNaN(step) || rtIsNaN(kd)) {
              idx = 1;
              anew = rtNaN;
              apnd = kd;
            } else if ((step == 0.0) || ((anew < kd) && (step < 0.0)) || ((kd <
                         anew) && (step > 0.0))) {
              idx = 0;
              apnd = kd;
            } else if (rtIsInf(anew) || rtIsInf(kd)) {
              idx = 1;
              anew = rtNaN;
              apnd = kd;
            } else if (rtIsInf(step)) {
              idx = 1;
              apnd = kd;
            } else {
              ndbl = floor((kd - anew) / step + 0.5);
              apnd = anew + ndbl * step;
              if (step > 0.0) {
                cdiff = apnd - kd;
              } else {
                cdiff = kd - apnd;
              }

              absa = fabs(anew);
              absb = fabs(kd);
              if ((absa >= absb) || rtIsNaN(absb)) {
                absb = absa;
              }

              if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
                ndbl++;
                apnd = kd;
              } else if (cdiff > 0.0) {
                apnd = anew + (ndbl - 1.0) * step;
              } else {
                ndbl++;
              }

              if (ndbl >= 0.0) {
                idx = (int)ndbl;
              } else {
                idx = 0;
              }
            }

            nx = r1->size[0] * r1->size[1];
            r1->size[0] = 1;
            r1->size[1] = idx;
            emxEnsureCapacity((emxArray__common *)r1, nx, (int)sizeof(double));
            if (idx > 0) {
              r1->data[0] = anew;
              if (idx > 1) {
                r1->data[idx - 1] = apnd;
                nx = idx - 1;
                nm1d2 = nx / 2;
                for (nx = 1; nx < nm1d2; nx++) {
                  kd = (double)nx * step;
                  r1->data[nx] = anew + kd;
                  r1->data[(idx - nx) - 1] = apnd - kd;
                }

                if (nm1d2 << 1 == idx - 1) {
                  r1->data[nm1d2] = (anew + apnd) / 2.0;
                } else {
                  kd = (double)nm1d2 * step;
                  r1->data[nm1d2] = anew + kd;
                  r1->data[nm1d2 + 1] = apnd - kd;
                }
              }
            }

            nm1d2 = r1->size[1];
            for (nx = 0; nx < nm1d2; nx++) {
              data1->data[i0 + nx] = r1->data[r1->size[0] * nx];
            }
          }
        }
      }
    } else {
      nm1d2 = data1->size[0];
      i0 = data1->size[0];
      data1->size[0] = nm1d2;
      emxEnsureCapacity((emxArray__common *)data1, i0, (int)sizeof(double));
      for (i0 = 0; i0 < nm1d2; i0++) {
        data1->data[i0] = 0.0;
      }
    }
    break;
  }

  emxFree_int32_T(&ii);
  emxFree_boolean_T(&x);
  emxFree_real_T(&r1);
  emxFree_int32_T(&r0);
  emxFree_real_T(&flag_yc);
  i0 = data->size[0] * data->size[1];
  data->size[0] = data1->size[0];
  data->size[1] = 1;
  emxEnsureCapacity((emxArray__common *)data, i0, (int)sizeof(double));
  nm1d2 = data1->size[0];
  for (i0 = 0; i0 < nm1d2; i0++) {
    data->data[i0] = data1->data[i0];
  }
}

/*
 * File trailer for inter_consis.c
 *
 * [EOF]
 */
