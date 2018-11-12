#ifndef FORM1_H
#define FORM1_H

#include <QDialog>
#include <qtimer.h>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qtimer.h>
#include <qlistview.h>
#include <string>
#include <qfiledialog.h>
#include <qdatetimeedit.h>
#include <qdatetime.h>
#include<iostream>
using namespace std;
#include <stdlib.h>
//#include <sys/times.h>
//#include <unistd.h>
#include <time.h>

#include"dhnetsdk.h"

namespace Ui {
    class Form1;
}

class Form1 : public QDialog
{
    Q_OBJECT

public:
    explicit Form1(QWidget *parent = 0);
    ~Form1();

    void InitForm();
    void InitData();
    void destroyForm();
    int ReceiveRealData(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, LDWORD dwBufSize);
    void ReceivePlayPos(LLONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize);
    void TimeDownLoadCallBack(LLONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, int index, NET_RECORDFILE_INFO recordfileinfo);
private:
    Ui::Form1 *ui;
    QTimer* m_counter;

    LLONG m_lLoginHandle;
    LLONG m_hPlayBack;
    LLONG m_lDownLoadFile;
    LLONG m_lDownLoadByTime;
    DWORD m_dwFileTotalSize;
    DWORD m_dwFileCurValue;
    int   m_nListViewCurIndex;
    DWORD m_dwTimeTotalSize;
    DWORD m_dwTimeCurValue;
    QString m_FileName;
    BOOL m_bExit;
    BOOL m_bRecData;
    int m_nOperateType;
    int m_nPlaybackBufSize;
    int m_OperateType;
    NET_RECORDFILE_INFO m_netFileInfo[2000];


    void ConvertTime( QDate date, QTime time, NET_TIME * nettime);
    void AddRecordInfoToListView(LPNET_RECORDFILE_INFO pRecordFiles, int nFileCount);
    void ConvertTimeToStr(NET_TIME nettime, QDate *date, QTime *time);
    void PlayBackByFileServerMode(NET_RECORDFILE_INFO fileInfo);
    BOOL DownLoadByFile(NET_RECORDFILE_INFO fileInfo,BOOL bLoad);
    bool eventFilter(QObject *obj, QEvent *event);
    int CompareTime(NET_TIME *pSrcTime, NET_TIME *pDestTime);

private slots:
    void on_Form1_destroyed();
    void on_ButStopLoadByTime_clicked();
    void on_ButLoadByTime_clicked();
    void on_ButStopPlayByTime_clicked();
    void on_ButPlayByTime_clicked();
    void on_ButDownLoad_clicked();
    void on_ButPlayByRecord_clicked();
    void on_ButSearch_clicked();
    void on_Logout_clicked();
    void on_Login_clicked();
    void UpdataProgressbar();
};

#endif // FORM1_H
