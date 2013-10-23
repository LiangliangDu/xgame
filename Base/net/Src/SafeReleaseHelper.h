/*******************************************************************
** �ļ���:	SafeReleaseHelper.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	02/29/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __SAFE_RELEASE_HELPER_H__
#define __SAFE_RELEASE_HELPER_H__

#include "singleton.h"
#include "AsynIoDevice.h"
#include "AsynIoResult.h"
#include "AsynIoFrame.h"
#include "Proactor.h"
#include "net.h"

namespace xs
{
	/**
	@name :
	@brief: closesocket���ú���ɶ˿ڻὫ����pending״̬������첽io��������
	�������ڴ�������¼��Ĺ����̲߳�һ���͵���Close���߳���ͬһ��
	�������ﲻ��ֱ��delete pending״̬�Ľ������,��ѡ��������
	1.Postһ����Ϣ�������߳�,�ù����߳�ȥRelease AsynIODevice
	2.��result����������һ����־,�ӳٵ��ò������ʱdelete��,��ȻҪȷ����Ҫ�����ڴ�й¶
	ʹ�õ�һ�ַ�����Ϊ����.

	���������þ���Post��Ϣ����ɶ˿�,��ɺ�deleteָ��Device
	@warning: 
	         ���������ƺ����������⣬������...
	         CHEN.TAO 2008.3.5 
	*/
	class SafeReleaseHelper : public AsynIoHandler,public Singleton<SafeReleaseHelper>
	{
	public:
		virtual void HandleIoComplete( AsynIoResult * result )
		{
			AsynIoDevice * pDevice = result->GetAsynDevice();
			assert(pDevice);

			AsynIoType type = result->GetType();
			pDevice->DeleteAsynIoResult(result);

			if ( type==ASYN_IO_CLOSE )
			{
				pDevice->Release();
			}
		}

		void ReleaseAsynIoDevice(AsynIoDevice * pDevice)
		{
			AsynIoResult * result = pDevice->CreateAsynIoResult(ASYN_IO_CLOSE,this);
			GetAsynIoProactor()->PostCompletion(result);
		}

		virtual ~SafeReleaseHelper()
		{
			// �����ͷ�һ��ͨѶ��
			UninitializeNetwork();
		}
	};
}

#endif//__SAFE_RELEASE_HELPER_H__