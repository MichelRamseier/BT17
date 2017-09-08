#include "model.h"
#include <Qt3DRender/QMesh>


Model::Model(Qt3DCore::QEntity *sceneRoot)
{
    this->sceneRoot = sceneRoot;
}

QMatrix4x4 Model::GetTranslationMatrix(float x, float y, float z)
{
    return QMatrix4x4(1,0,0,x
                      ,0,1,0,y
                      ,0,0,1,z
                      ,0,0,0,1);
}

QMatrix4x4 Model::GetTranslationMatrix(QVector4D vector)
{
    return QMatrix4x4(1,0,0,vector.x(),
                      0,1,0,vector.y(),
                      0,0,1,vector.z(),
                      0,0,0,vector.w());
}


void Model::Initialize()
{
    // Points from Blender
    this->connectorHeadCenterOrigin = QVector4D(-0.29, 14.8, -2.58, 1);
    this->connectorCenterAndLeftUpperArmOrigin = QVector4D(-5.65, 10.84, -1.53, 1);
    this->connectorCenterAndRightUpperArmOrigin = QVector4D(5.65, 10.84, -1.53, 1);
    this->connectorRightUpperAndLowerArmOrigin = QVector4D(9.91, 0.2, -4, 1);
    this->connectorLeftUpperAndLowerArmOrigin = QVector4D(-9.91, 0.2, -4, 1);
    this->connectorCenterAndLeftUpperLegOrigin = QVector4D(-3.3, -7.6, 0.47, 1);
    this->connectorCenterAndRightUpperLegOrigin = QVector4D(3.3, -7.6, 0.47, 1);
    this->connectorRightUpperAndLowerLegOrigin = QVector4D(3.58,-24.55,-1.12, 1);
    this->connectorLeftUpperAndLowerLegOrigin = QVector4D(-3.58, -24.55, -1.12, 1);


    this->connectorHeadCenterTMOrigin = this->GetTranslationMatrix(this->connectorHeadCenterOrigin);
    this->connectorCenterAndLeftUpperArmTMOrigin = this->GetTranslationMatrix(this->connectorCenterAndLeftUpperArmOrigin);
    this->connectorCenterAndRightUpperArmTMOrigin = this->GetTranslationMatrix(this->connectorCenterAndRightUpperArmOrigin);
    this->connectorRightUpperAndLowerArmTMOrigin = this->GetTranslationMatrix(this->connectorRightUpperAndLowerArmOrigin);
    this->connectorLeftUpperAndLowerArmTMOrigin = this->GetTranslationMatrix(this->connectorLeftUpperAndLowerArmOrigin);
    this->connectorCenterAndLeftUpperLegTMOrigin = this->GetTranslationMatrix(this->connectorCenterAndLeftUpperLegOrigin);
    this->connectorCenterAndRightUpperLegTMOrigin = this->GetTranslationMatrix(this->connectorCenterAndRightUpperLegOrigin);
    this->connectorRightUpperAndLowerLegTMOrigin = this->GetTranslationMatrix(this->connectorRightUpperAndLowerLegOrigin);
    this->connectorLeftUpperAndLowerLegTMOrigin = this->GetTranslationMatrix(this->connectorLeftUpperAndLowerLegOrigin);

    this->centerTransform = new Qt3DCore::QTransform();
    this->leftLowerArmTransform = new Qt3DCore::QTransform();
    this->leftUpperArmTransform = new Qt3DCore::QTransform();
    this->leftUpperLegTransform = new Qt3DCore::QTransform();
    this->leftLowerLegTransform = new Qt3DCore::QTransform();
    this->rightLowerArmTransform = new Qt3DCore::QTransform();
    this->rightUpperArmTransform = new Qt3DCore::QTransform();
    this->rightUpperLegTransform = new Qt3DCore::QTransform();
    this->rightLowerLegTransform = new Qt3DCore::QTransform();
    this->headTransform = new Qt3DCore::QTransform();

    Qt3DExtras::QPhongMaterial *phongMaterial = new Qt3DExtras::QPhongMaterial();
    phongMaterial->setDiffuse(QColor(QRgb(0x34F247)));

    Qt3DRender::QMesh *rightLowerLegMesh = new Qt3DRender::QMesh();
    rightLowerLegMesh->setSource(QUrl("qrc:assets/rightlowerleg.obj"));
    Qt3DCore::QEntity *rightLowerLegEntity = new Qt3DCore::QEntity(sceneRoot);
    rightLowerLegEntity = new Qt3DCore::QEntity(rightLowerLegEntity);
    rightLowerLegEntity->addComponent(rightLowerLegMesh);
    rightLowerLegEntity->addComponent(phongMaterial);
    rightLowerLegEntity->addComponent(rightLowerLegTransform);

    Qt3DRender::QMesh *rightUpperLegMesh = new Qt3DRender::QMesh();
    rightUpperLegMesh->setSource(QUrl("qrc:assets/rightupperleg.obj"));
    Qt3DCore::QEntity *rightUpperLegEntity = new Qt3DCore::QEntity(sceneRoot);
    rightUpperLegEntity = new Qt3DCore::QEntity(rightUpperLegEntity);
    rightUpperLegEntity->addComponent(rightUpperLegMesh);
    rightUpperLegEntity->addComponent(phongMaterial);
    rightUpperLegEntity->addComponent(rightUpperLegTransform);

    Qt3DRender::QMesh *leftLowerLegMesh = new Qt3DRender::QMesh();
    leftLowerLegMesh->setSource(QUrl("qrc:assets/leftlowerleg.obj"));
    Qt3DCore::QEntity *leftLowerLegEntity = new Qt3DCore::QEntity(sceneRoot);
    leftLowerLegEntity = new Qt3DCore::QEntity(leftLowerLegEntity);
    leftLowerLegEntity->addComponent(leftLowerLegMesh);
    leftLowerLegEntity->addComponent(phongMaterial);
    leftLowerLegEntity->addComponent(leftLowerLegTransform);

    Qt3DRender::QMesh *leftUpperLegMesh = new Qt3DRender::QMesh();
    leftUpperLegMesh->setSource(QUrl("qrc:assets/leftupperleg.obj"));
    Qt3DCore::QEntity *leftUpperLegEntity = new Qt3DCore::QEntity(sceneRoot);
    leftUpperLegEntity = new Qt3DCore::QEntity(leftUpperLegEntity);
    leftUpperLegEntity->addComponent(leftUpperLegMesh);
    leftUpperLegEntity->addComponent(phongMaterial);
    leftUpperLegEntity->addComponent(leftUpperLegTransform);

    Qt3DRender::QMesh *centerMesh = new Qt3DRender::QMesh();
    centerMesh->setSource(QUrl("qrc:assets/center.obj"));
    Qt3DCore::QEntity *centerEntity = new Qt3DCore::QEntity(sceneRoot);
    centerEntity = new Qt3DCore::QEntity(centerEntity);
    centerEntity->addComponent(centerMesh);
    centerEntity->addComponent(phongMaterial);
    centerEntity->addComponent(this->centerTransform);

    Qt3DRender::QMesh *headMesh = new Qt3DRender::QMesh();
    headMesh->setSource(QUrl("qrc:assets/head.obj"));
    Qt3DCore::QEntity *headEntity = new Qt3DCore::QEntity(sceneRoot);
    headEntity = new Qt3DCore::QEntity(headEntity);
    headEntity->addComponent(headMesh);
    headEntity->addComponent(phongMaterial);
    headEntity->addComponent(headTransform);

    Qt3DRender::QMesh *leftLowerArmMesh = new Qt3DRender::QMesh();
    leftLowerArmMesh->setSource(QUrl("qrc:assets/leftlowerarm.obj"));
    Qt3DCore::QEntity *leftLowerArmEntity = new Qt3DCore::QEntity(sceneRoot);
    leftLowerArmEntity = new Qt3DCore::QEntity(leftLowerArmEntity);
    leftLowerArmEntity->addComponent(leftLowerArmMesh);
    leftLowerArmEntity->addComponent(phongMaterial);
    leftLowerArmEntity->addComponent(leftLowerArmTransform);

    Qt3DRender::QMesh *leftUpperArmMesh = new Qt3DRender::QMesh();
    leftUpperArmMesh->setSource(QUrl("qrc:assets/leftupperarm.obj"));
    Qt3DCore::QEntity *leftUpperArmEntity = new Qt3DCore::QEntity(sceneRoot);
    leftUpperArmEntity = new Qt3DCore::QEntity(leftUpperArmEntity);
    leftUpperArmEntity->addComponent(leftUpperArmMesh);
    leftUpperArmEntity->addComponent(phongMaterial);
    leftUpperArmEntity->addComponent(this->leftUpperArmTransform);

    Qt3DRender::QMesh *rightLowerArmMesh = new Qt3DRender::QMesh();
    rightLowerArmMesh->setSource(QUrl("qrc:assets/rightlowerarm.obj"));
    Qt3DCore::QEntity *rightLowerArmEntity = new Qt3DCore::QEntity(sceneRoot);
    rightLowerArmEntity = new Qt3DCore::QEntity(rightLowerArmEntity);
    rightLowerArmEntity->addComponent(rightLowerArmMesh);
    rightLowerArmEntity->addComponent(phongMaterial);
    rightLowerArmEntity->addComponent(rightLowerArmTransform);

    Qt3DRender::QMesh *rightUpperArmMesh = new Qt3DRender::QMesh();
    rightUpperArmMesh->setSource(QUrl("qrc:assets/rightupperarm.obj"));
    Qt3DCore::QEntity *rightUpperArmEntity = new Qt3DCore::QEntity(sceneRoot);
    rightUpperArmEntity = new Qt3DCore::QEntity(rightUpperArmEntity);
    rightUpperArmEntity->addComponent(rightUpperArmMesh);
    rightUpperArmEntity->addComponent(phongMaterial);
    rightUpperArmEntity->addComponent(rightUpperArmTransform);
}

void Model::SetCenterRotation(QQuaternion quaternion)
{
    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    this->centerTransform->setMatrix(rotationMatrix);
    QVector4D connectorCenterAndLeftUpperArm = rotationMatrix * this->connectorCenterAndLeftUpperArmOrigin;
    this->connectorCenterAndLeftUpperArmTM = GetTranslationMatrix(connectorCenterAndLeftUpperArm.x(),
                                                                  connectorCenterAndLeftUpperArm.y(),
                                                                  connectorCenterAndLeftUpperArm.z());

    QVector4D connectorCenterAndRightUpperArm = rotationMatrix * this->connectorCenterAndRightUpperArmOrigin;
    this->connectorCenterAndRightUpperArmTM = GetTranslationMatrix(connectorCenterAndRightUpperArm.x(),
                                                                   connectorCenterAndRightUpperArm.y(),
                                                                   connectorCenterAndRightUpperArm.z());

    QVector4D connectorCenterAndLeftUpperLeg = rotationMatrix * this->connectorCenterAndLeftUpperLegOrigin;
    this->connectorCenterAndLeftUpperLegTM = GetTranslationMatrix(connectorCenterAndLeftUpperLeg.x(),
                                                                  connectorCenterAndLeftUpperLeg.y(),
                                                                  connectorCenterAndLeftUpperLeg.z());

    QVector4D connectorCenterAndRightUpperLeg = rotationMatrix * this->connectorCenterAndRightUpperLegOrigin;
    this->connectorCenterAndRightUpperLegTM = GetTranslationMatrix(connectorCenterAndRightUpperLeg.x(),
                                                                   connectorCenterAndRightUpperLeg.y(),
                                                                   connectorCenterAndRightUpperLeg.z());

    QVector4D connectorRightUpperAndLowerArm = rotationMatrix * this->connectorRightUpperAndLowerArmOrigin;
    this->connectorRightUpperAndLowerArmTM = GetTranslationMatrix(connectorRightUpperAndLowerArm.x(),
                                                                   connectorRightUpperAndLowerArm.y(),
                                                                   connectorRightUpperAndLowerArm.z());

    QVector4D connectorLeftUpperAndLowerArm = rotationMatrix * this->connectorLeftUpperAndLowerArmOrigin;
    this->connectorLeftUpperAndLowerArmTM = GetTranslationMatrix(connectorLeftUpperAndLowerArm.x(),
                                                                   connectorLeftUpperAndLowerArm.y(),
                                                                   connectorLeftUpperAndLowerArm.z());

    QVector4D connectorRightUpperAndLowerLeg = rotationMatrix * this->connectorRightUpperAndLowerLegOrigin;
    this->connectorRightUpperAndLowerLegTM = GetTranslationMatrix(connectorRightUpperAndLowerLeg.x(),
                                                                   connectorRightUpperAndLowerLeg.y(),
                                                                   connectorRightUpperAndLowerLeg.z());

    QVector4D connectorLeftUpperAndLowerLeg = rotationMatrix * this->connectorLeftUpperAndLowerLegOrigin;
    this->connectorLeftUpperAndLowerLegTM = GetTranslationMatrix(connectorLeftUpperAndLowerLeg.x(),
                                                                   connectorLeftUpperAndLowerLeg.y(),
                                                                   connectorLeftUpperAndLowerLeg.z());

    QVector4D connectorHeadCenter = rotationMatrix * this->connectorHeadCenterOrigin;
    this->connectorHeadCenterTM = GetTranslationMatrix(connectorHeadCenter.x(),
                                                        connectorHeadCenter.y(),
                                                        connectorHeadCenter.z());

    this->leftUpperArmTransform->setMatrix(this->connectorCenterAndLeftUpperArmTM * this->connectorCenterAndLeftUpperArmTMOrigin.inverted());
    this->leftLowerArmTransform->setMatrix(this->connectorCenterAndLeftUpperArmTM * this->connectorCenterAndLeftUpperArmTMOrigin.inverted());
    this->rightUpperArmTransform->setMatrix(this->connectorCenterAndRightUpperArmTM * this->connectorCenterAndRightUpperArmTMOrigin.inverted());
    this->rightLowerArmTransform->setMatrix(this->connectorCenterAndRightUpperArmTM * this->connectorCenterAndRightUpperArmTMOrigin.inverted());
    this->leftUpperLegTransform->setMatrix(this->connectorCenterAndLeftUpperLegTM * this->connectorCenterAndLeftUpperLegTMOrigin.inverted());
    this->leftLowerLegTransform->setMatrix(this->connectorCenterAndLeftUpperLegTM * this->connectorCenterAndLeftUpperLegTMOrigin.inverted());
    this->rightUpperLegTransform->setMatrix(this->connectorCenterAndRightUpperLegTM * this->connectorCenterAndRightUpperLegTMOrigin.inverted());
    this->rightLowerLegTransform->setMatrix(this->connectorCenterAndRightUpperLegTM * this->connectorCenterAndRightUpperLegTMOrigin.inverted());
    this->headTransform->setMatrix(this->connectorHeadCenterTM * this->connectorHeadCenterTMOrigin.inverted());
}

void Model::SetLeftUpperArmRotation(QQuaternion quaternion)
{
    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    this->leftUpperArmTransform->setMatrix(this->connectorCenterAndLeftUpperArmTM * rotationMatrix * this->connectorCenterAndLeftUpperArmTMOrigin.inverted());


//    QVector4D connectorLeftUpperAndLowerArm = rotationMatrix * this->connectorLeftUpperAndLowerArmOrigin;
//    this->connectorLeftUpperAndLowerArmTM = GetTranslationMatrix(connectorLeftUpperAndLowerArm.x(),
//                                                                 connectorLeftUpperAndLowerArm.y(),
//                                                                 connectorLeftUpperAndLowerArm.z());

//    SetLeftLowerArmRotation(quaternion);
}

void Model::SetLeftLowerArmRotation(QQuaternion quaternion)
{
//    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
//    this->leftLowerArmTransform->setMatrix(this->connectorLeftUpperAndLowerArmTM * topCenterTM  * rotationMatrix * this->llaOffsetRM * this->offsetTM);
}

void Model::SetRightUpperArmRotation(QQuaternion quaternion)
{
//    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
//    this->rightUpperArmTransform->setMatrix(this->topCenterTM * rotationMatrix * this->ruaOffsetRM * this->offsetTM);
//    QVector4D connectorRightUpperAndLowerArm = rotationMatrix * this->connectorRightUpperAndLowerArmOrigin;
//    this->connectorRightUpperAndLowerArmTM = GetTranslationMatrix(connectorRightUpperAndLowerArm.x(),
//                                                                 connectorRightUpperAndLowerArm.y(),
//                                                                 connectorRightUpperAndLowerArm.z());

//    SetRightLowerArmRotation(quaternion);
}

void Model::SetRightLowerArmRotation(QQuaternion quaternion)
{
//    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
//    this->rightLowerArmTransform->setMatrix(this->connectorRightUpperAndLowerArmTM * topCenterTM  * rotationMatrix * this->rlaOffsetRM * this->offsetTM);
}

void Model::SetLeftUpperLegRotation(QQuaternion quaternion)
{
//    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
//    this->leftUpperLegTransform->setMatrix(this->bottomCenterTM * rotationMatrix * this->lulOffsetRM * this->offsetTM);
//    QVector4D connectorLeftUpperAndLowerLeg = rotationMatrix * this->connectorLeftUpperAndLowerLegOrigin;
//    this->connectorLeftUpperAndLowerLegTM = GetTranslationMatrix(connectorLeftUpperAndLowerLeg.x(),
//                                                                 connectorLeftUpperAndLowerLeg.y(),
//                                                                 connectorLeftUpperAndLowerLeg.z());

//    SetLeftLowerLegRotation(quaternion);
}

void Model::SetLeftLowerLegRotation(QQuaternion quaternion)
{
//    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
//    this->leftLowerLegTransform->setMatrix(this->connectorLeftUpperAndLowerLegTM * this->bottomCenterTM  * rotationMatrix * this->lllOffsetRM * this->offsetTM);
}

void Model::SetRightUpperLegRotation(QQuaternion quaternion)
{
//    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
//    this->rightUpperLegTransform->setMatrix(this->bottomCenterTM * rotationMatrix * this->rulOffsetRM * this->offsetTM);
//    QVector4D connectorRightUpperAndLowerLeg = rotationMatrix * this->connectorRightUpperAndLowerLegOrigin;
//    this->connectorRightUpperAndLowerLegTM = GetTranslationMatrix(connectorRightUpperAndLowerLeg.x(),
//                                                                 connectorRightUpperAndLowerLeg.y(),
//                                                                 connectorRightUpperAndLowerLeg.z());

//    SetRightLowerLegRotation(quaternion);
}

void Model::SetRightLowerLegRotation(QQuaternion quaternion)
{
//    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
//    this->rightLowerLegTransform->setMatrix(this->connectorRightUpperAndLowerLegTM * this->bottomCenterTM  * rotationMatrix * this->rllOffsetRM * this->offsetTM);
}

void Model::SetHeadRotation(QQuaternion quaternion)
{
//    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
//    this->headTransform->setMatrix(this->topCenterTM * this->headTM * rotationMatrix * this->headOffsetTM);
}
