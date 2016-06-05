/*
 * File: enpost.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 13-May-2016 08:54:51
 */

/* Include Files */
#include "libs/commons/rt_nonfinite.h"
#include "enpost.h"
#include "libs/commons/emxutil.h"
#include "libs/commons/cos.h"
#include "libs/commons/sin.h"
#include "libs/commons/floor.h"
#include "libs/commons/rdivide.h"
#include "libs/commons/power.h"
#include "libs/commons/tan.h"

/* Function Declarations */
static double rt_powd_snf(double u0, double u1);
static void wgs2utm(const emxArray_real_T *Lat, const emxArray_real_T *Lon,
                    emxArray_real_T *x, emxArray_real_T *y, emxArray_real_T
                    *utmzone);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d1;
  double d2;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d1 = fabs(u0);
    d2 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d1 == 1.0) {
        y = rtNaN;
      } else if (d1 > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d2 == 0.0) {
      y = 1.0;
    } else if (d2 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/*
 * -------------------------------------------------------------------------
 *  [x,y,utmzone] = wgs2utm(Lat,Lon)
 *
 *  Description:
 *     Convert WGS84 coordinates (Latitude, Longitude) into UTM coordinates
 *     (northing, easting).
 *
 *  Input:
 *     Lat: WGS84 Latitude scalar or vector in decimal degrees  纬度，十进制
 *     Lon: WGS84 Longitude scalar or vector in decimal degrees  经度，十进制
 *
 *  Output:
 *     x: UTM easting in meters
 *     y: UTM northing in meters
 *     utmzone: UTM longitudinal zone
 *
 *
 *  Example:
 *     Lat=[48.866667; 34.05;   -36.85 ];
 *     Lon=[2.333056;  -118.25; 174.783333];
 *     [x,y,utmzone] = wgs2utm(Lat,Lon)
 * Arguments    : const emxArray_real_T *Lat
 *                const emxArray_real_T *Lon
 *                emxArray_real_T *x
 *                emxArray_real_T *y
 *                emxArray_real_T *utmzone
 * Return Type  : void
 */
static void wgs2utm(const emxArray_real_T *Lat, const emxArray_real_T *Lon,
                    emxArray_real_T *x, emxArray_real_T *y, emxArray_real_T
                    *utmzone)
{
  emxArray_real_T *b_Lat;
  int i3;
  int k;
  emxArray_real_T *Lon0;
  emxArray_real_T *r10;
  emxArray_real_T *N;
  emxArray_real_T *T;
  emxArray_real_T *C;
  emxArray_real_T *b_Lon;
  emxArray_real_T *A;
  emxArray_real_T *b_Lon0;
  emxArray_real_T *r11;
  emxArray_real_T *r12;
  emxArray_real_T *r13;
  unsigned int A_idx_0;
  emxArray_real_T *r14;
  emxArray_real_T *r15;
  emxArray_real_T *r16;
  emxArray_real_T *r17;
  emxArray_real_T *r18;
  emxArray_real_T *r19;
  emxArray_real_T *r20;
  emxArray_real_T *r21;
  emxArray_real_T *r22;
  emxInit_real_T(&b_Lat, 1);

  /* 船尾海拔高度，单位米 */
  /* ------------------------------------------------------------------------- */
  /* % Argument checking */
  /*  error(nargchk(2, 2, nargin));  %2 arguments required */
  /*  n1=size(Lat); */
  /*  n2=size(Lon); */
  /*  if (n1~=n2) */
  /*     error('Lat and Lon should have same size');return */
  /*  end */
  /* % coordinates in radians */
  i3 = b_Lat->size[0];
  b_Lat->size[0] = Lat->size[0];
  emxEnsureCapacity((emxArray__common *)b_Lat, i3, (int)sizeof(double));
  k = Lat->size[0];
  for (i3 = 0; i3 < k; i3++) {
    b_Lat->data[i3] = Lat->data[i3] * 3.1415926535897931;
  }

  emxInit_real_T(&Lon0, 1);
  rdivide(b_Lat, 180.0, y);

  /* % WGS84 parameters */
  /* semi-major axis */
  /* semi-minor axis */
  /*  b = 6356752.314140;  %GRS80 value, originally used for WGS84 before refinements */
  /*  eccentricity */
  /* % UTM parameters */
  /*  lat0 = 0;                % reference latitude, not used here */
  rdivide(Lon, 6.0, Lon0);
  b_floor(Lon0);
  i3 = Lon0->size[0];
  emxEnsureCapacity((emxArray__common *)Lon0, i3, (int)sizeof(double));
  k = Lon0->size[0];
  emxFree_real_T(&b_Lat);
  for (i3 = 0; i3 < k; i3++) {
    Lon0->data[i3] = Lon0->data[i3] * 6.0 + 3.0;
  }

  emxInit_real_T(&r10, 1);

  /*  reference longitude in degrees */
  /*  in radians */
  /*  scale on central meridian */
  /*  false easting */
  /*  false northing  */
  /* % Equations parameters */
  /*  e prime square */
  /*  N: radius of curvature of the earth perpendicular to meridian plane */
  /*  Also, distance from point to polar axis */
  i3 = r10->size[0];
  r10->size[0] = y->size[0];
  emxEnsureCapacity((emxArray__common *)r10, i3, (int)sizeof(double));
  k = y->size[0];
  for (i3 = 0; i3 < k; i3++) {
    r10->data[i3] = y->data[i3];
  }

  b_sin(r10);
  power(r10, x);
  i3 = x->size[0];
  emxEnsureCapacity((emxArray__common *)x, i3, (int)sizeof(double));
  k = x->size[0];
  for (i3 = 0; i3 < k; i3++) {
    x->data[i3] = 1.0 - 0.0066943799901975076 * x->data[i3];
  }

  emxInit_real_T(&N, 1);
  i3 = N->size[0];
  N->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)N, i3, (int)sizeof(double));
  k = x->size[0];
  for (i3 = 0; i3 < k; i3++) {
    N->data[i3] = x->data[i3];
  }

  for (k = 0; k + 1 <= x->size[0]; k++) {
    N->data[k] = sqrt(N->data[k]);
  }

  i3 = N->size[0];
  emxEnsureCapacity((emxArray__common *)N, i3, (int)sizeof(double));
  k = N->size[0];
  for (i3 = 0; i3 < k; i3++) {
    N->data[i3] = 6.378137E+6 / N->data[i3];
  }

  i3 = r10->size[0];
  r10->size[0] = y->size[0];
  emxEnsureCapacity((emxArray__common *)r10, i3, (int)sizeof(double));
  k = y->size[0];
  for (i3 = 0; i3 < k; i3++) {
    r10->data[i3] = y->data[i3];
  }

  emxInit_real_T(&T, 1);
  b_tan(r10);
  power(r10, T);
  i3 = r10->size[0];
  r10->size[0] = y->size[0];
  emxEnsureCapacity((emxArray__common *)r10, i3, (int)sizeof(double));
  k = y->size[0];
  for (i3 = 0; i3 < k; i3++) {
    r10->data[i3] = y->data[i3];
  }

  emxInit_real_T(&C, 1);
  b_cos(r10);
  power(r10, C);
  i3 = C->size[0];
  emxEnsureCapacity((emxArray__common *)C, i3, (int)sizeof(double));
  k = C->size[0];
  for (i3 = 0; i3 < k; i3++) {
    C->data[i3] *= 0.0067394967423333859;
  }

  i3 = r10->size[0];
  r10->size[0] = y->size[0];
  emxEnsureCapacity((emxArray__common *)r10, i3, (int)sizeof(double));
  k = y->size[0];
  for (i3 = 0; i3 < k; i3++) {
    r10->data[i3] = y->data[i3];
  }

  emxInit_real_T(&b_Lon, 1);
  b_cos(r10);
  i3 = b_Lon->size[0];
  b_Lon->size[0] = Lon->size[0];
  emxEnsureCapacity((emxArray__common *)b_Lon, i3, (int)sizeof(double));
  k = Lon->size[0];
  for (i3 = 0; i3 < k; i3++) {
    b_Lon->data[i3] = Lon->data[i3] * 3.1415926535897931;
  }

  emxInit_real_T(&A, 1);
  emxInit_real_T(&b_Lon0, 1);
  rdivide(b_Lon, 180.0, A);
  i3 = b_Lon0->size[0];
  b_Lon0->size[0] = Lon0->size[0];
  emxEnsureCapacity((emxArray__common *)b_Lon0, i3, (int)sizeof(double));
  k = Lon0->size[0];
  emxFree_real_T(&b_Lon);
  for (i3 = 0; i3 < k; i3++) {
    b_Lon0->data[i3] = Lon0->data[i3] * 3.1415926535897931;
  }

  emxInit_real_T(&r11, 1);
  rdivide(b_Lon0, 180.0, r11);
  i3 = A->size[0];
  emxEnsureCapacity((emxArray__common *)A, i3, (int)sizeof(double));
  k = A->size[0];
  emxFree_real_T(&b_Lon0);
  for (i3 = 0; i3 < k; i3++) {
    A->data[i3] = (A->data[i3] - r11->data[i3]) * r10->data[i3];
  }

  /*  M: true distance along the central meridian from the equator to lat */
  i3 = r10->size[0];
  r10->size[0] = y->size[0];
  emxEnsureCapacity((emxArray__common *)r10, i3, (int)sizeof(double));
  k = y->size[0];
  for (i3 = 0; i3 < k; i3++) {
    r10->data[i3] = 2.0 * y->data[i3];
  }

  b_sin(r10);
  i3 = r10->size[0];
  emxEnsureCapacity((emxArray__common *)r10, i3, (int)sizeof(double));
  k = r10->size[0];
  for (i3 = 0; i3 < k; i3++) {
    r10->data[i3] *= 0.0025146070605398477;
  }

  i3 = r11->size[0];
  r11->size[0] = y->size[0];
  emxEnsureCapacity((emxArray__common *)r11, i3, (int)sizeof(double));
  k = y->size[0];
  for (i3 = 0; i3 < k; i3++) {
    r11->data[i3] = 4.0 * y->data[i3];
  }

  b_sin(r11);
  i3 = r11->size[0];
  emxEnsureCapacity((emxArray__common *)r11, i3, (int)sizeof(double));
  k = r11->size[0];
  for (i3 = 0; i3 < k; i3++) {
    r11->data[i3] *= 2.6390465943820355E-6;
  }

  emxInit_real_T(&r12, 1);
  i3 = r12->size[0];
  r12->size[0] = y->size[0];
  emxEnsureCapacity((emxArray__common *)r12, i3, (int)sizeof(double));
  k = y->size[0];
  for (i3 = 0; i3 < k; i3++) {
    r12->data[i3] = 6.0 * y->data[i3];
  }

  b_sin(r12);
  i3 = r12->size[0];
  emxEnsureCapacity((emxArray__common *)r12, i3, (int)sizeof(double));
  k = r12->size[0];
  for (i3 = 0; i3 < k; i3++) {
    r12->data[i3] *= 3.4180460866818588E-9;
  }

  emxInit_real_T(&r13, 1);

  /* % easting */
  A_idx_0 = (unsigned int)A->size[0];
  i3 = r13->size[0];
  r13->size[0] = (int)A_idx_0;
  emxEnsureCapacity((emxArray__common *)r13, i3, (int)sizeof(double));
  for (k = 0; k + 1 <= A->size[0]; k++) {
    r13->data[k] = rt_powd_snf(A->data[k], 3.0);
  }

  emxInit_real_T(&r14, 1);
  emxInit_real_T(&r15, 1);
  power(T, r14);
  k = A->size[0];
  i3 = r15->size[0];
  r15->size[0] = k;
  emxEnsureCapacity((emxArray__common *)r15, i3, (int)sizeof(double));
  for (k = 0; k + 1 <= A->size[0]; k++) {
    r15->data[k] = rt_powd_snf(A->data[k], 5.0);
  }

  emxInit_real_T(&r16, 1);
  i3 = r16->size[0];
  r16->size[0] = T->size[0];
  emxEnsureCapacity((emxArray__common *)r16, i3, (int)sizeof(double));
  k = T->size[0];
  for (i3 = 0; i3 < k; i3++) {
    r16->data[i3] = ((1.0 - T->data[i3]) + C->data[i3]) * r13->data[i3];
  }

  emxInit_real_T(&r17, 1);
  rdivide(r16, 6.0, x);
  i3 = r17->size[0];
  r17->size[0] = T->size[0];
  emxEnsureCapacity((emxArray__common *)r17, i3, (int)sizeof(double));
  k = T->size[0];
  emxFree_real_T(&r16);
  for (i3 = 0; i3 < k; i3++) {
    r17->data[i3] = ((((5.0 - 18.0 * T->data[i3]) + r14->data[i3]) + 72.0 *
                      C->data[i3]) - 0.39089081105533641) * r15->data[i3];
  }

  rdivide(r17, 120.0, r13);
  i3 = x->size[0];
  x->size[0] = N->size[0];
  emxEnsureCapacity((emxArray__common *)x, i3, (int)sizeof(double));
  k = N->size[0];
  emxFree_real_T(&r17);
  for (i3 = 0; i3 < k; i3++) {
    x->data[i3] = 500000.0 + 0.9996 * N->data[i3] * ((A->data[i3] + x->data[i3])
      + r13->data[i3]);
  }

  /* % northing  */
  /*  M(lat0) = 0 so not used in following formula */
  i3 = r13->size[0];
  r13->size[0] = y->size[0];
  emxEnsureCapacity((emxArray__common *)r13, i3, (int)sizeof(double));
  k = y->size[0];
  for (i3 = 0; i3 < k; i3++) {
    r13->data[i3] = y->data[i3];
  }

  b_tan(r13);
  power(C, r14);
  i3 = r14->size[0];
  emxEnsureCapacity((emxArray__common *)r14, i3, (int)sizeof(double));
  k = r14->size[0];
  for (i3 = 0; i3 < k; i3++) {
    r14->data[i3] *= 4.0;
  }

  k = A->size[0];
  i3 = r15->size[0];
  r15->size[0] = k;
  emxEnsureCapacity((emxArray__common *)r15, i3, (int)sizeof(double));
  for (k = 0; k + 1 <= A->size[0]; k++) {
    r15->data[k] = rt_powd_snf(A->data[k], 4.0);
  }

  emxInit_real_T(&r18, 1);
  emxInit_real_T(&r19, 1);
  emxInit_real_T(&r20, 1);
  power(A, r20);
  rdivide(r20, 2.0, r18);
  power(T, r20);
  k = A->size[0];
  i3 = r19->size[0];
  r19->size[0] = k;
  emxEnsureCapacity((emxArray__common *)r19, i3, (int)sizeof(double));
  for (k = 0; k + 1 <= A->size[0]; k++) {
    r19->data[k] = rt_powd_snf(A->data[k], 6.0);
  }

  emxFree_real_T(&A);
  emxInit_real_T(&r21, 1);
  i3 = r21->size[0];
  r21->size[0] = T->size[0];
  emxEnsureCapacity((emxArray__common *)r21, i3, (int)sizeof(double));
  k = T->size[0];
  for (i3 = 0; i3 < k; i3++) {
    r21->data[i3] = (((5.0 - T->data[i3]) + 9.0 * C->data[i3]) + r14->data[i3]) *
      r15->data[i3];
  }

  emxInit_real_T(&r22, 1);
  rdivide(r21, 24.0, r14);
  i3 = r22->size[0];
  r22->size[0] = T->size[0];
  emxEnsureCapacity((emxArray__common *)r22, i3, (int)sizeof(double));
  k = T->size[0];
  emxFree_real_T(&r21);
  for (i3 = 0; i3 < k; i3++) {
    r22->data[i3] = ((((61.0 - 58.0 * T->data[i3]) + r20->data[i3]) + 600.0 *
                      C->data[i3]) - 2.2240339249700174) * r19->data[i3];
  }

  emxFree_real_T(&r20);
  emxFree_real_T(&r19);
  emxFree_real_T(&C);
  emxFree_real_T(&T);
  rdivide(r22, 720.0, r15);
  i3 = y->size[0];
  y->size[0] = Lat->size[0];
  emxEnsureCapacity((emxArray__common *)y, i3, (int)sizeof(double));
  k = Lat->size[0];
  emxFree_real_T(&r22);
  for (i3 = 0; i3 < k; i3++) {
    y->data[i3] = ((double)(Lat->data[i3] < 0.0) * 1.0E+7 + 0.9996 *
                   (6.378137E+6 * (((0.99832429845278126 * y->data[i3] -
      r10->data[i3]) + r11->data[i3]) - r12->data[i3]))) + 0.9996 * N->data[i3] *
      r13->data[i3] * ((r18->data[i3] + r14->data[i3]) + r15->data[i3]);
  }

  emxFree_real_T(&r12);
  emxFree_real_T(&r11);
  emxFree_real_T(&r10);
  emxFree_real_T(&r18);
  emxFree_real_T(&r15);
  emxFree_real_T(&r14);
  emxFree_real_T(&r13);
  emxFree_real_T(&N);

  /* % UTM zone */
  rdivide(Lon0, 6.0, utmzone);
  b_floor(utmzone);
  i3 = utmzone->size[0];
  emxEnsureCapacity((emxArray__common *)utmzone, i3, (int)sizeof(double));
  k = utmzone->size[0];
  emxFree_real_T(&Lon0);
  for (i3 = 0; i3 < k; i3++) {
    utmzone->data[i3] += 31.0;
  }
}

/*
 * example
 *   [spx,spmy,spmz,aftx,afty,aftz]=enpost(39.0148446,121.5347176,0,0,0,45)
 *   [spx,spmy,spmz,aftx,afty,aftz]=enpost(39.0148446,121.5347176,0,0,90,45)
 * ======input==================
 *  Lat，gps/imu输出的纬度，十进制；
 *  Lon，gps/imu输出的经度，十进制；
 *  roll,gps/imu输出的横摇，十进制
 *  pitch,gps/imu输出的纵摇，十进制
 *  heading,gps/imu输出的艏向，十进制
 *  altitude,gps/imu输出的海拔高度，十进制
 * ======output=================
 * Arguments    : const emxArray_real_T *Lat
 *                const emxArray_real_T *Lon
 *                emxArray_real_T *roll
 *                emxArray_real_T *pitch
 *                const emxArray_real_T *heading
 *                const emxArray_real_T *altitude
 *                double *spmx
 *                double *spmy
 *                double *spmz
 *                double *Aftx
 *                double *Afty
 *                double *Aftz
 * Return Type  : void
 */
void enpost(const emxArray_real_T *Lat, const emxArray_real_T *Lon,
            emxArray_real_T *roll, emxArray_real_T *pitch, const emxArray_real_T
            *heading, const emxArray_real_T *altitude, double *spmx, double
            *spmy, double *spmz, double *Aftx, double *Afty, double *Aftz)
{
  emxArray_real_T *b_roll;
  int i0;
  int loop_ub;
  emxArray_real_T *b_pitch;
  emxArray_real_T *b_heading;
  emxArray_real_T *yaw;
  emxArray_real_T *mx;
  emxArray_real_T *my;
  emxArray_real_T *mzone;
  emxArray_real_T *r0;
  emxArray_real_T *r1;
  emxArray_real_T *r2;
  emxArray_real_T *r3;
  emxArray_real_T *r4;
  emxArray_real_T *r5;
  emxArray_real_T *r6;
  emxArray_real_T *r7;
  emxArray_real_T *r8;
  emxArray_real_T *r9;
  double b_mzone[9];
  double dv0[9];
  static const signed char iv0[3] = { 0, 0, 1 };

  static const signed char iv1[3] = { 0, 1, 0 };

  double c_mzone[9];
  double dv1[9];
  int i1;
  static const signed char iv2[3] = { 1, 0, 0 };

  double D[9];
  emxArray_real_T *b_mx;
  double spm[3];
  double d0;
  static const double b[3] = { 0.0, 204.29999999999998, -24.35 };

  emxArray_real_T *c_mx;
  double Aft[3];
  static const double b_b[3] = { 0.0, 0.0, -24.35 };

  emxInit_real_T(&b_roll, 1);

  /* this script is ucsed to transfer the gps lattitude and longitude to utm coordinates */
  /* the spm position is calculated from the measured data */
  /*  */
  /* clear;clc; */
  /*  */
  /*  spmx，单点中心东向坐标，单位米； */
  /*  spmy，单点中心北向坐标，单位米； */
  /*  spmz, 单点主甲板面海拔高度，单位米 */
  /*  Aftx, 船尾主甲板中心线东向坐标，单位米 */
  /*  Afty, 船尾主甲板中心线北向坐标，单位米 */
  /*  Aftz, 船尾主甲板中心线海拔高度，单位米 */
  /*            *************************** */
  /*          *             X |           * */
  /*  BOW  *      O   Y <-----            * Aft */
  /*          *                           * */
  /*            *************************** */
  /* 大地坐标系 */
  i0 = b_roll->size[0];
  b_roll->size[0] = roll->size[0];
  emxEnsureCapacity((emxArray__common *)b_roll, i0, (int)sizeof(double));
  loop_ub = roll->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_roll->data[i0] = roll->data[i0] * 3.1415926535897931;
  }

  emxInit_real_T(&b_pitch, 1);
  rdivide(b_roll, 180.0, roll);

  /* roll; %gps/imu 输出横摇角roll，单位弧度 */
  i0 = b_pitch->size[0];
  b_pitch->size[0] = pitch->size[0];
  emxEnsureCapacity((emxArray__common *)b_pitch, i0, (int)sizeof(double));
  loop_ub = pitch->size[0];
  emxFree_real_T(&b_roll);
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_pitch->data[i0] = pitch->data[i0] * 3.1415926535897931;
  }

  emxInit_real_T(&b_heading, 1);
  rdivide(b_pitch, 180.0, pitch);

  /* pitch;%gps/imu输出纵摇角pitch，单位弧度 */
  i0 = b_heading->size[0];
  b_heading->size[0] = heading->size[0];
  emxEnsureCapacity((emxArray__common *)b_heading, i0, (int)sizeof(double));
  loop_ub = heading->size[0];
  emxFree_real_T(&b_pitch);
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_heading->data[i0] = heading->data[i0] * 3.1415926535897931;
  }

  emxInit_real_T(&yaw, 1);
  emxInit_real_T(&mx, 1);
  emxInit_real_T(&my, 1);
  emxInit_real_T(&mzone, 1);
  rdivide(b_heading, 180.0, yaw);

  /* heading;%gps/imu输出艏向角heading，单位弧度 */
  /* altitude;%gps/imu输出海拔高度 */
  /* ================================================================ */
  /* 船体坐标系 */
  /* 单点 */
  /* 局部坐标系下,单点相对测点X向坐标，单位米 */
  /* 局部坐标系下,单点相对测点Y向坐标，单位米 */
  /* 局部坐标系下,单点相对测点Z向坐标，单位米 */
  /* 船尾 */
  /* 局部坐标系下，测点投影至主甲板X向坐标，单位米 */
  /* 局部坐标系系下，测点投影至主甲板Y向坐标，单位米 */
  /* 局部坐标系，测点投影至主甲板Z向坐标，单位米 */
  /*  Lat=39.0148446; */
  /*  Lon=121.5347176; */
  wgs2utm(Lat, Lon, mx, my, mzone);

  /* 将测点经纬度转换成大地坐标系 */
  /* 船体坐标系到大地坐标系转换矩阵 */
  i0 = mzone->size[0];
  mzone->size[0] = yaw->size[0];
  emxEnsureCapacity((emxArray__common *)mzone, i0, (int)sizeof(double));
  loop_ub = yaw->size[0];
  emxFree_real_T(&b_heading);
  for (i0 = 0; i0 < loop_ub; i0++) {
    mzone->data[i0] = yaw->data[i0];
  }

  emxInit_real_T(&r0, 1);
  b_cos(mzone);
  i0 = r0->size[0];
  r0->size[0] = yaw->size[0];
  emxEnsureCapacity((emxArray__common *)r0, i0, (int)sizeof(double));
  loop_ub = yaw->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r0->data[i0] = yaw->data[i0];
  }

  b_sin(r0);
  i0 = r0->size[0];
  emxEnsureCapacity((emxArray__common *)r0, i0, (int)sizeof(double));
  loop_ub = r0->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r0->data[i0] = -r0->data[i0];
  }

  emxInit_real_T(&r1, 1);
  i0 = r1->size[0];
  r1->size[0] = yaw->size[0];
  emxEnsureCapacity((emxArray__common *)r1, i0, (int)sizeof(double));
  loop_ub = yaw->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r1->data[i0] = yaw->data[i0];
  }

  emxInit_real_T(&r2, 1);
  b_sin(r1);
  b_cos(yaw);

  /* 绕Z轴旋转，转换矩阵 */
  i0 = r2->size[0];
  r2->size[0] = roll->size[0];
  emxEnsureCapacity((emxArray__common *)r2, i0, (int)sizeof(double));
  loop_ub = roll->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r2->data[i0] = roll->data[i0];
  }

  emxInit_real_T(&r3, 1);
  b_cos(r2);
  i0 = r3->size[0];
  r3->size[0] = roll->size[0];
  emxEnsureCapacity((emxArray__common *)r3, i0, (int)sizeof(double));
  loop_ub = roll->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r3->data[i0] = roll->data[i0];
  }

  emxInit_real_T(&r4, 1);
  b_sin(r3);
  i0 = r4->size[0];
  r4->size[0] = roll->size[0];
  emxEnsureCapacity((emxArray__common *)r4, i0, (int)sizeof(double));
  loop_ub = roll->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r4->data[i0] = roll->data[i0];
  }

  b_sin(r4);
  i0 = r4->size[0];
  emxEnsureCapacity((emxArray__common *)r4, i0, (int)sizeof(double));
  loop_ub = r4->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r4->data[i0] = -r4->data[i0];
  }

  emxInit_real_T(&r5, 1);
  i0 = r5->size[0];
  r5->size[0] = roll->size[0];
  emxEnsureCapacity((emxArray__common *)r5, i0, (int)sizeof(double));
  loop_ub = roll->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r5->data[i0] = roll->data[i0];
  }

  emxInit_real_T(&r6, 1);
  b_cos(r5);

  /* 绕y轴旋转，转换矩阵 */
  i0 = r6->size[0];
  r6->size[0] = pitch->size[0];
  emxEnsureCapacity((emxArray__common *)r6, i0, (int)sizeof(double));
  loop_ub = pitch->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r6->data[i0] = pitch->data[i0];
  }

  emxInit_real_T(&r7, 1);
  b_cos(r6);
  i0 = r7->size[0];
  r7->size[0] = pitch->size[0];
  emxEnsureCapacity((emxArray__common *)r7, i0, (int)sizeof(double));
  loop_ub = pitch->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r7->data[i0] = pitch->data[i0];
  }

  b_sin(r7);
  i0 = r7->size[0];
  emxEnsureCapacity((emxArray__common *)r7, i0, (int)sizeof(double));
  loop_ub = r7->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r7->data[i0] = -r7->data[i0];
  }

  emxInit_real_T(&r8, 1);
  i0 = r8->size[0];
  r8->size[0] = pitch->size[0];
  emxEnsureCapacity((emxArray__common *)r8, i0, (int)sizeof(double));
  loop_ub = pitch->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r8->data[i0] = pitch->data[i0];
  }

  emxInit_real_T(&r9, 1);
  b_sin(r8);
  i0 = r9->size[0];
  r9->size[0] = pitch->size[0];
  emxEnsureCapacity((emxArray__common *)r9, i0, (int)sizeof(double));
  loop_ub = pitch->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r9->data[i0] = pitch->data[i0];
  }

  b_cos(r9);

  /* 绕x轴旋转，转换矩阵 */
  b_mzone[0] = mzone->data[0];
  b_mzone[3] = r0->data[0];
  b_mzone[6] = 0.0;
  b_mzone[1] = r1->data[0];
  b_mzone[4] = yaw->data[0];
  b_mzone[7] = 0.0;
  emxFree_real_T(&r0);
  emxFree_real_T(&r1);
  emxFree_real_T(&mzone);
  emxFree_real_T(&yaw);
  for (i0 = 0; i0 < 3; i0++) {
    b_mzone[2 + 3 * i0] = iv0[i0];
  }

  dv0[0] = r2->data[0];
  dv0[3] = 0.0;
  dv0[6] = r3->data[0];
  emxFree_real_T(&r3);
  emxFree_real_T(&r2);
  for (i0 = 0; i0 < 3; i0++) {
    dv0[1 + 3 * i0] = iv1[i0];
  }

  dv0[2] = r4->data[0];
  dv0[5] = 0.0;
  dv0[8] = r5->data[0];
  emxFree_real_T(&r4);
  emxFree_real_T(&r5);
  for (i0 = 0; i0 < 3; i0++) {
    for (loop_ub = 0; loop_ub < 3; loop_ub++) {
      c_mzone[i0 + 3 * loop_ub] = 0.0;
      for (i1 = 0; i1 < 3; i1++) {
        c_mzone[i0 + 3 * loop_ub] += b_mzone[i0 + 3 * i1] * dv0[i1 + 3 * loop_ub];
      }
    }

    dv1[3 * i0] = iv2[i0];
  }

  dv1[1] = 0.0;
  dv1[4] = r6->data[0];
  dv1[7] = r7->data[0];
  dv1[2] = 0.0;
  dv1[5] = r8->data[0];
  dv1[8] = r9->data[0];
  emxFree_real_T(&r7);
  emxFree_real_T(&r9);
  emxFree_real_T(&r8);
  emxFree_real_T(&r6);
  for (i0 = 0; i0 < 3; i0++) {
    for (loop_ub = 0; loop_ub < 3; loop_ub++) {
      D[i0 + 3 * loop_ub] = 0.0;
      for (i1 = 0; i1 < 3; i1++) {
        D[i0 + 3 * loop_ub] += c_mzone[i0 + 3 * i1] * dv1[i1 + 3 * loop_ub];
      }
    }
  }

  emxInit_real_T(&b_mx, 1);

  /* 转换矩阵 */
  i0 = b_mx->size[0];
  b_mx->size[0] = (mx->size[0] + my->size[0]) + altitude->size[0];
  emxEnsureCapacity((emxArray__common *)b_mx, i0, (int)sizeof(double));
  loop_ub = mx->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_mx->data[i0] = mx->data[i0];
  }

  loop_ub = my->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_mx->data[i0 + mx->size[0]] = my->data[i0];
  }

  loop_ub = altitude->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_mx->data[(i0 + mx->size[0]) + my->size[0]] = altitude->data[i0];
  }

  for (i0 = 0; i0 < 3; i0++) {
    d0 = 0.0;
    for (loop_ub = 0; loop_ub < 3; loop_ub++) {
      d0 += D[i0 + 3 * loop_ub] * b[loop_ub];
    }

    spm[i0] = b_mx->data[i0] + d0;
  }

  emxFree_real_T(&b_mx);
  emxInit_real_T(&c_mx, 1);
  i0 = c_mx->size[0];
  c_mx->size[0] = (mx->size[0] + my->size[0]) + altitude->size[0];
  emxEnsureCapacity((emxArray__common *)c_mx, i0, (int)sizeof(double));
  loop_ub = mx->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    c_mx->data[i0] = mx->data[i0];
  }

  loop_ub = my->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    c_mx->data[i0 + mx->size[0]] = my->data[i0];
  }

  loop_ub = altitude->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    c_mx->data[(i0 + mx->size[0]) + my->size[0]] = altitude->data[i0];
  }

  emxFree_real_T(&my);
  emxFree_real_T(&mx);
  for (i0 = 0; i0 < 3; i0++) {
    d0 = 0.0;
    for (loop_ub = 0; loop_ub < 3; loop_ub++) {
      d0 += D[i0 + 3 * loop_ub] * b_b[loop_ub];
    }

    Aft[i0] = c_mx->data[i0] + d0;
  }

  emxFree_real_T(&c_mx);
  *spmx = spm[0];

  /* 单点中心东向坐标，单位米 */
  *spmy = spm[1];

  /* 单点中心北向坐标，单位米 */
  *spmz = spm[2];

  /* 单点中心高度（主甲板），单位米 */
  *Aftx = Aft[0];

  /* 船尾东向坐标，单位米 */
  *Afty = Aft[1];

  /* 船尾北向坐标，单位米 */
  *Aftz = Aft[2];
}

/*
 * File trailer for enpost.c
 *
 * [EOF]
 */
