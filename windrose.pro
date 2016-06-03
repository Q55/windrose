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
        mainwindow.cpp \
    rawdatafromdb.cpp \
    preprocesswidget.cpp \
    postprocesswidget.cpp \
    dataprocess.cpp \
    utils.cpp

HEADERS  += mainwindow.h \
    rawdatafromdb.h \
    preprocesswidget.h \
    postprocesswidget.h \
    dataprocess.h \
    utils.h

FORMS    += mainwindow.ui \
    preprocesswidget.ui \
    postprocesswidget.ui \
    dialog.ui
