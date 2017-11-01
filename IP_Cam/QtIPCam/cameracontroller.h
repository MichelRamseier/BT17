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
    void SetPosition(double x, double y);

private:
    void Login();
    bool SetLoginID(LLONG lLoginID);
    bool SetChannel(int nChannel);
    void InitData();

    LLONG      m_lLoginHandle;
    QTimer     *m_counter;
    int        m_bMessageTip;
    int        m_nChannelIndex;
    int        m_nCtrlParam;

protected:
    LLONG   m_lLoginID;
    int     m_nChannel;
};

#endif // CAMERACONTROLLER_H
