//// Ptz.cpp: implementation of the CPtz class.
////
////////////////////////////////////////////////////////////////////////

//#include "Ptz.h"


////////////////////////////////////////////////////////////////////////
//// Construction/Destruction
////////////////////////////////////////////////////////////////////////

//CPtz::CPtz()
//{

//}

//CPtz::~CPtz()
//{

//}

//bool CPtz::SetPtzParam(LLONG lLoginID, int nChannel)
//{
//    if(lLoginID <=0 || nChannel < 0 )
//    {
//        return false;
//    }

//    m_lLoginID = lLoginID;
//    m_nChannel = nChannel;

//    return true;
//}

//bool CPtz::SetLoginID(LLONG lLoginID)
//{
//    if(lLoginID <= 0)
//    {
//        return false;
//    }
//    m_lLoginID = lLoginID;
//    return true;
//}

//bool CPtz::SetChannel(int nChannel)
//{
//    if( nChannel < 0)
//    {
//        return false;
//    }
//    m_nChannel = nChannel;
//    return true;
//}

///*************************************************************************************************/

//#include<iostream>
//using namespace std;
//bool CPtz::PtzControl(int nType, int nParam1, int nParam2, int nParam3, bool bStop /* = false */)
//{
//    //cout<<nType<<"'"<<m_lLoginID<<","<<m_nChannel<<","<<nParam1<<","<<nParam2<<","<<nParam3<<","<<bStop<<endl;
//    if(m_lLoginID <=0 || m_nChannel < 0 )
//    {
//        return false;
//    }

//    return CLIENT_DHPTZControlEx(m_lLoginID, m_nChannel, nType, nParam1, nParam2, nParam3, bStop);
//}

//bool CPtz::PtzMenuControl(int nType)
//{
//    switch(nType)
//    {
//    case DH_EXTPTZ_MENUUP://��
//    case DH_EXTPTZ_MENUDOWN://��
//    case DH_EXTPTZ_MENULEFT://��
//    case DH_EXTPTZ_MENURIGHT://��
//    case DH_EXTPTZ_OPENMENU://���������˵�
//    case DH_EXTPTZ_CLOSEMENU://�رղ˵�
//    case DH_EXTPTZ_MENUOK://�˵�ȷ��
//    case DH_EXTPTZ_MENUCANCEL://�˵�ȡ��
//        {
//            return PtzControl(nType, 0, 0, 0);
//        }
//        break;
//    default:
//        return false;
//    }

//}

//bool CPtz::PtzAuxi(int nType, int nAuxi)
//{
//    switch(nType)
//    {
//    case DH_EXTPTZ_AUXIOPEN://��
//    case DH_EXTPTZ_AUXICLOSE://��
//        {
//            return PtzControl(nType, nAuxi, 0, 0);
//        }
//        break;
//    default:
//        return false;
//    }

//}

//bool CPtz::PtzBasicControl(int nType, int nStep, bool bStop /* = false */)
//{
//    switch(nType)
//    {
//    case DH_PTZ_UP_CONTROL:	//��
//    case DH_PTZ_DOWN_CONTROL://��
//    case DH_PTZ_LEFT_CONTROL://��
//    case DH_PTZ_RIGHT_CONTROL://��
//    case DH_PTZ_ZOOM_DEC_CONTROL://��ͷ��
//    case DH_PTZ_ZOOM_ADD_CONTROL://��ͷ��
//    case DH_PTZ_FOCUS_DEC_CONTROL://������
//    case DH_PTZ_FOCUS_ADD_CONTROL://����Զ
//    case DH_PTZ_APERTURE_DEC_CONTROL://��ȦС
//    case DH_PTZ_APERTURE_ADD_CONTROL://��Ȧ��
//        {
//            return PtzControl(nType, 0, nStep, 0, bStop);
//        }
//        break;
//    case DH_EXTPTZ_LEFTTOP:	//����
//    case DH_EXTPTZ_LEFTDOWN://����
//    case DH_EXTPTZ_RIGHTTOP: //����
//    case DH_EXTPTZ_RIGHTDOWN://����
//        {
//            return PtzControl(nType, nStep, nStep, 0, bStop);
//        }
//        break;
//    default:
//        return false;
//    }
//}

//bool CPtz::PtzFastGo(int nX, int nY, int nZoom)
//{
//    return PtzControl(DH_EXTPTZ_FASTGOTO, nX, nY, nZoom, false);
//}

//bool CPtz::PtzLineScan(int nType)
//{
//    switch(nType)
//    {
//    case DH_EXTPTZ_SETLEFTBORDER:		//�������߽�
//    case DH_EXTPTZ_SETRIGHTBORDER:		//�����ұ߽�
//    case DH_EXTPTZ_STARTLINESCAN:		//��ʼ��ɨ
//    case DH_EXTPTZ_CLOSELINESCAN:		//ֹͣ��ɨ
//        {
//            return PtzControl(nType, 0, 0, 0);
//        }
//        break;
//    default:
//        return false;
//    }
//}

//bool CPtz::PtzLoop(int nType, int nGroup, int nPresetData, bool bBeginLoop /* = false */)
//{
//    switch(nType)
//    {
//        case DH_PTZ_POINT_LOOP_CONTROL://��ʼѲ��,ֹͣѲ��
//            {
//                if (bBeginLoop)
//                {
//                    return PtzControl(nType, nGroup, 0, 76);//��ʼ
//                }
//                else
//                {
//                    return PtzControl(nType, nGroup, 0, 96);//ֹͣ
//                }
//            }
//            break;
//        case DH_EXTPTZ_ADDTOLOOP://����Ѳ����
//        case DH_EXTPTZ_DELFROMLOOP://ɾ��Ѳ����
//            {
//                return PtzControl(nType, nGroup, nPresetData, 0);
//            }
//            break;
//        case DH_EXTPTZ_CLOSELOOP://ɾ��Ѳ����
//            {
//                return PtzControl(nType, nGroup, 0, 0);
//            }
//            break;
//        default:
//            return false;
//    }
//}

//bool CPtz::PtzPreset(int nType, int nPresetData)
//{
//    switch(nType)
//    {
//    case DH_PTZ_POINT_MOVE_CONTROL://ת��Ԥ�õ�
//    case DH_PTZ_POINT_SET_CONTROL://����
//    case DH_PTZ_POINT_DEL_CONTROL://ɾ��
//        {
//            return PtzControl(nType, 0, nPresetData, 0);
//        }
//        break;
//    default:
//        return false;
//    }
//}

//bool CPtz::PtzRotate(int nType)
//{
//    switch(nType)
//    {
//    case DH_EXTPTZ_STARTPANCRUISE:		//��ʼˮƽ��ת
//    case DH_EXTPTZ_STOPPANCRUISE:		//ֹͣˮƽ��ת
//        {
//            return PtzControl(nType, 0, 0, 0);
//        }
//    default:
//        return false;
//    }
//}

//bool CPtz::PtzMode(int nType, int nGroup)
//{
//    switch(nType)
//    {
//    case DH_EXTPTZ_SETMODESTART://��ʼ��¼
//    case DH_EXTPTZ_SETMODESTOP:	//ֹͣ��¼
//    case DH_EXTPTZ_RUNMODE:	//��ʼѲ��
//    case DH_EXTPTZ_STOPMODE://ֹͣѲ��
//    case DH_EXTPTZ_DELETEMODE://ɾ��Ѳ��
//        {
//            return PtzControl(nType, nGroup, 0, 0);
//        }
//        break;
//    default:
//        return false;
//    }
//}

