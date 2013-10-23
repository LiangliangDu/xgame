/*******************************************************************
** �ļ���:	WorkerThreadPool.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/25/2008
** ��  ��:	1.0
** ��  ��:	�����̳߳�
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __WORKER_THREAD_POOL_H__
#define __WORKER_THREAD_POOL_H__

#include "singleton.h"
#include "Proactor_Win32.h"
#include "Reactor_Win32.h"
#include "Thread.h"

namespace xs{

	/**
	@name : ��ɶ˿ڹ����߳�
	@brief: �ù����߳����������Proactor����ȡIO����¼�
	*/
	class ProactorWorker : public IRunnable
	{
	public:
		virtual void run()
		{
			Proactor_Win32::getInstance().HandleEventsLoop();
		}

		virtual void release()
		{
			delete this;
		}
	};

	/**
	@name : ��Ӧ�������߳�
	@brief:
	*/
	class ReactorWorker : public IRunnable
	{
	public:
		virtual void run()
		{
			Reactor_Win32::getInstance().HandleEventsLoop();
		}

		virtual void release()
		{
			delete this;
		}
	};

	/**
	@name : �����߳�����
	@brief: 
	*/
	class WorkerThreadPool : public ThreadPool,public SingletonEx<WorkerThreadPool>
	{
	};
};

#endif//__WORKER_THREAD_POOL_H__