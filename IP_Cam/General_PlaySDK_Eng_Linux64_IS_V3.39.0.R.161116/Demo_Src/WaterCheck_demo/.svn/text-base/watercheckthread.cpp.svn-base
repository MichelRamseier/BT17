#include "watercheckthread.h"

WaterCheckThread::WaterCheckThread(IRunnable *runnable, QObject *parent) :
    QThread(parent),
    m_runnable(runnable)
{
}

void WaterCheckThread::run()
{
    if (NULL != m_runnable)
    {
        m_runnable->run();
    }
}
