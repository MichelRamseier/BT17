#ifndef DLGSETCOLOR_H
#define DLGSETCOLOR_H

#include <QDialog>

namespace Ui {
class dlgSetColor;
}

class dlgSetColor : public QDialog
{
    Q_OBJECT
    
public:
    explicit dlgSetColor(QWidget *parent = 0);
    ~dlgSetColor();
    
private:
    Ui::dlgSetColor *ui;
    int m_iSaturation;
    int m_iBright;
    int m_iContrast;
    int m_iHue;

private slots:
    void OnSaturationValueChanged(int pos);
    void OnBrightValueChanged(int pos);
    void OnContrastValueChanged(int pos);
    void OnHueValueChanged(int pos);
    void on_btnOK_clicked();
};

#endif // DLGSETCOLOR_H
