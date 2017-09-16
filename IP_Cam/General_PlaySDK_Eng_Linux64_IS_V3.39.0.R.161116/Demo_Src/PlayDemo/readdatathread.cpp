#include "readdatathread.h"

ReadDataThread::ReadDataThread(IRunnable* runnable, QObject *parent) :
    m_runnable(runnable),
    QThread(parent)
{
}

void ReadDataThread::run()
{
    if (NULL != m_runnable)
    {
        m_runnable->run();
    }
}
