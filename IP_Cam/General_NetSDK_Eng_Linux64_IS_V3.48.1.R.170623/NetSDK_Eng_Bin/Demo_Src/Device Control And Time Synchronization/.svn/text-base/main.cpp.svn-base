#include <QtGui/QApplication>
#include "dialog.h"
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    Dialog w;
    w.show();

    return a.exec();
}
