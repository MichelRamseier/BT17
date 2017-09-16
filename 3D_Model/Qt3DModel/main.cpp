#include <QtCore/QObject>
#include <QGuiApplication>
#include "skeletonview.h"



int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    //SkeletonView* view = new SkeletonView();
    SkeletonView view;

    return app.exec();
}
