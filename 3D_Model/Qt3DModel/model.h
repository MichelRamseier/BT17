#ifndef MODEL_H
#define MODEL_H

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
#include <Qt3DExtras/QNormalDiffuseSpecularMapMaterial>
#include <Qt3DExtras/QMorphPhongMaterial>

class Model
{
public:
    Model(Qt3DCore::QEntity *sceneRoot);

public slots:
    void Initialize();
    void SetCenterRotation(QQuaternion quaternion);
    void SetLeftUpperArmRotation(QQuaternion quaternion);
    void SetLeftLowerArmRotation(QQuaternion quaternion);
    void SetRightUpperArmRotation(QQuaternion quaternion);
    void SetRightLowerArmRotation(QQuaternion quaternion);
    void SetLeftUpperLegRotation(QQuaternion quaternion);
    void SetLeftLowerLegRotation(QQuaternion quaternion);
    void SetRightUpperLegRotation(QQuaternion quaternion);
    void SetRightLowerLegRotation(QQuaternion quaternion);

private:
    Qt3DCore::QEntity *sceneRoot;

    //transforms
    Qt3DCore::QTransform *centerTransform;
    Qt3DCore::QTransform *leftForearmTransform;
    Qt3DCore::QTransform *leftUpperArmTransform;
    Qt3DCore::QTransform *leftUpperLegTransform;
    Qt3DCore::QTransform *leftLowerLegTransform;
    Qt3DCore::QTransform *rightForearmTransform;
    Qt3DCore::QTransform *rightArmTransform;
    Qt3DCore::QTransform *rightUpperLegTransform;
    Qt3DCore::QTransform *rightLowerLegTransform;
    Qt3DCore::QTransform *headTransform;

    //matrices
    QMatrix4x4 offsetTM;

    QMatrix4x4 relativeCenterRotationMatrix;
    QMatrix4x4 relativeLeftUpperArmRotationMatrix;
    QMatrix4x4 relativeLeftLowerArmRotationMatrix;
    QMatrix4x4 relativeRightUpperArmRotationMatrix;
    QMatrix4x4 relativeRightLowerArmRotationMatrix;
    QMatrix4x4 relativeLeftUpperLegRotationMatrix;
    QMatrix4x4 relativeLeftLowerLegRotationMatrix;
    QMatrix4x4 relativeRightUpperLegRotationMatrix;
    QMatrix4x4 relativeRightLowerLegRotationMatrix;

    QMatrix4x4 leftUpperArmOriginMatrix;
    QMatrix4x4 leftLowerArmOriginMatrix;
    QMatrix4x4 rightUpperArmOriginMatrix;
    QMatrix4x4 rightLowerArmOriginMatrix;
    QMatrix4x4 leftUpperLegOriginMatrix;
    QMatrix4x4 leftLowerLegOriginMatrix;
    QMatrix4x4 rightUpperLegOriginMatrix;
    QMatrix4x4 rightLowerLegOriginMatrix;
    QMatrix4x4 centerOriginMatrix;
    QMatrix4x4 headOriginMatrix;
    QMatrix4x4 luaTM;
    QMatrix4x4 llaOffsetTM;
    QMatrix4x4 ruaTM;
    QMatrix4x4 rlaOffsetTM;
    QMatrix4x4 luaRM;
    QMatrix4x4 llaRM;
    QMatrix4x4 ruaRM;
    QMatrix4x4 rlaRM;
    QMatrix4x4 lulTM;
    QMatrix4x4 lllOffsetTM;
    QMatrix4x4 rulTM;
    QMatrix4x4 rllOffsetTM;
    QMatrix4x4 lulRM;
    QMatrix4x4 lllRM;
    QMatrix4x4 rulRM;
    QMatrix4x4 rllRM;




private slots:
    QMatrix4x4 GetTranslationMatrix(float x, float y, float z);
};

#endif // MODEL_H
