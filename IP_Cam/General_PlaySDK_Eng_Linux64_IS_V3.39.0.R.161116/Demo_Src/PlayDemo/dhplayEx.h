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

/*���ݾɰ汾���۽ӿ�*/
typedef enum
{
	FISHSHOWMODE_WALL_PANORAMA = 0,       //��װȫ��ģʽ
	FISHSHOWMODE_CEIL_PANORAMA,           //��װ360��ȫ��
	FISHSHOWMODE_CEIL_PANORAMA_TWO,       //��װ180��ȫ��
	FISHSHOWMODE_FLOOR_PANORAMA,          //�ذ尲װ360��ȫ��
	FISHSHOWMODE_FLOOR_PANORAMA_TWO,      //�ذ尲װ180��ȫ�� 
	FISHSHOWMODE_ONE_O_THREE,             //1+3ģʽ
	FISHSHOWMODE_CEIL_ONE_REGION = 10,    //��װ������eptz
	FISHSHOWMODE_CEIL_FOUR_REGION,        //��װ4����eptz
	FISHSHOWMODE_ORIGINAL,                //ԭʼģʽ����������ֱ�����ԭʼ����
	FISHSHOWMODE_WALL_ONE_REGION,         //��װ������eptz
	FISHSHOWMODE_WALL_FOUR_REGION,        //��װ4����eptz
	FISHSHOWMODE_FLOOR_ONE_REGION,        //�ذ尲װ������eptz
	FISHSHOWMODE_FLOOR_FOUR_REGION,       //�ذ尲װ4����eptz����ԭʼ����
	FISHSHOWMODE_WALL_ONE_O_THREE,	      //�ذ�1+3ģʽ
	FISHSHOWMODE_CEIL_ONE_O_THREE,	      //��װ1+3ģʽ
	FISHSHOWMODE_FLOOR_ONE_O_THREE,	      //��װ1+3ģʽ

}FISHSHOWMODES;

typedef enum
{
	FISHEPTZOPT_UPDATE_FOCUS,                   //���½���
	FISHEPTZOPT_ZOOM_IN,                        //�Ŵ�
	FISHEPTZOPT_ZOOM_OUT,                       //��С
	FISHEPTZOPT_MOVE_UP,                        //�����ƶ�
	FISHEPTZOPT_MOVE_DOWN,                      //�����ƶ�
	FISHEPTZOPT_MOVE_LEFT,                      //�����ƶ�
	FISHEPTZOPT_MOVE_RIGHT,                     //�����ƶ�
	FISHEPTZOPT_AUTO_ROTATE_CLOCKWISE,          //�Զ�˳ʱ����ת
	FISHEPTZOPT_AUTO_ROTATE_COUNTERCLOCKWISE,   //�Զ���ʱ����ת
	FISHEPTZOPT_STOP_AUTO_ROTATE,				//ֹͣ�Զ���ת
	FISHEPTZOPT_GET_POSITION,					//��ȡ��ǰ��̨��������λ��
	FISHEPTZOPT_SELECT_REGION_ZOOMIN_ON,        //��ѡ�Ŵ�
	FISHEPTZOPT_SELECT_REGION_ZOOMIN_OFF,		//�˳���ѡ�Ŵ�
	FISHEPTZOPT_RESTORE_DEFAULT_LOCATION,		//��̨�ָ�Ĭ��λ��

}FISHEPTZOPTS;
/***************/

//@begin��������
typedef struct
{
	int   himg_width;                       //�����ͼ���
	int   himg_height;                      //�����ͼ���
	int   *zoom_list;						/*���������*/
	int    zoom_list_size;					/*���������λ����*/
}MHFPTZ_INITPARAM;
//@end��������

typedef struct 
{
	int radius;      //Ŀ������Բ�뾶��������Ϊ8192����ϵ
	int originX;     //Ŀ������ԲԲ�ġ�������Ϊ8192����
	int originY;
	FISHEYE_SIZE srcSize; //��������Բ�Ŀ��
	FISHEYE_SIZE dstSize; //�������ͼ�Ŀ��
	int winId;			//Ŀ�괰�ڵ�id
	FISHEYE_MOUNTMODE mountMode;     //���۰�װģʽ
	FISHEYE_CALIBRATMODE calibMode; //����ģʽ
	FISHEYE_REGIONPARAM regionParam;  //ͨ��Fisheye_EptzUpdate ��FISHEYE_EPTZ_CMD_GET_CUR_REGION ���

}FISHRECTIFY_INFO;

// ������Ϣ
typedef struct __DATETIME_INFO
{
	unsigned int			nYear;			// ��
	unsigned int			nMonth;			// ��
	unsigned int			nDay;			// ��
	unsigned int			nHour;			// ʱ
	unsigned int			nMinute;		// ��
	unsigned int			nSecond;		// ��
	unsigned int			nMilliSecond;	// ����
}DATETIME_INFO;

typedef struct 
{
	char*	pHead;				//֡����(����ͷ)
	int		nLen;				//֡���ݳ���
	char*	pBody;				//������(������ͷ)
	int		nBodyLen;			//�����ݳ���
	
	int		nRet;				//0:��������  1://������  Ĭ��Ϊ0
	char	reserved[128];
}DemuInfoEx;

typedef struct
{
	int type;			// 1:VIDEO, 2:AUDIO, 3:DATA
	int subtype;		// I Frame, BP Frame, PCM8, MS-ADPCM etc.
	int encode;			// MPEG4, H264, STDH264
	int sequence;		// I֡�����������
	
	// ͼ���С��Ϣ
	int width;
	int height;
	
	// ֡����Ϣ
	int rate;
	
	// ʱ����Ϣ
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

// �ļ���Ϣ֡
typedef struct __FILE_INFO_FRAME
{
	unsigned int		nFrameSubType;	  // ֡�����ͣ���������֡���¼�֡��
	DATETIME_INFO*		pstDateTimeStart; // ��ʼʱ��
	DATETIME_INFO*		pstDateTimeEnd;   // ����ʱ��
	unsigned char*		pFrameData;		  // ֡����
	unsigned int		nFrameDataLen;	  // ֡���ݳ���
} FILE_INFO_FRAME;

typedef struct __FILE_INFO_FRAME_SEARCH
{
	unsigned int		nFileFrameType;		//�������ͣ�������ϣ��� PLAYER_INFO_TYPE_MOTIONDECT | PLAYER_INFO_TYPE_EVENT
	DATETIME_INFO		stStartDataTime;    //��ʼʱ��
	DATETIME_INFO		stEndDataTime;      //����ʱ��
	DISPLAYRECT			rtDetectedRegion;   //�������еĶ����ⷶΧ������֡ʱ��Ч���������Ϊ0ʱ����ʾȫ��������
	DISPLAYRECT			rtTotal;			//������, ����֡ʱ��Ч
} FILE_INFO_FRAME_SEARCH;

typedef struct __FILE_INFO_IMAGE
{
	tPicFormats	   imageType;				// ͼƬ������
	unsigned char* pPicBuf;					// ͼƬ�Ļ���ָ��
	unsigned int   nPicBufLen;				// ͼƬ�ĳ���

} FILE_INFO_IMAGE;

typedef struct NativeHandle
{
	void* display;
	void* context;
	void* surface;

}Android_NativeHandle;

// �ļ���Ϣ֡���������ͣ���ӦFILE_INFO_FRAME_SEARCH�ṹ���е�nFileFrameType
#define PLAY_INFO_TYPE_MOTIONDECT     1         // ����
#define PLAY_INFO_TYPE_EVENT		  2         // �¼�

//��������ģʽ���ܿ���
#define NEWFUNC_FTRACK_MODE_RT 0x01

/************************************************************************/
/* ��ǿ֧�ֵĹ���                                                         */
/************************************************************************/
typedef enum 
{
	IVSEFUNCTYPE_DEHAZE,	    // ȥ��
	IVSEFUNCTYPE_DENOISE,		// ȥ��
	IVSEFUNCTYPE_WB,			// ƫɫУ��
	IVSEFUNCTYPE_LOWLIGHT,		// ���ն���ǿ
	IVSEFUNCTYPE_HDR,			// ��̬
	IVSEFUNCTYPE_NUM			// ֧����ǿ�Ĺ��ܸ���
}IVSEFUNCTYPE;

/************************************************************************/
/* ROI�������Ͷ���                                                        */
/************************************************************************/
typedef struct
{
    int x;          // ���Ͻ�x����
    int y;          // ���Ͻ�y����
    int width;      // ������
    int height;     // ����߶�
}IVSEROI;

/************************************************************************/
/* ��Ƶ��ǿ�㷨�������                                                           */
/************************************************************************/
typedef struct
{
    IVSEFUNCTYPE eFuncType;   // ����ѡ��
    IVSEROI		 cRoi;        // ROI ����
	int			 nMode;       // 0��ʾͼƬģʽ�� 1��ʾ��Ƶģʽ
    int			 nProcess_param[2];     // �����������Χ[1,5]
	/*
    ���ܺ���	                process_param[0]	    process_param[1]
    IVSEFUNCTYPE_DEHAZE	        ������	                ���Ͷ�
    IVSEFUNCTYPE_DENOISE	    ������	                - ����Ƶģʽ��Ч��
    IVSEFUNCTYPE_WB	        -	                    -
    IVSEFUNCTYPE_LOWLIGHT	-   ������	                ���Ͷ�
    IVSEFUNCTYPE_HDR	        0:���� 1:��ҹ 2:�Զ�  	������
    */

}IVSEPARAMS;

/********************************************************************
*	������: 	    	PLAY_SetupPrepareTime
*	Ŀ��:				����Ԥ¼�Ļ���
*   �������:           nPort:		����ͨ����
						nTime:		Ԥ¼������
						tmpDir:		��ʱ��Ԥ¼Ŀ¼
*   �������:        
*   ����ֵ:             TRUE:	�ɹ�.
						FALSE:	ʧ��
*   ����ʱ��:	        2012:12:21  
*   �汾��Ϣ��¼:	    2012/12/21:YeYamin:modify......
*********************************************************************/

PLAYSDK_API BOOL	CALLMETHOD PLAY_SetupPrepareTime(LONG nPort,int nTime,const char* tmpDirectory);

/********************************************************************
*	������: 	    	PLAY_StartPrepareRecord
*	Ŀ��:				��ʼԤ¼
*   �������:		     nPort:		����ͨ����
						 pFileName:	¼��λ��
*   �������:        
*   ����ֵ:             TRUE:	�ɹ�.
						FALSE:	ʧ��
*   ����ʱ��:	        2012:12:21  
*   �汾��Ϣ:			2012/12/21:YeYamin:modify......
*********************************************************************/

PLAYSDK_API BOOL	CALLMETHOD PLAY_StartPrepareRecord(LONG nPort,const char* pFileName);

/********************************************************************
*	������: 	    	PLAY_StopPrepareRecord
*	Ŀ��:	
*   �������:			port:		����ͨ����
*   �������:        
*   ����ֵ:             TRUE:	�ɹ�.
						FALSE:	ʧ��
*   ����ʱ��:	        2012:12:21  
*   �汾��Ϣ��¼:		2012/12/21:YeYamin:modify......
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
#define IVSINFOTYPE_MOTIONFRAME		9 /*��̬�������֡*/
#define IVSINFOTYPE_VIDEO_CONCENTRATION    10 
#define PSIVS						240
/********************************************************************
*	������: 	    	PLAY_SetIVSCallBack
*	Ŀ��:	
*   �������:	        nPort:		����ͨ��
						pFunc:		���ý���ص�
						nUser:		�����ģ����ڻص������Ĳ���
*   �������:        
*   ����ֵ:             TRUE:	�ɹ� 
						FALSE:	ʧ��
*   ����ʱ��:	        2012:12:21  
*	�汾��Ϣ��¼:	    2012/12/21:YeYamin:modify......
*********************************************************************/

typedef void (CALLMETHOD *GetIVSInfoCallbackFunc)(char* buf, LONG type, LONG len, LONG reallen, void* pReserved, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetIVSCallBack(LONG nPort, GetIVSInfoCallbackFunc pFunc, void* pUserData);

/********************************************************************
*	������: 	    	PLAY_StartAVIResizeConvert
*	Ŀ��:				�ı�ֱ��ʵ�AVIת��
*   �������:           nPort:		����ͨ����
						sFileName:	AVI��¼���ŵ�ַ
						lWidth & lHeight:AVI��¼��Ŀ����
*   �������:	        
*   ����ֵ:             TRUE:	�ɹ� 
						FALSE:	ʧ��
*   ����ʱ��:	        2012:12:21  
*   �汾��Ϣ��¼:	    2012/12/21:YeYamin:modify......
*********************************************************************/

PLAYSDK_API BOOL CALLMETHOD PLAY_StartAVIResizeConvert(LONG nPort, char *sFileName, LONG lWidth, LONG lHeight);

/********************************************************************
*	������: 	    	PLAY_StopAVIResizeConvert
*	Ŀ��:				����AVIת��
*   �������:           nPort:		����ͨ����
*   �������:	        
*   ����ֵ:             TRUE:	�ɹ� 
						FALSE:	ʧ��
*   ����ʱ��:	        2012:12:21  
*   �汾��Ϣ��¼:	    2012/12/21:YeYamin:modify......
*********************************************************************/

PLAYSDK_API BOOL CALLMETHOD PLAY_StopAVIResizeConvert(LONG nPort);

/********************************************************************
*	������: 	    	PLAY_SetPandoraWaterMarkCallBack
*	Ŀ��:				��Ч
*   �������:         
*   �������:	        
*   ����ֵ:             TRUE:	�ɹ� 
						FALSE:	ʧ��
*   ����ʱ��:	        2012:12:21  
*   �汾��Ϣ��¼:	    2012/12/21:YeYamin:modify......
*********************************************************************/

PLAYSDK_API BOOL CALLMETHOD PLAY_SetPandoraWaterMarkCallBack(LONG nPort, GetWaterMarkInfoCallbackFunc pFunc, void* pUserData);


/********************************************************************
*	������: 	    	PLAY_SetDigitalSignCallBack
*	Ŀ��:				��������ǩ���ص�.
*   �������:           nPort:		����ͨ����
						nFrameID:	֡���
						bSuccess:	У���Ƿ�ͨ��
						pUserData   �û�����
*   �������:	        
*   ����ֵ:             TRUE:	�ɹ� 
						FALSE:	ʧ��
*********************************************************************/
typedef void (CALLBACK* fCheckDigitalSignCB)(LONG nPort, int nFrameID, BOOL bSuccess, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDigitalSignCallBack(LONG nPort, fCheckDigitalSignCB pDigitalSignCB, void* pUserData);

/********************************************************************
*	������: 	    	PLAY_GetTimePicture
*	Ŀ��:				��þ���ʱ��������ͼƬ
*   �������:           filepath:	������ļ�·��
						time:		����ʱ��
						DecCBFun:	���ý�ȥ�Ľ���ص�
						user:		�û�������
*   �������:	        
*   ����ֵ:             TRUE:	�ɹ� 
						FALSE:	ʧ��
*   ����ʱ��:	        2012:12:21  
*   �汾��Ϣ��¼:	    2012/12/21:YeYamin:modify......
*********************************************************************/
PLAYSDK_API BOOL CALLMETHOD PLAY_GetTimePicture(const char* filepath, struct tm* time, fDecCBFun fcbDec, void* pUserData);

//------------------------------------------------------------------------
// ����: PLAY_StartFisheyeEx
// ����: ��������������չ�ӿڣ���Ҫ����fisheye.dll MCL_FPTZ.dll��
// ����: [in] nPort : ͨ����
//		 [in] startType:  �������ͣ� 0ֻ��������У��, 1ͬʱ����������У��, 2ֻ�������������㷨, 3��ʾ180�����۽���
//		 [in] funcType:   ������Щ���ܣ�0��ʾ����������1��ʾֻ��������֡���ܣ�2��ʾֻ����ץͼ��
//						  3��ʾ����֡��ץͼ�������������Ĺ���Խ�࣬���ĵ��ڴ�Խ��
//       [in] ptzChannelParam: ����������ʼ��ͨ��������startTypeΪ0ʱ��ptzChannelParam��NULL
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartFisheyeEx(LONG nPort, int startType, int funcType, MHFPTZ_INITPARAM* ptzChannelParam);

//------------------------------------------------------------------------
// ����: PLAY_StartFisheyeMPTZ
// ����: ��������������չ�ӿڣ�֧��һ�����
// ����: [in] nPort : ͨ����
//		 [in] startType:  �������ͣ� 0ֻ��������У��, 1ͬʱ����������У��, 2ֻ�������������㷨, 3��ʾ180�����۽���
//		 [in] funcType:   ������Щ���ܣ�0��ʾ����������1��ʾֻ��������֡���ܣ�2��ʾֻ����ץͼ��
//						  3��ʾ����֡��ץͼ�������������Ĺ���Խ�࣬���ĵ��ڴ�Խ��
//       [in] ptzChannelParam: ����������ʼ��ͨ��������startTypeΪ0ʱ��ptzChannelParam��NULL
//		 [in] ptzChannelNum: ����������ʼ��ͨ����  
//		 [in] imgMaxOutput:  ���ͼ�����ķֱ���
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartFisheyeMPTZ(LONG nPort, int startType, int funcType, MHFPTZ_INITPARAM* ptzChannelParam, int ptzChannelNum, FISHEYE_SIZE* pImgMaxOutput);


//------------------------------------------------------------------------
// ����: PLAY_SetFisheyeParams, ���ݾɰ汾���۽ӿ�
// ����: �������۲���
// ����: [in]nPort           :  ͨ����
//		 [in]nX				 :  ����Բ�ĺ�����
//       [in]nY				 :  ����Բ��������
//       [in]nRadius         :  ���۰뾶
//       [in]nLensDirection  :  ��ͷ���� 
//       [in]mode            :  ͼ����ʾģʽ
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFisheyeParams(LONG nPort, int nX, int nY, int nRadius, int nLensDirection, FISHSHOWMODES mode);

//------------------------------------------------------------------------
// ����: PLAY_FisheyeGetPosition, ���ݾɰ汾���۽ӿ�
// ����: ���Ŀ�����Ķ�Ӧ������̨�Ľ���λ��
// ����: [in]nPort           :  ͨ����
//		 [in]row			 :  Ŀ������������
//       [in]column			 :  Ŀ������������
//		 [out]pX     		 :  Ŀ����������Ӧ������̨�Ľ��������
//       [out]pY		     :  Ŀ����������Ӧ������̨�Ľ���������
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_FisheyeGetPosition(LONG nPort, int row, int column, int *pX, int *pY);

//------------------------------------------------------------------------
// ����: PLAY_FisheyeEptzUpdate, ���ݾɰ汾���۽ӿ�
// ����: ����eptz(������̨�������������ƶ�
// ����: [in]nPort           :  ͨ����
//		 [in/out]pX			 :  eptz��������̨���Ľ��������
//       [in/out]pY			 :  eptz�Ľ���������
//		 [in/out]pHangle		 :  eptz��ˮƽ�Ƕȷ�Χ(0-3600)
//       [in/out]pVangle		 :  eptz�Ĵ�ֱ�Ƕȷ�Χ(0-900)
//       [in]ops             :  FISHEPTZOPTS�ṹ��,Ϊ0ʱ��ָ���������ý��㣬Ϊ1��ʾ�Ŵ�2��ʾ��С��3��ʾ�����ƶ���
//                              4��ʾ�����ƶ���5��ʾ�����ƶ���6��ʾ�����ƶ���7��ʾ�Զ�˳ʱ����ת��8��ʾ�Զ���ʱ����ת
//								9��ʾֹͣ��̨������10��ʾ��ȡ��ǰ��̨��������λ��
//       [in]nWinNum         :  Ҫ����eptz�Ĵ��ڱ�ţ����Ͻ�win_numΪ1�������ҵ���
//       [in]nZoomStep       :  �Ŵ���С�Ĳ���, ��Χ1-8
//       [in]nPtStep		 :  ���������ƶ��Ĳ���, ��Χ1-8
//		 [in]nRotateStep	 :  ��ת�Ĳ���, ��Χ1-8
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_OldFisheyeEptzUpdate(LONG nPort, int *pX, int *pY, int *pHAngle, int *pVAngle, FISHEPTZOPTS ops, int nWinNum,
												   int nZoomStep, int nPtStep, int nRotateStep);

/******************************************************************************
*
* ������  : Fisheye_TrancForm_TrackFrame
* ��  ��  : 1ģʽ�£���ivs����֡�еĵ�ǰ֡��Ŀ��켣����ת����ԭʼԲ������
* ��  ��  : - handle: �����㷨ʵ�����
			- ptrackframe: ����֡
			- track_frame_size������֡��С
* ��  ��  : - ptrackframe����ԭʼ����Բ�����װ��ԭ����֡��
* ����ֵ  : DH_FISHEYE_ERROR_NONE: �ɹ���
*           other: ʧ�ܡ�
*******************************************************************************/ 	
PLAYSDK_API BOOL CALLMETHOD PLAY_FisheyeTrancFormTrackFrame(LONG nPort, void *ptrackframe,int track_frame_size);

/******************************************************************************
*
* ������  : Fisheye_TrancForm_coordinate
* ��  ��  : ��������ͼ�����꣬�����ԭʼ����ԲԲ������
* ��  ��  : - param��������������� FishRectify_Info
			- inrpt������㣬8192����ϵ
			  
* ��  ��  : - orpt������㣬8192����ϵ
			v:ת���������
* ����ֵ  : DH_FISHEYE_ERROR_NONE: �ɹ���
*           other: ʧ�ܡ�
*******************************************************************************/ 	
PLAYSDK_API BOOL CALLMETHOD PLAY_FisheyeTrancFormCoordinate(FISHRECTIFY_INFO *param, FISHEYE_POINT2D* inrpt,
	FISHEYE_POINT2D *orpt);
		
/******************************************************************************
*
* ������  : Fisheye_TrancForm_Curve
* ��  ��  : ��������ͼ�����꣬�����ԭʼ����ԲԲ������
* ��  ��  : - param��������������� FishRectify_Info
            - rpt1:����ͼ�ϵ�һ���㣬8192����ϵ
			- rpt2������ͼ�ϵ�һ���㣬8192����ϵ
			- in_num�������ĵ����
* ��  ��  : - in_num����ֵ��ĵ���������������˵�
            - fpts����ֵ��õ��ĵ����У����������˵㣬8192����ϵ
* ����ֵ  : DH_FISHEYE_ERROR_NONE: �ɹ���
*           other: ʧ�ܡ�
*******************************************************************************/ 	
PLAYSDK_API BOOL CALLMETHOD PLAY_FisheyeTrancFormCurve(FISHRECTIFY_INFO *param,
	FISHEYE_POINT2D* rpt1,FISHEYE_POINT2D* rpt2,int *in_num,
	FISHEYE_POINT2D *fpts);

//------------------------------------------------------------------------
// ����: PLAY_StartDeNoise
// ����: ������Ƶȥ���㷨����,��Ҫ����3dnr.dll��
// ����: [in]nPort : ͨ����
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartDeNoise(LONG nPort);

//------------------------------------------------------------------------
// ����: PLAY_SetDeNoiseParams
// ����: ������Ƶȥ�����
// ����: [in]nPort           :  ͨ����
//		 [in]nTemporal		 :  ʱ��ȥ��ǿ�� [0,32]
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDeNoiseParams(LONG nPort, int nTemporal);

//------------------------------------------------------------------------
// ����: PLAY_StopDeNoise
// ����: ֹͣ��Ƶȥ���㷨����
// ����: [in]nPort : ͨ����
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StopDeNoise(LONG nPort);

//------------------------------------------------------------------------
// ����: PLAY_StartDeHaze
// ����: ������Ƶȥ���㷨���ܣ���Ҫ����dehazing.dll��
// ����: [in]nPort : ͨ����
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartDeHaze(LONG nPort);

//------------------------------------------------------------------------
// ����: PLAY_SetDehazeParams
// ����: ������Ƶȥ�����
// ����: [in]nPort           :  ͨ����
//		 [in]ALightValue	 :	�趨�Ĵ�����ǿ��ֵ����Χ0-255
//		 [in]AutoLightOn	 :  Ĭ��Ϊ1,�������Զ�Ѱ�Ҵ�����ǿ��0-�ر��Զ��������ֶ�
//       [in]AutoRun		 :	Ĭ��Ϊ1,����һֱ����ȥ���ܣ�0-�Զ��ж��Ƿ����첢ȥ��
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDehazeParams(LONG nPort, int ALightValue, int AutoLightOn, int AutoRun);

//------------------------------------------------------------------------
// ����: PLAY_STOPDeHaze
// ����: ֹͣ��Ƶȥ���㷨����
// ����: [in]nPort : ͨ����
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StopDeHaze(LONG nPort);

//------------------------------------------------------------------------
// ����: PLAY_StartIVSE
// ����: ������Ƶ��ǿ�㷨���ܣ���Ҫ����IvseDll.dll��
// ����: [in]nPort : ͨ����
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//
// ע�⣺���㷨����ʱ��ϳ��������鴦�������Ƶ
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartIVSE(LONG nPort);

//------------------------------------------------------------------------
// ����: PLAY_SetIVSEParams
// ����: ������Ƶ��ǿ���������Զ�ε��������ʹ�ö���IVSE��Ĺ���
// ����: [in]nPort           :  ͨ����
//		 [in]pIVSEParams	 :	IVSEPARAMS�ṹ�����
//		 [in]bEnable		 :  ��Ӧ��IVSEPARAMS�е�IVSEFUNCTYPE����ѡ�ʹ�ܿ���	
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetIVSEParams(LONG nPort, IVSEPARAMS* pIVSEParams, BOOL bEnable);

//------------------------------------------------------------------------
// ����: PLAY_StopIVSE
// ����: ֹͣ��Ƶ��ǿ�㷨����
// ����: [in]nPort : ͨ����
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StopIVSE(LONG nPort);

//------------------------------------------------------------------------
// ����: PLAY_ConvertToBmpFile
// ����: ͼ���ʽתΪBMP��ʽ.
// ����: pBuf,ͼ������ָ��
//		 nSize,ͼ�����ݴ�С
//		 nWidth,ͼ����
//		 nHeight,ͼ��߶�
//		 nType,��������.T_RGB32,T_UYVY��.
//		 sFileName,Ҫ������ļ���.�����BMP��Ϊ�ļ���չ��.
//       nBmpType, BMP���ͣ�PIC_BMP_32��ʾBMP32�� PIC_BMP_24��ʾBMP24
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ConvertToBmpFileEx(char * pBuf,LONG nSize,LONG nWidth,LONG nHeight,LONG nType, char *sFileName,int nBmpType);

//------------------------------------------------------------------------
// ����: PLAY_EnableLargePicAdjustment
// ����: �Ƿ����ø���ͼ���ڲ��������ԡ��ò�������ʱ���ڿ��4��������ʱ��ֻ����I֡��������ʱ����ÿ֡������
// ����: [in]nPort           :  ͨ����
//		 [in]bEnable		 :  TRUE��ʾ���ô˹��ܣ�FALSE��ʾ�رմ˹���
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_EnableLargePicAdjustment(LONG nPort, BOOL bEnable);

//------------------------------------------------------------------------
// ͬ�����Žӿ�
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// ����: PLAY_OpenPlayGroup
// ����: ��ͬ������
// ����: ��
// ����: ͬ�����ſ��ƾ�����ڵ���ͬ�����ſ��ƽӿ�ʱ��Ҫ����þ��������NULL��ʾʧ��
//------------------------------------------------------------------------
PLAYSDK_API void* CALLMETHOD PLAY_OpenPlayGroup();

//------------------------------------------------------------------------
// ����: PLAY_AddToPlayGroup
// ����: ���һ·�Ѿ���������Ƶ��ͬ��������
// ����: hPlayGroup,ͬ�����ž������PLAY_OpenPlayGroup����
//       nPort,ͨ����
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_AddToPlayGroup(void* hPlayGroup, LONG nPort);

//------------------------------------------------------------------------
// ����: PLAY_DelFromPlayGroup
// ����: ��ͬ�����Ŷ�����ɾ��ָ��ͨ����
// ����: hPlayGroup,ͬ�����ž������PLAY_OpenPlayGroup����
//       nPort,ͨ����
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_DelFromPlayGroup(void* hPlayGroup, LONG nPort);

//------------------------------------------------------------------------
// ����: PLAY_SetPlayGroupDirection
// ����: �ӵ�ǰʱ������Ż򵹷�
// ����: hPlayGroup,ͬ�����ž������PLAY_OpenPlayGroup����
//		 nDirection,���ŷ���0����ǰ��1�����
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayGroupDirection(void* hPlayGroup, int nDirection);

//------------------------------------------------------------------------
// ����: PLAY_SetPlayGroupSpeed
// ����: ���ò����ٶ�
// ����: hPlayGroup,ͬ�����ž������PLAY_OpenPlayGroup����
//		 fCoff,�����ٶ�,��Χ[1/64~64.0],С��1��ʾ���ţ�����1��ʾ����.
//			   �������ٶȽϿ�ʱ���ܻ��֡����.
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayGroupSpeed(void* hPlayGroup, float fSpeed);

//------------------------------------------------------------------------
// ����: PLAY_PausePlayGroup
// ����: ��ͣ�����
// ����: hPlayGroup,ͬ�����ž������PLAY_OpenPlayGroup����
//		 bPause,TRUE��ͣ,FLASE�ָ�
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_PausePlayGroup(void* hPlayGroup, BOOL bPause);

//------------------------------------------------------------------------
// ����: PLAY_StepPlayGroup
// ����: ��֡����
// ����: hPlayGroup,ͬ�����ž������PLAY_OpenPlayGroup����
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StepPlayGroup(void* hPlayGroup);

//------------------------------------------------------------------------
// ����: PLAY_StepPlayGroup
// ����: ���þ���ʱ����ж�λ
// ����: hPlayGroup,ͬ�����ž������PLAY_OpenPlayGroup����
//	     pstDateTime,����ʱ��
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SeekPlayGroup(void* hPlayGroup, DATETIME_INFO* pstDateTime);

//------------------------------------------------------------------------
// ����: PLAY_ClosePlayGroup
// ����: �ر�ͬ�����ſ���
// ����: hPlayGroup,ͬ�����ž������PLAY_OpenPlayGroup����
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ClosePlayGroup(void* hPlayGroup);

//------------------------------------------------------------------------
// ����: PLAY_SetFileDoneTimeCallBack
// ����: �ļ���ʼ������ʱ��ص����������ļ���ʼ�ͽ���ʱ������øûص���
// ����: nPort,ͨ����
//		 fFileTimeDoneCBFun,�ص�����ָ��,����ΪNULL,�������������:
//			nPort,ͨ����
//			nStartTime, �ļ���ʼʱ��.��1970��1��1��0��0��0�������.
//			nEndTime, �ļ�����ʱ��.��1970��1��1��0��0��0�������.
//			pUserData, �û��Զ������
//		 pUserData, �û��Զ������.
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
typedef void (CALLBACK* fFileTimeDoneCBFun)(LONG nPort, DWORD nStarTime, DWORD nEndTime, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileTimeDoneCallBack(LONG nPort, fFileTimeDoneCBFun FileTimeCBFun, void* pUserData);

//------------------------------------------------------------------------
// ����: PLAY_GetKeyFramePosByAbsoluteTime
// ����: ������ʱ�����ָ��λ��֮ǰ�Ĺؼ�֡λ��.
// ����: nPort,ͨ����
//		 t,����ʱ��,���SYSTEMTIME.���õ�������ʱ����.ע����ִ�гɹ����ֵ�洢������I֡��ʱ���
//		 framePos,���ҵ��Ĺؼ�֡���ļ�λ����Ϣ�ṹָ��,���PFRAME_POS.
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
PLAYSDK_API BOOL CALLMETHOD PLAY_GetKeyFramePosByAbsTime(LONG nPort, SYSTEMTIME* t, FRAME_POS* framePos);

//------------------------------------------------------------------------
// ����: PLAY_GetNextKeyFramePosByAbsoluteTime
// ����: ������ʱ�����ָ��λ��֮��Ĺؼ�֡λ��.
// ����: nPort,ͨ����
//		 t,����ʱ��,���SYSTEMTIME.���õ�������ʱ����.ע����ִ�гɹ����ֵ�洢�����ص�I֡��ʱ���
//		 framePos,���ҵ��Ĺؼ�֡���ļ�λ����Ϣ�ṹָ��,���PFRAME_POS.
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
PLAYSDK_API BOOL CALLMETHOD PLAY_GetNextKeyFramePosByAbsTime(LONG nPort, SYSTEMTIME* t, FRAME_POS* framePos);

//------------------------------------------------------------------------
// ����: PLAY_QueryGroupPlayingTime
// ����: ��ѯ��ǰ�������ڲ��ŵ�ʱ��.
// ����: nPort,ͨ����
//		 pDateTime,ʱ��
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
PLAYSDK_API BOOL CALLMETHOD PLAY_QueryGroupPlayingTime(void* hPlayGroup,  DATETIME_INFO *pDateTime);

//------------------------------------------------------------------------
// ����: PLAY_GetAudioChannels
// ����: ��ȡ��Ƶͨ������
// ����: nPort,ͨ����
//       pChannels, ���������[0-255].
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetAudioChannels(LONG nPort, DWORD* pChannels);

//------------------------------------------------------------------------
// ����: PLAY_ChooseAudio
// ����: ѡ����Ƶͨ��
// ����: nPort,ͨ����
//       nChannelID, ��Ƶͨ����0��ʼ.
//       bFlag,TRUE��,FALSE�ر�
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ChooseAudio(LONG nPort, DWORD nChannelID, BOOL bFlag);

//------------------------------------------------------------------------
// ����: PLAY_GetAudioChooseState
// ����: ��ȡ��Ƶͨ���򿪹ر�״̬
// ����: nPort,ͨ����
//       nChannelID, ��Ƶͨ��[0-255].
//       pFlag,TRUE��,FALSE�ر�
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetAudioChooseState(LONG nPort, DWORD nChannelID, BOOL* bFlag);

//------------------------------------------------------------------------
// ����: PLAY_SetPlayedAbsTime
// ����: ������ʱ�����ò���ʱ��
// ����: nPort,ͨ����
//		 pDateTime,����ʱ��
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayedAbsTime(LONG nPort, DATETIME_INFO *pDateTime);

//------------------------------------------------------------------------
// ����: PLAY_SetPlayPosByFileOffset
// ����: ���ļ�ƫ�����ò���λ��
// ����: nPort,ͨ����
//		 nFileOffset,�ļ�ƫ��λ��
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayPosByFileOffset(LONG nPort, UINT nFileOffset);

//------------------------------------------------------------------------
// ����: PLAY_GetCurrentFrameRateEx
// ����: ��õ�ǰ֡�ʣ�С����ʽ��
// ����: nPort,ͨ����
// ����: float,��ǰ֡��
//------------------------------------------------------------------------
PLAYSDK_API float CALLMETHOD PLAY_GetCurrentFrameRateEx(LONG nPort);

//------------------------------------------------------------------------
// ����: PLAY_InitDDraw
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_InitDDraw(HWND hWnd);

//------------------------------------------------------------------------
// ����: PLAY_GetCaps
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API int	CALLMETHOD PLAY_GetCaps();

//------------------------------------------------------------------------
// ����: PLAY_GetFileHeadLength
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetFileHeadLength();

//------------------------------------------------------------------------
// ����: PLAY_RealeseDDraw
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_RealeseDDraw();

//------------------------------------------------------------------------
// ����: PLAY_GetDDrawDeviceTotalNums
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetDDrawDeviceTotalNums();

//------------------------------------------------------------------------
// ����: PLAY_SetDDrawDevice
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDDrawDevice(LONG nPort,DWORD nDeviceNum);

//------------------------------------------------------------------------
// ����: PLAY_GetDDrawDeviceInfo
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetDDrawDeviceInfo(DWORD nDeviceNum,LPSTR  lpDriverDescription,DWORD nDespLen,LPSTR lpDriverName ,DWORD nNameLen,LONG *hhMonitor);

//------------------------------------------------------------------------
// ����: PLAY_GetCapsEx
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API int	CALLMETHOD PLAY_GetCapsEx(DWORD nDDrawDeviceNum);

//------------------------------------------------------------------------
// ����: PLAY_ThrowBFrameNum
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ThrowBFrameNum(LONG nPort,DWORD nNum);

//------------------------------------------------------------------------
// ����: PLAY_InitDDrawDevice
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API BOOL	CALLMETHOD PLAY_InitDDrawDevice();

//------------------------------------------------------------------------
// ����: PLAY_ReleaseDDrawDevice
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API void CALLMETHOD PLAY_ReleaseDDrawDevice();

//------------------------------------------------------------------------
// ����: PLAY_Back
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_Back(LONG nPort);

//------------------------------------------------------------------------
// ����: PLAY_SetDDrawDeviceEx
// ����: �˽ӿ���Ч 
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDDrawDeviceEx(LONG nPort,DWORD nRegionNum,DWORD nDeviceNum);


//------------------------------------------------------------------------
// ����: PLAY_SetOverlayMode
// ����: �˽ӿ���Ч��overlayģʽ�Ѿ���ʱ
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetOverlayMode(LONG nPort,BOOL bOverlay,COLORREF colorKey);


//------------------------------------------------------------------------
// ����: PLAY_GetOverlayMode
// ����: �˽ӿ���Ч��overlayģʽ�Ѿ���ʱ
//------------------------------------------------------------------------
PLAYSDK_API LONG CALLMETHOD PLAY_GetOverlayMode(LONG nPort);

//------------------------------------------------------------------------
// ����: PLAY_GetColorKey
// ����: �˽ӿ���Ч��overlayģʽ�Ѿ���ʱ
//------------------------------------------------------------------------
PLAYSDK_API COLORREF CALLMETHOD PLAY_GetColorKey(LONG nPort);

//------------------------------------------------------------------------
// ����: PLAY_ChangeRate
// ����: ����ӿ�PLAY_SetPlaySpeed
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ChangeRate(LONG nPort, int rate);

//------------------------------------------------------------------------
// ����: PLAY_SetTimerType
// ����: �˽ӿ���Ч
PLAYSDK_API BOOL CALLMETHOD PLAY_SetTimerType(LONG nPort,DWORD nTimerType,DWORD nReserved);

//------------------------------------------------------------------------
// ����: PLAY_GetTimerType
// ����: �˽ӿ���Ч
PLAYSDK_API BOOL CALLMETHOD PLAY_GetTimerType(LONG nPort,DWORD *pTimerType,DWORD *pReserved);

//------------------------------------------------------------------------
// ����: PLAY_SetMDRange
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMDRange(LONG nPort,DISPLAYRECT* rc,DWORD nVauleBegin,DWORD nValueEnd,DWORD nType);

//------------------------------------------------------------------------
// ����: PLAY_SetMDThreShold
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMDThreShold(LONG nPort, DWORD ThreShold);

//------------------------------------------------------------------------
// ����: PLAY_GetMDPosition
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetMDPosition(LONG nPort, DWORD Direction, DWORD nFrame, DWORD* MDValue);


//------------------------------------------------------------------------
// ����: PLAY_CutFileSegment
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
typedef void (CALLBACK *CutProgressFunc)(DWORD nPort, int iProgress, DWORD dwUser);
PLAYSDK_API BOOL CALLMETHOD PLAY_CutFileSegment(LONG nPort, 
												LONG lBeginTime, 
												LONG lEndTime, 
												CutProgressFunc pFunc, 
												char *sOutFilePath, 
												DWORD dwUser);

//------------------------------------------------------------------------
// ����: PLAY_SetVideoPerTimer
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetVideoPerTimer(int iVal);


//------------------------------------------------------------------------
// ����: PLAY_GetVideoPerTimer
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetVideoPerTimer(int* pVal);

//------------------------------------------------------------------------
// ����: PLAY_InputVideoData
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_InputVideoData(LONG nPort,PBYTE pBuf,DWORD nSize);

//------------------------------------------------------------------------
// ����: PLAY_InputAudioData
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_InputAudioData(LONG nPort,PBYTE pBuf,DWORD nSize);

//------------------------------------------------------------------------
// ����: PLAY_SetVerifyCallBack
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
typedef void (CALLBACK * fVerifyCBFun)(LONG nPort, FRAME_POS * pFilePos, DWORD bIsVideo, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetVerifyCallBack(LONG nPort, DWORD nBeginTime, DWORD nEndTime, fVerifyCBFun VerifyFun, void* pUserData);


//------------------------------------------------------------------------
// ����: PLAY_SetSourceBufCallBack
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
typedef void (CALLBACK * fSourceBufCBFun)(LONG nPort,DWORD nBufSize, void* pUserData,void*pResvered);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetSourceBufCallBack(LONG nPort,
													  DWORD nThreShold,
													  fSourceBufCBFun SourceBufCBFun,
													  void* pUserData,
													  void *pReserved);

//------------------------------------------------------------------------
// ����: PLAY_ResetSourceBufFlag
// ����: �˽ӿ���Ч
//------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ResetSourceBufFlag(LONG nPort);

//------------------------------------------------------------------------
// ����: PLAY_SetPandoraWaterMarkCallBack
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPandoraWaterMarkCallBack(LONG nPort, GetWaterMarkInfoCallbackFunc pFunc, void* pUserData);

//------------------------------------------------------------------------
// ����: PLAY_SetDisplayBuf
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayBuf(LONG nPort,DWORD nNum);

//------------------------------------------------------------------------
// ����: PLAY_GetDisplayBuf
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetDisplayBuf(LONG nPort);

//------------------------------------------------------------------------
// ����: PLAY_SetDisplayType
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayType(LONG nPort,LONG nType);

//------------------------------------------------------------------------
// ����: PLAY_GetDisplayType
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API LONG CALLMETHOD PLAY_GetDisplayType(LONG nPort);

//------------------------------------------------------------------------
// ����: PLAY_RefreshPlayEx
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_RefreshPlayEx(LONG nPort,DWORD nRegionNum);

//------------------------------------------------------------------------
// ����: PLAY_OpenStreamEx
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_OpenStreamEx(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize);

//------------------------------------------------------------------------
// ����: PLAY_CloseStreamEx
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_CloseStreamEx(LONG nPort);

//------------------------------------------------------------------------
// ����: PLAY_AdjustFluency
// ����: �˽ӿ���Ч
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_AdjustFluency(LONG nPort, int level);

//------------------------------------------------------------------------
// ����: PLAY_SurfaceChange
// ����: Android�汾ר�ã�Surface������仯֪ͨ
// ����: 
// ����: 
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SurfaceChange(LONG nPort, HWND hWnd);

//------------------------------------------------------------------------
// ����: PLAYER_SetFileInfoFrameCallback
// ����: �����ļ���Ϣ֡�ص�����
// ����: 
// ����: 
//------------------------------------------------------------------------
typedef int (CALLBACK* fOnFileInfoFrame)(LONG nPort, FILE_INFO_IMAGE* pFileInfoImage, FILE_INFO_FRAME* pFileInfoFrame, void* pUserParam);
PLAYSDK_API BOOL CALLMETHOD	PLAY_SetFileInfoFrameCallback(LONG nPort, fOnFileInfoFrame fFileInfoFrame, tPicFormats imageType, void* pUserParam);

//------------------------------------------------------------------------
// ����: PLAYER_SetAnalyzePositionCallback
// ����: �����ļ���Ϣ֡�������Ȼص�����
// ����: 
// ����: 
//------------------------------------------------------------------------
typedef int (CALLBACK *fOnAnalyzePosition)(LONG nPort, DATETIME_INFO* pstDateTime, void* pUserParam);
PLAYSDK_API BOOL CALLMETHOD	PLAY_SetAnalyzePositionCallback(LONG nPort, fOnAnalyzePosition fAnalyzePosition, void* pUserParam);

//------------------------------------------------------------------------
// ����: PLAYER_StartFileFrameDetect
// ����: ��Ҫ�������������֮�󣬿�ʼ�ļ���Ϣ֡��⣬������������
// ����: 
// ����: 
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD	PLAY_StartFileFrameDetect(LONG nPort, FILE_INFO_FRAME_SEARCH* pFileInfoFrameSearch);

//------------------------------------------------------------------------
// ����: PLAYER_StopFileFrameDetect
// ����: ��ֹ����
// ����: 
// ����: 
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD	PLAY_StopFileFrameDetect(LONG nPort);

//------------------------------------------------------------------------
// ����: PLAY_StartEdgeEnhance
// ����: ����ͼ���񻯴���
// ����: level	   -- ����ȼ�,0-�ر�,6-��ǿ,Ĭ�ϵȼ�4
//		 algMode   -- �㷨ģʽ,Ԥ���ӿ�,Ŀǰֻ֧��0
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartEdgeEnhance(LONG nPort, int level, int algMode);

//------------------------------------------------------------------------
// ����: PLAY_StopEdgeEnhance
// ����: �ر�ͼ���񻯴���
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StopEdgeEnhance(LONG nPort);

//------------------------------------------------------------------------
// ����: PLAY_StartVideoStable
// ����: ������Ƶ����
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartVideoStable(LONG nPort);

//------------------------------------------------------------------------
// ����: PLAY_StopEdgeEnhance
// ����: �ر���Ƶ����
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StopVideoStable(LONG nPort);

//------------------------------------------------------------------------
// ����: PLAY_SetDisplayScale
// ����: ������ʾ������С��IOSר���Ա����䲻ͬ�Ļ���.
// ����: nPort,ͨ����
//		 fScale����ʾ������Ĭ��Ϊ1.0
//		 nRegionNum,��ʾ�������,0~(MAX_DISPLAY_WND-1),���Ϊ0,�����õ�������ʾ����������.
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayScale(LONG nPort, float fScale, DWORD nRegionNum);

//------------------------------------------------------------------------
// ����: PLAY_Scale
// ����: �ֻ��汾ͼ������
// ����: nPort  �˿ں�
//       scale	���ű���[1.0, 8.0]
//       nRegionNum,��ʾ�������, ������
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_Scale(LONG nPort, float scale, DWORD nRegionNum);

//------------------------------------------------------------------------
// ����: PLAY_Translate
// ����: �ֻ��汾ͼ��ƽ��
// ����: nPort  �˿ں�
//       x	xƽ�����꣬����ֵ
//	     y	yƽ�����꣬����ֵ
//       nRegionNum,��ʾ�������, ������
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_Translate(LONG nPort, float x, float y, DWORD nRegionNum);

//------------------------------------------------------------------------
// ����: PLAY_SetIdentity
// ����: �ֻ��汾ͼ���һ��������ƽ�ƣ����Ų�����
// ����: nPort  �˿ں�
//       nRegionNum,��ʾ�������, ������
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetIdentity(LONG nPort, DWORD nRegionNum);

//------------------------------------------------------------------------
// ����: PLAY_GetScale
// ����: �ֻ��汾��ȡ��ǰ����ֵ��
// ����: nPort  �˿ں�
//       nRegionNum,��ʾ�������, ������
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
PLAYSDK_API float CALLMETHOD PLAY_GetScale(LONG nPort, DWORD nRegionNum);

//------------------------------------------------------------------------
// ����: PLAY_GetTranslateX
// ����: �ֻ��汾��ȡ��ǰx��ƽ�����ꡣ
// ����: nPort  �˿ں�
//       nRegionNum,��ʾ�������, ������
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
PLAYSDK_API float CALLMETHOD PLAY_GetTranslateX(LONG nPort, DWORD nRegionNum);

//------------------------------------------------------------------------
// ����: PLAY_GetTranslateX
// ����: �ֻ��汾��ȡ��ǰy��ƽ�����ꡣ
// ����: nPort  �˿ں�
//       nRegionNum,��ʾ�������, ������
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
PLAYSDK_API float CALLMETHOD PLAY_GetTranslateY(LONG nPort, DWORD nRegionNum);

//------------------------------------------------------------------------
// ����: PLAY_CleanScreen, PLAY_Stopǰ������Ч
// ����: nRegionNum Ĭ����0
// ����: �ֻ��汾��������
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_CleanScreen(LONG nPort, float red, float green, float blue, float alpha, DWORD nRegionNum);

//------------------------------------------------------------------------
// ����: PLAY_ViewResolutionChanged
// ����: Android�汾,SurfaceView��С�仯ʱ����
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ViewResolutionChanged(LONG nPort, int nWidth, int nHeight, DWORD nRegionNum);

//------------------------------------------------------------------------
// ����: PLAY_StartDataRecordEx
// ����: ��ʼ������¼��,ֻ����ģʽ����,��PLAY_Play֮�����.
// ����: nPort,ͨ����
//		 sFileName,¼���ļ���,����ļ������в����ڵ��ļ���,�ʹ������ļ���.
//		 idataType,0��ʾԭʼ��Ƶ��;1��ʾת����AVI��ʽ;2��ʾת����ASF��ʽ;3�ֶα����ļ�
//		 fListenter, �ص���������������д�����з�������.
// ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
//------------------------------------------------------------------------
typedef void (CALLBACK* fRecordErrorOccur)(LONG nPort, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_StartDataRecordEx(LONG nPort, char *sFileName, int idataType, fRecordErrorOccur fListenter, void* pUserData);

//------------------------------------------------------------------------
// ����: PLAY_SetMultiFrameDecCallBack
// ����: ����������Ϣ�ص������SVAC�����е�Щ�����Ϣ��
// ����: nPort  �˿ں�
//       nRegionNum,��ʾ�������, ������
//		 DecInfoCallBack, �ص�����
//		 pUser, �û��ص�����
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
typedef void (CALLBACK* fMultiFrameDecCallBack)(LONG nPort, LONG nStreamID, char* pData, LONG nLen, 
										  FRAME_INFO* stFrameInfo, void* pUserData, LONG nReserved1);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMultiFrameDecCallBack(LONG nPort, fMultiFrameDecCallBack DecInfoCallBack, void* pUser);

//------------------------------------------------------------------------
// ����: PLAY_SetMultiFrameCallBack
// ����: ������֡��Ϣ�ص���Ŀǰ��Ҫ���SVAC���룬
//       SVC�����У�һ�����ݴ��л��������ǿ����������
// ����: nPort  �˿ں�
//       MultiFrameCallBack, �ص�������
//       pUser  �û�����
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
typedef void (CALLBACK* fMultiFrameCallBack)(LONG nPort, LONG nStreamID, void* pUserData, LONG nReserved);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMultiFrameCallBack(LONG nPort, fMultiFrameCallBack MultiFrameCallBack, void* pUser);

//------------------------------------------------------------------------
// ����: PLAY_SetDecInfoCallBack
// ����: ������֡��Ϣ�ص������SVAC����
// ����: nPort  �˿ں�
//       nFrameID, ѡ����в��ŵ�֡
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
typedef void (CALLBACK* fDecInfoCallBack)(LONG nPort, FRAME_DEC_EXT_INFO* pDecInfo, void* pUserData, LONG nReserved);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecInfoCallBack(LONG nPort, fDecInfoCallBack DecInfoCallBack, void* pUserData);

//------------------------------------------------------------------------
// ����: PLAY_ChooseFrame
// ����: ѡ����ʾSVAC����SVC�Ļ��������ǿ��
// ����: nPort  �˿ں�
//       nFrameID, Ҫ��ʾ�Ĳ�(0: �����㣬1: ��ǿ��)
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ChooseFrame(LONG nPort, LONG nFrameID);

//------------------------------------------------------------------------
// ����: PLAY_RenderPrivateData
// ����: ��ʾ˽�����ݣ��������򣬹���򱨾����ƶ�����
// ����: nPort  �˿ں�
//       bTrue TRUE:�� FALSE:�ر�
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_RenderPrivateData(LONG nPort, BOOL bTrue, LONG nReserve);

//------------------------------------------------------------------------
// ����: PLAY_SetFileIndexProgressCallBack
// ����: ���������������Ȼص�
// ����: nPort  �˿ں�
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
typedef void (CALLBACK* fIndexProgressCB)(LONG nPort, float fProgress, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileIndexProgressCallBack(LONG nPort, fIndexProgressCB IndexProgressCB, void* pUser);

//------------------------------------------------------------------------
// ����: PLAY_GetLastYUVFrame
// ����: ������ȡ��һ֡��Ӧ��YUV����
// ����: nPort  �˿ں�
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetLastYUVFrame(LONG nPort, FRAME_DECODE_INFO* pFrameDecodeInfo);

//IOS����Ҫ���ڴ��С�汾
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMemMinimized(LONG nPort);

PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecodeThreadNum(LONG nPort, DWORD nNum);

//���ý�����Կ��SVAC����ʹ��
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecodeKey(LONG nPort, const unsigned char *key, unsigned int key_len);

PLAYSDK_API BOOL CALLMETHOD PLAY_GetIRefValue(LONG nPort, BYTE *pBuffer, DWORD *pSize);

#ifdef __native_client__

#define FISHEYE_REGION 16
//------------------------------------------------------------------------
// ����: PLAY_OutsideRender
// ����: nacl ui�̵߳��ô˽ӿ�
// ����: nPort  �˿ں�
// ����: nWidth  ���ڿ�
// ����: nHeight  ���ڸ�
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_OutsideRender(LONG nPort, int nX, int nY, int nWidth, int nHeight, unsigned int nRegionNum = 0);

namespace pp
{
	class Instance;
}
//------------------------------------------------------------------------
// ����: PLAY_SetNACLInstance
// ����: nacl ���̵߳��ô˽ӿ����þ����ַ
// ����: pInstance  ����pp::instance��ַ
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetNACLInstance(pp::Instance * pInstance);
#endif

typedef void (CALLBACK* fDoubleVisibleDecCBFun)(LONG nPort,char * pBuf, int nSize, int nWidth, int nHeight, 
												char* pSecondBuf, int nSecondSize, int nSecondWidth, int nSecondHeight, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDoubleVisibleDecCallBack(LONG nPort, fDoubleVisibleDecCBFun DataCBFun, void* pUserData);

//------------------------------------------------------------------------
// ����: PLAY_EnableAudioChannel
// ����: ��������������Ƶ���ţ���������������Ƶ��Ч��
// ����: nPort  �˿ں�
// ����: nChnNum  ����ͨ����0-��ͨ����1-��ͨ��
// ����: bEnable  ʹ�� TRUE-���ã� FALSE-����
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_EnableAudioChannel(LONG nPort, DWORD nChnNum, BOOL bEnable);

//------------------------------------------------------------------------
// ����: PLAY_SplitProc
// ����: yuv ƴ���㷨������4k��������ʾ
// ����: nPort  �˿ں�
// ����: nMode ģʽ��0��Ӧ����ģʽ��1��Ӧ1+3ģʽ��2��Ӧ1+5ģʽ, 3��Ӧ1+1ģʽ�����ӷŴ�
//					 4��Ӧ1P+3, 5��Ӧ1P+6
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SplitProc(LONG nPort, int nMode);

//------------------------------------------------------------------------
// ����: PLAY_SplitProcUpdate
// ����: yuv ƴ���㷨��������Ҫ�Ŵ�ľ���λ��
// ����: nPort  �˿ں�
// ����: pAreaRect ���������������ʼ��ַ
//       ���nMode��0����ӦΪNULL
//       ���nMode��1���������Ĵ�СӦΪ3
//       ���nMode��2���������Ĵ�СӦΪ5              | 
// ����: TRUE �ɹ� FALSE ʧ��
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SplitProcUpdate(LONG nPort, DISPLAYRECT* pAreaRect);

/************************************************************************/
/* ����: PLAY_SetRenderMode
   ����: ָ����Ⱦģʽ(Windowsƽ̨), PLAY_Play֮ǰ������Ч
   ����: nPort,ͨ����
	     nMode, ��Ⱦģʽ
   ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.                                                                     */
/************************************************************************/
PLAYSDK_API BOOL CALLMETHOD PLAY_SetRenderMode(LONG nPort, RenderType nMode);

/************************************************************************/
/* ����: PLAY_InitThirdPartyLibrary
   ����: ��ʼ�����������ܿ�
   ����: nPort,ͨ����
   ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
*/
/************************************************************************/
PLAYSDK_API BOOL CALLMETHOD PLAY_InitThirdPartyLibrary(LONG nPort, const char* kmcSvrIP,int kmcSvrPort,const char* macAddr);

/************************************************************************/
/* ����: PLAY_SetDecodeStrategy
   ����: ���ý������,������������������
   ����: nPort,ͨ����
   ����: 16:��ʾ����������frame����������ǰ����
		 8: ��ʾ�����������������ݲ�����Э�鵱�ɽ������
		 0: ��ʾ�����������������ݲ�����Э��������룬���������Ứ��
   ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
*/
/************************************************************************/
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecodeStrategy(LONG nPort, int nStrategyType);

/************************************************************************/
/* ����: PLAY_SetAVSyncType
   ����: ��������Ƶ���Ų���
   ����: nPort,ͨ����
         nAVSyncType,�������Ż�׼������nAVSyncType=0������ƵΪ��׼��nAVSyncType=1������ƵΪ��׼
   ����: BOOL,�ɹ�����TRUE,ʧ�ܷ���FALSE.
*/
/************************************************************************/
typedef enum
{
	AV_SYNC_VIDEO_MASTER,	//����ƵΪ��׼
	AV_SYNC_TIME_STAMP      //��ʱ���Ϊ��׼
}AV_SYNC_TYPE;
PLAYSDK_API BOOL CALLMETHOD PLAY_SetAVSyncType(LONG nPort,AV_SYNC_TYPE nAVSyncType);

/************************************************************************/
/* nMode����ȡ-1,0,1,2,3,4
-1��������������
 0���������ĳ̶���ͣ������������źŵ�����С
 4���������ĳ̶����,�����������źŵ������
 */
/************************************************************************/
PLAYSDK_API BOOL CALLMETHOD PLAY_SetSEnhanceMode(LONG nPort,int nMode);


/************************************************************************/
/* ������������չ�ӿ�, ֧�������ʵ��                   
 */
/************************************************************************/
enum ThirdDecryptType
{
	DECRYPT_KTJM = 4, /*�������*/
	DECRYPT_SYJM,	  /*��Ԫ����*/
	DECRYPT_HZSD,     /*��ʦ���㷨*/
	DECRYPT_ZBQL,     /*�б������㷨*/
};
typedef struct 
{ 
	ThirdDecryptType type; /*��������������*/
	BOOL (*Init)();		   /*��ʼ���ӿ�,ȫ�ֳ�ʼ��һ��*/
	BOOL (*DeInit)();	   /*����ʼ���ӿ�*/
	void* (*Open)();	   /*�򿪽���ͨ��, ����ֵ����Ϊ��!*/
	BOOL (*Decrypt)(void* handle, 
					unsigned char* inData,  unsigned int inLen, 
					unsigned char* outData, unsigned int& outLen);/*����, �Է���ֵ��Ҫ��(1�ɹ�0ʧ��)*/
	BOOL (*Close)(void* handle); /*�رս���ͨ��*/
}ThirdDecryptHook;
PLAYSDK_API BOOL CALLMETHOD PLAY_Register3rdDecryptHook(ThirdDecryptHook* decryptHook);

#ifdef	__cplusplus
}
#endif

#endif
