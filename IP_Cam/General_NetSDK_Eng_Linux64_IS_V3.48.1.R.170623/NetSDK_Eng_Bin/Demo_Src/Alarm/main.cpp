#include <QtGui/QApplication>
#include <QTextCodec>
#include "form1.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    Form1 w;
    w.InitForm();
    w.show();
   // a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    a.connect( &a, SIGNAL( lastWindowClosed() ), &w, SLOT( w.ButExit_clicked() ) );

    return a.exec();
}
