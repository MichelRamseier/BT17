#include "form1.h"
#include "ui_form1.h"
#include <qapplication.h>
#include <qmessagebox.h>
#include <qtimer.h>
#include <qlistview.h>
#include <string>
#include <qfiledialog.h>
#include <qdatetimeedit.h>
#include <qdatetime.h>
#include <QStandardItem>
#include<iostream>
#include <stdlib.h>
using namespace std;

#include"dhnetsdk.h"
#include "./include/dhmutex.h"
#include "UserDefine.h"
#include "AlarmInfo.h"



//list for alarm information
list<CAlarmInfo*> g_listAlarmInfo;
list<CAlarmInfoEx*> g_ListAlarmInfoEx;
DHMutex	g_cs;


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


BOOL CALLBACK MessCallBack(LONG lCommand, LLONG lLoginID, char *pBuf, DWORD dwBufLen, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
    Form1 * pThis = (Form1 *)dwUser;
    if(NULL == pThis)
    {
        return FALSE;
    }

    if(!pThis->NewVer())
    {
        //cout<<"pThis->ReceiveMessage<2.6"<<endl;
        return pThis->ReceiveMessage(lLoginID, lCommand, pchDVRIP, nDVRPort, pBuf, dwBufLen);
    }
    else
    {
        return pThis->ReceiveMessageEx(lLoginID, lCommand, pchDVRIP, nDVRPort, pBuf, dwBufLen);
    }
}


void Form1::InitForm()
{

    BOOL ret = CLIENT_Init(DisConnectFunc, (LDWORD)this);

    installEventFilter(this);//install filter
    if (ret)
    {

        CLIENT_SetDVRMessCallBack(MessCallBack, (LDWORD)this);
    }
    else
    {
        QMessageBox::about(this, tr("prompt"), tr("Init SDK failed!"));
    }

    InitData();


    m_counter = new QTimer( this );
    connect(m_counter, SIGNAL(timeout()), this, SLOT(UpdateAlarmInfo()));
    m_counter->start(1000);
}

void Form1::UnInitBox(int nChannelCount, int nAlarmCount, int nType)
{
	nChannelCount = nChannelCount>32?32:nChannelCount;
	nAlarmCount = nAlarmCount>32?32:nAlarmCount;
    int i = 0;
    for(i = 0; i < nAlarmCount; i++)
    {
        QTableWidgetItem *chkBox = ui->tableWidget->takeItem(0, i);
        if (chkBox) delete chkBox;
    }
    //Video Loss
    for(i = 0; i < nChannelCount; i++)
    {
        QTableWidgetItem *chkBox = ui->tableWidget->takeItem(1, i);
        if (chkBox) delete chkBox;
    }

    //Motion Alarm
    for(i = 0; i < nChannelCount; i++)
    {
        QTableWidgetItem *chkBox = ui->tableWidget->takeItem(2, i);
        if (chkBox) delete chkBox;
    }

    if(nType == 0)
    {
        //old Shelter Alarm
        for(i = 0; i < nAlarmCount; i++)
        {
            QTableWidgetItem * chkBox = ui->tableWidget_2->takeItem(0, i);
			if (chkBox) delete chkBox;
       }
        // Extern Alarm
        for(i = 0; i < nAlarmCount; i++)
        {
            QTableWidgetItem * chkBox = ui->tableWidget_2->takeItem(1, i);
			if (chkBox) delete chkBox;
        }
        //Video Loss
        for(i = 0; i < nChannelCount; i++)
        {
            QTableWidgetItem * chkBox = ui->tableWidget_2->takeItem(2, i);
			if (chkBox) delete chkBox;
        }

        //Motion Alarm
        for(i = 0; i < nChannelCount; i++)
        {
            QTableWidgetItem * chkBox = ui->tableWidget_2->takeItem(3, i);
			if (chkBox) delete chkBox;
        }
//         //audio
//         for(i = 0; i < nChannelCount; i++)
//         {
//             QTableWidgetItem * chkBox = ui->tableWidget_2->takeItem(4, i);
// 			if (chkBox) delete chkBox;
//         }
    }
    else if(nType == 1)
    {
        //new Shelter Alarm
        for(i = 0; i < nChannelCount; i++)
        {
            QTableWidgetItem * chkBox = ui->tableWidget_3->takeItem(0, i);
			if (chkBox) delete chkBox;
        }
        // Extern Alarm
        for(i = 0; i < nAlarmCount; i++)
        {
            QTableWidgetItem * chkBox = ui->tableWidget_3->takeItem(1, i);
			if (chkBox) delete chkBox;
        }
        //Video Loss
        for(i = 0; i < nChannelCount; i++)
        {
            QTableWidgetItem * chkBox = ui->tableWidget_3->takeItem(2, i);
			if (chkBox) delete chkBox;
        }

        //Motion Alarm
        for(i = 0; i < nChannelCount; i++)
        {
            QTableWidgetItem * chkBox = ui->tableWidget_3->takeItem(3, i);
			if (chkBox) delete chkBox;
        }
//         //Urgency Alarm
//         for(i = 0; i < 16; i++)
//         {
//             QTableWidgetItem * chkBox = ui->tableWidget_3->takeItem(4, i);
// 			if (chkBox) delete chkBox;
//        }
// 		
//         //Wireless Alarm
//         for(i = 0; i < 16; i++)
//         {
//             QTableWidgetItem * chkBox = ui->tableWidget_3->takeItem(5, i);
// 			if (chkBox) delete chkBox;
//        }
//         //Encoder Alarm
//         for(i = 0; i < 16; i++)
//         {
//             QTableWidgetItem * chkBox = ui->tableWidget_3->takeItem(6, i);
// 			if (chkBox) delete chkBox;
//         }
// 		
//         //Disk_Full
//         for(i = 0; i < 1; i++)
//         {
//             QTableWidgetItem * chkBox = ui->tableWidget_3->takeItem(7, i);
// 			if (chkBox) delete chkBox;
//         }
// 		
//         //Disk_Error
//         for(i = 0; i < 32; i++)
//         {
//             QTableWidgetItem * chkBox = ui->tableWidget_3->takeItem(8, i);
// 			if (chkBox) delete chkBox;
//         }

		//Disk_Full
		for(i = 0; i < 1; i++)
		{
			QTableWidgetItem * chkBox = ui->tableWidget_3->takeItem(4, i);
			if (chkBox) delete chkBox;
		}

		//Disk_Error
		for(i = 0; i < 32; i++)
		{
			QTableWidgetItem * chkBox = ui->tableWidget_3->takeItem(5, i);
			if (chkBox) delete chkBox;
		}
	}
}
void Form1::InitBox(int nChannelCount, int nAlarmCount, int nType)
{
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);

	nChannelCount = nChannelCount>32?32:nChannelCount;
	nAlarmCount = nAlarmCount>32?32:nAlarmCount;

    int nColIndex = 0;
    ui->tableWidget->setRowCount(3);
    ui->tableWidget->setColumnCount(32);
    for( nColIndex = 0; nColIndex < ui->tableWidget->columnCount (); nColIndex++)
    {
        ui->tableWidget->setColumnWidth (nColIndex, 30);
    }

 //   ui->tableWidget_2->setRowCount(5);
	ui->tableWidget_2->setRowCount(4);
    ui->tableWidget_2->setColumnCount(32);
    for( nColIndex = 0; nColIndex < ui->tableWidget_2->columnCount (); nColIndex++)
    {
        ui->tableWidget_2->setColumnWidth (nColIndex, 30);
    }
//   ui->tableWidget_3->setRowCount(9);
	ui->tableWidget_3->setRowCount(6);
    ui->tableWidget_3->setColumnCount(32);
    for( nColIndex = 0; nColIndex < ui->tableWidget_3->columnCount (); nColIndex++)
    {
        ui->tableWidget_3->setColumnWidth (nColIndex, 30);
    }

    QStringList header;
    header <<"Extern Alarm"<<"Video Loss"<<"Motion Alarm";
    ui->tableWidget->setVerticalHeaderLabels(header);

    QStringList header2;
 //   header2 <<"Shelter Alarm"<<"Extern Alarm"<<"Motion Alarm"<<"Video Loss"<<"Audio Alarm";
	header2 <<"Shelter Alarm"<<"Extern Alarm"<<"Motion Alarm"<<"Video Loss";
    ui->tableWidget_2->setVerticalHeaderLabels(header2);

    QStringList header3;
//    header3 <<"Shelter Alarm"<<"Extern Alarm"<<"Motion Alarm"<<"Video Loss"<<"Urgency Alarm"<<"Wireless Alarm"<<"Encoder Alarm"<<"Disk Full"<<"Disk Error";
	header3 <<"Shelter Alarm"<<"Extern Alarm"<<"Motion Alarm"<<"Video Loss"<<"Disk Full"<<"Disk Error";
    ui->tableWidget_3->setVerticalHeaderLabels(header3);


    //query Extern Alarm
    int i = 0;
    for(i = 0; i < nAlarmCount; i++)
    {
        QTableWidgetItem * chkBox = new QTableWidgetItem(true);
        chkBox->setFlags(Qt::ItemIsEnabled/*|Qt::ItemIsUserCheckable*/);
        chkBox->setCheckState (Qt::Unchecked);
        ui->tableWidget->setItem(0, i, chkBox);
    }
    //Video Loss
    for(i = 0; i < nChannelCount; i++)
    {
        QTableWidgetItem * chkBox = new QTableWidgetItem(true);
        chkBox->setFlags(Qt::ItemIsEnabled/*|Qt::ItemIsUserCheckable*/);
        chkBox->setCheckState (Qt::Unchecked);
        ui->tableWidget->setItem(1, i, chkBox);
    }

    //Motion Alarm
    for(i = 0; i < nChannelCount; i++)
    {
        QTableWidgetItem * chkBox = new QTableWidgetItem(true);
        chkBox->setFlags(Qt::ItemIsEnabled/*|Qt::ItemIsUserCheckable*/);
        chkBox->setCheckState (Qt::Unchecked);
        ui->tableWidget->setItem(2, i, chkBox);
    }

    if(nType == 0)
    {
        //old Shelter Alarm
        for(i = 0; i < nAlarmCount; i++)
        {
            QTableWidgetItem * chkBox = new QTableWidgetItem(true);
            chkBox->setFlags(Qt::ItemIsEnabled/*|Qt::ItemIsUserCheckable*/);
            chkBox->setCheckState (Qt::Unchecked);
            ui->tableWidget_2->setItem(0, i, chkBox);
        }
        // Extern Alarm
        for(i = 0; i < nAlarmCount; i++)
        {
            QTableWidgetItem * chkBox = new QTableWidgetItem(true);
            chkBox->setFlags(Qt::ItemIsEnabled/*|Qt::ItemIsUserCheckable*/);
            chkBox->setCheckState (Qt::Unchecked);
            ui->tableWidget_2->setItem(1, i, chkBox);
        }
        //Video Loss
        for(i = 0; i < nChannelCount; i++)
        {
            QTableWidgetItem * chkBox = new QTableWidgetItem(true);
            chkBox->setFlags(Qt::ItemIsEnabled/*|Qt::ItemIsUserCheckable*/);
            chkBox->setCheckState (Qt::Unchecked);
            ui->tableWidget_2->setItem(2, i, chkBox);
        }

        //Motion Alarm
        for(i = 0; i < nChannelCount; i++)
        {
            QTableWidgetItem * chkBox = new QTableWidgetItem(true);
            chkBox->setFlags(Qt::ItemIsEnabled/*|Qt::ItemIsUserCheckable*/);
             chkBox->setCheckState (Qt::Unchecked);
            ui->tableWidget_2->setItem(3, i, chkBox);
        }
//         //audio
//         for(i = 0; i < nChannelCount; i++)
//         {
//             QTableWidgetItem * chkBox = new QTableWidgetItem(true);
//             chkBox->setFlags(Qt::ItemIsEnabled/*|Qt::ItemIsUserCheckable*/);
//              chkBox->setCheckState (Qt::Unchecked);
//             ui->tableWidget_2->setItem(4, i, chkBox);
//         }
    }
    else if(nType == 1)
    {
        //new Shelter Alarm
        for(i = 0; i < nChannelCount; i++)
        {
            QTableWidgetItem * chkBox = new QTableWidgetItem(true);
            chkBox->setFlags(Qt::ItemIsEnabled/*|Qt::ItemIsUserCheckable*/);
             chkBox->setCheckState (Qt::Unchecked);
            ui->tableWidget_3->setItem(0, i, chkBox);
        }
        // Extern Alarm
        for(i = 0; i < nAlarmCount; i++)
        {
            QTableWidgetItem * chkBox = new QTableWidgetItem(true);
            chkBox->setFlags(Qt::ItemIsEnabled/*|Qt::ItemIsUserCheckable*/);
             chkBox->setCheckState (Qt::Unchecked);
            ui->tableWidget_3->setItem(1, i, chkBox);
        }
        //Video Loss
        for(i = 0; i < nChannelCount; i++)
        {
            QTableWidgetItem * chkBox = new QTableWidgetItem(true);
            chkBox->setFlags(Qt::ItemIsEnabled/*|Qt::ItemIsUserCheckable*/);
            chkBox->setCheckState (Qt::Unchecked);
            ui->tableWidget_3->setItem(2, i, chkBox);
        }

        //Motion Alarm
        for(i = 0; i < nChannelCount; i++)
        {
            QTableWidgetItem * chkBox = new QTableWidgetItem(true);
            chkBox->setFlags(Qt::ItemIsEnabled/*|Qt::ItemIsUserCheckable*/);
             chkBox->setCheckState (Qt::Unchecked);
            ui->tableWidget_3->setItem(3, i, chkBox);
		}
//         //Urgency Alarm
//         for(i = 0; i < 16; i++)
//         {
//             QTableWidgetItem * chkBox = new QTableWidgetItem(true);
//             chkBox->setFlags(Qt::ItemIsEnabled/*|Qt::ItemIsUserCheckable*/);
//              chkBox->setCheckState (Qt::Unchecked);
//             ui->tableWidget_3->setItem(4, i, chkBox);
//         }
// 
//         //Wireless Alarm
//         for(i = 0; i < 16; i++)
//         {
//             QTableWidgetItem * chkBox = new QTableWidgetItem(true);
//             chkBox->setFlags(Qt::ItemIsEnabled/*|Qt::ItemIsUserCheckable*/);
//              chkBox->setCheckState (Qt::Unchecked);
//             ui->tableWidget_3->setItem(5, i, chkBox);
//         }
//         //Encoder Alarm
//         for(i = 0; i < 16; i++)
//         {
//             QTableWidgetItem * chkBox = new QTableWidgetItem(true);
//             chkBox->setFlags(Qt::ItemIsEnabled/*|Qt::ItemIsUserCheckable*/);
//              chkBox->setCheckState (Qt::Unchecked);
//             ui->tableWidget_3->setItem(6, i, chkBox);
//         }
// 
//         //Disk_Full
//         for(i = 0; i < 1; i++)
//         {
//             QTableWidgetItem * chkBox = new QTableWidgetItem(true);
//             chkBox->setFlags(Qt::ItemIsEnabled/*|Qt::ItemIsUserCheckable*/);
//              chkBox->setCheckState (Qt::Unchecked);
//             ui->tableWidget_3->setItem(7, i, chkBox);
//         }
// 
//         //Disk_Error
//         for(i = 0; i < 32; i++)
//         {
//             QTableWidgetItem * chkBox = new QTableWidgetItem(true);
//             chkBox->setFlags(Qt::ItemIsEnabled/*|Qt::ItemIsUserCheckable*/);
//              chkBox->setCheckState (Qt::Unchecked);
//             ui->tableWidget_3->setItem(8, i, chkBox);
//         }

		//Disk_Full
		for(i = 0; i < 1; i++)
		{
			QTableWidgetItem * chkBox = new QTableWidgetItem(true);
			chkBox->setFlags(Qt::ItemIsEnabled/*|Qt::ItemIsUserCheckable*/);
			chkBox->setCheckState (Qt::Unchecked);
			ui->tableWidget_3->setItem(4, i, chkBox);
		}

		//Disk_Error
		for(i = 0; i < 32; i++)
		{
			QTableWidgetItem * chkBox = new QTableWidgetItem(true);
			chkBox->setFlags(Qt::ItemIsEnabled/*|Qt::ItemIsUserCheckable*/);
			chkBox->setCheckState (Qt::Unchecked);
			ui->tableWidget_3->setItem(5, i, chkBox);
		}

    }

}

void Form1::destroyForm()
{
    cout<<"destroyed"<<endl;


    if(m_bIsListen)
    {
        m_bIsListen = FALSE;
        CLIENT_StopListen(m_lLoginHandle);
    }


    if(0 != m_lLoginHandle)
    {
        CLIENT_Logout(m_lLoginHandle);
    }

    CLIENT_Cleanup();

    m_counter->stop();
}


void Form1::on_Logout_clicked()
{
    if (m_lLoginHandle != 0)
    {  
		if(m_bIsListen)
		{
			m_bIsListen = FALSE;
			CLIENT_StopListen(m_lLoginHandle);
		}
        BOOL bSuccess = CLIENT_Logout(m_lLoginHandle);
        if (bSuccess)
        {
            ui->Logout->setEnabled(false);
            ui->Login->setEnabled(true);
            ui->ButQueryAlarmState->setEnabled(false);
            ui->tabWidget2->setTabEnabled(1, true);

            ui->tabWidget2->setTabEnabled(2, true);

            ResetCheckstate();
        }
        else
        {
            QMessageBox::about(this, tr("Prompt"), tr("Logout failed!"));
        }

		UnInitBox(m_nChannelCount, m_nInputAlarmCount,m_bNewVer);
    }
}


void Form1::InitData()
{
    m_lLoginHandle = 0;

    ui->Logout->setEnabled(false);
    ui->Login->setEnabled(true);
    ui->ButQueryAlarmState->setEnabled(false);

	memset(&m_stNetAlarmState,0,sizeof(m_stNetAlarmState));
	memset(&m_stNetMotionDetectState,0,sizeof(m_stNetMotionDetectState));
	memset(&m_stNetVideoLostState,0,sizeof(m_stNetVideoLostState));

    m_nChannelCount = 16;
    m_nInputAlarmCount = 16;

    m_bNewVer = false;
    m_bIsListen = FALSE;

    ui->lineEdit3->setEchoMode(QLineEdit::Password);
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
            ui->Logout->setEnabled(true);
            ui->Login->setEnabled(false);
            ui->ButQueryAlarmState->setEnabled(true);
            int nProtoVer = 0;
            int nRet = 0;
            int nRetLen =0;
            m_nChannelCount = deviceInfo.byChanNum; 

			//登录时查不到alarminputcount数据，此处手动查询获�?
			 memset(&m_stNetAlarmState,0,sizeof(m_stNetAlarmState));
			 m_stNetAlarmState.dwSize = sizeof(NET_CLIENT_ALARM_STATE);
			 nRet = CLIENT_QueryDevState(m_lLoginHandle,DH_DEVSTATE_ALARM,(char*)&m_stNetAlarmState,sizeof(m_stNetAlarmState),&nRetLen);
			 if(nRet <= 0 && nRetLen == 0)
			 {
				  QMessageBox::about(this, tr("Prompt"), tr("Get AlarmState failed!"));
			 }
			 m_nInputAlarmCount = m_stNetAlarmState.alarminputcount;



            BOOL bSuccess = CLIENT_QueryDevState(m_lLoginHandle, DH_DEVSTATE_PROTOCAL_VER, (char*)&nProtoVer, sizeof(int), &nRet, 1000);
            if (bSuccess)
            {
              if (nProtoVer >= 5)
              {
                     m_bNewVer = true;
                     ui->tabWidget2->setTabEnabled(1, false);
                     InitBox(deviceInfo.byChanNum, m_nInputAlarmCount, 1);

              }
              else
              {
                     m_bNewVer =false;
                     ui->tabWidget2->setTabEnabled(2, false);
                     InitBox(deviceInfo.byChanNum, m_nInputAlarmCount, 0);
              }
            }

            BOOL bRet = FALSE;
            if(!m_bNewVer)
            {
                bRet = CLIENT_StartListen(m_lLoginHandle);
            }
            else
            {
                bRet = CLIENT_StartListenEx(m_lLoginHandle);
            }
            if(bRet)
            {
                m_bIsListen = TRUE;
            }
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

BOOL Form1::ReceiveMessage(LLONG lLoginID, LONG lCommand, char *pchDVRIP, LONG nDVRPort, char *pBuf, DWORD dwBufLen)
{
    //cout<<"receiveMessage in"<<endl;
    BOOL bRet = FALSE;
    switch(lCommand)
    {
        case DH_COMM_ALARM:
        {
            DHCommAlarm(pBuf,dwBufLen);
            bRet = TRUE;
        }
        break;
        case DH_SHELTER_ALARM:
        {
            DHShelterAlarm(pBuf,dwBufLen);
            bRet = TRUE;
        }
        break;
        case DH_DISK_FULL_ALARM:
        {
            DHDiskFullAlarm(pBuf,dwBufLen);
            bRet = TRUE;
        }
        break;
        case DH_DISK_ERROR_ALARM:
        {
            DHDiskError(pBuf,dwBufLen);
            bRet = TRUE;
        }
        break;
//         case DH_SOUND_DETECT_ALARM:
//         {
//             DHSoundAlarm(pBuf,dwBufLen);
//             bRet = TRUE;
//         }
//         break;
        case DH_ALARM_DECODER_ALARM:
        {
            bRet = TRUE;
        }
        break;
        default:
        break;
    }
    //    cout<<"receiveMessage out"<<lCommand<<endl;
    return bRet;

}

BOOL Form1::ReceiveMessageEx(LLONG lLoginID, LONG lCommand, char *pchDVRIP, LONG nDVRPort, char *pBuf, DWORD dwBufLen)
{
    BOOL bRet = FALSE;
    CAlarmInfoEx* alarmAlarm = new CAlarmInfoEx;

    switch(lCommand)
    {
        case DH_ALARM_ALARM_EX:
        {
            alarmAlarm->m_AlarmCommand = VIDEO_ALARM_ALARMEX;
            memcpy(alarmAlarm->m_dwAlarm,pBuf,dwBufLen);
            bRet = TRUE;
        }
        break;
        case DH_MOTION_ALARM_EX:
        {
            alarmAlarm->m_AlarmCommand = VIDEO_MOTIONDETECT_ALARMEX;
            memcpy(alarmAlarm->m_dwAlarm,pBuf,dwBufLen);

            bRet = TRUE;
        }
        break;
        case DH_VIDEOLOST_ALARM_EX:
        {
            alarmAlarm->m_AlarmCommand = VIDEO_VEDIOSHELTER_ALARMEX;
            memcpy(alarmAlarm->m_dwAlarm,pBuf,dwBufLen);
            bRet = TRUE;
        }
        break;
        case DH_SHELTER_ALARM_EX:
        {
            alarmAlarm->m_AlarmCommand = VIDEO_SHELTER_ALARMEX;
            memcpy(alarmAlarm->m_dwAlarm,pBuf,dwBufLen);
            bRet = TRUE;
        }
        break;
        case DH_SOUND_DETECT_ALARM_EX:
        {
            alarmAlarm->m_AlarmCommand = VIDEO_SOUNDDETECT_ALARMEX;
            memcpy(&alarmAlarm->m_stuNewSound,pBuf,dwBufLen);
            bRet = TRUE;
        }
        break;
        case DH_DISKFULL_ALARM_EX:
        {
            alarmAlarm->m_AlarmCommand = VIDEO_DISKFULL_ALARMEX;
            memcpy(alarmAlarm->m_dwAlarm,pBuf,dwBufLen);
            bRet = TRUE;
        }
        break;
        case DH_DISKERROR_ALARM_EX:
        {
            alarmAlarm->m_AlarmCommand = VIDEO_DISKERROR_ALARMEX;
            memcpy(alarmAlarm->m_dwAlarm,pBuf,dwBufLen);
            bRet = TRUE;
        }
        break;
//         case DH_ENCODER_ALARM_EX:
//         {
//             alarmAlarm->m_AlarmCommand = VIDEO_ENCODER_ALARMEX;
//             memcpy(alarmAlarm->m_dwAlarm,pBuf,dwBufLen);
//             bRet = TRUE;
//         }
//         break;
//         case DH_URGENCY_ALARM_EX:
//         {
//             alarmAlarm->m_AlarmCommand = VIDEO_URGENCY_ALARMEX;
//             memcpy(alarmAlarm->m_dwAlarm,pBuf,dwBufLen);
// 			  bRet = TRUE;
//         }
//         break;
//         case DH_WIRELESS_ALARM_EX:
//         {
//             alarmAlarm->m_AlarmCommand = VIDEO_WIRELESS_ALARMEX;
//             memcpy(alarmAlarm->m_dwAlarm,pBuf,dwBufLen);
//             bRet = TRUE;
//         }
//         break;
        default:
        break;
    }

        g_cs.Lock();
    g_ListAlarmInfoEx.push_back(alarmAlarm);
        g_cs.UnLock();
    return bRet;
}


void Form1::DHCommAlarm(char *pBuf, DWORD dwBufLen)
{
    NET_CLIENT_STATE *pState = (NET_CLIENT_STATE *)pBuf;
    if (dwBufLen != sizeof(NET_CLIENT_STATE) || pState == NULL)
    {
        return;
    }

    CAlarmInfo *alarmInfo = new CAlarmInfo;
    alarmInfo->m_nChannelCount = pState->channelcount;
    alarmInfo->m_nAlarmInputCount = pState->alarminputcount;
    alarmInfo->m_AlarmCommand = VIDEO_COMMON_ALARM;
    int i = 0;
    for(i=0;i<alarmInfo->m_nAlarmInputCount;i++)
    {
        if(1 == pState->alarm[i])
        {
            alarmInfo->m_InputAlarm = alarmInfo->m_InputAlarm | (1<<i);
        }
    }
    for(i=0;i<alarmInfo->m_nChannelCount;i++)
    {
        if(1 == pState->videolost[i])
        {
            alarmInfo->m_VideoLost = alarmInfo->m_VideoLost | (1<<i);
        }
    }

    for(i=0;i<alarmInfo->m_nChannelCount;i++)
    {
        if(1 == pState->motiondection[i])
        {
            alarmInfo->m_MotionDetect = alarmInfo->m_MotionDetect | (1<<i);
        }
    }
    //TRACE("wInputAlarm=%d  wVideoLost=%d  wMotionAlarm=%d\n",alarmInfo->m_InputAlarm,alarmInfo->m_VideoLost,alarmInfo->m_MotionDetect);
        g_cs.Lock();
    g_listAlarmInfo.push_back(alarmInfo);
        g_cs.UnLock();
}

void Form1::DHShelterAlarm(char *pBuf, DWORD dwBufLen)
{
    if (dwBufLen != 16)
    {
        return;
    }
    CAlarmInfo *alarmInfo = new CAlarmInfo;
    alarmInfo->m_AlarmCommand = VIDEO_VIDEOSHELTER_ALARM;
    for(int i=0;i<16;i++)
    {
        char c = pBuf[i];
        if(1 == c)
        {
            alarmInfo->m_ShelterAlarm = alarmInfo->m_ShelterAlarm | (1<<i);
        }
    }
        g_cs.Lock();
    g_listAlarmInfo.push_back(alarmInfo);
        g_cs.UnLock();
}

void Form1::DHDiskFullAlarm(char *pBuf, DWORD dwBufLen)
{
    if (dwBufLen != sizeof(DWORD))
    {
        return;
    }
    CAlarmInfo *alarmInfo = new CAlarmInfo;
    alarmInfo->m_AlarmCommand = VIDEO_DISKFULL_ALARM;
    DWORD dwDiskFull = *(DWORD*)pBuf;
    if(1 == dwDiskFull)
    {
        alarmInfo->m_DiskFull = TRUE;
    }
        g_cs.Lock();
    g_listAlarmInfo.push_back(alarmInfo);
        g_cs.UnLock();
}

void Form1::DHDiskError(char *pBuf, DWORD dwBufLen)
{
    if (dwBufLen != sizeof(DWORD))
    {
        return;
    }
    CAlarmInfo *alarmInfo = new CAlarmInfo;
    alarmInfo->m_AlarmCommand = VIDEO_DISKERROR_ALARM;
    alarmInfo->m_DiskError = *(DWORD*)pBuf;
    g_cs.Lock();
    g_listAlarmInfo.push_back(alarmInfo);
        g_cs.UnLock();
}


void Form1::DHSoundAlarm(char *pBuf, DWORD dwBufLen)
{
    if (dwBufLen != 16)
    {
        return;
    }
    CAlarmInfo *alarmInfo = new CAlarmInfo;
    alarmInfo->m_AlarmCommand = VIDEO_SOUNDDETECT_ALARM;
    for(int i=0;i<16;i++)
    {
        char c = pBuf[i];
        if(1 == c)
        {
            alarmInfo->m_SoundDetect = alarmInfo->m_SoundDetect | (1<<i);
        }
    }
        g_cs.Lock();
    g_listAlarmInfo.push_back(alarmInfo);
        g_cs.UnLock();
}


//change qTime to NET_TIME
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


void Form1::ConvertTimeToStr(NET_TIME nettime, QDate *date, QTime *time)
{
    date->setYMD(nettime.dwYear, nettime.dwMonth, nettime.dwDay);
    time->setHMS(nettime.dwHour, nettime.dwMinute, nettime.dwSecond);
}


void Form1::ButExit_clicked()
{
    destroyForm();
    exit(0);
}

void Form1::ButQueryAlarmState_clicked()
{
    int nRet =0 ;
    int nRetLen =0;

	memset(&m_stNetAlarmState,0,sizeof(m_stNetAlarmState));
	m_stNetAlarmState.dwSize = sizeof(NET_CLIENT_ALARM_STATE);
	nRet = CLIENT_QueryDevState(m_lLoginHandle,DH_DEVSTATE_ALARM,(char*)&m_stNetAlarmState,sizeof(m_stNetAlarmState),&nRetLen);
	if(nRet <= 0 && nRetLen == 0)
	{
		QMessageBox::about(this, tr("Prompt"), tr("Get AlarmState failed!"));
	}

	memset(&m_stNetVideoLostState,0,sizeof(m_stNetVideoLostState));
	m_stNetVideoLostState.dwSize = sizeof(NET_CLIENT_VIDEOLOST_STATE);
	nRet = CLIENT_QueryDevState(m_lLoginHandle,DH_DEVSTATE_VIDEOLOST,(char*)&m_stNetVideoLostState,sizeof(m_stNetVideoLostState),&nRetLen);
	if(nRet <= 0 && nRetLen == 0)
	{
		QMessageBox::about(this, tr("Prompt"), tr("Get VideoLostState failed!"));
	}

	memset(&m_stNetMotionDetectState,0,sizeof(m_stNetMotionDetectState));
	m_stNetMotionDetectState.dwSize = sizeof(NET_CLIENT_MOTIONDETECT_STATE);
	nRet = CLIENT_QueryDevState(m_lLoginHandle,DH_DEVSTATE_MOTIONDETECT,(char*)&m_stNetMotionDetectState,sizeof(m_stNetMotionDetectState),&nRetLen);
	if(nRet <= 0 && nRetLen == 0)
	{
		QMessageBox::about(this, tr("Prompt"), tr("Get MotionDetectState failed!"));
	}

	SetQueryAlarmInfo();

}


void Form1::SetQueryAlarmInfo()
{
	int nAlarmCount = m_nInputAlarmCount>32?32:m_nInputAlarmCount;
	int nCount = m_nChannelCount>32?32:m_nChannelCount;
	
	for(int i = 0;i < nAlarmCount;i++)
	{

		if(i < m_stNetAlarmState.alarminputcount)
		{
			ui->tableWidget->item(0, i)->setCheckState(((m_stNetAlarmState.dwAlarmState[0] >> i) & 0x01)>0?
				Qt::Checked:Qt::Unchecked);
		}

		else
		{
			//ui->tableWidget->item(0, i)->setCheckState(Qt::Unchecked);
		}
	}
	for(int i = 0;i < nCount;i++)
	{
		if(i < m_stNetVideoLostState.channelcount)
		{
			ui->tableWidget->item(1, i)->setCheckState(((m_stNetVideoLostState.dwAlarmState[0] >> i) & 0x01)>0? 
				Qt::Checked:Qt::Unchecked);
			ui->tableWidget->item(2, i)->setCheckState(((m_stNetMotionDetectState.dwAlarmState[0] >> i) & 0x01)>0?
				Qt::Checked:Qt::Unchecked);
		}
		else
		{
			ui->tableWidget->item(1, i)->setCheckState(Qt::Unchecked);
			ui->tableWidget->item(2, i)->setCheckState(Qt::Unchecked);
		}
	}

}


void Form1::UpdateAlarmInfo()
{
	//   cout<<"UpdateAlarmInfo() in"<<endl;
	g_cs.Lock();
	if (!m_bIsListen)
	{
		g_listAlarmInfo.clear();
	}
	//   cout<<"CReadWriteMutexLock lock in display"<<endl;
	else if(!m_bNewVer)//old
	{
		if(g_listAlarmInfo.size() != 0)
		{
			//           cout<<"g_listAlarmInfo dispalay in"<<endl;
			//TRACE("%dAAAAAAAAAAAAAAAAAAA\n",m_listAlarmInfo.GetCount());
			WORD wInputAlarm = 0;
			WORD wVideoLost = 0;
			WORD wMotionAlarm = 0;
			WORD wVideoShelter = 0;
			WORD wSoundAlarm = 0;

			list<CAlarmInfo*>::iterator it;
			for(it = g_listAlarmInfo.begin(); it != g_listAlarmInfo.end(); it++)
			{
				CAlarmInfo* alarmInfo = *it;
				if (alarmInfo != NULL)
				{
					EN_DVR_ALARMTYPE enAlarmType = alarmInfo->m_AlarmCommand;
					//TRACE("%dBBBBBBBBBBBBBBBBBBBBB\n",enAlarmType);
					switch(enAlarmType)
					{
					case VIDEO_COMMON_ALARM:
						{
							wInputAlarm = m_curAlarmInfo.m_InputAlarm ^ alarmInfo->m_InputAlarm;
							wVideoLost = m_curAlarmInfo.m_VideoLost ^ alarmInfo->m_VideoLost;
							wMotionAlarm = m_curAlarmInfo.m_MotionDetect ^ alarmInfo->m_MotionDetect;

							SetCommonAlarmInfo(wInputAlarm, wVideoLost, wMotionAlarm, alarmInfo->m_nChannelCount, alarmInfo->m_nAlarmInputCount);

							m_curAlarmInfo.m_InputAlarm = alarmInfo->m_InputAlarm;
							m_curAlarmInfo.m_VideoLost = alarmInfo->m_VideoLost;
							m_curAlarmInfo.m_MotionDetect = alarmInfo->m_MotionDetect;
							m_curAlarmInfo.m_nAlarmInputCount = alarmInfo->m_nAlarmInputCount;
							m_curAlarmInfo.m_nChannelCount = alarmInfo->m_nChannelCount;
						}
						break;
					case VIDEO_VIDEOSHELTER_ALARM:
						{
							wVideoShelter = m_curAlarmInfo.m_ShelterAlarm ^ alarmInfo->m_ShelterAlarm;

							SetShelterAlarmInfo(wVideoShelter);

							m_curAlarmInfo.m_ShelterAlarm = alarmInfo->m_ShelterAlarm;
						}
						break;
						//                                         case VIDEO_SOUNDDETECT_ALARM:
						//                                                 {
						//                                                         wSoundAlarm = m_curAlarmInfo.m_SoundDetect ^ alarmInfo->m_SoundDetect;
						// 
						//                                                         SetSoundAlarmInfo(wSoundAlarm);
						// 
						//                                                         m_curAlarmInfo.m_SoundDetect = alarmInfo->m_SoundDetect;
						//                                                 }
						//                                                break;
					case VIDEO_DISKFULL_ALARM:
						{
							SetDiskFullAlarmInfo(alarmInfo->m_DiskFull);

							m_curAlarmInfo.m_DiskFull = alarmInfo->m_DiskFull;
						}
						break;
					case VIDEO_DISKERROR_ALARM:
						{
							SetDiskErrorAlarmInfo(alarmInfo->m_DiskError);

							m_curAlarmInfo.m_DiskError = alarmInfo->m_DiskError;
						}
						break;
					default:
						break;
					}
					delete alarmInfo;
					alarmInfo = NULL;
				}

			}
			g_listAlarmInfo.clear();
			//            cout<<"g_listAlarmInfo dispalay out"<<endl;
		}
	}
	else
	{
		//define VER_2_600_0
		//////////////////////////////////////////////////////////////////////////
		//new alarm section
		//////////////////////////////////////////////////////////////////////////
		//        cout<<"g_listAlarmInfoex dispalay in"<<endl;
		if(g_ListAlarmInfoEx.size() != 0)
		{
			list<CAlarmInfoEx*>::iterator it;
			for(it = g_ListAlarmInfoEx.begin(); it != g_ListAlarmInfoEx.end(); it++)
			{
				CAlarmInfoEx* alarmInfoEx = *it;
				if (alarmInfoEx != NULL)
				{

					EN_DVR_ALARMTYPE_EX enAlarmType = alarmInfoEx->m_AlarmCommand;
					//TRACE("%dBBBBBBBBBBBBBBBBBBBBB\n",enAlarmType);
					switch(enAlarmType)
					{
					case VIDEO_ALARM_ALARMEX:
						SetAlarmInfo(alarmInfoEx->m_dwAlarm, 1);
						break;
					case VIDEO_MOTIONDETECT_ALARMEX:
						SetAlarmInfo(alarmInfoEx->m_dwAlarm, 2);
						break;
					case VIDEO_VEDIOSHELTER_ALARMEX:
						SetAlarmInfo(alarmInfoEx->m_dwAlarm, 3);
						break;
					case VIDEO_SHELTER_ALARMEX:
						//printf("coming in case VIDEO_SHELTER_ALARMEX, Data:%d\n", alarmInfoEx->m_dwAlarm[0]);
						SetAlarmInfo(alarmInfoEx->m_dwAlarm, 0);
						break;
						//                                         case VIDEO_ENCODER_ALARMEX:
						//                                                SetAlarmInfo(alarmInfoEx->m_dwAlarm, 6);
						//                                                 break;
						//                                         case VIDEO_URGENCY_ALARMEX:
						//                                                SetAlarmInfo(alarmInfoEx->m_dwAlarm, 4);
						//                                                 break;
						//                                         case VIDEO_WIRELESS_ALARMEX:
						//                                                 SetAlarmInfo(alarmInfoEx->m_dwAlarm, 5);
						//                                                 break;
						//                                         case VIDEO_SOUNDDETECT_ALARMEX:
						//                                                 SetSoundAlarmInfo(alarmInfoEx->m_stuNewSound);
						//                                                 break;
						//                                         case VIDEO_DISKFULL_ALARMEX:
						//                                                 SetAlarmInfo(alarmInfoEx->m_dwAlarm, 7);
						//                                                 break;
						//                                         case VIDEO_DISKERROR_ALARMEX:
						//                                                 SetAlarmInfo(alarmInfoEx->m_dwAlarm, 8);
						//                                                 break;
					case VIDEO_DISKFULL_ALARMEX:
						SetAlarmInfo(alarmInfoEx->m_dwAlarm, 4);
						break;
					case VIDEO_DISKERROR_ALARMEX:
						SetAlarmInfo(alarmInfoEx->m_dwAlarm, 5);
						break;
					default :
						break;
					}
					delete alarmInfoEx;
					alarmInfoEx = NULL;
				}

			}
			g_ListAlarmInfoEx.clear();
			//           cout<<"g_listAlarmInfo dispalay out"<<endl;
		}
	}
	g_cs.UnLock();
	//   cout<<"UpdateAlarmInfo() out"<<endl;
}


void Form1::SetCommonAlarmInfo(WORD wInputAlarm, WORD wVideoLost, WORD wMotionAlarm, int nChannelCount, int nInputAlarmCount)
{
	int i = 0;

	if(0 != wInputAlarm)
	{
		int nCount = m_nInputAlarmCount>32?32:m_nInputAlarmCount;
		for(i = 0; i < nCount; i++)
		{
			WORD wAI = (1<<i);
			WORD wInput = wInputAlarm | (~wAI);
			WORD wReverse = ~wInput;
			if(0 == wReverse)
			{
				if(ui->tableWidget_2->item(1, i)->checkState() == Qt::Checked)
				{
					ui->tableWidget_2->item(1, i)->setCheckState(Qt::Unchecked);
				}
				else
				{
					ui->tableWidget_2->item(1, i)->setCheckState(Qt::Checked);
				}
			}
		}
	}

	if(0 != wVideoLost)
	{
		int nCount = m_nChannelCount>32?32:m_nChannelCount;
		for(i=0;i<nCount;i++)
		{
			WORD wAV = (1<<i);
			WORD wVideo = wVideoLost | (~wAV);
			WORD wReverse = ~wVideo;
			if(0 == wReverse)
			{
				if(ui->tableWidget_2->item(3, i)->checkState() == Qt::Checked)
				{
					ui->tableWidget_2->item(3, i)->setCheckState(Qt::Unchecked);
				}
				else
				{
					ui->tableWidget_2->item(3, i)->setCheckState(Qt::Checked);
				}
			}
		}
	}

	if(0 != wMotionAlarm)
	{
		int nCount = m_nChannelCount>32?32:m_nChannelCount;
		for(i=0;i<nCount;i++)
		{
			WORD wAV = (1<<i);
			WORD wMotion = wMotionAlarm | (~wAV);
			WORD wReverse = ~wMotion;
			if(0 == wReverse)
			{
				if(ui->tableWidget_2->item(2, i)->checkState() == Qt::Checked)
				{
					ui->tableWidget_2->item(2, i)->setCheckState(Qt::Unchecked);
				}
				else
				{
					ui->tableWidget_2->item(2, i)->setCheckState(Qt::Checked);
				}
			}
		}
	}
	//TRACE(" %d  %d  %d \n",wInputAlarm,wVideoLost,wMotionAlarm);
}


void Form1::SetShelterAlarmInfo(WORD wVideoShelter)
{
	int i = 0;
	int nCount = m_nChannelCount>32?32:m_nChannelCount;
	for(i=0;i<nCount;i++)
	{
		WORD wAS = (1<<i);
		WORD wShelter = wVideoShelter | (~wAS);
		WORD wReverse = ~wShelter;
		if(0 == wReverse)
		{
			if(ui->tableWidget_2->item(0, i)->checkState() == Qt::Checked)
			{
				ui->tableWidget_2->item(0, i)->setCheckState(Qt::Unchecked);
			}
			else
			{
				ui->tableWidget_2->item(0, i)->setCheckState(Qt::Checked);
			}
		}
	}
}


void Form1::SetSoundAlarmInfo(WORD wSoundAlarm)
{
    int i = 0;
	int nCount = m_nChannelCount>32?32:m_nChannelCount;
    for(i=0;i<nCount;i++)
    {
        WORD wAS = (1<<i);
        WORD wSound = wSoundAlarm | (~wAS);
        WORD wReverse = ~wSound;
        if(0 == wReverse)
        {
            if(ui->tableWidget_2->item(4, i)->checkState() == Qt::Checked)
            {
                ui->tableWidget_2->item(4, i)->setCheckState(Qt::Unchecked);
            }
            else
            {
                ui->tableWidget_2->item(4, i)->setCheckState(Qt::Checked);
            }
        }
    }
}


void Form1::SetDiskFullAlarmInfo(BOOL bDiskFull)
{

    if(bDiskFull)
    {
        ui->tableWidget_3->item(7,1)->setCheckState(Qt::Checked);
    }
    else
    {
        ui->tableWidget_3->item(7,1)->setCheckState(Qt::Unchecked);
    }
}


void Form1::SetDiskErrorAlarmInfo(DWORD dwDiskError)
{
    QString strDiskError;
    for(int i = 0; i < 32; i++)
    {
        DWORD dwAD = (1<<i);
        DWORD dwDisk = dwDiskError | (~dwAD);
        DWORD wReverse = ~dwDisk;
        if(0 == wReverse)
        {
            QString str;
            str.sprintf(" %d ", i);
            strDiskError.append(str);
        }
    }
    ui->EditDiskError->setText(strDiskError);
}


void Form1::SetAlarmInfo(BYTE *dwAlarm, DWORD dwID)
{
    int i = 0;
    int nCount = 16;

    switch(dwID)
    {
    case 0:
    case 2:
    case 3:
    nCount = m_nChannelCount;
    break;
    case 1:
     nCount = m_nInputAlarmCount;
     break;
//     case 4:
//     case 5:
//     case 6:
//      nCount = 16;
//      break;
//     case 7:
//      nCount = 1;
//      break;
//     case 8:
//      nCount = 32;
//      break;

	case 4:
		nCount = 1;
		break;
	case 5:
		nCount = 32;
		break;
    }

	nCount = nCount>32?32:nCount;

    for(i=0; i < nCount; i++)
    {
      ui->tableWidget_3->item(dwID, i)->setCheckState(dwAlarm[i]>0?Qt::Checked:Qt::Unchecked);
    }
}


void Form1::SetSoundAlarmInfo(DH_NEW_SOUND_ALARM_STATE &stuSoundAlarm)
{
    char szBuf[2048] ={0};

	int nCount =stuSoundAlarm.channelcount>32?32:stuSoundAlarm.channelcount;

    for(int i=0;i<nCount;i++)
    {
        char szTempBuf[256];
        memset(szTempBuf,0,sizeof(char)*256);
        sprintf(szTempBuf
                        ,"channel:%d type:%d volume:%d \n"
                        ,stuSoundAlarm.SoundAlarmInfo[i].channel
                        ,stuSoundAlarm.SoundAlarmInfo[i].alarmType
                        ,stuSoundAlarm.SoundAlarmInfo[i].volume);
        strcat(szBuf,szTempBuf);
    }

    ui->EditNewAudio->setText(szBuf);
}


bool Form1::NewVer( void )
{
        return m_bNewVer;
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
    return QWidget::eventFilter(obj, event);//don't eat event
}

void Form1::ResetCheckstate()
{
    //query Extern Alarm
    int i = 0;
	int nAlarmCount = m_nInputAlarmCount>32?32:m_nInputAlarmCount;
	int nCount = m_nChannelCount>32?32:m_nChannelCount;
    for(i = 0; i < nAlarmCount; i++)
    {
		QTableWidgetItem * pItem = ui->tableWidget->item(0, i);
		if (pItem !=NULL)
		{
			pItem->setCheckState(Qt::Unchecked);
		}
       // ui->tableWidget->item(0, i)->setCheckState(Qt::Unchecked);
    }
    //Video Loss
    for(i = 0; i < nCount; i++)
    {
		QTableWidgetItem * pItem = ui->tableWidget->item(1, i);
		if (pItem !=NULL)
		{
			pItem->setCheckState(Qt::Unchecked);
		}
       // ui->tableWidget->item(1, i)->setCheckState(Qt::Unchecked);
    }

    //Motion Alarm
    for(i = 0; i < nCount; i++)
    {
		QTableWidgetItem * pItem = ui->tableWidget->item(2, i);
		if (pItem !=NULL)
		{
			pItem->setCheckState(Qt::Unchecked);
		}
        //ui->tableWidget->item(2, i)->setCheckState(Qt::Unchecked);
    }

    if(m_bNewVer == false)
    {
        //old Shelter Alarm
        for(i = 0; i < nAlarmCount; i++)
        {
			QTableWidgetItem * pItem = ui->tableWidget_2->item(0, i);
			if (pItem !=NULL)
			{
				pItem->setCheckState(Qt::Unchecked);
			}
            // ui->tableWidget_2->item(0, i)->setCheckState(Qt::Unchecked);
        }
        // Extern Alarm
        for(i = 0; i < nCount; i++)
        {
			QTableWidgetItem * pItem = ui->tableWidget_2->item(1, i);
			if (pItem !=NULL)
			{
				pItem->setCheckState(Qt::Unchecked);
			}
           // ui->tableWidget_2->item(1, i)->setCheckState(Qt::Unchecked);
        }
        //Video Loss
        for(i = 0; i < nCount; i++)
        {
			QTableWidgetItem * pItem = ui->tableWidget_2->item(2, i);
			if (pItem !=NULL)
			{
				pItem->setCheckState(Qt::Unchecked);
			}
          //  ui->tableWidget_2->item(2, i)->setCheckState(Qt::Unchecked);
        }

        //Motion Alarm
        for(i = 0; i < nCount; i++)
        {
			QTableWidgetItem * pItem = ui->tableWidget_2->item(3, i);
			if (pItem !=NULL)
			{
				pItem->setCheckState(Qt::Unchecked);
			}
           // ui->tableWidget_2->item(3, i)->setCheckState(Qt::Unchecked);
        }
//         //audio
//         for(i = 0; i < nCount; i++)
//         {
// 			QTableWidgetItem * pItem = ui->tableWidget_2->item(4, i);
// 			if (pItem !=NULL)
// 			{
// 				pItem->setCheckState(Qt::Unchecked);
// 			}
//            // ui->tableWidget_2->item(4, i)->setCheckState(Qt::Unchecked);
//         }
    }
    else
    {
        //new Shelter Alarm
        for(i = 0; i < nCount; i++)
        {
			QTableWidgetItem * pItem = ui->tableWidget_3->item(0, i);
			if (pItem !=NULL)
			{
				pItem->setCheckState(Qt::Unchecked);
			}
           // ui->tableWidget_3->item(0, i)->setCheckState(Qt::Unchecked);
        }
        // Extern Alarm
        for(i = 0; i < nAlarmCount; i++)
        {
			QTableWidgetItem * pItem = ui->tableWidget_3->item(1, i);
			if (pItem !=NULL)
			{
				pItem->setCheckState(Qt::Unchecked);
			}
          //  ui->tableWidget_3->item(1, i)->setCheckState(Qt::Unchecked);
        }
        //Video Loss
        for(i = 0; i < nCount; i++)
        {
			QTableWidgetItem * pItem = ui->tableWidget_3->item(2, i);
			if (pItem !=NULL)
			{
				pItem->setCheckState(Qt::Unchecked);
			}
           // ui->tableWidget_3->item(2, i)->setCheckState(Qt::Unchecked);
        }

        //Motion Alarm
        for(i = 0; i < nCount; i++)
        {
			QTableWidgetItem * pItem = ui->tableWidget_3->item(3, i);
			if (pItem !=NULL)
			{
				pItem->setCheckState(Qt::Unchecked);
			}
            //ui->tableWidget_3->item(3, i)->setCheckState(Qt::Unchecked);
        }
//         //Urgency Alarm
//         for(i = 0; i < 16; i++)
//         {
//             ui->tableWidget_3->item(4, i)->setCheckState(Qt::Unchecked);
//         }
// 
//         //Wireless Alarm
//         for(i = 0; i < 16; i++)
//         {
//             ui->tableWidget_3->item(5, i)->setCheckState(Qt::Unchecked);
//         }
//         //Encoder Alarm
//         for(i = 0; i < 16; i++)
//         {
//             ui->tableWidget_3->item(6, i)->setCheckState(Qt::Unchecked);
//         }
// 
//         //Disk_Full
//         for(i = 0; i < 1; i++)
//         {
//             ui->tableWidget_3->item(7, i)->setCheckState(Qt::Unchecked);
//         }
// 
//         //Disk_Error
//         for(i = 0; i < 32; i++)
//         {
//             ui->tableWidget_3->item(8, i)->setCheckState(Qt::Unchecked);
//         }

		//Disk_Full
		for(i = 0; i < 1; i++)
		{
			ui->tableWidget_3->item(4, i)->setCheckState(Qt::Unchecked);
		}

		//Disk_Error
		for(i = 0; i < 32; i++)
		{
			ui->tableWidget_3->item(5, i)->setCheckState(Qt::Unchecked);
		}
    }

}

void Form1::on_ButQueryAlarmState_clicked()
{
    int nRet =0 ;
    int nRetLen =0;


	memset(&m_stNetAlarmState,0,sizeof(m_stNetAlarmState));
	m_stNetAlarmState.dwSize = sizeof(NET_CLIENT_ALARM_STATE);
	nRet = CLIENT_QueryDevState(m_lLoginHandle,DH_DEVSTATE_ALARM,(char*)&m_stNetAlarmState,sizeof(m_stNetAlarmState),&nRetLen);
	if(nRet <= 0 && nRetLen == 0)
	{
		QMessageBox::about(this, tr("Prompt"), tr("Get AlarmState failed!"));
	}

	memset(&m_stNetVideoLostState,0,sizeof(m_stNetVideoLostState));
	m_stNetVideoLostState.dwSize = sizeof(NET_CLIENT_VIDEOLOST_STATE);
	nRet = CLIENT_QueryDevState(m_lLoginHandle,DH_DEVSTATE_VIDEOLOST,(char*)&m_stNetVideoLostState,sizeof(m_stNetVideoLostState),&nRetLen);
	if(nRet <= 0 && nRetLen == 0)
	{
		QMessageBox::about(this, tr("Prompt"), tr("Get VideoLostState failed!"));
	}

	memset(&m_stNetMotionDetectState,0,sizeof(m_stNetMotionDetectState));
	m_stNetMotionDetectState.dwSize = sizeof(NET_CLIENT_MOTIONDETECT_STATE);
	nRet = CLIENT_QueryDevState(m_lLoginHandle,DH_DEVSTATE_MOTIONDETECT,(char*)&m_stNetMotionDetectState,sizeof(m_stNetMotionDetectState),&nRetLen);
	if(nRet <= 0 && nRetLen == 0)
	{
		QMessageBox::about(this, tr("Prompt"), tr("Get MotionDetectState failed!"));
	}

	SetQueryAlarmInfo();

}
