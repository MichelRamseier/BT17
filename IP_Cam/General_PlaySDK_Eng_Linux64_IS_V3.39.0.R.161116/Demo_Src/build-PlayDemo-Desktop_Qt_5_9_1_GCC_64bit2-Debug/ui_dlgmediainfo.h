/********************************************************************************
** Form generated from reading UI file 'dlgmediainfo.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGMEDIAINFO_H
#define UI_DLGMEDIAINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_dlgMediaInfo
{
public:
    QLabel *mediainfo;
    QPushButton *btnOK;

    void setupUi(QDialog *dlgMediaInfo)
    {
        if (dlgMediaInfo->objectName().isEmpty())
            dlgMediaInfo->setObjectName(QStringLiteral("dlgMediaInfo"));
        dlgMediaInfo->resize(305, 191);
        dlgMediaInfo->setMaximumSize(QSize(305, 191));
        mediainfo = new QLabel(dlgMediaInfo);
        mediainfo->setObjectName(QStringLiteral("mediainfo"));
        mediainfo->setGeometry(QRect(20, 20, 271, 111));
        btnOK = new QPushButton(dlgMediaInfo);
        btnOK->setObjectName(QStringLiteral("btnOK"));
        btnOK->setGeometry(QRect(100, 150, 114, 32));

        retranslateUi(dlgMediaInfo);

        QMetaObject::connectSlotsByName(dlgMediaInfo);
    } // setupUi

    void retranslateUi(QDialog *dlgMediaInfo)
    {
        dlgMediaInfo->setWindowTitle(QApplication::translate("dlgMediaInfo", "Dialog", Q_NULLPTR));
        mediainfo->setText(QApplication::translate("dlgMediaInfo", "TextLabel", Q_NULLPTR));
        btnOK->setText(QApplication::translate("dlgMediaInfo", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class dlgMediaInfo: public Ui_dlgMediaInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGMEDIAINFO_H
