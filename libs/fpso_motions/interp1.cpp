/*
 * File: interp1.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "FPSO_MOTIONS.h"
#include "interp1.h"
#include "libs/commons/emxutil.h"
#include "bsearch.h"

/* Function Definitions */

/*
 * Arguments    : const double varargin_1[9]
 *                const double varargin_2[9]
 *                double varargin_3
 * Return Type  : double
 */
double b_interp1(const double varargin_1[9], const double varargin_2[9], double
                 varargin_3)
{
  double Vq;
  int low_i;
  int exitg1;
  int low_ip1;
  int high_i;
  int mid_i;
  double r;
  Vq = rtNaN;
  low_i = 1;
  do {
    exitg1 = 0;
    if (low_i < 10) {
      if (rtIsNaN(varargin_1[low_i - 1])) {
        exitg1 = 1;
      } else {
        low_i++;
      }
    } else {
      if (rtIsNaN(varargin_3) || (varargin_3 < 0.0)) {
      } else {
        low_i = 1;
        low_ip1 = 2;
        high_i = 9;
        while (high_i > low_ip1) {
          mid_i = (low_i + high_i) >> 1;
          if (varargin_3 >= varargin_1[mid_i - 1]) {
            low_i = mid_i;
            low_ip1 = mid_i + 1;
          } else {
            high_i = mid_i;
          }
        }

        r = (varargin_3 - varargin_1[low_i - 1]) / (varargin_1[low_i] -
          varargin_1[low_i - 1]);
        if (r == 0.0) {
          Vq = varargin_2[low_i - 1];
        } else if (r == 1.0) {
          Vq = varargin_2[low_i];
        } else if (varargin_2[low_i - 1] == varargin_2[low_i]) {
          Vq = varargin_2[low_i - 1];
        } else {
          Vq = (1.0 - r) * varargin_2[low_i - 1] + r * varargin_2[low_i];
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return Vq;
}

/*
 * Arguments    : const double varargin_1[28]
 *                const double varargin_2[28]
 *                const emxArray_real_T *varargin_3
 *                emxArray_real_T *Vq
 * Return Type  : void
 */
void c_interp1(const double varargin_1[28], const double varargin_2[28], const
               emxArray_real_T *varargin_3, emxArray_real_T *Vq)
{
  double y[28];
  double x[28];
  int outsize[2];
  int k;
  int low_i;
  int exitg1;
  double r;
  int low_ip1;
  int high_i;
  int mid_i;
  memcpy(&y[0], &varargin_2[0], 28U * sizeof(double));
  memcpy(&x[0], &varargin_1[0], 28U * sizeof(double));
  for (k = 0; k < 2; k++) {
    outsize[k] = varargin_3->size[k];
  }

  k = Vq->size[0] * Vq->size[1];
  Vq->size[0] = 1;
  Vq->size[1] = outsize[1];
  emxEnsureCapacity((emxArray__common *)Vq, k, (int)sizeof(double));
  low_i = outsize[1];
  for (k = 0; k < low_i; k++) {
    Vq->data[k] = rtNaN;
  }

  if (varargin_3->size[1] == 0) {
  } else {
    k = 1;
    do {
      exitg1 = 0;
      if (k < 29) {
        if (rtIsNaN(varargin_1[k - 1])) {
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        if (varargin_1[1] < varargin_1[0]) {
          for (k = 0; k < 14; k++) {
            r = x[k];
            x[k] = x[27 - k];
            x[27 - k] = r;
            r = y[k];
            y[k] = y[27 - k];
            y[27 - k] = r;
          }
        }

        for (k = 0; k + 1 <= varargin_3->size[1]; k++) {
          r = Vq->data[k];
          if (rtIsNaN(varargin_3->data[k])) {
            r = rtNaN;
          } else if ((varargin_3->data[k] > x[27]) || (varargin_3->data[k] < x[0]))
          {
          } else {
            low_i = 1;
            low_ip1 = 2;
            high_i = 28;
            while (high_i > low_ip1) {
              mid_i = (low_i + high_i) >> 1;
              if (varargin_3->data[k] >= x[mid_i - 1]) {
                low_i = mid_i;
                low_ip1 = mid_i + 1;
              } else {
                high_i = mid_i;
              }
            }

            r = (varargin_3->data[k] - x[low_i - 1]) / (x[low_i] - x[low_i - 1]);
            if (r == 0.0) {
              r = y[low_i - 1];
            } else if (r == 1.0) {
              r = y[low_i];
            } else if (y[low_i - 1] == y[low_i]) {
              r = y[low_i - 1];
            } else {
              r = (1.0 - r) * y[low_i - 1] + r * y[low_i];
            }
          }

          Vq->data[k] = r;
        }

        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
}

/*
 * Arguments    : const emxArray_real_T *varargin_1
 *                const emxArray_real_T *varargin_2
 *                const emxArray_real_T *varargin_3
 *                emxArray_real_T *Vq
 * Return Type  : void
 */
void d_interp1(const emxArray_real_T *varargin_1, const emxArray_real_T
               *varargin_2, const emxArray_real_T *varargin_3, emxArray_real_T
               *Vq)
{
  emxArray_real_T *y;
  int j2;
  int nd2;
  emxArray_real_T *x;
  int nx;
  int outsize[2];
  int exitg1;
  int b_j1;
  double r;
  emxInit_real_T(&y, 2);
  j2 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = varargin_2->size[1];
  emxEnsureCapacity((emxArray__common *)y, j2, (int)sizeof(double));
  nd2 = varargin_2->size[0] * varargin_2->size[1];
  for (j2 = 0; j2 < nd2; j2++) {
    y->data[j2] = varargin_2->data[j2];
  }

  emxInit_real_T(&x, 2);
  j2 = x->size[0] * x->size[1];
  x->size[0] = 1;
  x->size[1] = varargin_1->size[1];
  emxEnsureCapacity((emxArray__common *)x, j2, (int)sizeof(double));
  nd2 = varargin_1->size[0] * varargin_1->size[1];
  for (j2 = 0; j2 < nd2; j2++) {
    x->data[j2] = varargin_1->data[j2];
  }

  nx = varargin_1->size[1];
  for (j2 = 0; j2 < 2; j2++) {
    outsize[j2] = varargin_3->size[j2];
  }

  j2 = Vq->size[0] * Vq->size[1];
  Vq->size[0] = 1;
  Vq->size[1] = outsize[1];
  emxEnsureCapacity((emxArray__common *)Vq, j2, (int)sizeof(double));
  nd2 = outsize[1];
  for (j2 = 0; j2 < nd2; j2++) {
    Vq->data[j2] = rtNaN;
  }

  if (varargin_3->size[1] == 0) {
  } else {
    j2 = 1;
    do {
      exitg1 = 0;
      if (j2 <= nx) {
        if (rtIsNaN(varargin_1->data[j2 - 1])) {
          exitg1 = 1;
        } else {
          j2++;
        }
      } else {
        if (varargin_1->data[1] < varargin_1->data[0]) {
          j2 = nx >> 1;
          for (b_j1 = 1; b_j1 <= j2; b_j1++) {
            r = x->data[b_j1 - 1];
            x->data[b_j1 - 1] = x->data[nx - b_j1];
            x->data[nx - b_j1] = r;
          }

          nd2 = varargin_2->size[1] >> 1;
          for (b_j1 = 1; b_j1 <= nd2; b_j1++) {
            j2 = varargin_2->size[1] - b_j1;
            r = y->data[b_j1 - 1];
            y->data[b_j1 - 1] = y->data[j2];
            y->data[j2] = r;
          }
        }

        for (j2 = 0; j2 + 1 <= varargin_3->size[1]; j2++) {
          r = Vq->data[j2];
          if (rtIsNaN(varargin_3->data[j2])) {
            r = rtNaN;
          } else if ((varargin_3->data[j2] > x->data[x->size[1] - 1]) ||
                     (varargin_3->data[j2] < x->data[0])) {
          } else {
            nd2 = b_bsearch(x, varargin_3->data[j2]) - 1;
            r = (varargin_3->data[j2] - x->data[nd2]) / (x->data[nd2 + 1] -
              x->data[nd2]);
            if (r == 0.0) {
              r = y->data[nd2];
            } else if (r == 1.0) {
              r = y->data[nd2 + 1];
            } else if (y->data[nd2] == y->data[nd2 + 1]) {
              r = y->data[nd2];
            } else {
              r = (1.0 - r) * y->data[nd2] + r * y->data[nd2 + 1];
            }
          }

          Vq->data[j2] = r;
        }

        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  emxFree_real_T(&x);
  emxFree_real_T(&y);
}

/*
 * Arguments    : const double varargin_1_data[]
 *                const int varargin_1_size[2]
 *                const double varargin_2_data[]
 *                const int varargin_2_size[2]
 *                const double varargin_3_data[]
 *                const int varargin_3_size[2]
 *                double Vq_data[]
 *                int Vq_size[2]
 * Return Type  : void
 */
void e_interp1(const double varargin_1_data[], const int varargin_1_size[2],
               const double varargin_2_data[], const int varargin_2_size[2],
               const double varargin_3_data[], const int varargin_3_size[2],
               double Vq_data[], int Vq_size[2])
{
  int nd2;
  int j2;
  double y_data[1248];
  int x_size[2];
  double x_data[1248];
  int nyrows;
  int nx;
  short outsize[2];
  emxArray_real_T *x;
  int exitg1;
  int b_j1;
  double r;
  double minx;
  double maxx;
  emxArray_real_T b_x_data;
  nd2 = varargin_2_size[0] * varargin_2_size[1];
  for (j2 = 0; j2 < nd2; j2++) {
    y_data[j2] = varargin_2_data[j2];
  }

  x_size[0] = 1;
  x_size[1] = varargin_1_size[1];
  nd2 = varargin_1_size[0] * varargin_1_size[1];
  for (j2 = 0; j2 < nd2; j2++) {
    x_data[j2] = varargin_1_data[j2];
  }

  nyrows = varargin_2_size[1];
  nx = varargin_1_size[1];
  for (j2 = 0; j2 < 2; j2++) {
    outsize[j2] = (short)varargin_3_size[j2];
  }

  Vq_size[0] = 1;
  Vq_size[1] = outsize[1];
  nd2 = outsize[1];
  for (j2 = 0; j2 < nd2; j2++) {
    Vq_data[j2] = 0.0;
  }

  if (varargin_3_size[1] == 0) {
  } else {
    j2 = 1;
    emxInit_real_T(&x, 2);
    do {
      exitg1 = 0;
      if (j2 <= nx) {
        if (rtIsNaN(varargin_1_data[j2 - 1])) {
          exitg1 = 1;
        } else {
          j2++;
        }
      } else {
        if (varargin_1_data[1] < varargin_1_data[0]) {
          j2 = nx >> 1;
          for (b_j1 = 1; b_j1 <= j2; b_j1++) {
            r = x_data[b_j1 - 1];
            x_data[b_j1 - 1] = x_data[nx - b_j1];
            x_data[nx - b_j1] = r;
          }

          j2 = x->size[0] * x->size[1];
          x->size[0] = 1;
          x->size[1] = varargin_2_size[1];
          emxEnsureCapacity((emxArray__common *)x, j2, (int)sizeof(double));
          nd2 = varargin_2_size[0] * varargin_2_size[1];
          for (j2 = 0; j2 < nd2; j2++) {
            x->data[j2] = varargin_2_data[j2];
          }

          nd2 = varargin_2_size[1] >> 1;
          for (b_j1 = 1; b_j1 <= nd2; b_j1++) {
            j2 = varargin_2_size[1] - b_j1;
            r = x->data[b_j1 - 1];
            x->data[b_j1 - 1] = x->data[j2];
            x->data[j2] = r;
          }

          nd2 = x->size[0] * x->size[1];
          for (j2 = 0; j2 < nd2; j2++) {
            y_data[j2] = x->data[j2];
          }
        }

        minx = x_data[0];
        maxx = x_data[x_size[1] - 1];
        for (j2 = 0; j2 + 1 <= varargin_3_size[1]; j2++) {
          r = Vq_data[j2];
          if (rtIsNaN(varargin_3_data[j2])) {
            r = rtNaN;
          } else if (varargin_3_data[j2] > maxx) {
            if (nyrows > 1) {
              r = y_data[nyrows - 1] + (varargin_3_data[j2] - maxx) / (maxx -
                x_data[x_size[1] - 2]) * (y_data[nyrows - 1] - y_data[nyrows - 2]);
            }
          } else if (varargin_3_data[j2] < minx) {
            r = y_data[0] + (varargin_3_data[j2] - minx) / (x_data[1] - minx) *
              (y_data[1] - y_data[0]);
          } else {
            b_x_data.data = (double *)&x_data;
            b_x_data.size = (int *)&x_size;
            b_x_data.allocatedSize = 1248;
            b_x_data.numDimensions = 2;
            b_x_data.canFreeData = false;
            nd2 = b_bsearch(&b_x_data, varargin_3_data[j2]) - 1;
            r = (varargin_3_data[j2] - x_data[nd2]) / (x_data[nd2 + 1] -
              x_data[nd2]);
            if (r == 0.0) {
              r = y_data[nd2];
            } else if (r == 1.0) {
              r = y_data[nd2 + 1];
            } else if (y_data[nd2] == y_data[nd2 + 1]) {
              r = y_data[nd2];
            } else {
              r = (1.0 - r) * y_data[nd2] + r * y_data[nd2 + 1];
            }
          }

          Vq_data[j2] = r;
        }

        exitg1 = 1;
      }
    } while (exitg1 == 0);

    emxFree_real_T(&x);
  }
}

/*
 * Arguments    : const double varargin_1_data[]
 *                const int varargin_1_size[2]
 *                const double varargin_2_data[]
 *                const int varargin_2_size[1]
 *                const double varargin_3_data[]
 *                const int varargin_3_size[2]
 *                double Vq_data[]
 *                int Vq_size[2]
 * Return Type  : void
 */
void f_interp1(const double varargin_1_data[], const int varargin_1_size[2],
               const double varargin_2_data[], const int varargin_2_size[1],
               const double varargin_3_data[], const int varargin_3_size[2],
               double Vq_data[], int Vq_size[2])
{
  int n;
  int nd2;
  double y_data[1248];
  int x_size[2];
  double x_data[1248];
  int nyrows;
  int nx;
  short outsize[2];
  int k;
  int exitg1;
  double r;
  double minx;
  double maxx;
  emxArray_real_T b_x_data;
  n = varargin_2_size[0];
  for (nd2 = 0; nd2 < n; nd2++) {
    y_data[nd2] = varargin_2_data[nd2];
  }

  x_size[0] = 1;
  x_size[1] = varargin_1_size[1];
  n = varargin_1_size[0] * varargin_1_size[1];
  for (nd2 = 0; nd2 < n; nd2++) {
    x_data[nd2] = varargin_1_data[nd2];
  }

  nyrows = varargin_2_size[0];
  nx = varargin_1_size[1];
  for (nd2 = 0; nd2 < 2; nd2++) {
    outsize[nd2] = (short)varargin_3_size[nd2];
  }

  Vq_size[0] = 1;
  Vq_size[1] = outsize[1];
  n = outsize[1];
  for (nd2 = 0; nd2 < n; nd2++) {
    Vq_data[nd2] = 0.0;
  }

  if (varargin_3_size[1] == 0) {
  } else {
    k = 1;
    do {
      exitg1 = 0;
      if (k <= nx) {
        if (rtIsNaN(varargin_1_data[k - 1])) {
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        if (varargin_1_data[1] < varargin_1_data[0]) {
          nd2 = nx >> 1;
          for (n = 1; n <= nd2; n++) {
            r = x_data[n - 1];
            x_data[n - 1] = x_data[nx - n];
            x_data[nx - n] = r;
          }

          if ((!(varargin_2_size[0] == 0)) && (varargin_2_size[0] > 1)) {
            n = varargin_2_size[0];
            nd2 = varargin_2_size[0] >> 1;
            for (k = 1; k <= nd2; k++) {
              r = y_data[k - 1];
              y_data[k - 1] = y_data[n - k];
              y_data[n - k] = r;
            }
          }
        }

        minx = x_data[0];
        maxx = x_data[x_size[1] - 1];
        for (k = 0; k + 1 <= varargin_3_size[1]; k++) {
          r = Vq_data[k];
          if (rtIsNaN(varargin_3_data[k])) {
            r = rtNaN;
          } else if (varargin_3_data[k] > maxx) {
            if (nyrows > 1) {
              r = y_data[nyrows - 1] + (varargin_3_data[k] - maxx) / (maxx -
                x_data[x_size[1] - 2]) * (y_data[nyrows - 1] - y_data[nyrows - 2]);
            }
          } else if (varargin_3_data[k] < minx) {
            r = y_data[0] + (varargin_3_data[k] - minx) / (x_data[1] - minx) *
              (y_data[1] - y_data[0]);
          } else {
            b_x_data.data = (double *)&x_data;
            b_x_data.size = (int *)&x_size;
            b_x_data.allocatedSize = 1248;
            b_x_data.numDimensions = 2;
            b_x_data.canFreeData = false;
            n = b_bsearch(&b_x_data, varargin_3_data[k]) - 1;
            r = (varargin_3_data[k] - x_data[n]) / (x_data[n + 1] - x_data[n]);
            if (r == 0.0) {
              r = y_data[n];
            } else if (r == 1.0) {
              r = y_data[n + 1];
            } else if (y_data[n] == y_data[n + 1]) {
              r = y_data[n];
            } else {
              r = (1.0 - r) * y_data[n] + r * y_data[n + 1];
            }
          }

          Vq_data[k] = r;
        }

        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
}

/*
 * Arguments    : const emxArray_real_T *varargin_1
 *                const emxArray_real_T *varargin_2
 *                double varargin_3
 * Return Type  : double
 */
double g_interp1(const emxArray_real_T *varargin_1, const emxArray_real_T
                 *varargin_2, double varargin_3)
{
  double Vq;
  emxArray_real_T *y;
  int j2;
  int nd2;
  emxArray_real_T *x;
  int nyrows;
  int nx;
  int exitg1;
  int b_j1;
  double r;
  emxInit_real_T(&y, 2);
  j2 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = varargin_2->size[1];
  emxEnsureCapacity((emxArray__common *)y, j2, (int)sizeof(double));
  nd2 = varargin_2->size[0] * varargin_2->size[1];
  for (j2 = 0; j2 < nd2; j2++) {
    y->data[j2] = varargin_2->data[j2];
  }

  emxInit_real_T(&x, 2);
  j2 = x->size[0] * x->size[1];
  x->size[0] = 1;
  x->size[1] = varargin_1->size[1];
  emxEnsureCapacity((emxArray__common *)x, j2, (int)sizeof(double));
  nd2 = varargin_1->size[0] * varargin_1->size[1];
  for (j2 = 0; j2 < nd2; j2++) {
    x->data[j2] = varargin_1->data[j2];
  }

  nyrows = varargin_2->size[1];
  nx = varargin_1->size[1];
  Vq = 0.0;
  nd2 = 1;
  do {
    exitg1 = 0;
    if (nd2 <= nx) {
      if (rtIsNaN(varargin_1->data[nd2 - 1])) {
        exitg1 = 1;
      } else {
        nd2++;
      }
    } else {
      if (varargin_1->data[1] < varargin_1->data[0]) {
        j2 = nx >> 1;
        for (b_j1 = 1; b_j1 <= j2; b_j1++) {
          r = x->data[b_j1 - 1];
          x->data[b_j1 - 1] = x->data[nx - b_j1];
          x->data[nx - b_j1] = r;
        }

        nd2 = varargin_2->size[1] >> 1;
        for (b_j1 = 1; b_j1 <= nd2; b_j1++) {
          j2 = varargin_2->size[1] - b_j1;
          r = y->data[b_j1 - 1];
          y->data[b_j1 - 1] = y->data[j2];
          y->data[j2] = r;
        }
      }

      if (rtIsNaN(varargin_3)) {
        Vq = rtNaN;
      } else if (varargin_3 > x->data[x->size[1] - 1]) {
        if (nyrows > 1) {
          Vq = y->data[nyrows - 1] + (varargin_3 - x->data[x->size[1] - 1]) /
            (x->data[x->size[1] - 1] - x->data[x->size[1] - 2]) * (y->
            data[nyrows - 1] - y->data[nyrows - 2]);
        }
      } else if (varargin_3 < x->data[0]) {
        Vq = y->data[0] + (varargin_3 - x->data[0]) / (x->data[1] - x->data[0]) *
          (y->data[1] - y->data[0]);
      } else {
        nd2 = b_bsearch(x, varargin_3) - 1;
        r = (varargin_3 - x->data[nd2]) / (x->data[nd2 + 1] - x->data[nd2]);
        if (r == 0.0) {
          Vq = y->data[nd2];
        } else if (r == 1.0) {
          Vq = y->data[nd2 + 1];
        } else if (y->data[nd2] == y->data[nd2 + 1]) {
          Vq = y->data[nd2];
        } else {
          Vq = (1.0 - r) * y->data[nd2] + r * y->data[nd2 + 1];
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  emxFree_real_T(&x);
  emxFree_real_T(&y);
  return Vq;
}

/*
 * Arguments    : double varargin_3
 * Return Type  : double
 */
double interp1(double varargin_3)
{
  double Vq;
  int low_i;
  int low_ip1;
  int high_i;
  int mid_i;
  static const unsigned char x[9] = { 0U, 15U, 30U, 45U, 90U, 135U, 150U, 165U,
    180U };

  double r;
  static const double y[9] = { -0.778, -1.042, -1.055, -0.982, 0.0, 0.982, 1.055,
    1.042, 0.778 };

  Vq = rtNaN;
  if (rtIsNaN(varargin_3) || (varargin_3 < 0.0)) {
  } else {
    low_i = 1;
    low_ip1 = 2;
    high_i = 9;
    while (high_i > low_ip1) {
      mid_i = (low_i + high_i) >> 1;
      if (varargin_3 >= x[mid_i - 1]) {
        low_i = mid_i;
        low_ip1 = mid_i + 1;
      } else {
        high_i = mid_i;
      }
    }

    r = (varargin_3 - (double)x[low_i - 1]) / (double)(x[low_i] - x[low_i - 1]);
    if (r == 0.0) {
      Vq = y[low_i - 1];
    } else if (r == 1.0) {
      Vq = y[low_i];
    } else if (y[low_i - 1] == y[low_i]) {
      Vq = y[low_i - 1];
    } else {
      Vq = (1.0 - r) * y[low_i - 1] + r * y[low_i];
    }
  }

  return Vq;
}

/*
 * File trailer for interp1.c
 *
 * [EOF]
 */
