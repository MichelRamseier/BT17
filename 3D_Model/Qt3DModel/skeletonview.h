#ifndef SKELETONVIEW_H
#define SKELETONVIEW_H


#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QAspectEngine>
#include <Qt3DRender/QCamera>

#include <Qt3DInput/QInputAspect>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QDiffuseMapMaterial>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DRender/QTextureImage>

#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>
#include <QDirectionalLight>

#include <model.h>
#include <QtMath>


#include "model.h"

class SkeletonView : public QObject
{
    Q_OBJECT
public:
    SkeletonView();
    void show();

public slots:
    void vectorSample(quint64 deviceSerial, quint32 trackId,quint32 sampleNumber,QList<double> data);

private:
    void setAxis(Qt3DCore::QEntity *sceneRoot);

     Qt3DExtras::Qt3DWindow view;
     Model *model;

};

#endif // SKELETONVIEW_H