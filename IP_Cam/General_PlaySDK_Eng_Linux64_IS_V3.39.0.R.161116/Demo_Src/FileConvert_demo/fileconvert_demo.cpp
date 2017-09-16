#include "fileconvert_demo.h"
#include "ui_fileconvert_demo.h"
#include <QFileDialog>
#include <QMessageBox>
#include <unistd.h>

#define LANG_CS(a)              a
#define PORT                    0
#define SOURCEBUF_SIZE          (500 * 1024)

FileConvert_demo::FileConvert_demo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileConvert_demo),
    m_convertThread(NULL),
    m_isConverting(false),
    m_nChangeCount(0)
{
    ui->setupUi(this);

    ui->ConvertProgress->setRange(0, 500);
    ui->ConvertProgress->setValue(0);

    connect(this, SIGNAL(startConvertFailed()), this, SLOT(onStartConvertFailed()), Qt::QueuedConnection);
    connect(this, SIGNAL(openFileFailed()), this, SLOT(onOpenFileFailed()), Qt::QueuedConnection);
    connect(this, SIGNAL(convertCompleted()), this, SLOT(onConvertCompleted()), Qt::QueuedConnection);
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(changeUIState(int)), this, SLOT(onChangeUIState(int)), Qt::QueuedConnection);

    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
}

FileConvert_demo::~FileConvert_demo()
{
    delete ui;
}

void FileConvert_demo::onStartConvertFailed()
{
    QMessageBox::warning(this, "FileConvert_demo", LANG_CS("ASF Convert Failed!"));
}

void FileConvert_demo::onOpenFileFailed()
{

}

void FileConvert_demo::onConvertCompleted()
{
    QMessageBox::warning(this, "FileConvert_demo", LANG_CS("ASF Convert complete!"));
}

void FileConvert_demo::onValueChanged(int value)
{
    ui->ConvertProgress->setValue(value);
}

void FileConvert_demo::on_StartConvert_clicked()
{
    if (NULL != m_convertThread)
    {
        m_isConverting = false;

        if (m_convertThread->isRunning())
        {
            m_convertThread->wait();
        }

        delete m_convertThread;
        m_convertThread = NULL;
    }

    m_nChangeCount = 0;

    m_convertThread = new FileConvertThread(this, this);
    m_convertThread->start();

    m_isConverting = true;
}

void FileConvert_demo::run()
{
    QFile srcFile(ui->SourcePathEdit->text());
    if (!srcFile.open(QFile::ReadOnly))
    {
        emit openFileFailed();
        return;
    }

    if (!startConvert())
    {
        srcFile.close();
        return;
    }

    emit changeUIState(CONVERT);

    qint64 fileLen = srcFile.size();
    qint64 readPos = 0;
    const int READ_LEN = 8 * 1024;
    unsigned char readBuf[READ_LEN] = {0};

    while (m_isConverting)
    {
        qint64 readLen = srcFile.read((char*)readBuf, READ_LEN);
        if (readLen <= 0)
        {
            break;
        }

        while (!PLAY_InputData(PORT, readBuf, readLen) && m_isConverting)
        {
			usleep(10);
        }

        readPos += readLen;

        if (m_isConverting)
        {
            double proPercent = ((double)readPos / (double)fileLen) * 500;
            emit valueChanged(proPercent);
        }
    }

    if (m_isConverting)
    {
        emit convertCompleted();
        emit changeUIState(CANCEL);
    }

    while ((PLAY_GetBufferValue(PORT, BUF_VIDEO_RENDER) + PLAY_GetSourceBufferRemain(PORT)) > 0)
    {
        usleep(5);
    }

    stopConvert();
    srcFile.close();
}

bool FileConvert_demo::startConvert()
{
    PLAY_SetStreamOpenMode(PORT, STREAME_FILE);
    PLAY_OpenStream(PORT, NULL, 0, SOURCEBUF_SIZE);
    PLAY_Play(PORT, NULL);

    BOOL retValue = PLAY_StartDataRecord(PORT, (char*)ui->DestPathEdit->text().toStdString().c_str(), 2);

    if (!retValue)
    {
        // 触发失败事件
        emit startConvertFailed();
        m_isConverting = false;
        PLAY_Stop(PORT);
        PLAY_CloseStream(PORT);

        return false;
    }

    return true;
}

void FileConvert_demo::stopConvert()
{
    PLAY_StopDataRecord(PORT);

    PLAY_Stop(PORT);
    PLAY_CloseStream(PORT);
}

void FileConvert_demo::on_StopConvert_clicked()
{
    m_isConverting = false;
    if (NULL != m_convertThread)
    {
        m_convertThread->wait();
    }

    m_nChangeCount = 0;

    onChangeUIState(CANCEL);
}

void FileConvert_demo::closeEvent(QCloseEvent *event)
{
    on_StopConvert_clicked();
}

void FileConvert_demo::on_BrowseSourcePath_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, LANG_CS("Select one file to open"), ui->SourcePathEdit->text(), "DAV (*.dav);;All Files(*.*)");
    if (fileName.isEmpty())
    {
        return;
    }

    ui->SourcePathEdit->setText(fileName);

    QString strExt = ".asf";

    ui->DestPathEdit->setText(fileName + strExt);
}

void FileConvert_demo::on_BrowseDestPath_clicked()
{
    QString strFilter;
    QString strDefault = ui->DestPathEdit->text();
    strFilter.append("ASF (*.asf);;All files (*.*)");
    if (strDefault.isEmpty())
    {
        strDefault.append("/home/convert.asf");
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Save file", strDefault, strFilter);
    if (!fileName.isEmpty())
    {
        ui->DestPathEdit->setText(fileName);
    }
}

void FileConvert_demo::changeExtensionName(const QString& srcExtName, const QString& dstExtName)
{
    if (ui->DestPathEdit->text().indexOf(dstExtName) > 0)
    {
        return;
    }

    QString fileName = ui->DestPathEdit->text();
    int index = ui->DestPathEdit->text().lastIndexOf(srcExtName);
    if (index < 0)
    {
        index = ui->DestPathEdit->text().lastIndexOf(dstExtName);
    }

    if (index >= 0)
    {
        fileName = ui->DestPathEdit->text().mid(0, index);
        ui->DestPathEdit->setText(fileName + dstExtName);
    }
}

void FileConvert_demo::onChangeUIState(int state)
{
    bool isEnable = (state == CONVERT) ? false : true;

    ui->StopConvert->setEnabled(!isEnable);
    ui->StartConvert->setEnabled(isEnable);
    ui->DestPathEdit->setEnabled(isEnable);
    ui->SourcePathEdit->setEnabled(isEnable);
    ui->BrowseSourcePath->setEnabled(isEnable);
    ui->BrowseDestPath->setEnabled(isEnable);

    if (state == CANCEL)
    {
        emit valueChanged(0);
    }
}
