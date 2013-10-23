/*******************************************************************
** �ļ���:	TimerHandler.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/22/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __TIMER_HANDLER_H__
#define __TIMER_HANDLER_H__

#include "Common.h"
#include "Trace.h"

namespace xs {

	//////////////////////////////////////////////////////////////////////////
	/*********************** ��ʱ������ӿ� *********************************/
	// ʹ�÷���:
	//           class A : public TimerHandler
	//           {
	//                  virtual void OnTimer( unsigned long dwTimerID )
	//                  { do something .... }
	//           }
	//
	//          A a;
	//          TimeAxis.SetTimer(1000,&a);
	//          TimeAxis.KillTimer(&a);
	//////////////////////////////////////////////////////////////////////////


	// ---------------------------------------------------------------------------
	// Name	: ��ʱ��������Ĵ���ӿ�
	// Desc : ��Ӧ�ò�ʹ��ʱ������TimerHandler�̳У�
	// ---------------------------------------------------------------------------
	struct ITimerHandler
	{
		/**
		@purpose          : ��ʱ��������ص�,������������д�������
		@param	 dwTimerID: ��ʱ��ID,�����������ĸ���ʱ��
		@return		      : empty
		*/
		virtual void OnTimer( unsigned long dwTimerID ) = 0;

		/**
		@purpose          : ȡ�ô�Ŷ�ʱ���ڲ����ݵ�ָ��
		@note             : ���������Ӧ�ò��޹�,����TimerHandler�����ʵ�ּ���
		@note             : ʱ�������ʵ������Ҫ��߶�ʱ���Ĳ���ɾ��Ч�ʣ�������Ӧ�ò��¼һ��ָ��
		@return		      : ����ָ����ʱ��Ϣ��ָ��,��ָ������ʼ����0
		*/
		virtual void ** GetTimerInfoPtr() = 0;
	};

	// ---------------------------------------------------------------------------
	// Name	: ��ʱ�����������
	// Desc : ��Ҫ�Ƿ�װһ��GetTimerInfoPtr��ʵ��
	// ---------------------------------------------------------------------------
	class RKT_EXPORT TimerHandler : public ITimerHandler
	{
	public:
		virtual void ** GetTimerInfoPtr() { return &_InfoPtr; }  

		TimerHandler() : _InfoPtr(0)
		{
		}

		virtual ~TimerHandler()
		{
			Assert( _InfoPtr==0 );
		}

	protected:
		void * _InfoPtr; // ָ����ʱ���ݵ�ָ��
	};

} // namespace

#endif//__TIMER_HANDLER_H__