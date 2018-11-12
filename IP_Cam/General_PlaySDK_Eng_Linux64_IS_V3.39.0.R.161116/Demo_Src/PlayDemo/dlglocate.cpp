#include "dlglocate.h"
#include "ui_dlglocate.h"
#include "Player.h"
#include <QMessageBox>

dlgLocate::dlgLocate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgLocate),
    m_locateType(TYPEBYFRAME)
{
    ui->setupUi(this);

    QString str = "Frame Range\t0--";
    str.append(QString::number(CPlayer::Instance()->GetTotalFrame() - 1));
    str.append("\n");
    str.append("Time Range(Sec)\t0--");
    str.append(QString::number(CPlayer::Instance()->GetTotalTime()));
    str.append("\n");

    ui->labelShow->setText(str);

}

dlgLocate::~dlgLocate()
{
    delete ui;
}

void dlgLocate::on_btnLocate_clicked()
{
    bool isOk = false;
    int locatevaclue = (ui->inputValue->text()).toInt(&isOk);

    if (!isOk)
    {
        QMessageBox::warning(this, tr("warning"), tr("Input number error!"));
        return;
    }

    if (m_locateType == TYPEBYFRAME)
    {
        if ( locatevaclue < 0 || locatevaclue > CPlayer::Instance()->GetTotalFrame() - 1)
        {
            QMessageBox::warning(this, tr("warning"), tr("Input number error!"));
            return ;
        }

        CPlayer::Instance()->SetCurrentFrameNum(locatevaclue);
    }
    else
    {
        if (locatevaclue < 0 || locatevaclue > CPlayer::Instance()->GetTotalTime())
        {
            QMessageBox::warning(this, tr("warning"), tr("Input number error!"));
            return ;
        }

        CPlayer::Instance()->SetPlayedTiemEx(locatevaclue*1000);
    }
}

void dlgLocate::on_frameNumType_clicked()
{
     m_locateType = TYPEBYFRAME;
}

void dlgLocate::on_timeType_clicked()
{
     m_locateType = TYPEBYTIME;
}

void dlgLocate::on_btnCancel_clicked()
{
    QDialog::accept();
}
