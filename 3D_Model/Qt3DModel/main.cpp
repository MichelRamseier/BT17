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
Qt3DExtras::QCylinderMesh *bodyMesh;

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
    bodyMesh = new Qt3DExtras::QCylinderMesh();
    bodyMesh->setRadius(0.1f);
    bodyMesh->setLength(6);
    bodyMesh->setRings(100);
    bodyMesh->setSlices(20);

    modelMesh = new Qt3DExtras::QCylinderMesh();
    modelMesh->setRadius(0.1f);
    modelMesh->setLength(3);
    modelMesh->setRings(10);
    modelMesh->setSlices(20);

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

    //x, y, z
    QVector3D offsetT = QVector3D(-1.5, 0, 0);
    QVector3D lfT = QVector3D(0,3,0);
    QVector3D laOffsetT = QVector3D(-3,0,0);

    QMatrix4x4 lfTM = GetTranslationMatrix(lfT.x(), lfT.y(), lfT.z());
    QMatrix4x4 laOffsetTM = GetTranslationMatrix(laOffsetT.x(), laOffsetT.y(), laOffsetT.z());
    QMatrix4x4 offsetTM = GetTranslationMatrix(offsetT.x(), offsetT.y(), offsetT.z());

    QMatrix4x4 offsetRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,90).toRotationMatrix());
    QMatrix4x4 lfRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,1,0,20).toRotationMatrix());
    QMatrix4x4 laRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,10).toRotationMatrix());

    leftForearmTransform->setMatrix(lfTM*lfRM*offsetTM*offsetRM);
    leftArmTransform->setMatrix(lfTM*lfRM*laOffsetTM*laRM*lfRM.inverted()*offsetTM*offsetRM);









    Qt3DExtras::QPhongMaterial *modelMaterial = new Qt3DExtras::QPhongMaterial();
    modelMaterial->setDiffuse(QColor(QRgb(0x00FF00)));

    Qt3DCore::QEntity *bodyEntity = new Qt3DCore::QEntity(sceneRoot);
    bodyEntity = new Qt3DCore::QEntity(bodyEntity);
    bodyEntity->addComponent(modelMesh);
    bodyEntity->addComponent(modelMaterial);
    bodyEntity->addComponent(leftForearmTransform);


    // Cylinder
    Qt3DCore::QEntity *leftForearmEntity = new Qt3DCore::QEntity(sceneRoot);
    leftForearmEntity = new Qt3DCore::QEntity(leftForearmEntity);
    leftForearmEntity->addComponent(bodyMesh);
    leftForearmEntity->addComponent(modelMaterial);
    leftForearmEntity->addComponent(bodyTransform);
    //m_cylinderEntity->setParent(bodyEntity);

    Qt3DCore::QEntity *leftArmEntity = new Qt3DCore::QEntity(sceneRoot);
    leftArmEntity = new Qt3DCore::QEntity(leftArmEntity);
    leftArmEntity->addComponent(modelMesh);
    leftArmEntity->addComponent(modelMaterial);
    leftArmEntity->addComponent(leftArmTransform);
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

    // Cylinder shape data
//    Qt3DExtras::QCylinderMesh *cylinder = new Qt3DExtras::QCylinderMesh();
//    cylinder->setRadius(0.5f);
//    cylinder->setLength(3);
//    cylinder->setRings(100);
//    cylinder->setSlices(20);

//    Qt3DExtras::QCylinderMesh *cylinder2 = new Qt3DExtras::QCylinderMesh();
//    cylinder2->setRadius(0.5f);
//    cylinder2->setLength(3);
//    cylinder2->setRings(100);
//    cylinder2->setSlices(20);

//    Qt3DCore::QTransform *cylinderTransform = new Qt3DCore::QTransform();
//    QVector3D translation = QVector3D(3,0,0);
//    QMatrix4x4 translationMatrix = QMatrix4x4(1,0,0,translation.x()
//                                             ,0,1,0,translation.y()
//                                             ,0,0,1,translation.z()
//                                             ,0,0,0,1);

//    //3x3 Matrix will automatically converted to 4x4
//    QMatrix4x4 rotationMatrix = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,90).toRotationMatrix());
//    cylinderTransform->setMatrix(rotationMatrix*translationMatrix);

//    Qt3DCore::QTransform *cylinderTransform2 = new Qt3DCore::QTransform();
//    QVector3D translation2 = QVector3D(10,10,10);
//    QMatrix4x4 translationMatrix2 = QMatrix4x4(1,0,0,translation2.x()
//                                             ,0,1,0,translation2.y()
//                                             ,0,0,1,translation2.z()
//                                             ,0,0,0,1);

//    //3x3 Matrix will automatically converted to 4x4
//    QMatrix4x4 rotationMatrix2 = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,0).toRotationMatrix());
//    cylinderTransform2->setMatrix(rotationMatrix2*translationMatrix2);



//    Qt3DExtras::QPhongMaterial *cylinderMaterial = new Qt3DExtras::QPhongMaterial();
//    cylinderMaterial->setDiffuse(QColor(QRgb(0x928327)));



//    Qt3DCore::QEntity *bodyEntity = new Qt3DCore::QEntity(sceneRoot);
//    bodyEntity = new Qt3DCore::QEntity(bodyEntity);
//    bodyEntity->addComponent(cylinder);
//    bodyEntity->addComponent(cylinderMaterial);
//    bodyEntity->addComponent(cylinderTransform2);


//    // Cylinder
//    Qt3DCore::QEntity *m_cylinderEntity = new Qt3DCore::QEntity(sceneRoot);
//    m_cylinderEntity = new Qt3DCore::QEntity(m_cylinderEntity);
//    m_cylinderEntity->addComponent(cylinder);
//    m_cylinderEntity->addComponent(cylinderMaterial);
//    m_cylinderEntity->addComponent(cylinderTransform);
//    m_cylinderEntity->setParent(bodyEntity);


    // Cylinder2
//    Qt3DCore::QEntity *m_cylinderEntity2 = new Qt3DCore::QEntity(sceneRoot);
//    m_cylinderEntity2 = new Qt3DCore::QEntity(m_cylinderEntity2);
//    m_cylinderEntity2->addComponent(cylinder2);
//    m_cylinderEntity2->addComponent(cylinderMaterial);
//    m_cylinderEntity2->addComponent(cylinder2Transform);

    setAxis(sceneRoot);
    CreateModel(sceneRoot);
    view.setRootEntity(sceneRoot);
    view.show();

    return app.exec();
}
