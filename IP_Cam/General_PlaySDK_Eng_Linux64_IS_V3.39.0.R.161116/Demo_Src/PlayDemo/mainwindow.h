#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Player.h"
#include "PlayStateText.h"
#include "dlgopenfile.h"
#include "dlgsnappicsetting.h"
#include "IWindowEvent.h"

enum MENU_STATE
{
    FILEOPEN,
    FILECLOSE,
    FILEINDEXCREATED,
    STOPPLAY,
    STARTPLAY
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public IWindowEvent
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_Play_clicked();

    void on_Pause_clicked();

    void on_Stop_clicked();

    void on_ToBegin_clicked();

    void on_ToEnd_clicked();

    void on_StepBackOne_clicked();

    void on_StepGo_clicked();

    void on_Slow_clicked();

    void on_Fast_clicked();

    void on_Backword_clicked();

    void on_Forword_clicked();

    void on_SnapPicture_clicked();

    void on_SetColor_clicked();

    void on_SetVolume_clicked();

    void on_actionOpen_triggered();

    void on_actionClose_triggered();

    void on_actionCutFile_triggered();

    void on_actionSnapPicture_triggered();

    void on_actionLocate_triggered();

    void on_actionMediaInfo_triggered();

    void on_actionIVS_triggered();

    void on_actionVecticalSync_triggered();

    void on_actionHwaccel_triggered();

    void OnProcessTimer();
    void OnWaveChanged(int pos);
    void OnVolumeChanged(int pos);
    void OnProcessChanged(int pos);

    void closeEvent(QCloseEvent *event);

public:
    virtual void onFileIndexEvent(int indexState);

signals:
    void indexCreated(int indexState);

private slots:
   void onIndexCreated(int indexState);

private:
    void OnOperator(PLAY_STATE nState);
    int ChangeUIState(PLAY_STATE nState);
    int ChangeSingleUIState(PLAY_STATE nState, BOOL bEnable);
    int ChangeMenuState(MENU_STATE nState);
    void OpenFile();
    int OpenAudio();
    int CloseAudio();

protected:
    void dragEnterEvent(QDragEnterEvent * event);
    void dropEvent(QDropEvent * event);

private:
    Ui::MainWindow *ui;
    CPlayStateText m_dlgStateText;
    PLAY_STATE m_lastState;
    DlgOpenFile m_dlgOpenFile;
    DlgSnapPicSetting m_dlgSnapPicSetting;
    QTimer *m_pTimer;
    bool m_isPlaySound;
};

#endif // MAINWINDOW_H
