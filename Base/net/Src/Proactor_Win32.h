/*******************************************************************
** �ļ���:	Proactor_Win32.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/24/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  Windows��Proactorʵ�� - ��ɶ˿�(IOCP)	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __PROACTOR_WIN32_IOCP_H__
#define __PROACTOR_WIN32_IOCP_H__

#include "Proactor.h"
#include "singleton.h"

namespace xs{

	#ifdef WIN32

	/**
	@name : Windows��Proactorʵ�� - ��ɶ˿�(IOCP)
	@brief: ��ɶ˿�����������:
			1.�ֽ�����¼�
			2.���Ʋ��������߳�
	@warning: ע��: Window98 Window95��֧����ɶ˿�
	*/
	class Proactor_Win32 : public Proactor,public SingletonEx<Proactor_Win32>
	{
	public:
		//////////////////////////////////////////////////////////////////////////
		virtual bool Create(unsigned long nConcurrentThreadsNum=0);

		virtual void Close();

		virtual bool RegisterDevice(AsynIoDevice * device);

		virtual bool HandleEvents(unsigned long wait=INFINITE);

		virtual void HandleEventsLoop();

		virtual bool PostCompletion( AsynIoResult * result);

		Proactor_Win32() : m_hCompletePort(0),m_dwConcurrentThreadsNum(0)
		{}

		virtual ~Proactor_Win32()
		{
			Close();
		}

	protected:
		HANDLE  m_hCompletePort;         // ��ɶ˿ھ��
		DWORD   m_dwConcurrentThreadsNum;// ���������߳�����
	};

	#endif
};

#endif//__PROACTOR_WIN32_IOCP_H__