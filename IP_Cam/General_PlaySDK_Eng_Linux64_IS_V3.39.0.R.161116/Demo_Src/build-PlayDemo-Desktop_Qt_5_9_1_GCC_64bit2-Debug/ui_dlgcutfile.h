/********************************************************************************
** Form generated from reading UI file 'dlgcutfile.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGCUTFILE_H
#define UI_DLGCUTFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dlgCutFile
{
public:
    QLabel *labelShow;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *frameNumType;
    QRadioButton *timeType;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *labelDef1;
    QLabel *labelDef2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *inputValueBegin;
    QLineEdit *realValueBegin;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *inputValueEnd;
    QLineEdit *realValueEnd;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnCancel;
    QPushButton *btnSave;

    void setupUi(QDialog *dlgCutFile)
    {
        if (dlgCutFile->objectName().isEmpty())
            dlgCutFile->setObjectName(QStringLiteral("dlgCutFile"));
        dlgCutFile->resize(280, 276);
        dlgCutFile->setMaximumSize(QSize(280, 276));
        labelShow = new QLabel(dlgCutFile);
        labelShow->setObjectName(QStringLiteral("labelShow"));
        labelShow->setGeometry(QRect(20, 60, 251, 61));
        layoutWidget = new QWidget(dlgCutFile);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 261, 21));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        frameNumType = new QRadioButton(layoutWidget);
        frameNumType->setObjectName(QStringLiteral("frameNumType"));
        frameNumType->setChecked(true);

        horizontalLayout_4->addWidget(frameNumType);

        timeType = new QRadioButton(layoutWidget);
        timeType->setObjectName(QStringLiteral("timeType"));

        horizontalLayout_4->addWidget(timeType);

        layoutWidget1 = new QWidget(dlgCutFile);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 160, 261, 104));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labelDef1 = new QLabel(layoutWidget1);
        labelDef1->setObjectName(QStringLiteral("labelDef1"));

        verticalLayout->addWidget(labelDef1);

        labelDef2 = new QLabel(layoutWidget1);
        labelDef2->setObjectName(QStringLiteral("labelDef2"));

        verticalLayout->addWidget(labelDef2);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        inputValueBegin = new QLineEdit(layoutWidget1);
        inputValueBegin->setObjectName(QStringLiteral("inputValueBegin"));

        horizontalLayout->addWidget(inputValueBegin);

        realValueBegin = new QLineEdit(layoutWidget1);
        realValueBegin->setObjectName(QStringLiteral("realValueBegin"));

        horizontalLayout->addWidget(realValueBegin);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        inputValueEnd = new QLineEdit(layoutWidget1);
        inputValueEnd->setObjectName(QStringLiteral("inputValueEnd"));

        horizontalLayout_2->addWidget(inputValueEnd);

        realValueEnd = new QLineEdit(layoutWidget1);
        realValueEnd->setObjectName(QStringLiteral("realValueEnd"));

        horizontalLayout_2->addWidget(realValueEnd);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        btnCancel = new QPushButton(layoutWidget1);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));

        horizontalLayout_5->addWidget(btnCancel);

        btnSave = new QPushButton(layoutWidget1);
        btnSave->setObjectName(QStringLiteral("btnSave"));

        horizontalLayout_5->addWidget(btnSave);


        verticalLayout_3->addLayout(horizontalLayout_5);


        retranslateUi(dlgCutFile);

        QMetaObject::connectSlotsByName(dlgCutFile);
    } // setupUi

    void retranslateUi(QDialog *dlgCutFile)
    {
        dlgCutFile->setWindowTitle(QApplication::translate("dlgCutFile", "Dialog", Q_NULLPTR));
        labelShow->setText(QApplication::translate("dlgCutFile", "Frame Range", Q_NULLPTR));
        frameNumType->setText(QApplication::translate("dlgCutFile", "Frame Num", Q_NULLPTR));
        timeType->setText(QApplication::translate("dlgCutFile", "Time", Q_NULLPTR));
        labelDef1->setText(QApplication::translate("dlgCutFile", "Begin Pos", Q_NULLPTR));
        labelDef2->setText(QApplication::translate("dlgCutFile", "End Pos", Q_NULLPTR));
        btnCancel->setText(QApplication::translate("dlgCutFile", "Cancel", Q_NULLPTR));
        btnSave->setText(QApplication::translate("dlgCutFile", "Save", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class dlgCutFile: public Ui_dlgCutFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGCUTFILE_H
