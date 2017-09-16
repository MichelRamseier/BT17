#ifndef FileConvertThread_H
#define FileConvertThread_H

#include <QThread>

class IRunnable
{
public:
    virtual ~IRunnable() {}

public:
    virtual void run() = 0;
};

class FileConvertThread : public QThread
{
    Q_OBJECT
public:
    explicit FileConvertThread(IRunnable* runnable, QObject *parent = 0);
    
signals:
    
public slots:

protected:
    virtual void run();
    
private:
    IRunnable* m_runnable;
};

#endif // FileConvertThread_H
