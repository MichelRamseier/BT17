#include "dlgopenfile.h"
#include "ui_dlgopenfile.h"
#include <QFileDialog>

DlgOpenFile::DlgOpenFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgOpenFile)
{
    m_nType = 0;
    ui->setupUi(this);
}

DlgOpenFile::~DlgOpenFile()
{
    delete ui;
}

void DlgOpenFile::on_btnOpenFile_clicked()
{
    QString strFile = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                ui->editFilePath->text(),
                tr("DAV Files (*.dav);;All Files (*.*)"));

    if (strFile.isEmpty())
    {
        return;
    }

    m_strFile = strFile;
    ui->editFilePath->setText(m_strFile);
}

void DlgOpenFile::showEvent(QShowEvent *event)
{
    ui->editFilePath->setText(m_strFile);
}

void DlgOpenFile::on_btnOK_clicked()
{
    m_strFile = ui->editFilePath->text();
    QDialog::accept();
}

void DlgOpenFile::on_filetype_clicked()
{
    m_nType = 0;
}

void DlgOpenFile::on_filestreamtype_clicked()
{
    m_nType = 1;
}
