/********************************************************************
 * File: dhplayEx.h
 * Copyright:
 * Author:Zhou Guofeng/Wang Weifen 
 * Created: 2006.12
 * purpose:Function interface definition and explanatino for user 2nd development.
*********************************************************************/
#ifndef _DHPLAY_EX_H
#define _DHPLAY_EX_H

#include "dhplay.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define PIC_BMP_32                      0       //BMP32
#define PIC_BMP_24                      1       //BMP24

/*兼容旧版本鱼眼接口*/
typedef enum
{
	FISHSHOWMODE_WALL_PANORAMA = 0,       //壁装全景模式
	FISHSHOWMODE_CEIL_PANORAMA,           //顶装360度全景
	FISHSHOWMODE_CEIL_PANORAMA_TWO,       //顶装180度全景
	FISHSHOWMODE_FLOOR_PANORAMA,          //地板安装360度全景
	FISHSHOWMODE_FLOOR_PANORAMA_TWO,      //地板安装180度全景 
	FISHSHOWMODE_ONE_O_THREE,             //1+3模式
	FISHSHOWMODE_CEIL_ONE_REGION = 10,    //顶装单窗口eptz
	FISHSHOWMODE_CEIL_FOUR_REGION,        //顶装4窗口eptz
	FISHSHOWMODE_ORIGINAL,                //原始模式，不做处理直接输出原始数据
	FISHSHOWMODE_WALL_ONE_REGION,         //壁装单窗口eptz
	FISHSHOWMODE_WALL_FOUR_REGION,        //壁装4窗口eptz
	FISHSHOWMODE_FLOOR_ONE_REGION,        //地板安装单窗口eptz
	FISHSHOWMODE_FLOOR_FOUR_REGION,       //地板安装4窗口eptz数据原始数据
	FISHSHOWMODE_WALL_ONE_O_THREE,	      //地板1+3模式
	FISHSHOWMODE_CEIL_ONE_O_THREE,	      //顶装1+3模式
	FISHSHOWMODE_FLOOR_ONE_O_THREE,	      //壁装1+3模式

}FISHSHOWMODES;

typedef enum
{
	FISHEPTZOPT_UPDATE_FOCUS,                   //更新焦点
	FISHEPTZOPT_ZOOM_IN,                        //放大
	FISHEPTZOPT_ZOOM_OUT,                       //缩小
	FISHEPTZOPT_MOVE_UP,                        //向上移动
	FISHEPTZOPT_MOVE_DOWN,                      //向下移动
	FISHEPTZOPT_MOVE_LEFT,                      //向左移动
	FISHEPTZOPT_MOVE_RIGHT,                     //向右移动
	FISHEPTZOPT_AUTO_ROTATE_CLOCKWISE,          //自动顺时针旋转
	FISHEPTZOPT_AUTO_ROTATE_COUNTERCLOCKWISE,   //自动逆时针旋转
	FISHEPTZOPT_STOP_AUTO_ROTATE,				//停止自动旋转
	FISHEPTZOPT_GET_POSITION,					//获取当前云台窗口所在位置
	FISHEPTZOPT_SELECT_REGION_ZOOMIN_ON,        //框选放大
	FISHEPTZOPT_SELECT_REGION_ZOOMIN_OFF,		//退出框选放大
	FISHEPTZOPT_RESTORE_DEFAULT_LOCATION,		//云台恢复默认位置

}FISHEPTZOPTS;
/***************/

//@begin鱼球联动
typedef struct
{
	int   himg_width;                       //从相机图像宽
	int   himg_height;                      //从相机图像高
	int   *zoom_list;						/*球机倍数表*/
	int    zoom_list_size;					/*球机倍数表档位个数*/
}MHFPTZ_INITPARAM;
//@end鱼球联动

typedef struct 
{
	int radius;      //目标鱼眼圆半径——输入为8192坐标系
	int originX;     //目标鱼眼圆圆心——输入为8192坐标
	int originY;
	FISHEYE_SIZE srcSize; //输入鱼眼圆的宽高
	FISHEYE_SIZE dstSize; //输出矫正图的宽高
	int winId;			//目标窗口的id
	FISHEYE_MOUNTMODE mountMode;     //鱼眼安装模式
	FISHEYE_CALIBRATMODE calibMode; //矫正模式
	FISHEYE_REGIONPARAM regionParam;  //通过Fisheye_EptzUpdate ，FISHEYE_EPTZ_CMD_GET_CUR_REGION 获得

}FISHRECTIFY_INFO;

// 日期信息
typedef struct __DATETIME_INFO
{
	unsigned int			nYear;			// 年
	unsigned int			nMonth;			// 月
	unsigned int			nDay;			// 日
	unsigned int			nHour;			// 时
	unsigned int			nMinute;		// 分
	unsigned int			nSecond;		// 秒
	unsigned int			nMilliSecond;	// 毫秒
}DATETIME_INFO;

typedef struct 
{
	char*	pHead;				//帧数据(带大华头)
	int		nLen;				//帧数据长度
	char*	pBody;				//裸数据(不带大华头)
	int		nBodyLen;			//裸数据长度
	
	int		nRet;				//0:继续解码  1://不解码  默认为0
	char	reserved[128];
}DemuInfoEx;

typedef struct
{
	int type;			// 1:VIDEO, 2:AUDIO, 3:DATA
	int subtype;		// I Frame, BP Frame, PCM8, MS-ADPCM etc.
	int encode;			// MPEG4, H264, STDH264
	int sequence;		// I帧间隔里面的序号
	
	// 图像大小信息
	int width;
	int height;
	
	// 帧率信息
	int rate;
	
	// 时间信息
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int secode;
	LONG timestamp;
	
	int channels;
	int bitspersample;
	int samplespersecond;
}DEMUX_INFO;

// 文件信息帧
typedef struct __FILE_INFO_FRAME
{
	unsigned int		nFrameSubType;	  // 帧子类型，动检数据帧、事件帧等
	DATETIME_INFO*		pstDateTimeStart; // 开始时间
	DATETIME_INFO*		pstDateTimeEnd;   // 结束时间
	unsigned char*		pFrameData;		  // 帧数据
	unsigned int		nFrameDataLen;	  // 帧数据长度
} FILE_INFO_FRAME;

typedef struct __FILE_INFO_FRAME_SEARCH
{
	unsigned int		nFileFrameType;		//搜索类型，可以组合，如 PLAYER_INFO_TYPE_MOTIONDECT | PLAYER_INFO_TYPE_EVENT
	DATETIME_INFO		stStartDataTime;    //开始时间
	DATETIME_INFO		stEndDataTime;      //结束时间
	DISPLAYRECT			rtDetectedRegion;   //总区域中的动检检测范围，动检帧时有效，区域矩形为0时，表示全区域搜索
	DISPLAYRECT			rtTotal;			//总区域, 动检帧时有效
} FILE_INFO_FRAME_SEARCH;

typedef struct __FILE_INFO_IMAGE
{
	tPicFormats	   imageType;				// 图片的类型
	unsigned char* pPicBuf;					// 图片的缓冲指针
	unsigned int   nPicBufLen;				// 图片的长度

} FILE_INFO_IMAGE;

typedef struct NativeHandle
{
	void* display;
	void* context;
	void* surface;

}Android_NativeHandle;

// 文件信息帧的搜索类型，对应FILE_INFO_FRAME_SEARCH结构体中的nFileFrameType
#define PLAY_INFO_TYPE_MOTIONDECT     1         // 动检
#define PLAY_INFO_TYPE_EVENT		  2         // 事件

//鱼眼新增模式功能开关
#define NEWFUNC_FTRACK_MODE_RT 0x01

/************************************************************************/
/* 增强支持的功能                                                         */
/************************************************************************/
typedef enum 
{
	IVSEFUNCTYPE_DEHAZE,	    // 去雾
	IVSEFUNCTYPE_DENOISE,		// 去噪
	IVSEFUNCTYPE_WB,			// 偏色校正
	IVSEFUNCTYPE_LOWLIGHT,		// 低照度增强
	IVSEFUNCTYPE_HDR,			// 宽动态
	IVSEFUNCTYPE_NUM			// 支持增强的功能个数
}IVSEFUNCTYPE;

/************************************************************************/
/* ROI数据类型定义                                                        */
/************************************************************************/
typedef struct
{
    int x;          // 左上角x坐标
    int y;          // 左上角y坐标
    int width;      // 区域宽度
    int height;     // 区域高度
}IVSEROI;

/************************************************************************/
/* 视频增强算法输入参数                                                           */
/************************************************************************/
typedef struct
{
    IVSEFUNCTYPE eFuncType;   // 功能选项
    IVSEROI		 cRoi;        // ROI 配置
	int			 nMode;       // 0表示图片模式， 1表示视频模式
    int			 nProcess_param[2];     // 处理参数，范围[1,5]
	/*
    功能函数	                process_param[0]	    process_param[1]
    IVSEFUNCTYPE_DEHAZE	        灵敏度	                饱和度
    IVSEFUNCTYPE_DENOISE	    灵敏度	                - （视频模式有效）
    IVSEFUNCTYPE_WB	        -	                    -
    IVSEFUNCTYPE_LOWLIGHT	-   灵敏度	                饱和度
    IVSEFUNCTYPE_HDR	        0:白天 1:黑夜 2:自动  	灵敏度
    */

}IVSEPARAMS;

/********************************************************************
*	函数名: 	    	PLAY_SetupPrepareTime
*	目的:				设置预录的环境
*   输入参数:           nPort:		解码通道。
						nTime:		预录多少秒
						tmpDir:		临时的预录目录
*   输出参数:        
*   返回值:             TRUE:	成功.
						FALSE:	失败
*   创建时间:	        2012:12:21  
*   版本信息记录:	    2012/12/21:YeYamin:modify......
*********************************************************************/

PLAYSDK_API BOOL	CALLMETHOD PLAY_SetupPrepareTime(LONG nPort,int nTime,const char* tmpDirectory);

/********************************************************************
*	函数名: 	    	PLAY_StartPrepareRecord
*	目的:				开始预录
*   输入参数:		     nPort:		解码通道。
						 pFileName:	录像位置
*   输出参数:        
*   返回值:             TRUE:	成功.
						FALSE:	失败
*   创建时间:	        2012:12:21  
*   版本信息:			2012/12/21:YeYamin:modify......
*********************************************************************/

PLAYSDK_API BOOL	CALLMETHOD PLAY_StartPrepareRecord(LONG nPort,const char* pFileName);

/********************************************************************
*	函数名: 	    	PLAY_StopPrepareRecord
*	目的:	
*   输入参数:			port:		解码通道。
*   输出参数:        
*   返回值:             TRUE:	成功.
						FALSE:	失败
*   创建时间:	        2012:12:21  
*   版本信息记录:		2012/12/21:YeYamin:modify......
*********************************************************************/

PLAYSDK_API BOOL	CALLMETHOD PLAY_StopPrepareRecord(LONG nPort);

//
// 
#define IVSINFOTYPE_PRESETPOS		1
#define IVSINFOTYPE_MOTINTRKS		2
#define IVSINFOTYPE_MOTINTRKS_EX	3
#define IVSINFOTYPE_LIGHT			4
#define IVSINFOTYPE_RAWDATA			5
#define IVSINFOTYPE_TRACK			6
#define IVSINFOTYPE_TRACK_EX_B0		7
#define IVSINFOTYPE_MOTIONFRAME		9 /*动态监测数据帧*/
#define IVSINFOTYPE_VIDEO_CONCENTRATION    10 
#define PSIVS						240
/********************************************************************
*	函数名: 	    	PLAY_SetIVSCallBack
*	目的:	
*   输入参数:	        nPort:		解码通道
						pFunc:		设置解码回调
						nUser:		上下文，用于回调回来的参数
*   输出参数:        
*   返回值:             TRUE:	成功 
						FALSE:	失败
*   创建时间:	        2012:12:21  
*	版本信息记录:	    2012/12/21:YeYamin:modify......
*********************************************************************/

typedef void (CALLMETHOD *GetIVSInfoCallbackFunc)(char* buf, LONG type, LONG len, LONG reallen, void* pReserved, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetIVSCallBack(LONG nPort, GetIVSInfoCallbackFunc pFunc, void* pUserData);

/********************************************************************
*	函数名: 	    	PLAY_StartAVIResizeConvert
*	目的:				改变分辨率的AVI转换
*   输入参数:           nPort:		解码通道。
						sFileName:	AVI的录像存放地址
						lWidth & lHeight:AVI的录像的宽跟高
*   输出参数:	        
*   返回值:             TRUE:	成功 
						FALSE:	失败
*   创建时间:	        2012:12:21  
*   版本信息记录:	    2012/12/21:YeYamin:modify......
*********************************************************************/

PLAYSDK_API BOOL CALLMETHOD PLAY_StartAVIResizeConvert(LONG nPort, char *sFileName, LONG lWidth, LONG lHeight);

/********************************************************************
*	函数名: 	    	PLAY_StopAVIResizeConvert
*	目的:				结束AVI转换
*   输入参数:           nPort:		解码通道。
*   输出参数:	        
*   返回值:             TRUE:	成功 
						FALSE:	失败
*   创建时间:	        2012:12:21  
*   版本信息记录:	    2012/12/21:YeYamin:modify......
*********************************************************************/

PLAYSDK_API BOOL CALLMETHOD PLAY_StopAVIResizeConvert(LONG nPort);

/********************************************************************
*	函数名: 	    	PLAY_SetPandoraWaterMarkCallBack
*	目的:				无效
*   输入参数:         
*   输出参数:	        
*   返回值:             TRUE:	成功 
						FALSE:	失败
*   创建时间:	        2012:12:21  
*   版本信息记录:	    2012/12/21:YeYamin:modify......
*********************************************************************/

PLAYSDK_API BOOL CALLMETHOD PLAY_SetPandoraWaterMarkCallBack(LONG nPort, GetWaterMarkInfoCallbackFunc pFunc, void* pUserData);


/********************************************************************
*	函数名: 	    	PLAY_SetDigitalSignCallBack
*	目的:				设置数字签名回调.
*   输入参数:           nPort:		解码通道。
						nFrameID:	帧序号
						bSuccess:	校验是否通过
						pUserData   用户数据
*   输出参数:	        
*   返回值:             TRUE:	成功 
						FALSE:	失败
*********************************************************************/
typedef void (CALLBACK* fCheckDigitalSignCB)(LONG nPort, int nFrameID, BOOL bSuccess, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDigitalSignCallBack(LONG nPort, fCheckDigitalSignCB pDigitalSignCB, void* pUserData);

/********************************************************************
*	函数名: 	    	PLAY_GetTimePicture
*	目的:				获得绝对时间点上面的图片
*   输入参数:           filepath:	保存的文件路径
						time:		绝对时间
						DecCBFun:	设置进去的解码回调
						user:		用户上下文
*   输出参数:	        
*   返回值:             TRUE:	成功 
						FALSE:	失败
*   创建时间:	        2012:12:21  
*   版本信息记录:	    2012/12/21:YeYamin:modify......
*********************************************************************/
PLAYSDK_API BOOL CALLMETHOD PLAY_GetTimePicture(const char* filepath, struct tm* time, fDecCBFun fcbDec, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_StartFisheyeEx
// 描述: 鱼球联动功能扩展接口，需要包含fisheye.dll MCL_FPTZ.dll库
// 参数: [in] nPort : 通道号
//		 [in] startType:  开启类型， 0只开启鱼眼校正, 1同时开启联动和校正, 2只开启鱼球联动算法, 3表示180度鱼眼矫正
//		 [in] funcType:   开启哪些功能，0表示都不开启，1表示只开启智能帧功能，2表示只开启抓图，
//						  3表示智能帧和抓图都开启，开启的功能越多，消耗的内存越大
//       [in] ptzChannelParam: 鱼球联动初始化通道参数，startType为0时，ptzChannelParam填NULL
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartFisheyeEx(LONG nPort, int startType, int funcType, MHFPTZ_INITPARAM* ptzChannelParam);

//------------------------------------------------------------------------
// 函数: PLAY_StartFisheyeMPTZ
// 描述: 鱼球联动功能扩展接口，支持一鱼多球
// 参数: [in] nPort : 通道号
//		 [in] startType:  开启类型， 0只开启鱼眼校正, 1同时开启联动和校正, 2只开启鱼球联动算法, 3表示180度鱼眼矫正
//		 [in] funcType:   开启哪些功能，0表示都不开启，1表示只开启智能帧功能，2表示只开启抓图，
//						  3表示智能帧和抓图都开启，开启的功能越多，消耗的内存越大
//       [in] ptzChannelParam: 鱼球联动初始化通道参数，startType为0时，ptzChannelParam填NULL
//		 [in] ptzChannelNum: 鱼球联动初始化通道数  
//		 [in] imgMaxOutput:  输出图像最大的分辨率
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartFisheyeMPTZ(LONG nPort, int startType, int funcType, MHFPTZ_INITPARAM* ptzChannelParam, int ptzChannelNum, FISHEYE_SIZE* pImgMaxOutput);


//------------------------------------------------------------------------
// 函数: PLAY_SetFisheyeParams, 兼容旧版本鱼眼接口
// 描述: 设置鱼眼参数
// 参数: [in]nPort           :  通道号
//		 [in]nX				 :  鱼眼圆心横坐标
//       [in]nY				 :  鱼眼圆心纵坐标
//       [in]nRadius         :  鱼眼半径
//       [in]nLensDirection  :  镜头方向 
//       [in]mode            :  图像显示模式
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFisheyeParams(LONG nPort, int nX, int nY, int nRadius, int nLensDirection, FISHSHOWMODES mode);

//------------------------------------------------------------------------
// 函数: PLAY_FisheyeGetPosition, 兼容旧版本鱼眼接口
// 描述: 获得目标中心对应电子云台的焦点位置
// 参数: [in]nPort           :  通道号
//		 [in]row			 :  目标中心所在行
//       [in]column			 :  目标中心所在列
//		 [out]pX     		 :  目标中心所对应电子云台的焦点横坐标
//       [out]pY		     :  目标中心所对应电子云台的焦点纵坐标
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_FisheyeGetPosition(LONG nPort, int row, int column, int *pX, int *pY);

//------------------------------------------------------------------------
// 函数: PLAY_FisheyeEptzUpdate, 兼容旧版本鱼眼接口
// 描述: 开启eptz(电子云台），进行缩放移动
// 参数: [in]nPort           :  通道号
//		 [in/out]pX			 :  eptz（电子云台）的焦点横坐标
//       [in/out]pY			 :  eptz的焦点纵坐标
//		 [in/out]pHangle		 :  eptz的水平角度范围(0-3600)
//       [in/out]pVangle		 :  eptz的垂直角度范围(0-900)
//       [in]ops             :  FISHEPTZOPTS结构体,为0时对指定窗口设置焦点，为1表示放大，2表示缩小，3表示向上移动，
//                              4表示向下移动，5表示向左移动，6表示向右移动，7表示自动顺时针旋转，8表示自动逆时针旋转
//								9表示停止云台操作，10表示获取当前云台窗口所在位置
//       [in]nWinNum         :  要进行eptz的窗口编号，左上角win_num为1，从左到右递增
//       [in]nZoomStep       :  放大缩小的步长, 范围1-8
//       [in]nPtStep		 :  上下左右移动的步长, 范围1-8
//		 [in]nRotateStep	 :  旋转的步长, 范围1-8
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_OldFisheyeEptzUpdate(LONG nPort, int *pX, int *pY, int *pHAngle, int *pVAngle, FISHEPTZOPTS ops, int nWinNum,
												   int nZoomStep, int nPtStep, int nRotateStep);

/******************************************************************************
*
* 函数名  : Fisheye_TrancForm_TrackFrame
* 描  述  : 1模式下，将ivs跟踪帧中的当前帧的目标轨迹坐标转换到原始圆上坐标
* 输  入  : - handle: 鱼眼算法实例句柄
			- ptrackframe: 跟踪帧
			- track_frame_size：跟踪帧大小
* 输  出  : - ptrackframe，将原始鱼眼圆坐标封装到原智能帧中
* 返回值  : DH_FISHEYE_ERROR_NONE: 成功。
*           other: 失败。
*******************************************************************************/ 	
PLAYSDK_API BOOL CALLMETHOD PLAY_FisheyeTrancFormTrackFrame(LONG nPort, void *ptrackframe,int track_frame_size);

/******************************************************************************
*
* 函数名  : Fisheye_TrancForm_coordinate
* 描  述  : 给定矫正图上坐标，计算出原始鱼眼圆圆上坐标
* 输  入  : - param：矫正参数，详见 FishRectify_Info
			- inrpt：输入点，8192坐标系
			  
* 输  出  : - orpt：输出点，8192坐标系
			v:转换后的坐标
* 返回值  : DH_FISHEYE_ERROR_NONE: 成功。
*           other: 失败。
*******************************************************************************/ 	
PLAYSDK_API BOOL CALLMETHOD PLAY_FisheyeTrancFormCoordinate(FISHRECTIFY_INFO *param, FISHEYE_POINT2D* inrpt,
	FISHEYE_POINT2D *orpt);
		
/******************************************************************************
*
* 函数名  : Fisheye_TrancForm_Curve
* 描  述  : 给定矫正图上坐标，计算出原始鱼眼圆圆上坐标
* 输  入  : - param：矫正参数，详见 FishRectify_Info
            - rpt1:矫正图上的一个点，8192坐标系
			- rpt2：矫正图上的一个点，8192坐标系
			- in_num：两点间的点个数
* 输  出  : - in_num：插值后的点个数，包括两个端点
            - fpts：插值后得到的点序列，包括两个端点，8192坐标系
* 返回值  : DH_FISHEYE_ERROR_NONE: 成功。
*           other: 失败。
*******************************************************************************/ 	
PLAYSDK_API BOOL CALLMETHOD PLAY_FisheyeTrancFormCurve(FISHRECTIFY_INFO *param,
	FISHEYE_POINT2D* rpt1,FISHEYE_POINT2D* rpt2,int *in_num,
	FISHEYE_POINT2D *fpts);

//------------------------------------------------------------------------
// 函数: PLAY_StartDeNoise
// 描述: 开启视频去噪算法功能,需要包含3dnr.dll库
// 参数: [in]nPort : 通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartDeNoise(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetDeNoiseParams
// 描述: 设置视频去噪参数
// 参数: [in]nPort           :  通道号
//		 [in]nTemporal		 :  时域去噪强度 [0,32]
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDeNoiseParams(LONG nPort, int nTemporal);

//------------------------------------------------------------------------
// 函数: PLAY_StopDeNoise
// 描述: 停止视频去噪算法功能
// 参数: [in]nPort : 通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StopDeNoise(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_StartDeHaze
// 描述: 开启视频去雾算法功能，需要包含dehazing.dll库
// 参数: [in]nPort : 通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartDeHaze(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetDehazeParams
// 描述: 设置视频去雾参数
// 参数: [in]nPort           :  通道号
//		 [in]ALightValue	 :	设定的大气光强的值，范围0-255
//		 [in]AutoLightOn	 :  默认为1,代表开启自动寻找大气光强；0-关闭自动，开启手动
//       [in]AutoRun		 :	默认为1,代表一直开启去雾功能，0-自动判断是否雾天并去雾
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDehazeParams(LONG nPort, int ALightValue, int AutoLightOn, int AutoRun);

//------------------------------------------------------------------------
// 函数: PLAY_STOPDeHaze
// 描述: 停止视频去雾算法功能
// 参数: [in]nPort : 通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StopDeHaze(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_StartIVSE
// 描述: 开启视频增强算法功能，需要包含IvseDll.dll库
// 参数: [in]nPort : 通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//
// 注意：此算法处理时间较长，不建议处理高清视频
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartIVSE(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetIVSEParams
// 描述: 设置视频增强参数，可以多次调用来组合使用多种IVSE库的功能
// 参数: [in]nPort           :  通道号
//		 [in]pIVSEParams	 :	IVSEPARAMS结构体参数
//		 [in]bEnable		 :  对应于IVSEPARAMS中的IVSEFUNCTYPE功能选项，使能开关	
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetIVSEParams(LONG nPort, IVSEPARAMS* pIVSEParams, BOOL bEnable);

//------------------------------------------------------------------------
// 函数: PLAY_StopIVSE
// 描述: 停止视频增强算法功能
// 参数: [in]nPort : 通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StopIVSE(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_ConvertToBmpFile
// 描述: 图像格式转为BMP格式.
// 参数: pBuf,图像数据指针
//		 nSize,图像数据大小
//		 nWidth,图像宽度
//		 nHeight,图像高度
//		 nType,数据类型.T_RGB32,T_UYVY等.
//		 sFileName,要保存的文件名.最好以BMP作为文件扩展名.
//       nBmpType, BMP类型，PIC_BMP_32表示BMP32， PIC_BMP_24表示BMP24
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ConvertToBmpFileEx(char * pBuf,LONG nSize,LONG nWidth,LONG nHeight,LONG nType, char *sFileName,int nBmpType);

//------------------------------------------------------------------------
// 函数: PLAY_EnableLargePicAdjustment
// 描述: 是否启用高清图像内部调整策略。该策略启用时，在快放4倍速以上时，只播放I帧，不启用时，则每帧都播放
// 参数: [in]nPort           :  通道号
//		 [in]bEnable		 :  TRUE表示启用此功能，FALSE表示关闭此功能
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_EnableLargePicAdjustment(LONG nPort, BOOL bEnable);

//------------------------------------------------------------------------
// 同步播放接口
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// 函数: PLAY_OpenPlayGroup
// 描述: 打开同步播放
// 参数: 无
// 返回: 同步播放控制句柄，在调用同步播放控制接口时需要传入该句柄，返回NULL表示失败
//------------------------------------------------------------------------
PLAYSDK_API void* CALLMETHOD PLAY_OpenPlayGroup();

//------------------------------------------------------------------------
// 函数: PLAY_AddToPlayGroup
// 描述: 添加一路已经代开的视频至同步播放中
// 参数: hPlayGroup,同步播放句柄，由PLAY_OpenPlayGroup返回
//       nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_AddToPlayGroup(void* hPlayGroup, LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_DelFromPlayGroup
// 描述: 从同步播放队列中删除指定通道号
// 参数: hPlayGroup,同步播放句柄，由PLAY_OpenPlayGroup返回
//       nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_DelFromPlayGroup(void* hPlayGroup, LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetPlayGroupDirection
// 描述: 从当前时间点正放或倒放
// 参数: hPlayGroup,同步播放句柄，由PLAY_OpenPlayGroup返回
//		 nDirection,播放方向：0，向前，1，向后
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayGroupDirection(void* hPlayGroup, int nDirection);

//------------------------------------------------------------------------
// 函数: PLAY_SetPlayGroupSpeed
// 描述: 设置播放速度
// 参数: hPlayGroup,同步播放句柄，由PLAY_OpenPlayGroup返回
//		 fCoff,播放速度,范围[1/64~64.0],小于1表示慢放，大于1表示正放.
//			   当播放速度较快时可能会抽帧播放.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayGroupSpeed(void* hPlayGroup, float fSpeed);

//------------------------------------------------------------------------
// 函数: PLAY_PausePlayGroup
// 描述: 暂停或继续
// 参数: hPlayGroup,同步播放句柄，由PLAY_OpenPlayGroup返回
//		 bPause,TRUE暂停,FLASE恢复
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_PausePlayGroup(void* hPlayGroup, BOOL bPause);

//------------------------------------------------------------------------
// 函数: PLAY_StepPlayGroup
// 描述: 单帧播放
// 参数: hPlayGroup,同步播放句柄，由PLAY_OpenPlayGroup返回
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StepPlayGroup(void* hPlayGroup);

//------------------------------------------------------------------------
// 函数: PLAY_StepPlayGroup
// 描述: 采用绝对时间进行定位
// 参数: hPlayGroup,同步播放句柄，由PLAY_OpenPlayGroup返回
//	     pstDateTime,绝对时间
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SeekPlayGroup(void* hPlayGroup, DATETIME_INFO* pstDateTime);

//------------------------------------------------------------------------
// 函数: PLAY_ClosePlayGroup
// 描述: 关闭同步播放控制
// 参数: hPlayGroup,同步播放句柄，由PLAY_OpenPlayGroup返回
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ClosePlayGroup(void* hPlayGroup);

//------------------------------------------------------------------------
// 函数: PLAY_SetFileDoneTimeCallBack
// 描述: 文件开始、结束时间回调。分析出文件开始和结束时间后会调用该回调。
// 参数: nPort,通道号
//		 fFileTimeDoneCBFun,回调函数指针,不能为NULL,其参数含义如下:
//			nPort,通道号
//			nStartTime, 文件开始时间.自1970年1月1日0点0分0秒的秒数.
//			nEndTime, 文件结束时间.自1970年1月1日0点0分0秒的秒数.
//			pUserData, 用户自定义参数
//		 pUserData, 用户自定义参数.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef void (CALLBACK* fFileTimeDoneCBFun)(LONG nPort, DWORD nStarTime, DWORD nEndTime, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileTimeDoneCallBack(LONG nPort, fFileTimeDoneCBFun FileTimeCBFun, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_GetKeyFramePosByAbsoluteTime
// 描述: 按绝对时间查找指定位置之前的关键帧位置.
// 参数: nPort,通道号
//		 t,绝对时间,详见SYSTEMTIME.仅用到年月日时分秒.注：在执行成功后该值存储所返回I帧的时间戳
//		 framePos,查找到的关键帧的文件位置信息结构指针,详见PFRAME_POS.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
PLAYSDK_API BOOL CALLMETHOD PLAY_GetKeyFramePosByAbsTime(LONG nPort, SYSTEMTIME* t, FRAME_POS* framePos);

//------------------------------------------------------------------------
// 函数: PLAY_GetNextKeyFramePosByAbsoluteTime
// 描述: 按绝对时间查找指定位置之后的关键帧位置.
// 参数: nPort,通道号
//		 t,绝对时间,详见SYSTEMTIME.仅用到年月日时分秒.注：在执行成功后该值存储所返回的I帧的时间戳
//		 framePos,查找到的关键帧的文件位置信息结构指针,详见PFRAME_POS.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
PLAYSDK_API BOOL CALLMETHOD PLAY_GetNextKeyFramePosByAbsTime(LONG nPort, SYSTEMTIME* t, FRAME_POS* framePos);

//------------------------------------------------------------------------
// 函数: PLAY_QueryGroupPlayingTime
// 描述: 查询当前组中正在播放的时间.
// 参数: nPort,通道号
//		 pDateTime,时间
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
PLAYSDK_API BOOL CALLMETHOD PLAY_QueryGroupPlayingTime(void* hPlayGroup,  DATETIME_INFO *pDateTime);

//------------------------------------------------------------------------
// 函数: PLAY_GetAudioChannels
// 描述: 获取音频通道总数
// 参数: nPort,通道号
//       pChannels, 输出参数，[0-255].
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetAudioChannels(LONG nPort, DWORD* pChannels);

//------------------------------------------------------------------------
// 函数: PLAY_ChooseAudio
// 描述: 选择音频通道
// 参数: nPort,通道号
//       nChannelID, 音频通道从0开始.
//       bFlag,TRUE打开,FALSE关闭
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ChooseAudio(LONG nPort, DWORD nChannelID, BOOL bFlag);

//------------------------------------------------------------------------
// 函数: PLAY_GetAudioChooseState
// 描述: 获取音频通道打开关闭状态
// 参数: nPort,通道号
//       nChannelID, 音频通道[0-255].
//       pFlag,TRUE打开,FALSE关闭
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetAudioChooseState(LONG nPort, DWORD nChannelID, BOOL* bFlag);

//------------------------------------------------------------------------
// 函数: PLAY_SetPlayedAbsTime
// 描述: 按绝对时间设置播放时间
// 参数: nPort,通道号
//		 pDateTime,绝对时间
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayedAbsTime(LONG nPort, DATETIME_INFO *pDateTime);

//------------------------------------------------------------------------
// 函数: PLAY_SetPlayPosByFileOffset
// 描述: 按文件偏移设置播放位置
// 参数: nPort,通道号
//		 nFileOffset,文件偏移位置
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayPosByFileOffset(LONG nPort, UINT nFileOffset);

//------------------------------------------------------------------------
// 函数: PLAY_GetCurrentFrameRateEx
// 描述: 获得当前帧率（小数形式）
// 参数: nPort,通道号
// 返回: float,当前帧率
//------------------------------------------------------------------------
PLAYSDK_API float CALLMETHOD PLAY_GetCurrentFrameRateEx(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_InitDDraw
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_InitDDraw(HWND hWnd);

//------------------------------------------------------------------------
// 函数: PLAY_GetCaps
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API int	CALLMETHOD PLAY_GetCaps();

//------------------------------------------------------------------------
// 函数: PLAY_GetFileHeadLength
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetFileHeadLength();

//------------------------------------------------------------------------
// 函数: PLAY_RealeseDDraw
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_RealeseDDraw();

//------------------------------------------------------------------------
// 函数: PLAY_GetDDrawDeviceTotalNums
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetDDrawDeviceTotalNums();

//------------------------------------------------------------------------
// 函数: PLAY_SetDDrawDevice
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDDrawDevice(LONG nPort,DWORD nDeviceNum);

//------------------------------------------------------------------------
// 函数: PLAY_GetDDrawDeviceInfo
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetDDrawDeviceInfo(DWORD nDeviceNum,LPSTR  lpDriverDescription,DWORD nDespLen,LPSTR lpDriverName ,DWORD nNameLen,LONG *hhMonitor);

//------------------------------------------------------------------------
// 函数: PLAY_GetCapsEx
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API int	CALLMETHOD PLAY_GetCapsEx(DWORD nDDrawDeviceNum);

//------------------------------------------------------------------------
// 函数: PLAY_ThrowBFrameNum
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ThrowBFrameNum(LONG nPort,DWORD nNum);

//------------------------------------------------------------------------
// 函数: PLAY_InitDDrawDevice
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL	CALLMETHOD PLAY_InitDDrawDevice();

//------------------------------------------------------------------------
// 函数: PLAY_ReleaseDDrawDevice
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API void CALLMETHOD PLAY_ReleaseDDrawDevice();

//------------------------------------------------------------------------
// 函数: PLAY_Back
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_Back(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetDDrawDeviceEx
// 描述: 此接口无效 
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDDrawDeviceEx(LONG nPort,DWORD nRegionNum,DWORD nDeviceNum);


//------------------------------------------------------------------------
// 函数: PLAY_SetOverlayMode
// 描述: 此接口无效，overlay模式已经过时
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetOverlayMode(LONG nPort,BOOL bOverlay,COLORREF colorKey);


//------------------------------------------------------------------------
// 函数: PLAY_GetOverlayMode
// 描述: 此接口无效，overlay模式已经过时
//------------------------------------------------------------------------
PLAYSDK_API LONG CALLMETHOD PLAY_GetOverlayMode(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_GetColorKey
// 描述: 此接口无效，overlay模式已经过时
//------------------------------------------------------------------------
PLAYSDK_API COLORREF CALLMETHOD PLAY_GetColorKey(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_ChangeRate
// 描述: 替代接口PLAY_SetPlaySpeed
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ChangeRate(LONG nPort, int rate);

//------------------------------------------------------------------------
// 函数: PLAY_SetTimerType
// 描述: 此接口无效
PLAYSDK_API BOOL CALLMETHOD PLAY_SetTimerType(LONG nPort,DWORD nTimerType,DWORD nReserved);

//------------------------------------------------------------------------
// 函数: PLAY_GetTimerType
// 描述: 此接口无效
PLAYSDK_API BOOL CALLMETHOD PLAY_GetTimerType(LONG nPort,DWORD *pTimerType,DWORD *pReserved);

//------------------------------------------------------------------------
// 函数: PLAY_SetMDRange
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMDRange(LONG nPort,DISPLAYRECT* rc,DWORD nVauleBegin,DWORD nValueEnd,DWORD nType);

//------------------------------------------------------------------------
// 函数: PLAY_SetMDThreShold
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMDThreShold(LONG nPort, DWORD ThreShold);

//------------------------------------------------------------------------
// 函数: PLAY_GetMDPosition
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetMDPosition(LONG nPort, DWORD Direction, DWORD nFrame, DWORD* MDValue);


//------------------------------------------------------------------------
// 函数: PLAY_CutFileSegment
// 描述: 此接口无效
//------------------------------------------------------------------------
typedef void (CALLBACK *CutProgressFunc)(DWORD nPort, int iProgress, DWORD dwUser);
PLAYSDK_API BOOL CALLMETHOD PLAY_CutFileSegment(LONG nPort, 
												LONG lBeginTime, 
												LONG lEndTime, 
												CutProgressFunc pFunc, 
												char *sOutFilePath, 
												DWORD dwUser);

//------------------------------------------------------------------------
// 函数: PLAY_SetVideoPerTimer
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetVideoPerTimer(int iVal);


//------------------------------------------------------------------------
// 函数: PLAY_GetVideoPerTimer
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetVideoPerTimer(int* pVal);

//------------------------------------------------------------------------
// 函数: PLAY_InputVideoData
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_InputVideoData(LONG nPort,PBYTE pBuf,DWORD nSize);

//------------------------------------------------------------------------
// 函数: PLAY_InputAudioData
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_InputAudioData(LONG nPort,PBYTE pBuf,DWORD nSize);

//------------------------------------------------------------------------
// 函数: PLAY_SetVerifyCallBack
// 描述: 此接口无效
//------------------------------------------------------------------------
typedef void (CALLBACK * fVerifyCBFun)(LONG nPort, FRAME_POS * pFilePos, DWORD bIsVideo, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetVerifyCallBack(LONG nPort, DWORD nBeginTime, DWORD nEndTime, fVerifyCBFun VerifyFun, void* pUserData);


//------------------------------------------------------------------------
// 函数: PLAY_SetSourceBufCallBack
// 描述: 此接口无效
//------------------------------------------------------------------------
typedef void (CALLBACK * fSourceBufCBFun)(LONG nPort,DWORD nBufSize, void* pUserData,void*pResvered);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetSourceBufCallBack(LONG nPort,
													  DWORD nThreShold,
													  fSourceBufCBFun SourceBufCBFun,
													  void* pUserData,
													  void *pReserved);

//------------------------------------------------------------------------
// 函数: PLAY_ResetSourceBufFlag
// 描述: 此接口无效
//------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ResetSourceBufFlag(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetPandoraWaterMarkCallBack
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPandoraWaterMarkCallBack(LONG nPort, GetWaterMarkInfoCallbackFunc pFunc, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_SetDisplayBuf
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayBuf(LONG nPort,DWORD nNum);

//------------------------------------------------------------------------
// 函数: PLAY_GetDisplayBuf
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetDisplayBuf(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetDisplayType
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayType(LONG nPort,LONG nType);

//------------------------------------------------------------------------
// 函数: PLAY_GetDisplayType
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API LONG CALLMETHOD PLAY_GetDisplayType(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_RefreshPlayEx
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_RefreshPlayEx(LONG nPort,DWORD nRegionNum);

//------------------------------------------------------------------------
// 函数: PLAY_OpenStreamEx
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_OpenStreamEx(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize);

//------------------------------------------------------------------------
// 函数: PLAY_CloseStreamEx
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_CloseStreamEx(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_AdjustFluency
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_AdjustFluency(LONG nPort, int level);

//------------------------------------------------------------------------
// 函数: PLAY_SurfaceChange
// 描述: Android版本专用，Surface建立或变化通知
// 参数: 
// 返回: 
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SurfaceChange(LONG nPort, HWND hWnd);

//------------------------------------------------------------------------
// 函数: PLAYER_SetFileInfoFrameCallback
// 描述: 设置文件信息帧回调函数
// 参数: 
// 返回: 
//------------------------------------------------------------------------
typedef int (CALLBACK* fOnFileInfoFrame)(LONG nPort, FILE_INFO_IMAGE* pFileInfoImage, FILE_INFO_FRAME* pFileInfoFrame, void* pUserParam);
PLAYSDK_API BOOL CALLMETHOD	PLAY_SetFileInfoFrameCallback(LONG nPort, fOnFileInfoFrame fFileInfoFrame, tPicFormats imageType, void* pUserParam);

//------------------------------------------------------------------------
// 函数: PLAYER_SetAnalyzePositionCallback
// 描述: 设置文件信息帧分析进度回调函数
// 参数: 
// 返回: 
//------------------------------------------------------------------------
typedef int (CALLBACK *fOnAnalyzePosition)(LONG nPort, DATETIME_INFO* pstDateTime, void* pUserParam);
PLAYSDK_API BOOL CALLMETHOD	PLAY_SetAnalyzePositionCallback(LONG nPort, fOnAnalyzePosition fAnalyzePosition, void* pUserParam);

//------------------------------------------------------------------------
// 函数: PLAYER_StartFileFrameDetect
// 描述: 需要在索引建立完成之后，开始文件信息帧检测，输入搜索条件
// 参数: 
// 返回: 
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD	PLAY_StartFileFrameDetect(LONG nPort, FILE_INFO_FRAME_SEARCH* pFileInfoFrameSearch);

//------------------------------------------------------------------------
// 函数: PLAYER_StopFileFrameDetect
// 描述: 中止搜索
// 参数: 
// 返回: 
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD	PLAY_StopFileFrameDetect(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_StartEdgeEnhance
// 描述: 开启图像锐化处理
// 参数: level	   -- 处理等级,0-关闭,6-最强,默认等级4
//		 algMode   -- 算法模式,预留接口,目前只支持0
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartEdgeEnhance(LONG nPort, int level, int algMode);

//------------------------------------------------------------------------
// 函数: PLAY_StopEdgeEnhance
// 描述: 关闭图像锐化处理
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StopEdgeEnhance(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_StartVideoStable
// 描述: 开启视频防抖
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartVideoStable(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_StopEdgeEnhance
// 描述: 关闭视频防抖
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StopVideoStable(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetDisplayScale
// 描述: 设置显示比例大小，IOS专用以便适配不同的机型.
// 参数: nPort,通道号
//		 fScale，显示比例，默认为1.0
//		 nRegionNum,显示区域序号,0~(MAX_DISPLAY_WND-1),如果为0,则将设置的区域显示在主窗口中.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayScale(LONG nPort, float fScale, DWORD nRegionNum);

//------------------------------------------------------------------------
// 函数: PLAY_Scale
// 描述: 手机版本图像缩放
// 参数: nPort  端口号
//       scale	缩放比例[1.0, 8.0]
//       nRegionNum,显示区域序号, 保留。
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_Scale(LONG nPort, float scale, DWORD nRegionNum);

//------------------------------------------------------------------------
// 函数: PLAY_Translate
// 描述: 手机版本图像平移
// 参数: nPort  端口号
//       x	x平移坐标，绝对值
//	     y	y平移坐标，绝对值
//       nRegionNum,显示区域序号, 保留。
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_Translate(LONG nPort, float x, float y, DWORD nRegionNum);

//------------------------------------------------------------------------
// 函数: PLAY_SetIdentity
// 描述: 手机版本图像归一化，重置平移，缩放操作。
// 参数: nPort  端口号
//       nRegionNum,显示区域序号, 保留。
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetIdentity(LONG nPort, DWORD nRegionNum);

//------------------------------------------------------------------------
// 函数: PLAY_GetScale
// 描述: 手机版本获取当前缩放值。
// 参数: nPort  端口号
//       nRegionNum,显示区域序号, 保留。
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API float CALLMETHOD PLAY_GetScale(LONG nPort, DWORD nRegionNum);

//------------------------------------------------------------------------
// 函数: PLAY_GetTranslateX
// 描述: 手机版本获取当前x轴平移坐标。
// 参数: nPort  端口号
//       nRegionNum,显示区域序号, 保留。
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API float CALLMETHOD PLAY_GetTranslateX(LONG nPort, DWORD nRegionNum);

//------------------------------------------------------------------------
// 函数: PLAY_GetTranslateX
// 描述: 手机版本获取当前y轴平移坐标。
// 参数: nPort  端口号
//       nRegionNum,显示区域序号, 保留。
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API float CALLMETHOD PLAY_GetTranslateY(LONG nPort, DWORD nRegionNum);

//------------------------------------------------------------------------
// 函数: PLAY_CleanScreen, PLAY_Stop前调用有效
// 参数: nRegionNum 默认填0
// 描述: 手机版本清屏功能
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_CleanScreen(LONG nPort, float red, float green, float blue, float alpha, DWORD nRegionNum);

//------------------------------------------------------------------------
// 函数: PLAY_ViewResolutionChanged
// 描述: Android版本,SurfaceView大小变化时调用
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ViewResolutionChanged(LONG nPort, int nWidth, int nHeight, DWORD nRegionNum);

//------------------------------------------------------------------------
// 函数: PLAY_StartDataRecordEx
// 描述: 开始流数据录像,只对流模式有用,在PLAY_Play之后调用.
// 参数: nPort,通道号
//		 sFileName,录像文件名,如果文件名中有不存在的文件夹,就创建该文件夹.
//		 idataType,0表示原始视频流;1表示转换成AVI格式;2表示转换成ASF格式;3分段保存文件
//		 fListenter, 回调函数，监听数据写过程中发生错误.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef void (CALLBACK* fRecordErrorOccur)(LONG nPort, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_StartDataRecordEx(LONG nPort, char *sFileName, int idataType, fRecordErrorOccur fListenter, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_SetMultiFrameDecCallBack
// 描述: 开启解码信息回调，针对SVAC码流中的些监控信息。
// 参数: nPort  端口号
//       nRegionNum,显示区域序号, 保留。
//		 DecInfoCallBack, 回调函数
//		 pUser, 用户回调数据
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
typedef void (CALLBACK* fMultiFrameDecCallBack)(LONG nPort, LONG nStreamID, char* pData, LONG nLen, 
										  FRAME_INFO* stFrameInfo, void* pUserData, LONG nReserved1);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMultiFrameDecCallBack(LONG nPort, fMultiFrameDecCallBack DecInfoCallBack, void* pUser);

//------------------------------------------------------------------------
// 函数: PLAY_SetMultiFrameCallBack
// 描述: 开启多帧信息回调，目前主要针对SVAC编码，
//       SVC功能中，一份数据带有基本层和增强层两份数据
// 参数: nPort  端口号
//       MultiFrameCallBack, 回调函数。
//       pUser  用户数据
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
typedef void (CALLBACK* fMultiFrameCallBack)(LONG nPort, LONG nStreamID, void* pUserData, LONG nReserved);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMultiFrameCallBack(LONG nPort, fMultiFrameCallBack MultiFrameCallBack, void* pUser);

//------------------------------------------------------------------------
// 函数: PLAY_SetDecInfoCallBack
// 描述: 开启多帧信息回调，针对SVAC码流
// 参数: nPort  端口号
//       nFrameID, 选择进行播放的帧
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
typedef void (CALLBACK* fDecInfoCallBack)(LONG nPort, FRAME_DEC_EXT_INFO* pDecInfo, void* pUserData, LONG nReserved);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecInfoCallBack(LONG nPort, fDecInfoCallBack DecInfoCallBack, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_ChooseFrame
// 描述: 选择显示SVAC编码SVC的基本层或增强层
// 参数: nPort  端口号
//       nFrameID, 要显示的层(0: 基本层，1: 增强层)
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ChooseFrame(LONG nPort, LONG nFrameID);

//------------------------------------------------------------------------
// 函数: PLAY_RenderPrivateData
// 描述: 显示私有数据，例如规则框，规则框报警，移动侦测等
// 参数: nPort  端口号
//       bTrue TRUE:打开 FALSE:关闭
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_RenderPrivateData(LONG nPort, BOOL bTrue, LONG nReserve);

//------------------------------------------------------------------------
// 函数: PLAY_SetFileIndexProgressCallBack
// 描述: 设置索引创建进度回调
// 参数: nPort  端口号
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
typedef void (CALLBACK* fIndexProgressCB)(LONG nPort, float fProgress, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileIndexProgressCallBack(LONG nPort, fIndexProgressCB IndexProgressCB, void* pUser);

//------------------------------------------------------------------------
// 函数: PLAY_GetLastYUVFrame
// 描述: 主动获取上一帧对应的YUV数据
// 参数: nPort  端口号
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetLastYUVFrame(LONG nPort, FRAME_DECODE_INFO* pFrameDecodeInfo);

//IOS特殊要求：内存减小版本
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMemMinimized(LONG nPort);

PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecodeThreadNum(LONG nPort, DWORD nNum);

//设置解密密钥，SVAC解码使用
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecodeKey(LONG nPort, const unsigned char *key, unsigned int key_len);

PLAYSDK_API BOOL CALLMETHOD PLAY_GetIRefValue(LONG nPort, BYTE *pBuffer, DWORD *pSize);

#ifdef __native_client__

#define FISHEYE_REGION 16
//------------------------------------------------------------------------
// 函数: PLAY_OutsideRender
// 描述: nacl ui线程调用此接口
// 参数: nPort  端口号
// 参数: nWidth  窗口宽
// 参数: nHeight  窗口高
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_OutsideRender(LONG nPort, int nX, int nY, int nWidth, int nHeight, unsigned int nRegionNum = 0);

namespace pp
{
	class Instance;
}
//------------------------------------------------------------------------
// 函数: PLAY_SetNACLInstance
// 描述: nacl 主线程调用此接口设置句柄地址
// 参数: pInstance  传入pp::instance地址
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetNACLInstance(pp::Instance * pInstance);
#endif

typedef void (CALLBACK* fDoubleVisibleDecCBFun)(LONG nPort,char * pBuf, int nSize, int nWidth, int nHeight, 
												char* pSecondBuf, int nSecondSize, int nSecondWidth, int nSecondHeight, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDoubleVisibleDecCallBack(LONG nPort, fDoubleVisibleDecCBFun DataCBFun, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_EnableAudioChannel
// 描述: 控制左右声道音频播放，仅对左右声道音频有效。
// 参数: nPort  端口号
// 参数: nChnNum  左右通道，0-左通道，1-右通道
// 参数: bEnable  使能 TRUE-启用， FALSE-禁用
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_EnableAudioChannel(LONG nPort, DWORD nChnNum, BOOL bEnable);

//------------------------------------------------------------------------
// 函数: PLAY_SplitProc
// 描述: yuv 拼接算法，用于4k大屏的显示
// 参数: nPort  端口号
// 参数: nMode 模式，0对应基本模式，1对应1+3模式，2对应1+5模式, 3对应1+1模式（电子放大）
//					 4对应1P+3, 5对应1P+6
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SplitProc(LONG nPort, int nMode);

//------------------------------------------------------------------------
// 函数: PLAY_SplitProcUpdate
// 描述: yuv 拼接算法，更新需要放大的矩形位置
// 参数: nPort  端口号
// 参数: pAreaRect 矩形坐标数组的起始地址
//       如果nMode是0，则应为NULL
//       如果nMode是1，则该数组的大小应为3
//       如果nMode是2，则该数组的大小应为5              | 
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SplitProcUpdate(LONG nPort, DISPLAYRECT* pAreaRect);

/************************************************************************/
/* 函数: PLAY_SetRenderMode
   描述: 指定渲染模式(Windows平台), PLAY_Play之前调用有效
   参数: nPort,通道号
	     nMode, 渲染模式
   返回: BOOL,成功返回TRUE,失败返回FALSE.                                                                     */
/************************************************************************/
PLAYSDK_API BOOL CALLMETHOD PLAY_SetRenderMode(LONG nPort, RenderType nMode);

/************************************************************************/
/* 函数: PLAY_InitThirdPartyLibrary
   描述: 初始化第三方解密库
   参数: nPort,通道号
   返回: BOOL,成功返回TRUE,失败返回FALSE.
*/
/************************************************************************/
PLAYSDK_API BOOL CALLMETHOD PLAY_InitThirdPartyLibrary(LONG nPort, const char* kmcSvrIP,int kmcSvrPort,const char* macAddr);

/************************************************************************/
/* 函数: PLAY_SetDecodeStrategy
   描述: 设置解码策略,错误码流花屏或跳秒
   参数: nPort,通道号
   参数: 16:表示解码中遇到frame不连续，提前返回
		 8: 表示解码中遇到码流数据不符合协议当成解码错误
		 0: 表示解码中遇到码流数据不符合协议继续解码，错误码流会花屏
   返回: BOOL,成功返回TRUE,失败返回FALSE.
*/
/************************************************************************/
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecodeStrategy(LONG nPort, int nStrategyType);

/************************************************************************/
/* 函数: PLAY_SetAVSyncType
   描述: 设置音视频播放策略
   参数: nPort,通道号
         nAVSyncType,码流播放基准参数。nAVSyncType=0，以视频为基准；nAVSyncType=1，以音频为基准
   返回: BOOL,成功返回TRUE,失败返回FALSE.
*/
/************************************************************************/
typedef enum
{
	AV_SYNC_VIDEO_MASTER,	//以视频为基准
	AV_SYNC_TIME_STAMP      //以时间戳为基准
}AV_SYNC_TYPE;
PLAYSDK_API BOOL CALLMETHOD PLAY_SetAVSyncType(LONG nPort,AV_SYNC_TYPE nAVSyncType);

/************************************************************************/
/* nMode可以取-1,0,1,2,3,4
-1不进行噪声消除
 0噪声消除的程度最低，对有用语音信号的损害最小
 4噪声消除的程度最大,对有用语音信号的损害最大
 */
/************************************************************************/
PLAYSDK_API BOOL CALLMETHOD PLAY_SetSEnhanceMode(LONG nPort,int nMode);


/************************************************************************/
/* 第三方解密扩展接口, 支持外层自实现                   
 */
/************************************************************************/
enum ThirdDecryptType
{
	DECRYPT_KTJM = 4, /*凯天解密*/
	DECRYPT_SYJM,	  /*晟元解密*/
	DECRYPT_HZSD,     /*杭师大算法*/
	DECRYPT_ZBQL,     /*中标麒麟算法*/
};
typedef struct 
{ 
	ThirdDecryptType type; /*第三方解密类型*/
	BOOL (*Init)();		   /*初始化接口,全局初始化一次*/
	BOOL (*DeInit)();	   /*反初始化接口*/
	void* (*Open)();	   /*打开解密通道, 返回值不能为空!*/
	BOOL (*Decrypt)(void* handle, 
					unsigned char* inData,  unsigned int inLen, 
					unsigned char* outData, unsigned int& outLen);/*解密, 对返回值有要求(1成功0失败)*/
	BOOL (*Close)(void* handle); /*关闭解密通道*/
}ThirdDecryptHook;
PLAYSDK_API BOOL CALLMETHOD PLAY_Register3rdDecryptHook(ThirdDecryptHook* decryptHook);

#ifdef	__cplusplus
}
#endif

#endif
