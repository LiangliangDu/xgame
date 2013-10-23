/*******************************************************************
** �ļ���:	SenderThread.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/30/2008
** ��  ��:	1.0
** ��  ��:	ר�����ڷ������ݵ��߳�
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __SENDER_THREAD_H__
#define __SENDER_THREAD_H__

#include "AsynIoFrame.h"
#include "Handle.h"
#include "Thread.h"
#include "LockFree.h"
#include "singleton.h"
using namespace xs;

#include <list>
#include <vector>
#include <map>


namespace xs{
	/**
	@name : �����߳�
	@brief: ר�����ڷ������ݵ��߳�,��Ҫ��;������
			1.�����û��̷߳������ݴ�����ѹ��
			2.��һ�������Ⱥ��͵Ķ����������������IO�豸
	*/
	class SenderThread : public IRunnable,public SingletonEx<SenderThread>
	{
	public :
		SenderThread()
		{
			lSendQueueDeth = 0;
		}
	protected:
		struct Send_Request
		{
			//crr mod,����ľ����װ,������һ�٣���������̰߳�ȫ������ʹ��
			//handle         hSecurity;  // ͨ���þ���ж�device�Ƿ��ͷ�
			AsynIoDevice * pSender;  
			AsynIoHandler* pHandler;
			AsynIoBuffer   Buffer;
		};

		volatile LONG lSendQueueDeth; //crr add��ǰ���뷢�Ͷ��е���Ϣ��
		typedef LockFreeQueue<Send_Request>  SEND_LIST;
		SEND_LIST                  m_SendList;

		//�ڳ�Ա�����ж���map�ṹ��Щ����汾����������Ƶ��࿪ͷ
		typedef std::vector<AsynIoBuffer>	            BUFFER_ARRAY;

		struct  REQUEST_DATA
		{
			BUFFER_ARRAY  m_BufferArray;
			Send_Request  m_RequestInfo;
		};

		typedef std::map<AsynIoDevice*,REQUEST_DATA>	REQUEST_MAP;

	public:
		/**
		@name         : ������һ������
 		@brief        :
		@param pSocket: �������ݵ��豸
		@param pHandler:���ͽ���Ĵ���ӿ�
		@param hSecurity:ͨ���þ���ж�device�Ƿ��ͷ�
		@param pBuff  : Ҫ���͵�����
		@return       :
		*/
		//crr mod,����ľ����װ,������һ�٣���������̰߳�ȫ������ʹ��
		//void  RequestSendData(AsynIoDevice * pSocket,AsynIoHandler * pHandler,handle hSecurity,AsynIoBuffer & pBuff)
		void  RequestSendData(AsynIoDevice * pSocket,AsynIoHandler * pHandler,AsynIoBuffer & pBuff)
		{
			Send_Request request;
			//request.hSecurity = hSecurity;
			request.pSender   = pSocket;
			request.pHandler  = pHandler;
			request.Buffer    = pBuff;
			if(!((AsynStreamSocket*)pSocket)->IncreaseSendRef())
			{
				return;
			}

			//crr�������Ϊ100Mbit/s = 12500KByte/s	//��¼����ɫ��Ϣ����p����Ϣƽ��ÿ����Ϣ>50Byte
			//���ۻ�100ms���͵���Ϣ����Ϊ25k
			//Ϊ�˱��ⷢ�Ͳ�������ǿ�������뷢�͵�Դ�߳�˯��һ��
			if (lSendQueueDeth >= 10000)
			{
				ErrorOnce("=============��������Ϣ�ۻ�����..lSendQueueDeth=" << lSendQueueDeth << "\r\n");
				//Sleep(1);
			}

			InterlockedIncrement(&lSendQueueDeth);
			m_SendList.Add(request);
		}

		virtual void run()
		{
			SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
			while(1)
			{
				// ����һ�־���Ϣһ��,�ѿ���Ȩ���������߳�
				if (0 == lSendQueueDeth)
				{
					Sleep(1);
				}
				
				REQUEST_MAP										m_RequestMap; // ÿ���豸Ҫ���͵���������,����������������

				Send_Request request;

				// ȡ����������,������������
				int iPopOutSize =0;
				while (m_SendList.Get(request))
				{
					InterlockedDecrement(&lSendQueueDeth);
					REQUEST_MAP::iterator it = m_RequestMap.find(request.pSender);
					if ( it==m_RequestMap.end() )
					{
						m_RequestMap[request.pSender].m_BufferArray.push_back(request.Buffer);
						m_RequestMap[request.pSender].m_RequestInfo = request;
					}else
					{
						// �п��ܴ����಻ͬ,���ر�ע��
						REQUEST_DATA & request_data = it->second;
						if ( request_data.m_RequestInfo.pHandler != request.pHandler )
						{
							BatchSend(request_data.m_RequestInfo,request_data.m_BufferArray);
							request_data.m_RequestInfo.pHandler = request.pHandler;
							request_data.m_BufferArray.clear();
						}
						request_data.m_BufferArray.push_back(request.Buffer);
					}

					iPopOutSize++;
					if (iPopOutSize >= 2)
					{
						break;
					}
					
				}

				REQUEST_MAP::iterator it = m_RequestMap.begin();
				for ( ;it!=m_RequestMap.end();++it )
				{
					REQUEST_DATA & requestData = it->second;
					Send_Request & request     = requestData.m_RequestInfo;

					BatchSend(request,requestData.m_BufferArray);
				}
			}
		}

		void BatchSend(Send_Request & request,std::vector<AsynIoBuffer> & BufferArray)
		{
			//crr mod, ����ľ����װ,������һ�٣���������̰߳�ȫ������ʹ��
// 			if ( !isValidHandle(request.hSecurity))
// 			{
// 				return;
// 			}

			// ������������
			bool bRetSuccess = true;
			for ( size_t i=0;i<BufferArray.size();i+=MAX_ASYN_IO_BUFF_COUNT)
			{
				DWORD count = min(MAX_ASYN_IO_BUFF_COUNT,BufferArray.size()-i);

				//����ʧ��
				if(bRetSuccess)
				{
					bRetSuccess = request.pSender->Writer()->writeEx(&BufferArray[i],count,request.pHandler);
				}

				((AsynStreamSocket*)request.pSender)->DecreaseSendRef(count);
			}		
		}

		virtual void release(){	delete this;}
	};
}

#endif//__SENDER_THREAD_H__