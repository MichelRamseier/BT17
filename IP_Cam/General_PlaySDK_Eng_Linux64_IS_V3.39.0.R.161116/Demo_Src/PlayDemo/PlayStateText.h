// PlayStateText.h: interface for the CPlayStateText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYSTATETEXT_H__6868F88B_5D4B_4581_8F02_77FA1D466F1A__INCLUDED_)
#define AFX_PLAYSTATETEXT_H__6868F88B_5D4B_4581_8F02_77FA1D466F1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <QTextEdit>
#include <QString>

/*
* ����״̬���仯�����ؽ϶࣬������Ϲ�һ�����֡�
*/
class CPlayStateText  
{
public:
	CPlayStateText();
	virtual ~CPlayStateText();

public:
    void SetState(QString szState);
	void SetPlayedTime(int nPlayedTime , int nTotalTime /*0 ��ʾ���ı��ֵ*/);
	void SetPlayedFrame(int nPlayedFrame, int nTotalFrame /*0 ��ʾ���ı��ֵ*/);
	void SetBitrate(double dbBitrate);
	void SetRate(int nRate);
	void SetPictureSize(int nWidth, int nHeight);
	/*���*/
    void Init(QTextEdit* lpWnd);
	void Show();
	void Clear();
private:
    QTextEdit*	m_lpWnd;
	
    QString m_szState;
	int m_nPlayedTime;
	int m_nTotalTime;
	int m_nPlayedFrame;
	int m_nTotalFrame;
	double m_dbBitrate;
	int m_nRate;
	int m_nWidth;
	int m_nHeight;
};

#endif // !defined(AFX_PLAYSTATETEXT_H__6868F88B_5D4B_4581_8F02_77FA1D466F1A__INCLUDED_)
