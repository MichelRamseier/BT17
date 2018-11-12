/********************************************************************************
** Form generated from reading UI file 'dlglocate.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGLOCATE_H
#define UI_DLGLOCATE_H

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

class Ui_dlgLocate
{
public:
    QLabel *labelShow;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelDef;
    QLineEdit *inputValue;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnCancel;
    QPushButton *btnLocate;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QRadioButton *frameNumType;
    QRadioButton *timeType;

    void setupUi(QDialog *dlgLocate)
    {
        if (dlgLocate->objectName().isEmpty())
            dlgLocate->setObjectName(QStringLiteral("dlgLocate"));
        dlgLocate->setWindowModality(Qt::NonModal);
        dlgLocate->resize(298, 218);
        dlgLocate->setMaximumSize(QSize(298, 218));
        dlgLocate->setModal(false);
        labelShow = new QLabel(dlgLocate);
        labelShow->setObjectName(QStringLiteral("labelShow"));
        labelShow->setGeometry(QRect(20, 50, 191, 61));
        layoutWidget = new QWidget(dlgLocate);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 140, 280, 67));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelDef = new QLabel(layoutWidget);
        labelDef->setObjectName(QStringLiteral("labelDef"));

        horizontalLayout_2->addWidget(labelDef);

        inputValue = new QLineEdit(layoutWidget);
        inputValue->setObjectName(QStringLiteral("inputValue"));
        inputValue->setMaxLength(10);

        horizontalLayout_2->addWidget(inputValue);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        btnCancel = new QPushButton(layoutWidget);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));

        horizontalLayout_3->addWidget(btnCancel);

        btnLocate = new QPushButton(layoutWidget);
        btnLocate->setObjectName(QStringLiteral("btnLocate"));

        horizontalLayout_3->addWidget(btnLocate);


        verticalLayout->addLayout(horizontalLayout_3);

        layoutWidget1 = new QWidget(dlgLocate);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 281, 20));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        frameNumType = new QRadioButton(layoutWidget1);
        frameNumType->setObjectName(QStringLiteral("frameNumType"));
        frameNumType->setFocusPolicy(Qt::TabFocus);
        frameNumType->setChecked(true);

        horizontalLayout->addWidget(frameNumType);

        timeType = new QRadioButton(layoutWidget1);
        timeType->setObjectName(QStringLiteral("timeType"));

        horizontalLayout->addWidget(timeType);


        retranslateUi(dlgLocate);

        QMetaObject::connectSlotsByName(dlgLocate);
    } // setupUi

    void retranslateUi(QDialog *dlgLocate)
    {
        dlgLocate->setWindowTitle(QApplication::translate("dlgLocate", "Dialog", Q_NULLPTR));
        labelShow->setText(QApplication::translate("dlgLocate", "Frame Rang...", Q_NULLPTR));
        labelDef->setText(QApplication::translate("dlgLocate", "Frame Num or Time", Q_NULLPTR));
        inputValue->setText(QString());
        btnCancel->setText(QApplication::translate("dlgLocate", "Cancel", Q_NULLPTR));
        btnLocate->setText(QApplication::translate("dlgLocate", "Locate", Q_NULLPTR));
        frameNumType->setText(QApplication::translate("dlgLocate", "Frame Num", Q_NULLPTR));
        timeType->setText(QApplication::translate("dlgLocate", "Time", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class dlgLocate: public Ui_dlgLocate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGLOCATE_H
