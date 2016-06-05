/*
 * File: weightedfit.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 13-May-2016 10:46:52
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "weightedfit.h"
#include "libs/commons/emxutil.h"
#include "libs/commons/sum.h"
#include "libs/commons/power.h"

/* Function Definitions */

/*
 * This code fits makes a linear fit to a data set (using y =bx+a) where each data point
 *  has a different or constant standard deviation. Your data should have three or two columns.
 *  The first column should be the independent variable(x) and the second
 *  column should be the dependent variable(y). Column three should contain
 *  your standard deviations for each datapoint. In the situations where you
 *  do not specify a column three, the code assigns a weight of one to all
 *  data points and this corresponds to the regular linear fits.
 * ==========
 *  INPUTS
 * ==========
 * data = 3 columns; column 1 = x, column2 = y and column 3 = standard dev.
 * Arguments    : const emxArray_real_T *data
 *                double *a
 *                double *b
 * Return Type  : void
 */
void weightedfit(const emxArray_real_T *data, double *a, double *b)
{
  emxArray_real_T *x;
  int loop_ub;
  int i0;
  emxArray_real_T *y;
  emxArray_real_T *r0;
  emxArray_real_T *w;
  emxArray_real_T *b_w;
  double S;
  emxArray_real_T *c_w;
  double Sx;
  emxArray_real_T *r1;
  emxArray_real_T *d_w;
  double Sy;
  emxArray_real_T *e_w;
  double Sxx;
  double Sxy;
  double Delta;
  emxInit_real_T(&x, 1);

  /* ========== */
  /* OUTPUTS */
  /* ========== */
  /* Result.slope= b; Fitted slope */
  /* Result.Intercept = a; Fitted intercept */
  /* Coded by Ebo Ewusi-Annan (University of Florida, 2011) */
  /* ============ */
  /* REFERENCES */
  /* =========== */
  /* 1. Willam H. Press, Saul A. Teukolsky and Willan T. Vetterling (1997). */
  /* Numerical Recipes in Fortran. */
  /* 2. Philip R. Bevington and D. Keith Robinson (2003). Data Reduction and */
  /* Error Analysis for the Physical Sciences. */
  loop_ub = data->size[0];
  i0 = x->size[0];
  x->size[0] = loop_ub;
  emxEnsureCapacity((emxArray__common *)x, i0, (int)sizeof(double));
  for (i0 = 0; i0 < loop_ub; i0++) {
    x->data[i0] = data->data[i0];
  }

  emxInit_real_T(&y, 1);
  loop_ub = data->size[0];
  i0 = y->size[0];
  y->size[0] = loop_ub;
  emxEnsureCapacity((emxArray__common *)y, i0, (int)sizeof(double));
  for (i0 = 0; i0 < loop_ub; i0++) {
    y->data[i0] = data->data[i0 + data->size[0]];
  }

  emxInit_real_T(&r0, 1);
  i0 = r0->size[0];
  r0->size[0] = data->size[0];
  emxEnsureCapacity((emxArray__common *)r0, i0, (int)sizeof(double));
  loop_ub = data->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r0->data[i0] = 1.0;
  }

  emxInit_real_T(&w, 1);
  power(r0, w);
  i0 = w->size[0];
  emxEnsureCapacity((emxArray__common *)w, i0, (int)sizeof(double));
  loop_ub = w->size[0];
  emxFree_real_T(&r0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    w->data[i0] = 1.0 / w->data[i0];
  }

  emxInit_real_T(&b_w, 1);
  S = sum(w);
  i0 = b_w->size[0];
  b_w->size[0] = w->size[0];
  emxEnsureCapacity((emxArray__common *)b_w, i0, (int)sizeof(double));
  loop_ub = w->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_w->data[i0] = w->data[i0] * x->data[i0];
  }

  emxInit_real_T(&c_w, 1);
  Sx = sum(b_w);
  i0 = c_w->size[0];
  c_w->size[0] = w->size[0];
  emxEnsureCapacity((emxArray__common *)c_w, i0, (int)sizeof(double));
  loop_ub = w->size[0];
  emxFree_real_T(&b_w);
  for (i0 = 0; i0 < loop_ub; i0++) {
    c_w->data[i0] = w->data[i0] * y->data[i0];
  }

  emxInit_real_T(&r1, 1);
  emxInit_real_T(&d_w, 1);
  Sy = sum(c_w);
  power(x, r1);
  i0 = d_w->size[0];
  d_w->size[0] = w->size[0];
  emxEnsureCapacity((emxArray__common *)d_w, i0, (int)sizeof(double));
  loop_ub = w->size[0];
  emxFree_real_T(&c_w);
  for (i0 = 0; i0 < loop_ub; i0++) {
    d_w->data[i0] = w->data[i0] * r1->data[i0];
  }

  emxFree_real_T(&r1);
  emxInit_real_T(&e_w, 1);
  Sxx = sum(d_w);
  i0 = e_w->size[0];
  e_w->size[0] = w->size[0];
  emxEnsureCapacity((emxArray__common *)e_w, i0, (int)sizeof(double));
  loop_ub = w->size[0];
  emxFree_real_T(&d_w);
  for (i0 = 0; i0 < loop_ub; i0++) {
    e_w->data[i0] = w->data[i0] * x->data[i0] * y->data[i0];
  }

  emxFree_real_T(&w);
  emxFree_real_T(&y);
  emxFree_real_T(&x);
  Sxy = sum(e_w);
  Delta = S * Sxx - Sx * Sx;
  *a = (Sxx * Sy - Sx * Sxy) / Delta;
  *b = (S * Sxy - Sx * Sy) / Delta;

  /*  fprintf('\n slope=%f Int=%f \n',b,a) */
  /*  Results.slope=b; */
  /*  Results.Intercept= a; */
  /*  y_fit = a + b*x; */
  /*    if t==2 */
  /*      h=plot(x,y,'rs','MarkerFaceColor','r'); */
  /*       title('Unweighted fit') */
  /*    else */
  /*       clf;set(gcf,'color','w'); */
  /*       h=errorbar(x,y,stdv,'rs','MarkerFaceColor','r'); */
  /*       title('Weighted fit') */
  /*    end */
  /*  hold on; q=plot(x,y_fit,'b.--','linewidth',2); */
  /*  xlabel('x (Column 1)') */
  /*  ylabel('y (Column 2)') */
  /*  legend([h(1),q(1)],'Data',sprintf('\nSlope=%f\nIntercept=%f\n',b,a),'location','Southeast')  */
  emxFree_real_T(&e_w);
}

/*
 * File trailer for weightedfit.c
 *
 * [EOF]
 */
