#include "fileconvertthread.h"

FileConvertThread::FileConvertThread(IRunnable *runnable, QObject *parent) :
    QThread(parent),
    m_runnable(runnable)
{
}

void FileConvertThread::run()
{
    if (NULL != m_runnable)
    {
        m_runnable->run();
    }
}
