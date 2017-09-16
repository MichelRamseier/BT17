#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include <QDate>
#include <QTime>

namespace Ui {
    class Dialog;
}

#include "dhnetsdk.h"

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
public:
    void GetDiskInformation();
    void ConvertTime( QDate date, QTime time, NET_TIME * nettime);
    void ConvertTimeToStr(NET_TIME nettime, QDate *date, QTime *time);
    void OperateKeyboard( CtrlType nType);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
protected:
    bool InitData();
    bool UnInitData();

private:
    LLONG m_lLoginHandle;
    QTimer *m_counter;
    DH_HARDDISK_STATE m_DiskInfo;
    int m_nCurDiskType;
private:
    Ui::Dialog *ui;

private slots:
    void on_ButBoot_2_clicked();
    void on_ButAddr_clicked();
    void on_ButInfo_clicked();
    void on_ButSplit_clicked();
    void on_ButOne_clicked();
    void on_ButNine_clicked();
    void on_ButDown_clicked();
    void on_ButRight_clicked();
    void on_ButEnter_clicked();
    void on_ButLeft_clicked();
    void on_ButUP_clicked();
    void on_ButFn2_clicked();
    void on_ButJmpDown_clicked();
    void on_ButJmpUp_clicked();
    void on_ButStop_clicked();
    void on_ButNext_clicked();
    void on_ButFast_clicked();
    void on_ButPlay_clicked();
    void on_ButSlow_clicked();
    void on_ButPrew_clicked();
    void on_ButRec_clicked();
    void on_ButFn1_clicked();
    void on_ButNUM16_clicked();
    void on_ButNUM14_clicked();
    void on_ButNUM15_clicked();
    void on_ButNUM13_clicked();
    void on_ButNUM12_clicked();
    void on_ButNUM11_clicked();
    void on_ButNUM10_clicked();
    void on_ButNUM9_clicked();
    void on_ButEsc_clicked();
    void on_ButNUM8_clicked();
    void on_ButNUM6_clicked();
    void on_ButNUM5_clicked();
    void on_ButNUM4_clicked();
    void on_ButNUM3_clicked();
    void on_ButNUM2_clicked();
    void on_ButNUM7_clicked();
    void on_ButPower_clicked();
    void on_ButNUM1_clicked();
    void on_ButNUM0_clicked();
    void on_ComboxDiskNo_activated(int index);
    void on_ButDiskControl_clicked();
    void on_ButAlarmOutStop_clicked();
    void on_ButAlarmOutStart_clicked();
    void on_ButSetTime_clicked();
    void on_ButGetTime_clicked();
    void on_ButBoot_clicked();
    void on_ButAlarmInStop_clicked();
    void on_ButAlarmInStart_clicked();
    void on_Logout_clicked();
    void on_Login_clicked();
};

#endif // DIALOG_H
