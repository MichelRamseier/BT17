#ifndef FORM1_H
#define FORM1_H

#include <QDialog>
#include <qdatetime.h>
#include "dhnetsdk.h"

namespace Ui {
    class form1;
}

class form1 : public QDialog
{
    Q_OBJECT

public:
    explicit form1(QWidget *parent = 0);
    ~form1();


    void InitForm();
    void InitData();
    void destroyForm();
    void ConvertTimeToStr(DHDEVTIME *nettime, QDate *date, QTime *time);
    void DisplayQueryResult(char *recBuf, int nLength);
    BOOL JudgeType(int nQueryType, int nInfoType);
    bool eventFilter(QObject *obj, QEvent *event);
    int /*void*/ TransLogInfo(void *pLoginfo, int nStructType, QString &strLogType, QString &strLogTime, QString &strLogContext);
    QString ConvertCfgType(const DH_LOG_ITEM* pLogItem);
    void InsertListViewItem(QString strLogType, QString strLogTime, QString strLogContext);
    void DisPlayNewLogInfo(DH_DEVICE_LOG_ITEM_EX* pLogItem, int nCount, BOOL bAppend = FALSE);

private:
    Ui::form1 *ui;
    LLONG m_lLoginHandle;
    DH_DEV_ENABLE_INFO m_stuEnable;
    int m_nPageLine;
    int m_nPageLineOld; //m_nPageLine changed when nextpage or prepage button clicked
    int m_nPreStartNum;
    int m_nPreEndNum;

private slots:
    void on_ButXMLQuery_clicked();
    void on_ButNextPage_clicked();
    void on_ButPrePage_clicked();
    void on_ButExit_clicked();
    void on_ButQuery_clicked();
    void on_Logout_clicked();
    void on_Login_clicked();

};

#endif // FORM1_H
