/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionClose;
    QAction *actionSnapPicture;
    QAction *actionLocate;
    QAction *actionCutFile;
    QAction *actionMediaInfo;
    QAction *actionVecticalSync;
    QAction *actionIVS;
    QAction *actionHwaccel;
    QWidget *centralWidget;
    QFrame *Display;
    QPushButton *Play;
    QPushButton *Pause;
    QPushButton *Stop;
    QPushButton *ToBegin;
    QPushButton *ToEnd;
    QPushButton *StepBackOne;
    QPushButton *StepGo;
    QPushButton *Slow;
    QPushButton *Fast;
    QPushButton *Backword;
    QPushButton *Forword;
    QPushButton *SnapPicture;
    QPushButton *SetColor;
    QSlider *Process;
    QTextEdit *state;
    QPushButton *SetVolume;
    QSlider *Volume;
    QSlider *AdjustWave;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSetting;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(670, 590);
        MainWindow->setMinimumSize(QSize(670, 590));
        MainWindow->setMaximumSize(QSize(670, 590));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionSnapPicture = new QAction(MainWindow);
        actionSnapPicture->setObjectName(QStringLiteral("actionSnapPicture"));
        actionLocate = new QAction(MainWindow);
        actionLocate->setObjectName(QStringLiteral("actionLocate"));
        actionCutFile = new QAction(MainWindow);
        actionCutFile->setObjectName(QStringLiteral("actionCutFile"));
        actionMediaInfo = new QAction(MainWindow);
        actionMediaInfo->setObjectName(QStringLiteral("actionMediaInfo"));
        actionVecticalSync = new QAction(MainWindow);
        actionVecticalSync->setObjectName(QStringLiteral("actionVecticalSync"));
        actionIVS = new QAction(MainWindow);
        actionIVS->setObjectName(QStringLiteral("actionIVS"));
        actionHwaccel = new QAction(MainWindow);
        actionHwaccel->setObjectName(QStringLiteral("actionHwaccel"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Display = new QFrame(centralWidget);
        Display->setObjectName(QStringLiteral("Display"));
        Display->setGeometry(QRect(3, 1, 665, 450));
        Display->setFrameShape(QFrame::StyledPanel);
        Display->setFrameShadow(QFrame::Raised);
        Play = new QPushButton(centralWidget);
        Play->setObjectName(QStringLiteral("Play"));
        Play->setGeometry(QRect(10, 490, 23, 23));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/icon/Res/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        Play->setIcon(icon);
        Play->setIconSize(QSize(23, 23));
        Pause = new QPushButton(centralWidget);
        Pause->setObjectName(QStringLiteral("Pause"));
        Pause->setGeometry(QRect(40, 490, 23, 23));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/icon/Res/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        Pause->setIcon(icon1);
        Pause->setIconSize(QSize(23, 23));
        Stop = new QPushButton(centralWidget);
        Stop->setObjectName(QStringLiteral("Stop"));
        Stop->setGeometry(QRect(70, 490, 23, 23));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/res/icon/Res/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        Stop->setIcon(icon2);
        Stop->setIconSize(QSize(23, 23));
        ToBegin = new QPushButton(centralWidget);
        ToBegin->setObjectName(QStringLiteral("ToBegin"));
        ToBegin->setGeometry(QRect(100, 490, 23, 23));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/res/icon/Res/tobegin.png"), QSize(), QIcon::Normal, QIcon::Off);
        ToBegin->setIcon(icon3);
        ToBegin->setIconSize(QSize(23, 23));
        ToEnd = new QPushButton(centralWidget);
        ToEnd->setObjectName(QStringLiteral("ToEnd"));
        ToEnd->setGeometry(QRect(130, 490, 23, 23));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/res/icon/Res/toend.png"), QSize(), QIcon::Normal, QIcon::Off);
        ToEnd->setIcon(icon4);
        ToEnd->setIconSize(QSize(23, 23));
        StepBackOne = new QPushButton(centralWidget);
        StepBackOne->setObjectName(QStringLiteral("StepBackOne"));
        StepBackOne->setGeometry(QRect(160, 490, 23, 23));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/res/icon/Res/onebyoneback.png"), QSize(), QIcon::Normal, QIcon::Off);
        StepBackOne->setIcon(icon5);
        StepBackOne->setIconSize(QSize(23, 23));
        StepGo = new QPushButton(centralWidget);
        StepGo->setObjectName(QStringLiteral("StepGo"));
        StepGo->setGeometry(QRect(190, 490, 23, 23));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/res/icon/Res/playonebyone.png"), QSize(), QIcon::Normal, QIcon::Off);
        StepGo->setIcon(icon6);
        StepGo->setIconSize(QSize(23, 23));
        Slow = new QPushButton(centralWidget);
        Slow->setObjectName(QStringLiteral("Slow"));
        Slow->setGeometry(QRect(220, 490, 23, 23));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/res/icon/Res/slow.png"), QSize(), QIcon::Normal, QIcon::Off);
        Slow->setIcon(icon7);
        Slow->setIconSize(QSize(23, 23));
        Fast = new QPushButton(centralWidget);
        Fast->setObjectName(QStringLiteral("Fast"));
        Fast->setGeometry(QRect(250, 490, 23, 23));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/res/icon/Res/fast.png"), QSize(), QIcon::Normal, QIcon::Off);
        Fast->setIcon(icon8);
        Fast->setIconSize(QSize(23, 23));
        Backword = new QPushButton(centralWidget);
        Backword->setObjectName(QStringLiteral("Backword"));
        Backword->setGeometry(QRect(310, 490, 23, 23));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/res/icon/Res/play_backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        Backword->setIcon(icon9);
        Backword->setIconSize(QSize(23, 23));
        Forword = new QPushButton(centralWidget);
        Forword->setObjectName(QStringLiteral("Forword"));
        Forword->setGeometry(QRect(340, 490, 23, 23));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/res/icon/Res/play_forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        Forword->setIcon(icon10);
        Forword->setIconSize(QSize(23, 23));
        SnapPicture = new QPushButton(centralWidget);
        SnapPicture->setObjectName(QStringLiteral("SnapPicture"));
        SnapPicture->setGeometry(QRect(400, 490, 23, 23));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/res/icon/Res/catchpic.png"), QSize(), QIcon::Normal, QIcon::Off);
        SnapPicture->setIcon(icon11);
        SnapPicture->setIconSize(QSize(23, 23));
        SetColor = new QPushButton(centralWidget);
        SetColor->setObjectName(QStringLiteral("SetColor"));
        SetColor->setGeometry(QRect(430, 490, 23, 23));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/res/icon/Res/color.png"), QSize(), QIcon::Normal, QIcon::Off);
        SetColor->setIcon(icon12);
        SetColor->setIconSize(QSize(23, 23));
        Process = new QSlider(centralWidget);
        Process->setObjectName(QStringLiteral("Process"));
        Process->setGeometry(QRect(10, 460, 651, 22));
        Process->setOrientation(Qt::Horizontal);
        state = new QTextEdit(centralWidget);
        state->setObjectName(QStringLiteral("state"));
        state->setGeometry(QRect(10, 530, 651, 31));
        state->setReadOnly(true);
        SetVolume = new QPushButton(centralWidget);
        SetVolume->setObjectName(QStringLiteral("SetVolume"));
        SetVolume->setGeometry(QRect(491, 486, 31, 31));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/res/icon/Res/sound.png"), QSize(), QIcon::Normal, QIcon::Off);
        SetVolume->setIcon(icon13);
        SetVolume->setIconSize(QSize(23, 23));
        Volume = new QSlider(centralWidget);
        Volume->setObjectName(QStringLiteral("Volume"));
        Volume->setGeometry(QRect(530, 484, 131, 17));
        Volume->setOrientation(Qt::Horizontal);
        AdjustWave = new QSlider(centralWidget);
        AdjustWave->setObjectName(QStringLiteral("AdjustWave"));
        AdjustWave->setGeometry(QRect(530, 502, 131, 22));
        AdjustWave->setOrientation(Qt::Horizontal);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 670, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuSetting = new QMenu(menuBar);
        menuSetting->setObjectName(QStringLiteral("menuSetting"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSetting->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionClose);
        menuSetting->addAction(actionSnapPicture);
        menuSetting->addAction(actionLocate);
        menuSetting->addAction(actionCutFile);
        menuSetting->addAction(actionMediaInfo);
        menuSetting->addAction(actionIVS);
        menuSetting->addAction(actionHwaccel);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
        actionClose->setText(QApplication::translate("MainWindow", "Close", Q_NULLPTR));
        actionSnapPicture->setText(QApplication::translate("MainWindow", "Snap Picture", Q_NULLPTR));
        actionLocate->setText(QApplication::translate("MainWindow", "Locate", Q_NULLPTR));
        actionCutFile->setText(QApplication::translate("MainWindow", "Cut File", Q_NULLPTR));
        actionMediaInfo->setText(QApplication::translate("MainWindow", "Media Info", Q_NULLPTR));
        actionVecticalSync->setText(QApplication::translate("MainWindow", "VecticalSync", Q_NULLPTR));
        actionIVS->setText(QApplication::translate("MainWindow", "IVS", Q_NULLPTR));
        actionHwaccel->setText(QApplication::translate("MainWindow", "Hwaccel", Q_NULLPTR));
        Play->setText(QString());
        Pause->setText(QString());
        Stop->setText(QString());
        ToBegin->setText(QString());
        ToEnd->setText(QString());
        StepBackOne->setText(QString());
        StepGo->setText(QString());
        Slow->setText(QString());
        Fast->setText(QString());
        Backword->setText(QString());
        Forword->setText(QString());
        SnapPicture->setText(QString());
        SetColor->setText(QString());
        SetVolume->setText(QString());
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuSetting->setTitle(QApplication::translate("MainWindow", "Setting", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
