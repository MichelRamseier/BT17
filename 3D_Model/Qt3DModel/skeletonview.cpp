#include "skeletonview.h"

// FIXME: Properly integrate Axiamo Enumerations
#define Quat6 0x0140
#define Quat9 0x0141


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

    //model->SetRightUpperArmRotation(finalLeftUpperArmQuaternion);
    //model->SetRightLowerArmRotation(rotation);
    //QMatrix4x4 rotationMatrix = QMatrix4x4(rotation.toRotationMatrix());
    //this->testTransform->setMatrix(rotationMatrix);




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

    QPushButton *removeOffsetButton = new QPushButton();
    removeOffsetButton->setText("Remove Offset");

//    QPushButton *removeDriftButton = new QPushButton();
//    removeDriftButton->setText("Remove Z-Axis Drift");

    vLayout->addWidget(removeOffsetButton);
    //vLayout->addWidget(removeDriftButton);

    QObject::connect(removeOffsetButton, &QPushButton::clicked, this, &SkeletonView::removeOffset);
    //QObject::connect(removeDriftButton, &QPushButton::clicked, this, &SkeletonView::removeZaxisDrift);

    // Show window
    widget->show();
    widget->resize(1200, 800);
}

void SkeletonView::vectorSample(quint64 deviceSerial, quint32 trackId, quint32 sampleNumber, QList<double> data)
{
    //led nach oben beim anbringen an körper
    //hinweis: kamera 180° gedreht
    //sensor hat eine initiale position (x und z-Achse fix, y-Achse variabel)

    if(trackId == Quat9)
    {
        if(data.size() >= 4)
        {
            QQuaternion rotation(data[0], data[1], -data[3], data[2]);

            // Oberarm Links
            if(deviceSerial == 2615221423530695350)
            {
                //  HACK: set right instead of left rotation, otherwise the model don't act as desired
                currentRightUpperArmQuaternion = rotation;
                finalRightUpperArmQuaternion = currentRightUpperArmQuaternion * invertedRightUpperArmOffset;
            }
            //Unterarm Rechts
            else if(deviceSerial == 2630769608869141230)
            {
                //  HACK: set left instead of right rotation, otherwise the model don't act as desired
                currentLeftLowerArmQuaternion = rotation;
                finalLeftLowerArmQuaternion = currentLeftLowerArmQuaternion * invertedLeftLowerArmOffset;
            }
            //Oberarm Rechts
            else if(deviceSerial == 2630769608869141119)
            {
                //  HACK: set left instead of right rotation, otherwise the model don't act as desired
                currentLeftUpperArmQuaternion = rotation;
                finalLeftUpperArmQuaternion = currentLeftUpperArmQuaternion * invertedLeftUpperArmOffset;
            }
            //Unterarm Links
            else if(deviceSerial == 2652720250416126580)
            {
                //  HACK: set right instead of left rotation, otherwise the model don't act as desired
                currentRightLowerArmQuaternion = rotation;
                finalRightLowerArmQuaternion = currentRightLowerArmQuaternion * invertedRightLowerArmOffset;
            }
            //Rumpf
            else if(deviceSerial == 2660762074166713025)
            {
                currentCenterQuaternion = rotation;
                finalCenterQuaternion = currentCenterQuaternion * invertedCenterOffset;
            }
            //Bein Rechts Oben
            else if(deviceSerial == 0)
            {

            }
            //Bein Rechts Unten
            else if(deviceSerial == 0)
            {

            }
            //Bein Links Oben
            else if(deviceSerial == 0)
            {

            }
            //Bein Links Unten
            else if(deviceSerial == 0)
            {

            }

            model->SetCenterRotation(finalCenterQuaternion * modelOffsetRotation);
            model->SetLeftUpperArmRotation(finalLeftUpperArmQuaternion * modelOffsetRotation);
            model->SetLeftLowerArmRotation(finalLeftLowerArmQuaternion * modelOffsetRotation);
            model->SetRightUpperArmRotation(finalRightUpperArmQuaternion * modelOffsetRotation);
            model->SetRightLowerArmRotation(finalRightLowerArmQuaternion * modelOffsetRotation);
            model->SetLeftUpperLegRotation(finalLeftUpperLegQuaternion * modelOffsetRotation);
            model->SetLeftLowerLegRotation(finalLeftLowerLegQuaternion * modelOffsetRotation);
            model->SetRightUpperLegRotation(finalRightUpperLegQuaternion * modelOffsetRotation);
            model->SetRightLowerLegRotation(finalRightLowerLegQuaternion * modelOffsetRotation);

            //add finalHeadQuaternion if needed
            model->SetHeadRotation(modelOffsetRotation);
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

void SkeletonView::removeOffset()
{
    invertedLeftLowerArmOffset = currentLeftLowerArmQuaternion.inverted();
    invertedLeftUpperArmOffset = currentLeftUpperArmQuaternion.inverted();
    invertedRightLowerArmOffset = currentRightLowerArmQuaternion.inverted();
    invertedRightUpperArmOffset = currentRightUpperArmQuaternion.inverted();
    invertedCenterOffset = currentCenterQuaternion.inverted();
    invertedLeftLowerLegOffset = currentLeftLowerLegQuaternion.inverted();
    invertedLeftUpperLegOffset = currentLeftUpperLegQuaternion.inverted();
    invertedRightLowerLegOffset = currentRightLowerLegQuaternion.inverted();
    invertedRightUpperLegOffset = currentRightUpperLegQuaternion.inverted();
}

void SkeletonView::removeZaxisDrift()
{
    // be in initial position for drift removal

    // the resulting rotation (currentRotation * invertedSensorRotation) should be zero in initial position
    // if there is a drift, the resulting rotation will be different to zero
    //QQuaternion drift = currentQuaternion * invertedSensorOffsetRotation;
    float pitch = 0;
    float yaw = 0;
    float roll = 0;
    //drift.getEulerAngles(&pitch, &yaw, &roll);
    pitch = 0;
    roll = 0;
    //invertedZAxisDriftRotation = QQuaternion::fromEulerAngles(pitch, yaw, roll).inverted();
}
