#-------------------------------------------------
#
# Project created by QtCreator 2012-11-10T15:49:32
#
#-------------------------------------------------
CONFIG += gui
QT       += core gui
QT      += widgets

TARGET = PTZControl
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
        cameracontroller.cpp \
    Ptz.cpp

HEADERS  += dialog.h \
    Ptz.h \
    UserDefine.h \
    dhnetsdk.h \
    dhassistant.h \
    cameracontroller.h

FORMS    += dialog.ui

win32:LIBS += '.\dhnetsdk.lib'
#unix:LIBS  += -L. -ldhdvr -ldhnetsdk
unix:LIBS  += -L. -ldhnetsdk

unix:!macx: LIBS += -L$$PWD/DLL/ -lavnetsdk

INCLUDEPATH += $$PWD/DLL
DEPENDPATH += $$PWD/DLL
