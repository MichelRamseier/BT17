#ifndef WATERCHECK_DEMO_H
#define WATERCHECK_DEMO_H

#include <QDialog>
#include <QStandardItemModel>
#include <QMutex>
#include <QWaitCondition>
#include <QFile>
#include <QSemaphore>
#include <QMessageBox>
#include "watercheckthread.h"

namespace Ui {
class WaterCheck_demo;
}

class WaterCheck_demo : public QDialog, public IRunnable
{
    Q_OBJECT
    
public:
    explicit WaterCheck_demo(QWidget *parent = 0);
    ~WaterCheck_demo();
    
private slots:
    void on_BrowseFile_clicked();

    void on_StopCheck_clicked();

    void on_StartCheck_clicked();

    void onValueChanged(int value);

signals:
    void valueChanged(int value);

private:
    enum UI_STATE
    {
        INIT,
        OPENFILE,
        CHECK,
        STOP,
        COMPLETE
    };

public:
    virtual void run();

public:
    int onWaterMarkCheck(long nPort, char* buf, long lTimeStamp, long lInfoType, long len, long reallen, long lCheckResult);

public:
//    bool event(QEvent *event);

private:
    void initTableView();
    void changeUIState(UI_STATE state);
    void deleteAllItems();

public slots:
    void EndSlot();

signals:
    void EndSignal();

private:
    Ui::WaterCheck_demo *ui;
    QStandardItemModel  *m_itemModel;
    QMutex               m_mutex;
    QWaitCondition       m_exitCondition;
    QFile                m_checkFile;
    WaterCheckThread*    m_thread;
    bool                 m_isExit;
    QSemaphore           m_sema;
    QMessageBox          m_hMess;
};

#endif // WATERCHECK_DEMO_H
