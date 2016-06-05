/*
 * File: diraverage.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 12-May-2016 15:51:32
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "diraverage.h"
#include "libs/commons/emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *dir
 * Return Type  : double
 */
double diraverage(const emxArray_real_T *dir)
{
  double mean_dir;
  emxArray_real_T *dir_pic;
  int k;
  int loop_ub;
  int ii;
  double minus;
  double y;
  double temp;
  emxInit_real_T(&dir_pic, 1);
  k = dir_pic->size[0];
  dir_pic->size[0] = dir->size[0];
  emxEnsureCapacity((emxArray__common *)dir_pic, k, (int)sizeof(double));
  loop_ub = dir->size[0];
  for (k = 0; k < loop_ub; k++) {
    dir_pic->data[k] = 0.0;
  }

  dir_pic->data[0] = dir->data[0];
  for (ii = 0; ii <= dir->size[0] - 2; ii++) {
    minus = dir->data[1 + ii] - dir_pic->data[ii];
    if (minus < -180.0) {
      dir_pic->data[1 + ii] = (dir_pic->data[ii] + minus) + 360.0;
    } else if (minus > 180.0) {
      dir_pic->data[1 + ii] = (dir_pic->data[ii] + minus) - 360.0;
    } else {
      if (fabs(minus) < 180.0) {
        dir_pic->data[1 + ii] = dir_pic->data[ii] + minus;
      }
    }
  }

  if (dir_pic->size[0] == 0) {
    y = 0.0;
  } else {
    y = dir_pic->data[0];
    for (k = 2; k <= dir_pic->size[0]; k++) {
      y += dir_pic->data[k - 1];
    }
  }

  mean_dir = y / (double)dir_pic->size[0];
  temp = fabs(mean_dir / 360.0);
  emxFree_real_T(&dir_pic);
  if (temp - floor(temp / 360.0) * 360.0 == 0.0) {
    mean_dir = 0.0;
  } else if (temp < 1.0) {
    if (mean_dir < 0.0) {
      mean_dir += 360.0;
    }
  } else {
    if (temp >= 1.0) {
      if (mean_dir < 0.0) {
        mean_dir += 360.0 * ceil(temp);
      } else {
        mean_dir -= 360.0 * floor(temp);
      }
    }
  }

  return mean_dir;
}

/*
 * File trailer for diraverage.c
 *
 * [EOF]
 */
