// Ptz.h: interface for the CPtz class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PTZ_H__3CBE7307_BC91_490C_91E9_B08535C6C7F4__INCLUDED_)
#define AFX_PTZ_H__3CBE7307_BC91_490C_91E9_B08535C6C7F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "dhnetsdk.h"

class CPtz  
{
public:
	CPtz();
	virtual ~CPtz();

public://interface
	
        bool SetPtzParam(LLONG lLoginID, int nChannel);//设置云台操作的登陆句柄和通道号。
        bool SetLoginID(LLONG lLoginID);
	bool SetChannel(int nChannel);

	bool PtzBasicControl(int nType, int nStep, bool bStop = false);//云台方向,镜头，光圈，调焦的控制
	bool PtzMenuControl(int nType);//云台菜单控制
	bool PtzFastGo(int nX, int nY, int nZoom);//三维定位控制
	bool PtzRotate(int nType);//水平旋转
	bool PtzAuxi(int nType, int nAuxi);//辅助功能
	bool PtzLineScan(int nType);//线性扫描
	bool PtzLoop(int nType, int nGroup, int nPresetData, bool bBeginLoop = false);//巡航
	bool PtzPreset(int nType, int nPresetData);//预制点
	bool PtzMode(int nType, int nGroup);//云台巡迹
	
protected://data member
        LLONG	                        m_lLoginID;//设备登陆句柄
	int				m_nChannel;//控制通道

protected://method member
	bool PtzControl(int nType, int nParam1, int nParam2, int nParam3, bool bStop = false);
};

#endif // !defined(AFX_PTZ_H__3CBE7307_BC91_490C_91E9_B08535C6C7F4__INCLUDED_)
