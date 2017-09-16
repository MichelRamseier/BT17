#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dlgmediainfo.h"
#include "dlglocate.h"
#include "dlgcutfile.h"
#include "dlgsetcolor.h"
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>
#include <QMimeData>
#include <QUrl>
#include <QList>
#include <QDropEvent>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_dlgOpenFile(this),
    m_dlgSnapPicSetting(this),
    m_pTimer(NULL),
    m_isPlaySound(true)
{
    ui->setupUi(this);

    m_dlgStateText.Init(ui->state);
    ui->AdjustWave->setRange(-100,100);
    ui->Volume->setRange(0,0xffff);
    ui->Process->setRange(0,100);
    ui->actionIVS->setCheckable(true);
    ui->actionHwaccel->setCheckable(true);
    ChangeUIState(Close);

    QObject::connect(ui->AdjustWave, SIGNAL(valueChanged(int)), this, SLOT(OnWaveChanged(int)));
    QObject::connect(ui->Volume, SIGNAL(valueChanged(int)), this, SLOT(OnVolumeChanged(int)));
    QObject::connect(ui->Process, SIGNAL(sliderMoved(int)), this, SLOT(OnProcessChanged(int)));
    QObject::connect(this, SIGNAL(indexCreated(int)), this, SLOT(onIndexCreated(int)));

    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnOperator(PLAY_STATE nState)
{
    if (nState==Stop)
    {
        ui->actionIVS->setChecked(false);
    }

    /*change player status*/
    CPlayer::Instance()->ChangeState(nState);

    /*Operation to switch status*/
    if( CPlayer::Instance()->Do() <= 0)
    {
        ChangeSingleUIState(nState, FALSE);
    }

    /*Refresh status bar*/
    char* szDesc = CPlayer::Instance()->Description();
    if((NULL != szDesc) && (0 == strcmp(szDesc, "Play")))
    {
        /*Operation of Slow and Fast are special. To switch between slow/fast play, you may need to change play state*/
        nState = Play;
    }
    m_dlgStateText.SetState(szDesc);

    /*change ui status*/
    ChangeUIState(nState);
}

void ChangePlayButtonUIState(QPushButton* lpUI[STATE_SIZE] , int nState[9])
{
    for(int i = 0 ; i < STATE_SIZE; i++)
    {
        if(nState[i]!=2)
        {
            lpUI[i]->setEnabled(nState[i]==0?false:true);
        }
    }
}

int MainWindow::ChangeUIState(PLAY_STATE nState)
{
    QPushButton* lpUI[STATE_SIZE] = { ui->Play, ui->Pause, ui->Stop, ui->ToEnd, ui->ToBegin,
        ui->StepBackOne, ui->StepGo, ui->Slow, ui->Fast };

    if(nState == Open)
    {
        ui->SetColor->setEnabled(true);
        ui->Volume->setEnabled(true);
        ui->AdjustWave->setEnabled(true);
        ui->SetVolume->setEnabled(true);
        ChangePlayButtonUIState(lpUI, CPlayer::Instance()->openTable);
        ChangeMenuState(FILEOPEN);
    }
    else if(nState == Close)
    {
        ui->SnapPicture->setEnabled(false);
        ui->SetColor->setEnabled(false);
        ui->Volume->setEnabled(false);
        ui->AdjustWave->setEnabled(false);
        ui->SetVolume->setEnabled(false);
        ChangePlayButtonUIState(lpUI, CPlayer::Instance()->closeTable);
        ChangeMenuState(FILECLOSE);
    }
    else if(nState>=Play && nState<=Fast)
    {
        ui->SnapPicture->setEnabled(nState!=Stop?true:false);
        if(nState==Stop)
        {
            ChangeMenuState(STOPPLAY);
        }

        if (nState == Play)
        {
            ChangeMenuState(STARTPLAY);
        }

        ChangePlayButtonUIState(lpUI, CPlayer::Instance()->stateTable[nState]);
    }

    m_lastState = nState;
    return 1;
}

int MainWindow::ChangeSingleUIState(PLAY_STATE nState, BOOL bEnable)
{
    QPushButton* lpUI[STATE_SIZE] = { ui->Play, ui->Pause, ui->Stop, ui->ToEnd, ui->ToBegin,
        ui->StepBackOne, ui->StepGo, ui->Slow, ui->Fast };
    lpUI[nState]->setEnabled(bEnable==TRUE?true:false);
    return 1;
}

int MainWindow::ChangeMenuState(MENU_STATE nState)
{
    if(nState == FILEOPEN)
    {
        ui->actionOpen->setEnabled(false);
        ui->actionClose->setEnabled(true);
        ui->Process->setEnabled(true);
        ui->actionHwaccel->setEnabled(true);
    }
    else if(nState == FILECLOSE)
    {
        ui->actionOpen->setEnabled(true);
        ui->actionClose->setEnabled(false);
        ui->actionLocate->setEnabled(false);
        ui->actionCutFile->setEnabled(false);
        ui->actionMediaInfo->setEnabled(false);
        ui->actionIVS->setEnabled(false);
		ui->actionHwaccel->setChecked(false);
        ui->actionHwaccel->setEnabled(false);
        ui->Process->setEnabled(false);
    }
    /*When index has been created, set single frame back to TRUE, eliminating quick play and slow play.*/
    else if(nState == FILEINDEXCREATED)
    {
        ui->actionLocate->setEnabled(true);
        ui->actionCutFile->setEnabled(true);
    }
    else if(nState == STOPPLAY)
    {
        ui->actionLocate->setEnabled(false);
    }
    else if(nState == STARTPLAY)
    {
        if(CPlayer::Instance()->IsIndexCreated())
        {
            ui->actionLocate->setEnabled(true);
            ui->actionCutFile->setEnabled(true);
        }
        ui->actionMediaInfo->setEnabled(true);
        ui->actionIVS->setEnabled(true);
    }
    return 1;
}

void MainWindow::on_Play_clicked()
{
    OnOperator(Play);
}

void MainWindow::on_Pause_clicked()
{
    OnOperator(Pause);
}

void MainWindow::on_Stop_clicked()
{
    OnOperator(Stop);
	
	update();
}

void MainWindow::on_ToBegin_clicked()
{
    OnOperator(ToBegin);
}

void MainWindow::on_ToEnd_clicked()
{
    OnOperator(ToEnd);
}

void MainWindow::on_StepBackOne_clicked()
{
    OnOperator(BackOne);
}

void MainWindow::on_StepGo_clicked()
{
    OnOperator(OneByOne);
}

void MainWindow::on_Slow_clicked()
{
    OnOperator(Slow);
}

void MainWindow::on_Fast_clicked()
{
    OnOperator(Fast);
}

void MainWindow::on_Backword_clicked()
{
    CPlayer::Instance()->SetPlayDirection(1);
}

void MainWindow::on_Forword_clicked()
{
    CPlayer::Instance()->SetPlayDirection(0);
}

void MainWindow::on_SnapPicture_clicked()
{
    QDateTime localTime = QDateTime::currentDateTime();
    QString strFileName = m_dlgSnapPicSetting.m_strPath;
    strFileName.append(localTime.toString("/yyyy.MM.dd_hh:mm:ss"));
    if(0 == m_dlgSnapPicSetting.m_iPicType)
    {
        strFileName.append(".bmp");
    }
    else
    {
        strFileName.append(".jpg");
    }

    if(!CPlayer::Instance()->SnapPicture((char*)strFileName.toStdString().c_str(), m_dlgSnapPicSetting.m_iPicType))
    {
        QMessageBox::warning(this, tr("warning"), tr("snap picture failed!"));
    }
}

void MainWindow::on_SetColor_clicked()
{
    dlgSetColor dlgcolor(this);
    dlgcolor.exec();
}

int MainWindow::OpenAudio()
{
    CPlayer::Instance()->OpenSound(TRUE);
    ui->AdjustWave->setEnabled(true);
    ui->Volume->setEnabled(true);
    int nVolume = CPlayer::Instance()->GetAudioVolume();
    CPlayer::Instance()->SetAudioVolume(nVolume);
    ui->Volume->setValue(nVolume);
    QIcon icon(":/res/icon/Res/sound.png");
    ui->SetVolume->setIcon(icon);
    m_isPlaySound = true;
    return 1;
}

int MainWindow::CloseAudio()
{
    CPlayer::Instance()->OpenSound(FALSE);
    ui->AdjustWave->setEnabled(false);
    ui->Volume->setEnabled(false);
    ui->Volume->setValue(0);
    QIcon icon(":/res/icon/Res/mute.png");
    ui->SetVolume->setIcon(icon);
    m_isPlaySound = false;

    return 1;
}

void MainWindow::on_SetVolume_clicked()
{
    if(m_isPlaySound)
    {
        /*Turn off audio if on*/
        CloseAudio();
    }
    else
    {
        /*Turn on audio if off*/
        OpenAudio();
    }
}

void MainWindow::OnProcessTimer()
{
    int nProc = CPlayer::Instance()->GetProcess();
    ui->Process->setValue(nProc);

    double dbBitrate;
    CPlayer::Instance()->GetBitrate(&dbBitrate);
    m_dlgStateText.SetBitrate(dbBitrate);

    int nRate;
    CPlayer::Instance()->GetRate(&nRate);
    m_dlgStateText.SetRate(nRate);

    LONG nWidht  = 0;
    LONG nHeight = 0;
    CPlayer::Instance()->GetPicSize(&nWidht, &nHeight);
    m_dlgStateText.SetPictureSize(nWidht, nHeight);

    m_dlgStateText.SetPlayedTime(CPlayer::Instance()->GetPlayedTime(), CPlayer::Instance()->GetTotalTime());
    m_dlgStateText.SetPlayedFrame(CPlayer::Instance()->GetPlayedFrame(), CPlayer::Instance()->GetTotalFrame()-1);

    m_dlgStateText.Show();
}

void MainWindow::onFileIndexEvent(int indexState)
{
    emit indexCreated(indexState);
}

void MainWindow::onIndexCreated(int indexState)
{
    CPlayer::Instance()->stateTable[0][5] = indexState;
    if (indexState)
    {
        ChangeUIState(m_lastState);
        ChangeMenuState(FILEINDEXCREATED);
    }
}

void MainWindow::OpenFile()
{
    CPlayer::Instance()->stateTable[0][5] = 0;

    int ret = CPlayer::Instance()->Open(CPlayer::TYPE(m_dlgOpenFile.m_nType), (char*)m_dlgOpenFile.m_strFile.toStdString().c_str(),
                                        (HWND)ui->Display->winId(), this);

    if(ret <= 0)
    {
        QMessageBox::warning(this, tr("warning"), tr("open file failed!"));
        return;
    }

    ChangeUIState(Open);

    m_dlgStateText.SetPlayedTime(0, CPlayer::Instance()->GetTotalTime());
    m_dlgStateText.SetPlayedFrame(0, CPlayer::Instance()->GetTotalFrame());

    OpenAudio();

    if(NULL == m_pTimer)
    {
        m_pTimer = new QTimer(this);
    }
    QObject::connect(m_pTimer, SIGNAL(timeout()), this, SLOT(OnProcessTimer()));
    m_pTimer->start(1000);
}

void MainWindow::dragEnterEvent(QDragEnterEvent * event)
{
    event->acceptProposedAction();
}

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>

void toAbsURL(QString& localFileString)
{
    if( localFileString.startsWith("/.file/id=") )
    {
        CFStringRef relCFStringRef = CFStringCreateWithCString(kCFAllocatorDefault
                                                        , localFileString.toUtf8().constData()
                                                        , kCFStringEncodingUTF8);
        CFURLRef relCFURL = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, relCFStringRef, kCFURLPOSIXPathStyle,false);

        CFErrorRef error = 0;
        CFURLRef absCFURL = CFURLCreateFilePathURL(kCFAllocatorDefault, relCFURL, &error);
        if(!error)
        {
            static const CFIndex maxAbsPathLen = 4096;
            char absPathCStr[maxAbsPathLen];
            if(CFURLGetFileSystemRepresentation(absCFURL, true, reinterpret_cast<uint8_t*>(&absPathCStr[0]),
                   maxAbsPathLen ))
            {
                   localFileString = QString(absPathCStr);
            }
        }
 
        CFRelease(absCFURL);
        CFRelease(relCFURL);
        CFRelease(relCFStringRef);
    }
}
#endif

void MainWindow::dropEvent(QDropEvent * event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())
    {
        return;
    }

    QString fName = urls.first().toLocalFile();
#ifdef __APPLE__
	toAbsURL(fName);
#endif
    if(!fName.isEmpty())
    {
        on_actionClose_triggered();
        m_dlgOpenFile.m_strFile = fName;
        OpenFile();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    if(QDialog::Accepted == m_dlgOpenFile.exec() && !m_dlgOpenFile.m_strFile.isEmpty())
    {
        OpenFile();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    on_actionClose_triggered();
    event->accept();
}

void MainWindow::on_actionClose_triggered()
{
    if(m_pTimer)
    {
        m_pTimer->stop();
        delete m_pTimer;
        m_pTimer = NULL;
    }

    ui->Process->setValue(0);
    m_dlgStateText.Clear();
    m_dlgStateText.Show();

    CloseAudio();
    CPlayer::Instance()->Close();

    ChangeUIState(Close);
	
	update();
}

void MainWindow::on_actionCutFile_triggered()
{
    dlgCutFile cutfile(m_dlgOpenFile.m_strFile, this);
    cutfile.exec();
}

void MainWindow::on_actionSnapPicture_triggered()
{
    QString lastStrFileName = m_dlgSnapPicSetting.m_strPath;
    int nLastType = m_dlgSnapPicSetting.m_iPicType;
    if (1 != m_dlgSnapPicSetting.exec())
    {
        m_dlgSnapPicSetting.ResetSet(lastStrFileName, nLastType);
    }
}

void MainWindow::on_actionLocate_triggered()
{
   dlgLocate locate(this);
   locate.exec();
}

void MainWindow::on_actionMediaInfo_triggered()
{
    dlgMediaInfo mediainfo(this);
    mediainfo.exec();
}

void MainWindow::on_actionIVS_triggered()
{
    if ( ui->actionIVS->isChecked() )
        CPlayer::Instance()->RenderPrivateData(TRUE);
    else
        CPlayer::Instance()->RenderPrivateData(FALSE);
}


void MainWindow::on_actionHwaccel_triggered()
{  
    if(ui->actionHwaccel->isChecked())
    {
        CPlayer::Instance()->SetEngine(2, 0); /*DECODE_HW */
    }
    else
    {
        CPlayer::Instance()->SetEngine(1, 0); /*DECODE_SW*/
    }
}

void MainWindow::on_actionVecticalSync_triggered()
{
    bool bCheckFlg = ui->actionVecticalSync->isChecked();
    if(bCheckFlg)
    {
        ui->actionVecticalSync->setChecked(false);
    }
    else
    {
        ui->actionVecticalSync->setChecked(true);
    }

    CPlayer::Instance()->SetVerticalSync(!bCheckFlg);
}

void MainWindow::OnWaveChanged(int pos)
{
    CPlayer::Instance()->SetAudioWave(pos);
}

void MainWindow::OnVolumeChanged(int pos)
{
   CPlayer::Instance()->SetAudioVolume(pos);
}

void MainWindow::OnProcessChanged(int pos)
{
    CPlayer::Instance()->Seek(pos);
}
