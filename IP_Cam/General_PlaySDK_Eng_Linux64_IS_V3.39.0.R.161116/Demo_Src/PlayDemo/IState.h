// IState.h: interface for the IState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISTATE_H__E213B858_4FDB_4C00_AE3A_DE11C4E3D8D8__INCLUDED_)
#define AFX_ISTATE_H__E213B858_4FDB_4C00_AE3A_DE11C4E3D8D8__INCLUDED_

#include <stdio.h>
#include "dhplay.h"
#include "IWindowEvent.h"

enum PLAY_STATE{ NONE=-3, Open, Close,
Play = 0, Pause, Stop, ToBegin, ToEnd, BackOne, OneByOne, Slow, Fast, 
STATE_SIZE };
enum SPEED{SLOW4, SLOW3, SLOW2, SLOW1, NORMAL, FAST1, FAST2, FAST3, FAST4};

struct PlayParam
{
	/*解码端口*/
	int nPort;
	/*显示窗口句柄*/
	HWND hWnd;
	/*播放速度*/
	float fSpeedCoff;//需要判断当前是否为正常速度播放
	/*是否打开音频*/
	BOOL bOpenAudio;
    IWindowEvent* pMainWnd;
	BOOL bIndexCreated;

	/*文件流方式用*/
	FILE* lpfDav;
    long long nDavSize;
};

/*
* 抽象播放状态，统一处理播放流程，以避免复杂的状态逻辑处理过程。
* 状态的逻辑处理按照状态迁移表进行。
*/
class IPlayState
{
public:
    virtual ~IPlayState(){};
	/*更种状态下的逻辑处理工作*/
	virtual BOOL Do(PlayParam* lpPlayParam) = 0;
	/*获得各个状态下的描述，返回NULL表示描述不需变化*/
	virtual char* Description(PlayParam* lpPlayParam) = 0;
};


#endif // !defined(AFX_ISTATE_H__E213B858_4FDB_4C00_AE3A_DE11C4E3D8D8__INCLUDED_)
