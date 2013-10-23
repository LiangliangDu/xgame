/*******************************************************************
** �ļ���:	CallbackDispatcher.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/26/2008
** ��  ��:	1.0
** ��  ��:	�ص��ַ���
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __CALLBACK_DISPATCHER_H__
#define __CALLBACK_DISPATCHER_H__

#include "singleton.h"
#include "LockFree.h"
#include "AsynIoFrame.h"
#include "Connection.h"
#include "UDPSocket.h"
#include "Handle.h"
#include "Thread.h"
#include "LockFree.h"

namespace xs{

	/**
	@name : �ص��ַ���
	@brief: ���ڴ��ڶ�������߳����в�ѯ��ɶ˿ڣ�������ɲ��������ڶ���̴߳���
			��Ӧ�ò�ͨ��ֻ��һ���߼��߳���Ϊ�˱���Ӧ�ò��д�߳�ͬ�����룬�����
			�ڲ�ͬ�߳���ɵ��¼�ͳһת���û����߼��߳����ص�
	*/
	class CallbackDispatcher : public SingletonEx<CallbackDispatcher>
	{
	public:
		/// �ص�����
		struct CallbackObject : public IRunnable
		{
			virtual void run() = 0;
			virtual void release() = 0;
		};

		// ����һ�λص�
		void RequestCallback(CallbackObject * context)
		{
			m_ResultList.Add(context);
			SetEvent(m_hEventHandle);
		}

		// �û��߳������ȡ�ص��ڴ�
		void DispatchCallback()
		{
			CallbackObject * pCall = 0;
			while(m_ResultList.Get(pCall))
			{
				if ( pCall==0 )
				{
					break;
				}

				pCall->run();
				pCall->release();
			}
		}

		HANDLE GetEventHandle() const
		{
			return m_hEventHandle;
		}

		CallbackDispatcher()
		{
			m_hEventHandle = ::CreateEvent(0,FALSE,FALSE,0);
		}

		virtual ~CallbackDispatcher()
		{
			if ( m_hEventHandle!=INVALID_HANDLE_VALUE )
			{
				::CloseHandle(m_hEventHandle);
				m_hEventHandle = INVALID_HANDLE_VALUE;
			}
		}

	protected:
		LockFreeQueue<CallbackObject *>   m_ResultList;
		HANDLE                            m_hEventHandle;
	};
};

#endif//__CALLBACK_DISPATCHER_H__