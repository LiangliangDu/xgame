/*******************************************************************
** �ļ���:	TimerAxis.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/21/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: crr
** ��  ��: 2010-05-04
** ��  ��: ���ӿ�ʼ�ڹ̶�ʱ���Ķ�ʱ��
********************************************************************/

#ifndef  __TIMER_AXIS_H__
#define  __TIMER_AXIS_H__

#include "Common.h"
#include <string>
#include <list>
#include <vector>
#include "TimerHandler.h"
#include "Timer.h"

// ������������
#ifdef WIN32
#	include <windows.h>
#else
	typedef unsigned long DWORD;
#endif

#ifdef RKT_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable : 4251)
#endif

namespace xs {

	/*
	*  ����:
	*  1.OnCheck����Ƶ�ʴ��ڵ�λʱ��̶�ʱ��ô����?
	*  2.���߳�֧��
	*  3.��Timer��ô����?
	*  4.��Ҫ֧�ֵ��Թ���
	*
	*  ����:
	*  1.ʱ����ĺ���ʵ����һ����Ч�������㷨
	*  2.���㷨�Բ���ɾ������Ҫ�󼫸�
	*  3.��Ҫ�ǲ�������,���Ƕ�һ��������������
	*  4.��������ʵ������Ҫ��Ҫ������ξ����ҵ�һ��ֵ�������ڵ�λ��
	*  
	*  ��Ʒ���:
	*  1.��ʱ����ֳ�N���̶�,ÿ���̶��ڱ���˶�ʱ������Ҫ���õ�Timer
	*  2.��Timer�����N����Timer�ص�
	*  3.��Ϊ�ڵ�λʱ��̶���ֻ��Ҳֻ����ü���,����ͬһ�̶��ڵ�Timer��������
	*  4.����ʱ������N����ͬ���ȶε���ʱ������϶���,������ʱƵ����1������
	*    ��ҪƵ�����õĶ�ʱ�����Է���һ��ÿ�񳤶�1ms���ȵ���1�뼫��ϸ����ʱ������
	*    �Դﵽ���Ч��
	*  5.�������ɾ��Timerʱ�Ĳ��Ҳ������Դ�����Ч��.
	*/

	//////////////////////////////////////////////////////////////////////////
	/************************* TimerAxis Config *****************************/

	// �Ƽ����Ƶ��	:	16(ms) 
	// �Ƽ�ʱ��̶� :       64(ms)
#	define CHECK_FREQUENCY	        16	//��ȷ��16ms
#	define TIME_GRID	        64

	// ʱ���᳤��
#	define TIME_AXIS_LENGTH		720000
#	define INVALID_TIMER	        0xffffffff
#	define INFINITY_CALL            0xffffffff

	//////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////

	class RKT_EXPORT FixTimerAxis
	{
	public:
		/**
		@purpose          : ����һ���̶�ʱ���Ķ�ʱ��
		@param	 timerID  : ��ʱ��ID
		@param	 dwFixStartTime  : �̶��Ŀ�ʼʱ�䣬����Ϊ��λ��ȡֵ��Χ[0,60*60*24)
		@param   intervalDays : ��ʱ�����ü������
		@param   handler  : ����ӿ�
		@param   callTimes: ���ô���,Ĭ�ϵ��������
		@param   debugInfo: ������Ϣ
		@return		      : ������óɹ��򷵻�true
		*/
		bool SetFixTimer( DWORD timerID,DWORD dwFixStartTime, DWORD intervalDays,ITimerHandler * handler,DWORD callTimes=INFINITY_CALL,const char * debugInfo=0 );


		/**
		@purpose          : ɾ����ʱ��
		@param	 timerID  : ��ʱ��ID
		@param   handler  : ����ӿ�
		@return		      : �����Ƿ�ɾ���ɹ�
		*/
		bool KillFixTimer( DWORD timerID,ITimerHandler * handler );

		void CheckFixTimer();

		FixTimerAxis();

		virtual ~FixTimerAxis();

	protected:
		/// ȡ�õ�ǰʱ������Ϊ��λ��ȡֵ��Χ[0,60*60*24),������޸ĳ�ʹ������API
		DWORD GetSecondCount();

	protected:
		struct FixTimer
		{
			DWORD           dwTimerID;
			DWORD			dwFixStartTime;	   // �̶���ʱ����ʼʱ��
			DWORD           dwIntervalDays;    // ��ʱ�����ü������
			DWORD           dwCallTimes;       // �ܹ���Ҫ�ص����ٴ�
			DWORD           dwLastCallSecond;  // ���һ�ε��õ�ʱ��
			DWORD           dwGridIndex;       // ���ڵ�ʱ��̶�
			ITimerHandler * handler;
			std::string     debugInfo;
			std::list<FixTimer*>::iterator pos; // ��ʱ��̶��е�iterator,�ӿ�����
		};

		typedef std::list<FixTimer>          FIX_TIMER_INFO;   // ����ITimerHandler�еĶ�ʱ����ʱ��Ϣ
		typedef std::list<FixTimer *>        FIX_TIMER_LIST;   // ÿһ��ʱ��̶��д�ŵĶ�ʱ���б�
		typedef std::vector<FIX_TIMER_LIST>  FIX_TIMER_AXIS;	// ��������ʱ��̶���Ϣ��ʱ����ṹ

		FIX_TIMER_AXIS     m_FixTimerAxis;
		DWORD              m_dwLastCheckSecond;        // ���һ�μ���ʱ��
		DWORD              m_dwInitializeTime;          // ʱ�����ʼʱ��
	};

	//////////////////////////////////////////////////////////////////////////////


	class RKT_EXPORT TimerAxis
	{
	public:
		/**
		@purpose          : ����һ����ʱ��
		@param	 timerID  : ��ʱ��ID
		@param   interval : ��ʱ�����ü��
		@param   handler  : ����ӿ�
		@param   callTimes: ���ô���,Ĭ�ϵ��������
		@param   debugInfo: ������Ϣ
		@return		      : ������óɹ��򷵻�true
		*/
		bool SetTimer( DWORD timerID,DWORD interval,ITimerHandler * handler,DWORD callTimes=INFINITY_CALL,const char * debugInfo=0 );

		/**
		@purpose          : ɾ����ʱ��
		@param	 timerID  : ��ʱ��ID
		@param   handler  : ����ӿ�
		@return		      : �����Ƿ�ɾ���ɹ�
		*/
		bool KillTimer( DWORD timerID,ITimerHandler * handler );

		void CheckTimer();
		/////////////////////////////////////////////////////////////
		//ʹ��TimerAxis ���� FixTimerAxis�Ľӿڣ�ʹ�ö���Ľӿ�ͳһ
		/**
		@purpose          : ����һ���̶�ʱ���Ķ�ʱ��
		@param	 timerID  : ��ʱ��ID
		@param	 dwFixStartTime  : �̶��Ŀ�ʼʱ�䣬����Ϊ��λ��ȡֵ��Χ[0,60*60*24)
		@param   intervalDays : ��ʱ�����ü������
		@param   handler  : ����ӿ�
		@param   callTimes: ���ô���,Ĭ�ϵ��������
		@param   debugInfo: ������Ϣ
		@return		      : ������óɹ��򷵻�true
		*/
		bool SetFixTimer( DWORD timerID,DWORD dwFixStartTime, DWORD intervalDays,ITimerHandler * handler,DWORD callTimes=INFINITY_CALL,const char * debugInfo=0 );


		/**
		@purpose          : ɾ����ʱ��
		@param	 timerID  : ��ʱ��ID
		@param   handler  : ����ӿ�
		@return		      : �����Ƿ�ɾ���ɹ�
		*/
		bool KillFixTimer( DWORD timerID,ITimerHandler * handler );

		//��鶨�㶨ʱ��
		void CheckFixTimer();
		/////////////////////////////////////////////////////////////

		TimerAxis();

		virtual ~TimerAxis();

	protected:
		/// ȡ�õ�ǰʱ��,������޸ĳ�ʹ������API
		inline DWORD GetTickCount() { return ::GetTickCount();}

	protected:
		struct Timer
		{
			DWORD           dwTimerID;
			DWORD           dwInterval;      // 
			DWORD           dwCallTimes;     // �ܹ���Ҫ�ص����ٴ�
			DWORD           dwLastCallTick;  // ���һ�ε��õ�ʱ��
			DWORD           dwGridIndex;     // ���ڵ�ʱ��̶�
			ITimerHandler * handler;
			std::string     debugInfo;
			std::list<Timer*>::iterator pos; // ��ʱ��̶��е�iterator,�ӿ�����
		};

		typedef std::list<Timer>          TIMER_INFO;   // ����ITimerHandler�еĶ�ʱ����ʱ��Ϣ
		typedef std::list<Timer *>        TIMER_LIST;   // ÿһ��ʱ��̶��д�ŵĶ�ʱ���б�
		typedef std::vector<TIMER_LIST>   TIMER_AXIS;	// ��������ʱ��̶���Ϣ��ʱ����ṹ

		TIMER_AXIS         m_TimerAxis;
		DWORD              m_dwLastCheckTick;           // ���һ�μ���ʱ��
		DWORD              m_dwInitializeTime;          // ʱ�����ʼʱ��

		FixTimerAxis	   m_FixTimerAxis;            //���붨�㶨ʱ���Ĺ���
	};

} // namespace


#ifdef RKT_COMPILER_MSVC
#pragma warning(pop)
#endif

#endif// __TIMER_AXIS_H__