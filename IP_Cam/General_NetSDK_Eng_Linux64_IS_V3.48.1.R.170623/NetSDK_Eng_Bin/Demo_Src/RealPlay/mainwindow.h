#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qtimer.h>
#include <qlistview.h>
#include <qstring.h>
#include <string>
#include <pthread.h>
#include <QFileDialog>
#include <pthread.h>
#include<stdlib.h>
#include <QStandardItemModel>
#include "dhnetsdk.h"
#include "./utility/dhmutex.h"
#include "UserDefine.h"
#include "./utility/Profile.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    int  LoadConfig(int * nThreadNum);
    void Logindev(int nThreadNum);
    QStandardItemModel *createListModel();
    void addRowData(QAbstractItemModel *model, QStringList rowDataList);

protected:
    bool InitData();
    bool UnInitData();

private:
#if defined(WIN32) || defined(WIN64)
    HANDLE		m_thread;
#else
        pthread_t	m_thread;
#endif
    QTimer * m_counter;
    LLONG  m_lLoginHandle;
    QString m_FileName;
    QStandardItemModel *standardItemModel;
private:
    Ui::MainWindow *ui;

private slots:
    void on_pushButStop_clicked();
    void on_pushButStopALL_clicked();
    void on_pushButPlay_clicked();
    void on_pushButLoad_clicked();
    void UpdataListview();
};

#endif // MAINWINDOW_H
