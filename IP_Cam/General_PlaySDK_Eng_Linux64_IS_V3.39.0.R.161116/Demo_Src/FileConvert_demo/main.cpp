#include "fileconvert_demo.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	
    FileConvert_demo w;
    w.show();
    
    return a.exec();
}
