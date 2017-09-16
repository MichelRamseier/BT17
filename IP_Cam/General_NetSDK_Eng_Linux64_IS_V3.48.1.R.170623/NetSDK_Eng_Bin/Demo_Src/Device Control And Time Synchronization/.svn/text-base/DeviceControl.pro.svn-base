#-------------------------------------------------
#
# Project created by QtCreator 2012-11-12T15:39:54
#
#-------------------------------------------------

QT       += core gui

TARGET = DeviceControl
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \

HEADERS  += dialog.h \
    UserDefine.h \
    dhnetsdk.h \
    dhassistant.h

FORMS    += dialog.ui

win32:LIBS += '.\dhnetsdk.lib'
#unix:LIBS  += -L. -ldhdvr -ldhnetsdk
unix:LIBS  += -L. -ldhnetsdk
