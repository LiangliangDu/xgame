/*******************************************************************
** �ļ���:	Reactor_Win32.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/24/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __REACTOR_WIN32_H__
#define __REACTOR_WIN32_H__

#ifdef WIN32

#include "Reactor.h"
#include "singleton.h"
#include "Thread.h"
#include "SwappingList.h"

#include <map>
#include <list>

namespace xs{

	// ��ѯʱ����
#	define  POLLING_INTERVAL     1

	/**
	@name : ��Ӧ�� (Reactor)
	@brief: ��Ӧ�����ǵȴ�����¼�Ȼ�������Ӧ�Ĵ���������ôһ��װ��
			Windows����WaitForMultipleObjectsʵ��
	@warning: ע��:
	        1.���/ɾ���¼���Ҫע����̼߳���
			2.֧�ֶ���64���¼��ļ���,����64���¼�ʱʹ����ѯ��ʽ����¼�
	*/
	class Reactor_Win32 : public Reactor,public EventHandler,public SingletonEx<Reactor_Win32>
	{
	public:
		/**
		@purpose    : ���Ҫ�������¼�
		@param event: �¼����
		@return		  : true  ... ע��ɹ�
		false ... �Ѿ��ﵽ����¼�����
		false ... ���¼�������
		*/
		virtual bool AddEvent( HANDLE event );

		/**
		@purpose    : �Ƴ�Ҫ�������¼�
		@param event: �¼����
		*/
		virtual void RemoveEvent( HANDLE event );

		/**
		@purpose      : ע��һ���¼� (һ��Handler���Դ������¼�,һ���¼������ɶ������������)
		@param event  : �¼����
		@param handler: �¼��������
		@return		  : true  ... ע��ɹ�
		false ... �Ѿ��ﵽ����¼�����
		false ... ���¼�������
		*/
		virtual bool RegisterEventHandler( HANDLE event,EventHandler * handler);

		/**
		@purpose      : ȡ��һ���¼�������
		@note         : �ô��������ٴ�������¼�����������¼����ɼ�����ֻ�е���RemoveEvent�Ų��ټ����¼�
		@param event  : �¼����
		@param handler: �¼��������
		@return		  :
		*/
		virtual void UnRegisterEventHandler( HANDLE event,EventHandler * handler);

		/**
		//crr add
		@name         : �ڷ�Ӧ����ɾ���¼��������
		@brief        : RegisterEventHandler �����¼��Ķ�������ڷ�Ӧ���̴߳����¼�֮ǰ��ɾ�� ����������
		���ӽӿں����ڷ�Ӧ���߳� ��ɾ�� �¼��������
		@note         : 
		@param event  : �¼����
		@param handler: �¼��������
		@return		  :
		*/
		virtual void SafeReleaseEventHandler(HANDLE event,EventHandler * handler);

		/**
		@purpose      : �ȴ��¼�����������
		@param	wait  : �ȴ��ĺ�����
		@return       : �ȴ��Ĺ������Ƿ����
		*/
		virtual bool HandleEvents( DWORD wait );

		/**
		@purpose      : ѭ���ȴ�/�����¼�
		*/
		virtual bool HandleEventsLoop();

		/**
		@name         : ֪ͨ��Ӧ���߳��˳�
		@brief        : ��Щ�������Ƕ��̰߳�ȫ��
		*/
		virtual void NotifyExit();

		/**
		@name         : ��������Ĳ����¼�,���������߳�ͬ��
		@brief        :
		*/
		virtual void OnEvent( HANDLE event );

		virtual void Release() { delete this;}

		Reactor_Win32();

		virtual ~Reactor_Win32();

	protected:
		// �����Ĵ�����,�����Ѿ����˷�Ӧ���Լ����߳�,û�ж��߳�ͬ��������
		bool AddEventAux( HANDLE event );
		void RemoveEventAux( HANDLE event );
		bool RegisterEventHandlerAux( HANDLE event,EventHandler * handler);
		void UnRegisterEventHandlerAux( HANDLE event,EventHandler * handler);
		void ReleaseEventHandlerAux( HANDLE event,EventHandler * handler);
		void NotifyExitAux();

	protected:
		typedef std::list<EventHandler *>     HANDLER_LIST;
		typedef std::map<HANDLE,HANDLER_LIST> HANDLERS_MAP;

		HANDLE    *  m_EventHandles;                        // ���������¼�����
		DWORD        m_dwEventsNum;                         // �¼�����
		DWORD        m_dwArrayCapability;                   // ��������
		HANDLERS_MAP m_HandlersMap;                         // �¼��������б�

		HANDLE       m_hSelfEvent;                          // ��Ӧ���Լ���ά���¼�
		struct       REACTOR_TASK
		{
			enum
			{
				REACTOR_ADD = 0   , 
				REACTOR_DELETE    ,
				REACTOR_REGISTER  ,
				REACTOR_UNREGISTER,
				REACTOR_RELEASE_HANDLER,
				REACTOR_EXIT      ,
			};

			int      type;          // ��������
			HANDLE   event;       
			EventHandler * handler;
		};

		SwappingList<REACTOR_TASK>   m_TaskList; // �����б�
	};

};

#endif

#endif//__REACTOR_WIN32_H__