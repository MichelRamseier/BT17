#ifndef FORM1_H
#define FORM1_H

#include <QDialog>
#include "ui_form1.h"
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
#include"dhnetsdk.h"
#include "./include/dhmutex.h"
#include "UserDefine.h"
#include <stdlib.h>
//#include <stl_list.h>
//#include <sys/times.h>
#include <unistd.h>

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
    void destroyForm();

private:
    Ui::Form1 *ui;
    long m_lLoginHandle;
    QTimer* m_counter;
    DWORD m_dwGroupID;
    DWORD m_dwUserID;
    USER_MANAGE_INFO_NEW m_usersInfo;
   // std::list<QListViewItem*> m_AccountRightparentList;
   // QValueList<QListViewItem*> m_AccountparentList;

    bool eventFilter(QObject *obj, QEvent *event);
    void InitData();
    void InitAccountTree();
    void RefreshAccountRightList();
    void RefreshGroupRightList();
    void InitGroupRightTree(DWORD dwNum, DWORD *dwList);
    void InitGroupInformation(USER_GROUP_INFO_NEW groupList);
    void RefreshUserRightList();
    void InitUserRightTree(DWORD dwNum, DWORD *dwList);
    void InitUserInformation(USER_INFO_NEW userList);
    int GetAccountIndex(DWORD dwID);
    void ClearTableWidget(QTableWidget* pList);

private slots:
    void on_Form1_destroyed();
    void on_Logout_clicked();
    void on_ButModifyUserCanel_clicked();
    void on_ButModGroupCancel_clicked();
    void on_ButModGroupOK_clicked();
    void on_ButAddGroupCancel_clicked();
    void on_ButAddGroupOK_clicked();
    void on_ButModPwdCancel_clicked();
    void on_ButModPwdOK_clicked();
    void on_ButModifyUserOK_clicked();
    void on_ButAddUserCancel_clicked();
    void on_ButAddUserAdd_clicked();
    void on_ButDeleteGroup_clicked();
    void on_ButDeleteUser_clicked();
    void on_listViewAccount_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);
    void on_Login_clicked();
};

#endif // FORM1_H
