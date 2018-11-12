#ifndef WATERCHECKTHREAD_H
#define WATERCHECKTHREAD_H

#include <QThread>

class IRunnable
{
public:
    virtual ~IRunnable() {}

public:
    virtual void run() = 0;
};

class WaterCheckThread : public QThread
{
    Q_OBJECT
public:
    explicit WaterCheckThread(IRunnable* runnable, QObject *parent = 0);
    
signals:
    
public slots:
    
protected:
    virtual void run();

private:
    IRunnable* m_runnable;
};

#endif // WATERCHECKTHREAD_H
