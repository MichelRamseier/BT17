#include "cameracontroller.h"
#include <QMessageBox>
#include <QtMath>
#include <QDebug>
#include "UserDefine.h"
#include <iostream>
#include <qfile.h>
#include <qdir.h>
#include <camera.h>
using namespace std;

CameraController::CameraController()
{
    //evtl. mit id des tag
    camConfigs = this->GetCamConfigs();
    this->InitData();
    //cameras = new QList<Camera>();
    foreach (QStringList camConfig, camConfigs)
    {
        QString ip = camConfig[0];
        long port = camConfig[1].toLong();
        QString username = camConfig[2];
        QString pw = camConfig[3];
        int posx = camConfig[4].toInt();
        int posy = camConfig[5].toInt();

        //Camera *cam = new Camera(ip, port, username, pw);
        //this->cameras->append(*cam);

        this->Login(ip, port, username, pw);
        this->SetPosition(posx, posy);
    }
}

CameraController::~CameraController()
{
    CLIENT_Cleanup();
}

void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
    //TODO: handle this stuff
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

void CameraController::Login(QString ip, long port, QString username, QString pw)
{
    QString strIp = "192.168.2.108";
    QString strUserName = "admin";
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
    cameraPositionX = x;
    cameraPositionY = y;
}

//kamera id; QPair
void CameraController::DriveCameraToPosition(QList<QList<double>> points, QList<QString> cameras)
{
    double sumOfX = 0;
    double sumOfY = 0;
    foreach (QList<double> point, points)
    {
        sumOfX += point[0];
        sumOfY += point[1];
    }

    double x = sumOfX / points.length();
    double y = sumOfY / points.length();

    if(m_lLoginID <=0 || m_nChannel < 0 )
    {
        return;
    }

    // kamera id
    // drehung
    // zoom einstellen?
    // threading, QThread, Objekt in Thread verschieben
    // mehrere Kameras
    // aufzeichnung starten (directory vorgegeben, file zurückliefern)
    // aufzeichung stoppen
    // set camera position funktion ergänzen (x, y, z)

    //http://192.168.1.108/axis-cgi/mjpg/video.cgi?subtype=1

    double diffCamPointX = x - cameraPositionX;
    double diffCamPointY = y - cameraPositionY;

    double panAngle;
    if(diffCamPointX >= 0 && diffCamPointY >= 0)
    {
        panAngle = qRadiansToDegrees(qAtan2(y, x));
    }
    else if(diffCamPointX >= 0 && diffCamPointY < 0)
    {
        panAngle = 360 - qRadiansToDegrees(qAtan2(y, x));
    }
    else if(diffCamPointX < 0 && diffCamPointY >= 0)
    {
        panAngle = qRadiansToDegrees(qAtan2(y, x)) + 180;
    }
    else if(diffCamPointX < 0 && diffCamPointY < 0)
    {
        panAngle = qRadiansToDegrees(qAtan2(y, x)) + 180;
    }

    // PAN RANGE: 0 - 3600
    // TILT RANGE: 0 - 900
    // ZOOM RANGE: 1 - 128
    // Adjust the angle because the pan range goes to 3600 instead of 360
    int adjustedPanAngle = qFloor(panAngle*10);
    int tiltAngle = 0;
    int zoom = 1;

    // DH_EXTPTZ_EXACTGOTO means: go to tilt angle x and pan angle y
    int nType = DH_EXTPTZ_EXACTGOTO;
    int nParam1 = adjustedPanAngle;
    int nParam2 = tiltAngle;
    int nParam3 = zoom;
    bool bStop = false;

    CLIENT_DHPTZControlEx(m_lLoginID, m_nChannel, DH_EXTPTZ_MOVE_CONTINUOUSLY, 0, 0, 0, bStop);
    CLIENT_DHPTZControlEx(m_lLoginID, m_nChannel, nType, nParam1, nParam2, nParam3, bStop);
    CLIENT_DHPTZControlEx(m_lLoginID, m_nChannel, nType, 1000, 0, 1, bStop);

    CLIENT_DHPTZControlEx(m_lLoginID, m_nChannel, nType, 0, 0, 1, bStop);
    CLIENT_DHPTZControlEx(m_lLoginID, m_nChannel, nType, 1000, 0, 1, bStop);
    CLIENT_DHPTZControlEx(m_lLoginID, m_nChannel, nType, 0, 0, 1, bStop);
    CLIENT_DHPTZControlEx(m_lLoginID, m_nChannel, nType, 1000, 0, 1, bStop);
    CLIENT_DHPTZControlEx(m_lLoginID, m_nChannel, nType, 0, 0, 1, bStop);
    CLIENT_DHPTZControlEx(m_lLoginID, m_nChannel, nType, 1000, 0, 1, bStop);
    CLIENT_DHPTZControlEx(m_lLoginID, m_nChannel, nType, 0, 0, 1, bStop);


    qDebug() << "test";
}


QList<QStringList> CameraController::GetCamConfigs()
{
    QFile file("../QtIPCam/Config/CamConfig");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString() + "Current Path: " + QDir::currentPath());
    }

    QTextStream in(&file);

    QList<QStringList> camConfigs = QList<QStringList>();

    bool firstLine = true;
    while(!in.atEnd())
    {
        QString line = in.readLine();
        if(!firstLine)
        {
            QStringList cam = line.split(",");
            camConfigs.append(cam);
        }
        else
        {
            firstLine = false;
        }
    }

    file.close();

    return camConfigs;
}
