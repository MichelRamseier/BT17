#include "dlgcutfile.h"
#include "ui_dlgcutfile.h"
#include "Player.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>

dlgCutFile::dlgCutFile(QString originFile, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgCutFile),
    m_originFile(originFile),
    m_cutType(CUTBYFRAMENUM)
{
    ui->setupUi(this);

    m_nMaxTime = CPlayer::Instance()->GetTotalTime();
    m_nMaxFrameNum = CPlayer::Instance()->GetTotalFrame();

    QString str = "Frame Range\t0--";
    str.append(QString::number(m_nMaxFrameNum - 1));
    str.append("\n");
    str.append("Time Range(Sec)\t0--");
    str.append(QString::number(m_nMaxTime));
    str.append("\n");

    ui->labelShow->setText(str);
}

dlgCutFile::~dlgCutFile()
{
    delete ui;
}

void dlgCutFile::on_btnSave_clicked()
{
    bool isStartPosOk = false;
    int startPos = (ui->inputValueBegin->text()).toInt(&isStartPosOk);

    bool isEndPosOk = false;
    int endPos = (ui->inputValueEnd->text()).toInt(&isEndPosOk);

    if (!isStartPosOk || !isEndPosOk)
    {
        QMessageBox::warning(this, tr("warning"), tr("Input number error!"));
        return;
    }

    if (m_cutType == CUTBYFRAMENUM)  //By Frame number
    {
        if (startPos < 0 || startPos > m_nMaxFrameNum -1
             || endPos< 0 || endPos > m_nMaxFrameNum -1
             || startPos > endPos)
        {
             QMessageBox::warning(this, tr("warning"), tr("Input number error!"));
             return ;
        }
    }
    else
    {
        if (startPos < 0|| startPos > m_nMaxTime
            || endPos < 0|| endPos > m_nMaxTime
            || startPos > endPos)
        {
            QMessageBox::warning(this, tr("warning"), tr("Input number error!"));
            return;
        }
    }

    FRAME_POS realBegin, realEnd;
    BOOL bBefore = CPlayer::Instance()->GetKeyFramePos(startPos*((m_cutType == 0)?1:1000), m_cutType+1, &realBegin);
    BOOL bAfter = CPlayer::Instance()->GetNextKeyFramePos(endPos*((m_cutType == 0)?1:1000), m_cutType+1, &realEnd);


    QFile file_in(m_originFile);
    file_in.open(QIODevice::ReadOnly);

    DWORD newfilelen = 0;
    LONG realFileStartPos = 0;
    LONG realFileEndPos = 0;
    int realStartPos = 0;
    int realEndPos = 0;

    if ( bBefore && bAfter )
    {
        realFileStartPos = realBegin.nFilePos;
        realFileEndPos = realEnd.nFilePos;

        //newfilelen = realEnd.nFilePos - realBegin.nFilePos;

        realStartPos = (m_cutType == 0) ? (realBegin.nFrameNum):((realBegin.nFrameTime/1000));
        realEndPos = (m_cutType == 0) ? (realEnd.nFrameNum):((realEnd.nFrameTime/1000));

    }
    else if ( bBefore && !bAfter )
    {
        realFileStartPos = realBegin.nFilePos;
        realFileEndPos = file_in.size();

        realStartPos = (m_cutType == 0) ? (realBegin.nFrameNum):((realBegin.nFrameTime/1000));
        realEndPos = (m_cutType == 0) ? m_nMaxFrameNum - 1: m_nMaxTime;
    }
    else
    {
        file_in.close();
        return;
    }

    newfilelen = realFileEndPos - realFileStartPos;

    ui->realValueBegin->setText(QString::number(realStartPos, 10));
    ui->realValueEnd->setText(QString::number(realEndPos, 10));

    QString savefile = QFileDialog::getSaveFileName(this, tr("Save File"),
                                   "./untitled.dav",
                                   tr("dav Files (*.dav);;All Files (*.*)"));
    QFile file_out(savefile);
    file_out.open(QIODevice::WriteOnly);

    const int nSize = 2048;
    DWORD nBlock = newfilelen/nSize;
    char *pBuf = new char[nSize];
    memset(pBuf, 0, nSize);

    file_in.seek(realFileStartPos);

    for (DWORD i = 0 ; i < nBlock ; i++ )
    {
        file_in.read(pBuf,nSize);
        file_out.write(pBuf,nSize);
    }

    DWORD nRemain = newfilelen - nBlock*nSize;
    if (nRemain > 0)
    {
        file_in.read(pBuf,nRemain);
        file_out.write(pBuf,nRemain);
    }

    delete[] pBuf;
    file_in.close();
    file_out.close();

    /*
    QFile file_in(m_originFile);
    file_in.open(QIODevice::ReadOnly);

    DWORD newfilelen = 0;
    int realStartPos = 0;
    int realEndPos = 0;
    if (realBegin.nFrameNum > realEnd.nFrameNum)
    {
        QMessageBox::warning(this, tr("warning"), tr("Input number error!"));
        return ;
    }
    else if((m_cutType == 0 && (realEnd.nFrameNum) < endPos) ||
            (m_cutType == 1 && realEnd.nFrameTime < ((endPos)*1000)))
    {
        // This situation usually happens when cut last few frames.
        newfilelen = file_in.size() - realBegin.nFilePos;
        realEndPos = (m_cutType == 0)?(m_nMaxFrameNum-1):m_nMaxTime;
    }
    else
    {
        realEndPos = (m_cutType == 0)?(realEnd.nFrameNum):((realEnd.nFrameTime/1000));
        newfilelen = realEnd.nFilePos+ realEnd.nFrameLen - realBegin.nFilePos ;
    }

    realStartPos = (m_cutType == 0)?(realBegin.nFrameNum):(realBegin.nFrameTime/1000);
    ui->realValueBegin->setText(QString::number(realStartPos, 10));
    ui->realValueEnd->setText(QString::number(realEndPos, 10));

    QString savefile = QFileDialog::getSaveFileName(this, tr("Save File"),
                                   "./untitled.dav",
                                   tr("dav Files (*.dav);;All Files (*.*)"));
    QFile file_out(savefile);
    file_out.open(QIODevice::WriteOnly);

    const int nSize = 2048;
    DWORD nBlock = newfilelen/nSize;
    char *pBuf = new char[nSize];
    memset(pBuf, 0, nSize);

    if (realBegin.nFilePos < (1<<31))
        file_in.seek(realBegin.nFilePos);
    else
    {
        bool ret = file_in.seek(realBegin.nFilePos/2);
        ret = file_in.seek(realBegin.nFilePos);
    }

    for (DWORD i = 0 ; i < nBlock ; i++ )
    {
        file_in.read(pBuf,nSize);
        file_out.write(pBuf,nSize);
    }

    DWORD nRemain = newfilelen - nBlock*nSize;
    if (nRemain > 0)
    {
        file_in.read(pBuf,nRemain);
        file_out.write(pBuf,nRemain);
    }

    file_out.close();
    */
}

void dlgCutFile::on_frameNumType_clicked()
{
    m_cutType = CUTBYFRAMENUM;
}

void dlgCutFile::on_timeType_clicked()
{
    m_cutType = CUTBYTIME;
}

void dlgCutFile::on_btnCancel_clicked()
{
    QDialog::accept();
}
