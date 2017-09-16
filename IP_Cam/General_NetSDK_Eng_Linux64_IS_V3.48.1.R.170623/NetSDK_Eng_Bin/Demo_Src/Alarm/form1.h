#ifndef FORM1_H
#define FORM1_H

#include <QDialog>
#include <qdatetime.h>
#include "dhnetsdk.h"
#include "AlarmInfo.h"
#include "include/dhmutex.h"

namespace Ui {
    class Form1;
}

class Form1 : public QDialog
{
    Q_OBJECT

public:
    explicit Form1(QWidget *parent = 0);
    ~Form1();

    virtual BOOL ReceiveMessage( LLONG lLoginID, LONG lCommand, char * pchDVRIP, LONG nDVRPort, char * pBuf, DWORD dwBufLen );
    virtual BOOL ReceiveMessageEx( LLONG lLoginID, LONG lCommand, char * pchDVRIP, LONG nDVRPort, char * pBuf, DWORD dwBufLen );
    void ConvertTime( QDate date, QTime time, NET_TIME * nettime );
    virtual bool eventFilter( QObject * obj, QEvent * event );
    virtual bool NewVer( void );
    void InitBox(int nChannelCount, int nAlarmCount, int nType);
    void UnInitBox(int nChannelCount, int nAlarmCount, int nType);
    virtual void InitForm();

private:
    Ui::Form1 *ui;
    int m_nChannelCount;
    int m_nInputAlarmCount;
	NET_CLIENT_ALARM_STATE  m_stNetAlarmState;
	NET_CLIENT_VIDEOLOST_STATE m_stNetVideoLostState;
	NET_CLIENT_MOTIONDETECT_STATE m_stNetMotionDetectState;
    CAlarmInfo m_curAlarmInfo;
    BOOL m_bIsListen;
    bool m_bNewVer;
    QTimer *m_counter;
    LLONG m_lLoginHandle;

private slots:
    void on_ButQueryAlarmState_clicked();
    void on_Logout_clicked();
    void on_Login_clicked();
    virtual void destroyForm();
    virtual void InitData();
    virtual void DHCommAlarm( char * pBuf, DWORD dwBufLen );
    virtual void DHShelterAlarm( char * pBuf, DWORD dwBufLen );
    virtual void DHDiskFullAlarm( char * pBuf, DWORD dwBufLen );
    virtual void DHDiskError( char * pBuf, DWORD dwBufLen );
    virtual void DHSoundAlarm( char * pBuf, DWORD dwBufLen );
    virtual void ConvertTimeToStr( NET_TIME nettime, QDate * date, QTime * time );
    virtual void ButExit_clicked();
    virtual void ButQueryAlarmState_clicked();
    virtual void SetQueryAlarmInfo();
    virtual void UpdateAlarmInfo();
    virtual void SetCommonAlarmInfo( WORD wInputAlarm, WORD wVideoLost, WORD wMotionAlarm, int nChannelCount, int nInputAlarmCount );
    virtual void SetShelterAlarmInfo( WORD wVideoShelter );
    virtual void SetSoundAlarmInfo( WORD wSoundAlarm );
    virtual void SetDiskFullAlarmInfo( BOOL bDiskFull );
    virtual void SetDiskErrorAlarmInfo( DWORD dwDiskError );
    virtual void SetAlarmInfo( BYTE * dwAlarm, DWORD dwID );
    virtual void SetSoundAlarmInfo( DH_NEW_SOUND_ALARM_STATE & stuSoundAlarm );
    virtual void ResetCheckstate();
};

#endif // FORM1_H
