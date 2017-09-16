// Ptz.cpp: implementation of the CPtz class.
//
//////////////////////////////////////////////////////////////////////

#include "Ptz.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPtz::CPtz()
{

}

CPtz::~CPtz()
{

}

bool CPtz::SetPtzParam(LLONG lLoginID, int nChannel)
{
    if(lLoginID <=0 || nChannel < 0 )
	{
		return false;
	}

	m_lLoginID = lLoginID;
	m_nChannel = nChannel;
	
	return true;
}

bool CPtz::SetLoginID(LLONG lLoginID)
{
	if(lLoginID <= 0)
	{
		return false;
	}
	m_lLoginID = lLoginID;
	return true;
}

bool CPtz::SetChannel(int nChannel)
{
    if( nChannel < 0)  
	{
		return false;
	}
	m_nChannel = nChannel;
	return true;
}

/*************************************************************************************************/

#include<iostream>
using namespace std;
bool CPtz::PtzControl(int nType, int nParam1, int nParam2, int nParam3, bool bStop /* = false */)
{
	//cout<<nType<<"'"<<m_lLoginID<<","<<m_nChannel<<","<<nParam1<<","<<nParam2<<","<<nParam3<<","<<bStop<<endl;
    if(m_lLoginID <=0 || m_nChannel < 0 )
	{
		return false;
	}
	
	return CLIENT_DHPTZControlEx(m_lLoginID, m_nChannel, nType, nParam1, nParam2, nParam3, bStop);
}

bool CPtz::PtzMenuControl(int nType)
{
	switch(nType) 
	{
	case DH_EXTPTZ_MENUUP://上
	case DH_EXTPTZ_MENUDOWN://下
	case DH_EXTPTZ_MENULEFT://左
	case DH_EXTPTZ_MENURIGHT://右
	case DH_EXTPTZ_OPENMENU://打开球机菜单
	case DH_EXTPTZ_CLOSEMENU://关闭菜单
	case DH_EXTPTZ_MENUOK://菜单确定
	case DH_EXTPTZ_MENUCANCEL://菜单取消
		{
			return PtzControl(nType, 0, 0, 0);
		}	
		break;
	default:
		return false;
	}

}

bool CPtz::PtzAuxi(int nType, int nAuxi)
{
	switch(nType) 
	{
	case DH_EXTPTZ_AUXIOPEN://开
	case DH_EXTPTZ_AUXICLOSE://关
		{
			return PtzControl(nType, nAuxi, 0, 0);
		}
		break;
	default:
		return false;
	}

}

bool CPtz::PtzBasicControl(int nType, int nStep, bool bStop /* = false */)
{
	switch(nType) 
	{
	case DH_PTZ_UP_CONTROL:	//上
	case DH_PTZ_DOWN_CONTROL://下
	case DH_PTZ_LEFT_CONTROL://左
	case DH_PTZ_RIGHT_CONTROL://右
	case DH_PTZ_ZOOM_DEC_CONTROL://镜头缩
	case DH_PTZ_ZOOM_ADD_CONTROL://镜头伸
	case DH_PTZ_FOCUS_DEC_CONTROL://焦距近
	case DH_PTZ_FOCUS_ADD_CONTROL://焦距远
	case DH_PTZ_APERTURE_DEC_CONTROL://光圈小
	case DH_PTZ_APERTURE_ADD_CONTROL://光圈大
		{
			return PtzControl(nType, 0, nStep, 0, bStop);
		}	
		break;
	case DH_EXTPTZ_LEFTTOP:	//左上
	case DH_EXTPTZ_LEFTDOWN://左下
	case DH_EXTPTZ_RIGHTTOP: //右上
	case DH_EXTPTZ_RIGHTDOWN://右下
		{
			return PtzControl(nType, nStep, nStep, 0, bStop);
		}
		break;
	default:
		return false;
	}
}

bool CPtz::PtzFastGo(int nX, int nY, int nZoom)
{
	return PtzControl(DH_EXTPTZ_FASTGOTO, nX, nY, nZoom, false);
}

bool CPtz::PtzLineScan(int nType)
{
	switch(nType)
	{
	case DH_EXTPTZ_SETLEFTBORDER:		//设置左边界			
	case DH_EXTPTZ_SETRIGHTBORDER:		//设置右边界			
	case DH_EXTPTZ_STARTLINESCAN:		//开始线扫			
    case DH_EXTPTZ_CLOSELINESCAN:		//停止线扫			
		{
			return PtzControl(nType, 0, 0, 0);
		}
		break;
	default:
		return false;
	}
}

bool CPtz::PtzLoop(int nType, int nGroup, int nPresetData, bool bBeginLoop /* = false */)
{
	switch(nType)
	{
		case DH_PTZ_POINT_LOOP_CONTROL://开始巡航,停止巡航
			{
				if (bBeginLoop) 
				{
					return PtzControl(nType, nGroup, 0, 76);//开始
				}
				else
				{
					return PtzControl(nType, nGroup, 0, 96);//停止
				}
			}
			break;
		case DH_EXTPTZ_ADDTOLOOP://增加巡航点
		case DH_EXTPTZ_DELFROMLOOP://删除巡航点
			{
				return PtzControl(nType, nGroup, nPresetData, 0);
			}
			break;
		case DH_EXTPTZ_CLOSELOOP://删除巡航组
			{
				return PtzControl(nType, nGroup, 0, 0);
			}
			break;
		default:
			return false;
	}
}

bool CPtz::PtzPreset(int nType, int nPresetData)
{
	switch(nType)
	{
	case DH_PTZ_POINT_MOVE_CONTROL://转至预置点
	case DH_PTZ_POINT_SET_CONTROL://设置
	case DH_PTZ_POINT_DEL_CONTROL://删除
		{
			return PtzControl(nType, 0, nPresetData, 0);
		}
		break;
	default:
		return false;
	}
}

bool CPtz::PtzRotate(int nType)
{
	switch(nType)
	{
	case DH_EXTPTZ_STARTPANCRUISE:		//开始水平旋转			
	case DH_EXTPTZ_STOPPANCRUISE:		//停止水平旋转
		{
			return PtzControl(nType, 0, 0, 0);
		}
	default:
		return false;
	}
}

bool CPtz::PtzMode(int nType, int nGroup)
{
	switch(nType)
	{
	case DH_EXTPTZ_SETMODESTART://开始记录
	case DH_EXTPTZ_SETMODESTOP:	//停止记录
	case DH_EXTPTZ_RUNMODE:	//开始巡迹
	case DH_EXTPTZ_STOPMODE://停止巡迹
	case DH_EXTPTZ_DELETEMODE://删除巡迹
		{
			return PtzControl(nType, nGroup, 0, 0);
		}
		break;
	default:
		return false;
	}
}
	
