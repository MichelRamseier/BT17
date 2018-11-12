#include "dlgsetcolor.h"
#include "ui_dlgsetcolor.h"
#include "Player.h"

dlgSetColor::dlgSetColor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSetColor),
    m_iSaturation(0),
    m_iBright(0),
    m_iContrast(0),
    m_iHue(0)
{
    ui->setupUi(this);
    ui->saturation->setRange(0, 128);
    ui->brightness->setRange(0, 128);
    ui->contrast->setRange(0, 128);
    ui->hue->setRange(0, 128);

    CPlayer::Instance()->GetColor(&m_iSaturation, &m_iBright, &m_iContrast, &m_iHue);
    ui->saturation->setValue(m_iSaturation);
    ui->brightness->setValue(m_iBright);
    ui->contrast->setValue(m_iContrast);
    ui->hue->setValue(m_iHue);

    QObject::connect(ui->saturation, SIGNAL(valueChanged(int)), this, SLOT(OnSaturationValueChanged(int)));
    QObject::connect(ui->brightness, SIGNAL(valueChanged(int)), this, SLOT(OnBrightValueChanged(int)));
    QObject::connect(ui->contrast, SIGNAL(valueChanged(int)), this, SLOT(OnContrastValueChanged(int)));
    QObject::connect(ui->hue, SIGNAL(valueChanged(int)), this, SLOT(OnHueValueChanged(int)));
}

dlgSetColor::~dlgSetColor()
{
    delete ui;
}


void dlgSetColor::OnSaturationValueChanged(int pos)
{
    m_iSaturation = pos;

    CPlayer::Instance()->SetColor(m_iSaturation, m_iBright, m_iContrast, m_iHue);
}

void dlgSetColor::OnBrightValueChanged(int pos)
{
    m_iBright = pos;

    CPlayer::Instance()->SetColor(m_iSaturation, m_iBright, m_iContrast, m_iHue);
}

void dlgSetColor::OnContrastValueChanged(int pos)
{
    m_iContrast = pos;

    CPlayer::Instance()->SetColor(m_iSaturation, m_iBright, m_iContrast, m_iHue);
}

void dlgSetColor::OnHueValueChanged(int pos)
{
    m_iHue = pos;

    CPlayer::Instance()->SetColor(m_iSaturation, m_iBright, m_iContrast, m_iHue);

}

void dlgSetColor::on_btnOK_clicked()
{
    QDialog::accept();
}
