#ifndef DLGCUTFILE_H
#define DLGCUTFILE_H

#include <QDialog>

namespace Ui {
class dlgCutFile;
}

class dlgCutFile : public QDialog
{
    Q_OBJECT
    
public:
    explicit dlgCutFile(QString originFile,QWidget *parent = 0);
    ~dlgCutFile();
    
private slots:
    void on_btnSave_clicked();

    void on_frameNumType_clicked();

    void on_timeType_clicked();

    void on_btnCancel_clicked();

private:
    Ui::dlgCutFile *ui;

    typedef enum{
        CUTBYFRAMENUM,
        CUTBYTIME
    }CUTTYPE;

    QString m_originFile;
    int	m_cutType;
    int m_nMaxFrameNum;
    int m_nMaxTime;
};

#endif // DLGCUTFILE_H
