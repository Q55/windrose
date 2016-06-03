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


SOURCES += main.cpp\
    rawdatafromdb.cpp \
    dataprocess.cpp \
    utils.cpp \
    dialog.cpp

HEADERS  += \
    rawdatafromdb.h \
    dataprocess.h \
    utils.h \
    dialog.h

FORMS    += \
    dialog.ui
