#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <QDialog>
#include <QTimer>
#include "dhnetsdk.h"

class CameraController
{
public:
    CameraController();

private:
    void Login();

    LLONG      m_lLoginHandle;
    QTimer     *m_counter;
    int        m_bMessageTip;
    int        m_nChannelIndex;
    int        m_nCtrlParam;
};

#endif // CAMERACONTROLLER_H
