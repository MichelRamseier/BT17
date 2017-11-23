#-------------------------------------------------
#
# Project created by QtCreator 2012-11-10T15:49:32
#
#-------------------------------------------------

QT       += core gui

TARGET = PTZControl
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    Ptz.cpp

HEADERS  += dialog.h \
    Ptz.h \
    UserDefine.h \
    dhnetsdk.h \
    dhassistant.h

FORMS    += dialog.ui

win32:LIBS += '.\dhnetsdk.lib'
#unix:LIBS  += -L. -ldhdvr -ldhnetsdk
unix:LIBS  += -L. -ldhnetsdk
