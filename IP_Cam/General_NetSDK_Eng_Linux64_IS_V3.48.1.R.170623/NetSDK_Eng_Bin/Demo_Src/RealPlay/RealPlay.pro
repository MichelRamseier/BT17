#-------------------------------------------------
#
# Project created by QtCreator 2012-11-09T10:25:01
#
#-------------------------------------------------

QT       += core gui
QT       += core gui
QT       += widgets

TARGET = RealPlay
TEMPLATE = app
#DEFINES += MAC

SOURCES += main.cpp\
        mainwindow.cpp \
    utility/Profile.cpp \
    utility/dhmutex.cpp

HEADERS  += mainwindow.h \
    utility/Profile.h \
    utility/dhmutex.h \
    UserDefine.h \
    dhnetsdk.h \
    dhassistant.h

FORMS    += mainwindow.ui

#win32:LIBS += D:\SVNcode\QtProj\RealPlay\lib\dhnetsdk.lib
##unix:LIBS  += -L. -ldhdvr -ldhnetsdk -lpthread
#unix:LIBS  += -L. -ldhnetsdk -lpthread

win32:LIBS += '.\dhnetsdk.lib'
#unix:LIBS  += -L. -ldhdvr -ldhnetsdk
unix:LIBS  += -L. -ldhnetsdk

unix:!macx: LIBS += -L$$PWD/../../DLL/ -lavnetsdk

INCLUDEPATH += $$PWD/../../DLL
DEPENDPATH += $$PWD/../../DLL
