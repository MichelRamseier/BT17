/********************************************************************************
** Form generated from reading UI file 'dlgsetcolor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETCOLOR_H
#define UI_DLGSETCOLOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_dlgSetColor
{
public:
    QSlider *saturation;
    QSlider *brightness;
    QSlider *contrast;
    QSlider *hue;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *btnOK;

    void setupUi(QDialog *dlgSetColor)
    {
        if (dlgSetColor->objectName().isEmpty())
            dlgSetColor->setObjectName(QStringLiteral("dlgSetColor"));
        dlgSetColor->resize(318, 224);
        dlgSetColor->setMaximumSize(QSize(318, 224));
        saturation = new QSlider(dlgSetColor);
        saturation->setObjectName(QStringLiteral("saturation"));
        saturation->setGeometry(QRect(110, 30, 160, 22));
        saturation->setOrientation(Qt::Horizontal);
        brightness = new QSlider(dlgSetColor);
        brightness->setObjectName(QStringLiteral("brightness"));
        brightness->setGeometry(QRect(110, 70, 160, 22));
        brightness->setOrientation(Qt::Horizontal);
        contrast = new QSlider(dlgSetColor);
        contrast->setObjectName(QStringLiteral("contrast"));
        contrast->setGeometry(QRect(110, 110, 160, 22));
        contrast->setOrientation(Qt::Horizontal);
        hue = new QSlider(dlgSetColor);
        hue->setObjectName(QStringLiteral("hue"));
        hue->setGeometry(QRect(110, 150, 160, 22));
        hue->setOrientation(Qt::Horizontal);
        label = new QLabel(dlgSetColor);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 71, 21));
        label_2 = new QLabel(dlgSetColor);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 70, 71, 20));
        label_3 = new QLabel(dlgSetColor);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 110, 62, 16));
        label_4 = new QLabel(dlgSetColor);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 150, 62, 16));
        btnOK = new QPushButton(dlgSetColor);
        btnOK->setObjectName(QStringLiteral("btnOK"));
        btnOK->setGeometry(QRect(100, 190, 114, 32));

        retranslateUi(dlgSetColor);

        QMetaObject::connectSlotsByName(dlgSetColor);
    } // setupUi

    void retranslateUi(QDialog *dlgSetColor)
    {
        dlgSetColor->setWindowTitle(QApplication::translate("dlgSetColor", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("dlgSetColor", "Saturation", Q_NULLPTR));
        label_2->setText(QApplication::translate("dlgSetColor", "Brightness", Q_NULLPTR));
        label_3->setText(QApplication::translate("dlgSetColor", "Contrast", Q_NULLPTR));
        label_4->setText(QApplication::translate("dlgSetColor", "Hue", Q_NULLPTR));
        btnOK->setText(QApplication::translate("dlgSetColor", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class dlgSetColor: public Ui_dlgSetColor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGSETCOLOR_H
