#-------------------------------------------------
#
# Project created by QtCreator 2016-04-14T14:41:29
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RTPlot
TEMPLATE = app


SOURCES +=  src/main.cpp\
            src/mainwindow.cpp\
            src/inputparserthread.cpp\
            src/qcustomplot.cpp

HEADERS  += inc/mainwindow.h\
            inc/inputparserthread.h\
            inc/qcustomplot.h

FORMS    += mainwindow.ui

INCLUDEPATH += inc
