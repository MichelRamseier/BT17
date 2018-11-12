#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>

#include "Ptz.h"
#include "UserDefine.h"
#include <iostream>
using namespace std;
CPtz g_PTZ;

void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
    Dialog * pThis = (Dialog *)dwUser;
    if(NULL == pThis)
    {
        return;
    }

        QEvent*  eventDisconnect = new QEvent(QEvent::User);
        QApplication::postEvent((QObject*)pThis, eventDisconnect);
    return;
}
\
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ///初始化
    InitData();
}

Dialog::~Dialog()
{
    /// 反初始化
    UnInitData();
    delete ui;
}

void Dialog::ShowMessage()
{
    if (m_bMessageTip)
    {
        m_bMessageTip = FALSE;

        QMessageBox::information(this, tr("Operate"), tr("Operate fail"));
    }
}
bool Dialog::InitData()
{
    CLIENT_Init(DisConnectFunc, (LDWORD)this);

    installEventFilter(this);//install filter
    m_lLoginHandle = 0;
    ui->lineEdit3->setEchoMode(QLineEdit::Password);
    m_bMessageTip = FALSE;
    ui->Login->setEnabled(true);
    ui->Logout->setEnabled(false);
    m_counter = new QTimer( this );
    connect(m_counter, SIGNAL(timeout()), this, SLOT(ShowMessage()));
    m_counter->start(1000);
    return true;
}
bool Dialog::UnInitData()
{
    CLIENT_Cleanup();
    if(m_counter)
       delete m_counter;
    return true;
}

void Dialog::on_Login_clicked()
{
        QString strIp;
        QString strUserName;
        QString strDvrPort;
        QString strPassword;

        strIp = ui->lineEdit1->text();
        strUserName = ui->lineEdit4->text();
        strPassword = ui->lineEdit3->text();
        strDvrPort = ui->lineEdit2->text();

        NET_DEVICEINFO deviceInfo = {0};
        int error = 0;

        bool numok = false;
        long lPort = strDvrPort.toUInt(&numok);
        if(numok)
        {
            m_lLoginHandle = CLIENT_Login((char *)strIp.toUtf8().data(), lPort, (char*)strUserName.toUtf8().data(),
                                          (char*)strPassword.toUtf8().data(),  &deviceInfo, &error);
            if(m_lLoginHandle == 0)
            {
                if(error != 255)
                {
                    QMessageBox::about(this, tr("Prompt"), tr("Login failed!"));
                }
                else
                {
                    error = CLIENT_GetLastError();
                    if(error ==NET_ERROR_MAC_VALIDATE_FAILED )
                    {
                        QMessageBox::about(this, tr("Prompt"), tr("Login failed! bad mac address"));
                    }
                    else if(error ==NET_ERROR_SENIOR_VALIDATE_FAILED)
                    {
                        QMessageBox::about(this, tr("Prompt"), tr("Login failed! senior validate failed"));
                    }
                }
            }
            else
            {
                g_PTZ.SetLoginID(m_lLoginHandle);
                ui->Login->setEnabled(false);
                ui->Logout->setEnabled(true);

                //initalize comboxChannel
                ui->comboxChannel->clear();
                for(int i = 1; i <= deviceInfo.byChanNum; i++)
                {
                    QString strdata = QString::number(i, 10);
                    int nCount = ui->comboxChannel->count();
                    ui->comboxChannel->insertItem(nCount, strdata);
                    ui->comboxChannel->setCurrentIndex(0);
                    m_nChannelIndex = 0;
                    g_PTZ.SetChannel(m_nChannelIndex);
                    m_nCtrlParam = 1;
                }

            }
        }
        else
        {
            int nRet = QMessageBox::warning(this, tr("Input Error"),
                            "could not convert the port to numbers!\n"
                            "please try again!\n\n ",
                            "Retry",
                            "Quit",0,0,1);
            if (nRet == QMessageBox::Retry)
            {

            }
        }
}

void Dialog::on_Logout_clicked()
{
    if (m_lLoginHandle != 0)
    {
                BOOL bSuccess = CLIENT_Logout(m_lLoginHandle);
                if(bSuccess)
                {
                    ui->Login->setEnabled(true);
                    ui->Logout->setEnabled(false);

                }
                else
                {
                    QMessageBox::about(this, tr("Prompt"), tr("Logout failed!"));
                }
    }
}
void Dialog::PTZForBasicControl(int nType, bool bStop)
{
    bool bRet = false;
    bRet = g_PTZ.PtzBasicControl(nType, m_nCtrlParam, bStop);
    if(bRet == false)
    {
        m_bMessageTip = TRUE;
    }
}
void Dialog::on_pushButLeftUp_pressed()
{
    PTZForBasicControl(DH_EXTPTZ_LEFTTOP, false);
}

void Dialog::on_pushButLeftUp_released()
{
    PTZForBasicControl(DH_EXTPTZ_LEFTTOP, true);
}

void Dialog::on_pushButUp_pressed()
{
    PTZForBasicControl(DH_PTZ_UP_CONTROL, false);
}

void Dialog::on_pushButUp_released()
{
    PTZForBasicControl(DH_PTZ_UP_CONTROL, true);
}

void Dialog::on_comboxChannel_activated(QString )
{
    m_nChannelIndex = ui->comboxChannel->currentIndex();
    g_PTZ.SetChannel(m_nChannelIndex);
}

void Dialog::on_comboxCtrlParam_activated(QString )
{
    m_nCtrlParam = ui->comboxCtrlParam->currentIndex() + 1;
}

void Dialog::on_pushButRightUP_pressed()
{
    PTZForBasicControl(DH_EXTPTZ_RIGHTTOP, false);
}

void Dialog::on_pushButRightUP_released()
{
    PTZForBasicControl(DH_EXTPTZ_RIGHTTOP, true);
}

void Dialog::on_pushButLeft_pressed()
{
    PTZForBasicControl(DH_PTZ_LEFT_CONTROL, false);
}

void Dialog::on_pushButLeft_released()
{
    PTZForBasicControl(DH_PTZ_LEFT_CONTROL, true);
}

void Dialog::on_pushButRight_pressed()
{
     PTZForBasicControl(DH_PTZ_RIGHT_CONTROL, false);
}
void Dialog::on_pushButRight_released()
{
    PTZForBasicControl(DH_PTZ_RIGHT_CONTROL, true);
}

void Dialog::on_pushButLeftDown_pressed()
{
    PTZForBasicControl(DH_EXTPTZ_LEFTDOWN, false);
}

void Dialog::on_pushButLeftDown_released()
{
    PTZForBasicControl(DH_EXTPTZ_LEFTDOWN, true);
}

void Dialog::on_pushButDown_pressed()
{
    PTZForBasicControl(DH_PTZ_DOWN_CONTROL, false);
}

void Dialog::on_pushButDown_released()
{
    PTZForBasicControl(DH_PTZ_DOWN_CONTROL, true);
}

void Dialog::on_pushButRDown_pressed()
{
    PTZForBasicControl(DH_EXTPTZ_RIGHTDOWN, false);
}

void Dialog::on_pushButRDown_released()
{
    PTZForBasicControl(DH_EXTPTZ_RIGHTDOWN, true);
}

void Dialog::on_pushButAZoom_pressed()
{
    PTZForBasicControl(DH_PTZ_ZOOM_ADD_CONTROL, false);
}

void Dialog::on_pushButAZoom_released()
{
    PTZForBasicControl(DH_PTZ_ZOOM_ADD_CONTROL, true);
}

void Dialog::on_pushButDZoom_pressed()
{
    PTZForBasicControl(DH_PTZ_ZOOM_DEC_CONTROL, false);
}

void Dialog::on_pushButDZoom_released()
{
    PTZForBasicControl(DH_PTZ_ZOOM_DEC_CONTROL, true);
}

void Dialog::on_pushButAFocus_pressed()
{
    PTZForBasicControl(DH_PTZ_FOCUS_ADD_CONTROL, false);
}

void Dialog::on_pushButAFocus_released()
{
    PTZForBasicControl(DH_PTZ_FOCUS_ADD_CONTROL, true);
}

void Dialog::on_pushButDFocus_pressed()
{
    PTZForBasicControl(DH_PTZ_FOCUS_DEC_CONTROL, false);
}

void Dialog::on_pushButDFocus_released()
{
    PTZForBasicControl(DH_PTZ_FOCUS_DEC_CONTROL, true);
}

void Dialog::on_pushButAperture_pressed()
{
    PTZForBasicControl(DH_PTZ_APERTURE_ADD_CONTROL, false);
}

void Dialog::on_pushButAperture_released()
{
    PTZForBasicControl(DH_PTZ_APERTURE_ADD_CONTROL, true);
}

void Dialog::on_pushButDAperture_pressed()
{
    PTZForBasicControl(DH_PTZ_APERTURE_DEC_CONTROL, false);
}

void Dialog::on_pushButDAperture_released()
{
    PTZForBasicControl(DH_PTZ_APERTURE_DEC_CONTROL, true);
}

void Dialog::on_pushButSet_clicked()
{
        bool numok = false;
        QString strPresetNo = ui->EditPreSetNo->text();
        long    lPresetNo = strPresetNo.toUInt(&numok);

        if (lPresetNo < 1 || lPresetNo > 255)
        {
            QMessageBox::information(this, tr("Operate"), tr("Preset num must is between 1 and 255"));
            return;
        }

        if(numok)
        {
            PTZForPresetControl(DH_PTZ_POINT_SET_CONTROL, lPresetNo);
        }
        else
        {
            QMessageBox::information(this, tr("Operate"), tr("Operate failed, Input data error"));
        }
}

void Dialog::on_pushButPresetDel_clicked()
{
       bool numok = false;
       QString strPresetNo = ui->EditPreSetNo->text();
       long	lPresetNo = strPresetNo.toUInt(&numok);

       if (lPresetNo < 1 || lPresetNo > 255)
       {
           QMessageBox::information(this, tr("Operate"), tr("Preset num must is between 1 and 255"));
           return;
       }

       if(numok)
       {
           PTZForPresetControl(DH_PTZ_POINT_DEL_CONTROL, lPresetNo);
       }
       else
       {
           QMessageBox::information(this, tr("Operate"), tr("Operate failed, Input data error"));

       }
}

void Dialog::on_pushButGotoPreset_clicked()
{
       bool numok = false;
       QString strPresetNo = ui->EditPreSetNo->text();
       long	lPresetNo = strPresetNo.toUInt(&numok);

       if (lPresetNo < 1 || lPresetNo > 255)
       {
           QMessageBox::information(this, tr("Operate"), tr("Preset num must is between 1 and 255"));
           return;
       }

       if(numok)
       {
           PTZForPresetControl(DH_PTZ_POINT_MOVE_CONTROL, lPresetNo);
       }
       else
       {
           QMessageBox::information(this, tr("Operate"), tr("Operate failed, Input data error"));

       }
}

void Dialog::on_ButStartTour_clicked()
{
       bool bPresetnumok = false;
       bool bTournumok = false;

       QString strPresetNo = ui->EditPresetNum->text();
       long	lPresetNo = strPresetNo.toUInt(&bPresetnumok);

       QString strTourNo = ui->AutoTourNo->text();
       long	lTourNo  = strTourNo.toUInt(&bTournumok);

       if( bTournumok)
       {
           PTZForAutoTour( DH_PTZ_POINT_LOOP_CONTROL, lTourNo, lPresetNo, true );
       }
       else
       {
           QMessageBox::information(this, tr("Operate"), tr("Operate failed, Input data error"));
       }
}

void Dialog::on_ButStopTour_clicked()
{
        bool bPresetnumok = false;
        bool bTournumok = false;

        QString strPresetNo = ui->EditPresetNum->text();
        long	lPresetNo   = strPresetNo.toUInt(&bPresetnumok);

        QString strTourNo = ui->AutoTourNo->text();
        long	lTourNo   = strTourNo.toUInt(&bTournumok);

        if(bTournumok)
        {
            PTZForAutoTour(DH_PTZ_POINT_LOOP_CONTROL, lTourNo, lPresetNo, false);
        }
        else
        {
            QMessageBox::information(this, tr("Operate"), tr("Operate failed, Input data error"));
        }
}

void Dialog::on_ButAddTour_clicked()
{
        bool bPresetnumok = false;
        bool bTournumok = false;

        QString strPresetNo = ui->EditPresetNum->text();
        long	lPresetNo   = strPresetNo.toUInt(&bPresetnumok);

        if (lPresetNo < 1 || lPresetNo > 255)
        {
            QMessageBox::information(this, tr("Operate"), tr("Preset num must is between 1 and 255"));
            return;
        }

        QString strTourNo = ui->AutoTourNo->text();
        long	lTourNo   = strTourNo.toUInt(&bTournumok);

        if(bPresetnumok && bTournumok)
        {
            PTZForAutoTour( DH_EXTPTZ_ADDTOLOOP, lTourNo, lPresetNo, false );
        }
        else
        {
            QMessageBox::information(this, tr("Operate"), tr("Operate failed, Input data error"));
        }
}

void Dialog::on_ButDelTourPreset_clicked()
{
        bool bPresetnumok = false;
        bool bTournumok = false;

        QString strPresetNo = ui->EditPresetNum->text();
        long	lPresetNo = strPresetNo.toUInt(&bPresetnumok);

        QString strTourNo = ui->AutoTourNo->text();
        long	lTourNo = strTourNo.toUInt(&bTournumok);

        if (lPresetNo < 1 || lPresetNo > 255)
        {
            QMessageBox::information(this, tr("Operate"), tr("Preset num must is between 1 and 255"));
            return;
        }

        if(bPresetnumok && bTournumok)
        {
            PTZForAutoTour( DH_EXTPTZ_DELFROMLOOP, lTourNo, lPresetNo, false );
        }
        else
        {
            QMessageBox::information(this, tr("Operate"), tr("Operate failed, Input data error"));
        }
}

void Dialog::on_ButDelTourNo_clicked()
{
       bool bPresetnumok = false;
       bool bTournumok = false;

       QString strPresetNo = ui->EditPresetNum->text();
       long	lPresetNo  = strPresetNo.toUInt(&bPresetnumok);

       QString strTourNo = ui->AutoTourNo->text();
       long    lTourNo   = strTourNo.toUInt(&bTournumok);

       if(bTournumok)
       {
           PTZForAutoTour( DH_EXTPTZ_CLOSELOOP, lTourNo, lPresetNo, false );
       }
       else
       {
           QMessageBox::information(this, tr("Operate"), tr("Operate failed, Input data error"));
       }
}

void Dialog::on_ButMenuLeft_clicked()
{
    PTZForMenu(DH_EXTPTZ_MENULEFT);
}

void Dialog::on_ButMenuUP_clicked()
{
    PTZForMenu(DH_EXTPTZ_MENUUP);
}

void Dialog::on_ButMenuRight_clicked()
{
    PTZForMenu(DH_EXTPTZ_MENURIGHT);
}

void Dialog::on_ButMenuDown_clicked()
{
    PTZForMenu(DH_EXTPTZ_MENUDOWN);
}

void Dialog::on_ButOpenMenu_clicked()
{
    PTZForMenu(DH_EXTPTZ_OPENMENU);
}

void Dialog::on_ButCloseMenu_clicked()
{
    PTZForMenu(DH_EXTPTZ_CLOSEMENU);
}

void Dialog::on_ButMenuOK_clicked()
{
    PTZForMenu(DH_EXTPTZ_MENUOK);
}

void Dialog::on_ButMenuCancel_clicked()
{
    PTZForMenu(DH_EXTPTZ_MENUCANCEL);
}

void Dialog::on_ButSIT_clicked()
{
        bool nXumok = false;
        bool nYumok = false;
        bool nZoomumok = false;

        QString strX = ui->lineEditX->text();
        long    lX   = strX.toLong(&nXumok);

        QString strY = ui->lineEditY->text();
        long    lY   = strY.toLong(&nYumok);

        QString strZoom = ui->lineEditZoom->text();
        long    lZoom   = strZoom.toLong(&nZoomumok);

        if (nXumok && nYumok && nZoomumok)
        {
            PTZForSIT( lX, lY, lZoom);
        }
        else
        {
            QMessageBox::information(this, tr("Operate"), tr("Operate failed, Input data error"));
        }
}

void Dialog::on_ButOpenAUX_clicked()
{
       bool numok = false;
       QString strAuxNo = ui->comboxAuxNo->currentText();
       long    lAuxNo = strAuxNo.toUInt(&numok);

       if(numok)
       {
           PTZForAUX( DH_EXTPTZ_AUXIOPEN, lAuxNo );
       }
       else
       {
           QMessageBox::information(this, tr("Operate"), tr("Operate failed, Input data error"));
       }
}

void Dialog::on_ButCloseAUX_clicked()
{
        bool numok = false;
        QString strAuxNo = ui->comboxAuxNo->currentText();
        long    lAuxNo = strAuxNo.toUInt(&numok);

        if(numok)
        {
            PTZForAUX( DH_EXTPTZ_AUXICLOSE, lAuxNo );
        }
        else
        {
            QMessageBox::information(this, tr("Operate"), tr("Operate failed, Input data error"));
        }
}

void Dialog::on_ButLimitLeft_clicked()
{
    PTZForScan(DH_EXTPTZ_SETLEFTBORDER);
}

void Dialog::on_ButLimitRight_clicked()
{
    PTZForScan(DH_EXTPTZ_SETRIGHTBORDER);
}

void Dialog::on_ButStartScan_clicked()
{
    PTZForScan(DH_EXTPTZ_STARTLINESCAN);
}

void Dialog::on_butStopScan_clicked()
{
    PTZForScan(DH_EXTPTZ_CLOSELINESCAN);
}

void Dialog::on_ButStartPan_clicked()
{
    PTZForPan(DH_EXTPTZ_STARTPANCRUISE);
}

void Dialog::on_ButStopPan_clicked()
{
    PTZForPan(DH_EXTPTZ_STOPPANCRUISE);
}

void Dialog::on_ButStartProgram_clicked()
{
        bool numok = false;
        QString strPattemNo = ui->PattermNo->text();
        long    lPattemNo = strPattemNo.toUInt(&numok);

        if(numok)
        {
            PTZForPattem( DH_EXTPTZ_SETMODESTART, lPattemNo );
        }
        else
        {
            QMessageBox::information(this, tr("Operate"), tr("Operate failed, Input data error"));
        }
}

void Dialog::on_ButStopProgram_clicked()
{
       bool numok = false;
       QString strPattemNo = ui->PattermNo->text();
       long    lPattemNo = strPattemNo.toUInt(&numok);

       if(numok)
       {
           PTZForPattem( DH_EXTPTZ_SETMODESTOP, lPattemNo );
       }
       else
       {
           QMessageBox::information(this, tr("Operate"), tr("Operate failed, Input data error"));
       }
}

void Dialog::on_ButStartPatterm_clicked()
{
    bool numok = false;
       QString strPattemNo = ui->PattermNo->text();
       long    lPattemNo   = strPattemNo.toUInt(&numok);

       if(numok)
       {
           PTZForPattem( DH_EXTPTZ_RUNMODE, lPattemNo );
       }
       else
       {
           QMessageBox::information(this, tr("Operate"), tr("Operate failed, Input data error"));
       }
}

void Dialog::on_ButStopPatterm_clicked()
{
       bool numok = false;
       QString strPattemNo = ui->PattermNo->text();
       long	lPattemNo = strPattemNo.toUInt(&numok);

       if(numok)
       {
           PTZForPattem( DH_EXTPTZ_STOPMODE, lPattemNo );
       }
       else
       {
           QMessageBox::information(this, tr("Operate"), tr("Operate failed, Input data error"));
       }
}

void Dialog::on_ButDelPatterm_clicked()
{
        bool numok = false;
        QString strPattemNo = ui->PattermNo->text();
        long    lPattemNo = strPattemNo.toUInt(&numok);

        if(numok)
        {
            PTZForPattem( DH_EXTPTZ_DELETEMODE, lPattemNo );
        }
        else
        {
            QMessageBox::information(this, tr("Operate"), tr("Operate failed, Input data error"));
        }
}

void Dialog::PTZForPresetControl( int nType, int nPresetNo )
{
    bool bRet = false;

    bRet = g_PTZ.PtzPreset(nType, nPresetNo);

    if(bRet == false)
    {
        QMessageBox::information(this, tr("Operate"), tr("Operate fail"));
    }
}


void Dialog::PTZForAutoTour( int nType, int nTourNo, int nPresetNo, bool bAutoTour )
{
    bool bRet = false;

    bRet = g_PTZ.PtzLoop(nType, nTourNo, nPresetNo, bAutoTour);

    if(bRet == false)
    {
        QMessageBox::information(this, tr("Operate"), tr("Operate fail"));
    }

}


void Dialog::PTZForPattem( int nType, int nPattemNo )
{
    bool bRet = false;

    bRet = g_PTZ.PtzMode(nType, nPattemNo);

    if(bRet == false)
    {
        QMessageBox::information(this, tr("Operate"), tr("Operate fail"));
    }
}


void Dialog::PTZForScan( int nType )
{
    bool bRet = false;

    bRet = g_PTZ.PtzLineScan(nType);

    if(bRet == false)
    {
        QMessageBox::information(this, tr("Operate"), tr("Operate fail"));
    }

}


void Dialog::PTZForPan( int nType )
{
    bool bRet = false;

    bRet = g_PTZ.PtzRotate(nType);

    if(bRet == false)
    {
        QMessageBox::information(this, tr("Operate"), tr("Operate fail"));
    }

}


void Dialog::PTZForSIT( int nX, int nY, int nZoom)
{
    bool bRet = false;

    bRet = g_PTZ.PtzFastGo(nX, nY, nZoom);

    if(bRet == false)
    {
        QMessageBox::information(this, tr("Operate"), tr("Operate fail"));
    }

}


void Dialog::PTZForAUX( int nType, int nAuxNo )
{
    bool bRet = false;

    bRet = g_PTZ.PtzAuxi(nType, nAuxNo);

    if(bRet == false)
    {
        QMessageBox::information(this, tr("Operate"), tr("Operate fail"));
    }
}


void Dialog::PTZForMenu( int nType)
{
    bool bRet = false;

    bRet = g_PTZ.PtzMenuControl(nType);

    if(bRet == false)
    {
        QMessageBox::information(this, tr("Operate"), tr("Operate fail"));
    }
}

bool Dialog::eventFilter(QObject *obj, QEvent *event)//message filter
{
    if(event->type() == QEvent::User)
    {
        QString strDevInfo;
        strDevInfo.append("Disconnect!");
        QMessageBox::information(0, "Promt", strDevInfo);
    }
    return QWidget::eventFilter(obj, event);//don't eat event
}


