#include "form1.h"
#include "ui_form1.h"
#include <qmessagebox.h>
#include <QStringList>
#include <QTextCodec>
#include <QDebug>

#include"dhnetsdk.h"
#include "./include/dhmutex.h"
#include "UserDefine.h"
#include<iostream>
#include<stdlib.h>
#include <string>
#include <stdio.h>
using namespace std;

#define DEMO_SDK_WAITTIME 10000 

void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
    form1 * pThis = (form1 *)dwUser;
    if(NULL == pThis)
    {
        return;
    }
    //deal
    QEvent*  eventDisconnect = new QEvent(QEvent::User);
    QApplication::postEvent((QObject*)pThis, eventDisconnect);
    return;
}

form1::form1(QWidget *parent) :
QDialog(parent),
ui(new Ui::form1)
{
    ui->setupUi(this);
}

form1::~form1()
{
    delete ui;
}

void form1::InitForm()
{
    CLIENT_Init(DisConnectFunc, (LDWORD)this);
	
    installEventFilter(this);//install filter
	
    InitData();
	
	//    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
	//   QFont font("Times", 12, QFont::Normal, FALSE);
	
	//  this->setFont (font);
    // m_counter = new QTimer( this );
    // connect(m_counter, SIGNAL(timeout()), this, SLOT(UpdataProgressbar()));
    // m_counter->start(1000);
	connect(this, SIGNAL(ShowLogItem(QString&, QString&, QString&)), this, SLOT(ShowListLogItem(QString&, QString&, QString&)));
}

void form1::InitData()
{
    m_lLoginHandle = 0;
    m_nPreStartNum = 0;
    m_nPreEndNum = 0;
	
    ui->lineEdit3->setEchoMode(QLineEdit::Password);
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QDateTime curDateTime(date, time);
    ui->StartdateTime->setDisplayFormat("yyyy.MM.dd hh:mm:ss");
    ui->StartdateTime->setDateTime(curDateTime);
    ui->EnddateTime->setDisplayFormat("yyyy.MM.dd hh:mm:ss");
    ui->EnddateTime->setDateTime(curDateTime);
    ui->EnddateTime->setEnabled(FALSE);
    ui->EnddateTime->setEnabled(FALSE);
    ui->PageLine->setEnabled(FALSE);
    ui->ButXMLQuery->hide();
}

void form1::destroyForm()
{
    cout<<"destroyed"<<endl;
    CLIENT_Cleanup();
    // m_counter->stop();
}


void form1::on_Login_clicked()
{
    QString strIp;
    QString strUserName;
    QString strDvrPort;
    QString strPassword;
	
    strIp = ui->lineEdit1->text();
    strUserName = ui->lineEdit4->text();
    strPassword = ui->lineEdit3->text();
    strDvrPort = ui->lineEdit2->text();
	
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
            //tell the device's log style
            memset(&m_stuEnable, 0, sizeof(DH_DEV_ENABLE_INFO));
            int nRetLen = 0;
            BOOL bRet = CLIENT_QuerySystemInfo(m_lLoginHandle, ABILITY_DEVALL_INFO, (char*)&m_stuEnable, sizeof(DH_DEV_ENABLE_INFO), &nRetLen,3000);
			
			if (!bRet)
			{
				QMessageBox::about(this, tr("Prompt"), tr("Get device cap failed!"));
			}
			printf("EN_LOG: 0x%x !\n", m_stuEnable.IsFucEnable[EN_LOG]);
			if (m_stuEnable.IsFucEnable[EN_LOG] != 0)
			{
                m_nPageLine = 100;
				
                ui->StartdateTime->setEnabled(TRUE);
                ui->EnddateTime->setEnabled(TRUE);
                ui->PageLine->setEnabled(TRUE);
			}
			
            ui->Login->setEnabled( FALSE );
            ui->Logout->setEnabled( TRUE );
            ui->ButQuery->setEnabled( TRUE );
            ui->ButXMLQuery->setEnabled( FALSE );
        }
    }
    else
    {
        int nRet = QMessageBox::warning(this, tr("Input Error"),
			tr("could not convert the port to numbers!\n"
			"please try again!\n\n "),
			tr("Retry"),
			tr("Quit"), 0, 0, 1);
        if (nRet == QMessageBox::Retry)
        {
			
        }
    }
}

void form1::on_Logout_clicked()
{
    if (m_lLoginHandle != 0)
	{
		BOOL bSuccess = CLIENT_Logout(m_lLoginHandle);
		cout<<"CLIENT_Logout: "<<bSuccess<<endl;
		
		if (TRUE == bSuccess)
		{
			m_lLoginHandle = 0;
			ui->Login->setEnabled( TRUE );
			ui->Logout->setEnabled( FALSE );
			ui->ButQuery->setEnabled( FALSE );
			ui->ButXMLQuery->setEnabled( FALSE );
			ui->StartdateTime->setEnabled( FALSE );
			ui->EnddateTime->setEnabled( FALSE );
			ui->ButPrePage->setEnabled( FALSE );
			ui->ButNextPage->setEnabled( FALSE );
			ui->PageLine->setEnabled( FALSE );
			
			int nRowCount = ui->listViewLog->rowCount();
			for(int i = nRowCount - 1; i >= 0; i--)
			{
				ui->listViewLog->removeRow(i);
			}
		}
		else
		{
			QMessageBox::about(this, tr("Prompt"), tr("Logout Failed!"));
		}
	}
	
}

void form1::ConvertTimeToStr(DHDEVTIME *nettime, QDate *date, QTime *time)
{
    date->setYMD(nettime->year + 2000, nettime->month, nettime->day);
    time->setHMS(nettime->hour, nettime->minute, nettime->second);
}

void form1::on_ButQuery_clicked()
{
    char szTmpLog[1024] = {0}; // using for log output
    if(0 != m_lLoginHandle)
	{
        if (m_stuEnable.IsFucEnable[EN_LOG] == 0)
        {
			char* recBuf = new char[1024*sizeof(DH_LOG_ITEM)];
                        if (NULL == recBuf) return ;
			memset(recBuf, 0, 1024*sizeof(DH_LOG_ITEM));
			int nRetLen = 0;
			int nIndex = ui->comboxType->currentIndex();
			if(nIndex >= 0)
			{
				BOOL bSuccess = CLIENT_QueryLogEx(m_lLoginHandle, DHLOG_ALL, recBuf, 1024*sizeof(DH_LOG_ITEM), &nRetLen, NULL, DEMO_SDK_WAITTIME);
                                sprintf(szTmpLog, "CLIENT_QueryLogEx query DHLOG_ALL ... return %s , ret log num is %d !\n", bSuccess>0?"ok":"failure", nRetLen%sizeof(DH_LOG_ITEM));
                                printf(szTmpLog);qDebug()<<szTmpLog;
				if(bSuccess)
				{
					if ((nRetLen%sizeof(DH_LOG_ITEM)) == 0)
					{
						char szbuf[128] = {0};
						sprintf(szbuf, "ncount = %d, index= %d\n", nRetLen%sizeof(DH_LOG_ITEM),nIndex);
						printf(szbuf);

						int nRowCount = ui->listViewLog->rowCount();
                                                for(int i = nRowCount - 1; i >= 0; i--)
						{
							ui->listViewLog->removeRow(i);
						}
						
						DisplayQueryResult(recBuf,nRetLen);
						
						if(0 == ui->listViewLog->rowCount())
						{
							QMessageBox::about(this, tr("Promt"), tr("No iterms!"));
						}
					}
					else
					{
						int nRowCount = ui->listViewLog->rowCount();
                                                for(int i = nRowCount - 1; i >= 0; i--)
						{
							ui->listViewLog->removeRow(i);
						}
						QMessageBox::about(this, tr("Promt"), tr("Data check error!"));
					}
				}
				else
				{
					int nRowCount = ui->listViewLog->rowCount();
					for(int i = nRowCount - 1; i >= 0; i--)
					{
						ui->listViewLog->removeRow(i);
					}
					QMessageBox::about(this, tr("Promt"), tr("Fail to query!"));
				}
			}
                        if (NULL != recBuf) delete[] recBuf;
		}
		else
		{
			if(ui->StartdateTime->dateTime()>= ui->EnddateTime->dateTime())
			{
				QMessageBox::about(this, tr("Promt"), tr("Bad time set!!"));
				return;
			}
			
			//get nunber
			bool numok = false;
			int nPageLine = ui->PageLine->text().toInt(&numok);
			if(!numok)
			{
				QMessageBox::about(this, "Promt", tr("Bad number set!"));
				return;
			}

			m_nPageLine = nPageLine;
                        m_nPageLineOld = m_nPageLine;
			
			QUERY_DEVICE_LOG_PARAM stuLogParam;
			memset(&stuLogParam, 0, sizeof(QUERY_DEVICE_LOG_PARAM));
			stuLogParam.emLogType = (DH_LOG_QUERY_TYPE)ui->comboxType->currentIndex();
			
			stuLogParam.nStartNum = 0;
			stuLogParam.nEndNum = m_nPageLine -1;
			stuLogParam.nLogStuType = 1;
			m_nPreEndNum = stuLogParam.nEndNum + 1;
			m_nPreStartNum = stuLogParam.nStartNum;
			stuLogParam.stuStartTime.dwYear = ui->StartdateTime->date().year();
			stuLogParam.stuStartTime.dwMonth = ui->StartdateTime->date().month();
			stuLogParam.stuStartTime.dwDay = ui->StartdateTime->date().day();
			stuLogParam.stuStartTime.dwHour = ui->StartdateTime->time().hour();
			stuLogParam.stuStartTime.dwMinute = ui->StartdateTime->time().minute();
			stuLogParam.stuStartTime.dwSecond = ui->StartdateTime->time().second();
			
			stuLogParam.stuEndTime.dwYear = ui->EnddateTime->date().year();
			stuLogParam.stuEndTime.dwMonth = ui->EnddateTime->date().month();
			stuLogParam.stuEndTime.dwDay = ui->EnddateTime->date().day();
			stuLogParam.stuEndTime.dwHour = ui->EnddateTime->time().hour();
			stuLogParam.stuEndTime.dwMinute = ui->EnddateTime->time().minute();
			stuLogParam.stuEndTime.dwSecond = ui->EnddateTime->time().second();
			
			DH_DEVICE_LOG_ITEM_EX* szLogInfos = new DH_DEVICE_LOG_ITEM_EX[1024];
			if(szLogInfos == NULL)
			{
				return;
			}
			int nRetLogNum = 0;
			BOOL bRet = CLIENT_QueryDeviceLog(m_lLoginHandle, &stuLogParam, (char*)szLogInfos, 1024 * sizeof(DH_DEVICE_LOG_ITEM_EX), &nRetLogNum,DEMO_SDK_WAITTIME);
                        sprintf(szTmpLog, "CLIENT_QueryDeviceLog query [%d, %d] ... return %s, nRetLogNum is %d !\n", stuLogParam.nStartNum, stuLogParam.nEndNum, bRet>0?"ok":"failure", nRetLogNum);
                        printf(szTmpLog);qDebug()<<szTmpLog;

                        if (bRet) // page page searching successfully
                        {
                                //display log info
				if (nRetLogNum <= 0)
				{
					
					QMessageBox::about(this, tr("Promt"), tr("No record!"));
                                        ui->ButPrePage->setEnabled(FALSE);
                                        ui->ButNextPage->setEnabled(FALSE);
					delete[] szLogInfos;
					return;
				}
				// not enough, continue
				else if (nRetLogNum < m_nPageLine)
				{
                                    ui->ButPrePage->setEnabled(FALSE); // prepage button disable

					DisPlayNewLogInfo(szLogInfos, nRetLogNum);
				
					int iLoop = 0;
					int nTotal = nRetLogNum;
					do
					{
						memset(szLogInfos, 0, sizeof(DH_DEVICE_LOG_ITEM_EX) * 1024);
						stuLogParam.nStartNum = m_nPreStartNum + nTotal;
						stuLogParam.nEndNum = m_nPreEndNum - 1;
						bRet = CLIENT_QueryDeviceLog(m_lLoginHandle, &stuLogParam, (char*)szLogInfos, 1024 * sizeof(DH_DEVICE_LOG_ITEM_EX), &nRetLogNum,3*DEMO_SDK_WAITTIME);
                                                sprintf(szTmpLog, "loop[%d], CLIENT_QueryDeviceLog query [%d, %d] ... return %s, nRetLogNum is %d !\n", ++iLoop,stuLogParam.nStartNum, stuLogParam.nEndNum, bRet>0?"ok":"failure", nRetLogNum);
                                                printf(szTmpLog);qDebug()<<szTmpLog;
						if (bRet)
                                                {
                                                    // no more
                                                    if (nRetLogNum <= 0)
                                                    {
                                                        break;
                                                    }
                                                    DisPlayNewLogInfo(szLogInfos, nRetLogNum, TRUE);
                                                    nTotal += nRetLogNum;
						}
						else
						{
                                                    ui->ButNextPage->setEnabled(TRUE);
                                                    break;
						}
						
					} while (nTotal < m_nPageLine);
				}
				else
				{
                                    ui->ButPrePage->setEnabled(FALSE); // prepage button disable

					DisPlayNewLogInfo(szLogInfos, nRetLogNum);
				}
				
				//tell if there has more logs
				memset(szLogInfos, 0, sizeof(DH_DEVICE_LOG_ITEM_EX) * 1024);
				stuLogParam.nStartNum = m_nPreEndNum;
				stuLogParam.nEndNum = m_nPreEndNum + 2;
				bRet = CLIENT_QueryDeviceLog(m_lLoginHandle, &stuLogParam, (char*)szLogInfos, 1024 * sizeof(DH_DEVICE_LOG_ITEM_EX), &nRetLogNum,DEMO_SDK_WAITTIME);
                                sprintf(szTmpLog, "2 CLIENT_QueryDeviceLog query [%d, %d] ... return %s, nRetLogNum is %d !\n", stuLogParam.nStartNum, stuLogParam.nEndNum, bRet>0?"ok":"failure", nRetLogNum);
                                printf(szTmpLog);qDebug()<<szTmpLog;
				if (bRet)
				{
					if (nRetLogNum > 0)
					{
						ui->ButPrePage->setEnabled(FALSE);
						ui->ButNextPage->setEnabled(TRUE);
					}
					else
					{
						ui->ButPrePage->setEnabled(FALSE);
						ui->ButNextPage->setEnabled(FALSE);
					}
				}
				else
				{
					ui->ButPrePage->setEnabled(FALSE);
					ui->ButNextPage->setEnabled(TRUE);
				}
			}
                        else // page page searching failure
			{
				int nRowCount = ui->listViewLog->rowCount();
				for(int i = nRowCount - 1; i >= 0; i--)
				{
					ui->listViewLog->removeRow(i);
				}
				QMessageBox::about(this, tr("Promt"), tr("Query log failed!"));
			}
			
			delete[] szLogInfos;
          }
       }
       else
       {
           QMessageBox::about(this, tr("Promt"), tr("Please login first!"));
       }
}

int/*void*/ form1::TransLogInfo(void *pLoginfo, int nStructType, QString &strLogType, QString &strLogTime, QString &strLogContext)
{
	int nRet = 1;
    if (pLoginfo == NULL)
    {
		nRet = 0;
        return nRet;
    }
    QDate Date;
    QTime Time;
	
    DHDEVTIME stuTime = {0};
    int nLogType = 0;
    DH_LOG_ITEM *pLogItem = NULL;
    if (nStructType == 0)
    {
		// new log
		DH_DEVICE_LOG_ITEM_EX *pLog = (DH_DEVICE_LOG_ITEM_EX*)pLoginfo;
		nLogType = pLog->nLogType;
		memcpy(&stuTime, &pLog->stuOperateTime, sizeof(DHDEVTIME));
		strLogContext = QString::fromLocal8Bit(pLog->szDetailContext);
	}
	else if (nStructType == 1)
	{
        // old log
        pLogItem = (DH_LOG_ITEM*)pLoginfo;
        nLogType = pLogItem->type;
        memcpy(&stuTime, &pLogItem->time, sizeof(DHDEVTIME));
	}
	
	ConvertTimeToStr(&stuTime, &Date, &Time);
	strLogTime = QString("%1, %2").arg(Date.toString("yyyy.MM.dd")).arg(Time.toString());
	
	switch(nLogType)
	{
	case DH_LOG_REBOOT:
        {
            strLogType = tr("Restart Device");
            if (pLogItem != NULL)
            {
				if (0 == pLogItem->data)
				{
                    strLogContext = tr("Normal Reboot!");
				}
				else
				{
					strLogContext = tr("Exceptional Reboot!");
				}
            }
        }
		break;
	case DH_LOG_SHUT:
		{
			strLogType = tr("Shut dowm");
			
			if(pLogItem != NULL)
			{
				DHDEVTIME *shutTime = (DHDEVTIME *)&pLogItem->context[0];
				ConvertTimeToStr(shutTime, &Date, &Time);
				strLogContext = QString("time:%1, %2").arg(Date.toString("yyyy.MM.dd")).arg(Time.toString());
			}
		}
		break;
	case DH_LOG_REPORTSTOP:
		{
			strLogType = tr("Report Stop");
		}
		break;
	case DH_LOG_REPORTSTART:
		{
			strLogType = tr("Report Start");
		}
		break;
	case DH_LOG_UPGRADE:
		{
			strLogType = tr("Upgrade Device");
			if (pLogItem !=NULL)
			{
				DHDEVTIME *shutTime = (DHDEVTIME*)pLogItem->context;
				ConvertTimeToStr(shutTime, &Date, &Time);
				strLogContext = QString("time:%1, %2").arg(Date.toString("yyyy.MM.dd")).arg(Time.toString());
				
				if (0 == pLogItem->data)
				{
					strLogContext = tr("Upgrade successful, ") + strLogContext;
				}
				else
				{
					strLogContext = tr("Upgrade failed, ") + strLogContext;
				}
			}
			
		}
		break;
	case DH_LOG_SYSTIME_UPDATE:
		{
			strLogType = tr("System Time Update");
			if (pLogItem != NULL)
			{
				strLogContext = tr("System Time Update");
			}
		}
		break;
	case DH_LOG_GPS_TIME_UPDATE:
		{
			strLogType = tr("GPS Time Update");
			if (pLogItem != NULL)
			{
				strLogContext = tr("GPS Time Update");
			}
		}
		break;		
	case DH_LOG_AUDIO_TALKBACK:
		{
			strLogType = tr("Audio Talkback");
			if (pLogItem != NULL)
			{
				if (0 == pLogItem->data)
				{
					strLogContext = tr("Audio Talkback OFF");
				}
				else
				{
					strLogContext = tr("Audio Talkback ON");
				}
			}
		}
		break;
	case DH_LOG_COMM_ADAPTER:
		{
			strLogType = tr("COMM Adapter");
			if (pLogItem != NULL)
			{
				if (0 == pLogItem->data)
				{
					strLogContext = tr("COMM Adapter OFF");
				}
				else
				{
					strLogContext = tr("COMM Adapter ON");
				}
			}
		}
		break;
	case DH_LOG_NET_TIMING:
		{
			strLogType = tr("Time Update");
			if (pLogItem != NULL)
			{
				strLogContext = tr("Time Update");
			}
		}
		break;		
	case DH_LOG_CONFSAVE:
		{
			strLogType = tr("Save Config Info");
			if (pLogItem != NULL)
			{
				strLogContext = tr("config type: ");
				strLogContext += ConvertCfgType(pLogItem);
			}
		}
		break;
	case DH_LOG_CONFLOAD:
		{
			strLogType = tr("Load Config Info");
			if (pLogItem != NULL)
			{
				strLogContext = tr("config type: ");
				strLogContext += ConvertCfgType(pLogItem);
			}
			
		}
		break;
	case DH_LOG_FSERROR:
		{
			strLogType = tr("File System Error");
			if (pLogItem != NULL)
			{
				strLogContext = tr("File system appears error");
			}
		}
		break;
	case DH_LOG_HDD_WERR:
		{
			strLogType = tr("Write DISK Error");
			if (pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = tr("Disk number:") + strdata;
			}
		}
		break;
	case DH_LOG_HDD_RERR:
		{
			strLogType = tr("Read DISK Error");
			if (pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = tr("Disk number:") + strdata;
			}
		}
		break;
	case DH_LOG_HDD_TYPE:
		{
			strLogType = tr("Set DISK Type");
			if (pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = tr("Disk number:") + strdata;
			}
		}
		break;
	case DH_LOG_HDD_FORMAT:
		{
			strLogType = tr("Format DISK");
			if (pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = tr("Disk number:") + strdata;
			}
		}
		break;
	case DH_LOG_HDD_NOSPACE:
		{
			strLogType = tr("Storage device is no space");
			if (pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = tr("The residual percentage of storage device is:") + strdata;
			}
		}
		break;
	case DH_LOG_HDD_TYPE_RW:
		{
			strLogType = tr("Set Storage device Type");
			if (pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = QString(tr("Storage device No.%1(read-write)").arg(strdata));
			}
		}
		break;
	case DH_LOG_HDD_TYPE_RO:
		{
			strLogType = tr("Set Storage device Type");
			if (pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = QString(tr("Storage device No.%1(read-only)").arg(strdata));
			}
		}
		break;
	case DH_LOG_HDD_TYPE_RE:
		{
			strLogType = tr("Set Storage device Type");
			if (pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = QString(tr("Storage device No.%1(Redundancye)").arg(strdata));
			}
		}
		break;
	case DH_LOG_HDD_TYPE_SS:
		{
			strLogType = tr("Set Storage device Type");
			if (pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = QString(tr("Storage device No.%1(snapshot)").arg(strdata));
			}
		}
		break;
	case DH_LOG_HDD_NONE:
		{
			strLogType = tr("No hard disk recording");
			if (pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = QString(tr("Storage device No.%1(None)").arg(strdata));
			}
		}
		break;
	case DH_LOG_HDD_NOWORKHDD:
		{
			strLogType = tr("None WORKHDD");
			if (pLogItem != NULL)
			{
				strLogContext = tr("There is no work disk");
			}
		}
		break;
	case DH_LOG_HDD_TYPE_BK:
		{
			strLogType = tr("Set Storage device Type");
			if (pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = QString(tr("Storage device No.%1(Backup)").arg(strdata));
			}
		}
		break;
	case DH_LOG_HDD_TYPE_REVERSE:
		{
			strLogType = tr("Set Storage device Type");
			if (pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = QString(tr("Storage device No.%1(Reverse)").arg(strdata));
			}
		}
		break;
	case DH_LOG_HDD_START_INFO:
		{
			//记录开机时的硬盘信息
			strLogType = tr("Storage device infomation");
			if (pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = QString(tr("HDD amount %1 ,Working HDD %2").arg(strdata).arg((char *)pLogItem->context));
				
			}
		}
		break;
	case DH_LOG_HDD_WORKING_DISK:
		{
			strLogType = tr("Storage device work disk");
		}
		break;
	case DH_LOG_HDD_OTHER_ERROR:
		{
			strLogType = tr("Storage device other errors");
		}
		break;
	case DH_LOG_HDD_SLIGHT_ERR:
		{
			//硬盘轻微问题
			strLogType = tr("Storage device problem");
		}
		break;
	case DH_LOG_HDD_SERIOUS_ERR:
		{
			//硬盘严重问题
			strLogType = tr("Storage device problem");
		}	
		break;
	case DH_LOG_HDD_NOSPACE_END: 
		{
			strLogType = tr("Storage device is no space end");
			if (pLogItem != NULL)
			{
			    QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = QString(tr("Current DISK is enough space，disk number：%1").arg(strdata));
			}
		}
		break;
	case DH_LOG_HDD_TYPE_RAID_CONTROL: 
		{
			strLogType = tr("Raid Operation");
		}
		break;
	case DH_LOG_HDD_TEMPERATURE_HIGH: 
		{
			strLogType = tr("Temperature too high");
		}
		break;	
	case DH_LOG_HDD_TEMPERATURE_LOW: 
		{
			strLogType = tr("Temperature too low");
		}
		break;		
	case DH_LOG_HDD_ESATA_REMOVE: 
		{
			strLogType = tr("Remove eSATA");
		}
		break;				
	case DH_LOG_ALM_IN:
		{
			strLogType = tr("Alarm Input");
			if (pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = QString(tr("Alarm Input，channel:%1").arg(strdata));
			}
		}
		break;
	case DH_LOG_NETALM_IN:
		{
			strLogType = tr("Net Alarm Input");
			if (pLogItem != NULL)
			{
				strLogContext = QString(tr("Alarm Input，channel:%1").arg((char *)pLogItem->context));
			}
		}
		break;
	case DH_LOG_ALM_END:
		{
			strLogType = tr("Alarm Input End");
			if (pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = QString(tr("Alarm Input End，channel:%1").arg(strdata));
			}
		}
		break;
	case DH_LOG_LOSS_IN:
		{
			strLogType = tr("Video Loss");
			if (pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = QString(tr("Channel No.:%1").arg(strdata));
			}
		}
		break;
	case DH_LOG_LOSS_END:
		{
			strLogType = tr("Video Loss End");
			if (pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = QString(tr("Channel No.:%1").arg(strdata));
			}
		}
		break;
	case DH_LOG_MOTION_IN:
		{
			strLogType = tr("Motion Detect");
			if (pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = QString(tr("Channel No.:%1").arg(strdata));
			}
		}
		break;
	case DH_LOG_MOTION_END:
		{
			strLogType = tr("Motion Detect End");
			if (pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = QString(tr("Channel No.:%1").arg(strdata));
			}
		}
		break;
	case DH_LOG_ALM_BOSHI:
		{
			strLogType = tr("Alarm Alarm Input");
		}
		break;
	case DH_LOG_NET_ABORT:
		{
			strLogType = tr("Network Disconnect");
			
			if (pLogItem != NULL && 1 == pLogItem->data)
			{
				strLogContext = tr("Wireless");
			}
		}
		break;
	case DH_LOG_NET_ABORT_RESUME:
		{
			strLogType = tr("Network Resumed");
			
			if (pLogItem != NULL && 1 == pLogItem->data)
			{
				strLogContext = tr("Wireless");
			}
		}
		break;
	case DH_LOG_CODER_BREAKDOWN:
		{
			strLogType = tr("CODER Error");
			if(pLogItem != NULL)
			{
				strLogContext = tr("CODER Error");
			}
		}
		break;
	case DH_LOG_CODER_BREAKDOWN_RESUME:
		{
			strLogType = tr("CODER Error Resumed");
			if(pLogItem != NULL)
			{
				strLogContext = tr("CODER Error Resumed");
			}
		}
		break;
	case DH_LOG_BLIND_IN:
		{
			strLogType = tr("Camera Mask Detect");
			if(pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = QString(tr("Channel No.:%1").arg(strdata));
			}
		}
		break;
	case DH_LOG_BLIND_END:
		{
			strLogType = tr("Camera Mask Detect End");
			if(pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = QString(tr("Channel No.:%1").arg(strdata));
			}
		}
		break;
	case DH_LOG_ALM_TEMP_HIGH:
		{
			strLogType = tr("Temperature Alarm");
			if(pLogItem != NULL)
			{
				strLogContext = tr("Temperature is too high");
			}
		}
		break;
	case DH_LOG_ALM_VOLTAGE_LOW:
		{
			strLogType = tr("Temperature Alarm");
			if(pLogItem != NULL)
			{
				strLogContext = tr("Temperature is too low");
			}
		}
		break;
	case DH_LOG_ALM_BATTERY_LOW:
		{
			strLogType = tr("Battery Alarm");
			if(pLogItem != NULL)
			{
				strLogContext = tr("Low Battery");
			}
		}
		break;
	case DH_LOG_ALM_ACC_BREAK:
		{
			strLogType = tr("ACC OFF");
			if(pLogItem != NULL)
			{
				strLogContext = tr("ACC OFF");
			}
		}
		break;
	case DH_LOG_ALM_ACC_RES:
		{
			strLogType = tr("ACC ON");
			if(pLogItem != NULL)
			{
				strLogContext = tr("ACC ON");
			}
		}
		break;		
	case DH_LOG_GPS_SIGNAL_LOST:
		{
			strLogType = tr("GPS No Signal");
		}
		break;
	case DH_LOG_GPS_SIGNAL_RESUME:
		{
			strLogType = tr("GPS Signal Resumed");
		}
		break;
	case DH_LOG_3G_SIGNAL_LOST:
		{
			strLogType = tr("3G No Signal");
		}
		break;
	case DH_LOG_3G_SIGNAL_RESUME:
		{
			strLogType = tr("3G Signal Resumed");
		}
		break;	
	case DH_LOG_ALM_IPC_IN:
		{
			strLogType = tr("IPC Alarm ON");
		}
		break;	
	case DH_LOG_ALM_IPC_END:
		{
			strLogType = tr("IPC Alarm OFF");
		}
		break;	
	case DH_LOG_ALM_DIS_IN:
		{
			strLogType = tr("Disconnet Alarm");
		}
		break;	
	case DH_LOG_ALM_DIS_END:
		{
			strLogType = tr("Disconnet Resumed");
		}
		break;			
	case DH_LOG_INFRAREDALM_IN :
		{
			strLogType = tr("Infrared Alarm");
			if(pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = QString(tr("Channel No.:%1").arg(strdata));
			}
		}
		break;
	case DH_LOG_INFRAREDALM_END:
		{
			strLogType = tr("Infrared Alarm End");
			if(pLogItem != NULL)
			{
				QString strdata = QString::number(pLogItem->data, 10);
				strLogContext = QString(tr("Channel No.:%1").arg(strdata));
			}
		}
		break;
	case DH_LOG_IPCONFLICT:
		{
			strLogType = tr("IP Conflict");
			
			if (pLogItem != NULL && 1 == pLogItem->data)
			{
				strLogContext = tr("Wireless");
			}
		}
		break;
	case DH_LOG_IPCONFLICT_RESUME:
		{
			strLogType = tr("IP Conflict Resumed");
			
			if (pLogItem != NULL && 1 == pLogItem->data)
			{
				strLogContext = tr("Wireless");
			}
		}
		break;
	case DH_LOG_SDPLUG_IN:
		{
			strLogType = tr("SD card Alarm");
			if (pLogItem != NULL)
			{
				strLogContext = tr("SD card inserted");
			}
		}
		break;
	case DH_LOG_SDPLUG_OUT:
		{
			strLogType = tr("SD card Alarm");
			if (pLogItem != NULL)
			{
				strLogContext = tr("SD card pulled out");
			}
		}
		break;
	case DH_LOG_NET_PORT_BIND_FAILED:
		{
			strLogType = tr("Failed to bind port");
		}
		break;
	case DH_LOG_HDD_BEEP_RESET:
		{
			strLogType = tr("Beep reset alarm");
			if (pLogItem != NULL)
			{
				strLogContext = tr("Hard disk error beep reset");
			}
		}
		break;
	case DH_LOG_MAC_CONFLICT:
		{
			strLogType = tr("MAC Conflict");
		}
		break;
	case DH_LOG_MAC_CONFLICT_RESUME:
		{
			strLogType = tr("MAC Conflict Resumed");
		}
		break;
	case DH_LOG_ALARM_OUT:
		{
			strLogType = tr("Alarm out status");
		}
		break;
	case DH_LOG_ALM_RAID_STAT_EVENT:
		{
			strLogType = tr("Raid status changed");
		}
		break;
	case DH_LOG_ABLAZE_ON:
		{
			strLogType = tr("Ablaze ON");
		}
		break;
	case DH_LOG_ABLAZE_OFF:
		{
			strLogType = tr("Ablaze OFF");
		}
		break;		
	case DH_LOG_INTELLI_ALARM_PLUSE:
		{
			strLogType = tr("Intelligent pluse alarm");
		}
		break;
	case DH_LOG_INTELLI_ALARM_IN:
		{
			strLogType = tr("Intelligent alarm begin");
		}
		break;
	case DH_LOG_INTELLI_ALARM_END:
		{
			strLogType = tr("Intelligent alarm end");
		}
		break;
	case DH_LOG_3G_SIGNAL_SCAN:
		{
			strLogType = tr("3G Signal Scan");
		}
		break;
	case DH_LOG_GPS_SIGNAL_SCAN:
		{
			strLogType = tr("GPS Signal Scan");
		}
		break;
	case DH_LOG_AUTOMATIC_RECORD:
		{
			strLogType = tr("Automatic Record");
			if (pLogItem != NULL)
			{
				strLogContext = tr("Start automatic recording, channel: ");
				DWORD dwMask = *(DWORD*)pLogItem->context;
				DWORD dwPos = 1;
				QString str;
				for (int i = 0; i < 32; i++)
				{
					if ((dwMask & dwPos) != 0)
					{
						str = QString::number(i, 10);
						strLogContext += str;
					}
					
					dwPos = dwPos << 1;
				}
			}
		}
		break;
	case DH_LOG_MANUAL_RECORD:
		{
			strLogType = tr("Manual recording is beginning");
			if (pLogItem != NULL)
			{
				strLogContext = tr("Manual recording is beginning, channel: ");
				DWORD dwMask = *(DWORD*)pLogItem->context;
				DWORD dwPos = 1;
				QString str;
				for (int i = 0; i < 32; i++)
				{
					if ((dwMask & dwPos) != 0)
					{
						str = QString::number(i, 10);
						strLogContext += str;
					}
					
					dwPos = dwPos << 1;
				}
			}
		}
		break;
	case DH_LOG_CLOSED_RECORD:
		{
			strLogType = tr("Stop Manual Recording");
			if (pLogItem != NULL)
			{
				strLogContext = tr("Stop manual recording, channel: ");
				DWORD dwMask = *(DWORD*)pLogItem->context;
				DWORD dwPos = 1;
				QString str;
				for (int i = 0; i < 32; i++)
				{
					if ((dwMask & dwPos) != 0)
					{
						str = QString::number(i, 10);
						strLogContext += str;
					}
					
					dwPos = dwPos << 1;
				}
			}
		}
		break;
	case DH_LOG_LOGIN:
		{
			strLogType = tr("Login");
			
			if (pLogItem != NULL)
			{
				strLogContext = QString(tr("User login:%1").arg((char *)pLogItem->context).toLocal8Bit ());
			}
		}
		break;
	case DH_LOG_LOGOUT:
		{
			strLogType = tr("Logout");
			
			if (pLogItem != NULL)
			{
				strLogContext = QString(tr("User logout:%1").arg((char *)pLogItem->context));
			}
		}
		break;
	case DH_LOG_ADD_USER:
		{
			strLogType = tr("Add User");
			
			if (pLogItem != NULL)
			{
				strLogContext = QString(tr("Add user:%1").arg((char *)pLogItem->context));
			}
		}
		break;
	case DH_LOG_DELETE_USER:
		{
			strLogType = tr("Delete User");
			
			if (pLogItem != NULL)
			{
				strLogContext = QString(tr("Delete user:%1").arg((char *)pLogItem->context));
			}
		}
		break;
	case DH_LOG_MODIFY_USER:
		{
			strLogType = tr("Modify User");
			
			if (pLogItem != NULL)
			{
				strLogContext = QString(tr("Modify user info:%1").arg((char *)pLogItem->context));
			}
		}
		break;
	case DH_LOG_ADD_GROUP:
		{
			strLogType = tr("Add User Group");
			
			if (pLogItem != NULL)
			{
				strLogContext = QString(tr("Add user group:group name:%1").arg((char *)pLogItem->context));
			}
		}
		break;
	case DH_LOG_DELETE_GROUP:
		{
			strLogType = tr("Delete User Group");
			
			if (pLogItem != NULL)
			{
				strLogContext = QString(tr("Delete user group:group name:%1").arg((char *)pLogItem->context));
			}
		}
		break;
	case DH_LOG_MODIFY_GROUP:
		{
			strLogType = tr("Modify User Group");
			
			if (pLogItem != NULL)
			{
				strLogContext = QString(tr("Modify user group:group name:%1").arg((char *)pLogItem->context));
			}
		}
		break;
	case DH_LOG_NET_LOGIN:
		{
			strLogType = tr("Net User Login");
			
			if (pLogItem != NULL)
			{
				strLogContext= QString(tr("IP: %1.%2.%3.%4").arg(QString::number(pLogItem->context[0], 10)).arg(QString::number(pLogItem->context[1], 10)).arg(QString::number(pLogItem->context[2], 10)).arg(QString::number(pLogItem->context[3], 10)));
			}
		}
		break;
	case DH_LOG_MODIFY_PASSWORD:
		{
			strLogType = tr("Net User Modify Password");
			if (pLogItem != NULL)
			{
				strLogContext = QString(tr("Who Modify Password %1").arg(tr((char *)pLogItem->context)));
			}
		}
		break;
	case DH_LOG_CLEAR:
		{
			strLogType = tr("clean log");
			if (pLogItem != NULL)
			{
				strLogContext = (tr("clean log"));
			}
		}
		break;
	case DH_LOG_SEARCHLOG:
		{
			strLogType = tr("Search Log");
			
			if (pLogItem != NULL)
			{
				strLogContext = QString(tr("Search Log: %1").arg((char *)pLogItem->context));
			}
		}
		break;
	case DH_LOG_SEARCH:
		{
			strLogType = tr("Record Search");
			
			if (pLogItem != NULL)
			{
				LOG_ITEM_RECORD *shutTime = (LOG_ITEM_RECORD*)(char *)pLogItem->context;
				if (255 == shutTime->channel)
				{
					strLogContext = tr("Record Search: Channel No. all");
				}
				else
				{
					strLogContext= QString(tr("Record Search: Channel No. %1").arg( QString::number(shutTime->channel, 10)));
				}
			}
		}
		break;
	case DH_LOG_DOWNLOAD:
		{
			strLogType = tr("Record Download");
			if (pLogItem != NULL)
			{
				LOG_ITEM_RECORD *shutTime = (LOG_ITEM_RECORD*)pLogItem->context;
				strLogContext= QString(tr("Record Download: Channel No. %1").arg( QString::number(shutTime->channel, 10)));
			}
		}
		break;
	case DH_LOG_PLAYBACK:
		{
			strLogType = tr("Record Playback");
			if (pLogItem != NULL)
			{
				LOG_ITEM_RECORD *shutTime = (LOG_ITEM_RECORD*)pLogItem->context;
				strLogContext= QString(tr("Record Playback: Channel No. %1").arg( QString::number(shutTime->channel, 10)));
				
			}
		}
		break;    
    case DH_PLAY_PAUSE:
    	{
        	strLogType = tr("Record pause");
            if (pLogItem != NULL)
            {
            	LOG_ITEM_RECORD *shutTime = (LOG_ITEM_RECORD*)pLogItem->context;
                strLogContext= QString(tr("Record Playback: Channel No. %1").arg( QString::number(shutTime->channel, 10)));
            }
        }
		break;
	case DH_PLAY_START:
		{
			strLogType = tr("PLAY START");
		}
		break;
	case LOG_PLAY_STOP:
		{
			strLogType = tr("PLAY STOP");
		}
		break;
	case DH_LOG_BACKUP:
		{
			strLogType = tr("Record Backup");
			if (pLogItem != NULL)
			{
				LOG_ITEM_RECORD *shutTime = (LOG_ITEM_RECORD*)pLogItem->context;
				strLogContext= QString(tr("Record Backup: Channel No. %1").arg( QString::number(shutTime->channel, 10)));
			}
		}
		break;
	case DH_LOG_BACKUPERROR:
		{
			strLogType = tr("Record Backup");
			if (pLogItem != NULL)
			{
				strLogContext = tr("Record Backup Error");
			}
		}
		break;
	case DH_LOG_BACK_UPRT:
		{
			strLogType = tr("Real-time Backup");
		}
		break;		
	case DH_LOG_BACKUPCLONE:
		{
			strLogType = tr("Backup Clone");
		}
		break;		
	case DH_LOG_DISK_CHANGED:
		{
			strLogType = tr("Disk Changed");
		}
		break;		
	case DH_LOG_IMAGEPLAYBACK:
		{
			strLogType = tr("Image Playback");
		}
		break;		
	case DH_LOG_LOCKFILE:
		{
			strLogType = tr("Lock File");
		}
		break;		
	case DH_LOG_UNLOCKFILE:
		{
			strLogType = tr("Unlock File");
		}
		break;		
	case DH_LOG_ATMPOS:
		{
			strLogType = tr("ATM POS");
		}
		break;				
	case DH_LOG_TIME_UPDATE:
		{
			strLogType = tr("Time Update");
			if (pLogItem != NULL)
			{
				strLogContext = tr("Time Update");
			}
		}
		break;
	case DH_LOG_REMOTE_STATE:
		{
			strLogType = tr("Remote State");
		}
		break;				
	case DH_LOG_USER_DEFINE:
		{
			strLogType = tr("User Define");
		}
		break;
	case LOG_PLAY_BACK:
        {
            strLogType = tr("PLAY BACK");
        }
		break;	
	case LOG_PLAY_FAST:
        {
            strLogType = tr("PLAY FAST");
        }
		break;
    case LOG_PLAY_SLOW:
        {
            strLogType = tr("PLAY SLOW");
        }
		break;
    case LOG_SMART_SEARCH:
        {
            strLogType = tr("SMART SEARCH");
        }
		break;
    case LOG_RECORD_SNAP:
        {
            strLogType = tr("RECORD SNAP");
        }
		break;
    case LOG_ADD_TAG:
        {
            strLogType = tr("ADD TAG");
        }
		break;
    case LOG_DEL_TAG:
        {
            strLogType = tr("DEL TAG");
        }
		break;
    case LOG_USB_IN:
        {
            strLogType = tr("USB IN");
        }
		break;
    case LOG_USB_OUT:
        {
            strLogType = tr("USB OUT");
        }
		break;
    case LOG_BACKUP_FILE:
        {
            strLogType = tr("BACKUP FILE");
        }
		break;
    case LOG_BACKUP_LOG:
        {
            strLogType = tr("BACKUP LOG");
        }
		break;
    case LOG_BACKUP_CONFIG:
        {
            strLogType = tr("BACKUP CONFIG");
        }
		break;		
	default:
		{
			nRet = 0;
		}
		break;
	}
	
	return nRet;
}

QString form1::ConvertCfgType(const DH_LOG_ITEM* pLogItem)
{
	if (pLogItem==NULL)
	{
		return "";
	}
	
	QString strCfgType;
	int nCfgType = (int)pLogItem->data;
	switch(nCfgType)
	{
	case 0:
		strCfgType = tr("normal config");
		break;
	case 1:
		strCfgType = tr("COM config");
		break;
	case 2:
		strCfgType = tr("Network config");
		break;
	case 3:
		strCfgType = tr("Record config");
		break;
	case 4:
		strCfgType = tr("Image Setting");
		break;
	case 5:
		strCfgType = tr("PTZ config");
		break;
	case 6:
		strCfgType = tr("Dynamic Detecting config");
		break;
	case 7:
		strCfgType = tr("Alarm config");
		break;
	case 8:
		strCfgType = tr("Show Setting");
		break;
	case 10:
		strCfgType = tr("Channel Title Setting");
		break;
	case 11:
		strCfgType = tr("Mail Setting");
		break;
	case 12:
		strCfgType = tr("Preview Setting");
		break;
	case 13:
		strCfgType = tr("pppoe setting");
		break;
	case 14:
		strCfgType = tr("DDNS setting");
		break;
	case 15:
		strCfgType = tr("Realplay Capture Setting");
		break;
	case 16:
		strCfgType = tr("coding information");
		break;
	case 18:
		strCfgType = tr("Auto Maintain");
		break;
	case 19:
		strCfgType = tr("ntp config");
		break;
	case 24:
		strCfgType = tr("DSP Max Rate");
		break;
	case 29:
		strCfgType = tr("Water Mark");
		break;
	case 30:
		strCfgType = tr("MATRIX");
		break;
	case 34:
		strCfgType = tr("Video Cover");
		break;
	case 35:
		strCfgType = tr("DHCP");
		break;
	case 36:
		strCfgType = tr("WEB");
		break;
	case 37:
		strCfgType = tr("FTP config");
		break;
	case 38:
		strCfgType = tr("Camera Properties config");
		break;
	case 39:
		strCfgType = tr("Wireless Module config");
		break;
	case 40:
		strCfgType = tr("DNS");
		break;
	case 42:
		strCfgType = tr("Download Recording File");
		break;
	case 43:
		strCfgType = tr("Audio Format");
		break;
	case 44:
		strCfgType = tr("Video OSD config");
		break;
	case 46:
		strCfgType = tr("Machine config");
		break;
	case 49:
		strCfgType = tr("UPNP");
		break;
	case 60:
		strCfgType = tr("Local alarmName config");
		break;
	case 61:
		strCfgType = tr("Alarm in method config");
		break;
	case  100:
		strCfgType = QString(tr("IP Modify %1 %2 %3 %4").arg((char *)pLogItem->context[0]).arg( (char *)pLogItem->context[1]).arg((char *) pLogItem->context[2]).arg((char *) pLogItem->context[3]));
		break;
	case  101:
		strCfgType = QString(tr("Gateway Modify %1 %2 %3 %4").arg((char *)pLogItem->context[0]).arg( (char *)pLogItem->context[1]).arg((char *) pLogItem->context[2]).arg((char *) pLogItem->context[3]));
		break;
	case  102:
		strCfgType = QString(tr("Subnetwork Modify %1 %2 %3 %4").arg((char *)pLogItem->context[0]).arg( (char *)pLogItem->context[1]).arg((char *) pLogItem->context[2]).arg((char *) pLogItem->context[3]));
		break;
	case 120:
		strCfgType = tr("Alarm center config");
		break;
	case 123:
		strCfgType = tr("New Record Setting");
		break;
	case 124:
		strCfgType = tr("Event Config");
		break;
	case 125:
		strCfgType = tr("WorkSheet");
		break;
	case 126:
		strCfgType = tr("color information");
		break;
	case 127:
		strCfgType = tr("Image Setting");
		break;
	case 128:
		strCfgType = tr("Image Setting");
		break;
	case 131:
		strCfgType = tr("Wifi config");
		break;
	case 133:
		strCfgType = tr("Transfer Policy config");
		break;
	case 135:
		strCfgType = tr("Wifi scanning");
		break;
	case 136:
		strCfgType = tr("Backup config");
		break;
	case 137:
		strCfgType = tr("RTSP config");
		break;
	case 140:
		strCfgType = tr("DDNS config");
		break;
	case 141:
		strCfgType = tr("SNMP config");
	    break;
	case 142:
		strCfgType = tr("ISCSI config");
	    break;
	case 154:
		strCfgType = tr("AES encrypt info");
	    break;
	case 156:
		strCfgType = tr("SNAP upload config");
	    break;
	case 190:
		strCfgType = tr("Platform access configuration");
		break;
	case 200:
		strCfgType = tr("Camera IPC configuration");
		break;
	case 201:
		strCfgType = tr("Local configuration");
		break;
	case 202:
		strCfgType = tr("GUI configuration");
		break;
	case 203:
		strCfgType = tr("Record Worksheet configuration");
		break;
	case 204:
		strCfgType = tr("PTZ linkage alarm configuration");
		break;
	case 205:
		strCfgType = tr("Network Alarm configuration");
		break;
	case 206:
		strCfgType = tr("Alarm worksheet configuration");
		break;
	case 207:
		strCfgType = tr("Motion worksheet configuration");
		break;
	case 208:
		strCfgType = tr("PTZ Preset point");
		break;
	case 209:
		strCfgType = tr("PTZ tour");
		break;
	case 210:
		strCfgType = tr("Video Lost");
		break;
	case 211:
		strCfgType = tr("Video Blind");
		break;
	case 212:
		strCfgType = tr("Playback");
		break;
	case 213:
		strCfgType = tr("User configuration");
		break;
	case 214:
		strCfgType = tr("User Group configuration");
		break;
	case 215:
		strCfgType = tr("Monitor Tour");
		break;
	case 216:
		strCfgType = tr("TV Adjust");
		break;
	case 217:
		strCfgType = tr("ATM configuration");
		break;
	case 218:
		strCfgType = tr("No Hard Disk");
		break;
	case 219:
		strCfgType = tr("Hard Disk Error");
		break;
	case 220:
		strCfgType = tr("Hard Disk Nospace");
		break;
	case 221:
		strCfgType = tr("Broken network events");
		break;
	case 222:
		strCfgType = tr("Video Widget");
		break;
	case 223:
		strCfgType = tr("Video Matrix");
		break;
	case 224:
		strCfgType = tr("System Time");
		break;
	case 225:
		strCfgType = tr("Lost Focus configuration");
		break;
	case 226:
		strCfgType = tr("Lost Focus Worksheet configuration");
		break;
	case 227:
		strCfgType = tr("Scene change configuration");
		break;
	case 228:
		strCfgType = tr("Scene change worksheet configuration");
		break;
	case 230:
		strCfgType = tr("Network configuration");
		break;
	case 231:
		strCfgType = tr("FTP Server configuration");
		break;
	case 232:
		strCfgType = tr("FTP Application configuration");
		break;
	case 233:
		strCfgType = tr("IP Filter");
		break;
	case 234:
		strCfgType = tr("Multicast configuration");
		break;
	case 235:
		strCfgType = tr("PPPOE configuration");
		break;
	case 236:
		strCfgType = tr("DDNS configuration");
		break;
	case 237:
		strCfgType = tr("Alarm Server configuration");
		break;
	case 238:
		strCfgType = tr("NTP configuration");
		break;
	case 239:
		strCfgType = tr("Email configuration");
		break;
	case 240:
		strCfgType = tr("Sniffer configuration");
		break;
	case 243:
		strCfgType = tr("Backup configuration");
		break;
	case 245:
		strCfgType = tr("Motion Record State");
		break;
	case 246:
		strCfgType = tr("Storage configuration");
		break;
	case 247:
		strCfgType = tr("NVD TV Config");
		break;
	default:
		strCfgType = tr("new type");
		break;
        }
		
        return strCfgType;
}

void form1::DisplayQueryResult(char *recBuf, int nLength)
{
    QString strLogType = "";
    QString strLogTime = "";
    QString strLogContext = "";
    QDate Date;
    QTime Time;
    int nCount = nLength/sizeof(DH_LOG_ITEM);
	
    for(int i=0; i<nCount; i++)
    {
        // cout<<"nCount="<<i<<endl;
        DH_LOG_ITEM *pLogItem = (DH_LOG_ITEM*)(recBuf + i*sizeof(DH_LOG_ITEM));
		
        if(!TransLogInfo(pLogItem, 1, strLogType, strLogTime, strLogContext))
		{
			continue;
		}
		
        ConvertTimeToStr(&pLogItem->time, &Date, &Time);
        strLogTime = QString("%1, %2").arg(Date.toString("yyyy.MM.dd")).arg(Time.toString());
		
		
        DH_LOG_QUERY_TYPE eQueryType = (DH_LOG_QUERY_TYPE)ui->comboxType->currentIndex();
        if(JudgeType(eQueryType,pLogItem->type))
        {
            InsertListViewItem(strLogType,strLogTime,strLogContext);
        }
    }
}

void form1::InsertListViewItem(QString strLogType, QString strLogTime, QString strLogContext)
{
    QStringList header;
    header <<"Type"<<"time"<<"Context";
    ui->listViewLog->setHorizontalHeaderLabels(header);
	ui->listViewLog->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
    ui->listViewLog->setColumnCount(3);
    int nRowCount = ui->listViewLog->rowCount() + 1;
    ui->listViewLog->setRowCount(nRowCount);
	
    QTableWidgetItem * LogTypeitem = new QTableWidgetItem(strLogType);
    ui->listViewLog->setItem(nRowCount-1, 0, LogTypeitem);
	
    QTableWidgetItem * LogTimeitem = new QTableWidgetItem(strLogTime);
    ui->listViewLog->setItem(nRowCount-1, 1, LogTimeitem);
	
    QTableWidgetItem * LogContextitem = new QTableWidgetItem(strLogContext);
    ui->listViewLog->setItem(nRowCount-1, 2, LogContextitem);
	
}

BOOL form1::JudgeType(int nQueryType, int nInfoType)
{
    BOOL bShow = FALSE;
	switch(nQueryType) {
	case DHLOG_ALL:
		bShow = TRUE;
		break;
	case DHLOG_SYSTEM:
		if(nInfoType == DH_LOG_REBOOT || nInfoType == DH_LOG_SHUT || nInfoType == DH_LOG_REPORTSTOP 
			|| nInfoType == DH_LOG_REPORTSTART || nInfoType == DH_LOG_UPGRADE || nInfoType == DH_LOG_UPGRADE 
			|| nInfoType == DH_LOG_SYSTIME_UPDATE || nInfoType == DH_LOG_GPS_TIME_UPDATE || nInfoType == DH_LOG_AUDIO_TALKBACK 
			|| nInfoType == DH_LOG_COMM_ADAPTER || nInfoType == DH_LOG_NET_TIMING || nInfoType == DH_LOG_TIME_UPDATE)
		{
			bShow = TRUE;
		}
		break;
	case DHLOG_CONFIG:
		if(nInfoType == DH_LOG_CONFSAVE || nInfoType == DH_LOG_CONFLOAD)
		{
			bShow = TRUE;
		}
		break;
	case DHLOG_STORAGE:
		if(nInfoType == DH_LOG_FSERROR || nInfoType == DH_LOG_HDD_WERR || nInfoType == DH_LOG_HDD_RERR
			|| nInfoType == DH_LOG_HDD_TYPE || nInfoType == DH_LOG_HDD_FORMAT || nInfoType == DH_LOG_HDD_NOSPACE
			|| nInfoType == DH_LOG_HDD_TYPE_RW || nInfoType == DH_LOG_HDD_TYPE_RO || nInfoType == DH_LOG_HDD_TYPE_RE
			|| nInfoType == DH_LOG_HDD_TYPE_SS || nInfoType == DH_LOG_HDD_NONE || nInfoType == DH_LOG_HDD_NOWORKHDD
			|| nInfoType == DH_LOG_HDD_TYPE_BK || nInfoType == DH_LOG_HDD_TYPE_REVERSE || nInfoType == DH_LOG_SDPLUG_IN
			|| nInfoType == DH_LOG_SDPLUG_OUT || nInfoType == DH_LOG_HDD_START_INFO || nInfoType == DH_LOG_HDD_SLIGHT_ERR 
			|| nInfoType == DH_LOG_HDD_SERIOUS_ERR || nInfoType == DH_LOG_HDD_WORKING_DISK || nInfoType == DH_LOG_HDD_OTHER_ERROR
            || nInfoType == DH_LOG_HDD_NOSPACE_END || nInfoType == DH_LOG_HDD_TYPE_RAID_CONTROL || nInfoType == DH_LOG_HDD_TEMPERATURE_HIGH
			|| nInfoType == DH_LOG_HDD_TEMPERATURE_LOW || nInfoType == DH_LOG_HDD_ESATA_REMOVE
			)
		{
			bShow = TRUE;
		}
		break;
	case DHLOG_ALARM:
		if(nInfoType == DH_LOG_ALM_IN || nInfoType == DH_LOG_NETALM_IN || nInfoType == DH_LOG_ALM_END
			|| nInfoType == DH_LOG_LOSS_IN || nInfoType == DH_LOG_LOSS_END || nInfoType == DH_LOG_MOTION_IN
			|| nInfoType == DH_LOG_MOTION_END || nInfoType == DH_LOG_ALM_BOSHI || nInfoType == DH_LOG_NET_ABORT
			|| nInfoType == DH_LOG_NET_ABORT_RESUME || nInfoType == DH_LOG_CODER_BREAKDOWN
			|| nInfoType == DH_LOG_CODER_BREAKDOWN_RESUME || nInfoType == DH_LOG_BLIND_IN
			|| nInfoType == DH_LOG_BLIND_END || nInfoType == DH_LOG_ALM_TEMP_HIGH || nInfoType == DH_LOG_ALM_VOLTAGE_LOW
			|| nInfoType == DH_LOG_ALM_BATTERY_LOW || nInfoType == DH_LOG_ALM_ACC_BREAK || nInfoType == DH_LOG_ALM_ACC_RES
			|| nInfoType == DH_LOG_GPS_SIGNAL_LOST || nInfoType == DH_LOG_GPS_SIGNAL_RESUME || nInfoType == DH_LOG_3G_SIGNAL_LOST
			|| nInfoType == DH_LOG_3G_SIGNAL_RESUME || nInfoType == DH_LOG_ALM_IPC_IN || nInfoType == DH_LOG_ALM_IPC_END
			|| nInfoType == DH_LOG_ALM_DIS_IN || nInfoType == DH_LOG_ALM_DIS_END || nInfoType == DH_LOG_INFRAREDALM_IN
			|| nInfoType == DH_LOG_INFRAREDALM_END || nInfoType == DH_LOG_IPCONFLICT || nInfoType == DH_LOG_IPCONFLICT_RESUME
			|| nInfoType == DH_LOG_NET_PORT_BIND_FAILED || nInfoType == DH_LOG_HDD_BEEP_RESET || nInfoType == DH_LOG_MAC_CONFLICT 
			|| nInfoType == DH_LOG_MAC_CONFLICT_RESUME || nInfoType == DH_LOG_ALARM_OUT || nInfoType == DH_LOG_ALM_RAID_STAT_EVENT 
			|| nInfoType == DH_LOG_ABLAZE_ON || nInfoType == DH_LOG_ABLAZE_OFF || nInfoType == DH_LOG_INTELLI_ALARM_PLUSE 
			|| nInfoType == DH_LOG_INTELLI_ALARM_IN || nInfoType == DH_LOG_INTELLI_ALARM_END || nInfoType == DH_LOG_3G_SIGNAL_SCAN 
			|| nInfoType == DH_LOG_GPS_SIGNAL_SCAN || nInfoType == DH_LOG_HDD_NOSPACE)
		{
			bShow = TRUE;
		}
		break;
	case DHLOG_RECORD:
		if (nInfoType == DH_LOG_AUTOMATIC_RECORD || nInfoType == DH_LOG_MANUAL_RECORD || nInfoType == DH_LOG_CLOSED_RECORD
			|| nInfoType == DH_LOG_SEARCH || nInfoType == DH_LOG_DOWNLOAD || nInfoType == DH_LOG_PLAYBACK
			|| nInfoType == DH_LOG_BACKUP || nInfoType == DH_LOG_BACKUPERROR )
		{
			bShow = TRUE;
		}
		break;
	case DHLOG_ACCOUNT:
		if(nInfoType == DH_LOG_LOGIN || nInfoType == DH_LOG_LOGOUT
			||nInfoType == DH_LOG_ADD_USER || nInfoType == DH_LOG_DELETE_USER
			||nInfoType == DH_LOG_MODIFY_USER || nInfoType == DH_LOG_ADD_GROUP
			||nInfoType == DH_LOG_DELETE_GROUP || nInfoType == DH_LOG_MODIFY_GROUP || nInfoType == DH_LOG_NET_LOGIN
			||nInfoType == DH_LOG_MODIFY_PASSWORD)
		{
			bShow = TRUE;
		}
		break;
	case DHLOG_CLEAR:
		if(nInfoType == DH_LOG_CLEAR || nInfoType == DH_LOG_SEARCHLOG)
		{
			bShow = TRUE;
		}
		break;
	case DHLOG_PLAYBACK:
		if (nInfoType == DH_LOG_SEARCH || nInfoType == DH_LOG_DOWNLOAD || nInfoType == DH_LOG_PLAYBACK
            || nInfoType == DH_LOG_BACK_UPRT || nInfoType == DH_LOG_BACKUPCLONE || nInfoType == DH_LOG_DISK_CHANGED
			|| nInfoType == DH_LOG_IMAGEPLAYBACK || nInfoType == DH_LOG_LOCKFILE || nInfoType == DH_LOG_UNLOCKFILE
			|| nInfoType == DH_LOG_ATMPOS || nInfoType == DH_PLAY_PAUSE || nInfoType == DH_PLAY_START 
			|| nInfoType == LOG_PLAY_STOP || nInfoType == LOG_PLAY_BACK || nInfoType == LOG_PLAY_FAST
			|| nInfoType == LOG_PLAY_SLOW)
		{
			bShow = TRUE;
		}
		break;
        case DHLOG_MANAGER:
                if (nInfoType == DH_LOG_REMOTE_STATE || nInfoType == DH_LOG_TIME_UPDATE)
                {
                        bShow = TRUE;
                }
                break;
	default:
		break;
	}
	return bShow;
}

bool form1::eventFilter(QObject *obj, QEvent *event)//message filter
{
    if(event->type() == QEvent::Close)//windows close
    {
        cout<<"message distroy"<<endl;
        destroyForm();
    }
	
    if(event->type() == QEvent::User)
    {
        QString strDevInfo;
        strDevInfo.append("Disconnect!");
        QMessageBox::information(0, "Promt", strDevInfo);
    }
    return QWidget::eventFilter(obj, event);//don't eat event
}


void form1::on_ButExit_clicked()
{
    destroyForm();
    exit(0) ;
}

void form1::on_ButPrePage_clicked()
{
    char szTmpLog[1024] = {0}; // using for log output

    if(ui->StartdateTime->dateTime() >= ui->EnddateTime->dateTime())
    {
		QMessageBox::about(this, "Promt", tr("Bad time set!"));
		return;
    }
	
    //get nunber
    bool numok = false;
    int nPageLine = ui->PageLine->text().toInt(&numok);
    if(!numok)
    {
        QMessageBox::about(this, "Promt", tr("Bad number set!"));
        return;
    }

    m_nPageLineOld = m_nPageLine;
    m_nPageLine = nPageLine;
	
    QUERY_DEVICE_LOG_PARAM stuLogParam;
    memset(&stuLogParam, 0, sizeof(QUERY_DEVICE_LOG_PARAM));
    stuLogParam.emLogType = (DH_LOG_QUERY_TYPE)ui->comboxType->currentIndex();
	if (m_nPreStartNum - m_nPageLine > 0)
	{
                stuLogParam.nStartNum = m_nPreStartNum - m_nPageLine;
	}
	else
	{
		stuLogParam.nStartNum = 0;
	}
        stuLogParam.nEndNum = m_nPreEndNum - m_nPageLineOld - 1;
	int nPreEndNum = stuLogParam.nEndNum + 1;
	int nPreStartNum = stuLogParam.nStartNum;
	stuLogParam.nLogStuType = 1;
	stuLogParam.stuStartTime.dwYear = ui->StartdateTime->date().year();
	stuLogParam.stuStartTime.dwMonth = ui->StartdateTime->date().month();
	stuLogParam.stuStartTime.dwDay = ui->StartdateTime->date().day();
	stuLogParam.stuStartTime.dwHour = ui->StartdateTime->time().hour();
	stuLogParam.stuStartTime.dwMinute = ui->StartdateTime->time().minute();
	stuLogParam.stuStartTime.dwSecond = ui->StartdateTime->time().second();
	
	stuLogParam.stuEndTime.dwYear = ui->EnddateTime->date().year();
	stuLogParam.stuEndTime.dwMonth = ui->EnddateTime->date().month();
	stuLogParam.stuEndTime.dwDay = ui->EnddateTime->date().day();
	stuLogParam.stuEndTime.dwHour = ui->EnddateTime->time().hour();
	stuLogParam.stuEndTime.dwMinute = ui->EnddateTime->time().minute();
	stuLogParam.stuEndTime.dwSecond = ui->EnddateTime->time().second();
	
	DH_DEVICE_LOG_ITEM_EX *szLogInfos = new DH_DEVICE_LOG_ITEM_EX[1024];
	memset(szLogInfos, 0, sizeof(DH_DEVICE_LOG_ITEM_EX) * 1024);
	int nRetLogNum = 0;
	BOOL bRet = CLIENT_QueryDeviceLog(m_lLoginHandle, &stuLogParam, (char*)szLogInfos, 1024 * sizeof(DH_DEVICE_LOG_ITEM_EX), &nRetLogNum,DEMO_SDK_WAITTIME);
        sprintf(szTmpLog, "CLIENT_QueryDeviceLog prepage query [%d, %d] ... return %s, nRetLogNum is %d !\n", stuLogParam.nStartNum, stuLogParam.nEndNum, bRet>0?"ok":"failure", nRetLogNum);
        printf(szTmpLog);qDebug()<<szTmpLog;
	if (bRet)
	{
		//display log info
		if (nRetLogNum <= 0)
		{
                    ui->ButPrePage->setEnabled(FALSE);
			QMessageBox::about(this, "Promt", tr("No record!"));
			delete[] szLogInfos;
			return;
		}
                // not enough, continue
                else if (nRetLogNum < m_nPageLine && nRetLogNum < stuLogParam.nEndNum - stuLogParam.nStartNum)
		{
			DisPlayNewLogInfo(szLogInfos, nRetLogNum);
			
			int iLoop = 0;
			int nTotal = nRetLogNum;
			do
			{
				memset(szLogInfos, 0, sizeof(DH_DEVICE_LOG_ITEM_EX) * 1024);
                                //stuLogParam.nStartNum = nPreStartNum + nTotal;
                                stuLogParam.nEndNum = nPreEndNum - 1 - nRetLogNum;
				bRet = CLIENT_QueryDeviceLog(m_lLoginHandle, &stuLogParam, (char*)szLogInfos, 1024 * sizeof(DH_DEVICE_LOG_ITEM_EX), &nRetLogNum,DEMO_SDK_WAITTIME);
                                sprintf(szTmpLog, "loop[%d], CLIENT_QueryDeviceLog prepage query [%d, %d] ... return %s, nRetLogNum is %d !\n", ++iLoop,stuLogParam.nStartNum, stuLogParam.nEndNum, bRet>0?"ok":"failure", nRetLogNum);
                                printf(szTmpLog);qDebug()<<szTmpLog;
				if (bRet)
				{
					// no more
					if (nRetLogNum <= 0)
					{
						break;
					}
					DisPlayNewLogInfo(szLogInfos, nRetLogNum, TRUE);
					nTotal += nRetLogNum;
				}
				else
				{
                                    ui->ButPrePage->setEnabled(TRUE);
                                    break;
				}
				
			} while (nTotal < m_nPageLine);
		}
		else
		{
			DisPlayNewLogInfo(szLogInfos, nRetLogNum);
		}

		m_nPreStartNum = nPreStartNum;
		m_nPreEndNum = nPreEndNum;
		
		//tell if there has more logs
		if (m_nPreStartNum == 0)
		{
			ui->ButPrePage->setEnabled(FALSE);
			ui->ButNextPage->setEnabled(TRUE);
			delete[] szLogInfos;
			return;
		}
		
		memset(szLogInfos, 0, sizeof(DH_DEVICE_LOG_ITEM_EX) * 1024);
                stuLogParam.nStartNum = m_nPreStartNum - 3;
                stuLogParam.nEndNum = m_nPreStartNum - 1;
		bRet = CLIENT_QueryDeviceLog(m_lLoginHandle, &stuLogParam, (char*)szLogInfos, 1024 * sizeof(DH_DEVICE_LOG_ITEM_EX), &nRetLogNum,DEMO_SDK_WAITTIME);
                sprintf(szTmpLog, "2 CLIENT_QueryDeviceLog prepage query [%d, %d] ... return %s, nRetLogNum is %d !\n", stuLogParam.nStartNum, stuLogParam.nEndNum, bRet>0?"ok":"failure", nRetLogNum);
                printf(szTmpLog);qDebug()<<szTmpLog;
		
		if (bRet)
		{
			if (nRetLogNum > 0)
			{
				ui->ButPrePage->setEnabled(TRUE);
			}
			else
			{
				ui->ButPrePage->setEnabled(FALSE);
			}
		}
                ui->ButNextPage->setEnabled(TRUE);
        }
	else
	{
		int nRowCount = ui->listViewLog->rowCount();
		for(int i = nRowCount - 1; i >= 0; i--)
		{
			ui->listViewLog->removeRow(i);
		}
		QMessageBox::about(this, tr("Promt"), tr("Query log failed!"));
	}
	delete[] szLogInfos;
	
}

void form1::on_ButNextPage_clicked()
{
    char szTmpLog[1024] = {0}; // using for log output

    if(ui->StartdateTime->dateTime() >= ui->EnddateTime->dateTime())
    {
		QMessageBox::about(this, "Promt", tr("Bad time set!"));
		return;
    }
	
    //get nunber
    bool numok = false;
    int nPageLine = ui->PageLine->text().toInt(&numok);
    if(!numok)
    {
        QMessageBox::about(this, "Promt", tr("Bad number set!"));
        return;
    }
	
    m_nPageLineOld = m_nPageLine;
    m_nPageLine = nPageLine;
	
    QUERY_DEVICE_LOG_PARAM stuLogParam;
    memset(&stuLogParam, 0, sizeof(QUERY_DEVICE_LOG_PARAM));
    stuLogParam.emLogType = (DH_LOG_QUERY_TYPE)ui->comboxType->currentIndex();
    stuLogParam.nStartNum = m_nPreEndNum ;
    stuLogParam.nEndNum = m_nPreEndNum + m_nPageLine - 1;
    m_nPreEndNum = stuLogParam.nEndNum + 1;
    m_nPreStartNum = stuLogParam.nStartNum;
    stuLogParam.nLogStuType = 1;
    stuLogParam.stuStartTime.dwYear = ui->StartdateTime->date().year();
    stuLogParam.stuStartTime.dwMonth = ui->StartdateTime->date().month();
    stuLogParam.stuStartTime.dwDay = ui->StartdateTime->date().day();
    stuLogParam.stuStartTime.dwHour = ui->StartdateTime->time().hour();
    stuLogParam.stuStartTime.dwMinute = ui->StartdateTime->time().minute();
    stuLogParam.stuStartTime.dwSecond = ui->StartdateTime->time().second();
	
    stuLogParam.stuEndTime.dwYear = ui->EnddateTime->date().year();
    stuLogParam.stuEndTime.dwMonth = ui->EnddateTime->date().month();
    stuLogParam.stuEndTime.dwDay = ui->EnddateTime->date().day();
    stuLogParam.stuEndTime.dwHour = ui->EnddateTime->time().hour();
    stuLogParam.stuEndTime.dwMinute = ui->EnddateTime->time().minute();
    stuLogParam.stuEndTime.dwSecond = ui->EnddateTime->time().second();
	
    DH_DEVICE_LOG_ITEM_EX *szLogInfos = new DH_DEVICE_LOG_ITEM_EX[1024];
    memset(szLogInfos, 0, sizeof(DH_DEVICE_LOG_ITEM_EX) * 1024);
    int nRetLogNum = 0;
    BOOL bRet = CLIENT_QueryDeviceLog(m_lLoginHandle, &stuLogParam, (char*)szLogInfos, 1024 * sizeof(DH_DEVICE_LOG_ITEM_EX), &nRetLogNum,DEMO_SDK_WAITTIME);
        sprintf(szTmpLog, "CLIENT_QueryDeviceLog nextpage query [%d, %d] ... return %s, nRetLogNum is %d !\n", stuLogParam.nStartNum, stuLogParam.nEndNum, bRet>0?"ok":"failure", nRetLogNum);
        printf(szTmpLog);qDebug()<<szTmpLog;
    if (bRet)
    {
        //display log info
        if (nRetLogNum <= 0)
        {
            ui->ButNextPage->setEnabled(FALSE);
                QMessageBox::about(this, tr("Promt"), tr("No record!"));
                delete[] szLogInfos;
                return;
        }
        // not enough, continue
        else if (nRetLogNum < m_nPageLine)
        {
            ui->ButPrePage->setEnabled(TRUE);

                DisPlayNewLogInfo(szLogInfos, nRetLogNum);

                int iLoop = 0;
                int nTotal = nRetLogNum;
                do
                {
                        memset(szLogInfos, 0, sizeof(DH_DEVICE_LOG_ITEM_EX) * 1024);
                        stuLogParam.nStartNum = m_nPreStartNum + nTotal;
                        stuLogParam.nEndNum = m_nPreEndNum - 1;
                        bRet = CLIENT_QueryDeviceLog(m_lLoginHandle, &stuLogParam, (char*)szLogInfos, 1024 * sizeof(DH_DEVICE_LOG_ITEM_EX), &nRetLogNum,DEMO_SDK_WAITTIME);
                        sprintf(szTmpLog, "loop[%d], CLIENT_QueryDeviceLog nextpage query [%d, %d] ... return %s, nRetLogNum is %d !\n", ++iLoop,stuLogParam.nStartNum, stuLogParam.nEndNum, bRet>0?"ok":"failure", nRetLogNum);
                        printf(szTmpLog);qDebug()<<szTmpLog;
                        if (bRet)
                        {
                                // no more
                                if (nRetLogNum <= 0)
                                {
                                        break;
                                }
                                DisPlayNewLogInfo(szLogInfos, nRetLogNum, TRUE);
                                nTotal += nRetLogNum;
                        }
                        else
                        {
                            ui->ButNextPage->setEnabled(TRUE);
                            break;
                        }

                } while (nTotal < m_nPageLine);
        }
        else
        {
            ui->ButPrePage->setEnabled(TRUE);

            DisPlayNewLogInfo(szLogInfos, nRetLogNum);
        }

        //tell if there has more logs
        memset(szLogInfos, 0, sizeof(DH_DEVICE_LOG_ITEM_EX) * 1024);
        stuLogParam.nStartNum = m_nPreEndNum;
        stuLogParam.nEndNum = m_nPreEndNum + 2;
        bRet = CLIENT_QueryDeviceLog(m_lLoginHandle, &stuLogParam, (char*)szLogInfos, 1024 * sizeof(DH_DEVICE_LOG_ITEM_EX), &nRetLogNum,DEMO_SDK_WAITTIME);
        sprintf(szTmpLog, "2 CLIENT_QueryDeviceLog nextpage query [%d, %d] ... return %s, nRetLogNum is %d !\n", stuLogParam.nStartNum, stuLogParam.nEndNum, bRet>0?"ok":"failure", nRetLogNum);
        printf(szTmpLog);qDebug()<<szTmpLog;
        if (bRet)
        {
            if (nRetLogNum > 0)
            {
                    ui->ButNextPage->setEnabled(TRUE);
            }
            else
            {
                    ui->ButNextPage->setEnabled(FALSE);
            }
        }
    }
    else
    {
        int nRowCount = ui->listViewLog->rowCount();
        for(int i = nRowCount - 1; i >= 0; i--)
        {
            ui->listViewLog->removeRow(i);
        }
        QMessageBox::about(this, tr("Promt"), tr("Query log failed!"));
    }
	
    delete[] szLogInfos;
	
}

void form1::DisPlayNewLogInfo(DH_DEVICE_LOG_ITEM_EX* pLogItem, int nCount, BOOL bAppend/* = FALSE*/)
{
	if(NULL == pLogItem || nCount <= 0)
	{
		return;
	}
	
	QString strLogType;
	QString strLogTime;
	QString strLogContext;
	
	if (!bAppend)
	{
		int nRowCount = ui->listViewLog->rowCount();
		for(int i = nRowCount - 1; i >= 0; i--)
		{
			ui->listViewLog->removeRow(i);
		}
	}
	
	if(pLogItem->bUnionType == 0)//新日志
	{
		for(int i=0; i< nCount; i++)
		{
			if(!TransLogInfo(&pLogItem[i], 0, strLogType, strLogTime, strLogContext))
			{
				continue;
			}
			
			int nIndex = ui->comboxType->currentIndex();
			if(nIndex >= 0)
			{
				DH_LOG_QUERY_TYPE eQueryType = (DH_LOG_QUERY_TYPE)nIndex;
				if(JudgeType(eQueryType,pLogItem[i].nLogType))
				{
					InsertListViewItem(strLogType,strLogTime,strLogContext);
				}
                                else
                                {
                                    QString strInfo = QString("Log type failed! Type is %1").arg(pLogItem[i].nLogType, 0, 10);
                                    QMessageBox::about(this, tr("Info"), strInfo);
                                    break;
                                }
			}// if
		}
	}
	else if(pLogItem->bUnionType == 1)//旧日志
	{
		for(int i=0; i < nCount; i++)
		{
			DH_LOG_ITEM *pOldLogItem = &(pLogItem[i].stuOldLog.stuLog);
			
			if(!TransLogInfo(pOldLogItem, 1, strLogType, strLogTime, strLogContext))
			{
				continue;
			}
			
			int nIndex = ui->comboxType->currentIndex();
			if(nIndex >= 0)
			{
				DH_LOG_QUERY_TYPE eQueryType = (DH_LOG_QUERY_TYPE)nIndex;
				if(JudgeType(eQueryType,pOldLogItem->type))
				{
					InsertListViewItem(strLogType,strLogTime,strLogContext);
				}
                                else
                                {
                                    QString strInfo = QString("Log type failed! Type is %1").arg(pLogItem[i].nLogType, 0, 10);
                                    QMessageBox::about(this, tr("Info"), strInfo);
                                    break;
                                }
			}// if
		}// for
	}
}

void form1::on_ButXMLQuery_clicked()
{
	
}
