// Player.h: interface for the CPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYER_H__9DC81D4F_E754_4C5F_8C69_B621C8D09651__INCLUDED_)
#define AFX_PLAYER_H__9DC81D4F_E754_4C5F_8C69_B621C8D09651__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IPlay.h"

class CPlayer  
{
public:
	//状态迁移表，直接暴露出来方便调用
	int stateTable[STATE_SIZE][STATE_SIZE];
	int openTable[STATE_SIZE];
	int closeTable[STATE_SIZE];
public:
	/*
	* 采用单件模式，因为CPlayer需要被不同的UI所使用，
	* 逻辑会分散到各处，单件模式可以避免直接的依赖关系
	*/
	static CPlayer* Instance();

	enum TYPE {FILE, FILESTREAM};
    int Open(TYPE eType, char* lpszFile, HWND hWnd, IWindowEvent* wnd);
	int Close();
	int ChangeState(PLAY_STATE nState);
	int Do();
	int OpenSound(BOOL bOpen);
	int SetAudioVolume(int nVolume);
	int GetAudioVolume();
	int SetAudioWave(int nWave);
	char* Description(); 
	int GetProcess();
	int Seek(int nPos);
	int SetColor(int nSaturation, int nBrightness, int nContrast, int nHue);
	int GetColor(int* nSaturation, int* nBrightness, int* nContrast, int* nHue);
	int GetPlayedTime();
	int GetTotalTime();
	int GetPlayedFrame();
	int GetTotalFrame();
	int GetPicture(int* nWidth, int* nHeight);
	int GetRate(int* nRate);
	int GetBitrate(double* dbBitrate);
	int SnapPicture(char* szFileName, int nType);
	int SetDisplayRegion(DWORD nRegionNum, DISPLAYRECT *pSrcRect, HWND hDestWnd, BOOL bEnable);
	BOOL GetPicSize(LONG *width, LONG *height);
	BOOL SetCurrentFrameNum(int frameNum);
	BOOL SetPlayedTiemEx(int time);
	BOOL GetNextKeyFramePos(DWORD nValue, int nType, PFRAME_POS pFramePos);
	BOOL GetKeyFramePos(DWORD nValue, int nType, PFRAME_POS pFramePos);
	BOOL SetVerticalSync(bool bVerticalSync);
	BOOL GetQueryInfo(int cmdType, char* buf, int buflen, int* returnlen);
	BOOL IsIndexCreated();
	BOOL RegistDrawCallback(fDrawCBFun cbDrawCBFun,void* nUser);
	BOOL SetPlayDirection(DWORD emDirection);
    BOOL RenderPrivateData(BOOL bTrue);
	BOOL SetEngine(int decodeType, int renderType);

protected:
	int CreateFile();
	int CreateFileStream();
	int Destroy();
private:
	/*由单件创建，其它类无法创建*/
	CPlayer();
	virtual ~CPlayer();
private:
	IPlayState* m_lpState[STATE_SIZE];
	PlayParam m_playParam;
	IPlay* m_lpPlay;
};

#endif // !defined(AFX_PLAYER_H__9DC81D4F_E754_4C5F_8C69_B621C8D09651__INCLUDED_)
