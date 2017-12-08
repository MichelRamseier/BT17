#ifndef CAMERA_H
#define CAMERA_H
#include "cameracontroller.h"
#include <QMessageBox>
#include <QtMath>
#include <QDebug>
#include "UserDefine.h"
#include <iostream>
#include <qfile.h>
#include <qdir.h>
#include <camera.h>


class camera
{
public:
    camera(QString ip, long port, QString username, QString pw);
};

#endif // CAMERA_H
