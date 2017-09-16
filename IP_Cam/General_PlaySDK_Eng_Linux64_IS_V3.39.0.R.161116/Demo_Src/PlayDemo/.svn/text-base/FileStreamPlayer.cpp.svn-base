// FileStreamPlayer.cpp: implementation of the CFileStreamPlayer class.
//
//////////////////////////////////////////////////////////////////////
#define _FILE_OFFSET_BITS 64

#include "FileStreamPlayer.h"
#include "dhplay.h"
#include "dhplayEx.h"
#include <unistd.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileStreamPlayer::CFileStreamPlayer()
{
	m_lpPlayParam = NULL;
    m_pThread     = NULL;
}

CFileStreamPlayer::~CFileStreamPlayer()
{

}

/*
int WINAPI ThreadProc(LPVOID lpvData)
{
	CFileStreamPlayer* lpPlayer = (CFileStreamPlayer*)lpvData;
	return lpPlayer->OnProc();
}
*/

void CFileStreamPlayer::run()
{
    OnProc();
}

void CALLBACK EncTypeChangeFunC(LONG nPort, void* nUser)
{

}

int CFileStreamPlayer::Open(char* lpszFile, PlayParam* lpPlayParam)
{
	FILE* fDav = fopen(lpszFile, "rb");
	if(fDav==NULL)
		return -1;
	if(fseek(fDav, 0, SEEK_END) == -1)
		return -1;
	fpos_t fPos;
	fgetpos(fDav, &fPos);
	fseek(fDav, 0, SEEK_SET);
	lpPlayParam->lpfDav = fDav;
#ifdef Q_OS_LINUX
    lpPlayParam->nDavSize = fPos.__pos;
#else
	lpPlayParam->nDavSize = fPos;
#endif
	 
	m_lpPlayParam = lpPlayParam;
	
	PLAY_SetEncTypeChangeCallBack(lpPlayParam->nPort, EncTypeChangeFunC, (void*)lpPlayParam->pMainWnd);
	PLAY_SetStreamOpenMode(lpPlayParam->nPort, STREAME_FILE);
	PLAY_OpenStream(lpPlayParam->nPort, NULL, 0, 800*1024);

    WaitThreadExit();

//    m_pThread = new ReadDataThread(this);
//    m_isExit = false;
//    m_pThread->start();
    /*
	m_hExit = CreateEvent(NULL, FALSE, FALSE, NULL);
	DWORD dwThreadID;
	m_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, this, NULL, &dwThreadID);
    */

	return 1;
}

void CFileStreamPlayer::WaitThreadExit()
{
    if (NULL != m_pThread)
    {
        m_isExit = true;
        if (m_pThread->isRunning())
        {
            m_pThread->wait();
        }

        delete m_pThread;
        m_pThread = NULL;
    }
}

int CFileStreamPlayer::Close(PlayParam* lpPlayParam)
{
    WaitThreadExit();
    /*
	SetEvent(m_hExit);
	if(WaitForSingleObject(m_hThread, 5000) != WAIT_OBJECT_0)
	{
		TerminateThread(m_hThread, -1);
	}
    */

	PLAY_Stop(lpPlayParam->nPort);
	PLAY_CloseStream(lpPlayParam->nPort);

	if(lpPlayParam->lpfDav)
	{
		fclose(lpPlayParam->lpfDav);
		lpPlayParam->lpfDav= NULL;
	}

    /*
	if (NULL != m_hExit)
	{
		CloseHandle(m_hExit);
		m_hExit = NULL;
	}

	if (NULL != m_hThread)
	{
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
    */
	return 1;
}

int CFileStreamPlayer::Do(PlayParam* lpPlayParam)
{
    char* pDesc = m_lpState->Description(lpPlayParam);
    if ((NULL != pDesc) && (strcmp(pDesc, "Stop") == 0))
    {
        WaitThreadExit();
    }
    else if ((NULL != pDesc) && (strcmp(pDesc, "Play") == 0))
    {
        if (NULL != m_pThread)
        {
            WaitThreadExit();
        }
        m_pThread = new ReadDataThread(this);
        m_isExit = false;
        m_pThread->start();
    }

	return m_lpState->Do(lpPlayParam);
}

int CFileStreamPlayer::OpenSound(PlayParam* lpPlayParam, BOOL bOpen)
{
	lpPlayParam->bOpenAudio = bOpen;
	if(bOpen)
		return PLAY_PlaySoundShare(lpPlayParam->nPort);
	else
		return PLAY_StopSoundShare(lpPlayParam->nPort);
}

int CFileStreamPlayer::SetAudioVolume(PlayParam* lpPlayParam, int nVolume)
{
	return PLAY_SetVolume(lpPlayParam->nPort, nVolume);
}

int CFileStreamPlayer::SetAudioWave(PlayParam* lpPlayParam, int nWave)
{
	return PLAY_AdjustWaveAudio(lpPlayParam->nPort, nWave);
}

int CFileStreamPlayer::GetAudioVolume(PlayParam* lpPlayParam)
{
	return PLAY_GetVolume(lpPlayParam->nPort);
}

char* CFileStreamPlayer::Description(PlayParam* lpPlayParam)
{
	return m_lpState->Description(lpPlayParam);
}

int CFileStreamPlayer::ChangeState(IPlayState* lpState)
{
	if(lpState==NULL)
		return -1;

	m_lpState = lpState;
	return 1;
}

int CFileStreamPlayer::GetProcess(PlayParam* lpPlayParam)
{
	fpos_t fPos;
	fgetpos(lpPlayParam->lpfDav, &fPos);
#ifdef Q_OS_LINUX
    return int(fPos.__pos*100/lpPlayParam->nDavSize);
#else
	return int(fPos*100/lpPlayParam->nDavSize);
#endif
}

int CFileStreamPlayer::Seek(PlayParam* lpPlayParam, int nPos)
{
	if(nPos<0 || nPos>100)
		return -1;

	fseeko(lpPlayParam->lpfDav, nPos*lpPlayParam->nDavSize/100, SEEK_SET);
	return 1;
}

int CFileStreamPlayer::SetColor(PlayParam* lpPlayParam, int nSaturation, int nBrightness, int nContrast, int nHue)
{
	return PLAY_SetColor(lpPlayParam->nPort, 0, nBrightness, nContrast, nSaturation, nHue);
}

int CFileStreamPlayer::GetColor(PlayParam* lpPlayParam, int* nSaturation, int* nBrightness, int* nContrast, int* nHue)
{
	return PLAY_GetColor(lpPlayParam->nPort, 0, nBrightness, nContrast, nSaturation, nHue);
}

int CFileStreamPlayer::GetPlayedTime(PlayParam* lpPlayParam)
{
	return 0;
}

int CFileStreamPlayer::GetTotalTime(PlayParam* lpPlayParam)
{
	return 0;
}

int CFileStreamPlayer::GetPlayedFrame(PlayParam* lpPlayParam)
{
	return 0;
}

int CFileStreamPlayer::GetTotalFrame(PlayParam* lpPlayParam)
{
	return 0;
}

int CFileStreamPlayer::GetRate(PlayParam* lpPlayParam, int* nRate)
{
	DWORD dwRate = PLAY_GetCurrentFrameRate(lpPlayParam->nPort);
	*nRate = dwRate;
	return dwRate;
}

int CFileStreamPlayer::GetBitrate(PlayParam* lpPlayParam, double* dbBitrate)
{
	return PLAY_GetRealFrameBitRate(lpPlayParam->nPort, dbBitrate);
}

BOOL CFileStreamPlayer::SnapPicture(PlayParam* lpPlayParam, char* szFileName, int nType)/*nType,0 bmp 1 jpg*/
{
	return PLAY_CatchPicEx(lpPlayParam->nPort, szFileName, tPicFormats(nType));
}

int CFileStreamPlayer::SetDisplayRegion(PlayParam* lpPlayParam, DWORD nRegionNum, DISPLAYRECT *pSrcRect, HWND hDestWnd, BOOL bEnable)
{
	return PLAY_SetDisplayRegion(lpPlayParam->nPort, nRegionNum, pSrcRect, hDestWnd, bEnable);
}

int CFileStreamPlayer::GetPicSize(PlayParam* lpPlayParam, LONG *width, LONG *height)
{
	return PLAY_GetPictureSize(lpPlayParam->nPort, width, height);
}

BOOL CFileStreamPlayer::SetVerticalSync(PlayParam *lpPlayParam, BOOL bVerticalSync)
{
	return PLAY_VerticalSyncEnable(lpPlayParam->nPort, bVerticalSync);
}

/*Receive video info. cmdType: PLAY_CMD_GetTime  Encoding time info;
							   PLAY_CMD_GetFileRate  Frame rate info;
							   PLAY_CMD_GetMediaInfo  Media info*/
BOOL CFileStreamPlayer::GetQueryInfo(PlayParam *lpPlayParam, int cmdType, char* buf, int buflen, int* returnlen)
{
	return PLAY_QueryInfo(lpPlayParam->nPort, cmdType, buf, buflen, returnlen);
}

BOOL CFileStreamPlayer::RegistDrawCallback(PlayParam *lpPlayParam, fDrawCBFun DrawCBFun, void* nUser)
{
	return PLAY_RigisterDrawFun(lpPlayParam->nPort, DrawCBFun, nUser);
}

BOOL CFileStreamPlayer::SetPlayDirection(PlayParam* lpPlayParam, DWORD emDirection)
{
	return PLAY_SetPlayDirection(lpPlayParam->nPort, emDirection);
}

int CFileStreamPlayer::OnProc()
{
	const int READ_SIZE = 1024*128;
	unsigned char* lpReadBuf = new unsigned char[READ_SIZE];
	/*Add bInput to prevent long-time loop*/
	BOOL bInput = TRUE;
	int nReadSize = 0;
    //while(WaitForSingleObject(m_hExit, 0) != WAIT_OBJECT_0)/*Set short time interval to prevent slow data sending during quick play*/
    while (!m_isExit)
    {
		if(bInput!=FALSE)
		{
			nReadSize = fread(lpReadBuf, 1, READ_SIZE, m_lpPlayParam->lpfDav);
			if(nReadSize <= 0)
			{
                usleep(2);
                continue;
			}
		}

		/*Continue sending data if failed*/
		bInput = PLAY_InputData(m_lpPlayParam->nPort, lpReadBuf, nReadSize);
		if(bInput==FALSE)
		{
            usleep(2);
		}
	}

	delete []lpReadBuf;

	return 1;
}

BOOL CFileStreamPlayer::RenderPrivateData(PlayParam* lpPlayParam, BOOL bTrue)
{
    PLAY_RenderPrivateData(lpPlayParam->nPort, bTrue, 0);
}

BOOL CFileStreamPlayer::SetEngine(PlayParam* lpPlayParam, int decodeType, int renderType)
{
	return PLAY_SetEngine(lpPlayParam->nPort, (DecodeType)decodeType, (RenderType)renderType);
}

namespace FileStreamState
{
	/*CStop*/
	int CStop::Do(PlayParam* lpPlayParam)
	{
		PLAY_Stop(lpPlayParam->nPort);
		fseek(lpPlayParam->lpfDav, 0, SEEK_SET);
		return 1;
	}
	char* CStop::Description(PlayParam* lpPlayParam)
	{
		return "Stop";
	}

	/*CToBegin*/
	int CToBegin::Do(PlayParam* lpPlayParam)
	{
		fseek(lpPlayParam->lpfDav, 0, SEEK_SET);
		return 1;
	}
	char* CToBegin::Description(PlayParam* lpPlayParam)
	{
		return NULL;
	}

	/*CToEnd*/
	int CToEnd::Do(PlayParam* lpPlayParam)
	{
		fseek(lpPlayParam->lpfDav, 0, SEEK_END);
		return 1;
	}
	char* CToEnd::Description(PlayParam* lpPlayParam)
	{
		return NULL;
	}
}
