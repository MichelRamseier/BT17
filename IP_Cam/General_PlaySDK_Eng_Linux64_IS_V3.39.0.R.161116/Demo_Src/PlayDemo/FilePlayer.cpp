// FilePlayer.cpp: implementation of the CFilePlayer class.
//
//////////////////////////////////////////////////////////////////////

#include "FilePlayer.h"
#include "dhplay.h"
#include "dhplayEx.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CFilePlayer::CFilePlayer()
{
	m_lpState = NULL;
}

CFilePlayer::~CFilePlayer()
{
	m_lpState = NULL;
}

void CALLBACK FileRefDone(DWORD nPort, BOOL bIndexCreated, void* nUser)
{
	PlayParam* lpPlayParam = (PlayParam*)nUser;
	
	lpPlayParam->bIndexCreated = bIndexCreated;

    IWindowEvent* pWindowEvent = (IWindowEvent*)lpPlayParam->pMainWnd;
    if (NULL != pWindowEvent)
    {
        pWindowEvent->onFileIndexEvent(bIndexCreated);
    }
//	PostMessage(lpPlayParam->pMainWnd, 0x401, bIndexCreated, NULL);
}

void CALLBACK EncTypeChangeFunc(LONG nPort, void* nUser)
{

}

int CFilePlayer::Open(char* lpszFile, PlayParam* lpPlayParam)
{
	PLAY_SetEncTypeChangeCallBack(lpPlayParam->nPort, EncTypeChangeFunc, (void*)lpPlayParam->pMainWnd);
	PLAY_SetFileRefCallBackEx(lpPlayParam->nPort, FileRefDone, (void*)lpPlayParam);
	return PLAY_OpenFile(lpPlayParam->nPort, lpszFile);
}

int CFilePlayer::Close(PlayParam* lpPlayParam)
{
	PLAY_Stop(lpPlayParam->nPort);
	return PLAY_CloseFile(lpPlayParam->nPort);
}

int CFilePlayer::Do(PlayParam* lpPlayParam)
{
	return m_lpState->Do(lpPlayParam);
}

int CFilePlayer::OpenSound(PlayParam* lpPlayParam, BOOL bOpen)
{
	lpPlayParam->bOpenAudio = bOpen;
	if(bOpen)
		return PLAY_PlaySoundShare(lpPlayParam->nPort);
	else
		return PLAY_StopSoundShare(lpPlayParam->nPort);
}

int CFilePlayer::SetAudioVolume(PlayParam* lpPlayParam, int nVolume)
{
	return PLAY_SetVolume(lpPlayParam->nPort, nVolume);
}

int CFilePlayer::SetAudioWave(PlayParam* lpPlayParam, int nWave)
{
	return PLAY_AdjustWaveAudio(lpPlayParam->nPort, nWave);
}

int CFilePlayer::GetAudioVolume(PlayParam* lpPlayParam)
{
	return PLAY_GetVolume(lpPlayParam->nPort);
}

char* CFilePlayer::Description(PlayParam* lpPlayParam)
{
 	if(m_lpState == NULL)
 		return NULL;
	return m_lpState->Description(lpPlayParam);
}

int CFilePlayer::ChangeState(IPlayState* lpState)
{
	m_lpState = lpState;
	return 1;
}

int CFilePlayer::GetProcess(PlayParam* lpPlayParam)
{
	float fProc = PLAY_GetPlayPos(lpPlayParam->nPort)+0.001;/*±ÜÃâ 99.9%·µ»Ø99*/
	return int(fProc*100);
}

int CFilePlayer::Seek(PlayParam* lpPlayParam, int nPos)
{
	float fPos = float(nPos)/100;
	return PLAY_SetPlayPos(lpPlayParam->nPort, fPos);
}

int CFilePlayer::SetColor(PlayParam* lpPlayParam, int nSaturation, int nBrightness, int nContrast, int nHue)
{
	return PLAY_SetColor(lpPlayParam->nPort, 0, nBrightness, nContrast, nSaturation, nHue);
}

int CFilePlayer::GetColor(PlayParam* lpPlayParam, int* nSaturation, int* nBrightness, int* nContrast, int* nHue)
{
	return PLAY_GetColor(lpPlayParam->nPort, 0, nBrightness, nContrast, nSaturation, nHue);
}

int CFilePlayer::GetPlayedTime(PlayParam* lpPlayParam)
{
	return PLAY_GetPlayedTime(lpPlayParam->nPort);
}

int CFilePlayer::GetTotalTime(PlayParam* lpPlayParam)
{
	return PLAY_GetFileTime(lpPlayParam->nPort);
}

int CFilePlayer::GetPlayedFrame(PlayParam* lpPlayParam)
{
	return (PLAY_GetCurrentFrameNum(lpPlayParam->nPort));
}

int CFilePlayer::GetTotalFrame(PlayParam* lpPlayParam)
{
	return PLAY_GetFileTotalFrames(lpPlayParam->nPort);
}

int CFilePlayer::GetRate(PlayParam* lpPlayParam, int* nRate)
{
	DWORD dwRate = PLAY_GetCurrentFrameRate(lpPlayParam->nPort);
	*nRate = dwRate;
	return dwRate;
}

int CFilePlayer::GetBitrate(PlayParam* lpPlayParam, double* dbBitrate)
{
	return PLAY_GetRealFrameBitRate(lpPlayParam->nPort, dbBitrate);
}

BOOL CFilePlayer::SnapPicture(PlayParam* lpPlayParam, char* szFileName, int nType)/*nType,0 bmp 1 jpg*/
{
	return PLAY_CatchPicEx(lpPlayParam->nPort, szFileName, tPicFormats(nType));
}

int CFilePlayer::SetDisplayRegion(PlayParam* lpPlayParam, DWORD nRegionNum, DISPLAYRECT *pSrcRect, HWND hDestWnd, BOOL bEnable)
{
	return PLAY_SetDisplayRegion(lpPlayParam->nPort, nRegionNum, pSrcRect, hDestWnd, bEnable);
}

int CFilePlayer::GetPicSize(PlayParam* lpPlayParam, LONG *width, LONG *height)
{
	return PLAY_GetPictureSize(lpPlayParam->nPort, width, height);
}

BOOL CFilePlayer::SetCurrentFrameNum(PlayParam *lpPlayParam, int nFrameNum)
{
	return PLAY_SetCurrentFrameNum(lpPlayParam->nPort, nFrameNum);
}

BOOL CFilePlayer::SetPlayedTimeEx(PlayParam *lpPlayParam, int nTime)
{
	return PLAY_SetPlayedTimeEx(lpPlayParam->nPort, nTime);
}

BOOL CFilePlayer::GetNextKeyFramePos(PlayParam *lpPlayParam, DWORD nValue, int nType, PFRAME_POS pFramePos)
{
	return PLAY_GetNextKeyFramePos(lpPlayParam->nPort, nValue, nType, pFramePos);
}

BOOL CFilePlayer::GetKeyFramePos(PlayParam *lpPlayParam, DWORD nValue, int nType, PFRAME_POS pFramePos)
{
	return PLAY_GetKeyFramePos(lpPlayParam->nPort, nValue, nType, pFramePos);
}

BOOL CFilePlayer::SetVerticalSync(PlayParam *lpPlayParam, BOOL bVerticalSync)
{
	return PLAY_VerticalSyncEnable(lpPlayParam->nPort, bVerticalSync);
}


BOOL CFilePlayer::GetQueryInfo(PlayParam *lpPlayParam, int cmdType, char* buf, int buflen, int* returnlen)
{
	return PLAY_QueryInfo(lpPlayParam->nPort, cmdType, buf, buflen, returnlen);
}

BOOL CFilePlayer::RegistDrawCallback(PlayParam *lpPlayParam, fDrawCBFun DrawCBFun, void* nUser)
{
	return PLAY_RigisterDrawFun(lpPlayParam->nPort, DrawCBFun, nUser);
}

BOOL CFilePlayer::SetPlayDirection(PlayParam* lpPlayParam, DWORD emDirection)
{
	return PLAY_SetPlayDirection(lpPlayParam->nPort, emDirection);
}

BOOL CFilePlayer::RenderPrivateData(PlayParam* lpPlayParam, BOOL bTrue)
{
    PLAY_RenderPrivateData(lpPlayParam->nPort, bTrue, 0);
}

BOOL CFilePlayer::SetEngine(PlayParam* lpPlayParam, int decodeType, int renderType)
{
	return PLAY_SetEngine(lpPlayParam->nPort, (DecodeType)decodeType, (RenderType)renderType);
}

/************************************************************************/
/* States                                                               */
/************************************************************************/

namespace FileState
{
	/*CPlay*/
	int CPlay::Do(PlayParam* lpPlayParam)
	{
		lpPlayParam->fSpeedCoff = 1.0;
		
		if(!PLAY_Play(lpPlayParam->nPort, lpPlayParam->hWnd))
			return -1;

		/*call PLAY_Pause function to differentiate pause state and fast\slow state.*/
		if(!PLAY_Pause(lpPlayParam->nPort, FALSE))
			return -1;

		if(lpPlayParam->bOpenAudio && !PLAY_PlaySoundShare(lpPlayParam->nPort))
			return -1;

		return 1;
	}
	char* CPlay::Description(PlayParam* lpPlayParam)
	{
		return "Play";
	}

	/*CPause*/
	int CPause::Do(PlayParam* lpPlayParam)
	{
		return PLAY_Pause(lpPlayParam->nPort, TRUE);
	}
	char* CPause::Description(PlayParam* lpPlayParam)
	{
		return "Pause";
	}

	/*CStop*/
	int CStop::Do(PlayParam* lpPlayParam)
	{
		return PLAY_Stop(lpPlayParam->nPort);
	}
	char* CStop::Description(PlayParam* lpPlayParam)
	{
		return "Stop";
	}
	
	/*CToBegin*/
	int CToBegin::Do(PlayParam* lpPlayParam)
	{
		return PLAY_SetPlayPos(lpPlayParam->nPort, 0.00000);
	}
	char* CToBegin::Description(PlayParam* lpPlayParam)
	{
        return "";
	}

	/*CToEnd*/
	int CToEnd::Do(PlayParam* lpPlayParam)
	{
		return PLAY_SetPlayPos(lpPlayParam->nPort, 1.000000);
	}
	char* CToEnd::Description(PlayParam* lpPlayParam)
	{
        return "";
	}

	/*CBackOne*/
	int CBackOne::Do(PlayParam* lpPlayParam)
	{
		if(lpPlayParam->bIndexCreated==FALSE)
			return -1;

		PLAY_BackOne(lpPlayParam->nPort);
		return 1;
	}
	char* CBackOne::Description(PlayParam* lpPlayParam)
	{
		return "BackOne";
	}

	/*COneByeOne*/
	int COneByeOne::Do(PlayParam* lpPlayParam)
	{
		PLAY_OneByOne(lpPlayParam->nPort);
		return 1;
	}
	char* COneByeOne::Description(PlayParam* lpPlayParam)
	{
		return "OneByOne";
	}

	/*CSlow*/
	int CSlow::Do(PlayParam* lpPlayParam)
	{
		float fSpeedCoff = lpPlayParam->fSpeedCoff/2.0;
		BOOL bRet = PLAY_SetPlaySpeed(lpPlayParam->nPort, fSpeedCoff);
		if(bRet)
		{
			lpPlayParam->fSpeedCoff = fSpeedCoff;
			return 1;
		}
		return -1;
	}
	char* CSlow::Description(PlayParam* lpPlayParam)
	{
		if(lpPlayParam->fSpeedCoff>=0.999999 && lpPlayParam->fSpeedCoff<=1.000001)
		{
			return "Play";
		}
		else
		{
			static char s_szSpeedInfo[48];
			memset(s_szSpeedInfo, 0, sizeof(s_szSpeedInfo));	
            sprintf(s_szSpeedInfo, "%s:%f", "Speed", lpPlayParam->fSpeedCoff);
			return s_szSpeedInfo;
		}
	}

	/*CFast*/
	int CFast::Do(PlayParam* lpPlayParam)
	{
		float fSpeedCoff = lpPlayParam->fSpeedCoff*2.0;
		BOOL bRet = PLAY_SetPlaySpeed(lpPlayParam->nPort, fSpeedCoff);
		if(bRet)
		{
			lpPlayParam->fSpeedCoff = fSpeedCoff;
			return 1;
		}
		return -1;
	}
	char* CFast::Description(PlayParam* lpPlayParam)
	{
		if(lpPlayParam->fSpeedCoff>=0.999999 && lpPlayParam->fSpeedCoff<=1.000001)
		{
			return "Play";
		}
		else
		{
			static char s_szSpeedInfo[48];
			memset(s_szSpeedInfo, 0, sizeof(s_szSpeedInfo));	
            sprintf(s_szSpeedInfo, "%s:%f", "Speed", lpPlayParam->fSpeedCoff);
			return s_szSpeedInfo;
		}
	}
}
