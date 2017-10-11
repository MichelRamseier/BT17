#include "cameracontroller.h"
#include "ui_dialog.h"
#include <QMessageBox>

#include "Ptz.h"
#include "UserDefine.h"
#include <iostream>
using namespace std;
CPtz g_PTZ;

CameraController::CameraController()
{
    this->Login();
}

void CameraController::Login()
{
    QString strIp = "192.168.1.108";
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
        g_PTZ.SetLoginID(m_lLoginHandle);

        //initalize comboxChannel
        for(int i = 1; i <= deviceInfo.byChanNum; i++)
        {
            m_nChannelIndex = 0;
            g_PTZ.SetChannel(m_nChannelIndex);
            m_nCtrlParam = 1;
        }
    }
}
