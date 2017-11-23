#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <QDialog>
#include <QTimer>
#include "dhnetsdk.h"

class CameraController
{
public:
    CameraController();
    ~CameraController();
    void DriveCameraToPosition(double x, double y);
    void SetPosition(double x, double y);

private:
    void Login(QString ip, long port, QString username, QString pw);
    bool SetLoginID(LLONG lLoginID);
    bool SetChannel(int nChannel);
    void InitData();
    QList<QStringList> GetCamConfigs();

    LLONG               m_lLoginHandle;
    QTimer              *m_counter;
    int                 m_bMessageTip;
    int                 m_nChannelIndex;
    int                 m_nCtrlParam;
    double              cameraPositionX;
    double              cameraPositionY;
    QList<QStringList>  camConfigs;

protected:
    LLONG   m_lLoginID;
    int     m_nChannel;
};

#endif // CAMERACONTROLLER_H
