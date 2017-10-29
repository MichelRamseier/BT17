#include "skeletonview.h"

// FIXME: Properly integrate Axiamo Enumerations
#define Quat6 0x0140
#define Quat9 0x0141

bool initialization = true;
QQuaternion invertedZAxisRotation;
QQuaternion currentQuaternion;

SkeletonView::SkeletonView()
{
}

void SkeletonView::show(){
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
    QWidget *container = QWidget::createWindowContainer(view);
    QSize screenSize = view->screen()->size();
    container->setMinimumSize(QSize(200, 100));
    container->setMaximumSize(screenSize);

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignTop);
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);

    widget->setWindowTitle(QStringLiteral("3D-Model"));

    Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect;
    view->registerAspect(input);

    // Root entity
    Qt3DCore::QEntity *sceneRoot = new Qt3DCore::QEntity();

    // Camera
    Qt3DRender::QCamera *cameraEntity = view->camera();

    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(0, 0, -20.0f));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(sceneRoot);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(cameraEntity->position());
    lightEntity->addComponent(lightTransform);

    // Set root object of the scene
    view->setRootEntity(sceneRoot);

    // Scene Camera
    Qt3DRender::QCamera *basicCamera = view->camera();
    basicCamera->setProjectionType(Qt3DRender::QCameraLens::PerspectiveProjection);
    basicCamera->setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
    basicCamera->setViewCenter(QVector3D(0.0f, 3.5f, 0.0f));
    basicCamera->setPosition(QVector3D(0.0f, 3.5f, -100.0f));

    // For camera controls
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(sceneRoot);
    camController->setCamera(cameraEntity);



    Qt3DExtras::QPhongMaterial *modelMaterial = new Qt3DExtras::QPhongMaterial();
    modelMaterial->setDiffuse(QColor(QRgb(0x34F247)));


//    this->testTransform = new Qt3DCore::QTransform();
//    Qt3DExtras::QCuboidMesh *testMesh = new Qt3DExtras::QCuboidMesh();
//    testMesh->setXExtent(10);
//    testMesh->setYExtent(40);
//    testMesh->setZExtent(20);
    //    Qt3DCore::QEntity *testEntity = new Qt3DCore::QEntity(sceneRoot);
    //    testEntity = new Qt3DCore::QEntity(testEntity);
    //    testEntity->addComponent(testMesh);
    //    testEntity->addComponent(modelMaterial);
    //    testEntity->addComponent(this->testTransform);




    setAxis(sceneRoot);

    modelOffsetRotation = QQuaternion::fromAxisAndAngle(0, 1, 0, 180);
    model = new Model(sceneRoot);
    model->Initialize();

    model->SetCenterRotation(modelOffsetRotation);
    model->SetLeftUpperArmRotation(modelOffsetRotation);
    model->SetLeftLowerArmRotation(modelOffsetRotation);
    model->SetRightUpperArmRotation(modelOffsetRotation);
    model->SetRightLowerArmRotation(modelOffsetRotation);
    model->SetLeftUpperLegRotation(modelOffsetRotation);
    model->SetLeftLowerLegRotation(modelOffsetRotation);
    model->SetRightUpperLegRotation(modelOffsetRotation);
    model->SetRightLowerLegRotation(modelOffsetRotation);
    model->SetHeadRotation(modelOffsetRotation);

    QPushButton *calibrateButton = new QPushButton();
    calibrateButton->setText("Remove Offset");

    QPushButton *resetDriftButton = new QPushButton();
    resetDriftButton->setText("Reset z-Axis Drift");

    vLayout->addWidget(calibrateButton);
    vLayout->addWidget(resetDriftButton);

    QObject::connect(calibrateButton, &QPushButton::clicked, this, &SkeletonView::calibrate);
    QObject::connect(resetDriftButton, &QPushButton::clicked, this, &SkeletonView::resetZaxisDrift);

    // Show window
    widget->show();
    widget->resize(1200, 800);
}

void SkeletonView::vectorSample(quint64 deviceSerial, quint32 trackId, quint32 sampleNumber, QList<double> data)
{
    //sensor hat eine "initial" position
    if(trackId == Quat9)
    {
        if(data.size() >= 4)
        {
            //      |z /
            //      | /
            //      |/
            //-------------y
            //     /|
            //    / |
            //   /x |

            QQuaternion rotation(data[0], data[1], -data[3], data[2]);
            currentQuaternion = rotation;
            //currentQuaternionWithOffsetCorrection =

            rotation = rotation * invertedSensorOffsetRotation * modelOffsetRotation;

            model->SetLeftLowerArmRotation(rotation);
//            QMatrix4x4 rotationMatrix = QMatrix4x4(rotation.toRotationMatrix());
//            this->testTransform->setMatrix(rotationMatrix);
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

void SkeletonView::calibrate()
{
    invertedSensorOffsetRotation = currentQuaternion.inverted();
    //initialization = false;

//    float pitch = 0;
//    float yaw = 0;
//    float roll = 0;
//    currentQuaternion.getEulerAngles(&pitch, &yaw, &roll);

//    yaw = 0;
//    invertedOffsetRotation = QQuaternion::fromEulerAngles(pitch, yaw, roll).inverted();
}

void SkeletonView::resetZaxisDrift()
{
    float pitch = 0;
    float yaw = 0;
    float roll = 0;
    currentQuaternion.getEulerAngles(&pitch, &yaw, &roll);
    pitch = 0;
    roll = 0;
    invertedZAxisRotation = QQuaternion::fromEulerAngles(pitch, yaw, roll).inverted();
}
