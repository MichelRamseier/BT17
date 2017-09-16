// FilePlayer.h: interface for the CFilePlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEPLAYER_H__9B2B286E_795E_4F5A_883B_7932A3397FF2__INCLUDED_)
#define AFX_FILEPLAYER_H__9B2B286E_795E_4F5A_883B_7932A3397FF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IPlay.h"

namespace FileState
{
	//状态迁移表，表述状态间的变迁关系。0表示关闭，1表示打开，2表示无变化
	static int stateTable[STATE_SIZE][STATE_SIZE] = {
		/*				Play	Pause	Stop	ToBegin	ToEnd	BackOne	One		Slow	Fast */
		/*Play*/		{0,		1,		1,		1,		1,		0,		1,		1,		1},
		/*Pause*/		{1,		0,		1,		1,		1,		2,		1,		0,		0},
		/*Stop*/		{1,		0,		0,		0,		0,		0,		0,		0,		0},
		/*ToBegin*/		{2,		2,		2,		2,		2,		2,		2,		2,		2},
		/*ToEnd*/		{2,		2,		2,		2,		2,		2,		2,		2,		2},
		/*BackOne*/		{1,		0,		1,		1,		1,		2,		1,		0,		0},
		/*OneByOne*/	{1,		0,		1,		1,		1,		2,		1,		0,		0},
		/*Slow*/		{1,		0,		1,		1,		1,		0,		0,		1,		1},
		/*Fast*/		{1,		0,		1,		1,		1,		0,		0,		1,		1}
	};
	
	static int openTable[STATE_SIZE] = {1, 0, 0, 0, 0, 0, 0, 0, 0};
	static int closeTable[STATE_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0};


	class CPlay : public IPlayState
	{
	public:
		virtual int Do(PlayParam* lpPlayParam);
		virtual char* Description(PlayParam* lpPlayParam);
	};

	class CPause : public IPlayState
	{
	public:
		virtual int Do(PlayParam* lpPlayParam);
		virtual char* Description(PlayParam* lpPlayParam);
	};

	class CStop : public IPlayState
	{
	public:
		virtual int Do(PlayParam* lpPlayParam);
		virtual char* Description(PlayParam* lpPlayParam);
	};

	class CToBegin : public IPlayState
	{
	public:
		virtual int Do(PlayParam* lpPlayParam);
		virtual char* Description(PlayParam* lpPlayParam);
	};

	class CToEnd : public IPlayState
	{
	public:
		virtual int Do(PlayParam* lpPlayParam);
		virtual char* Description(PlayParam* lpPlayParam);
	};

	class CBackOne : public IPlayState
	{
	public:
		virtual int Do(PlayParam* lpPlayParam);
		virtual char* Description(PlayParam* lpPlayParam);
	};

	class COneByeOne : public IPlayState
	{
	public:
		virtual int Do(PlayParam* lpPlayParam);
		virtual char* Description(PlayParam* lpPlayParam);
	};

	class CSlow : public IPlayState
	{
	public:
		virtual int Do(PlayParam* lpPlayParam);
		virtual char* Description(PlayParam* lpPlayParam);
	};

	class CFast : public IPlayState
	{
	public:
		virtual int Do(PlayParam* lpPlayParam);
		virtual char* Description(PlayParam* lpPlayParam);
	};
}

class CFilePlayer : public IPlay
{
public:
	CFilePlayer();
	virtual ~CFilePlayer();

	virtual int Open(char* lpszFile, PlayParam* lpPlayParam);
	virtual int Close(PlayParam* lpPlayParam);
	virtual int Do(PlayParam* lpPlayParam);
	virtual int OpenSound(PlayParam* lpPlayParam, BOOL bOpen);
	virtual int SetAudioVolume(PlayParam* lpPlayParam, int nVolume);
	virtual int SetAudioWave(PlayParam* lpPlayParam, int nWave);
	virtual int GetAudioVolume(PlayParam* lpPlayParam);
	virtual char* Description(PlayParam* lpPlayParam);
	virtual int ChangeState(IPlayState* lpState);
	virtual int GetProcess(PlayParam* lpPlayParam);
	virtual int Seek(PlayParam* lpPlayParam, int nPos);
	virtual int SetColor(PlayParam* lpPlayParam, int nSaturation, int nBrightness, int nContrast, int nHue);
	virtual int GetColor(PlayParam* lpPlayParam, int* nSaturation, int* nBrightness, int* nContrast, int* nHue);
	virtual int GetPlayedTime(PlayParam* lpPlayParam);
	virtual int GetTotalTime(PlayParam* lpPlayParam);
	virtual int GetPlayedFrame(PlayParam* lpPlayParam);
	virtual int GetTotalFrame(PlayParam* lpPlayParam);
	virtual int GetRate(PlayParam* lpPlayParam, int* nRate);
	virtual int GetBitrate(PlayParam* lpPlayParam, double* dbBitrate);
	virtual BOOL SnapPicture(PlayParam* lpPlayParam, char* szFileName, int nType);/*nType,0 bmp 1 jpg*/
	virtual int SetDisplayRegion(PlayParam* lpPlayParam, DWORD nRegionNum, DISPLAYRECT *pSrcRect, HWND hDestWnd, BOOL bEnable);
	virtual int GetPicSize(PlayParam* lpPlayParam, LONG *nWidth, LONG *nHeight);
	virtual BOOL SetCurrentFrameNum(PlayParam *lpPlayParam, int nFrameNum);
	virtual BOOL SetPlayedTimeEx(PlayParam *lpPlayParam, int nTime);
	virtual BOOL GetNextKeyFramePos(PlayParam *lpPlayParam, DWORD nValue, int nType, PFRAME_POS pFramePos);
	virtual BOOL GetKeyFramePos(PlayParam *lpPlayParam, DWORD nValue, int nType, PFRAME_POS pFramePos);
	virtual BOOL SetVerticalSync(PlayParam *lpPlayParam, BOOL bVerticalSync);
	virtual BOOL GetQueryInfo(PlayParam *lpPlayParam, int cmdType, char* buf, int buflen, int* returnlen);
	virtual BOOL RegistDrawCallback(PlayParam *lpPlayParam, fDrawCBFun DrawCBFun, void* nUser);
	virtual BOOL SetPlayDirection(PlayParam* lpPlayParam, DWORD emDirection);
    virtual BOOL RenderPrivateData(PlayParam* lpPlayParam, BOOL bTrue);
	virtual BOOL SetEngine(PlayParam* lpPlayParam, int decodeType, int renderType);
private:
	IPlayState* m_lpState;
};


#endif // !defined(AFX_FILEPLAYER_H__9B2B286E_795E_4F5A_883B_7932A3397FF2__INCLUDED_)
