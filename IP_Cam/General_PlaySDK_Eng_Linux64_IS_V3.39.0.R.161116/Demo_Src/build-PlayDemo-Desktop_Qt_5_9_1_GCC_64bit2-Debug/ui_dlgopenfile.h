/********************************************************************************
** Form generated from reading UI file 'dlgopenfile.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGOPENFILE_H
#define UI_DLGOPENFILE_H

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

class Ui_DlgOpenFile
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *editFilePath;
    QHBoxLayout *horizontalLayout;
    QRadioButton *filetype;
    QRadioButton *filestreamtype;
    QVBoxLayout *verticalLayout;
    QPushButton *btnOpenFile;
    QPushButton *btnOK;

    void setupUi(QDialog *DlgOpenFile)
    {
        if (DlgOpenFile->objectName().isEmpty())
            DlgOpenFile->setObjectName(QStringLiteral("DlgOpenFile"));
        DlgOpenFile->resize(397, 91);
        DlgOpenFile->setMaximumSize(QSize(397, 91));
        layoutWidget = new QWidget(DlgOpenFile);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 381, 68));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        editFilePath = new QLineEdit(layoutWidget);
        editFilePath->setObjectName(QStringLiteral("editFilePath"));

        verticalLayout_2->addWidget(editFilePath);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        filetype = new QRadioButton(layoutWidget);
        filetype->setObjectName(QStringLiteral("filetype"));
        filetype->setChecked(true);

        horizontalLayout->addWidget(filetype);

        filestreamtype = new QRadioButton(layoutWidget);
        filestreamtype->setObjectName(QStringLiteral("filestreamtype"));

        horizontalLayout->addWidget(filestreamtype);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        btnOpenFile = new QPushButton(layoutWidget);
        btnOpenFile->setObjectName(QStringLiteral("btnOpenFile"));

        verticalLayout->addWidget(btnOpenFile);

        btnOK = new QPushButton(layoutWidget);
        btnOK->setObjectName(QStringLiteral("btnOK"));

        verticalLayout->addWidget(btnOK);


        horizontalLayout_2->addLayout(verticalLayout);


        retranslateUi(DlgOpenFile);

        QMetaObject::connectSlotsByName(DlgOpenFile);
    } // setupUi

    void retranslateUi(QDialog *DlgOpenFile)
    {
        DlgOpenFile->setWindowTitle(QApplication::translate("DlgOpenFile", "Dialog", Q_NULLPTR));
        filetype->setText(QApplication::translate("DlgOpenFile", "file", Q_NULLPTR));
        filestreamtype->setText(QApplication::translate("DlgOpenFile", "file stream", Q_NULLPTR));
        btnOpenFile->setText(QApplication::translate("DlgOpenFile", "open file", Q_NULLPTR));
        btnOK->setText(QApplication::translate("DlgOpenFile", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DlgOpenFile: public Ui_DlgOpenFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGOPENFILE_H
