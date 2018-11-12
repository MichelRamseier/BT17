#include "soundcapture_demo.h"
#include "ui_soundcapture_demo.h"
#include "dhplay.h"
#include <QFileDialog>
#include <QMessageBox>

#define LANG_CS(a) a

SoundCapture_demo::SoundCapture_demo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SoundCapture_demo)
{
    ui->setupUi(this);

    m_fpPCM = NULL;

    InitCombobox();

    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
}

SoundCapture_demo::~SoundCapture_demo()
{
    delete ui;
}

void CALLBACK AudioRecord(LPBYTE pDataBuffer, DWORD DataLength, void* pUserData)
{
    SoundCapture_demo* pDemo = (SoundCapture_demo*)pUserData;

    if (NULL != pDemo->m_fpPCM)
    {
        fwrite(pDataBuffer, 1, DataLength, pDemo->m_fpPCM);
    }
}

void SoundCapture_demo::on_StartRecord_clicked()
{
    m_fpPCM = fopen(ui->FilePathEdit->text().toStdString().c_str(), "wb+");
    if (NULL == m_fpPCM)
    {
        QMessageBox::warning(this, "SoundCapture_demo", LANG_CS("File path error!"), QMessageBox::Ok, QMessageBox::Cancel);
        return;
    }

    int nBitPerSample  = ui->BitPerSample->itemData(ui->BitPerSample->currentIndex()).toInt();
    int nSamplesPerSec = ui->SamplersPerSec->itemData(ui->SamplersPerSec->currentIndex()).toInt();

    long nSampleLen = 40 * nBitPerSample * nSamplesPerSec / 16000;
    if (nSampleLen < 320)
    {
        nSampleLen = 320;
    }

    PLAY_OpenAudioRecord(AudioRecord, nBitPerSample, nSamplesPerSec, nSampleLen, 0, this);

    changeUIState(false);
}

void SoundCapture_demo::changeUIState(bool isEnable)
{
    ui->FilePathEdit->setEnabled(isEnable);
    ui->BrowseFileButton->setEnabled(isEnable);
    ui->StartRecord->setEnabled(isEnable);
    ui->StopRecord->setEnabled(!isEnable);
    ui->BitPerSample->setEnabled(isEnable);
    ui->SamplersPerSec->setEnabled(isEnable);
}

void SoundCapture_demo::on_StopRecord_clicked()
{
    PLAY_CloseAudioRecord();

    if (NULL != m_fpPCM)
    {
        fclose(m_fpPCM);
        m_fpPCM = NULL;
    }

    changeUIState(true);
}

void SoundCapture_demo::InitCombobox()
{
    ui->SamplersPerSec->addItem("11025 Hz", 11025);
    ui->SamplersPerSec->addItem("16000 Hz", 16000);
    ui->SamplersPerSec->addItem("22050 Hz", 22050);
    ui->SamplersPerSec->addItem("32000 Hz", 32000);
    ui->SamplersPerSec->addItem("44100 Hz", 44100);
    ui->SamplersPerSec->addItem("8000 Hz", 8000);
    ui->SamplersPerSec->addItem("96000 Hz", 96000);
    ui->SamplersPerSec->setCurrentIndex(5);

    ui->BitPerSample->addItem("16 bit", 16);
    ui->BitPerSample->addItem("8 bit", 8);
}

void SoundCapture_demo::on_BrowseFileButton_clicked()
{
    QString defaultDir = ui->FilePathEdit->text();
    if (defaultDir.isEmpty())
    {
        defaultDir = "/home/record_audio.pcm";
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Save Audio File", defaultDir, "PCM (*.pcm);;All files (*.*)");
    if (fileName.isEmpty())
    {
        return;
    }
    ui->FilePathEdit->setText(fileName);
}
