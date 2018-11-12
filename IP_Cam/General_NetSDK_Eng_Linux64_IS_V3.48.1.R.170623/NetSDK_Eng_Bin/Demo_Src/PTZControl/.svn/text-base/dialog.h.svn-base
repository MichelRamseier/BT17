#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include "dhnetsdk.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public:
    void ShowMessage();
    void PTZForBasicControl(int nType, bool bStop);
    void PTZForPresetControl( int nType, int nPresetNo );
    void PTZForAutoTour( int nType, int nTourNo, int nPresetNo, bool bAutoTour );
    void PTZForPattem( int nType, int nPattemNo );
    void PTZForScan( int nType );
    void PTZForPan( int nType );
    void PTZForSIT( int nX, int nY, int nZoom);
    void PTZForAUX( int nType, int nAuxNo );
    void PTZForMenu( int nType);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
protected:
    bool InitData();
    bool UnInitData();
private:
    LLONG      m_lLoginHandle;   ///登陆句柄
    QTimer     *m_counter;       ///计时器
    int        m_bMessageTip;
    int        m_nChannelIndex;  ///当前通道
    int        m_nCtrlParam;     /// 云台控制参数
private:
    Ui::Dialog *ui;

private slots:
    void on_ButDelPatterm_clicked();
    void on_ButStopPatterm_clicked();
    void on_ButStartPatterm_clicked();
    void on_ButStopProgram_clicked();
    void on_ButStartProgram_clicked();
    void on_pushButRightUP_released();
    void on_pushButRight_pressed();
    void on_pushButLeft_released();
    void on_pushButLeft_pressed();
    void on_ButStopPan_clicked();
    void on_ButStartPan_clicked();
    void on_butStopScan_clicked();
    void on_ButStartScan_clicked();
    void on_ButLimitRight_clicked();
    void on_ButLimitLeft_clicked();
    void on_ButCloseAUX_clicked();
    void on_ButOpenAUX_clicked();
    void on_ButSIT_clicked();
    void on_ButMenuCancel_clicked();
    void on_ButMenuOK_clicked();
    void on_ButCloseMenu_clicked();
    void on_ButOpenMenu_clicked();
    void on_ButMenuDown_clicked();
    void on_ButMenuRight_clicked();
    void on_ButMenuUP_clicked();
    void on_ButMenuLeft_clicked();
    void on_ButDelTourNo_clicked();
    void on_ButDelTourPreset_clicked();
    void on_ButAddTour_clicked();
    void on_ButStopTour_clicked();
    void on_ButStartTour_clicked();
    void on_pushButGotoPreset_clicked();
    void on_pushButPresetDel_clicked();
    void on_pushButSet_clicked();
    void on_pushButDAperture_released();
    void on_pushButDAperture_pressed();
    void on_pushButAperture_released();
    void on_pushButAperture_pressed();
    void on_pushButDFocus_released();
    void on_pushButDFocus_pressed();
    void on_pushButAFocus_released();
    void on_pushButAFocus_pressed();
    void on_pushButDZoom_released();
    void on_pushButDZoom_pressed();
    void on_pushButAZoom_released();
    void on_pushButAZoom_pressed();
    void on_pushButRDown_released();
    void on_pushButRDown_pressed();
    void on_pushButDown_released();
    void on_pushButDown_pressed();
    void on_pushButLeftDown_released();
    void on_pushButLeftDown_pressed();
    void on_pushButRight_released();
    void on_pushButRightUP_pressed();
    void on_comboxCtrlParam_activated(QString );
    void on_comboxChannel_activated(QString );
    void on_pushButUp_released();
    void on_pushButUp_pressed();
    void on_pushButLeftUp_released();
    void on_pushButLeftUp_pressed();
    void on_Logout_clicked();
    void on_Login_clicked();
};

#endif // DIALOG_H
