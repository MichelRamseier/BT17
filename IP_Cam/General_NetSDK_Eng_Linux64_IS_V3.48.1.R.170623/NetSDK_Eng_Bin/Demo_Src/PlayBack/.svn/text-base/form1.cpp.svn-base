#include "form1.h"
#include "ui_form1.h"

Form1::Form1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form1)
{
    ui->setupUi(this);
}

Form1::~Form1()
{
    delete ui;
}

void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
    Form1 * pThis = (Form1 *)dwUser;
    if(NULL == pThis)
    {
        return;
    }
    //deal
    QEvent*  eventDisconnect = new QEvent(QEvent::User);
    QApplication::postEvent((QObject*)pThis, eventDisconnect);
    return;
}


int CALLBACK DataCallBack(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser)
{
    int nRet = 1;

    Form1 * pThis = (Form1 *)dwUser;
    if(NULL == pThis)
    {
        return 1;
    }

    nRet = pThis->ReceiveRealData(lRealHandle,dwDataType, pBuffer, dwBufSize);
    return nRet;
}


int Form1::ReceiveRealData(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, LDWORD dwBufSize)
{
    return 1;
}


void CALLBACK PlayCallBack(LLONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, LDWORD dwUser)
{
    Form1 * pThis = (Form1 *)dwUser;
    if(NULL == pThis)
    {
        return;
    }
    pThis->ReceivePlayPos(lPlayHandle, dwTotalSize, dwDownLoadSize);
    return;
}



void Form1::ReceivePlayPos(LLONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize)
{
    if(lPlayHandle == m_hPlayBack)
    {
        if(-1 != dwDownLoadSize)
        {
            m_dwFileTotalSize = dwTotalSize;
            m_dwFileCurValue = dwDownLoadSize;
        }
        else
        {
            m_dwFileTotalSize = 100;
            m_dwFileCurValue = 0;
            if(0 != m_hPlayBack)
            {
                QEvent* pEvent = new QEvent(QEvent::Type(QEvent::User+3));
                QApplication::postEvent((QObject*)this, pEvent);
            }
        }
    }
    else if(lPlayHandle == m_lDownLoadFile)
    {
        if(-1 != dwDownLoadSize)
        {
            m_dwFileTotalSize = dwTotalSize;
            m_dwFileCurValue = dwDownLoadSize;
        }
        else
        {
            m_dwFileTotalSize = 100;
            m_dwFileCurValue = 0;
            if(0 != m_lDownLoadFile)
            {
                QEvent* pEvent = new QEvent(QEvent::Type(QEvent::User+1));
                QApplication::postEvent((QObject*)this, pEvent);

            }
        }
    }
}


void CALLBACK TimeDownLoadPos(LLONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, int index, NET_RECORDFILE_INFO recordfileinfo, LDWORD dwUser)
{
    Form1 * pThis = (Form1 *)dwUser;
    if(NULL == pThis)
    {
        return;
    }

    pThis->TimeDownLoadCallBack(lPlayHandle, dwTotalSize, dwDownLoadSize, index, recordfileinfo);

}


void Form1::TimeDownLoadCallBack(LLONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, int index, NET_RECORDFILE_INFO recordfileinfo)
{
    if(lPlayHandle == m_lDownLoadByTime)
    {
        if(-1 != dwDownLoadSize)
        {
            m_dwTimeTotalSize = dwTotalSize;
            m_dwTimeCurValue = dwDownLoadSize;
        }
        else
        {
            m_dwTimeTotalSize = 100;
            m_dwTimeCurValue = 0;
            if(0 != m_lDownLoadByTime)
            {
                //CLIENT_StopDownload(m_lDownLoadByTime);
                QEvent* pEvent = new QEvent(QEvent::Type(QEvent::User+2));
                QApplication::postEvent((QObject*)this, pEvent);
                //m_lDownLoadByTime = 0;
            }
        //ui->ButPlayByTime->setEnabled(true);
        //ui->ButStopPlayByTime->setEnabled(true);
        }
    }
}

void Form1::UpdataProgressbar()
{
    if(0 != m_hPlayBack)
    {
        switch(m_OperateType)
        {
        case 0:
            ui->progressBarByRecord->setRange(0, m_dwFileTotalSize);
            ui->progressBarByRecord->setValue(m_dwFileCurValue);
            break;
        case 1:
            ui->progressBarByTime->setRange(0, m_dwFileTotalSize);
            ui->progressBarByTime->setValue(m_dwFileCurValue);
            break;
        default:
            break;
        }

        /*if (-1 != m_nListViewCurIndex)
        {
            QString strBufSize = QString::number(m_nPlaybackBufSize, 10);
            QString name = "";
            char cTemp[20];
            sprintf(cTemp, "%04d", m_nListViewCurIndex);
            name = cTemp;

            QListViewItem *itemfind = listView1->findItem(name, 0);
            if (NULL != itemfind)
            {
             //   itemfind->setText(6, strBufSize);
            }
        }*/
    }

    else if (0 != m_lDownLoadByTime)
    {
        ui->progressBarByTime->setRange(0, m_dwTimeTotalSize);
        ui->progressBarByTime->setValue(m_dwTimeCurValue);
    }

    else if (0 != m_lDownLoadFile)
    {
        ui->progressBarByRecord->setRange(0, m_dwFileTotalSize);
        ui->progressBarByRecord->setValue(m_dwFileCurValue);
    }

    else
    {
        ui->progressBarByRecord->setRange(0, 1000);
        ui->progressBarByRecord->setValue(0);

        ui->progressBarByTime->setRange(0, 1000);
        ui->progressBarByTime->setValue(0);
    }
    if(ui->progressBarByRecord->value() == 0)
        ui->tabWidget2->setTabEnabled(1,true);
    if(ui->progressBarByTime->value() == 0)
        ui->tabWidget2->setTabEnabled(0,true);
}


bool Form1::eventFilter(QObject *obj, QEvent *event)//message filter
{
    if(event->type() == QEvent::Close)//windows close
    {
        destroyForm();
    }
    if(event->type() == QEvent::User)
    {
        QString strDevInfo;
        strDevInfo.append("Disconnect!");
        QMessageBox::information(0, "Promt", strDevInfo);
    }
    if(event->type() == QEvent::User+1)
    {
        CLIENT_StopDownload(m_lDownLoadFile);
        m_lDownLoadFile = 0;
        ui->ButDownLoad->setText("DownLoad");
        ui->ButPlayByRecord->setEnabled(true);
    }
    if(event->type() == QEvent::User+2)
    {
        CLIENT_StopDownload(m_lDownLoadByTime);
        m_lDownLoadByTime = 0;
        ui->ButPlayByTime->setEnabled(true);
        ui->ButStopPlayByTime->setEnabled(true);
    }
    if(event->type() == QEvent::User+3)
    {
        ui->ButPlayByRecord->setText("Play");
        ui->ButDownLoad->setEnabled(true);
        ui->ButLoadByTime->setEnabled(true);
        ui->ButStopLoadByTime->setEnabled(true);
        if(0 != m_hPlayBack)
        {
            CLIENT_StopPlayBack(m_hPlayBack);
            m_hPlayBack = 0;
            m_nListViewCurIndex = -1;
        }
    }
    return QWidget::eventFilter(obj, event);//don't eat event
}


void Form1::on_Login_clicked()
{
    QString strIp;
    QString strUserName;
    QString strDvrPort;
    QString strPassword;

    strIp = ui->lineEdit1->text();
    strUserName = ui->lineEdit4->text();
    strPassword = ui->lineEdit3->text();
    strDvrPort = ui->lineEdit2->text();
    ui->tabWidget2->setTabEnabled(0,true);
    ui->tabWidget2->setTabEnabled(1,true);

    NET_DEVICEINFO deviceInfo = {0};
    int error = 0;

    //get nunber
    bool numok = false;
    long lPort = strDvrPort.toLong(&numok);
    if(numok)
    {
        m_lLoginHandle = CLIENT_Login((char*)strIp.toUtf8().data(), lPort, (char*)strUserName.toUtf8().data(),(char*)strPassword.toUtf8().data(),  &deviceInfo, &error);

        if(m_lLoginHandle == 0)
        {
            if(error != 255)
			{
				QMessageBox::about(this, tr("Prompt"), tr("Login failed!"));
			}
			else
			{
				error = CLIENT_GetLastError();
				if(error ==NET_ERROR_MAC_VALIDATE_FAILED )
				{
					QMessageBox::about(this, tr("Prompt"), tr("Login failed! bad mac address"));
				}
				else if(error ==NET_ERROR_SENIOR_VALIDATE_FAILED)
				{
					QMessageBox::about(this, tr("Prompt"), tr("Login failed! senior validate failed"));
				}
			}
        }
        else
        {
            //cout<<"CLIENT_Login success, ip = "<<strIp<<endl;

            ui->ComboxChannel->clear();
            for(int i = 1; i <= deviceInfo.byChanNum; i++)
            {
                QString strdata = QString::number(i, 10);
              //  ui->ComboxChannel->insertItem(i, strdata);
              //  ui->ComboxChannel->setItemData(i,i);
				ui->ComboxChannel->addItem(strdata,i-1);
            }

            ui->Login->setEnabled(FALSE);
            ui->Logout->setEnabled(TRUE);
            ui->ButSearch->setEnabled(TRUE);
            ui->ButPlayByRecord->setEnabled(FALSE);
            ui->ButDownLoad->setEnabled(FALSE);
            ui->ButLoadByTime->setEnabled(TRUE);
            ui->ButPlayByTime->setEnabled(TRUE);
        }
    }
    else
    {
        int nRet = QMessageBox::warning(this,"Input Error",
                        "could not convert the port to numbers!\n"
                        "please try again!\n\n ",
                        "Retry",
                        "Quit",0,0,1);
        if (nRet == QMessageBox::Retry)
        {

        }
    }
}

void Form1::on_Logout_clicked()
{
    if(0 != m_hPlayBack)
     {
         CLIENT_StopPlayBack(m_hPlayBack);
         ui->ButPlayByRecord->setText("Play");
     }

     if(0 != m_lDownLoadFile)
     {
         CLIENT_StopDownload(m_lDownLoadFile);
         m_lDownLoadFile = 0;

         ui->ButDownLoad->setText("DownLoad");
         ui->ButPlayByRecord->setEnabled(true);
         m_dwFileTotalSize = 100;
         m_dwFileCurValue = 0;
     }

     if(0 != m_lDownLoadByTime)
     {
         CLIENT_StopDownload(m_lDownLoadByTime);
         m_lDownLoadByTime = 0;
     }

     if (m_lLoginHandle != 0)
     {
         BOOL bSuccess = CLIENT_Logout(m_lLoginHandle);

         if (TRUE == bSuccess)
         {
             ui->ComboxChannel->clear();

             InitData();
         }
         else
         {
             QMessageBox::about(this, tr("Promt"), tr("Logout failed!"));
         }
     }
}

void Form1::InitForm()
{
    CLIENT_Init(DisConnectFunc, (LDWORD)this);

    installEventFilter(this);//install filter

    InitData();

    m_counter = new QTimer( this );
    connect(m_counter, SIGNAL(timeout()), this, SLOT(UpdataProgressbar()));
    m_counter->start(1000);
}


void Form1::InitData()
{
    m_lLoginHandle = 0;
    m_lDownLoadFile = 0;
    m_lDownLoadByTime = 0;
    ui->EditCardNo->hide();
    m_dwFileCurValue = 0;
    m_dwFileTotalSize = 100;
    m_dwTimeCurValue = 0;
    m_dwTimeTotalSize = 100;
    m_FileName = "";
    m_hPlayBack = 0;
    m_nPlaybackBufSize = 0;
    m_nListViewCurIndex = -1;
    m_OperateType = 0;
    m_bExit = FALSE;
    m_bRecData = TRUE;

    ui->lineEdit3->setEchoMode(QLineEdit::Password);
    ui->Login->setEnabled(TRUE);
    ui->Logout->setEnabled(FALSE);
    ui->ButSearch->setEnabled(FALSE);
    ui->ButPlayByRecord->setEnabled(FALSE);
    ui->ButDownLoad->setEnabled(FALSE);
    ui->ButLoadByTime->setEnabled(FALSE);
    ui->ButPlayByTime->setEnabled(FALSE);
}


void Form1::destroyForm()
{
    cout<<"destroyed"<<endl;
    m_counter->stop();

    if(0 != m_hPlayBack)
    {
        CLIENT_StopPlayBack(m_hPlayBack);
    }

    if(0 != m_lDownLoadFile)
    {
        CLIENT_StopDownload(m_lDownLoadFile);
    }

    if(0 != m_lDownLoadByTime)
    {
        CLIENT_StopDownload(m_lDownLoadByTime);
    }

    if(0 != m_lLoginHandle)
    {
        BOOL bLogout = CLIENT_Logout(m_lLoginHandle);
    }

    CLIENT_Cleanup();
}

void Form1::on_ButSearch_clicked()
{
    if(0 != m_lLoginHandle )
      {
          int nMaxLen = 2000 * sizeof(NET_RECORDFILE_INFO);
          int nFileCount = 0;

          int nRecordFileType = 0;
          int nIndex = ui->comboRecordType->currentIndex();
          char *pchCardid = NULL;

          if (0 == nIndex )
          {
              nRecordFileType = 0;
          }
          else if(1 == nIndex)
          {
              nRecordFileType = 3;
          }
          else if(2 == nIndex)
          {
              nRecordFileType = 9;
          }
          else if(3 == nIndex)
          {
              nRecordFileType = 8;
              QString str = ui->EditCardNo->text();
              if(str != "")
              {
                  pchCardid = new char[20];
                  strcpy(pchCardid, str.toUtf8().data());
              }
          }

          int nChannelId = 0;
          nIndex = ui->ComboxChannel->currentIndex();
          nChannelId = ui->ComboxChannel->itemData(nIndex).toInt();

          NET_TIME netTimeFrom = {0};
          ConvertTime(ui->RecordStartTime->dateTime().date(),ui->RecordStartTime->dateTime().time(), &netTimeFrom);

          NET_TIME netTimeTo = {0};
          ConvertTime(ui->RecordEndTime->dateTime().date(),ui->RecordEndTime->dateTime().time(), &netTimeTo);

          BOOL bSuccess = CLIENT_QueryRecordFile(m_lLoginHandle,nChannelId,nRecordFileType, &netTimeFrom,&netTimeTo,pchCardid,m_netFileInfo,nMaxLen,&nFileCount,5000,FALSE);

          if(pchCardid != NULL)
          {
              delete[] pchCardid;
          }
          if(bSuccess)
          {
              if(0 == nFileCount)
              {
                  QMessageBox::information(this, tr("Promt"), tr("No iterm!"));
              }
              else
              {
                  AddRecordInfoToListView(m_netFileInfo,nFileCount);
                  ui->ButPlayByRecord->setEnabled(TRUE);
                  ui->ButDownLoad->setEnabled(TRUE);
              }
          }
          else
          {
              QMessageBox::information(this, tr("Promt"), tr("Fail to query record file!"));
          }
      }
      else
      {
          QMessageBox::information(this, tr("Promt"), tr("Please login first!"));
      }
}

void Form1::ConvertTime( QDate date, QTime time, NET_TIME * nettime)
{
    NET_TIME netTime = {0};
    netTime.dwYear = date.year();
    netTime.dwMonth = date.month();
    netTime.dwDay = date.day();
    netTime.dwHour = time.hour();
    netTime.dwMinute = time.minute();
    netTime.dwSecond =time.second();

    *nettime = netTime;
}

void Form1::AddRecordInfoToListView(LPNET_RECORDFILE_INFO pRecordFiles, int nFileCount)
{
    ui->listView1->clearContents();//all item delete
    ui->listView1->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int i = 0;
    int nRowCount = ui->listView1->rowCount();
    for(i = 0; i < nRowCount; i++)
    {
        ui->listView1->removeRow(0);
    }

    int nRowNum = 0;
    for(i=0;i<nFileCount;i++)
    {
        NET_RECORDFILE_INFO netFileInfo = pRecordFiles[i];

        char cTemp[20];
        sprintf(cTemp, "%04d", i);
        QString strNum = cTemp;

        QString strFileName = netFileInfo.filename;
        QString strFileLength = QString::number(netFileInfo.size, 10);

        QString 	strStartTime = "";
        QDate   	Startdate;
        QTime	StartTime;
        ConvertTimeToStr(netFileInfo.starttime, &Startdate, &StartTime);
        strStartTime = QString("%1, %2").arg(Startdate.toString("yyyy.MM.dd")).arg(StartTime.toString());

        QString 	strEndTime = "";
        QDate   	Enddate;
        QTime	EndTime;
        ConvertTimeToStr(netFileInfo.endtime, &Enddate, &EndTime);
        strEndTime = QString("%1, %2").arg(Enddate.toString("yyyy.MM.dd")).arg(EndTime.toString());

        QString strDisk = QString::number(netFileInfo.driveno, 10);

        nRowNum = ui->listView1->rowCount();
        ui->listView1->insertRow(nRowNum);
        QTableWidgetItem * pNumItem = new QTableWidgetItem(strNum);
        ui->listView1->setItem(nRowNum, 0, pNumItem);

        QTableWidgetItem * pFileNameItem = new QTableWidgetItem(strFileName);
        ui->listView1->setItem(nRowNum, 1, pFileNameItem);

        QTableWidgetItem * pFileLengthItem = new QTableWidgetItem(strFileLength);
        ui->listView1->setItem(nRowNum, 2, pFileLengthItem);

        QTableWidgetItem * pStartTimeItem = new QTableWidgetItem(strStartTime);
        ui->listView1->setItem(nRowNum, 3, pStartTimeItem);

        QTableWidgetItem * pEndTimeItem = new QTableWidgetItem(strEndTime);
        ui->listView1->setItem(nRowNum, 4, pEndTimeItem);

        QTableWidgetItem * pDiskItem = new QTableWidgetItem(strDisk);
        ui->listView1->setItem(nRowNum, 5, pDiskItem);
    }
}

void Form1::ConvertTimeToStr(NET_TIME nettime, QDate *date, QTime *time)
{
    date->setYMD(nettime.dwYear, nettime.dwMonth, nettime.dwDay);
    time->setHMS(nettime.dwHour, nettime.dwMinute, nettime.dwSecond);
}


void Form1::on_ButPlayByRecord_clicked()
{
    m_OperateType = 0;
    QTableWidgetItem * iterm = NULL;
    QString strText;
    strText = ui->ButPlayByRecord->text();
    ui->tabWidget2->setTabEnabled(1,true);

    if(strText == "Play")
    {
        cout<<"Play"<<endl;
        if(0 != ui->listView1->rowCount())
        {
            int nRowIndex = ui->listView1->currentRow();
            iterm = ui->listView1->item(nRowIndex, 0);
            if(NULL != iterm)
            {
                cout<<"Play in"<<endl;
                QString str = iterm->text();
                int nIndex =   str.toLong();

                NET_RECORDFILE_INFO fileInfo = {0};
                fileInfo = m_netFileInfo[nIndex];

                m_nListViewCurIndex = nIndex;

                m_nPlaybackBufSize = 0;

                PlayBackByFileServerMode(fileInfo);
                ui->tabWidget2->setTabEnabled(1,false);
            }
            else
            {
                QMessageBox::information(this, tr("Promt"), tr("Please a iterm!"));
            }
        }
        else
        {
            QMessageBox::information(this, tr("Promt"), tr("No iterms!"));
        }
    }
    else
    {
        if(0 != m_hPlayBack)
        {
            cout<<"stop"<<endl;
            BOOL bSuccess = CLIENT_StopPlayBack(m_hPlayBack);
            cout<<"CLIENT_StopPlayBack(m_hPlayBack)"<<bSuccess <<endl;
            if (TRUE == bSuccess)
            {
                m_hPlayBack = 0;
                m_nListViewCurIndex = -1;
                m_dwFileCurValue = 0;
                m_dwFileTotalSize = 100;

                m_nPlaybackBufSize = 0;
                ui->ButPlayByRecord->setText("Play");
                ui->ButDownLoad->setEnabled(true);
            }
            else
            {
                QMessageBox::information(0,"Promt","Fail to stop play!");
            }

            cout<<"stop"<<endl;
        }
    }
}

void Form1::PlayBackByFileServerMode(NET_RECORDFILE_INFO fileInfo)
{
    if(0 != m_lLoginHandle)
    {
        if(0 != m_hPlayBack)
        {
            BOOL bSuccess = CLIENT_StopPlayBack(m_hPlayBack);
            m_hPlayBack = 0;
        }

        long lHandle = CLIENT_PlayBackByRecordFileEx(m_lLoginHandle,&fileInfo,0,PlayCallBack,(LDWORD)this,DataCallBack,(LDWORD)this);
        if(0 != lHandle)
        {
                m_hPlayBack = lHandle;
                ui->ButPlayByRecord->setText("Stop");
                ui->ButDownLoad->setEnabled(false);
        }
        else
        {
                QMessageBox::information(this, tr("Promt"), tr("Playback failed!"));
        }
    }
    else
    {
            QMessageBox::information(this, tr("Promt"), tr("Please login first!"));
    }

}

void Form1::on_ButDownLoad_clicked()
{
    m_OperateType = 0;
    QString strText;
    strText = ui->ButDownLoad->text();
    QTableWidgetItem * iterm = NULL;
    if(strText == "DownLoad")
    {
        if(0 != ui->listView1->rowCount())
        {
            int nRowIndex =  ui->listView1->currentRow();
            iterm = ui->listView1->item(nRowIndex, 0);
            if(NULL != iterm)
            {
                QString str = iterm ->text();
                int nIndex = str.toLong();

                NET_RECORDFILE_INFO fileInfo = {0};
                fileInfo = m_netFileInfo[nIndex];
                BOOL bSuccess = DownLoadByFile(fileInfo, TRUE);
                if(bSuccess > 0)
                {
                    ui->ButDownLoad->setText("Stop");
                    ui->ButPlayByRecord->setEnabled(false);
                }
            }
            else
            {
                QMessageBox::information(this, tr("Promt"), tr("Please a iterm!"));
            }
        }
        else
        {
            QMessageBox::information(this, tr("Promt"), tr("No iterms!"));
        }
    }
    else //stop
    {
        NET_RECORDFILE_INFO fileInfo = {0};
        BOOL bSuccess = DownLoadByFile(fileInfo, FALSE);
        if(bSuccess)
        {
            ui->ButDownLoad->setText("DownLoad");
            ui->ButPlayByRecord->setEnabled(true);
            m_dwFileTotalSize = 100;
            m_dwFileCurValue = 0;
            long hDownLoadFile = m_lDownLoadFile;
            if(0 != hDownLoadFile)
            {
                CLIENT_StopDownload(hDownLoadFile);
                m_lDownLoadFile = 0;
            }
        }
    }
}

BOOL Form1::DownLoadByFile(NET_RECORDFILE_INFO fileInfo,BOOL bLoad)
{
    BOOL bRet = FALSE;
    if(bLoad)
    {
        if(0 != m_lLoginHandle)
        {
            if(0 != m_lDownLoadFile)
                        {
                BOOL bSuccess = CLIENT_StopDownload(m_lDownLoadFile);
                if(bSuccess)
                {
                    m_lDownLoadFile = 0;
                }
                else
                {
                    QMessageBox::information(this, tr("Promt"), tr("Fail to stop download!"));
                }
            }

            QFileDialog * fDialog = new QFileDialog(this);

            m_FileName = fDialog->getSaveFileName(this,"download",
                               "download.dav", "download (*.dav *.mp4 *.jpg)");

            if(m_FileName.isNull() == TRUE)
            {
                return -1;
            }

        /*{
            FILE* file = fopen((char *)m_FileName.toUtf8().data(), "r");
            if(NULL != file)
            {
                    fclose(file);
                    if(QMessageBox::No == QMessageBox::information(this, tr("Promt"), tr("File is existing, do you want cover it"), QMessageBox::Yes, QMessageBox::No))
                    {
                        printf("File is exiting, choose not cover it.\n");
                        return -1;
                }
        }
        }*/

            long lRet = CLIENT_DownloadByRecordFile(m_lLoginHandle, &fileInfo,  (char *)m_FileName.toUtf8().data(), PlayCallBack, (LDWORD)this);

            if(0 != lRet)
            {
                m_lDownLoadFile = lRet;
                bRet = TRUE;
            }
            else
            {
                QMessageBox::information(this, tr("Promt"), tr("Fail to download!"));
            }

            delete fDialog;

        }
    }
    else
    {
        if(0 != m_lDownLoadFile)
        {
            BOOL bSuccess = CLIENT_StopDownload(m_lDownLoadFile);

            if(bSuccess)
            {
                m_lDownLoadFile = 0;
                bRet = TRUE;
            }
            else
            {
                QMessageBox::information(this, tr("Promt"), tr("Fail to stop download!"));
            }
        }
    }
    return bRet;
}

void Form1::on_ButPlayByTime_clicked()
{
    m_OperateType = 1;

    int nChannelId = 0;
    int nIndex = ui->ComboxChannel->currentIndex();
    nChannelId = ui->ComboxChannel->itemData(nIndex).toInt();

    NET_TIME netTimeFrom = {0};
    ConvertTime(ui->dateTimeStart->dateTime().date(),ui->dateTimeStart->dateTime().time(), &netTimeFrom);

    NET_TIME netTimeTo = {0};
    ConvertTime(ui->dateTimeEnd->dateTime().date(),ui->dateTimeEnd->dateTime().time(), &netTimeTo);

    if(0 != m_lLoginHandle)
    {
        if(0 != m_hPlayBack)
        {
            BOOL bSuccess = CLIENT_StopPlayBack(m_hPlayBack);

            m_hPlayBack = 0;
        }

        long lHandle = CLIENT_PlayBackByTimeEx(m_lLoginHandle,nChannelId,&netTimeFrom,&netTimeTo,0,PlayCallBack,(LDWORD)this,DataCallBack,(LDWORD)this);
        if(0 != lHandle)
        {
                m_hPlayBack = lHandle;
                ui->ButLoadByTime->setEnabled(false);
                ui->ButStopLoadByTime->setEnabled(false);
                 ui->tabWidget2->setTabEnabled(0,false);
        }
        else
        {
                QMessageBox::information(this, tr("Promt"), tr("Playback failed!"));
        }
    }
    else
    {
        QMessageBox::information(this, tr("Promt"), tr("Please login first!"));
    }
}

void Form1::on_ButStopPlayByTime_clicked()
{
    m_OperateType = 1;

    if(0 != m_hPlayBack)
    {
        BOOL bSuccess = CLIENT_StopPlayBack(m_hPlayBack);

        m_hPlayBack = 0;
        m_dwFileCurValue = 0;
        m_dwFileTotalSize = 100;

        ui->ButLoadByTime->setEnabled(true);
        ui->ButStopLoadByTime->setEnabled(true);
         ui->tabWidget2->setTabEnabled(0,true);
    }
}

int Form1::CompareTime(NET_TIME *pSrcTime, NET_TIME *pDestTime)
{
    struct tm tSrc;
    tSrc.tm_year=pSrcTime->dwYear-1900;
    tSrc.tm_mon=pSrcTime->dwMonth-1;
    tSrc.tm_mday=pSrcTime->dwDay;
    tSrc.tm_hour=pSrcTime->dwHour;
    tSrc.tm_min=pSrcTime->dwMinute;
    tSrc.tm_sec=pSrcTime->dwSecond;
    tSrc.tm_isdst=-1;

    time_t ltSrc;
    ltSrc=mktime(&tSrc);

    struct tm tDst;
    tDst.tm_year=pDestTime->dwYear-1900;
    tDst.tm_mon=pDestTime->dwMonth-1;
    tDst.tm_mday=pDestTime->dwDay;
    tDst.tm_hour=pDestTime->dwHour;
    tDst.tm_min=pDestTime->dwMinute;
    tDst.tm_sec=pDestTime->dwSecond;
    tDst.tm_isdst=-1;

    time_t ltDst;
    ltDst=mktime(&tDst);

    int nRet = ltDst - ltSrc;

    return nRet;
}

void Form1::on_ButLoadByTime_clicked()
{
    int nChannelId = 0;
    int nIndex = ui->ComboxChannel->currentIndex();
    nChannelId = ui->ComboxChannel->itemData(nIndex).toInt();

    NET_TIME netTimeFrom = {0};
    ConvertTime(ui->dateTimeStartLoad->dateTime().date(),ui->dateTimeStartLoad->dateTime().time(), &netTimeFrom);

    NET_TIME netTimeTo = {0};
    ConvertTime(ui->dateTimeEndLoad->dateTime().date(),ui->dateTimeEndLoad->dateTime().time(), &netTimeTo);

    int nRet = CompareTime(&netTimeFrom, &netTimeTo);
    if(nRet< 0 || nRet > 60*60)
    {
        QMessageBox::information(this, tr("Promt"), tr("bad time region, the region is overstep 1 hour or less than 0"));
        return;
    }
    if(0 != m_lLoginHandle)
    {
        if(0 != m_lDownLoadByTime)
        {
            BOOL bSuccess = CLIENT_StopDownload(m_lDownLoadByTime);
            if(bSuccess)
            {
                m_lDownLoadByTime = 0;
                m_dwTimeTotalSize = 100;
                m_dwTimeCurValue = 0;
            }
            else
            {
                QMessageBox::information(this, tr("Promt"), tr("Fail to stop download!"));
            }
        }

        QFileDialog * fDialog = new QFileDialog(this);

        QString   strFileName = fDialog->getSaveFileName(this,"download",
                                                         "download.dav", "download (*.dav *.mp4 )");


        if(strFileName.isNull() == TRUE)
        {
            return;
        }

        /*{
            FILE* file = fopen((char *)strFileName.ascii(), "r");
            if(NULL != file)
            {
                fclose(file);
                if(QMessageBox::No == QMessageBox::information(this, tr("Promt"), tr("File is existing, do you want cover it"), QMessageBox::Yes, QMessageBox::No))
                {
                    printf("File is exiting, choose not cover it.\n");
                    return;
                }
             }
        }*/


        long lRet = CLIENT_DownloadByTime(m_lLoginHandle, nChannelId, 0, &netTimeFrom, &netTimeTo, (char *)strFileName.toUtf8().data(),TimeDownLoadPos, (LDWORD)this);

        if(0 != lRet)
        {
            m_lDownLoadByTime = lRet;
            ui->ButPlayByTime->setEnabled(false);
            ui->ButStopPlayByTime->setEnabled(false);
        }
        else
        {
            QMessageBox::information(this, tr("Promt"), tr("Fail to download!"));
        }

    }
}

void Form1::on_ButStopLoadByTime_clicked()
{
    if(0 != m_lDownLoadByTime)
    {
       BOOL bSuccess = CLIENT_StopDownload(m_lDownLoadByTime);
       if(bSuccess)
       {
           m_lDownLoadByTime = 0;
           m_dwTimeTotalSize = 100;
           m_dwTimeCurValue = 0;
           ui->ButPlayByTime->setEnabled(true);
           ui->ButStopPlayByTime->setEnabled(true);
       }
       else
       {
           QMessageBox::information(this, tr("Promt"), tr("Fail to Stop download!"));
       }
   }
}

void Form1::on_Form1_destroyed()
{
    destroyForm();
}
