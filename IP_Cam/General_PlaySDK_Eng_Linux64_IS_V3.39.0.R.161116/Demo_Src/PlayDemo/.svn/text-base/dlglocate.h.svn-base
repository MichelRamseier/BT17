#ifndef DLGLOCATE_H
#define DLGLOCATE_H

#include <QDialog>

namespace Ui {
class dlgLocate;
}

class dlgLocate : public QDialog
{
    Q_OBJECT
    
public:
    explicit dlgLocate(QWidget *parent = 0);
    ~dlgLocate();
    
private slots:
    void on_btnLocate_clicked();

    void on_frameNumType_clicked();

    void on_timeType_clicked();

    void on_btnCancel_clicked();

private:
    Ui::dlgLocate *ui;

public:
    typedef enum{
        TYPEBYFRAME,
        TYPEBYTIME
    }LOCATETYPE;

    int	m_locateType;
};

#endif // DLGLOCATE_H
