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
#include <QDirectionalLight>

#include <model.h>
#include <Qt3DRender/QMesh>
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

    Qt3DExtras::QPhongMaterial *phongMaterial = new Qt3DExtras::QPhongMaterial();
    phongMaterial->setDiffuse(QColor(204, 205, 75)); // Safari Yellow #cccd4b
    phongMaterial->setSpecular(Qt::white);

    Qt3DRender::QMesh *m_mesh = new Qt3DRender::QMesh();
    m_mesh->setSource(QUrl("qrc:assets/rightlowerleg.obj"));
    Qt3DCore::QEntity *test = new Qt3DCore::QEntity(sceneRoot);
    test = new Qt3DCore::QEntity(test);
    test->addComponent(m_mesh);
    test->addComponent(phongMaterial);

    Qt3DRender::QMesh *m_mesh2 = new Qt3DRender::QMesh();
    m_mesh2->setSource(QUrl("qrc:assets/leftlowerleg.obj"));
    Qt3DCore::QEntity *test2 = new Qt3DCore::QEntity(sceneRoot);
    test = new Qt3DCore::QEntity(test2);
    test->addComponent(m_mesh2);
    test->addComponent(phongMaterial);
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

    Model *model = new Model(sceneRoot);
    model->Initialize();

    model->SetCenterRotation(QQuaternion::fromAxisAndAngle(0, 0, 1, 0));
    model->SetLeftUpperArmRotation(QQuaternion::fromAxisAndAngle(0, 1, 0,45));
    model->SetLeftLowerArmRotation(QQuaternion::fromAxisAndAngle(0, 0, 1, 90));
    model->SetRightUpperArmRotation(QQuaternion::fromAxisAndAngle(0, 0, 1, -45));
    model->SetRightLowerArmRotation(QQuaternion::fromAxisAndAngle(0, 0, 1, -90));
    model->SetLeftUpperLegRotation(QQuaternion::fromAxisAndAngle(0, 0, 1, 45));
    model->SetLeftLowerLegRotation(QQuaternion::fromAxisAndAngle(0, 0, 1, 90));
    model->SetRightUpperLegRotation(QQuaternion::fromAxisAndAngle(0, 0, 1, -45));
    model->SetRightLowerLegRotation(QQuaternion::fromAxisAndAngle(0, 0, 1, -90));
    model->SetHeadRotation(QQuaternion::fromAxisAndAngle(0, 0, 1, 45));

    view.setRootEntity(sceneRoot);
    view.show();

    return app.exec();
}
