#ifndef DLGSNAPPICSETTING_H
#define DLGSNAPPICSETTING_H

#include <QDialog>

namespace Ui {
class DlgSnapPicSetting;
}

class DlgSnapPicSetting : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgSnapPicSetting(QWidget *parent = 0);
    ~DlgSnapPicSetting();

    void ResetSet(QString strPath, int iPicType);
private slots:
    void on_bmpType_clicked();

    void on_jpgType_clicked();

    void on_btnPath_clicked();

    void on_OK_clicked();

private:
    Ui::DlgSnapPicSetting *ui;

public:
    QString m_strPath;
    int m_iPicType;
};

#endif // DLGSNAPPICSETTING_H
