#-------------------------------------------------
#
# Project created by QtCreator 2013-08-15T15:19:12
#
#-------------------------------------------------

cache()

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlayDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    PlayStateText.cpp \
    Player.cpp \
    IState.cpp \
    IPlay.cpp \
    FileStreamPlayer.cpp \
    FilePlayer.cpp \
    dlgopenfile.cpp \
    dlgsetcolor.cpp \
    dlgsnappicsetting.cpp \
    dlgcutfile.cpp \
    dlglocate.cpp \
    dlgmediainfo.cpp \
    readdatathread.cpp

HEADERS  += mainwindow.h \
    PlayStateText.h \
    Player.h \
    IState.h \
    IPlay.h \
    FileStreamPlayer.h \
    FilePlayer.h \
    dhplay.h \
    dlgopenfile.h \
    dlgsetcolor.h \
    dlgsnappicsetting.h \
    dlgcutfile.h \
    dlglocate.h \
    dlgmediainfo.h \
    readdatathread.h \
    IWindowEvent.h

FORMS    += mainwindow.ui \
    dlgopenfile.ui \
    dlgsetcolor.ui \
    dlgsnappicsetting.ui \
    dlgcutfile.ui \
    dlglocate.ui \
    dlgmediainfo.ui

OTHER_FILES += \
    PlayDemo.pro.user

LIBS += -L$$PWD -ldhplay

RESOURCES += \
    resource.qrc
