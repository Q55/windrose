/*
 * File: gamma.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jun-2016 15:17:02
 */

/* Include Files */
#include "rt_nonfinite.h"
//#include "max_shang_one.h"
#include "gamma.h"

/* Function Definitions */

/*
 * Arguments    : double *x
 * Return Type  : void
 */
void b_gamma(double *x)
{
  static const double gam[23] = { 1.0, 1.0, 2.0, 6.0, 24.0, 120.0, 720.0, 5040.0,
    40320.0, 362880.0, 3.6288E+6, 3.99168E+7, 4.790016E+8, 6.2270208E+9,
    8.71782912E+10, 1.307674368E+12, 2.0922789888E+13, 3.55687428096E+14,
    6.402373705728E+15, 1.21645100408832E+17, 2.43290200817664E+18,
    5.109094217170944E+19, 1.1240007277776077E+21 };

  double fact;
  double n;
  boolean_T parity;
  double yint;
  double xkold;
  double sum;
  double xden;
  int i;
  static const double p[8] = { -1.716185138865495, 24.76565080557592,
    -379.80425647094563, 629.3311553128184, 866.96620279041326,
    -31451.272968848367, -36144.413418691176, 66456.143820240541 };

  static const double q[8] = { -30.840230011973897, 315.35062697960416,
    -1015.1563674902192, -3107.7716715723109, 22538.11842098015,
    4755.8462775278813, -134659.95986496931, -115132.25967555349 };

  static const double c[7] = { -0.001910444077728, 0.00084171387781295,
    -0.00059523799130430121, 0.0007936507935003503, -0.0027777777777776816,
    0.083333333333333329, 0.0057083835261 };

  if ((*x >= 1.0) && (*x <= 23.0) && (*x == floor(*x))) {
    *x = gam[(int)*x - 1];
  } else if ((*x < 1.0) && (*x == floor(*x))) {
    *x = rtInf;
  } else if (rtIsNaN(*x)) {
    *x = rtNaN;
  } else if (rtIsInf(*x)) {
    *x = rtInf;
  } else {
    fact = 1.0;
    n = 0.0;
    parity = false;
    if (*x <= 0.0) {
      yint = floor(-*x);
      if (yint != floor(-*x / 2.0) * 2.0) {
        parity = true;
      }

      fact = -3.1415926535897931 / sin(3.1415926535897931 * (-*x - yint));
      *x = -*x + 1.0;
    }

    if (*x < 12.0) {
      xkold = *x;
      if (*x < 1.0) {
        yint = *x;
        (*x)++;
      } else {
        n = floor(*x) - 1.0;
        *x -= floor(*x) - 1.0;
        yint = *x - 1.0;
      }

      sum = 0.0 * yint;
      xden = 1.0;
      for (i = 0; i < 8; i++) {
        sum = (sum + p[i]) * yint;
        xden = xden * yint + q[i];
      }

      yint = sum / xden + 1.0;
      if (xkold < *x) {
        yint /= xkold;
      } else {
        if (xkold > *x) {
          for (i = 0; i < (int)n; i++) {
            yint *= *x;
            (*x)++;
          }
        }
      }
    } else {
      yint = *x * *x;
      sum = 0.0057083835261;
      for (i = 0; i < 6; i++) {
        sum = sum / yint + c[i];
      }

      sum = (sum / *x - *x) + 0.91893853320467278;
      sum += (*x - 0.5) * log(*x);
      yint = exp(sum);
    }

    if (parity) {
      yint = -yint;
    }

    if (fact != 1.0) {
      yint = fact / yint;
    }

    *x = yint;
  }
}

/*
 * File trailer for gamma.c
 *
 * [EOF]
 */
