#ifndef SOUNDCAPTURE_DEMO_H
#define SOUNDCAPTURE_DEMO_H

#include <QDialog>

namespace Ui {
class SoundCapture_demo;
}

class SoundCapture_demo : public QDialog
{
    Q_OBJECT
    
public:
    explicit SoundCapture_demo(QWidget *parent = 0);
    ~SoundCapture_demo();
    
private slots:
    void on_StartRecord_clicked();

    void on_StopRecord_clicked();

    void on_BrowseFileButton_clicked();

private:
    void InitCombobox();
    void changeUIState(bool isEnable);

public:
    FILE* m_fpPCM;

private:
    Ui::SoundCapture_demo *ui;
};

#endif // SOUNDCAPTURE_DEMO_H
