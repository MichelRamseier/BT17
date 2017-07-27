#include <QtCore/QObject>

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>

#include <QGuiApplication>

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

#include <QtMath>

Qt3DExtras::QCylinderMesh *modelMesh;
Qt3DExtras::QCylinderMesh *centerMesh;
Qt3DExtras::QSphereMesh *headMesh;

Qt3DCore::QTransform *bodyTransform;
Qt3DCore::QTransform *leftForearmTransform;
Qt3DCore::QTransform *leftArmTransform;
Qt3DCore::QTransform *leftThighTransform;
Qt3DCore::QTransform *leftLegTransform;
Qt3DCore::QTransform *rightForearmTransform;
Qt3DCore::QTransform *rightArmTransform;
Qt3DCore::QTransform *rightThighTransform;
Qt3DCore::QTransform *rightLegTransform;
Qt3DCore::QTransform *headTransform;

void setAxis(Qt3DCore::QEntity *sceneRoot)
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

QMatrix4x4 GetTranslationMatrix(float x, float y, float z)
{
    return QMatrix4x4(1,0,0,x
                      ,0,1,0,y
                      ,0,0,1,z
                      ,0,0,0,1);
}

void CreateModel(Qt3DCore::QEntity *sceneRoot)
{
    float centerLength = 4;
    centerMesh = new Qt3DExtras::QCylinderMesh();
    centerMesh->setRadius(0.2f);
    centerMesh->setLength(centerLength);
    centerMesh->setRings(100);
    centerMesh->setSlices(20);

    float bodyPartLength = 2;
    modelMesh = new Qt3DExtras::QCylinderMesh();
    modelMesh->setRadius(0.2f);
    modelMesh->setLength(bodyPartLength);
    modelMesh->setRings(10);
    modelMesh->setSlices(20);

    headMesh = new Qt3DExtras::QSphereMesh();
    headMesh->setRadius(0.5);

    bodyTransform = new Qt3DCore::QTransform();
    leftForearmTransform = new Qt3DCore::QTransform();
    leftArmTransform = new Qt3DCore::QTransform();
    leftThighTransform = new Qt3DCore::QTransform();
    leftLegTransform = new Qt3DCore::QTransform();
    rightForearmTransform = new Qt3DCore::QTransform();
    rightArmTransform = new Qt3DCore::QTransform();
    rightThighTransform = new Qt3DCore::QTransform();
    rightLegTransform = new Qt3DCore::QTransform();
    headTransform = new Qt3DCore::QTransform();

    QVector3D offsetT = QVector3D(0, bodyPartLength/2, 0);
    QVector3D laT = QVector3D(0, centerLength/2, 0);
    QVector3D raT = QVector3D(0, centerLength/2, 0);
    QVector3D ltT = QVector3D(0, (centerLength/2)*-1, 0);
    QVector3D rtT = QVector3D(0, (centerLength/2)*-1, 0);
    QVector3D lfaOffsetT = QVector3D(0, bodyPartLength, 0);
    QVector3D rfaOffsetT = QVector3D(0, bodyPartLength, 0);
    QVector3D llOffsetT = QVector3D(0, bodyPartLength, 0);
    QVector3D rlOffsetT = QVector3D(0, bodyPartLength, 0);
    QVector3D headOffsetT = QVector3D(0, 4, 0);

    QMatrix4x4 offsetTM = GetTranslationMatrix(offsetT.x(), offsetT.y(), offsetT.z());

    //upper body
    QMatrix4x4 laTM = GetTranslationMatrix(laT.x(), laT.y(), laT.z());
    QMatrix4x4 lfaOffsetTM = GetTranslationMatrix(lfaOffsetT.x(), lfaOffsetT.y(), lfaOffsetT.z());
    QMatrix4x4 raTM = GetTranslationMatrix(raT.x(), raT.y(), raT.z());
    QMatrix4x4 rfaOffsetTM = GetTranslationMatrix(rfaOffsetT.x(), rfaOffsetT.y(), rfaOffsetT.z());

    QMatrix4x4 laRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,90).toRotationMatrix());
    QMatrix4x4 lfaRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,75).toRotationMatrix());
    QMatrix4x4 raRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,-90).toRotationMatrix());
    QMatrix4x4 rfaRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,-75).toRotationMatrix());

    //lower body
    QMatrix4x4 ltTM = GetTranslationMatrix(ltT.x(), ltT.y(), ltT.z());
    QMatrix4x4 llOffsetTM = GetTranslationMatrix(llOffsetT.x(), llOffsetT.y(), llOffsetT.z());
    QMatrix4x4 rtTM = GetTranslationMatrix(rtT.x(), rtT.y(), rtT.z());
    QMatrix4x4 rlOffsetTM = GetTranslationMatrix(rlOffsetT.x(), rlOffsetT.y(), rlOffsetT.z());

    QMatrix4x4 ltRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,140).toRotationMatrix());
    QMatrix4x4 llRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,160).toRotationMatrix());
    QMatrix4x4 rtRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,-140).toRotationMatrix());
    QMatrix4x4 rlRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,-160).toRotationMatrix());

    //center
    QMatrix4x4 centerRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,0).toRotationMatrix());

    //head
    QMatrix4x4 headOffsetTM = GetTranslationMatrix(headOffsetT.x(), headOffsetT.y(), headOffsetT.z());

    //root
    bodyTransform->setMatrix(centerRM);

    //subelements
    leftArmTransform->setMatrix(laTM*centerRM.inverted()*laRM*offsetTM);
    rightArmTransform->setMatrix(raTM*centerRM.inverted()*raRM*offsetTM);
    leftThighTransform->setMatrix(ltTM*centerRM.inverted()*ltRM*offsetTM);
    rightThighTransform->setMatrix(rtTM*centerRM.inverted()*rtRM*offsetTM);
    headTransform->setMatrix(headOffsetTM);

    //subsubelements
    leftForearmTransform->setMatrix(lfaOffsetTM*offsetTM.inverted()*laRM.inverted()*lfaRM*offsetTM);
    rightForearmTransform->setMatrix(rfaOffsetTM*offsetTM.inverted()*raRM.inverted()*rfaRM*offsetTM);
    leftLegTransform->setMatrix(llOffsetTM*offsetTM.inverted()*ltRM.inverted()*llRM*offsetTM);
    rightLegTransform->setMatrix(rlOffsetTM*offsetTM.inverted()*rtRM.inverted()*rlRM*offsetTM);

    Qt3DExtras::QPhongMaterial *modelMaterial = new Qt3DExtras::QPhongMaterial();
    modelMaterial->setDiffuse(QColor(QRgb(0x00FF00)));

    Qt3DCore::QEntity *centerEntity = new Qt3DCore::QEntity(sceneRoot);
    centerEntity = new Qt3DCore::QEntity(centerEntity);
    centerEntity->addComponent(centerMesh);
    centerEntity->addComponent(modelMaterial);
    centerEntity->addComponent(bodyTransform);

    Qt3DCore::QEntity *leftArmEntity = new Qt3DCore::QEntity(sceneRoot);
    leftArmEntity = new Qt3DCore::QEntity(leftArmEntity);
    leftArmEntity->addComponent(modelMesh);
    leftArmEntity->addComponent(modelMaterial);
    leftArmEntity->addComponent(leftArmTransform);
    leftArmEntity->setParent(centerEntity);

    Qt3DCore::QEntity *leftForearmEntity = new Qt3DCore::QEntity(sceneRoot);
    leftForearmEntity = new Qt3DCore::QEntity(leftForearmEntity);
    leftForearmEntity->addComponent(modelMesh);
    leftForearmEntity->addComponent(modelMaterial);
    leftForearmEntity->addComponent(leftForearmTransform);
    leftForearmEntity->setParent(leftArmEntity);

    Qt3DCore::QEntity *rightArmEntity = new Qt3DCore::QEntity(sceneRoot);
    rightArmEntity = new Qt3DCore::QEntity(rightArmEntity);
    rightArmEntity->addComponent(modelMesh);
    rightArmEntity->addComponent(modelMaterial);
    rightArmEntity->addComponent(rightArmTransform);
    rightArmEntity->setParent(centerEntity);

    Qt3DCore::QEntity *rightForearmEntity = new Qt3DCore::QEntity(sceneRoot);
    rightForearmEntity = new Qt3DCore::QEntity(rightForearmEntity);
    rightForearmEntity->addComponent(modelMesh);
    rightForearmEntity->addComponent(modelMaterial);
    rightForearmEntity->addComponent(rightForearmTransform);
    rightForearmEntity->setParent(rightArmEntity);

    Qt3DCore::QEntity *leftThighEntity = new Qt3DCore::QEntity(sceneRoot);
    leftThighEntity = new Qt3DCore::QEntity(leftThighEntity);
    leftThighEntity->addComponent(modelMesh);
    leftThighEntity->addComponent(modelMaterial);
    leftThighEntity->addComponent(leftThighTransform);
    leftThighEntity->setParent(centerEntity);

    Qt3DCore::QEntity *leftLegEntity = new Qt3DCore::QEntity(sceneRoot);
    leftLegEntity = new Qt3DCore::QEntity(leftLegEntity);
    leftLegEntity->addComponent(modelMesh);
    leftLegEntity->addComponent(modelMaterial);
    leftLegEntity->addComponent(leftLegTransform);
    leftLegEntity->setParent(leftThighEntity);

    Qt3DCore::QEntity *rightThighEntity = new Qt3DCore::QEntity(sceneRoot);
    rightThighEntity = new Qt3DCore::QEntity(rightThighEntity);
    rightThighEntity->addComponent(modelMesh);
    rightThighEntity->addComponent(modelMaterial);
    rightThighEntity->addComponent(rightThighTransform);
    rightThighEntity->setParent(centerEntity);

    Qt3DCore::QEntity *rightLegEntity = new Qt3DCore::QEntity(sceneRoot);
    rightLegEntity = new Qt3DCore::QEntity(rightLegEntity);
    rightLegEntity->addComponent(modelMesh);
    rightLegEntity->addComponent(modelMaterial);
    rightLegEntity->addComponent(rightLegTransform);
    rightLegEntity->setParent(rightThighEntity);

    Qt3DCore::QEntity *headEntity = new Qt3DCore::QEntity(sceneRoot);
    headEntity = new Qt3DCore::QEntity(headEntity);
    headEntity->addComponent(headMesh);
    headEntity->addComponent(modelMaterial);
    headEntity->addComponent(headTransform);
    headEntity->setParent(centerEntity);
}

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    Qt3DExtras::Qt3DWindow view;

    // Scene Root
    Qt3DCore::QEntity *sceneRoot = new Qt3DCore::QEntity();

    // Scene Camera
    Qt3DRender::QCamera *basicCamera = view.camera();
    basicCamera->setProjectionType(Qt3DRender::QCameraLens::PerspectiveProjection);
    basicCamera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
    basicCamera->setViewCenter(QVector3D(0.0f, 3.5f, 0.0f));
    basicCamera->setPosition(QVector3D(0.0f, 3.5f, 25.0f));
    // For camera controls
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(sceneRoot);
    camController->setCamera(basicCamera);

    setAxis(sceneRoot);
    CreateModel(sceneRoot);
    view.setRootEntity(sceneRoot);
    view.show();

    return app.exec();
}
