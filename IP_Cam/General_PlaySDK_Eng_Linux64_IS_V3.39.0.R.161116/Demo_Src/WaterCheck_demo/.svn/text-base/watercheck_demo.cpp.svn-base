#include "watercheck_demo.h"
#include "ui_watercheck_demo.h"
#include "dhplay.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <unistd.h>

#define PORT        0
#define LANG_CS(a)  a
#define BUF_SIZE    (1024*1024)
#define CHANGE_PROCESS_EVENT_TYPE   (QEvent::User + 1)

WaterCheck_demo::WaterCheck_demo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaterCheck_demo),
    m_isExit(false),
    m_sema(0)
{
    ui->setupUi(this);

    m_thread = new WaterCheckThread(this);
    initTableView();
    ui->CheckProgress->setRange(0, 1000);
    changeUIState(INIT);

    QEvent::registerEventType(CHANGE_PROCESS_EVENT_TYPE);

    connect(this, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)), Qt::QueuedConnection);

    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    connect(this, SIGNAL(EndSignal()), this, SLOT(EndSlot()) );
}

WaterCheck_demo::~WaterCheck_demo()
{
    deleteAllItems();
    on_StopCheck_clicked();

    delete m_thread;
    delete m_itemModel;
    delete ui;
}

void WaterCheck_demo::onValueChanged(int value)
{
    ui->CheckProgress->setValue(value);
}

void WaterCheck_demo::initTableView()
{
    m_itemModel = new QStandardItemModel();

    m_itemModel->setColumnCount(3);
    m_itemModel->setHeaderData(0, Qt::Horizontal, "Num");
    m_itemModel->setHeaderData(1, Qt::Horizontal, "Error Type");
    m_itemModel->setHeaderData(2, Qt::Horizontal, "Time Stamp");
    ui->CheckResultTable->setModel(m_itemModel);
    ui->CheckResultTable->verticalHeader()->hide();
    ui->CheckResultTable->horizontalHeader()->setStretchLastSection(true);
    ui->CheckResultTable->setColumnWidth(0, 50);
    ui->CheckResultTable->setColumnWidth(1, 250);
    //ui->CheckResultTable->setColumnWidth(1, 150);


    ui->CheckResultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void WaterCheck_demo::on_BrowseFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select one or more files to open", ui->FilePathEdit->text(), "DAV (*.dav);;All Files(*.*)");

    deleteAllItems();
    if (fileName.isEmpty())
    {
        return;
    }

    ui->FilePathEdit->setText(fileName);
    if (!fileName.isEmpty())
    {
        changeUIState(OPENFILE);
    }
}

void WaterCheck_demo::changeUIState(UI_STATE state)
{
    switch (state)
    {
    case INIT:
        ui->StartCheck->setEnabled(false);
        ui->StopCheck->setEnabled(false);
        emit valueChanged(0);
        ui->WatermarkInfoEdit->setText("");
        ui->FilePathEdit->setEnabled(true);
        ui->BrowseFile->setEnabled(true);
        break;

    case OPENFILE:
        ui->StartCheck->setEnabled(true);
        ui->StopCheck->setEnabled(false);
        ui->WatermarkInfoEdit->setText("");
        deleteAllItems();
        break;

    case STOP:
        ui->StartCheck->setEnabled(true);
        ui->StopCheck->setEnabled(false);
        emit valueChanged(0);
        ui->WatermarkInfoEdit->setText("");
        ui->FilePathEdit->setEnabled(true);
        ui->BrowseFile->setEnabled(true);
        break;

    case CHECK:
        ui->StartCheck->setEnabled(false);
        ui->StopCheck->setEnabled(true);
        ui->WatermarkInfoEdit->setText("");
        ui->FilePathEdit->setEnabled(false);
        ui->BrowseFile->setEnabled(false);
        deleteAllItems();
        break;

    default:
        ui->StartCheck->setEnabled(true);
        ui->StopCheck->setEnabled(false);
        emit valueChanged(0);
        ui->FilePathEdit->setEnabled(true);
        ui->BrowseFile->setEnabled(true);
        break;
    }
}

void WaterCheck_demo::deleteAllItems()
{
    //m_itemModel->clear();
    int count = m_itemModel->rowCount();
    m_itemModel->removeRows(0, count);
}

void WaterCheck_demo::on_StopCheck_clicked()
{
    m_exitCondition.wakeAll();
    m_isExit = true;
    m_thread->wait();
}

void WaterCheck_demo::on_StartCheck_clicked()
{
    m_checkFile.setFileName(ui->FilePathEdit->text());
    if (!m_checkFile.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, "WaterCheck_demo", LANG_CS("Open file failed!"), QMessageBox::Ok, QMessageBox::Cancel);
        return;
    }

    m_isExit = false;
    m_thread->start();

    changeUIState(CHECK);
}

int CALLBACK watermarkCheckCBFunc(LONG nPort, char* buf, LONG lTimeStamp, LONG lInfoType, LONG len, LONG reallen, LONG lCheckResult, void* pUserData)
{
    WaterCheck_demo* pDemo = (WaterCheck_demo*)pUserData;

    return pDemo->onWaterMarkCheck(nPort, buf, lTimeStamp, lInfoType, len ,reallen, lCheckResult);
}

void getTimeStamp(long lTimeStamp, QString& timeStamp)
{
    QDateTime dateTime = QDateTime::fromTime_t(lTimeStamp);

    timeStamp = dateTime.toString("yyyy-MM-dd hh:mm:ss");
}

int WaterCheck_demo::onWaterMarkCheck(long nPort, char* buf, long lTimeStamp, long lInfoType, long len, long reallen, long lCheckResult)
{
    QString strErrorType;

    switch (lCheckResult)
    {
    case 1:             // no error
        {
            if (lInfoType == WATERMARK_DATA_TEXT)
            {
                QString waterMark;
                buf[reallen] = '\0';
                waterMark = buf;
                ui->WatermarkInfoEdit->setText(waterMark);
            }
        }
        break;

    case 2:             // watermark error
        strErrorType = LANG_CS("Watermark verify error");
        break;

    case 3:             // frame data error
        strErrorType = LANG_CS("Frame data verify error");
        break;

    case 4:             // frame number discontinuity
        strErrorType = LANG_CS("Frame number discontinuity");
        break;

    default:
        break;
    }

    if ((2 == lCheckResult) || (3 == lCheckResult) || (4 == lCheckResult))
    {
        QString strTimeStamp;
        getTimeStamp(lTimeStamp, strTimeStamp);

        QList<QStandardItem*> list;

        QStandardItem* item0 = new QStandardItem(QString("%1").arg(m_itemModel->rowCount()));
        QStandardItem* item1 = new QStandardItem(strErrorType);
        QStandardItem* item2 = new QStandardItem(strTimeStamp);
        list.append(item0);
        list.append(item1);
        list.append(item2);
        m_itemModel->appendRow(list);
    }

    return 0;
}

void WaterCheck_demo::EndSlot()
{
    changeUIState(COMPLETE);
}

void WaterCheck_demo::run()
{
    PLAY_SetStreamOpenMode(PORT, STREAME_FILE);
    PLAY_OpenStream(PORT, NULL, 0, BUF_SIZE);
    PLAY_Play(PORT, NULL);
    PLAY_SetWaterMarkCallBackEx(PORT, watermarkCheckCBFunc, this);

    qint64 fileSize = m_checkFile.size();
    const int READ_SIZE = 128 * 1024;
    unsigned char pBuf[READ_SIZE] = {0};
    qint64 readPos = 0;

    bool bInput = true;
    qint64 readSize = 0;
    while (!m_isExit)
    {
        if (bInput)
        {
            emit valueChanged(((double)readPos * 1000) / (double)fileSize);
            readSize = m_checkFile.read((char*)pBuf, READ_SIZE);
            if (readSize <= 0)
            {
                break;
            }
            readPos += readSize;
        }

        while (!(bInput = PLAY_InputData(PORT, pBuf, readSize)) && !m_isExit)
        {
			usleep(5);
        }
    }

    while ((PLAY_GetBufferValue(PORT, BUF_VIDEO_RENDER) + PLAY_GetSourceBufferRemain(PORT)) > 0)
    {
		usleep(5);
    }

    PLAY_Stop(PORT);
    PLAY_CloseStream(PORT);
    m_checkFile.close();

    //changeUIState(COMPLETE);
    emit EndSignal();
}
