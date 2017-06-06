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
    Qt3DExtras::QCylinderMesh *cylinder = new Qt3DExtras::QCylinderMesh();
    cylinder->setRadius(0.5f);
    cylinder->setLength(3);
    cylinder->setRings(100);
    cylinder->setSlices(20);

    Qt3DExtras::QCylinderMesh *cylinder2 = new Qt3DExtras::QCylinderMesh();
    cylinder2->setRadius(0.5f);
    cylinder2->setLength(3);
    cylinder2->setRings(100);
    cylinder2->setSlices(20);

    //evtl. auch mit quaternion rotieren, die rotation auf einen punkt anwenden, dann verschieben

    Qt3DCore::QTransform *cylinderTransform = new Qt3DCore::QTransform();
    //cylinderTransform->setScale(1.5f);
    QVector3D armShoulder = QVector3D(0, cylinder->length()/2,0);
    QVector3D armForearm = QVector3D(0,-1 * cylinder->length()/2, 0);
    QMatrix4x4 armRotation = cylinderTransform->rotateAround(armShoulder, 90, QVector3D(0,0,1));
    cylinderTransform->setMatrix(armRotation);

    armForearm = armRotation * armForearm;

    Qt3DCore::QTransform *cylinder2Transform = new Qt3DCore::QTransform();
    QVector3D test = QVector3D(0,cylinder->length()/2,0);
    //QMatrix4x4 forearmRotation = cylinderTransform->rotateAround(test, -90, QVector3D(0,0,1));
    cylinder2Transform->setRotation(QQuaternion::fromAxisAndAngle(0,0,1,-45));
    QMatrix3x3 rotationBasic = cylinder2Transform->rotation().toRotationMatrix();
    //QMatrix4x4 translationBasic = QMatrix4x4(1,0,0,armForearm.x()
       //                                      ,0,1,0,armForearm.y()
         //                                    ,0,0,1,armForearm.z()
         //                                    ,0,0,0,1);


    QMatrix4x4 rotationBasicPlus = QMatrix4x4(rotationBasic);
    test = rotationBasicPlus * test;
    cylinder2Transform->setTranslation(armForearm+test);
    //QMatrix4x4 matrix = QMatrix4x4(1,0,0,0,0,qCos())
    //cylinder2Transform->setMatrix(translationBasic*rotationBasicPlus);


    //qDebug() <<  armForearm.x() + " " + armForearm.y() + " " + armForearm.z();
    //cylinderTransform->setTranslation(QVector3D(5,5,5));
    //cylinderTransform->setTranslation(QVector3D(cylinder->length()/2, 0, 0));
    //cylinderTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), 45.0f));


    Qt3DExtras::QPhongMaterial *cylinderMaterial = new Qt3DExtras::QPhongMaterial();
    cylinderMaterial->setDiffuse(QColor(QRgb(0x928327)));

    // Cylinder
    Qt3DCore::QEntity *m_cylinderEntity = new Qt3DCore::QEntity(sceneRoot);
    m_cylinderEntity = new Qt3DCore::QEntity(m_cylinderEntity);
    m_cylinderEntity->addComponent(cylinder);
    m_cylinderEntity->addComponent(cylinderMaterial);
    m_cylinderEntity->addComponent(cylinderTransform);

    // Cylinder2
    Qt3DCore::QEntity *m_cylinderEntity2 = new Qt3DCore::QEntity(sceneRoot);
    m_cylinderEntity2 = new Qt3DCore::QEntity(m_cylinderEntity2);
    m_cylinderEntity2->addComponent(cylinder2);
    m_cylinderEntity2->addComponent(cylinderMaterial);
    m_cylinderEntity2->addComponent(cylinder2Transform);

    setAxis(sceneRoot);
    view.setRootEntity(sceneRoot);
    view.show();

    return app.exec();
}
