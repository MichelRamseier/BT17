
#ifndef USERDEFINE_H
#define USERDEFINE_H
#include <list>
using namespace std;
#include "dhnetsdk.h"

//	channel information
typedef struct 
{
        LLONG			lRealPlayHandle;
	unsigned long		dwStatistic;
} DH_Channel_Info;


//	device information
typedef struct 
{
        LLONG			lLoginHandle;
	int			nChannelCount;
	int			bOnline;
	char			szDevIp[32];
	int				nPort;
	char			szUserName[32];
	char			szPassWord[32];
	DH_Channel_Info		channel[16];
	int				nBelongThread;
	unsigned int	nIndex;	
	unsigned long			nTimeCount;//计时器
} DH_Device_Info;


typedef std::list<DH_Device_Info*> DEVICE_LIST;


#endif // USERDEFINE_H
