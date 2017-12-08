#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <QDialog>
#include <QTimer>
#include <QVector3D>
#include <QObject>
#include "dhnetsdk.h"

class CameraController : public QObject
{
    Q_OBJECT
public:
    CameraController();
    ~CameraController();
    void SetPosition(double x, double y);

public slots:
    void playerLocationChanged(quint64, QVector3D);

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
