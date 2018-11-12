// Player.cpp: implementation of the CPlayer class.
//
//////////////////////////////////////////////////////////////////////

#include "Player.h"
#include "FilePlayer.h"
#include "FileStreamPlayer.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CPlayer::CPlayer()
{	
	memset(m_lpState, 0, sizeof(m_lpState));
	m_lpPlay = NULL;

	m_playParam.nPort = 0;
	m_playParam.hWnd = 0;
	m_playParam.bOpenAudio = 0;

	memset(stateTable, 0, sizeof(stateTable));
	memset(openTable, 0, sizeof(openTable));
	memset(closeTable, 0, sizeof(closeTable));
}

CPlayer::~CPlayer()
{
	memset(m_lpState, 0, sizeof(m_lpState));
	m_lpPlay = NULL;
}

CPlayer* CPlayer::Instance()
{
	static CPlayer* lpPlayer = NULL;
	if(NULL == lpPlayer)
	{
		/*memory leak*/
		lpPlayer = new CPlayer;
	}

	return lpPlayer;
}


int CPlayer::Open(TYPE eType, char* lpszFile, HWND playWnd, IWindowEvent* MainDlgWnd)
{
	if(eType == FILE)
		CreateFile();
	else if(eType == FILESTREAM)
		CreateFileStream();
	else
		return -1;
	
	m_playParam.bIndexCreated = FALSE;
	m_playParam.hWnd = playWnd;
    m_playParam.pMainWnd = MainDlgWnd;
	return m_lpPlay->Open(lpszFile, &m_playParam);
}

int CPlayer::Close()
{
	if(m_lpPlay)
		m_lpPlay->Close(&m_playParam);
	Destroy();

	return 1;
}

int CPlayer::GetProcess()
{
	if(!m_lpPlay)
		return -1;

	return m_lpPlay->GetProcess(&m_playParam);
}

int CPlayer::Seek(int nPos)
{
	if(!m_lpPlay)
		return -1;

	return m_lpPlay->Seek(&m_playParam, nPos);
}

int CPlayer::SetColor(int nSaturation, int nBrightness, int nContrast, int nHue)
{
	if(!m_lpPlay)
		return -1;
	
	return m_lpPlay->SetColor(&m_playParam, nSaturation, nBrightness, nContrast, nHue);
}

int CPlayer::GetColor(int* nSaturation, int* nBrightness, int* nContrast, int* nHue)
{
	if(!m_lpPlay)
		return -1;
	
	return m_lpPlay->GetColor(&m_playParam, nSaturation, nBrightness, nContrast, nHue);
}

int CPlayer::GetPlayedTime()
{
	if(!m_lpPlay)
		return -1;
	
	return m_lpPlay->GetPlayedTime(&m_playParam);
}

int CPlayer::GetTotalTime()
{
	if(!m_lpPlay)
		return -1;

	return m_lpPlay->GetTotalTime(&m_playParam);
}

int CPlayer::GetPlayedFrame()
{
	if(!m_lpPlay)
		return -1;

	return m_lpPlay->GetPlayedFrame(&m_playParam);
}

int CPlayer::GetTotalFrame()
{
	if(!m_lpPlay)
		return -1;

	return m_lpPlay->GetTotalFrame(&m_playParam);
}

int CPlayer::GetPicture(int* nWidth, int* nHeight)
{
	if(!m_lpPlay)
		return -1;

	return m_lpPlay->GetPicSize(&m_playParam, (LONG *)nWidth, (LONG *)nHeight);
}

int CPlayer::GetRate(int* nRate)
{
	if(!m_lpPlay)
		return -1;

	return m_lpPlay->GetRate(&m_playParam, nRate);
}

int CPlayer::GetBitrate(double* dbBitrate)
{
	if(!m_lpPlay)
		return -1;

	return m_lpPlay->GetBitrate(&m_playParam, dbBitrate);
}

int CPlayer::SnapPicture(char* szFileName, int nType)
{
	if(!m_lpPlay)
		return -1;

	return m_lpPlay->SnapPicture(&m_playParam, szFileName, nType);
}

BOOL CPlayer::GetPicSize(LONG *width, LONG *height)
{
	if (m_lpPlay == NULL)
		return FALSE;
	return m_lpPlay->GetPicSize(&m_playParam, width, height);
}

BOOL CPlayer::SetCurrentFrameNum(int frameNum)
{
	return m_lpPlay->SetCurrentFrameNum(&m_playParam, frameNum);
}

BOOL CPlayer::SetPlayedTiemEx(int time)
{
	return m_lpPlay->SetPlayedTimeEx(&m_playParam, time);
}

int CPlayer::SetDisplayRegion(DWORD nRegionNum, DISPLAYRECT *pSrcRect, HWND hDestWnd, BOOL bEnable)
{
	if(!m_lpPlay)
		return -1;

	return m_lpPlay->SetDisplayRegion(&m_playParam, nRegionNum, pSrcRect, hDestWnd, bEnable);
}

BOOL CPlayer::GetNextKeyFramePos(DWORD nValue, int nType, PFRAME_POS pFramePos) 
{
	return m_lpPlay->GetNextKeyFramePos(&m_playParam, nValue, nType, pFramePos);
}

BOOL CPlayer::GetKeyFramePos(DWORD nValue, int nType, PFRAME_POS pFramePos) 
{
	return m_lpPlay->GetKeyFramePos(&m_playParam, nValue, nType, pFramePos);
}

BOOL CPlayer::SetVerticalSync(bool bVerticalSync)
{
	return m_lpPlay->SetVerticalSync(&m_playParam, bVerticalSync);
}

BOOL CPlayer::GetQueryInfo(int cmdType, char* buf, int buflen, int* returnlen)
{
	return m_lpPlay->GetQueryInfo(&m_playParam, cmdType, buf, buflen, returnlen);
}

BOOL CPlayer::IsIndexCreated()
{
	return m_playParam.bIndexCreated;
}

int CPlayer::CreateFile()
{
	m_lpState[Play] = new FileState::CPlay;
	m_lpState[Pause] = new FileState::CPause;
	m_lpState[Stop] = new FileState::CStop;
	m_lpState[ToBegin] = new FileState::CToBegin;
	m_lpState[ToEnd] = new FileState::CToEnd;
	m_lpState[BackOne] = new FileState::CBackOne;
	m_lpState[OneByOne] = new FileState::COneByeOne;
	m_lpState[Slow] = new FileState::CSlow;
	m_lpState[Fast] = new FileState::CFast;

	memcpy(stateTable, FileState::stateTable, sizeof(stateTable));
	memcpy(openTable, FileState::openTable, sizeof(openTable));
	memcpy(closeTable, FileState::closeTable, sizeof(closeTable));

	m_lpPlay = new CFilePlayer;

	return 1;
}

int CPlayer::CreateFileStream()
{
	m_lpState[Play] = new FileStreamState::CPlay;
	m_lpState[Pause] = new FileStreamState::CPause;
	m_lpState[Stop] = new FileStreamState::CStop;
	m_lpState[ToBegin] = new FileStreamState::CToBegin;
	m_lpState[ToEnd] = new FileStreamState::CToEnd;
	m_lpState[BackOne] = new FileStreamState::CBackOne;
	m_lpState[OneByOne] = new FileStreamState::COneByeOne;
	m_lpState[Slow] = new FileStreamState::CSlow;
	m_lpState[Fast] = new FileStreamState::CFast;

	memcpy(stateTable, FileStreamState::stateTable, sizeof(stateTable));
	memcpy(openTable, FileStreamState::openTable, sizeof(openTable));
	memcpy(closeTable, FileStreamState::closeTable, sizeof(closeTable));

	m_lpPlay = new CFileStreamPlayer;
	
	return 1;
}

int CPlayer::Destroy()
{
	for(int i = 0 ; i < STATE_SIZE; i++)
	{
		if(m_lpState[i]) 
			delete m_lpState[i];
	}

	if(m_lpPlay)
		delete m_lpPlay;

	memset(m_lpState, 0, sizeof(m_lpState));
	m_lpPlay = NULL;

	return 1;
}

int CPlayer::ChangeState(PLAY_STATE nState)
{
	if(!m_lpPlay)
		return -1;

	return m_lpPlay->ChangeState(m_lpState[nState]);
}

int CPlayer::Do()
{
	if(!m_lpPlay)
		return -1;

	return m_lpPlay->Do(&m_playParam);
}

char* CPlayer::Description()
{
	if(!m_lpPlay)
		return NULL;

	return m_lpPlay->Description(&m_playParam);
}

int CPlayer::OpenSound(BOOL bOpen)
{
	if(!m_lpPlay)
		return -1;

	return m_lpPlay->OpenSound(&m_playParam, bOpen);
}

int CPlayer::SetAudioVolume(int nVolume)
{
	if(!m_lpPlay)
		return -1;

	return m_lpPlay->SetAudioVolume(&m_playParam, nVolume);
}

int CPlayer::GetAudioVolume()
{
	if(!m_lpPlay)
		return -1;

	return m_lpPlay->GetAudioVolume(&m_playParam);
}

int CPlayer::SetAudioWave(int nWave)
{
	if(!m_lpPlay)
		return -1;

	return m_lpPlay->SetAudioWave(&m_playParam, nWave);
}

BOOL CPlayer::RegistDrawCallback(fDrawCBFun cbDrawCBFun,void* nUser)
{
	if (!m_lpPlay)
		return -1;

	return m_lpPlay->RegistDrawCallback(&m_playParam, cbDrawCBFun, nUser);
}

BOOL CPlayer::SetPlayDirection(DWORD emDirection)
{
	if (!m_lpPlay)
		return -1;

	return m_lpPlay->SetPlayDirection(&m_playParam, emDirection);
}

BOOL CPlayer::RenderPrivateData(BOOL bTrue)
{
    if (!m_lpPlay)
        return -1;

    return m_lpPlay->RenderPrivateData(&m_playParam, bTrue);
}

BOOL CPlayer::SetEngine(int decodeType, int renderType)
{
    if (!m_lpPlay)
        return -1;

    return m_lpPlay->SetEngine(&m_playParam, decodeType, renderType);
}

