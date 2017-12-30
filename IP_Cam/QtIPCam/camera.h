#ifndef CAMERA_H
#define CAMERA_H

#include <QString>
#include <QTimer>


class Camera
{
public:
    Camera(QString ip, long port, QString username, QString pw);
    ~Camera();
};

#endif // CAMERA_H
