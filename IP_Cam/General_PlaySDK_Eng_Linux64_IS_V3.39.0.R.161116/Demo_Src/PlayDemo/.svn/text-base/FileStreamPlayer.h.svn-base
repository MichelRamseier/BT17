// FileStreamPlayer.h: interface for the CFileStreamPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILESTREAMPLAYER_H__7F04C817_EA84_45C6_8052_E69BBCF9A3B3__INCLUDED_)
#define AFX_FILESTREAMPLAYER_H__7F04C817_EA84_45C6_8052_E69BBCF9A3B3__INCLUDED_

#include "IPlay.h"
#include "FilePlayer.h" /*本无依赖关系，但有些方法可以共用*/
#include "readdatathread.h"

namespace FileStreamState
{
	//状态迁移表，表述状态间的变迁路径。0表示关闭，1表示打开，2表示无变化
	static int stateTable[STATE_SIZE][STATE_SIZE] = {
		/*				Play	Pause	Stop	ToBegin	ToEnd	BackOne	One		Slow	Fast */
		/*Play*/		{0,		1,		1,		1,		1,		0,		1,		1,		1},
		/*Pause*/		{1,		0,		1,		1,		1,		0,		1,		0,		0},
		/*Stop*/		{1,		0,		0,		0,		0,		0,		0,		0,		0},
		/*ToBegin*/		{2,		2,		2,		2,		2,		0,		2,		2,		2},
		/*ToEnd*/		{2,		2,		2,		2,		2,		0,		2,		2,		2},
		/*BackOne*/		{2,		2,		2,		2,		2,		0,		2,		2,		2},
		/*OneByOne*/	{1,		0,		1,		1,		1,		0,		1,		0,		0},
		/*Slow*/		{1,		0,		1,		1,		1,		0,		0,		1,		1},
		/*Fast*/		{1,		0,		1,		1,		1,		0,		0,		1,		1}
	};
	
	static int openTable[STATE_SIZE] = {1, 0, 0, 0, 0, 0, 0, 0, 0};
	static int closeTable[STATE_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

	/*共用文件播放的方法*/
	typedef FileState::CPlay CPlay;
	typedef FileState::CPause CPause;
	typedef FileState::CBackOne CBackOne;
	typedef FileState::COneByeOne COneByeOne;
	typedef FileState::CSlow CSlow;
	typedef FileState::CFast CFast;

	class CStop : public IPlayState
	{
		virtual int Do(PlayParam* lpPlayParam);
		virtual char* Description(PlayParam* lpPlayParam);
	};

	class CToBegin : public IPlayState
	{
		virtual int Do(PlayParam* lpPlayParam);
		virtual char* Description(PlayParam* lpPlayParam);
	};

	class CToEnd : public IPlayState
	{
		virtual int Do(PlayParam* lpPlayParam);
		virtual char* Description(PlayParam* lpPlayParam);
	};
}

class CFileStreamPlayer  : public IPlay, public IRunnable
{
public:
	CFileStreamPlayer();
	virtual ~CFileStreamPlayer();

	virtual int Open(char* lpszFile, PlayParam* lpPlayParam);
	virtual int Close(PlayParam* lpPlayParam);
	virtual int Do(PlayParam* lpPlayParam);
	virtual int OpenSound(PlayParam* lpPlayParam, BOOL bOpen);
	virtual int SetAudioVolume(PlayParam* lpPlayParam, int nVolume);
	virtual int GetAudioVolume(PlayParam* lpPlayParam);
	virtual int SetAudioWave(PlayParam* lpPlayParam, int nWave);
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
	virtual int GetPicSize(PlayParam* lpPlayParam, LONG *width, LONG *height);
    virtual BOOL SetCurrentFrameNum(PlayParam *lpPlayParam, int frameNum){return true;}
    virtual BOOL SetPlayedTimeEx(PlayParam *lpPlayParam, int nTime){return true;}
    virtual BOOL GetNextKeyFramePos(PlayParam *lpPlayParam, DWORD nValue, int nType, PFRAME_POS pFramePos){return true;}
	virtual BOOL GetKeyFramePos(PlayParam *lpPlayParam, DWORD nValue, int nType, PFRAME_POS pFramePos){return true;}
	virtual BOOL SetVerticalSync(PlayParam *lpPlayParam, BOOL bVerticalSync);
	virtual BOOL GetQueryInfo(PlayParam *lpPlayParam, int cmdType, char* buf, int buflen, int* returnlen);
	virtual BOOL RegistDrawCallback(PlayParam *lpPlayParam, fDrawCBFun DrawCBFun, void* nUser);
	virtual BOOL SetPlayDirection(PlayParam* lpPlayParam, DWORD emDirection);
    virtual BOOL RenderPrivateData(PlayParam* lpPlayParam, BOOL bTrue);
	virtual BOOL SetEngine(PlayParam* lpPlayParam, int decodeType, int renderType);
    virtual void run();

public:
    int OnProc();

private:
    void WaitThreadExit();

private:
	IPlayState* m_lpState;

	/*线程中使用，也可定义结构体传递给线程，为代码简单而直接保存变量*/
	PlayParam* m_lpPlayParam; 
	
    //HANDLE m_hExit;
    //HANDLE m_hThread;
    bool            m_isExit;
    ReadDataThread* m_pThread;
};

#endif // !defined(AFX_FILESTREAMPLAYER_H__7F04C817_EA84_45C6_8052_E69BBCF9A3B3__INCLUDED_)
