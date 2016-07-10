#-------------------------------------------------
#
# Project created by QtCreator 2016-05-30T21:04:19
#
#-------------------------------------------------
###### for qwt. changed reply on enviroment ##########
include (C:\Qwt-6.1.2\features\qwt.prf)
#include(/usr/local/qwt-6.1.2/features/qwt.prf)

QT       += core gui
QT       += sql
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = windrose
TEMPLATE = app

#INCLUDEPATH += /Users/lishiqiang/Developer/QtProject/windrose/libs/cycle_max
#INCLUDEPATH += /usr/local/qwtpolar-1.1.1/lib/qwtpolar.framework/Headers
#LIBS += /usr/local/qwtpolar-1.1.1/lib/qwtpolar.framework/qwtpolar

SOURCES += main.cpp\
    dataprocess.cpp \
    dialog.cpp \
    utils.cpp \
    queryDB.cpp \
    libs/commons/rt_nonfinite.cpp \
    libs/commons/rtGetInf.cpp \
    libs/commons/rtGetNaN.cpp \
    libs/commons/polyfit.cpp \
    libs/commons/sum.cpp \
    libs/commons/xgeqp3.cpp \
    libs/commons/xnrm2.cpp \
    libs/cycle_max/cycle_max_initialize.cpp \
    libs/cycle_max/cycle_max_terminate.cpp \
    libs/cycle_max/cycle_max.cpp \
    libs/inter_consis/inter_consis.cpp \
    libs/inter_consis/inter_consis_initialize.cpp \
    libs/inter_consis/inter_consis_terminate.cpp \
    libs/commons/emxAPI.cpp \
    libs/commons/emxutil.cpp \
    libs/correlation/correlation.cpp \
    libs/correlation/correlation_initialize.cpp \
    libs/correlation/correlation_terminate.cpp \
    libs/diraverage/diraverage.cpp \
    libs/diraverage/diraverage_initialize.cpp \
    libs/diraverage/diraverage_terminate.cpp \
    libs/commons/fft.cpp \
    libs/commons/floor.cpp \
    libs/commons/ifft.cpp \
    libs/commons/power.cpp \
    libs/commons/rdivide.cpp \
    libs/commons/sin.cpp \
    libs/commons/tan.cpp \
    libs/enpost/enpost.cpp \
    libs/enpost/enpost_initialize.cpp \
    libs/enpost/enpost_terminate.cpp \
    libs/filters/filters.cpp \
    libs/filters/filters_initialize.cpp \
    libs/filters/filters_terminate.cpp \
    libs/commons/cos.cpp \
    libs/range_check/range_check.cpp \
    libs/range_check/range_check_initialize.cpp \
    libs/range_check/range_check_terminate.cpp \
    libs/range_cont/range_cont.cpp \
    libs/range_cont/range_cont_initialize.cpp \
    libs/range_cont/range_cont_terminate.cpp \
    libs/spectral/spectral.cpp \
    libs/spectral/spectral_initialize.cpp \
    libs/spectral/spectral_terminate.cpp \
    libs/time_cont/time_cont.cpp \
    libs/time_cont/time_cont_initialize.cpp \
    libs/time_cont/time_cont_terminate.cpp \
    libs/weightedfit/weightedfit.cpp \
    libs/weightedfit/weightedfit_initialize.cpp \
    libs/weightedfit/weightedfit_terminate.cpp \
    libs/commons/diff.cpp \
    plot.cpp \
    calcexpression.cpp \
    postexprdialog.cpp \
    libs/commons/abs.cpp \
    libs/commons/fix.cpp \
    libs/commons/mod.cpp \
    libs/commons/gamma.cpp \
    libs/1D_max_entropy1/max_shang_one.cpp \
    libs/1D_max_entropy1/max_shang_one_initialize.cpp \
    libs/1D_max_entropy1/max_shang_one_terminate.cpp \
    qwtgraphplotcustom.cpp \
    qchartwindroseplot.cpp \
    chartview.cpp \
    libs/kendall/Kendall_initialize.cpp \
    libs/kendall/Kendall_terminate.cpp \
    libs/kendall/Kendall.cpp \
    libs/kendall/sortLE.cpp \
    libs/stats_1d/Statistics_1d_initialize.cpp \
    libs/stats_1d/Statistics_1d_terminate.cpp \
    libs/stats_1d/Statistics_1d.cpp \
    libs/stats_2d/Statistics_2d.cpp \
    libs/stats_2d/Statistics_2d_initialize.cpp \
    libs/stats_2d/Statistics_2d_sum.cpp \
    libs/stats_2d/Statistics_2d_terminate.cpp \
    libs/distr_F1/distr_F1.cpp \
    libs/distr_F1/distr_F1_initialize.cpp \
    libs/distr_F1/distr_F1_terminate.cpp \
    libs/distr_F2/distr_F2.cpp \
    libs/distr_F2/distr_F2_initialize.cpp \
    libs/distr_F2/distr_F2_terminate.cpp \
    libs/ff_AMH/ff_AMH.cpp \
    libs/ff_AMH/ff_AMH_initialize.cpp \
    libs/ff_AMH/ff_AMH_terminate.cpp \
    libs/ff_Gum/ff_Gum.cpp \
    libs/ff_Gum/ff_Gum_initialize.cpp \
    libs/ff_Gum/ff_Gum_terminate.cpp \
    libs/ff_Cla/ff_Cla.cpp \
    libs/ff_Cla/ff_Cla_initialize.cpp \
    libs/ff_Cla/ff_Cla_terminate.cpp \
    libs/ff_Fra/ff_Fra.cpp \
    libs/ff_Fra/ff_Fra_initialize.cpp \
    libs/ff_Fra/ff_Fra_terminate.cpp \
    libs/ff_GB/ff_GB.cpp \
    libs/ff_GB/ff_GB_initialize.cpp \
    libs/ff_GB/ff_GB_terminate.cpp \
    plotspectrogram.cpp \
    postcolrenamedialog.cpp \
    libs/fpso_motions/FPSO_MOTIONS_initialize.cpp \
    libs/fpso_motions/FPSO_MOTIONS_rtwutil.cpp \
    libs/fpso_motions/FPSO_MOTIONS_terminate.cpp \
    libs/fpso_motions/bsearch.cpp \
    libs/fpso_motions/exp.cpp \
    libs/fpso_motions/fliplr.cpp \
    libs/fpso_motions/flipud.cpp \
    libs/fpso_motions/FPSO_MOTIONS.cpp \
    libs/fpso_motions/interp1.cpp \
    libs/fpso_motions/mpower.cpp \
    libs/fpso_motions/mrdivide.cpp \
    libs/fpso_motions/qrsolve.cpp \
    libs/fpso_motions/sign.cpp \
    libs/fpso_motions/sortIdx.cpp \
    libs/fpso_motions/sqrt.cpp \
    libs/fpso_motions/trapz.cpp \
    libs/fpso_motions/unique.cpp \
    libs/fpso_motions/asin.cpp \
    libs/fpso_motions/sortrows.cpp \
    libs/fpso_motions/xzlarfg.cpp \
    libs/fpso_motions/fpso_sum.cpp \
    libs/fpso_motions/fpso_abs.cpp \
    libs/fpso_motions/fpso_power.cpp \
    libs/fpso_motions/fpso_sortLE.cpp \
    libs/fpso_motions/fpso_xgeqp3.cpp \
    libs/fpso_motions/fpso_rdivide.cpp \
    libs/fpso_motions/fpso_xnrm2.cpp

HEADERS  += \
    dataprocess.h \
    utils.h \
    dialog.h \
    queryDB.h \
    analyseparas.h \
    libs/commons/rt_nonfinite.h \
    libs/commons/rtGetInf.h \
    libs/commons/rtGetNaN.h \
    libs/commons/rtwtypes.h \
    libs/commons/polyfit.h \
    libs/commons/sum.h \
    libs/commons/xgeqp3.h \
    libs/commons/xnrm2.h \
    libs/cycle_max/cycle_max_initialize.h \
    libs/cycle_max/cycle_max_terminate.h \
    libs/cycle_max/cycle_max.h \
    libs/inter_consis/inter_consis_initialize.h \
    libs/inter_consis/inter_consis_terminate.h \
    libs/inter_consis/inter_consis.h \
    libs/commons/emxAPI.h \
    libs/commons/emxutil.h \
    libs/commons/types.h \
    libs/correlation/correlation_initialize.h \
    libs/correlation/correlation_terminate.h \
    libs/correlation/correlation.h \
    libs/diraverage/diraverage_terminate.h \
    libs/diraverage/diraverage.h \
    libs/diraverage/diraverage_initialize.h \
    libs/commons/floor.h \
    libs/commons/power.h \
    libs/commons/tan.h \
    libs/commons/rdivide.h \
    libs/commons/sin.h \
    libs/enpost/enpost_initialize.h \
    libs/enpost/enpost_terminate.h \
    libs/enpost/enpost.h \
    libs/commons/fft.h \
    libs/commons/ifft.h \
    libs/filters/filters_initialize.h \
    libs/filters/filters_terminate.h \
    libs/filters/filters.h \
    libs/commons/cos.h \
    libs/range_check/range_check_initialize.h \
    libs/range_check/range_check_terminate.h \
    libs/range_check/range_check.h \
    libs/range_cont/range_cont_initialize.h \
    libs/range_cont/range_cont_terminate.h \
    libs/range_cont/range_cont.h \
    libs/spectral/spectral_initialize.h \
    libs/spectral/spectral_terminate.h \
    libs/spectral/spectral.h \
    libs/commons/diff.h \
    libs/time_cont/time_cont_initialize.h \
    libs/time_cont/time_cont_terminate.h \
    libs/time_cont/time_cont.h \
    libs/weightedfit/weightedfit_initialize.h \
    libs/weightedfit/weightedfit_terminate.h \
    libs/weightedfit/weightedfit.h \
    plot.h \
    calcexpression.h \
    postexprdialog.h \
    libs/commons/fix.h \
    libs/commons/abs.h \
    libs/commons/mod.h \
    libs/1D_max_entropy1/max_shang_one_initialize.h \
    libs/1D_max_entropy1/max_shang_one_terminate.h \
    libs/1D_max_entropy1/max_shang_one.h \
    libs/commons/gamma.h \
    qwtgraphplotcustom.h \
    qchartwindroseplot.h \
    chartview.h \
    libs/kendall/Kendall_initialize.h \
    libs/kendall/Kendall_terminate.h \
    libs/kendall/Kendall.h \
    libs/kendall/sortLE.h \
    libs/stats_1d/Statistics_1d_initialize.h \
    libs/stats_1d/Statistics_1d_terminate.h \
    libs/stats_1d/Statistics_1d.h \
    libs/stats_2d/Statistics_2d_initialize.h \
    libs/stats_2d/Statistics_2d_sum.h \
    libs/stats_2d/Statistics_2d_terminate.h \
    libs/stats_2d/Statistics_2d.h \
    libs/distr_F1/distr_F1_initialize.h \
    libs/distr_F1/distr_F1_terminate.h \
    libs/distr_F1/distr_F1.h \
    libs/distr_F2/distr_F2_initialize.h \
    libs/distr_F2/distr_F2_terminate.h \
    libs/distr_F2/distr_F2.h \
    libs/ff_AMH/ff_AMH_initialize.h \
    libs/ff_AMH/ff_AMH_terminate.h \
    libs/ff_AMH/ff_AMH.h \
    libs/ff_Gum/ff_Gum_initialize.h \
    libs/ff_Gum/ff_Gum_terminate.h \
    libs/ff_Gum/ff_Gum.h \
    libs/ff_Cla/ff_Cla_initialize.h \
    libs/ff_Cla/ff_Cla_terminate.h \
    libs/ff_Cla/ff_Cla.h \
    libs/ff_Fra/ff_Fra_initialize.h \
    libs/ff_Fra/ff_Fra_terminate.h \
    libs/ff_Fra/ff_Fra.h \
    libs/ff_GB/ff_GB_initialize.h \
    libs/ff_GB/ff_GB_terminate.h \
    libs/ff_GB/ff_GB.h \
    plotspectrogram.h \
    postcolrenamedialog.h \
    libs/fpso_motions/FPSO_MOTIONS_initialize.h \
    libs/fpso_motions/FPSO_MOTIONS_rtwutil.h \
    libs/fpso_motions/FPSO_MOTIONS_terminate.h \
    libs/fpso_motions/bsearch.h \
    libs/fpso_motions/exp.h \
    libs/fpso_motions/fliplr.h \
    libs/fpso_motions/flipud.h \
    libs/fpso_motions/FPSO_MOTIONS.h \
    libs/fpso_motions/interp1.h \
    libs/fpso_motions/mpower.h \
    libs/fpso_motions/mrdivide.h \
    libs/fpso_motions/qrsolve.h \
    libs/fpso_motions/sign.h \
    libs/fpso_motions/sortIdx.h \
    libs/fpso_motions/sqrt.h \
    libs/fpso_motions/trapz.h \
    libs/fpso_motions/unique.h \
    libs/fpso_motions/asin.h \
    libs/fpso_motions/sortrows.h \
    libs/fpso_motions/xzlarfg.h \
    libs/fpso_motions/fpso_sum.h \
    libs/fpso_motions/fpso_abs.h \
    libs/fpso_motions/fpso_power.h \
    libs/fpso_motions/fpso_sortLE.h \
    libs/fpso_motions/fpso_xgeqp3.h \
    libs/fpso_motions/fpso_rdivide.h \
    libs/fpso_motions/fpso_xnrm2.h

FORMS    += \
    dialog.ui \
    postexprdialog.ui \
    postcolrenamedialog.ui

RESOURCES += \
    stylesheet.qrc

