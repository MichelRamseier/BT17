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
    this->relativeLeftUpperArmRotationMatrix =  QMatrix4x4();
    this->relativeLeftLowerArmRotationMatrix = QMatrix4x4();
    this->relativeRightUpperArmRotationMatrix= QMatrix4x4();
    this->relativeRightLowerArmRotationMatrix= QMatrix4x4();
    this->relativeLeftUpperLegRotationMatrix= QMatrix4x4();
    this->relativeLeftLowerLegRotationMatrix= QMatrix4x4();
    this->relativeRightUpperLegRotationMatrix= QMatrix4x4();
    this->relativeRightLowerLegRotationMatrix= QMatrix4x4();
    this->relativeCenterRotationMatrix = QMatrix4x4();

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

    Qt3DExtras::QSphereMesh *headMesh = new Qt3DExtras::QSphereMesh();
    headMesh->setRadius(0.5);

    this->centerTransform = new Qt3DCore::QTransform();
    this->leftForearmTransform = new Qt3DCore::QTransform();
    this->leftUpperArmTransform = new Qt3DCore::QTransform();
    this->leftUpperLegTransform = new Qt3DCore::QTransform();
    this->leftLowerLegTransform = new Qt3DCore::QTransform();
    this->rightForearmTransform = new Qt3DCore::QTransform();
    this->rightArmTransform = new Qt3DCore::QTransform();
    this->rightUpperLegTransform = new Qt3DCore::QTransform();
    this->rightLowerLegTransform = new Qt3DCore::QTransform();
    this->headTransform = new Qt3DCore::QTransform();

    QVector3D offsetT = QVector3D(0, bodyPartLength/2, 0);
    QVector3D luaT = QVector3D(0, centerLength/2, 0);
    QVector3D ruaT = QVector3D(0, centerLength/2, 0);
    QVector3D lulT = QVector3D(0, (centerLength/2)*-1, 0);
    QVector3D rulT = QVector3D(0, (centerLength/2)*-1, 0);
    QVector3D llaOffsetT = QVector3D(0, bodyPartLength, 0);
    QVector3D rlaOffsetT = QVector3D(0, bodyPartLength, 0);
    QVector3D lllOffsetT = QVector3D(0, bodyPartLength, 0);
    QVector3D rllOffsetT = QVector3D(0, bodyPartLength, 0);
    QVector3D headOffsetT = QVector3D(0, 3, 0);

    this->offsetTM = GetTranslationMatrix(offsetT.x(), offsetT.y(), offsetT.z());

    //upper body
    this->luaTM = GetTranslationMatrix(luaT.x(), luaT.y(), luaT.z());
    this->llaOffsetTM = GetTranslationMatrix(llaOffsetT.x(), llaOffsetT.y(), llaOffsetT.z());
    this->ruaTM = GetTranslationMatrix(ruaT.x(), ruaT.y(), ruaT.z());
    this->rlaOffsetTM = GetTranslationMatrix(rlaOffsetT.x(), rlaOffsetT.y(), rlaOffsetT.z());

    this->luaRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,90).toRotationMatrix());
    this->llaRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,90).toRotationMatrix());
    this->ruaRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,-90).toRotationMatrix());
    this->rlaRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,-90).toRotationMatrix());

    //lower body
    this->lulTM = GetTranslationMatrix(lulT.x(), lulT.y(), lulT.z());
    this->lllOffsetTM = GetTranslationMatrix(lllOffsetT.x(), lllOffsetT.y(), lllOffsetT.z());
    this->rulTM = GetTranslationMatrix(rulT.x(), rulT.y(), rulT.z());
    this->rllOffsetTM = GetTranslationMatrix(rllOffsetT.x(), rllOffsetT.y(), rllOffsetT.z());

    this->lulRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,90).toRotationMatrix());
    this->lllRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,90).toRotationMatrix());
    this->rulRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,-90).toRotationMatrix());
    this->rllRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(0,0,1,-90).toRotationMatrix());

    //center
    QMatrix4x4 centerRM = QMatrix4x4(QQuaternion::fromAxisAndAngle(1,0,0,0).toRotationMatrix());

    //head
    QMatrix4x4 headOffsetTM = GetTranslationMatrix(headOffsetT.x(), headOffsetT.y(), headOffsetT.z());

    //root
    this->centerOriginMatrix = centerRM;

    this->centerTransform->setMatrix(centerRM);

    //subelements
//    this->leftUpperArmOriginMatrix = this->luaTM * centerRM.inverted() *  this->luaRM *  this->offsetTM;
//    this->rightUpperArmOriginMatrix = this->ruaTM * centerRM.inverted() * this->ruaRM * this->offsetTM;
//    this->leftUpperLegOriginMatrix = this->lulTM * centerRM.inverted() * this->lulRM * this->offsetTM;
//    this->rightUpperLegOriginMatrix = this->rulTM * centerRM.inverted() * this->rulRM * this->offsetTM;
    this->leftUpperArmOriginMatrix = this->luaTM  *  this->luaRM *  this->offsetTM;
    this->rightUpperArmOriginMatrix = this->ruaTM * this->ruaRM * this->offsetTM;
    this->leftUpperLegOriginMatrix = this->lulTM * this->lulRM * this->offsetTM;
    this->rightUpperLegOriginMatrix = this->rulTM * this->rulRM * this->offsetTM;
    this->headOriginMatrix = headOffsetTM;

    this->leftUpperArmTransform->setMatrix(leftUpperArmOriginMatrix);
    this->rightArmTransform->setMatrix(rightUpperArmOriginMatrix);
    this->leftUpperLegTransform->setMatrix(leftUpperLegOriginMatrix);
    this->rightUpperLegTransform->setMatrix(rightUpperLegOriginMatrix);
    this->headTransform->setMatrix(headOriginMatrix);

    //subsubelements
//    this->leftLowerArmOriginMatrix = this->llaOffsetTM * this->offsetTM.inverted() * this->luaRM.inverted() * this->llaRM * this->offsetTM;
//    this->rightLowerArmOriginMatrix = this->rlaOffsetTM * this->offsetTM.inverted() * this->ruaRM.inverted() * this->rlaRM * this->offsetTM;
//    this->leftLowerLegOriginMatrix = this->lllOffsetTM * this->offsetTM.inverted() * this->lulRM.inverted() * this->lllRM * this->offsetTM;
//    this->rightLowerLegOriginMatrix = this->rllOffsetTM * this->offsetTM.inverted() * this->rulRM.inverted() * this->rllRM * this->offsetTM;
    this->leftLowerArmOriginMatrix = this->llaOffsetTM * this->offsetTM.inverted() * this->llaRM * this->offsetTM;
    this->rightLowerArmOriginMatrix = this->rlaOffsetTM * this->offsetTM.inverted() * this->rlaRM * this->offsetTM;
    this->leftLowerLegOriginMatrix = this->lllOffsetTM * this->offsetTM.inverted()  * this->lllRM * this->offsetTM;
    this->rightLowerLegOriginMatrix = this->rllOffsetTM * this->offsetTM.inverted() * this->rllRM * this->offsetTM;

    this->leftForearmTransform->setMatrix(leftLowerArmOriginMatrix);
    this->rightForearmTransform->setMatrix(rightLowerArmOriginMatrix);
    this->leftLowerLegTransform->setMatrix(leftLowerLegOriginMatrix);
    this->rightLowerLegTransform->setMatrix(rightLowerLegOriginMatrix);

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
    //leftArmEntity->setParent(centerEntity);

    Qt3DCore::QEntity *leftForearmEntity = new Qt3DCore::QEntity(this->sceneRoot);
    leftForearmEntity = new Qt3DCore::QEntity(leftForearmEntity);
    leftForearmEntity->addComponent(modelMesh);
    leftForearmEntity->addComponent(modelMaterial);
    leftForearmEntity->addComponent(this->leftForearmTransform);
    leftForearmEntity->setParent(leftArmEntity);

    Qt3DCore::QEntity *rightArmEntity = new Qt3DCore::QEntity(this->sceneRoot);
    rightArmEntity = new Qt3DCore::QEntity(rightArmEntity);
    rightArmEntity->addComponent(modelMesh);
    rightArmEntity->addComponent(modelMaterial);
    rightArmEntity->addComponent(this->rightArmTransform);
    rightArmEntity->setParent(centerEntity);

    Qt3DCore::QEntity *rightForearmEntity = new Qt3DCore::QEntity(this->sceneRoot);
    rightForearmEntity = new Qt3DCore::QEntity(rightForearmEntity);
    rightForearmEntity->addComponent(modelMesh);
    rightForearmEntity->addComponent(modelMaterial);
    rightForearmEntity->addComponent(this->rightForearmTransform);
    rightForearmEntity->setParent(rightArmEntity);

    Qt3DCore::QEntity *leftThighEntity = new Qt3DCore::QEntity(this->sceneRoot);
    leftThighEntity = new Qt3DCore::QEntity(leftThighEntity);
    leftThighEntity->addComponent(modelMesh);
    leftThighEntity->addComponent(modelMaterial);
    leftThighEntity->addComponent(this->leftUpperLegTransform);
    leftThighEntity->setParent(centerEntity);

    Qt3DCore::QEntity *leftLegEntity = new Qt3DCore::QEntity(this->sceneRoot);
    leftLegEntity = new Qt3DCore::QEntity(leftLegEntity);
    leftLegEntity->addComponent(modelMesh);
    leftLegEntity->addComponent(modelMaterial);
    leftLegEntity->addComponent(this->leftLowerLegTransform);
    leftLegEntity->setParent(leftThighEntity);

    Qt3DCore::QEntity *rightThighEntity = new Qt3DCore::QEntity(this->sceneRoot);
    rightThighEntity = new Qt3DCore::QEntity(rightThighEntity);
    rightThighEntity->addComponent(modelMesh);
    rightThighEntity->addComponent(modelMaterial);
    rightThighEntity->addComponent(this->rightUpperLegTransform);
    rightThighEntity->setParent(centerEntity);

    Qt3DCore::QEntity *rightLegEntity = new Qt3DCore::QEntity(this->sceneRoot);
    rightLegEntity = new Qt3DCore::QEntity(rightLegEntity);
    rightLegEntity->addComponent(modelMesh);
    rightLegEntity->addComponent(modelMaterial);
    rightLegEntity->addComponent(this->rightLowerLegTransform);
    rightLegEntity->setParent(rightThighEntity);

    Qt3DCore::QEntity *headEntity = new Qt3DCore::QEntity(this->sceneRoot);
    headEntity = new Qt3DCore::QEntity(headEntity);
    headEntity->addComponent(headMesh);
    headEntity->addComponent(modelMaterial);
    headEntity->addComponent(this->headTransform);
    headEntity->setParent(centerEntity);
}

void Model::SetCenterRotation(QQuaternion quaternion)
{
    this->relativeCenterRotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    centerTransform->setMatrix(QMatrix4x4(quaternion.toRotationMatrix()));
    QVector4D topCenter = QVector4D(0,2,0,1);
    topCenter = this->relativeCenterRotationMatrix * topCenter;
    QMatrix4x4 m = GetTranslationMatrix(topCenter.x(),topCenter.y(),topCenter.z());
    leftUpperArmTransform->setMatrix(m * this->luaRM * this->offsetTM);
}

void Model::SetLeftUpperArmRotation(QQuaternion quaternion)
{
    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    QMatrix4x4 parentRotationMatrix = this->relativeCenterRotationMatrix;
    QMatrix4x4 matrix = this->luaTM * parentRotationMatrix.inverted() * rotationMatrix * this->luaRM * this->offsetTM;
    leftUpperArmTransform->setMatrix(matrix);
    this->relativeLeftUpperArmRotationMatrix = rotationMatrix;
}

void Model::SetLeftLowerArmRotation(QQuaternion quaternion)
{
    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    QMatrix4x4 parentRotationMatrix = this->relativeLeftUpperArmRotationMatrix;
    //ob mit oder ohne parentmatrix -> ist das gleiche
    //evtl. parentRotation.inverted nach vorne verschieben
//    QMatrix4x4 matrix = this->llaOffsetTM * this->offsetTM.inverted() * rotationMatrix * parentRotationMatrix.inverted()  *  this->offsetTM;
    //QMatrix4x4 matrix =
    //leftForearmTransform->setMatrix(matrix);
    this->relativeLeftLowerArmRotationMatrix = rotationMatrix;
}

void Model::SetRightUpperArmRotation(QQuaternion quaternion)
{
    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    QMatrix4x4 parentRotationMatrix = this->relativeCenterRotationMatrix;
    QMatrix4x4 matrix = this->ruaTM * parentRotationMatrix.inverted() * rotationMatrix *  this->ruaRM *  this->offsetTM;
    rightArmTransform->setMatrix(matrix);
    this->relativeRightUpperArmRotationMatrix = rotationMatrix;
}

void Model::SetRightLowerArmRotation(QQuaternion quaternion)
{
    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    QMatrix4x4 parentRotationMatrix = this->relativeRightUpperArmRotationMatrix;
    QMatrix4x4 matrix = this->rlaOffsetTM * this->offsetTM.inverted() * parentRotationMatrix.inverted() * rotationMatrix * this->offsetTM;
    rightForearmTransform->setMatrix(matrix);
    this->relativeRightLowerArmRotationMatrix = rotationMatrix;
}

void Model::SetLeftUpperLegRotation(QQuaternion quaternion)
{
    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    QMatrix4x4 parentRotationMatrix = this->relativeCenterRotationMatrix;
    QMatrix4x4 matrix = this->lulTM * parentRotationMatrix.inverted() * rotationMatrix *  this->lulRM *  this->offsetTM;
    leftUpperLegTransform->setMatrix(matrix);
    this->relativeLeftUpperLegRotationMatrix = rotationMatrix;
}

void Model::SetLeftLowerLegRotation(QQuaternion quaternion)
{
    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    QMatrix4x4 parentRotationMatrix = this->relativeLeftUpperLegRotationMatrix;
    QMatrix4x4 matrix = this->lllOffsetTM * this->offsetTM.inverted() * parentRotationMatrix.inverted() * rotationMatrix * this->offsetTM;
    leftLowerLegTransform->setMatrix(matrix);
    this->relativeLeftLowerLegRotationMatrix = rotationMatrix;
}

void Model::SetRightUpperLegRotation(QQuaternion quaternion)
{
    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    QMatrix4x4 parentRotationMatrix = this->relativeCenterRotationMatrix;
    QMatrix4x4 matrix = this->rulTM * parentRotationMatrix.inverted() * rotationMatrix *  this->rulRM *  this->offsetTM;
    rightUpperLegTransform->setMatrix(matrix);
    this->relativeRightUpperLegRotationMatrix = rotationMatrix;
}

void Model::SetRightLowerLegRotation(QQuaternion quaternion)
{
    QMatrix4x4 rotationMatrix = QMatrix4x4(quaternion.toRotationMatrix());
    QMatrix4x4 parentRotationMatrix = this->relativeRightUpperLegRotationMatrix;
    QMatrix4x4 matrix = this->rllOffsetTM * this->offsetTM.inverted() * parentRotationMatrix.inverted() * rotationMatrix * this->offsetTM;
    rightLowerLegTransform->setMatrix(matrix);
    this->relativeRightLowerLegRotationMatrix = rotationMatrix;
}
