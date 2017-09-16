#include "deccb_demo.h"
#include "ui_deccb_demo.h"
#include "dhplay.h"
#include <QMessageBox>
#include <QFileDialog>

#define PORT 0
#define LANG_CS(a) a

DecCB_demo::DecCB_demo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DecCB_demo)
{
    ui->setupUi(this);

    m_fpOutAudioFile = NULL;
    m_fpOutVideoFile = NULL;

    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    connect( this, SIGNAL(EndSignal()), this, SLOT(EndSlot()) );
}

DecCB_demo::~DecCB_demo()
{
    delete ui;
}

void DecCB_demo::setAudioAndYuvPath(const QString& filePath)
{
    ui->OutputAudioFilePathEdit->setText(filePath + ".pcm");
    ui->OutputYuvFilePathEdit->setText(filePath + ".yuv");
}

void DecCB_demo::on_BrowseFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select one or more files to open", ui->FilePathEdit->text(), "DAV (*.dav);;All Files(*.*)");
    if (fileName.isEmpty())
    {
        return;
    }

    ui->FilePathEdit->setText(fileName);

    // 设置PCM和YUV的路径
    setAudioAndYuvPath(fileName);
}

void DecCB_demo::on_BrowseOutputAudioFile_clicked()
{
    QString defaultDir = ui->OutputAudioFilePathEdit->text();
    if (defaultDir.isEmpty())
    {
        defaultDir = "/home/dec_audio.pcm";
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Save Audio File", defaultDir, "PCM (*.pcm);;All files (*.*)");
    if (fileName.isEmpty())
    {
        return;
    }

    ui->OutputAudioFilePathEdit->setText(fileName);
}

void DecCB_demo::on_BrowseOutputYuvFile_clicked()
{
    QString defaultDir = ui->OutputYuvFilePathEdit->text();
    if (defaultDir.isEmpty())
    {
        defaultDir = "/home/dec_video.yuv";
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Save YUV File", defaultDir, "YUV (*.yuv);;All files (*.*)");
    if (fileName.isEmpty())
    {
        return;
    }

    ui->OutputYuvFilePathEdit->setText(fileName);
}

void CALLBACK fileEndCBFun(DWORD nPort, void* pUserData)
{
    DecCB_demo* pDemo = (DecCB_demo*)pUserData;
    pDemo->onFileEndCBFun(nPort);
}

void DecCB_demo::onFileEndCBFun(int nPort)
{
    printf("onFileEndCBFun: port[%d]\n", nPort);
    emit on_StopButton_clicked();
}

void DecCB_demo::on_DecodeButton_clicked()
{
    // 判断路径是否为空
    if (ui->FilePathEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "DecCB_demo", LANG_CS("Please select a file!"));
        return;
    }

    // 判断文件是否存在
    QFile file(ui->FilePathEdit->text());
    if (!file.exists())
    {
        QMessageBox::warning(this, "DecCB_demo", LANG_CS("File does not exist!"));
        return;
    }

    // 获取解码回调的类型
    DEC_TYPE decType = getDecodeType();

    // 打开解码回调类型对应的文件
    if (!openDestinationFiles(decType))
    {
        return;
    }

    // 打开文件
    if (!PLAY_OpenFile(PORT, (char*)ui->FilePathEdit->text().toStdString().c_str()))
    {
        changeUIState(STOP_DEC);
        QMessageBox::warning(this, "DecCB_demo", LANG_CS("Open source file failed!"));
        fclose(m_fpOutAudioFile);
        m_fpOutAudioFile = NULL;
        fclose(m_fpOutVideoFile);
        m_fpOutVideoFile = NULL;
        return;
    }

    // 设置回调
    setCallbacks(decType);

    // 播放
    play();

    // 改变界面上控件的状态
    changeUIState(START_DEC);
}

void DecCB_demo::play()
{
    if (ui->SetDecCBEx->isChecked() || ui->SetDecodeCB->isChecked())
    {
        PLAY_Play(PORT, NULL);
    }

    if (ui->SetVisibleDecCB->isChecked() || ui->SetVisibleDecodeCB->isChecked())
    {
        m_displayWindow.show();
        PLAY_Play(PORT, (HWND)m_displayWindow.winId());
        PLAY_PlaySound(PORT);
    }
}

void CALLBACK DecCbFun(LONG nPort, char * pBuf, LONG nSize, FRAME_INFO * pFrameInfo, void* pUserData, LONG nReserved2)
{
    DecCB_demo* pDemo = (DecCB_demo*)pUserData;

    if ((T_AUDIO16 == pFrameInfo->nType) || (T_AUDIO8 == pFrameInfo->nType))
    {
        if (NULL != pDemo->m_fpOutAudioFile)
        {
            fwrite(pBuf, 1, nSize, pDemo->m_fpOutAudioFile);
        }
    }

    if (T_IYUV == pFrameInfo->nType)
    {
        if (NULL != pDemo->m_fpOutVideoFile)
        {
            fwrite(pBuf, 1, nSize, pDemo->m_fpOutVideoFile);
        }
    }
}

void CALLBACK cbDecode(LONG nPort, FRAME_DECODE_INFO* pFrameDecodeInfo, FRAME_INFO_EX* pFrameInfo, void* pUser)
{
    DecCB_demo* pDemo = (DecCB_demo*)pUser;

    if ((FRAME_TYPE_VIDEO == pFrameDecodeInfo->nFrameType) && (NULL != pDemo->m_fpOutVideoFile))
    {
        for (int nIndex = 0; nIndex < 3; nIndex++)
        {
            char* pData = (char*)pFrameDecodeInfo->pVideoData[nIndex];
            for (int i = 0; i < pFrameDecodeInfo->nHeight[nIndex]; i++)
            {
                fwrite(pData, 1, pFrameDecodeInfo->nWidth[nIndex], pDemo->m_fpOutVideoFile);
                pData += pFrameDecodeInfo->nStride[nIndex];
            }
        }
    }

    if ((FRAME_TYPE_AUDIO == pFrameDecodeInfo->nFrameType) && (NULL != pDemo->m_fpOutAudioFile))
    {
        fwrite(pFrameDecodeInfo->pAudioData, 1, pFrameDecodeInfo->nAudioDataLen, pDemo->m_fpOutAudioFile);
    }
}

void CALLBACK cbVisibleDec(LONG nPort, char* pBuf, LONG nSize, FRAME_INFO* pFrameInfo, void* pUserData, LONG nReserved1)
{
    DecCB_demo* pDemo = (DecCB_demo*)pUserData;

    if ((T_AUDIO16 == pFrameInfo->nType) || (T_AUDIO8 == pFrameInfo->nType))
    {
        if (NULL != pDemo->m_fpOutAudioFile)
        {
            fwrite(pBuf, 1, nSize, pDemo->m_fpOutAudioFile);
        }
    }

    if (T_IYUV == pFrameInfo->nType)
    {
        if (NULL != pDemo->m_fpOutVideoFile)
        {
            fwrite(pBuf, 1, nSize, pDemo->m_fpOutVideoFile);
        }
    }
}

void DecCB_demo::setCallbacks(DEC_TYPE decType)
{
    // 设置文件结束回调
    PLAY_SetFileEndCallBack(PORT, fileEndCBFun, this);

    // 设置解码回调类型
    PLAY_SetDecCBStream(PORT, (int)decType + 1);

    if (ui->SetDecCBEx->isChecked())
    {
        PLAY_SetDecCallBackEx(PORT, DecCbFun, this);
    }

    if (ui->SetDecodeCB->isChecked())
    {
        PLAY_SetDecodeCallBack(PORT, cbDecode, this);
    }

    if (ui->SetVisibleDecCB->isChecked())
    {
        PLAY_SetVisibleDecCallBack(PORT, cbVisibleDec, this);
    }

    if (ui->SetVisibleDecodeCB->isChecked())
    {
        PLAY_SetVisibleDecodeCallBack(PORT, cbDecode, this);
    }
}

bool DecCB_demo::openDestinationFiles(DEC_TYPE decType)
{
    if (DEC_AUDIO != decType)
    {
        m_fpOutVideoFile = fopen(ui->OutputYuvFilePathEdit->text().toStdString().c_str(), "wb+");
        if (NULL == m_fpOutVideoFile)
        {
            QMessageBox::warning(this, "DecCB_demo", LANG_CS("Output YUV file error!"));
            return false;
        }
    }

    if (DEC_VIDEO != decType)
    {
        m_fpOutAudioFile = fopen(ui->OutputAudioFilePathEdit->text().toStdString().c_str(), "wb+");
        if (NULL == m_fpOutAudioFile)
        {
            QMessageBox::warning(this, "DecCB_demo", LANG_CS("Output audio file error!"));
            return false;
        }
    }

    return true;
}

void DecCB_demo::on_StopButton_clicked()
{
    PLAY_SetDecCallBackEx(PORT, NULL, NULL);
    PLAY_SetDecodeCallBack(PORT, NULL, NULL);
    PLAY_SetVisibleDecCallBack(PORT, NULL, NULL);
    PLAY_SetVisibleDecodeCallBack(PORT, NULL, NULL);

    PLAY_Stop(PORT);
    PLAY_CloseFile(PORT);

    if (NULL != m_fpOutAudioFile)
    {
        fclose(m_fpOutAudioFile);
        m_fpOutAudioFile = NULL;
    }

    if (NULL != m_fpOutVideoFile)
    {
        fclose(m_fpOutVideoFile);
        m_fpOutVideoFile = NULL;
    }

    emit EndSignal();
    //m_displayWindow.hide();

    // 改变界面上控件的状态
    //changeUIState(STOP_DEC);
}

void DecCB_demo::changeUIState(DECODE_STATE decState)
{
    bool isEnable = (START_DEC == decState) ? false : true;

    ui->BrowseFile->setEnabled(isEnable);
    ui->BrowseOutputAudioFile->setEnabled(isEnable);
    ui->BrowseOutputYuvFile->setEnabled(isEnable);
    ui->DecCBTypeAudio->setEnabled(isEnable);
    ui->DecCBTypeVideo->setEnabled(isEnable);
    ui->DecCBTypeComplex->setEnabled(isEnable);
    ui->FilePathEdit->setEnabled(isEnable);
    ui->OutputAudioFilePathEdit->setEnabled(isEnable);
    ui->OutputYuvFilePathEdit->setEnabled(isEnable);
    ui->DecodeButton->setEnabled(isEnable);
    ui->SetDecCBEx->setEnabled(isEnable);
    ui->SetDecodeCB->setEnabled(isEnable);
    ui->SetVisibleDecCB->setEnabled(isEnable);
    ui->SetVisibleDecodeCB->setEnabled(isEnable);
}

DecCB_demo::DEC_TYPE DecCB_demo::getDecodeType()
{
    DEC_TYPE decType = DEC_COMPLEX;

    if (ui->DecCBTypeAudio->isChecked())
    {
        decType = DEC_AUDIO;
    }
    else if (ui->DecCBTypeVideo->isChecked())
    {
        decType = DEC_VIDEO;
    }
    else
    {
        decType = DEC_COMPLEX;
    }

    return decType;
}

void DecCB_demo::EndSlot()
{
    m_displayWindow.hide();

    // 改变界面上控件的状态
    changeUIState(STOP_DEC);
}

