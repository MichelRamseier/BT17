/********************************************************************************
** Form generated from reading UI file 'dlgsnappicsetting.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSNAPPICSETTING_H
#define UI_DLGSNAPPICSETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DlgSnapPicSetting
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *editPath;
    QHBoxLayout *horizontalLayout;
    QRadioButton *bmpType;
    QRadioButton *jpgType;
    QVBoxLayout *verticalLayout;
    QPushButton *btnPath;
    QPushButton *OK;

    void setupUi(QDialog *DlgSnapPicSetting)
    {
        if (DlgSnapPicSetting->objectName().isEmpty())
            DlgSnapPicSetting->setObjectName(QStringLiteral("DlgSnapPicSetting"));
        DlgSnapPicSetting->resize(379, 99);
        DlgSnapPicSetting->setMaximumSize(QSize(379, 99));
        layoutWidget = new QWidget(DlgSnapPicSetting);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 361, 71));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        editPath = new QLineEdit(layoutWidget);
        editPath->setObjectName(QStringLiteral("editPath"));

        verticalLayout_2->addWidget(editPath);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        bmpType = new QRadioButton(layoutWidget);
        bmpType->setObjectName(QStringLiteral("bmpType"));
        bmpType->setChecked(true);

        horizontalLayout->addWidget(bmpType);

        jpgType = new QRadioButton(layoutWidget);
        jpgType->setObjectName(QStringLiteral("jpgType"));

        horizontalLayout->addWidget(jpgType);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        btnPath = new QPushButton(layoutWidget);
        btnPath->setObjectName(QStringLiteral("btnPath"));

        verticalLayout->addWidget(btnPath);

        OK = new QPushButton(layoutWidget);
        OK->setObjectName(QStringLiteral("OK"));

        verticalLayout->addWidget(OK);


        horizontalLayout_2->addLayout(verticalLayout);


        retranslateUi(DlgSnapPicSetting);

        QMetaObject::connectSlotsByName(DlgSnapPicSetting);
    } // setupUi

    void retranslateUi(QDialog *DlgSnapPicSetting)
    {
        DlgSnapPicSetting->setWindowTitle(QApplication::translate("DlgSnapPicSetting", "Dialog", Q_NULLPTR));
        bmpType->setText(QApplication::translate("DlgSnapPicSetting", "BMP", Q_NULLPTR));
        jpgType->setText(QApplication::translate("DlgSnapPicSetting", "JPG", Q_NULLPTR));
        btnPath->setText(QApplication::translate("DlgSnapPicSetting", "Path", Q_NULLPTR));
        OK->setText(QApplication::translate("DlgSnapPicSetting", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DlgSnapPicSetting: public Ui_DlgSnapPicSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGSNAPPICSETTING_H
