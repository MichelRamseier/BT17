#include "form1.h"

#ifndef __max
#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#endif
#ifndef __min
#define __min(a,b) (((a) < (b)) ? (a) : (b))
#endif

Form1::Form1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form1)
{
    ui->setupUi(this);
}

Form1::~Form1()
{
    delete ui;
}

#ifndef WIN32
#define Sleep(x)		usleep(x*1000)
#endif
void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
    Form1 * pThis = (Form1 *)dwUser;
    if(NULL == pThis)
    {
        return;
    }
    //deal
    //QString strDevInfo = pchDVRIP;
    //strDevInfo.append("is disconnect!");
    //QMessageBox::information(0, "Promt", strDevInfo);

    //deal
    QEvent*  eventDisconnect = new QEvent(QEvent::User);
    QApplication::postEvent((QObject*)pThis, eventDisconnect);
    return;
}


void Form1::InitForm()
{
    CLIENT_Init(DisConnectFunc, (LDWORD)this);

    installEventFilter(this);//install filter

    InitData();

    m_counter = new QTimer( this );
    m_counter->start(1000);
}

void Form1::InitData()
{
    m_lLoginHandle = 0;
    memset(&m_usersInfo, 0, sizeof(USER_MANAGE_INFO_NEW));
    m_usersInfo.dwSize = sizeof(m_usersInfo);
    m_dwGroupID = 0;
    m_dwUserID = -1;

    ui->Login->setEnabled(true);
    ui->Logout->setEnabled(false);
    ui->ButAddUserAdd->setEnabled(false);
    ui->ButModPwdOK->setEnabled(false);
    ui->ButAddGroupOK->setEnabled(false);
    ui->ButModPwdOK->setEnabled(false);
    ui->ButModGroupOK->setEnabled(false);
    ui->ButDeleteUser->setEnabled(false);
    ui->ButDeleteGroup->setEnabled(false);

    ui->lineEdit3->setEchoMode(QLineEdit::Password);
    ui->EditModPwdNew->setEchoMode(QLineEdit::Password);
    ui->EditModPwd->setEchoMode(QLineEdit::Password);
    ui->EditModPwdNewCheck->setEchoMode(QLineEdit::Password);
    ui->EditAddUserPwd->setEchoMode(QLineEdit::Password);
}


bool Form1::eventFilter(QObject *obj, QEvent *event)//message filter
{
    if(event->type() == QEvent::Close)//windows close
    {
        cout<<"message distroy"<<endl;
        destroyForm();
    }
    else if(event->type() == QEvent::User)//disconnect
    {
        QString strDevInfo;
        strDevInfo.append("Disconnect!");
        QMessageBox::information(0, "Promt", strDevInfo);
    }
    return QWidget::eventFilter(obj, event);//don't eat event
}

void Form1::destroyForm()
{
    cout<<"destroyed"<<endl;
    CLIENT_Cleanup();
    m_counter->stop();
}

void Form1::on_Login_clicked()
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

    //get nunber
    bool numok = false;
    long lPort = strDvrPort.toLong(&numok);
    if(numok)
    {
        m_lLoginHandle = CLIENT_Login((char*)strIp.toLocal8Bit().data(), lPort, (char*)strUserName.toLocal8Bit().data(),(char*)strPassword.toLocal8Bit().data(),  &deviceInfo, &error);

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
            ui->Login->setEnabled(false);
            ui->Logout->setEnabled(true);

            memset(&m_usersInfo, 0, sizeof(USER_MANAGE_INFO_NEW));
            m_usersInfo.dwSize = sizeof(m_usersInfo);
            BOOL bRet = CLIENT_QueryUserInfoNew(m_lLoginHandle, &m_usersInfo, NULL, 10000);
            if (!bRet)
            {
                QMessageBox::about(this, tr("prompt"), tr("Get User Information Failed!"));
            }
            else
            {
                ui->ButAddUserAdd->setEnabled(true);
                ui->ButModPwdOK->setEnabled(true);
                ui->ButAddGroupOK->setEnabled(true);
                ui->ButModPwdOK->setEnabled(true);
                ui->ButModGroupOK->setEnabled(true);
                ui->ButDeleteUser->setEnabled(true);
                ui->ButDeleteGroup->setEnabled(true);

                ui->EditAddUserName->setMaxLength(m_usersInfo.byNameMaxLength);
                ui->EditAddUserPwd->setMaxLength(m_usersInfo.byPSWMaxLength);
                ui->EditAddUserMemo->setMaxLength(DH_MEMO_LENGTH);
                ui->EditModUserNameNew->setMaxLength(m_usersInfo.byNameMaxLength);
                ui->EditModPwdNew->setMaxLength(m_usersInfo.byPSWMaxLength);
                ui->EditModPwd->setMaxLength(m_usersInfo.byPSWMaxLength);
                ui->EditModMemoNew->setMaxLength(DH_MEMO_LENGTH);
                ui->EditModGroupMemoNew->setMaxLength(DH_MEMO_LENGTH);
                ui->EditAddGroupMemo->setMaxLength(DH_MEMO_LENGTH);
                ui->EditModPwdNewCheck->setMaxLength(m_usersInfo.byPSWMaxLength);
                ui->EditAddGroupName->setMaxLength(m_usersInfo.byNameMaxLength);
                ui->EditModGroupNameNew->setMaxLength(m_usersInfo.byNameMaxLength);

                InitAccountTree();
            }
        }
    }
    else
    {
        int nRet = QMessageBox::warning(this,"Input Error",
                        "could not convert the port to numbers!\n"
                        "please try again!\n\n ",
                        "Retry",
                        "Quit",0,0,1);
        if (nRet == QMessageBox::Retry)
        {

        }
    }
}

void Form1::InitAccountTree()
{
    //all item delete
    ui->listViewAccount->clear();;//all item delete
    ClearTableWidget(ui->listViewAccountRight);
    ui->listViewAccountRight->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //m_AccountRightparentList.clear();

    QTreeWidgetItem *item = 0;
    QTableWidgetItem *Rightitem = 0;


    for(int i=0;i<(int)m_usersInfo.dwGroupNum;i++)
    {
        // create a list with n ListViewItems which will be parent items of other ListViewItems
        char szName[DH_NEW_USER_NAME_LENGTH] = {0};
        memcpy(szName, m_usersInfo.groupList[i].name, DH_USER_NAME_LENGTH_EX);
        item = new QTreeWidgetItem();
        item->setText(0, QString::fromLocal8Bit(szName));
        ui->listViewAccount->addTopLevelItem(item);
       // m_AccountparentList.append(item);

        //item->setOpen(TRUE);

        for(int j=0;j<(int)m_usersInfo.dwUserNum;j++)
        {
            if(m_usersInfo.userList[j].dwGroupID == m_usersInfo.groupList[i].dwID)
            {
                char szName[DH_NEW_USER_NAME_LENGTH] = {0};
                memcpy(szName, m_usersInfo.userList[j].name, DH_NEW_USER_NAME_LENGTH);
                QTreeWidgetItem *pChildItem = new QTreeWidgetItem();
                if(pChildItem)
                {
                    pChildItem->setText(0, QString::fromLocal8Bit(szName));
                    item->addChild(pChildItem);
                }

            }
        }
    }

    for(int k=0;k<(int)m_usersInfo.dwRightNum;k++)
    {
        QString str;
        str.sprintf("%d: %s : %s",m_usersInfo.rightList[k].dwID,m_usersInfo.rightList[k].name,m_usersInfo.rightList[k].memo);

        Rightitem = new QTableWidgetItem(str);
        if(Rightitem)
        {
            Rightitem->setCheckState(Qt::Unchecked);
            Rightitem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            int nRowNum = ui->listViewAccountRight->rowCount();
            ui->listViewAccountRight->insertRow(nRowNum);
            ui->listViewAccountRight->setItem(nRowNum, 0, Rightitem);
            //m_AccountRightparentList.append(Rightitem);
        }

    }

    if (item == NULL)
    {
        return;
    }

    ui->listViewAccount->setCurrentItem(item);
    RefreshAccountRightList();
}

void Form1::RefreshAccountRightList()
{
    QTreeWidgetItem *useritem = ui->listViewAccount->currentItem();
    if(useritem == NULL)
    {
        return;
    }
    //QList<QTableWidgetItem*> ItemList;

    for (int i = 0; i < ui->listViewAccountRight->rowCount(); i++)
    {
        ui->listViewAccountRight->item(i, 0)->setCheckState(Qt::Unchecked);
    }

    QByteArray str = useritem->text(0).toLocal8Bit();

    // ...check state of childs, and...
    if (useritem->parent())//(user)
    {
        for (int i = 0; i < m_usersInfo.dwUserNum; i++)
        {
            char szName[DH_NEW_USER_NAME_LENGTH] = {0};
            memcpy(szName, m_usersInfo.userList[i].name, DH_NEW_USER_NAME_LENGTH);
            if (strcmp(str.data(), szName) == 0)
            {
                QTableWidgetItem *UserRightitem = 0;

                m_dwGroupID = m_usersInfo.userList[i].dwGroupID;
                m_dwUserID = i;

                for (int k = 0; k < m_usersInfo.userList[i].dwRightNum; k++)
                {
                    QString strID;//= QString::number(m_usersInfo.userList[i].rights[k], 10);
                    strID.sprintf("%d: ", m_usersInfo.userList[i].rights[k]);

					QList<QTableWidgetItem*> lstItems = ui->listViewAccountRight->findItems(strID, Qt::MatchStartsWith);
					if (!lstItems.isEmpty())
					{
						UserRightitem = lstItems.first();
						if (UserRightitem)
						{
							UserRightitem->setCheckState(Qt::Checked);
						}
					}
                }
                break;
            }
        }
    }
    else //(Group)
    {
        for (int i = 0; i < m_usersInfo.dwGroupNum; i++)
        {
            char szName[DH_NEW_USER_NAME_LENGTH] = {0};
            memcpy(szName, m_usersInfo.groupList[i].name, DH_USER_NAME_LENGTH_EX);
            if (strcmp(str.data(), szName) == 0)
            {
                QTableWidgetItem *GroupRightitem = 0;
                m_dwGroupID = m_usersInfo.groupList[i].dwID;
                m_dwUserID = -1;

                for (int k = 0; k < m_usersInfo.groupList[i].dwRightNum; k++)
                {
                    QString strID;// = QString::number(m_usersInfo.groupList[i].rights[k], 10);
                    strID.sprintf("%d: ", m_usersInfo.groupList[i].rights[k]);

					QList<QTableWidgetItem*> lstItems = ui->listViewAccountRight->findItems(strID, Qt::MatchStartsWith);
					if (!lstItems.isEmpty())
					{
						GroupRightitem = lstItems.first();
						if (GroupRightitem)
						{
							GroupRightitem->setCheckState(Qt::Checked);
						}
					}
                 }
                break;
            }
        }
    }
    return;
}

void Form1::RefreshGroupRightList()
{
    QTreeWidgetItem *useritem = ui->listViewAccount->currentItem();
    if(useritem == NULL)
    {
        return;
    }

    QString str = useritem->text(0);

    // ...check state of childs, and...
    if (useritem->parent())//(user)
    {
        for (int i = 0; i < m_usersInfo.dwUserNum; i++)
        {
            char szName[DH_NEW_USER_NAME_LENGTH] = {0};
            memcpy(szName, m_usersInfo.userList[i].name, DH_NEW_USER_NAME_LENGTH);
            if (strcmp(str.toLocal8Bit().data(), szName) == 0)
            {
                for(int j = 0; j < (int)(m_usersInfo.dwGroupNum); j++)
                {
                    if(m_usersInfo.groupList[j].dwID == m_usersInfo.userList[i].dwGroupID)
                    {
                            InitGroupInformation(m_usersInfo.groupList[j]);

                            InitGroupRightTree(m_usersInfo.groupList[j].dwRightNum,m_usersInfo.groupList[j].rights);
                            break;
                    }
                }
                break;
            }
        }
    }
    else //(Group)
    {
        for (int i = 0; i < m_usersInfo.dwGroupNum; i++)
        {
            char szName[DH_NEW_USER_NAME_LENGTH] = {0};
            memcpy(szName, m_usersInfo.groupList[i].name, DH_USER_NAME_LENGTH_EX);
            if (strcmp(str.toLocal8Bit().data(), szName) == 0)
            {
                InitGroupInformation(m_usersInfo.groupList[i]);

                InitGroupRightTree(m_usersInfo.groupList[i].dwRightNum,m_usersInfo.groupList[i].rights);
                break;
            }
        }
    }
}

void Form1::ClearTableWidget(QTableWidget* pList)
{
    if(pList)
    {
        pList->clearContents();//all item delete
        int i = 0;
        int nRowCount = pList->rowCount();
        for(i = 0; i < nRowCount; i++)
        {
           pList->removeRow(0);
        }
    }

}

void Form1::InitGroupRightTree(DWORD dwNum, DWORD *dwList)
{
    if(dwList == NULL)
    {
        return;
    }

    ClearTableWidget(ui->listViewAddUser);
    ClearTableWidget(ui->listViewModGroup);
    ClearTableWidget(ui->listViewAddGroup);

    ui->listViewAddUser->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listViewAddGroup->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listViewModGroup->setEditTriggers(QAbstractItemView::NoEditTriggers);


    QTableWidgetItem *GroupRightitem = 0;
    int i = 0;
    int nRowNum = 0;
    for(i = 0; i < (int)m_usersInfo.dwRightNum; i++)
    {
        QString str;
        char szName[DH_NEW_USER_NAME_LENGTH] = {0};
        char szMemo[64] = {0};
        memcpy(szName, m_usersInfo.rightList[i].name, DH_NEW_USER_NAME_LENGTH);
        memcpy(szMemo, m_usersInfo.rightList[i].memo, DH_MEMO_LENGTH);
        str.sprintf("%d: %s : %s",m_usersInfo.rightList[i].dwID, szName, szMemo);

        //add user tab
        QTableWidgetItem *pItemAddUser = new QTableWidgetItem(str);
        if(pItemAddUser)
        {
            pItemAddUser->setCheckState(Qt::Unchecked);
            nRowNum = ui->listViewAddUser->rowCount();
            ui->listViewAddUser->insertRow(nRowNum);
            ui->listViewAddUser->setItem(nRowNum, 0, pItemAddUser);
        }

        //modify group tab
        QTableWidgetItem *pItemModGroup = new QTableWidgetItem(str);
        if(pItemModGroup)
        {
            pItemModGroup->setCheckState(Qt::Unchecked);
            nRowNum = ui->listViewModGroup->rowCount();
            ui->listViewModGroup->insertRow(nRowNum);
            ui->listViewModGroup->setItem(nRowNum, 0, pItemModGroup);
        }

        //add group tab
        QTableWidgetItem *pItemAddGroup = new QTableWidgetItem(str);
        if(pItemAddGroup)
        {
            pItemAddGroup->setCheckState(Qt::Unchecked);
            nRowNum = ui->listViewAddGroup->rowCount();
            ui->listViewAddGroup->insertRow(nRowNum);
            ui->listViewAddGroup->setItem(i, 0, pItemAddGroup);
        }

    }

    for(i = 0; i < (int)dwNum; i++)
    {
        QString strID;// = QString::number(dwList[i], 10);
        strID.sprintf("%d: ", dwList[i]);
        //add user tab
		QList<QTableWidgetItem*> lstItems = ui->listViewAddUser->findItems(strID, Qt::MatchStartsWith);
		if (!lstItems.isEmpty())
		{
			GroupRightitem = lstItems.first();
			if (0 != GroupRightitem)
			{
				GroupRightitem->setCheckState(Qt::Checked);
			}
		}

        //modify group tab
		lstItems = ui->listViewModGroup->findItems(strID, Qt::MatchStartsWith);
		if (!lstItems.isEmpty())
		{
			GroupRightitem = lstItems.first();
			if (0 != GroupRightitem)
			{
				GroupRightitem->setCheckState(Qt::Checked);
			}
		}
    }
    printf("out\n");
}


void Form1::InitGroupInformation(USER_GROUP_INFO_NEW groupList)
{
    char szName[DH_NEW_USER_NAME_LENGTH] = {0};
    memcpy(szName, groupList.name, sizeof(groupList.name));
    QString strGroupName = QString::fromLocal8Bit(szName);

    //add user tab
    ui->EditAddUserGroup->setText(strGroupName);
    ui->EditAddUserName->setText("");
    ui->EditAddUserPwd->setText("");
    ui->EditAddUserMemo->setText("");
    //modify user tab
    ui->EditModUserGroup->setText(strGroupName);

    //add group tab
    ui->EditAddGroupMemo->setText("");
    ui->EditAddGroupName->setText("");

    //modify group tab
    ui->EditModGroupName->setText(strGroupName);
    ui->EditModGroupNameNew->setText(strGroupName);
    ui->EditModGroupMemoNew->setText("");

    DWORD dwSpecial = (m_usersInfo.dwFouctionMask&0x01);
    if(dwSpecial == 0)
    {
        //add user tab
        ui->checkAddReusable->setEnabled(false);
        //modify user tab
        ui->CheckModReuse->setEnabled(false);
        ui->CheckModReuseNew->setEnabled(false);
    }

    //modify group tab
    char szMemo[64] = {0};
    memcpy(szMemo, groupList.memo, 32);
	QString strGroupMemo = QString::fromLocal8Bit(szMemo);
    ui->EditModGroupMemo->setText(strGroupMemo);
}

void Form1::RefreshUserRightList()
{
    QTreeWidgetItem *useritem = ui->listViewAccount->currentItem();
    if(useritem == NULL)
    {
        return;
    }
    QString str = useritem->text(0);

    // ...check state of childs, and...
    if (useritem->parent())//(user)
    {
        for (int i = 0; i < m_usersInfo.dwUserNum; i++)
        {
            char szName[DH_NEW_USER_NAME_LENGTH] = {0};
            memcpy(szName, m_usersInfo.userList[i].name, DH_NEW_USER_NAME_LENGTH);
            if (strcmp(str.toLocal8Bit().data(), szName) == 0)
            {
                InitUserInformation(m_usersInfo.userList[i]);

                InitUserRightTree(m_usersInfo.userList[i].dwRightNum, m_usersInfo.userList[i].rights);
                break;
            }
        }
    }
}


void Form1::InitUserRightTree(DWORD dwNum, DWORD *dwList)
{
    if(dwList == NULL)
    {
        return;
    }

    ClearTableWidget(ui->listViewModifyUser);
     ui->listViewModifyUser->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QTableWidgetItem *UserRightitem = 0;
    int i = 0;
    int nRowNum = 0;
    for(i = 0; i < (int)m_usersInfo.dwRightNum; i++)
    {
        QString str;
        char szName[DH_NEW_USER_NAME_LENGTH] = {0};
        char szMemo[64] = {0};
        memcpy(szName, m_usersInfo.rightList[i].name, DH_NEW_USER_NAME_LENGTH);
        memcpy(szMemo, m_usersInfo.rightList[i].memo, DH_MEMO_LENGTH);
        str.sprintf("%d: %s : %s",m_usersInfo.rightList[i].dwID, szName, szMemo);

        QTableWidgetItem *pItem = new QTableWidgetItem(str);
        pItem->setCheckState(Qt::Unchecked);
        nRowNum = ui->listViewModifyUser->rowCount();
        ui->listViewModifyUser->insertRow(nRowNum);
        ui->listViewModifyUser->setItem(nRowNum, 0, pItem);
    }

    for(i = 0; i < (int)dwNum; i++)
    {
        QString strID;// = QString::number(dwList[i], 10);
        strID.sprintf("%d: ", dwList[i]);
        //add user tab
		QList<QTableWidgetItem*> lstItems = ui->listViewModifyUser->findItems(strID, Qt::MatchStartsWith);
		if (!lstItems.isEmpty())
		{
			UserRightitem = lstItems.first();
			if (0 != UserRightitem)
			{
				UserRightitem->setCheckState(Qt::Checked);
			}
		}
    }
}

void Form1::InitUserInformation(USER_INFO_NEW userList)
{
    char szName[DH_NEW_USER_NAME_LENGTH] = {0};
    char szMemo[64] = {0};
    memcpy(szName, userList.name, DH_NEW_USER_NAME_LENGTH);
    memcpy(szMemo, userList.memo, DH_MEMO_LENGTH);
    QString strUserName = QString::fromLocal8Bit(szName);
    QString strUserMemo = QString::fromLocal8Bit(szMemo);

    //modify user tab
    ui->EditModUserName->setText(strUserName);
    ui->EditModMemo->setText(strUserMemo);
    ui->EditModUserNameNew->setText(strUserName);
    ui->EditModMemoNew->setText("");

    //modify password tab
    ui->EditModPwdUserName->setText(strUserName);
    ui->EditModPwdNew->setText("");
    ui->EditModPwdNewCheck->setText("");
    ui->EditModPwd->setText("");

    DWORD dwReusable = (userList.dwFouctionMask&0x01);
    if(dwReusable == 0)
    {
        ui->CheckModReuse->setChecked(false);
    }
    else
    {
        ui->CheckModReuse->setChecked(true);
    }
}



void Form1::on_listViewAccount_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous)
{
    RefreshAccountRightList();
    RefreshGroupRightList();
    RefreshUserRightList();
}

void Form1::on_ButDeleteUser_clicked()
{
    if(0 < m_lLoginHandle)
     {
         QTreeWidgetItem *useritem = ui->listViewAccount->currentItem();
         if(useritem == NULL)
         {
             return;
         }

         QByteArray str = useritem->text(0).toLocal8Bit();

         // ...check state of childs, and...
         if (useritem->parent())//(user)
         {
             for (int i = 0; i < m_usersInfo.dwUserNum; i++)
             {
                 char szName[DH_NEW_USER_NAME_LENGTH] = {0};
                 memcpy(szName, m_usersInfo.userList[i].name, DH_NEW_USER_NAME_LENGTH);
                 if (strcmp(str.data(), szName) == 0)
                 {
                    m_usersInfo.userList[i].dwSize = sizeof(USER_INFO_NEW);
                    BOOL bRet = CLIENT_OperateUserInfoNew(m_lLoginHandle, 4, (void *)&m_usersInfo.userList[i], 0, 0, 10000);
                    if (bRet)
                    {
                         BOOL bRet1 = CLIENT_QueryUserInfoNew(m_lLoginHandle, &m_usersInfo, 0, 10000);
                         if (!bRet1)
                         {
                                 QMessageBox::about(this, tr("prompt"), tr("Get User Information Failed!"));
                         }
                         else
                         {
                                 InitAccountTree();
                         }
                    }
                    else
                    {
                         int nError = CLIENT_GetLastError();
                         if(nError == NET_RETURN_DATA_ERROR)
                         {
                                 QMessageBox::about(this, tr("prompt"), tr("data check error!"));
                         }
                         else if(nError == NET_ILLEGAL_PARAM)
                         {
                                 QMessageBox::about(this, tr("prompt"), tr("Input data error!"));
                         }
                         else if(nError == NET_USER_NOEXIST)
                         {
                                 QMessageBox::about(this, tr("prompt"), tr("Account no exist!"));
                         }
                         else
                         {
                                 QMessageBox::about(this, tr("prompt"), tr("Delete user account error!"));
                         }
                    }
                    break;
                }
             }
         }

         else
         {
             QMessageBox::about(this, tr("prompt"), tr("Please select account!"));
         }
     }

     else
     {
         QMessageBox::about(this, tr("prompt"), tr("Please login first!"));
     }
}

void Form1::on_ButDeleteGroup_clicked()
{
    if(0 < m_lLoginHandle)
       {
           QTreeWidgetItem *useritem = ui->listViewAccount->currentItem();
           if(useritem != NULL)
           {
               QByteArray str = useritem->text(0).toLocal8Bit();

               if (useritem->parent() == NULL)//(Group)
               {
                   for (int i = 0; i < m_usersInfo.dwGroupNum; i++)
                   {
                       char szName[DH_NEW_USER_NAME_LENGTH] = {0};
                       memcpy(szName, m_usersInfo.groupList[i].name, DH_USER_NAME_LENGTH_EX);
                       if (memcmp(str.data(), szName, __min(DH_USER_NAME_LENGTH_EX, str.size())) == 0)
                       {
                           m_usersInfo.groupList[i].dwSize = sizeof(USER_GROUP_INFO_NEW);
                               BOOL bRet1 = CLIENT_OperateUserInfoNew(m_lLoginHandle, 1, (void *)&m_usersInfo.groupList[i], 0, 0, 10000);
                               if (bRet1)
                               {
                                       BOOL bRet = CLIENT_QueryUserInfoNew(m_lLoginHandle, &m_usersInfo, 0, 10000);
                                       if (!bRet)
                                       {
                                               QMessageBox::about(this, tr("prompt"), tr("Get User Information Failed!"));
                                       }
                                       else
                                       {
                                               InitAccountTree();
                                       }
                               }
                               else
                               {
                                       int nError = CLIENT_GetLastError();
                                       if(nError == NET_RETURN_DATA_ERROR)
                                       {
                                               QMessageBox::about(this, tr("prompt"), tr("data check error!"));
                                       }
                                       else if(nError == NET_ILLEGAL_PARAM)
                                       {
                                               QMessageBox::about(this, tr("prompt"), tr("Input data error!"));
                                       }
                                       else if(nError == NET_USER_NOEXIST)
                                       {
                                               QMessageBox::about(this, tr("prompt"), tr("Account no exist!"));
                                       }
                                       else
                                       {
                                               QMessageBox::about(this, tr("prompt"), tr("Delete group account error!"));
                                       }
                               }
                               break;
                       }
                   }
               }
               else
               {
                   QMessageBox::about(this, tr("prompt"), tr("Please select a group!"));
               }
           }
       }
       else
       {
           QMessageBox::about(this, tr("prompt"), tr("Please login first!"));
       }
}

void Form1::on_ButAddUserAdd_clicked()
{
    QString strUserName = ui->EditAddUserName->text();
    if (strUserName.isEmpty())
    {
       QMessageBox::about(this, tr("Prompt"), tr("User name can't be null!"));
       return;
    }

    QString strGroupName = ui->EditAddUserGroup->text();
    if (strGroupName.isEmpty())
    {
       QMessageBox::about(this, tr("Prompt"), tr("Please select a group first!"));
       return;
    }

    USER_INFO_NEW userInfo = {0};
    userInfo.dwSize = sizeof(userInfo);
    userInfo.dwID = m_usersInfo.dwUserNum + 1;
    memcpy(userInfo.name, ui->EditAddUserName->text().toLocal8Bit().data(), __min(ui->EditAddUserName->text().toLocal8Bit().length(),sizeof(userInfo.name)));
    memcpy(userInfo.passWord, ui->EditAddUserPwd->text().toLocal8Bit().data(), __min(ui->EditAddUserPwd->text().length(), sizeof(userInfo.passWord)));
    memcpy(userInfo.memo, ui->EditAddUserMemo->text().toLocal8Bit().data(), __min(ui->EditAddUserMemo->text().toLocal8Bit().length(), sizeof(userInfo.memo)));
    userInfo.dwFouctionMask = (DWORD)ui->checkAddReusable->isChecked();
    userInfo.dwGroupID = m_dwGroupID;

    int nCountItem = ui->listViewAddUser->rowCount();
    QTableWidgetItem *useritem = ui->listViewAddUser->item(0,0);

    int nIndex = 0;
    for (int i = 0; i< nCountItem && useritem; i++)
    {
		useritem = ui->listViewAddUser->item(i,0);

       if (useritem->checkState() == Qt::Checked)
       {
           QString str = useritem->text();
           userInfo.rights[nIndex] = (str.section(':', 0, 0)).toInt();
           nIndex++;
       }
		 // useritem = ui->listViewAddUser->item(i,0);
    }
    userInfo.dwRightNum = nIndex;

    BOOL bRet = CLIENT_OperateUserInfoNew(m_lLoginHandle, 3/*type: add user*/, &userInfo, 0,0, 1000);
    if (!bRet)
    {
       int nError = CLIENT_GetLastError();
       if(nError == NET_RETURN_DATA_ERROR)
       {
           QMessageBox::about(this, tr("prompt"), tr("data check error!"));
       }
       else if(nError == NET_ILLEGAL_PARAM)
       {
           QMessageBox::about(this, tr("prompt"), tr("Input data error!"));
       }
       else if(nError == NET_GROUP_NOEXIST)
       {
           QMessageBox::about(this, tr("prompt"), tr("Group is not exist!"));
       }
       else if(nError == NET_USER_EXIST)
       {
           QMessageBox::about(this, tr("prompt"), tr("User is already exist!"));
       }
       else if(nError == NET_USER_RIGHTOVER)
       {
           QMessageBox::about(this, tr("prompt"), tr("User's right is not exist!"));
       }
       else
       {
           QMessageBox::about(this, tr("prompt"), tr("Add user failed!"));
       }
    }
    else
    {
       bRet = CLIENT_QueryUserInfoNew(m_lLoginHandle, &m_usersInfo, 0, 10000);
       if (!bRet)
       {
           QMessageBox::about(this, tr("prompt"), tr("Get User Information Failed!"));
       }
       else
       {
           InitAccountTree();
       }
    }
}

void Form1::on_ButAddUserCancel_clicked()
{
    ui->EditAddUserName->setText("");
    ui->EditAddUserPwd->setText("");
    ui->EditAddUserMemo->setText("");
}

void Form1::on_ButModifyUserOK_clicked()
{
    if (m_dwUserID == -1)
    {
       QMessageBox::about(this, tr("Prompt"), tr("Please select a user!"));
       return;
    }

    QString strUserName = ui->EditModUserNameNew->text();
    if (strUserName.isEmpty())
    {
       QMessageBox::about(this, tr("Prompt"), tr("User name can't be null!"));
       return;
    }

    QString strGroupName = ui->EditModUserGroup->text();
    if (strGroupName.isEmpty())
    {
       QMessageBox::about(this, tr("Prompt"), tr("Please select a group first!"));
       return;
    }

    USER_INFO_NEW userInfo = {0};
    userInfo.dwSize = sizeof(userInfo);
    userInfo.dwID = m_usersInfo.userList[m_dwUserID].dwID;
    int nlen = __min(DH_NEW_USER_NAME_LENGTH, ui->EditModUserNameNew->text().toLocal8Bit().length());
    memcpy(userInfo.name, ui->EditModUserNameNew->text().toLocal8Bit().data(), nlen);
    memcpy(userInfo.passWord, m_usersInfo.userList[m_dwUserID].passWord, DH_NEW_USER_PSW_LENGTH);
    nlen =  __min(ui->EditModMemoNew->text().toLocal8Bit().length(),DH_MEMO_LENGTH);
    memcpy(userInfo.memo, ui->EditModMemoNew->text().toLocal8Bit().data(), nlen);
    userInfo.dwFouctionMask = (DWORD)(ui->CheckModReuseNew->isChecked());
    userInfo.dwGroupID = m_usersInfo.userList[m_dwUserID].dwGroupID;

    int nCountItem = ui->listViewModifyUser->rowCount();
    QTableWidgetItem *useritem = ui->listViewModifyUser->item(0,0);

    int nIndex = 0;
    for (int i = 0; i< nCountItem && useritem; i++)
    {
		useritem = ui->listViewModifyUser->item(i,0);

       if (useritem->checkState() == Qt::Checked)
       {
           QString str = useritem->text();
           userInfo.rights[nIndex] = (str.section(':', 0, 0)).toInt();
           nIndex++;
       }
      // useritem = ui->listViewModifyUser->item(i,0);
    }
    userInfo.dwRightNum = nIndex;

    m_usersInfo.userList[m_dwUserID].dwSize = sizeof(USER_INFO_NEW);
    BOOL bRet = CLIENT_OperateUserInfoNew(m_lLoginHandle, 5, (void *)&userInfo, (void *)&m_usersInfo.userList[m_dwUserID], 0, 1000);
    if (!bRet)
    {
       int nError = CLIENT_GetLastError();
       if(nError == NET_RETURN_DATA_ERROR)
       {
           QMessageBox::about(this, tr("prompt"), tr("data check error!"));
       }
       else if(nError == NET_ILLEGAL_PARAM)
       {
           QMessageBox::about(this, tr("prompt"), tr("Input data error!"));
       }
       else if(nError == NET_GROUP_NOEXIST)
       {
           QMessageBox::about(this, tr("prompt"), tr("Group is not exist!"));
       }
       else if(nError == NET_USER_EXIST)
       {
           QMessageBox::about(this, tr("prompt"), tr("User is already exist!"));
       }
       else if(nError == NET_USER_RIGHTOVER)
       {
           QMessageBox::about(this, tr("prompt"), tr("User's right is not exist!"));
       }
       else
       {
           QMessageBox::about(this, tr("prompt"), tr("Modify user failed!"));
       }
    }
    else
    {
       Sleep(100);
       bRet = CLIENT_QueryUserInfoNew(m_lLoginHandle, &m_usersInfo, 0,3000);
       if (!bRet)
       {
           QMessageBox::about(this, tr("prompt"), tr("Get User Information Failed!"));
       }
       else
       {
           InitAccountTree();
       }
    }
}

void Form1::on_ButModPwdOK_clicked()
{
	if (m_dwUserID == -1)
	{
		QMessageBox::about(this, tr("Prompt"), tr("Please select a user!"));
		return;
	}

    QString strUserName = ui->EditModPwdUserName->text();
      if (strUserName.isEmpty())
      {
          QMessageBox::about(this, tr("Prompt"), tr("Please select a user!"));
          return;
      }

      if (ui->EditModPwdNew->text() != ui->EditModPwdNewCheck->text())
      {
          QMessageBox::about(this, tr("Prompt"), tr("Password check error!"));
          return;
      }

      USER_INFO_NEW newInfo = {0};
      newInfo.dwSize = sizeof(newInfo);
      USER_INFO_NEW oldInfo = {0};
      oldInfo.dwSize = sizeof(oldInfo);
      char strPwd[DH_NEW_USER_PSW_LENGTH] = {0};

      int nlen = __min(ui->EditModPwdNew->text().toLocal8Bit().length(),DH_NEW_USER_PSW_LENGTH);
      memcpy(newInfo.passWord, ui->EditModPwdNew->text().toLocal8Bit().data(),nlen);
      memcpy(oldInfo.name,  m_usersInfo.userList[m_dwUserID].name, DH_NEW_USER_PSW_LENGTH);
      nlen = __min(ui->EditModPwd->text().toLocal8Bit().length(), DH_NEW_USER_PSW_LENGTH);
      memcpy(oldInfo.passWord, ui->EditModPwd->text().toLocal8Bit().data(), nlen);

      BOOL bRet = CLIENT_OperateUserInfoNew(m_lLoginHandle, 6, (void *)&newInfo, &oldInfo, 0, 1000);
      if (!bRet)
      {
          int nError = CLIENT_GetLastError();
          if(nError == NET_RETURN_DATA_ERROR)
          {
              QMessageBox::about(this, tr("prompt"), tr("data check error!"));
          }
          else if(nError == NET_ILLEGAL_PARAM)
          {
              QMessageBox::about(this, tr("prompt"), tr("Input data error!"));
          }
          else if(nError == NET_USER_PWD)
          {
              QMessageBox::about(this, tr("prompt"), tr("You have no right to modify the password!"));
          }
          else if(nError == NET_USER_FLASEPWD)
          {
              QMessageBox::about(this, tr("prompt"), tr("password error!"));
          }
          else if(nError == NET_USER_NOMATCHING)
          {
              QMessageBox::about(this, tr("prompt"), tr("password check error!"));
          }
          else
          {
              QMessageBox::about(this, tr("prompt"), tr("modify passsword error!"));
          }
      }
      else
      {
          bRet = CLIENT_QueryUserInfoNew(m_lLoginHandle, &m_usersInfo, 0, 10000);
          if (!bRet)
          {
              QMessageBox::about(this, tr("prompt"), tr("Get User Information Failed!"));
          }
          else
          {
              InitAccountTree();
          }
      }
}

void Form1::on_ButModPwdCancel_clicked()
{
    ui->EditModPwdNew->setText("");
    ui->EditModPwd->setText("");
    ui->EditModPwdNewCheck->setText("");
}

void Form1::on_ButAddGroupOK_clicked()
{
    QString strGroupName = ui->EditAddGroupName->text();
    if (strGroupName.isEmpty())
    {
        QMessageBox::about(this, tr("Prompt"), tr("Group name can't be null!"));
        return;
    }

    USER_GROUP_INFO_NEW groupInfo = {0};
    groupInfo.dwSize = sizeof(groupInfo);
    groupInfo.dwID = m_usersInfo.dwGroupNum + 1;

    int nlen = __min(ui->EditAddGroupName->text().toLocal8Bit().length(), DH_USER_NAME_LENGTH_EX);
    memcpy(groupInfo.name, ui->EditAddGroupName->text().toLocal8Bit().data(), nlen);
    nlen = __min(ui->EditAddGroupMemo->text().toLocal8Bit().length(),DH_MEMO_LENGTH);
    memcpy(groupInfo.memo, ui->EditAddGroupMemo->text().toLocal8Bit().data(), nlen);
    int nCountItem = ui->listViewAddGroup->rowCount();

    QTableWidgetItem *groupitem = ui->listViewAddGroup->item(0,0);

    int nIndex = 0;
    for (int i = 0; i< nCountItem && groupitem; i++)
    {
        if (groupitem->checkState()==Qt::Checked)
        {
            QString str = groupitem->text();
            groupInfo.rights[nIndex] = (str.section(':', 0, 0)).toInt();
            nIndex++;
        }
        groupitem = ui->listViewAddGroup->item(i+1, 0);
    }
    groupInfo.dwRightNum = nIndex;

    BOOL bRet = CLIENT_OperateUserInfoNew(m_lLoginHandle, 0/*type: add user group*/, &groupInfo, 0, 0, 1000);
    if (!bRet)
    {
        int nError = CLIENT_GetLastError();
        if(nError == NET_RETURN_DATA_ERROR)
        {
            QMessageBox::about(this, tr("prompt"), tr("data check error!"));
        }
        else if(nError == NET_ILLEGAL_PARAM)
        {
            QMessageBox::about(this, tr("prompt"), tr("Input data error!"));
        }
        else if(nError == NET_GROUP_EXIST)
        {
            QMessageBox::about(this, tr("prompt"), tr("The group is already exist!"));
        }
        else if(nError == NET_GROUP_RIGHTOVER)
        {
            QMessageBox::about(this, tr("prompt"), tr("right is error!"));
        }
        else
        {
            QMessageBox::about(this, tr("prompt"), tr("Add group failed!"));
        }
    }
    else
    {
        bRet = CLIENT_QueryUserInfoNew(m_lLoginHandle, &m_usersInfo, 0, 10000);
        if (!bRet)
        {
            QMessageBox::about(this, tr("prompt"), tr("Get User Information Failed!"));
        }
        else
        {
            InitAccountTree();
        }
    }
}

void Form1::on_ButAddGroupCancel_clicked()
{
    ui->EditAddGroupName->setText("");
    ui->EditAddGroupMemo->setText("");
}

void Form1::on_ButModGroupOK_clicked()
{
    QString strGroupName = ui->EditModGroupNameNew->text();
    if (strGroupName.isEmpty())
    {
        QMessageBox::about(this, tr("Prompt"), tr("Group name can't be null!"));
        return;
    }

    USER_GROUP_INFO_NEW groupInfo = {0};
    groupInfo.dwSize = sizeof(groupInfo);
    int nIDIndex = GetAccountIndex(m_dwGroupID);
    if (nIDIndex == -1)
    {
        QMessageBox::about(this, tr("Prompt"), tr("Group isn't exist!"));	     return;
    }

    groupInfo.dwID = m_usersInfo.groupList[nIDIndex].dwID;
    int nlen = __min(ui->EditModGroupNameNew->text().toLocal8Bit().length(), DH_USER_NAME_LENGTH_EX);
    memcpy(groupInfo.name, ui->EditModGroupNameNew->text().toLocal8Bit().data(), nlen);
    nlen = __min(ui->EditModGroupMemoNew->text().toLocal8Bit().length(),DH_MEMO_LENGTH);
    memcpy(groupInfo.memo, ui->EditModGroupMemoNew->text().toLocal8Bit().data(), nlen);

    int nCountItem = ui->listViewModGroup->rowCount();
    QTableWidgetItem *groupitem = ui->listViewModGroup->item(0,0);
    int nIndex = 0;
    for (int i = 0; i< nCountItem && groupitem; i++)
    {
        groupitem = ui->listViewModGroup->item(i,0);
        if (groupitem->checkState() == Qt::Checked)
        {
            QString str = groupitem->text();
            groupInfo.rights[nIndex] = (str.section(':', 0, 0)).toInt();
            nIndex++;
        }
    }
    groupInfo.dwRightNum = nIndex;

    m_usersInfo.groupList[nIDIndex].dwSize = sizeof(USER_GROUP_INFO_NEW);
    BOOL bRet = CLIENT_OperateUserInfoNew(m_lLoginHandle, 2, &groupInfo, &m_usersInfo.groupList[nIDIndex],0, 1000);
    if (!bRet)
    {
        int nError = CLIENT_GetLastError();
        if(nError == NET_RETURN_DATA_ERROR)
        {
            QMessageBox::about(this, tr("prompt"), tr("data check error!"));
        }
        else if(nError == NET_ILLEGAL_PARAM)
        {
            QMessageBox::about(this, tr("prompt"), tr("Input data error!"));
        }
        else if(nError == NET_GROUP_NOEXIST)
        {
            QMessageBox::about(this, tr("prompt"), tr("The Group isn't exist!"));
        }
        else if(nError == NET_GROUP_RIGHTUSE)
        {
            QMessageBox::about(this, tr("prompt"), tr("The group is  being used!"));
        }
        else if(nError == NET_GROUP_SAMENAME)
        {
            QMessageBox::about(this, tr("prompt"), tr("The group name has been exist!"));
        }
        else
        {
            QMessageBox::about(this, tr("prompt"), tr("Modify group failed!"));
        }
    }
    else
    {
        bRet = CLIENT_QueryUserInfoNew(m_lLoginHandle, &m_usersInfo, 0, 10000);
        if (!bRet)
        {
            QMessageBox::about(this, tr("prompt"), tr("Get User Information Failed!"));
        }
        else
        {
            InitAccountTree();
        }
    }
}

void Form1::on_ButModGroupCancel_clicked()
{
    ui->EditModGroupNameNew->setText("");
    ui->EditModGroupMemoNew->setText("");
}

int Form1::GetAccountIndex(DWORD dwID)
{
    int nIndex = -1;

    for (int i = 0; i < m_usersInfo.dwGroupNum; i++)
    {
       if (dwID == m_usersInfo.groupList[i].dwID)
        {
            nIndex = i;
            break;
        }
    }
    return nIndex;
}

void Form1::on_ButModifyUserCanel_clicked()
{
    ui->EditModUserNameNew->setText("");
    ui->EditModMemoNew->setText("");
}

void Form1::on_Logout_clicked()
{
    if (m_lLoginHandle != 0)
       {
           BOOL bSuccess = CLIENT_Logout(m_lLoginHandle);
           if (bSuccess)
           {
               ui->Login->setEnabled(true);
               ui->Logout->setEnabled(false);
               ui->ButAddUserAdd->setEnabled(false);
               ui->ButModPwdOK->setEnabled(false);
               ui->ButAddGroupOK->setEnabled(false);
               ui->ButModPwdOK->setEnabled(false);
               ui->ButModGroupOK->setEnabled(false);
               ui->ButDeleteUser->setEnabled(false);
               ui->ButDeleteGroup->setEnabled(false);

               //all item delete
               ui->listViewAccount->clear();//all item delete
               ClearTableWidget(ui->listViewAccountRight);
               ClearTableWidget(ui->listViewAddUser);
               ClearTableWidget(ui->listViewModifyUser);
               ClearTableWidget(ui->listViewModGroup);
               ClearTableWidget(ui->listViewAddGroup);

               //m_AccountparentList.clear();
               //m_AccountRightparentList.clear();

               on_ButModGroupCancel_clicked();
               on_ButAddUserCancel_clicked();
               on_ButModifyUserCanel_clicked();
               on_ButModPwdCancel_clicked();
               on_ButAddGroupCancel_clicked();
           }
           else
           {
               QMessageBox::about(this, tr("prompt"), tr("Logout failed!"));
           }
       }
}

void Form1::on_Form1_destroyed()
{
    destroyForm();
}
