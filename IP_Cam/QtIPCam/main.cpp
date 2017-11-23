#include <QApplication>
#include "dialog.h"
#include <QTextCodec>
#include "cameracontroller.h"
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimediaWidgets/QVideoWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    //Dialog w;
    //w.show();
    CameraController *camController = new CameraController();
    camController->SetPosition(50, 50);
    camController->DriveCameraToPosition(0,0);
    QMediaPlayer *player = new QMediaPlayer();
    QMediaContent *mc = new QMediaContent(QUrl("http://192.168.1.108/axis-cgi/mjpg/video.cgi"));
    player->setMedia(*mc);
    player->setVolume(50);
    QVideoWidget *videowidget = new QVideoWidget;
    videowidget->resize(700,700);
    videowidget->show();
    player->setVideoOutput(videowidget);
    player->play();
    return a.exec();
}
