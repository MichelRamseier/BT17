#include "model.h"


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


void Model::Initialize()
{
    float centerLength = 4;
    Qt3DExtras::QCylinderMesh *centerMesh = new Qt3DExtras::QCylinderMesh();
    centerMesh->setRadius(0.3f);
    centerMesh->setLength(centerLength);
    centerMesh->setRings(100);
    centerMesh->setSlices(20);

    float bodyPartLength = 2;
    Qt3DExtras::QCylinderMesh *modelMesh = new Qt3DExtras::QCylinderMesh();
    modelMesh->setRadius(0.3f);
    modelMesh->setLength(bodyPartLength);
    modelMesh->setRings(10);
    modelMesh->setSlices(20);

    float headRadius = 0.5;
    Qt3DExtras::QSphereMesh *headMesh = new Qt3DExtras::QSphereMesh();
    headMesh->setRadius(headRadius);

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

    QVector3D offsetT = QVector3D(0, bodyPartLength/2, 0);
    QVector3D headOffsetT = QVector3D(0, headRadius/2, 0);
    QVector3D headT = QVector3D(0, 1, 0);

    this->offsetTM = GetTranslationMatrix(offsetT.x(),
                                          offsetT.y(),
                                          offsetT.z());
    this->headOffsetTM = GetTranslationMatrix(headOffsetT.x(),
                                              headOffsetT.y(),
                                              headOffsetT.z());
    this->headTM = GetTranslationMatrix(headT.x(),
                                        headT.y(),
                                        headT.z());

    this->topCenterOrigin = QVector4D(0,centerLength/2,0,1);
    this->bottomCenterOrigin = QVector4D(0,(centerLength/2)*-1,0,1);
    this->connectorLeftUpperAndLowerArmOrigin = QVector4D(bodyPartLength*-1,0,0,1);
    this->connectorRightUpperAndLowerArmOrigin = QVector4D(bodyPartLength,0,0,1);
    this->connectorLeftUpperAndLowerLegOrigin = QVector4D(bodyPartLength*-1,0,0,1);
    this->connectorRightUpperAndLowerLegOrigin = QVector4D(bodyPartLength,0,0,1);

    QQuaternion headQ = QQuaternion::fromAxisAndAngle(0,0,1,0);
    QQuaternion centerOffsetQ = QQuaternion::fromAxisAndAngle(0,0,1,0);

    QQuaternion luaOffsetQ = QQuaternion::fromAxisAndAngle(0,0,1,90);
    QQuaternion llaOffsetQ = QQuaternion::fromAxisAndAngle(0,0,1,90);
    QQuaternion ruaOffsetQ = QQuaternion::fromAxisAndAngle(0,0,1,-90);
    QQuaternion rlaOffsetQ = QQuaternion::fromAxisAndAngle(0,0,1,-90);

    this->luaOffsetRM = QMatrix4x4(luaOffsetQ.toRotationMatrix());
    this->llaOffsetRM = QMatrix4x4(llaOffsetQ.toRotationMatrix());
    this->ruaOffsetRM = QMatrix4x4(ruaOffsetQ.toRotationMatrix());
    this->rlaOffsetRM = QMatrix4x4(rlaOffsetQ.toRotationMatrix());

    QQuaternion lulOffsetQ = QQuaternion::fromAxisAndAngle(0,0,1,90);
    QQuaternion lllOffsetQ = QQuaternion::fromAxisAndAngle(0,0,1,90);
    QQuaternion rulOffsetQ = QQuaternion::fromAxisAndAngle(0,0,1,-90);
    QQuaternion rllOffsetQ = QQuaternion::fromAxisAndAngle(0,0,1,-90);

    this->lulOffsetRM = QMatrix4x4(lulOffsetQ.toRotationMatrix());
    this->lllOffsetRM = QMatrix4x4(lllOffsetQ.toRotationMatrix());
    this->rulOffsetRM = QMatrix4x4(rulOffsetQ.toRotationMatrix());
    this->rllOffsetRM = QMatrix4x4(rllOffsetQ.toRotationMatrix());

    // set defaults
    this->SetCenterRotation(centerOffsetQ);
    this->SetHeadRotation(headQ);
    this->SetLeftUpperArmRotation(luaOffsetQ);
    this->SetLeftLowerArmRotation(llaOffsetQ);
    this->SetRightUpperArmRotation(ruaOffsetQ);
    this->SetRightLowerArmRotation(rlaOffsetQ);
    this->SetLeftUpperLegRotation(lulOffsetQ);
    this->SetLeftLowerLegRotation(lllOffsetQ);
    this->SetRightUpperLegRotation(rulOffsetQ);
    this->SetRightLowerLegRotation(rllOffsetQ);

    Qt3DExtras::QPhongMaterial *modelMaterial = new Qt3DExtras::QPhongMaterial();
    modelMaterial->setDiffuse(QColor(QRgb(0x34F247)));

    Qt3DCore::QEntity *centerEntity = new Qt3DCore::QEntity(this->sceneRoot);
    centerEntity = new Qt3DCore::QEntity(centerEntity);
    centerEntity->addComponent(centerMesh);
    centerEntity->addComponent(modelMaterial);
    centerEntity->addComponent(centerTransform);

    Qt3DCore::QEntity *leftArmEntity = new Qt3DCore::QEntity(this->sceneRoot);
    leftArmEntity = new Qt3DCore::QEntity(leftArmEntity);
    leftArmEntity->addComponent(modelMesh);
    leftArmEntity->addComponent(modelMaterial);
    leftArmEntity->addComponent(this->leftUpperArmTransform);

    Qt3DCore::QEntity *leftForearmEntity = new Qt3DCore::QEntity(this->sceneRoot);
    leftForearmEntity = new Qt3DCore::QEntity(leftForearmEntity);
    leftForearmEntity->addComponent(modelMesh);
    leftForearmEntity->addComponent(modelMaterial);
    leftForearmEntity->addComponent(this->leftLowerArmTransform);

    Qt3DCore::QEntity *rightUpperArmEntity = new Qt3DCore::QEntity(this->sceneRoot);
    rightUpperArmEntity = new Qt3DCore::QEntity(rightUpperArmEntity);
    rightUpperArmEntity->addComponent(modelMesh);
    rightUpperArmEntity->addComponent(modelMaterial);
    rightUpperArmEntity->addComponent(this->rightUpperArmTransform);

    Qt3DCore::QEntity *rightLowerArmEntity = new Qt3DCore::QEntity(this->sceneRoot);
    rightLowerArmEntity = new Qt3DCore::QEntity(rightLowerArmEntity);
    rightLowerArmEntity->addComponent(modelMesh);
    rightLowerArmEntity->addComponent(modelMaterial);
    rightLowerArmEntity->addComponent(this->rightLowerArmTransform);

    Qt3DCore::QEntity *leftThighEntity = new Qt3DCore::QEntity(this->sceneRoot);
    leftThighEntity = new Qt3DCore::QEntity(leftThighEntity);
    leftThighEntity->addComponent(modelMesh);
    leftThighEntity->addComponent(modelMaterial);
    leftThighEntity->addComponent(this->leftUpperLegTransform);

    Qt3DCore::QEntity *leftLegEntity = new Qt3DCore::QEntity(this->sceneRoot);
    leftLegEntity = new Qt3DCore::QEntity(leftLegEntity);
    leftLegEntity->addComponent(modelMesh);
    leftLegEntity->addComponent(modelMaterial);
    leftLegEntity->addComponent(this->leftLowerLegTransform);

    Qt3DCore::QEntity *rightThighEntity = new Qt3DCore::QEntity(this->sceneRoot);
    rightThighEntity = new Qt3DCore::QEntity(rightThighEntity);
    rightThighEntity->addComponent(modelMesh);
    rightThighEntity->addComponent(modelMaterial);
    rightThighEntity->addComponent(this->rightUpperLegTransform);

    Qt3DCore::QEntity *rightLegEntity = new Qt3DCore::QEntity(this->sceneRoot);
    rightLegEntity = new Qt3DCore::QEntity(rightLegEntity);
    rightLegEntity->addComponent(modelMesh);
    rightLegEntity->addComponent(modelMaterial);
    rightLegEntity->addComponent(this->rightLowerLegTransform);

    Qt3DCore::QEntity *headEntity = new Qt3DCore::QEntity(this->sceneRoot);
    headEntity = new Qt3DCore::QEntity(headEntity);
    headEntity->addComponent(headMesh);
    headEntity->addComponent(modelMaterial);
    headEntity->addComponent(this->headTransform);
}

void Model::SetCenterRotation(QQuaternion quaternion)
{
    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    this->centerTransform->setMatrix(rotationMatrix);
    QVector4D topCenter = rotationMatrix * this->topCenterOrigin;
    this->topCenterTM = GetTranslationMatrix(topCenter.x(),
                                             topCenter.y(),
                                             topCenter.z());

    QVector4D bottomCenter = rotationMatrix * this->bottomCenterOrigin;
    this->bottomCenterTM = GetTranslationMatrix(bottomCenter.x(),
                                                bottomCenter.y(),
                                                bottomCenter.z());

    //update all other segments, because this is the center
    SetLeftUpperArmRotation(quaternion);
    SetLeftLowerArmRotation(quaternion);
    SetRightUpperArmRotation(quaternion);
    SetRightLowerArmRotation(quaternion);
    SetLeftUpperLegRotation(quaternion);
    SetLeftLowerLegRotation(quaternion);
    SetRightUpperLegRotation(quaternion);
    SetRightLowerLegRotation(quaternion);
    SetHeadRotation(quaternion);
}

void Model::SetLeftUpperArmRotation(QQuaternion quaternion)
{
    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    this->leftUpperArmTransform->setMatrix(this->topCenterTM * rotationMatrix * this->luaOffsetRM * this->offsetTM);
    QVector4D connectorLeftUpperAndLowerArm = rotationMatrix * this->connectorLeftUpperAndLowerArmOrigin;
    this->connectorLeftUpperAndLowerArmTM = GetTranslationMatrix(connectorLeftUpperAndLowerArm.x(),
                                                                 connectorLeftUpperAndLowerArm.y(),
                                                                 connectorLeftUpperAndLowerArm.z());

    SetLeftLowerArmRotation(quaternion);
}

void Model::SetLeftLowerArmRotation(QQuaternion quaternion)
{
    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    this->leftLowerArmTransform->setMatrix(this->connectorLeftUpperAndLowerArmTM * topCenterTM  * rotationMatrix * this->llaOffsetRM * this->offsetTM);
}

void Model::SetRightUpperArmRotation(QQuaternion quaternion)
{
    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    this->rightUpperArmTransform->setMatrix(this->topCenterTM * rotationMatrix * this->ruaOffsetRM * this->offsetTM);
    QVector4D connectorRightUpperAndLowerArm = rotationMatrix * this->connectorRightUpperAndLowerArmOrigin;
    this->connectorRightUpperAndLowerArmTM = GetTranslationMatrix(connectorRightUpperAndLowerArm.x(),
                                                                 connectorRightUpperAndLowerArm.y(),
                                                                 connectorRightUpperAndLowerArm.z());

    SetRightLowerArmRotation(quaternion);
}

void Model::SetRightLowerArmRotation(QQuaternion quaternion)
{
    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    this->rightLowerArmTransform->setMatrix(this->connectorRightUpperAndLowerArmTM * topCenterTM  * rotationMatrix * this->rlaOffsetRM * this->offsetTM);
}

void Model::SetLeftUpperLegRotation(QQuaternion quaternion)
{
    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    this->leftUpperLegTransform->setMatrix(this->bottomCenterTM * rotationMatrix * this->lulOffsetRM * this->offsetTM);
    QVector4D connectorLeftUpperAndLowerLeg = rotationMatrix * this->connectorLeftUpperAndLowerLegOrigin;
    this->connectorLeftUpperAndLowerLegTM = GetTranslationMatrix(connectorLeftUpperAndLowerLeg.x(),
                                                                 connectorLeftUpperAndLowerLeg.y(),
                                                                 connectorLeftUpperAndLowerLeg.z());

    SetLeftLowerLegRotation(quaternion);
}

void Model::SetLeftLowerLegRotation(QQuaternion quaternion)
{
    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    this->leftLowerLegTransform->setMatrix(this->connectorLeftUpperAndLowerLegTM * this->bottomCenterTM  * rotationMatrix * this->lllOffsetRM * this->offsetTM);
}

void Model::SetRightUpperLegRotation(QQuaternion quaternion)
{
    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    this->rightUpperLegTransform->setMatrix(this->bottomCenterTM * rotationMatrix * this->rulOffsetRM * this->offsetTM);
    QVector4D connectorRightUpperAndLowerLeg = rotationMatrix * this->connectorRightUpperAndLowerLegOrigin;
    this->connectorRightUpperAndLowerLegTM = GetTranslationMatrix(connectorRightUpperAndLowerLeg.x(),
                                                                 connectorRightUpperAndLowerLeg.y(),
                                                                 connectorRightUpperAndLowerLeg.z());

    SetRightLowerLegRotation(quaternion);
}

void Model::SetRightLowerLegRotation(QQuaternion quaternion)
{
    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    this->rightLowerLegTransform->setMatrix(this->connectorRightUpperAndLowerLegTM * this->bottomCenterTM  * rotationMatrix * this->rllOffsetRM * this->offsetTM);
}

void Model::SetHeadRotation(QQuaternion quaternion)
{
    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    this->headTransform->setMatrix(this->topCenterTM * this->headTM * rotationMatrix * this->headOffsetTM);
}
