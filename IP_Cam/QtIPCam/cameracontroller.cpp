#include "cameracontroller.h"
//#include "ui_dialog.h"
#include <QMessageBox>
#include <QtMath>
#include <QDebug>

//#include "Ptz.h"
#include "UserDefine.h"
#include <iostream>
using namespace std;

CameraController::CameraController()
{
    this->InitData();
    this->Login();
}

CameraController::~CameraController()
{
    CLIENT_Cleanup();
}

void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
//    Dialog * pThis = (Dialog *)dwUser;
//    if(NULL == pThis)
//    {
//        return;
//    }

//    QEvent*  eventDisconnect = new QEvent(QEvent::User);
//    QApplication::postEvent((QObject*)pThis, eventDisconnect);
//    return;
}

void CameraController::InitData()
{
    CLIENT_Init(DisConnectFunc, (LDWORD)this);

//    installEventFilter(this);//install filter
//    m_lLoginHandle = 0;
//    ui->lineEdit3->setEchoMode(QLineEdit::Password);
//    m_bMessageTip = FALSE;
//    ui->Login->setEnabled(true);
//    ui->Logout->setEnabled(false);
//    m_counter = new QTimer( this );
//    connect(m_counter, SIGNAL(timeout()), this, SLOT(ShowMessage()));
//    m_counter->start(1000);
//    return true;
}

void CameraController::Login()
{
    QString strIp = "192.168.1.108";
    QString strUserName = "admin";
    //QString xxx = "37777";
    long dvrPort = 37777;
    QString strPassword = "positioning";

    NET_DEVICEINFO deviceInfo = {0};
    int error = 0;

    m_lLoginHandle = CLIENT_Login((char *)strIp.toUtf8().data(), dvrPort, (char*)strUserName.toUtf8().data(),
                                  (char*)strPassword.toUtf8().data(),  &deviceInfo, &error);
    if(m_lLoginHandle == 0)
    {
        if(error != 255)
        {
            //TODO: proper error handling
            //QMessageBox::about(this, tr("Prompt"), tr("Login failed!"));
            qDebug() << "login failed";
        }
        else
        {
            error = CLIENT_GetLastError();
            if(error == NET_ERROR_MAC_VALIDATE_FAILED )
            {
                //TODO: proper error handling
                //QMessageBox::about(this, tr("Prompt"), tr("Login failed! bad mac address"));
            }
            else if(error == NET_ERROR_SENIOR_VALIDATE_FAILED)
            {
                //TODO: proper error handling
                //QMessageBox::about(this, tr("Prompt"), tr("Login failed! senior validate failed"));
            }
        }
    }
    else
    {
        //g_PTZ.SetLoginID(m_lLoginHandle);
        this->SetLoginID(m_lLoginHandle);
        //initalize comboxChannel
        for(int i = 1; i <= deviceInfo.byChanNum; i++)
        {
            m_nChannelIndex = 0;
            //g_PTZ.SetChannel(m_nChannelIndex);
            this->SetChannel(m_nChannelIndex);
            m_nCtrlParam = 1;
        }
    }
}

bool CameraController::SetLoginID(LLONG lLoginID)
{
    if(lLoginID <= 0)
    {
        return false;
    }
    m_lLoginID = lLoginID;
    return true;
}

bool CameraController::SetChannel(int nChannel)
{
    if( nChannel < 0)
    {
        return false;
    }
    m_nChannel = nChannel;
    return true;
}

void CameraController::SetPosition(double x, double y)
{
    if(m_lLoginID <=0 || m_nChannel < 0 )
    {
        return;
    }

    // DH_EXTPTZ_EXACTGOTO means: go to tilt angle x and pan angle y
    // PAN RANGE: 0 - 3600
    // TILT RANGE: 0 - 900
    int nType = DH_EXTPTZ_EXACTGOTO;
    int panAngle = qFloor(qRadiansToDegrees(qAtan2(y, x))*10);
    int tiltAngle = 0;
    int zoom = 1;

    int nParam1 = panAngle;
    int nParam2 = tiltAngle;
    int nParam3 = zoom;
    bool bStop = false;
    CLIENT_DHPTZControlEx(m_lLoginID, m_nChannel, nType, nParam1, nParam2, nParam3, bStop);
}
