// PlayStateText.cpp: implementation of the CPlayStateText class.
//
//////////////////////////////////////////////////////////////////////
#include "PlayStateText.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlayStateText::CPlayStateText()
{
	Clear();
}

CPlayStateText::~CPlayStateText()
{

}

void CPlayStateText::SetState(QString szState)
{
    if(szState.isEmpty())
		return;
	m_szState = szState;
}

void CPlayStateText::SetPlayedTime(int nPlayedTime , int nTotalTime)
{
	m_nTotalTime = nTotalTime;
	m_nPlayedTime = nPlayedTime;
}

void CPlayStateText::SetPlayedFrame(int nPlayedFrame, int nTotoalFrame)
{
	m_nTotalFrame = nTotoalFrame;
	m_nPlayedFrame = nPlayedFrame;
}

void CPlayStateText::SetBitrate(double dbBitrate)
{
	m_dbBitrate = dbBitrate;
}

void CPlayStateText::SetRate(int nRate)
{
	m_nRate = nRate;
}

void CPlayStateText::SetPictureSize(int nWidth, int nHeight)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
}

void CPlayStateText::Init(QTextEdit* lpWnd)
{
	m_lpWnd = lpWnd;
}

void CPlayStateText::Clear()
{
    m_szState.clear();
	m_nPlayedTime = 0;
	m_nTotalTime = 0;
	m_nPlayedFrame = 0;
	m_nTotalFrame = 0;
	m_dbBitrate = 0;
	m_nWidth = 0;
	m_nHeight = 0;
	m_nRate = 0;
}

void ChangeChar(char* szBuf, int nSize, char cSrc, char cDest)
{
	for(int i = 0; i < nSize; i++)
	{
		if(szBuf[i] == cSrc) szBuf[i] = cDest;
	}
}

void CPlayStateText::Show()
{
	if(!m_nTotalFrame || !m_nTotalTime)
	{
        m_lpWnd->setText( QString("%1%2*%3%4f/s%5kb/s")
                          .arg(m_szState,-85)
                          .arg(m_nWidth,4)
                          .arg(m_nHeight,4)
                          .arg(m_nRate,8)
                          .arg(int(m_dbBitrate),8 ) );
	}
	else
	{
		int nHour = (m_nPlayedTime/3600) % 24;
		int nMinute = (m_nPlayedTime%3600) /60;
		int nSecond = (m_nPlayedTime%60);
		int nHour2 = (m_nTotalTime/3600) % 24;
		int nMinute2 = (m_nTotalTime%3600) /60;
		int nSecond2= (m_nTotalTime%60);
        QString strTime = QString("%1:%2:%3/%4:%5:%6")
                .arg(nHour,2)
                .arg(nMinute,2)
                .arg(nSecond,2)
                .arg(nHour2,2)
                .arg(nMinute2,2)
                .arg(nSecond2,2);

        m_lpWnd->setText( QString("%1%2*%3%4f/s%5kb/s%6/%7%8")
                          .arg(m_szState,-40)
                          .arg(m_nWidth,4)
                          .arg(m_nHeight,4)
                          .arg(m_nRate,4)
                          .arg(int(m_dbBitrate),8)
                          .arg(m_nPlayedFrame,6)
                          .arg(m_nTotalFrame,-6)
                          .arg(strTime) );
	}
}
