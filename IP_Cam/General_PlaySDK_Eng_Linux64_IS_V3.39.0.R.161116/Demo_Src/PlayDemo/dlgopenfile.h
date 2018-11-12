#ifndef DLGOPENFILE_H
#define DLGOPENFILE_H

#include <QDialog>
#include <QString>

namespace Ui {
class DlgOpenFile;
}

class DlgOpenFile : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgOpenFile(QWidget *parent = 0);
    ~DlgOpenFile();
    
private slots:
    void on_btnOpenFile_clicked();

    void on_btnOK_clicked();

    void on_filetype_clicked();

    void on_filestreamtype_clicked();

public:
    void showEvent(QShowEvent* event);

private:
    Ui::DlgOpenFile *ui;

public:
    int m_nType;
    QString m_strFile;
};

#endif // DLGOPENFILE_H
