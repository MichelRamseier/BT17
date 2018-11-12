#-------------------------------------------------
#
# Project created by QtCreator 2013-08-13T16:08:08
#
#-------------------------------------------------

cache()

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DecCB_demo
TEMPLATE = app


SOURCES += main.cpp\
        deccb_demo.cpp \
    displaywindow.cpp

HEADERS  += deccb_demo.h \
    displaywindow.h

FORMS    += deccb_demo.ui \
    displaywindow.ui

LIBS += -L$$PWD -ldhplay

