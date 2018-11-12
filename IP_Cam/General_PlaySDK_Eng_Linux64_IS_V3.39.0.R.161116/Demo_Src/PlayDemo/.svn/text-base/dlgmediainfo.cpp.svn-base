#include "dlgmediainfo.h"
#include "ui_dlgmediainfo.h"
#include "Player.h"

dlgMediaInfo::dlgMediaInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgMediaInfo)
{
    ui->setupUi(this);

    int len = 0;
    MEDIA_INFO tMediaInfo;
    memset(&tMediaInfo, 0, sizeof(MEDIA_INFO));
    CPlayer::Instance()->GetQueryInfo(PLAY_CMD_GetMediaInfo, (char *)&tMediaInfo, sizeof(MEDIA_INFO), &len);

    QString qsMediaInfo;

    if (tMediaInfo.lFrameRate != 0)
    {
        qsMediaInfo.append("Video Frame Rate\t\t");
        qsMediaInfo.append(QString::number(tMediaInfo.lFrameRate, 10));
        qsMediaInfo.append("\n");

        qsMediaInfo.append("Video resolution\t\t");
        qsMediaInfo.append(QString::number(tMediaInfo.lWidth, 10));
        qsMediaInfo.append("*");
        qsMediaInfo.append(QString::number(tMediaInfo.lHeight, 10));
        qsMediaInfo.append("\n\n");

    }

    if (tMediaInfo.lChannel != 0)
    {
        qsMediaInfo.append("Audio Channel\t\t");
        qsMediaInfo.append(QString::number(tMediaInfo.lChannel, 10));
        qsMediaInfo.append("\n");
#ifdef Q_OS_LINUX
        qsMediaInfo.append("Audio BitPerSample\t");
#else
        qsMediaInfo.append("Audio BitPerSample\t\t");
#endif
        qsMediaInfo.append(QString::number(tMediaInfo.lBitPerSample, 10));
        qsMediaInfo.append("\n");

        qsMediaInfo.append("Audio SamplesPerSec\t");
        qsMediaInfo.append(QString::number(tMediaInfo.lSamplesPerSec, 10));
        qsMediaInfo.append("\n");
    }

    ui->mediainfo->setText(qsMediaInfo);
}

dlgMediaInfo::~dlgMediaInfo()
{
    delete ui;
}

void dlgMediaInfo::on_btnOK_clicked()
{
    QDialog::accept();
}
