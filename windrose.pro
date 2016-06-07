#-------------------------------------------------
#
# Project created by QtCreator 2016-05-30T21:04:19
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = windrose
TEMPLATE = app

#INCLUDEPATH += /Users/lishiqiang/Developer/QtProject/windrose/libs/cycle_max

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
    formuladialog.cpp \
    scatterplot.cpp \
    curveplot.cpp \
    windroseplot.cpp \
    histogramplot.cpp

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
    formuladialog.h \
    scatterplot.h \
    curveplot.h \
    windroseplot.h \
    histogramplot.h

FORMS    += \
    dialog.ui \
    formuladialog.ui

#QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
#LIBS += -stdlib=libc++
#QMAKE_CXXFLAGS += -stdlib=libc++
