#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QByteArray>


#include <iostream>
using namespace std;

#ifdef WIN32
#include <windows.h>
typedef DWORD (WINAPI *LPTHREAD_START_ROUTINE)(LPVOID lpThreadParameter);
#endif
void * RoutineLoginThread(LPVOID lpPara);

DEVICE_LIST 	g_DeviceList;

DHMutex        	g_csDevice;
bool	        g_bExit = false;


void ChangeLoginError(int nErrorCode , QString &strErrorCode)
{
	switch(nErrorCode) 
	{
	case 0: 
		strErrorCode = "Login Success";
		break;

	case 1: 
		strErrorCode = "Login Password Error";
		break;

	case 2: 
		strErrorCode = "User Is Not Exist";
		break;

	case 3: 
		strErrorCode = "Login Timeout";
		break;

	case 4: 
		strErrorCode = "Repeat Login";
		break;

	case 5:
		strErrorCode = "User Account is Locked";
		break;

	case 6:
		strErrorCode = "User In Blacklist";
		break;

	case 7:
		strErrorCode = "Device Busy";
		break;

	case 8: 
		strErrorCode = "Sub Connect Failed";
		break;

	case 9:
		strErrorCode = "Host Connect Failed";
		break;
	
	case 10 :
		strErrorCode = "Max Connect";
		break;

	case 11:
		strErrorCode = "Support Protocol3 Only";
		break;

	case 12:
		strErrorCode = "UKey Info Error";
		break;

	case 13:
		strErrorCode = "No Authorized";
		break;

	default:
		break;
	}

}

void InitDecviceInfo(DH_Device_Info &stDeviceInfo)
{
	stDeviceInfo.lLoginHandle = 0UL;
	stDeviceInfo.nChannelCount = 0;
	stDeviceInfo.bOnline = FALSE;
	stDeviceInfo.strErrorCode = "";
	stDeviceInfo.nPort = 0;
	stDeviceInfo.nBelongThread = 0;
	stDeviceInfo.nIndex = 0;
	stDeviceInfo.nTimeCount = 0L;
	memset(&stDeviceInfo.szDevIp , 0 , 32);
	memset(&stDeviceInfo.szUserName , 0 , 32);
	memset(&stDeviceInfo.szPassWord , 0 , 32);
	memset(&stDeviceInfo.channel , 0 , sizeof(stDeviceInfo.channel));
}

void CALLBACK RealDataCallBack(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser)
{
    DH_Channel_Info* pChannelInfo = (DH_Channel_Info*)dwUser;
    if(NULL == pChannelInfo)
    {
        return;
    }

    pChannelInfo->dwStatistic = dwBufSize;
}

void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
    MainWindow * pThis = (MainWindow *)dwUser;
    if(NULL == pThis)
    {
        return;
    }

    g_csDevice.Lock();

    DEVICE_LIST::iterator it = g_DeviceList.begin();
    while (it != g_DeviceList.end())
    {
        DH_Device_Info *pDeviceInfo = (*it);
        if (pDeviceInfo != NULL)
        {
            if (pDeviceInfo->lLoginHandle == lLoginID)
            {
                pDeviceInfo->bOnline = FALSE;
				pDeviceInfo->strErrorCode = "Device Disconnected";
                int nMinCount = pDeviceInfo->nChannelCount > 16?16:pDeviceInfo->nChannelCount;
                for(int i = 0; i < nMinCount; i++)
                {
                    pDeviceInfo->channel[i].dwStatistic = 0;
                }
                break;
            }
        }

        it++;
    }
    g_csDevice.UnLock();

    return;
}

/**************************************************************************************
*   Funcname: HaveReConnectFunc
*   Purpose:断线重连函数，CLIENT_SetAutoReconnect函数调用
*   OutputParam:         LLONG              :lLoginID        // 登录ID
*   OutputParam:         char*              :pchDVRIP        // 登陆设备IP
*   OutputParam:         LONG               :nDVRPort        // 登陆设备端口
*   OutputParam:         LDWORD   		    :dwUser           // 用户自定义字段
*   Return:              void
*   Created:	        %2016%:%05%:%16%  
*   Revision Record:    date:author:modify sth
**************************************************************************************/
void CALLBACK  HaveReConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	if( pchDVRIP == NULL)
		return ;
    g_csDevice.Lock();
	NET_DEVICEINFO deviceInfo = {0};
    DEVICE_LIST::iterator it = g_DeviceList.begin();
    while (it != g_DeviceList.end())
    {
        DH_Device_Info *pDeviceInfo = (*it);
        if (pDeviceInfo == NULL)
        {
            it++;
            continue;
        }
        if ((0 == strcmp(pDeviceInfo->szDevIp,pchDVRIP)) && ( pDeviceInfo->nPort == nDVRPort))
        {
            if (lLoginID != 0)
            {
                 pDeviceInfo->lLoginHandle = lLoginID;
                 pDeviceInfo->bOnline = TRUE;
                 pDeviceInfo->strErrorCode = "Login Success";
                 break;
            }
        }
        it++;
    }
    g_csDevice.UnLock();
    return;
}
void * RoutineLoginThread(LPVOID lpPara)
{
    //  return 0;
    long nThreadID = (long)lpPara;
    if(nThreadID < 0)
    {
        return 0;
    }
    g_csDevice.Lock();

    NET_DEVICEINFO deviceInfo = {0};
    DEVICE_LIST::iterator it = g_DeviceList.begin();
    while (it != g_DeviceList.end())
    {
        if(g_bExit == true)
        {
            break;
        }

        DH_Device_Info *pDeviceInfo = (*it);

        if (pDeviceInfo == NULL)
        {
            it++;
            continue;
        }

        if (pDeviceInfo->nBelongThread == nThreadID)
        {
            int error = 0;

            pDeviceInfo->lLoginHandle = CLIENT_Login(pDeviceInfo->szDevIp, pDeviceInfo->nPort,pDeviceInfo->szUserName, pDeviceInfo->szPassWord,&deviceInfo, &error);
            ChangeLoginError(error , pDeviceInfo->strErrorCode);
            if (pDeviceInfo->lLoginHandle == 0)
            {
                if(error != 255)
                {
                  printf("Login failed! error = %d", error);
                }
                else
                {
                    error = CLIENT_GetLastError();
                    if(error ==NET_ERROR_MAC_VALIDATE_FAILED )
                    {
                        printf("Login failed! bad mac address");
                    }
                    else if(error ==NET_ERROR_SENIOR_VALIDATE_FAILED)
                    {
                        printf("Login failed! senior validate failed");
                    }
                }

                pDeviceInfo->bOnline = FALSE;
                it++;
                continue;
            }
            else
            {
                int nRetLen = 0;
                NET_DEV_CHN_COUNT_INFO stuChn = {sizeof(NET_DEV_CHN_COUNT_INFO)};
                stuChn.stuVideoIn.dwSize = sizeof(stuChn.stuVideoIn);
                stuChn.stuVideoOut.dwSize = sizeof(stuChn.stuVideoOut);
                if(CLIENT_QueryDevState(pDeviceInfo->lLoginHandle, DH_DEVSTATE_DEV_CHN_COUNT, (char*)&stuChn, stuChn.dwSize, &nRetLen))
                {
                    pDeviceInfo->nChannelCount = stuChn.stuVideoIn.nMaxTotal;
                }
                else
                {
                    pDeviceInfo->nChannelCount = deviceInfo.byChanNum;
                }
            }

            pDeviceInfo->bOnline = TRUE;
//           pDeviceInfo->nChannelCount = deviceInfo.byChanNum;
            int nLoopCount = pDeviceInfo->nChannelCount;
            if(nLoopCount > 16)
            {
                nLoopCount = 16;
            }
            for (int i = 0; i < nLoopCount; i++)
            {

                pDeviceInfo->channel[i].lRealPlayHandle = CLIENT_RealPlay(pDeviceInfo->lLoginHandle,i, NULL);
                if (pDeviceInfo->channel[i].lRealPlayHandle != 0)
                {
                CLIENT_SetRealDataCallBack(pDeviceInfo->channel[i].lRealPlayHandle, RealDataCallBack, (LDWORD)&(pDeviceInfo->channel[i]));
                }
                else
                {

                    printf("loginid = %d;real play failed!\n", pDeviceInfo->lLoginHandle);
                }
            }
        }

        it++;
    }
         g_csDevice.UnLock();
}

void MainWindow::addRowData(QAbstractItemModel *model, QStringList rowDataList)
{
    int row = model->rowCount();
    model->insertRow(row);
    int nCount = rowDataList.size ();
    int nIndex = 0;
    for( nIndex= 0; nIndex < nCount; nIndex++)
    {   
        QString string = static_cast<QString>(rowDataList.at (nIndex));
        model->setData(model->index(row, nIndex), string);
    }

}


QStandardItemModel *MainWindow::createListModel()
{
    QStandardItemModel *model = new QStandardItemModel(0, 21, this);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NO"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IP"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("On Line"));
	model->setHeaderData(3 ,Qt::Horizontal, QObject::tr("Device Status"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Channel count"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("1"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("2"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("3"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("4"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("5"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("6"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("7"));
    model->setHeaderData(12, Qt::Horizontal, QObject::tr("8"));
    model->setHeaderData(13, Qt::Horizontal, QObject::tr("9"));
    model->setHeaderData(14, Qt::Horizontal, QObject::tr("10"));
    model->setHeaderData(15, Qt::Horizontal, QObject::tr("11"));
    model->setHeaderData(16, Qt::Horizontal, QObject::tr("12"));
    model->setHeaderData(17, Qt::Horizontal, QObject::tr("13"));
    model->setHeaderData(18, Qt::Horizontal, QObject::tr("14"));
    model->setHeaderData(19, Qt::Horizontal, QObject::tr("15"));
    model->setHeaderData(20, Qt::Horizontal, QObject::tr("16"));
    return model;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //创建ListView
    standardItemModel = createListModel();
    ui->listView1->setModel(standardItemModel);

    ui->listView1->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->listView1->setEditTriggers(QAbstractItemView::EditKeyPressed/*NoEditTriggers*/);
    ui->listView1->setColumnWidth (0,60);
    ui->listView1->verticalHeader()->setVisible(false);
    ui->listView1->verticalHeader()->setDefaultSectionSize(20);
    ui->listView1->horizontalHeader()->setStretchLastSection(true);
    ui->listView1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->listView1->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // 数据初始化
    InitData();


}

MainWindow::~MainWindow()
{
    UnInitData();
    delete ui;
}

bool MainWindow::InitData()
{
    CLIENT_Init(DisConnectFunc, (LDWORD)this);
    CLIENT_SetAutoReconnect(HaveReConnectFunc, 0);
    installEventFilter(this);//install filter
    m_lLoginHandle = 0;
    ui->pushButStopALL->setEnabled(false);
    m_counter = NULL;
    m_counter = new QTimer( this );
    connect(m_counter, SIGNAL(timeout()), this, SLOT(UpdataListview()));
    return true;
}
bool MainWindow::UnInitData()
{
    CLIENT_Cleanup();
    if(m_counter)
       delete m_counter;
    if(standardItemModel)
        delete standardItemModel;
    return true;
}

void MainWindow::UpdataListview()
{
    QList<QStandardItem *> itemsfind;
    QStandardItem * item = NULL;
    QString name = "";
    QString strdata = "";

    g_csDevice.Lock();
    DEVICE_LIST::iterator it = g_DeviceList.begin();
    while (it != g_DeviceList.end())
    {
        DH_Device_Info *pDeviceInfo = (*it);
        if (pDeviceInfo == NULL)
        {
            it++;
            continue;
        }

        name = QString::number(pDeviceInfo->nIndex, 10);

        itemsfind = standardItemModel->findItems(name);
        if (itemsfind.size () == 0)
        {
            QStringList strList;
            strdata = QString::number(pDeviceInfo->nIndex, 10);
            strList.append(strdata);

            strdata = pDeviceInfo->szDevIp;
            strList.append(strdata);

            strdata  = QString::number(pDeviceInfo->bOnline , 10);
            strList.append(strdata);

			strList.append(pDeviceInfo->strErrorCode);

            strdata  = QString::number(pDeviceInfo->nChannelCount , 10);
            strList.append(strdata);

            addRowData(standardItemModel, strList);
        }
        else
        {
            int nIndex = 0;
            for(nIndex = 0; nIndex < itemsfind.size (); nIndex++)
            {
                item = static_cast<QStandardItem *>(itemsfind.at(nIndex));
                QModelIndex curIndex = standardItemModel->indexFromItem(item);
                int rowIndex = curIndex.row ();
                int colIndex = curIndex.column ();
                colIndex++; //IP不变
                strdata  = QString::number(pDeviceInfo->bOnline , 10) ;
                colIndex++;
                standardItemModel->setData(standardItemModel->index(rowIndex, colIndex), strdata);
				colIndex++;
				standardItemModel->setData(standardItemModel->index(rowIndex, colIndex), pDeviceInfo->strErrorCode);
                strdata  = QString::number(pDeviceInfo->nChannelCount , 10);
                colIndex++;
                standardItemModel->setData(standardItemModel->index(rowIndex, colIndex), strdata);

                pDeviceInfo->nTimeCount += 1;
                int nMinCount = pDeviceInfo->nChannelCount > 16 ? 16:pDeviceInfo->nChannelCount;
                for(int i = 0; i < nMinCount; i++)
                {
                    strdata = tr("0");
                    if(pDeviceInfo->bOnline > 0)//online
                    {
                        strdata = QString::number(pDeviceInfo->channel[i].dwStatistic, 10);
                    }
                    colIndex++;
                    standardItemModel->setData(standardItemModel->index(rowIndex, colIndex), strdata);
                }
            }
        }

        it++;
    }
        g_csDevice.UnLock();
}

int MainWindow::LoadConfig(int * nThreadNum)
{
	char szSection[128];
	char ip[64];
	char port[8];
	char username[16];
	char password[16];
	char connect_num[8];
	char thread_num[8] ={0};
	QFileDialog * fDialog = new QFileDialog(this);
	if(fDialog == NULL)
	{
		return 0;
	}
	g_csDevice.Lock();
	DEVICE_LIST::iterator it = g_DeviceList.begin();
	while (it != g_DeviceList.end())
	{
		DH_Device_Info *pDeviceInfo = (*it);
		if (pDeviceInfo != NULL)
		{
			delete  pDeviceInfo;
			pDeviceInfo = NULL;
		}
		it++;
	}
	g_DeviceList.clear();
	g_csDevice.UnLock ();
#if defined(WIN32) || defined(WIN64)
	m_FileName = fDialog->getOpenFileName(this,
		"open file dialog",
		"D:\SVNcode\QtProj\RealPlay",
		"config (*.ini *.txt )" );
#else
	m_FileName = fDialog->getOpenFileName(this,
		"open file dialog",
		"./",
		"config (*.ini *.txt )");
#endif
	if(fDialog)
	{
		delete fDialog;
	}
	if(m_FileName.isNull() == TRUE)
	{
		return 0;
	}

	QByteArray byt = m_FileName.toUtf8();
	char *p = byt.data();
	CProfile::GetPrivateProfileString("thread", "threadnum", "", thread_num, 8, p);

	*nThreadNum = atoi(thread_num);

	int nIndexCount = 0;

	for(int i = 0; i < *nThreadNum; i++)
	{
		for(int j = 0; ; j++)
		{
			sprintf(szSection, "thread%d.device%d", i, j);
			QByteArray byt = m_FileName.toUtf8();
			char *p = byt.data();
			int nSize = CProfile::GetPrivateProfileString(szSection, "IP", "", ip, 64, p);
			if(strcmp(ip, "") == 0)
			{
				break;
			}
			nSize = CProfile::GetPrivateProfileString(szSection, "Port", "", port, 8, p);
			nSize = CProfile::GetPrivateProfileString(szSection, "Username", "", username, 16, p);

			nSize = CProfile::GetPrivateProfileString(szSection, "Password", "", password, 16, p);

			nSize = CProfile::GetPrivateProfileString(szSection, "ConnectNum", "", connect_num, 8, p);
			int nConnectCount = atoi(connect_num);

			for(int k = 0; k < nConnectCount; k++)
			{
				DH_Device_Info* device_info = new DH_Device_Info;
				if(NULL == device_info)
				{
					continue;
				}
			
				InitDecviceInfo(*device_info);
				strcpy(device_info->szDevIp, ip);
				device_info->nPort = atoi(port);
				strcpy(device_info->szUserName, username);
				strcpy(device_info->szPassWord, password);

				device_info->nBelongThread = i;
				device_info->nIndex = nIndexCount;
				device_info->nTimeCount = 0;
				g_csDevice.Lock();
				g_DeviceList.push_back(device_info);
				g_csDevice.UnLock ();
				nIndexCount++;
			}
		}
	}

	return 1;
}

void MainWindow::Logindev(int nThreadNum)
{
    if(nThreadNum < 0)
    {
        return;
    }
#if defined(WIN32) || defined(WIN64)
    for(int i = 0; i< nThreadNum; i++)
    {
                DWORD dwThreadID = 0;
                m_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RoutineLoginThread, (void*)i, NULL, &dwThreadID);
                if (m_thread != 0)
                {

                }
    }
#else
    for(int i = 0; i< nThreadNum; i++)
    {

                int ret = pthread_create(&m_thread, 0, RoutineLoginThread, (void*)i);
                if (ret != 0)
                {
                    m_thread = 0;
                }
    }
#endif

}

void MainWindow::on_pushButLoad_clicked()
{
        standardItemModel->removeRows(0, standardItemModel->rowCount ());//all item delete

        int nThreadNum = 0;
        int nRet = LoadConfig(&nThreadNum);

        if(1 == nRet)
        {
            Logindev(nThreadNum);

            m_counter ->start(1000);

            ui->pushButLoad->setEnabled(false);
            ui->pushButStopALL->setEnabled(true);
        }
}

void MainWindow::on_pushButPlay_clicked()
{
       QModelIndex  curIndex = ui->listView1->currentIndex ();
       int nRow = curIndex.row ();
       QModelIndex rowNOIndex = standardItemModel->index (nRow, 0);
        QString strItemData = standardItemModel->data (rowNOIndex).toString ();
        bool numok = false;
        int nItem =  strItemData.toLong(&numok);
        if(numok)
        {
            g_csDevice.Lock();
            DEVICE_LIST::iterator it;
            for(it = g_DeviceList.begin(); it != g_DeviceList.end(); it++)
            {
                DH_Device_Info* pDeviceInfo = *it;
                if(pDeviceInfo->nIndex == nItem && pDeviceInfo->lLoginHandle != 0 && pDeviceInfo->bOnline)
                {
                    int nLoopCount = pDeviceInfo->nChannelCount>16?16:pDeviceInfo->nChannelCount;
                    for(int i = 0; i < nLoopCount; i++)
                    {
                                            if(pDeviceInfo->channel[i].lRealPlayHandle == 0)
                                            {
                                                    pDeviceInfo->channel[i].lRealPlayHandle = CLIENT_RealPlay(pDeviceInfo->lLoginHandle,i, NULL);
                                                    if (pDeviceInfo->channel[i].lRealPlayHandle != 0)
                                                    {
                                                       CLIENT_SetRealDataCallBack(pDeviceInfo->channel[i].lRealPlayHandle, RealDataCallBack, (LDWORD)&(pDeviceInfo->channel[i]));
                                                       pDeviceInfo->nTimeCount = 0;
                                                    }
                                            }
                   }
                }
            }
            g_csDevice.UnLock();
       }
}

void MainWindow::on_pushButStopALL_clicked()
{
      //kill the timer
       m_counter->stop();

       g_bExit = true;

       g_csDevice.Lock();

       DEVICE_LIST::iterator it;
       for(it = g_DeviceList.begin(); it != g_DeviceList.end(); it++)
       {
           DH_Device_Info* pDeviceInfo = *it;
           if(pDeviceInfo->lLoginHandle != 0)
           {
                   int nCount = pDeviceInfo->nChannelCount;
                   if(nCount > 16)
                   {
                       nCount = 16;
                   }
               for(int i = 0; i < nCount; i++)
               {
                   CLIENT_StopRealPlay(pDeviceInfo->channel[i].lRealPlayHandle);

               }

               CLIENT_Logout(pDeviceInfo->lLoginHandle);

           }

           delete pDeviceInfo;
           pDeviceInfo = NULL;
       }
       g_DeviceList.clear();
       g_csDevice.UnLock();
       int nRows = standardItemModel->rowCount ();
       standardItemModel->removeRows (0,nRows);
       g_bExit = false;
       ui->pushButLoad->setEnabled(true);

}

void MainWindow::on_pushButStop_clicked()
{
      QModelIndex  curIndex = ui->listView1->currentIndex ();
      int nRow = curIndex.row ();
      QModelIndex rowNOIndex = standardItemModel->index (nRow, 0);
      QString strItemData = standardItemModel->data (rowNOIndex).toString ();
       bool numok = false;
       int nItem = strItemData.toLong(&numok);
       if(numok)
       {
           g_csDevice.Lock();
           DEVICE_LIST::iterator it;
           for(it = g_DeviceList.begin(); it != g_DeviceList.end(); it++)
           {
               DH_Device_Info* pDeviceInfo = *it;
               if(pDeviceInfo->nIndex == nItem && pDeviceInfo->lLoginHandle != 0)
               {
                   int nCount = pDeviceInfo->nChannelCount;
                   if(nCount > 16)
                   {
                       nCount = 16;
                   }
                   for(int i = 0; i < nCount; i++)
                   {
                                           if(pDeviceInfo->channel[i].lRealPlayHandle != 0)
                                           {
                                                   CLIENT_StopRealPlay(pDeviceInfo->channel[i].lRealPlayHandle);
                                                   pDeviceInfo->channel[i].lRealPlayHandle = 0;
                                                   pDeviceInfo->channel[i].dwStatistic = 0;
                                           }
                                           pDeviceInfo->nTimeCount = 0;
                   }
                                   //  CLIENT_Logout(pDeviceInfo->lLoginHandle);
               }
           }

           g_csDevice.UnLock();
       }

}

