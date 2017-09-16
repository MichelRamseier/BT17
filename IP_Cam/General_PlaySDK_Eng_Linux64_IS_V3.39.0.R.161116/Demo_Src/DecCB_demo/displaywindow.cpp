#include "displaywindow.h"
#include "ui_displaywindow.h"

DisplayWindow::DisplayWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowTitleHint);
}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}
