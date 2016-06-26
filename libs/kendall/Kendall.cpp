/*
 * File: Kendall.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 12-Jun-2016 14:50:57
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "Kendall.h"
#include "libs/commons/emxutil.h"
#include "sortLE.h"

/* Function Definitions */

/*
 * 计算肯德尔系数
 * data1;data2均为一列数据
 * Arguments    : const emxArray_real_T *data1
 *                const emxArray_real_T *data2
 *                double limit_min1
 *                double limit_min2
 * Return Type  : double
 */
double Kendall(const emxArray_real_T *data1, const emxArray_real_T *data2,
               double limit_min1, double limit_min2)
{
  double R;
  int row;
  emxArray_real_T *sample1;
  int i2;
  int loop_ub;
  unsigned int mm;
  int ii;
  emxArray_real_T *sample;
  int m;
  emxArray_int32_T *b_ii;
  emxArray_int32_T *iwork;
  int i;
  int j;
  int pEnd;
  int p;
  int q;
  int qEnd;
  int kEnd;
  emxArray_real_T *nozero;
  unsigned int sample_idx_0;
  double P;
  int aa;
  int bb;
  if (data1->size[0] <= data2->size[0]) {
    row = data1->size[0];
  } else {
    row = data2->size[0];
  }

  emxInit_real_T(&sample1, 2);
  i2 = sample1->size[0] * sample1->size[1];
  sample1->size[0] = row;
  sample1->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)sample1, i2, (int)sizeof(double));
  loop_ub = row << 1;
  for (i2 = 0; i2 < loop_ub; i2++) {
    sample1->data[i2] = 0.0;
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
    loop_ub = 0;
  } else {
    loop_ub = (int)mm;
  }

  emxInit_real_T(&sample, 2);

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* 计算Kendall(肯德尔)秩相关系数，用于二维最大熵函数的拟合 */
  i2 = sample->size[0] * sample->size[1];
  sample->size[0] = loop_ub;
  sample->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)sample, i2, (int)sizeof(double));
  for (i2 = 0; i2 < 2; i2++) {
    for (m = 0; m < loop_ub; m++) {
      sample->data[m + sample->size[0] * i2] = sample1->data[m + sample1->size[0]
        * i2];
    }
  }

  emxFree_real_T(&sample1);
  emxInit_int32_T(&b_ii, 1);
  i2 = b_ii->size[0];
  b_ii->size[0] = loop_ub;
  emxEnsureCapacity((emxArray__common *)b_ii, i2, (int)sizeof(int));
  for (i2 = 0; i2 < loop_ub; i2++) {
    b_ii->data[i2] = 0;
  }

  if (loop_ub == 0) {
  } else {
    emxInit_int32_T(&iwork, 1);
    i2 = iwork->size[0];
    iwork->size[0] = loop_ub;
    emxEnsureCapacity((emxArray__common *)iwork, i2, (int)sizeof(int));
    for (m = 1; m <= loop_ub - 1; m += 2) {
      if (sortLE(sample, m, m + 1)) {
        b_ii->data[m - 1] = m;
        b_ii->data[m] = m + 1;
      } else {
        b_ii->data[m - 1] = m + 1;
        b_ii->data[m] = m;
      }
    }

    if ((loop_ub & 1) != 0) {
      b_ii->data[loop_ub - 1] = loop_ub;
    }

    i = 2;
    while (i < loop_ub) {
      i2 = i << 1;
      j = 1;
      for (pEnd = 1 + i; pEnd < loop_ub + 1; pEnd = qEnd + i) {
        p = j;
        q = pEnd;
        qEnd = j + i2;
        if (qEnd > loop_ub + 1) {
          qEnd = loop_ub + 1;
        }

        m = 0;
        kEnd = qEnd - j;
        while (m + 1 <= kEnd) {
          if (sortLE(sample, b_ii->data[p - 1], b_ii->data[q - 1])) {
            iwork->data[m] = b_ii->data[p - 1];
            p++;
            if (p == pEnd) {
              while (q < qEnd) {
                m++;
                iwork->data[m] = b_ii->data[q - 1];
                q++;
              }
            }
          } else {
            iwork->data[m] = b_ii->data[q - 1];
            q++;
            if (q == qEnd) {
              while (p < pEnd) {
                m++;
                iwork->data[m] = b_ii->data[p - 1];
                p++;
              }
            }
          }

          m++;
        }

        for (m = 0; m + 1 <= kEnd; m++) {
          b_ii->data[(j + m) - 1] = iwork->data[m];
        }

        j = qEnd;
      }

      i = i2;
    }

    emxFree_int32_T(&iwork);
  }

  emxInit_real_T1(&nozero, 1);
  m = sample->size[0];
  sample_idx_0 = (unsigned int)sample->size[0];
  i2 = nozero->size[0];
  nozero->size[0] = (int)sample_idx_0;
  emxEnsureCapacity((emxArray__common *)nozero, i2, (int)sizeof(double));
  for (j = 0; j < 2; j++) {
    for (i = 0; i + 1 <= m; i++) {
      nozero->data[i] = sample->data[(b_ii->data[i] + sample->size[0] * j) - 1];
    }

    for (i = 0; i + 1 <= m; i++) {
      sample->data[i + sample->size[0] * j] = nozero->data[i];
    }
  }

  emxFree_int32_T(&b_ii);
  emxFree_real_T(&nozero);

  /* 按波高为关键值，对波高和周期的组合进行排序 */
  P = 0.0;
  for (aa = 0; aa < loop_ub; aa++) {
    i2 = loop_ub + (int)(1.0 - ((1.0 + (double)aa) + 1.0));
    for (bb = 0; bb < i2; bb++) {
      if (sample->data[aa + sample->size[0]] <= sample->data[((int)((unsigned
             int)aa + bb) + sample->size[0]) + 1]) {
        P++;
      }
    }
  }

  emxFree_real_T(&sample);
  R = 4.0 * P / ((double)loop_ub * ((double)loop_ub - 1.0)) - 1.0;

  /* Kendall(肯德尔)秩相关系数 */
  return R;
}

/*
 * File trailer for Kendall.c
 *
 * [EOF]
 */
