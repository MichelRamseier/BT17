#include <QApplication>
#include "dialog.h"
#include <QTextCodec>
#include "cameracontroller.h"
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtMultimedia/QMediaRecorder>
#include <QFile>
#include <QThread>
#include <QGuiApplication>

#include <Qt3DRender/qcamera.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcameralens.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtGui/QScreen>

QMediaRecorder *mediaRecorder;

void stopRecording()
{
    mediaRecorder->stop();
    qDebug() << mediaRecorder->status();
    qDebug() << mediaRecorder->state();
    qDebug() << mediaRecorder->error();
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignTop);
    //hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);



    widget->setWindowTitle(QStringLiteral("3D-Model"));
    QPushButton *removeOffsetButton = new QPushButton();
    removeOffsetButton->setText("Remove Offset");

    QPushButton *removeDriftButton = new QPushButton();
    removeDriftButton->setText("Remove Z-Axis Drift");

    vLayout->addWidget(removeOffsetButton);
    vLayout->addWidget(removeDriftButton);

    QObject::connect(removeOffsetButton, &QPushButton::clicked, stopRecording);
    QObject::connect(removeDriftButton, &QPushButton::clicked, stopRecording);

    // Show window
    widget->show();
    widget->resize(1200, 800);
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    //Dialog w;
    //w.show();
    CameraController *camController = new CameraController();
    camController->SetPosition(50, 50);
    QList<QList<double>> *points = new QList<QList<double>>();
    QList<double> *point = new QList<double>();
    point->insert(0, 12.5);
    point->insert(1, 10);
    points->append(*point);

    QStringList *cams = new QStringList();
    cams->append("192.168.1.108");

    camController->DriveCameraToPosition(*points, *cams);
//    QMediaPlayer *player = new QMediaPlayer(0, QMediaPlayer::StreamPlayback);
//    QMediaContent *mc = new QMediaContent(QUrl("http://192.168.2.108/axis-cgi/mjpg/video.cgi"));
//    player->setMedia(*mc);
//    player->setVolume(50);
//    QVideoWidget *videowidget = new QVideoWidget;
//    videowidget->resize(700,700);
//    videowidget->show();
//    player->setVideoOutput(videowidget);
//    player->play();

//    mediaRecorder = new QMediaRecorder(player);
//    QVideoEncoderSettings *videosettings = new QVideoEncoderSettings;

//    videosettings->setResolution(1280,720);
//    videosettings->setQuality(QMultimedia::VeryHighQuality);
//    videosettings->setFrameRate(25.0);
//    videosettings->setCodec("video/mpeg2");
//    mediaRecorder->setVideoSettings(*videosettings);
//    qDebug() << mediaRecorder->supportedVideoCodecs().length();
//    QString file = "record.avi";
//    QFile file1(file);
//    file1.open(QIODevice::WriteOnly);
//    mediaRecorder->setContainerFormat("avi");
//    mediaRecorder->setOutputLocation(QUrl::fromLocalFile(file));
//    mediaRecorder->record();
//    qDebug() << mediaRecorder->status();
//    qDebug() << mediaRecorder->state();
//    qDebug() << mediaRecorder->error();
    return a.exec();
}


