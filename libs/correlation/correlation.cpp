/*
 * File: correlation.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 12-May-2016 15:49:24
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "correlation.h"
#include "libs/commons/emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                const emxArray_real_T *y
 *                emxArray_real_T *b
 *                emxArray_real_T *a
 *                double *b_index
 * Return Type  : void
 */
void correlation(const emxArray_real_T *x, const emxArray_real_T *y,
                 emxArray_real_T *b, emxArray_real_T *a, double *b_index)
{
  int maxval;
  int m;
  int na;
  double nabclp;
  double bpadclp;
  double nc;
  int i0;
  int i;
  double s;
  double boffset;
  double jstart;
  double ndbl;
  double b_ndbl;
  int j;
  double apnd;
  int n;
  emxArray_real_T *b_x;
  emxArray_real_T *c_x;
  double xy[4];
  double d[2];
  if (x->size[0] >= y->size[0]) {
    maxval = x->size[0];
  } else {
    maxval = y->size[0];
  }

  if (x->size[0] >= y->size[0]) {
    m = x->size[0];
  } else {
    m = y->size[0];
  }

  m = (int)(((double)m - ((double)maxval - 1.0)) - 1.0);
  na = x->size[0];
  if (x->size[0] > y->size[0]) {
    nabclp = (double)x->size[0] - (double)m;
    bpadclp = nabclp - (double)y->size[0];
  } else {
    nabclp = (double)y->size[0] - (double)m;
    bpadclp = -(double)m;
  }

  nc = 2.0 * nabclp - 1.0;
  i0 = a->size[0];
  a->size[0] = (int)nc;
  emxEnsureCapacity((emxArray__common *)a, i0, (int)sizeof(double));
  for (i = 0; i < (int)nc; i++) {
    s = 0.0;
    boffset = (1.0 + (double)i) - nabclp;
    if (boffset > 0.0) {
      jstart = 1.0 + boffset;
    } else {
      jstart = 1.0;
    }

    ndbl = (1.0 + (double)i) - bpadclp;
    if (ndbl <= na) {
      b_ndbl = ndbl;
    } else {
      b_ndbl = na;
    }

    i0 = (int)(b_ndbl + (1.0 - jstart));
    for (j = 0; j < i0; j++) {
      ndbl = jstart + (double)j;
      apnd = y->data[(int)(ndbl - boffset) - 1];
      s += apnd * x->data[(int)ndbl - 1];
    }

    a->data[i] = s;
  }

  if (maxval - 1 < 1 - maxval) {
    n = 0;
    i = 1 - maxval;
    apnd = (double)maxval - 1.0;
  } else {
    i = 1 - maxval;
    ndbl = floor((((double)maxval - 1.0) - (-((double)maxval - 1.0))) + 0.5);
    apnd = -((double)maxval - 1.0) + ndbl;
    nabclp = apnd - ((double)maxval - 1.0);
    m = (int)fabs(-((double)maxval - 1.0));
    na = (int)fabs((double)maxval - 1.0);
    if (m >= na) {
      na = m;
    }

    if (fabs(nabclp) < 4.4408920985006262E-16 * (double)na) {
      ndbl++;
      apnd = (double)maxval - 1.0;
    } else if (nabclp > 0.0) {
      apnd = -((double)maxval - 1.0) + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      n = (int)ndbl;
    } else {
      n = 0;
    }
  }

  i0 = b->size[0] * b->size[1];
  b->size[0] = 1;
  b->size[1] = n;
  emxEnsureCapacity((emxArray__common *)b, i0, (int)sizeof(double));
  if (n > 0) {
    b->data[0] = i;
    if (n > 1) {
      b->data[n - 1] = apnd;
      i0 = n - 1;
      m = i0 / 2;
      for (na = 1; na < m; na++) {
        b->data[na] = i + na;
        b->data[(n - na) - 1] = apnd - (double)na;
      }

      if (m << 1 == n - 1) {
        b->data[m] = ((double)i + apnd) / 2.0;
      } else {
        b->data[m] = i + m;
        b->data[m + 1] = apnd - (double)m;
      }
    }
  }

  emxInit_real_T(&b_x, 2);
  m = x->size[0];
  na = y->size[0];
  i0 = b_x->size[0] * b_x->size[1];
  b_x->size[0] = m;
  b_x->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)b_x, i0, (int)sizeof(double));
  for (i0 = 0; i0 < m; i0++) {
    b_x->data[i0] = x->data[i0];
  }

  for (i0 = 0; i0 < na; i0++) {
    b_x->data[i0 + b_x->size[0]] = y->data[i0];
  }

  emxInit_real_T(&c_x, 2);
  i0 = c_x->size[0] * c_x->size[1];
  c_x->size[0] = b_x->size[0];
  c_x->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)c_x, i0, (int)sizeof(double));
  m = b_x->size[0] * b_x->size[1];
  for (i0 = 0; i0 < m; i0++) {
    c_x->data[i0] = b_x->data[i0];
  }

  n = b_x->size[0];
  for (i0 = 0; i0 < 4; i0++) {
    xy[i0] = 0.0;
  }

  if (b_x->size[0] < 2) {
    for (i0 = 0; i0 < 4; i0++) {
      xy[i0] = rtNaN;
    }
  } else {
    for (j = 0; j < 2; j++) {
      s = 0.0;
      for (i = 1; i <= n; i++) {
        s += c_x->data[(i + c_x->size[0] * j) - 1];
      }

      s /= (double)b_x->size[0];
      for (i = 0; i + 1 <= n; i++) {
        c_x->data[i + c_x->size[0] * j] -= s;
      }
    }

    m = b_x->size[0] - 1;
    for (j = 0; j < 2; j++) {
      ndbl = 0.0;
      for (na = 0; na + 1 <= n; na++) {
        ndbl += c_x->data[na + c_x->size[0] * j] * c_x->data[na + c_x->size[0] *
          j];
      }

      xy[j + (j << 1)] = ndbl / (double)m;
      i = j + 2;
      while (i < 3) {
        s = 0.0;
        for (na = 0; na + 1 <= n; na++) {
          s += c_x->data[na + c_x->size[0]] * c_x->data[na + c_x->size[0] * j];
        }

        xy[1 + (j << 1)] = s / (double)m;
        i = 3;
      }
    }
  }

  emxFree_real_T(&c_x);
  emxFree_real_T(&b_x);
  for (na = 0; na < 2; na++) {
    d[na] = sqrt(xy[na + (na << 1)]);
  }

  for (j = 0; j < 2; j++) {
    i = j + 2;
    while (i < 3) {
      xy[1 + (j << 1)] = xy[1 + (j << 1)] / d[1] / d[j];
      i = 3;
    }

    i = j + 2;
    while (i < 3) {
      ndbl = fabs(xy[1 + (j << 1)]);
      if (ndbl > 1.0) {
        xy[1 + (j << 1)] /= ndbl;
      }

      xy[2 + j] = xy[1 + (j << 1)];
      i = 3;
    }

    if (xy[j + (j << 1)] > 0.0) {
      if (xy[j + (j << 1)] < 0.0) {
        xy[j + (j << 1)] = -1.0;
      } else if (xy[j + (j << 1)] > 0.0) {
        xy[j + (j << 1)] = 1.0;
      } else {
        if (xy[j + (j << 1)] == 0.0) {
          xy[j + (j << 1)] = 0.0;
        }
      }
    } else {
      xy[j + (j << 1)] = rtNaN;
    }
  }

  *b_index = xy[2];

  /*  figure */
  /*  stem(b,a); */
}

/*
 * File trailer for correlation.c
 *
 * [EOF]
 */
