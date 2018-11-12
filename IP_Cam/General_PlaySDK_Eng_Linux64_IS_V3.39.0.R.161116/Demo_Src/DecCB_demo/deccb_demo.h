#ifndef DECCB_DEMO_H
#define DECCB_DEMO_H

#include <QDialog>
#include <QFile>
#include "displaywindow.h"

namespace Ui {
class DecCB_demo;
}

class DecCB_demo : public QDialog
{
    Q_OBJECT
    
public:
    explicit DecCB_demo(QWidget *parent = 0);
    ~DecCB_demo();

private:
    enum DECODE_STATE
    {
        START_DEC,
        STOP_DEC
    };

    enum DEC_TYPE
    {
        DEC_VIDEO,
        DEC_AUDIO,
        DEC_COMPLEX
    };

private slots:
    void on_BrowseFile_clicked();

    void on_BrowseOutputAudioFile_clicked();

    void on_BrowseOutputYuvFile_clicked();

    void on_DecodeButton_clicked();

    void on_StopButton_clicked();

    void EndSlot();

signals:
    void EndSignal();

public:
    void onFileEndCBFun(int nPort);

private:
    void setAudioAndYuvPath(const QString& filePath);
    void changeUIState(DECODE_STATE decState);
    DEC_TYPE getDecodeType();
    bool openDestinationFiles(DEC_TYPE decType);
    void setCallbacks(DEC_TYPE decType);
    void play();

public:
    FILE*           m_fpOutAudioFile;
    FILE*           m_fpOutVideoFile;

private:
    Ui::DecCB_demo *ui;
    DisplayWindow   m_displayWindow;
};

#endif // DECCB_DEMO_H
