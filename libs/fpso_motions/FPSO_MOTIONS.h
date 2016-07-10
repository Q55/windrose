/*
 * File: FPSO_MOTIONS.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 06-Jul-2016 09:17:50
 */

#ifndef __FPSO_MOTIONS_H__
#define __FPSO_MOTIONS_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "libs/commons/rt_nonfinite.h"
#include "libs/commons/rtwtypes.h"
#include "libs/commons/types.h"

/* Function Declarations */
extern void FPSO_MOTIONS(double Hs, double Tp, double dir_wave, double Vw,
  double dir_win, double Vc, double dir_cur, double draft_aft, double draft_bow,
  double *heading, double *statoffset, double *maxoffset_ind, double *clearance,
  double *maxTx, double *maxTe, double *Sf, double st_xforce[24], double
  st_tension[24], double st_sf[24], double st_offset[24], double st_clearance[24],
  double st_roll[24], double st_pitch[24]);

#endif

/*
 * File trailer for FPSO_MOTIONS.h
 *
 * [EOF]
 */
