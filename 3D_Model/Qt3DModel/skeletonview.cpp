#include "skeletonview.h"

// FIXME: Properly integrate Axiamo Enumerations
#define Quat6 0x0140

SkeletonView::SkeletonView()
{
}

void SkeletonView::show(){


    // Scene Root
    Qt3DCore::QEntity *sceneRoot = new Qt3DCore::QEntity();

    // Scene Camera
    Qt3DRender::QCamera *basicCamera = view.camera();
    basicCamera->setProjectionType(Qt3DRender::QCameraLens::PerspectiveProjection);
    basicCamera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
    basicCamera->setViewCenter(QVector3D(0.0f, 3.5f, 0.0f));
    basicCamera->setPosition(QVector3D(0.0f, 3.5f, 300.0f));

    // For camera controls
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(sceneRoot);
    camController->setCamera(basicCamera);


    setAxis(sceneRoot);
    model = new Model(sceneRoot);
    model->Initialize();

    model->SetCenterRotation(QQuaternion::fromAxisAndAngle(1, 0, 0, 0));
//    model->SetLeftUpperArmRotation(QQuaternion::fromAxisAndAngle(0, 0, 1, -45));
//    model->SetLeftLowerArmRotation(QQuaternion::fromAxisAndAngle(0, 0, 1, -45));
//    model->SetRightUpperArmRotation(QQuaternion::fromAxisAndAngle(0, 0, 1, 45));
//    model->SetRightLowerArmRotation(QQuaternion::fromAxisAndAngle(0, 0, 1, 45));
//    model->SetLeftUpperLegRotation(QQuaternion::fromAxisAndAngle(0, 0, 1, -45));
//    model->SetLeftLowerLegRotation(QQuaternion::fromAxisAndAngle(0, 0, 1, -45));
//    model->SetRightUpperLegRotation(QQuaternion::fromAxisAndAngle(0, 0, 1, 45));
//    model->SetRightLowerLegRotation(QQuaternion::fromAxisAndAngle(0, 0, 1, 45));
//    model->SetHeadRotation(QQuaternion::fromAxisAndAngle(0, 0, 1, 45));

    view.setRootEntity(sceneRoot);
    view.show();


}

void SkeletonView::vectorSample(quint64 deviceSerial, quint32 trackId, quint32 sampleNumber, QList<double> data)
{
    if(trackId == Quat6){
        if(data.size() >= 4){
            //QQuaternion rotation(data[0],data[1],data[2],data[3]);
            QQuaternion rotation(data[0],data[1],data[3],data[2]);

            //QQuaternion rotation(data[0],data[1],-data[3],data[2]);
            //QQuaternion rotation(data[0],data[3],data[2],data[1]);
            //QQuaternion rotation(data[0],data[2],data[1],data[3]);
            model->SetLeftLowerArmRotation(rotation);
        }
    }

}

void SkeletonView::setAxis(Qt3DCore::QEntity *sceneRoot)
{
    Qt3DExtras::QCylinderMesh *axisX = new Qt3DExtras::QCylinderMesh();
    axisX->setRadius(0.01f);
    axisX->setLength(100);

    Qt3DExtras::QCylinderMesh *axisY = new Qt3DExtras::QCylinderMesh();
    axisY->setRadius(0.01f);
    axisY->setLength(100);

    Qt3DExtras::QCylinderMesh *axisZ = new Qt3DExtras::QCylinderMesh();
    axisZ->setRadius(0.01f);
    axisZ->setLength(100);

    Qt3DExtras::QPhongMaterial *axisMaterial = new Qt3DExtras::QPhongMaterial();
    axisMaterial->setDiffuse(QColor(QRgb(0x000000)));

    Qt3DCore::QTransform *axisYtransform = new Qt3DCore::QTransform();
    axisYtransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), 90.0f));

    Qt3DCore::QTransform *axisZtransform = new Qt3DCore::QTransform();
    axisZtransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 90.0f));

    Qt3DCore::QEntity *axisXEntity = new Qt3DCore::QEntity(sceneRoot);
    axisXEntity = new Qt3DCore::QEntity(axisXEntity);
    axisXEntity->addComponent(axisX);
    axisXEntity->addComponent(axisMaterial);

    Qt3DCore::QEntity *axisYEntity = new Qt3DCore::QEntity(sceneRoot);
    axisYEntity = new Qt3DCore::QEntity(axisYEntity);
    axisYEntity->addComponent(axisY);
    axisYEntity->addComponent(axisMaterial);
    axisYEntity->addComponent(axisYtransform);

    Qt3DCore::QEntity *axisZEntity = new Qt3DCore::QEntity(sceneRoot);
    axisZEntity = new Qt3DCore::QEntity(axisZEntity);
    axisZEntity->addComponent(axisZ);
    axisZEntity->addComponent(axisMaterial);
    axisZEntity->addComponent(axisZtransform);


}
