#include <QApplication>
#include "dialog.h"
#include <QTextCodec>
#include "cameracontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    //Dialog w;
    //w.show();
    CameraController *camController = new CameraController();
    camController->SetPosition(0,10);
    return a.exec();
}
