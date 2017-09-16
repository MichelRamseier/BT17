#include "dlgsnappicsetting.h"
#include "ui_dlgsnappicsetting.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

DlgSnapPicSetting::DlgSnapPicSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgSnapPicSetting),
    m_iPicType(0)
{
    ui->setupUi(this);


    QString picDir = QCoreApplication::applicationDirPath();// + "/picture";
    int iIndex = picDir.indexOf("/PlayDemo.app/Contents/MacOS");
    if ( iIndex != -1 )
    {
        picDir.truncate(iIndex);
    }

    picDir += "/picture";

    //QMessageBox::information( 0, "abc", picDir, QMessageBox::Ok );
    QDir dir(picDir);
    if(!dir.exists())
    {
        dir.mkpath(".");
    }

    m_strPath = picDir;
    ui->editPath->setText(picDir);

    m_iPicType = 0;
}

DlgSnapPicSetting::~DlgSnapPicSetting()
{
    delete ui;
}

void DlgSnapPicSetting::on_bmpType_clicked()
{
    m_iPicType = 0;
}

void DlgSnapPicSetting::on_jpgType_clicked()
{
    m_iPicType = 1;
}

void DlgSnapPicSetting::on_btnPath_clicked()
{
    QString defaultDir = ui->editPath->text();
    if (defaultDir.isEmpty())
    {
        defaultDir = QDir::currentPath() + "picture";
    }

    m_strPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), defaultDir,
                                                  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!m_strPath.isEmpty())
    {
        ui->editPath->setText(m_strPath);
    }
}

void DlgSnapPicSetting::on_OK_clicked()
{
    m_strPath = ui->editPath->text();

    QDialog::accept();
}

void DlgSnapPicSetting::ResetSet(QString strPath, int iPicType)
{
    m_strPath = strPath;
    m_iPicType = iPicType;

    ui->editPath->setText(strPath);
    if (iPicType == 0)
    {
        ui->bmpType->setChecked(true);
    }
    else if (iPicType == 1)
    {
        ui->jpgType->setChecked(true);
    }
}
