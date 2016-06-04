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
    libs/cycle_max/cycle_max.cpp \
    libs/cycle_max/cycle_max_emxAPI.cpp \
    libs/cycle_max/cycle_max_emxutil.cpp \
    libs/cycle_max/cycle_max_initialize.cpp \
    libs/cycle_max/cycle_max_terminate.cpp \
    libs/cycle_max/polyfit.cpp \
    libs/cycle_max/rt_nonfinite.cpp \
    libs/cycle_max/rtGetInf.cpp \
    libs/cycle_max/rtGetNaN.cpp \
    libs/cycle_max/sum.cpp \
    libs/cycle_max/xgeqp3.cpp \
    libs/cycle_max/xnrm2.cpp \
    queryDB.cpp

HEADERS  += \
    dataprocess.h \
    utils.h \
    dialog.h \
    libs/cycle_max/cycle_max_emxAPI.h \
    libs/cycle_max/cycle_max_initialize.h \
    libs/cycle_max/cycle_max_terminate.h \
    libs/cycle_max/cycle_max_emxutil.h \
    libs/cycle_max/cycle_max.h \
    libs/cycle_max/cycle_max_types.h \
    libs/cycle_max/polyfit.h \
    libs/cycle_max/rt_nonfinite.h \
    libs/cycle_max/rtGetInf.h \
    libs/cycle_max/rtGetNaN.h \
    libs/cycle_max/rtwtypes.h \
    libs/cycle_max/sum.h \
    libs/cycle_max/xgeqp3.h \
    libs/cycle_max/xnrm2.h \
    queryDB.h

FORMS    += \
    dialog.ui

#QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
#LIBS += -stdlib=libc++
#QMAKE_CXXFLAGS += -stdlib=libc++
