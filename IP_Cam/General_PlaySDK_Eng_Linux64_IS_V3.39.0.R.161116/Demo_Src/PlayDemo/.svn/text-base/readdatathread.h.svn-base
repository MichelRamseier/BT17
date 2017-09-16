#ifndef READDATATHREAD_H
#define READDATATHREAD_H

#include <QThread>

class IRunnable
{
public:
    virtual ~IRunnable() {}

public:
    virtual void run() = 0;
};

class ReadDataThread : public QThread
{
    Q_OBJECT
public:
    explicit ReadDataThread(IRunnable* runnalbe, QObject *parent = 0);
    
protected:
    virtual void run();
    
private:
    IRunnable* m_runnable;
};

#endif // READDATATHREAD_H
