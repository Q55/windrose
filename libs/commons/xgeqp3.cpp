/*
 * File: xgeqp3.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 20-May-2016 11:10:10
 */

/* Include Files */
#include "rt_nonfinite.h"
//#include "cycle_max.h"
#include "xgeqp3.h"
#include "xnrm2.h"

/* Function Declarations */
static double rt_hypotd_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_hypotd_snf(double u0, double u1)
{
  double y;
  double a;
  double b;
  a = fabs(u0);
  b = fabs(u1);
  if (a < b) {
    a /= b;
    y = b * sqrt(a * a + 1.0);
  } else if (a > b) {
    b /= a;
    y = a * sqrt(b * b + 1.0);
  } else if (rtIsNaN(b)) {
    y = b;
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

/*
 * Arguments    : double A[22]
 *                double tau[2]
 *                int jpvt[2]
 * Return Type  : void
 */
void xgeqp3(double A[22], double tau[2], int jpvt[2])
{
  double vn1[2];
  double vn2[2];
  int k;
  int pvt;
  double work[2];
  double smax;
  double temp2;
  int iy;
  double absxk;
  double t;
  int i;
  int i_i;
  int ix;
  int lastv;
  int lastc;
  boolean_T exitg2;
  int exitg1;
  int jy;
  k = 1;
  for (pvt = 0; pvt < 2; pvt++) {
    jpvt[pvt] = 1 + pvt;
    work[pvt] = 0.0;
    smax = 0.0;
    temp2 = 2.2250738585072014E-308;
    for (iy = k; iy <= k + 10; iy++) {
      absxk = fabs(A[iy - 1]);
      if (absxk > temp2) {
        t = temp2 / absxk;
        smax = 1.0 + smax * t * t;
        temp2 = absxk;
      } else {
        t = absxk / temp2;
        smax += t * t;
      }
    }

    smax = temp2 * sqrt(smax);
    vn1[pvt] = smax;
    vn2[pvt] = vn1[pvt];
    k += 11;
  }

  for (i = 0; i < 2; i++) {
    i_i = i + i * 11;
    iy = 0;
    if (2 - i > 1) {
      smax = vn1[i];
      k = 2;
      while (k <= 2 - i) {
        if (vn1[1] > smax) {
          iy = 1;
          smax = vn1[1];
        }

        k = 3;
      }
    }

    pvt = i + iy;
    if (pvt + 1 != i + 1) {
      ix = 11 * pvt;
      iy = 11 * i;
      for (k = 0; k < 11; k++) {
        smax = A[ix];
        A[ix] = A[iy];
        A[iy] = smax;
        ix++;
        iy++;
      }

      iy = jpvt[pvt];
      jpvt[pvt] = jpvt[i];
      jpvt[i] = iy;
      vn1[pvt] = vn1[i];
      vn2[pvt] = vn2[i];
    }

    absxk = A[i_i];
    temp2 = 0.0;
    smax = xnrm2(10 - i, A, i_i + 2);
    if (smax != 0.0) {
      smax = rt_hypotd_snf(A[i_i], smax);
      if (A[i_i] >= 0.0) {
        smax = -smax;
      }

      if (fabs(smax) < 1.0020841800044864E-292) {
        iy = 0;
        do {
          iy++;
          pvt = (i_i - i) + 11;
          for (k = i_i + 1; k + 1 <= pvt; k++) {
            A[k] *= 9.9792015476736E+291;
          }

          smax *= 9.9792015476736E+291;
          absxk *= 9.9792015476736E+291;
        } while (!(fabs(smax) >= 1.0020841800044864E-292));

        smax = rt_hypotd_snf(absxk, xnrm2(10 - i, A, i_i + 2));
        if (absxk >= 0.0) {
          smax = -smax;
        }

        temp2 = (smax - absxk) / smax;
        absxk = 1.0 / (absxk - smax);
        pvt = (i_i - i) + 11;
        for (k = i_i + 1; k + 1 <= pvt; k++) {
          A[k] *= absxk;
        }

        for (k = 1; k <= iy; k++) {
          smax *= 1.0020841800044864E-292;
        }

        absxk = smax;
      } else {
        temp2 = (smax - A[i_i]) / smax;
        absxk = 1.0 / (A[i_i] - smax);
        pvt = (i_i - i) + 11;
        for (k = i_i + 1; k + 1 <= pvt; k++) {
          A[k] *= absxk;
        }

        absxk = smax;
      }
    }

    tau[i] = temp2;
    A[i_i] = absxk;
    if (i + 1 < 2) {
      absxk = A[i_i];
      A[i_i] = 1.0;
      if (tau[0] != 0.0) {
        lastv = 11;
        iy = i_i + 10;
        while ((lastv > 0) && (A[iy] == 0.0)) {
          lastv--;
          iy--;
        }

        lastc = 1;
        exitg2 = false;
        while ((!exitg2) && (lastc > 0)) {
          iy = 12;
          do {
            exitg1 = 0;
            if (iy <= lastv + 11) {
              if (A[iy - 1] != 0.0) {
                exitg1 = 1;
              } else {
                iy++;
              }
            } else {
              lastc = 0;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        lastv = 0;
        lastc = 0;
      }

      if (lastv > 0) {
        if (lastc == 0) {
        } else {
          ix = i_i;
          smax = 0.0;
          for (iy = 12; iy <= lastv + 11; iy++) {
            smax += A[iy - 1] * A[ix];
            ix++;
          }

          work[0] = smax;
        }

        if (-tau[0] == 0.0) {
        } else {
          k = 11;
          jy = 0;
          pvt = 1;
          while (pvt <= lastc) {
            if (work[jy] != 0.0) {
              smax = work[jy] * -tau[0];
              ix = i_i;
              pvt = lastv + k;
              for (iy = k; iy + 1 <= pvt; iy++) {
                A[iy] += A[ix] * smax;
                ix++;
              }
            }

            jy++;
            k += 11;
            pvt = 2;
          }
        }
      }

      A[i_i] = absxk;
    }

    pvt = i + 2;
    while (pvt < 3) {
      if (vn1[1] != 0.0) {
        smax = fabs(A[11 + i]) / vn1[1];
        smax = 1.0 - smax * smax;
        if (smax < 0.0) {
          smax = 0.0;
        }

        temp2 = vn1[1] / vn2[1];
        temp2 = smax * (temp2 * temp2);
        if (temp2 <= 1.4901161193847656E-8) {
          smax = 0.0;
          temp2 = 2.2250738585072014E-308;
          for (k = i; k + 13 < 23; k++) {
            absxk = fabs(A[k + 12]);
            if (absxk > temp2) {
              t = temp2 / absxk;
              smax = 1.0 + smax * t * t;
              temp2 = absxk;
            } else {
              t = absxk / temp2;
              smax += t * t;
            }
          }

          smax = temp2 * sqrt(smax);
          vn1[1] = smax;
          vn2[1] = smax;
        } else {
          vn1[1] *= sqrt(smax);
        }
      }

      pvt = 3;
    }
  }
}

/*
 * File trailer for xgeqp3.c
 *
 * [EOF]
 */
