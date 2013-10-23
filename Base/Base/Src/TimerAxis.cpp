/*******************************************************************
** �ļ���:	TimerAxis.cpp 
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

#include "stdafx.h"
#include <set>
#include <assert.h>
#include <windows.h>
#include <ctime>
#include <sys/timeb.h>

#include "TimerAxis.h"

#define new RKT_NEW

namespace xs {

	//////////////////////////////////////////////////////////////////////////
	TimerAxis::TimerAxis()
	{
		m_TimerAxis.resize((TIME_AXIS_LENGTH+TIME_GRID-1)/TIME_GRID);
		m_dwInitializeTime = GetTickCount();
		m_dwLastCheckTick  = m_dwInitializeTime;
	}

	//////////////////////////////////////////////////////////////////////////
	TimerAxis::~TimerAxis()
	{
		for ( DWORD i=0;i<m_TimerAxis.size();++i )
		{
			TIMER_LIST & TimerList = m_TimerAxis[i];
			TIMER_LIST::iterator it = TimerList.begin();
			for ( ;it!=TimerList.end();++it )
			{
				Timer * timer = *it;
				if( timer )
				{
					KillTimer(timer->dwTimerID,timer->handler);
				}
			}
		}

		m_TimerAxis.clear();
	}

	//////////////////////////////////////////////////////////////////////////
	bool TimerAxis::SetTimer( DWORD timerID,DWORD interval,ITimerHandler * handler,DWORD calltimes,const char * debugInfo )
	{
		//if (timerID == 101 && interval == 5000)
		//	debugBreak;

		if( handler==0 )
		{
			return false;
		}

		if ( interval==0 )
		{
			interval = 1;
		}

		void ** ppTimerInfo = handler->GetTimerInfoPtr();
		assert(ppTimerInfo);

		TIMER_INFO * pTimerInfo = *(TIMER_INFO **)ppTimerInfo;

		if ( pTimerInfo==0 )
		{
			pTimerInfo = new TIMER_INFO;
			*ppTimerInfo = pTimerInfo;
		}

		// ����Ƿ��Ѿ���������Timer
		TIMER_INFO::iterator it = pTimerInfo->begin();
		for ( ;it!=pTimerInfo->end();++it )
		{
			Timer & timer = *it;
			if ( timer.dwTimerID==timerID )
			{
				return false;
			}
		}

		Timer timer;
		timer.dwTimerID = timerID;
		timer.dwInterval= interval;
		timer.dwCallTimes = calltimes;
		timer.dwLastCallTick = m_dwLastCheckTick;
		timer.handler = handler;

		if ( debugInfo ) timer.debugInfo = debugInfo;

		timer.dwGridIndex = ((timer.dwLastCallTick + timer.dwInterval - m_dwInitializeTime) / TIME_GRID) % m_TimerAxis.size();

		pTimerInfo->push_back(timer);

		Timer & timerRef = pTimerInfo->back();
		Timer * timerPtr = &timerRef;
		m_TimerAxis[timer.dwGridIndex].push_back(timerPtr);
		timerPtr->pos = --m_TimerAxis[timer.dwGridIndex].end();

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool TimerAxis::KillTimer( DWORD timerID,ITimerHandler * handler )
	{
		void ** ppTimerInfo = handler->GetTimerInfoPtr();
		assert(ppTimerInfo);

		TIMER_INFO * pTimerInfo = *(TIMER_INFO **)ppTimerInfo;
        
		// ������û���
        if ( pTimerInfo == 0 )
             return false;

		// ����Ƿ��Ѿ���������Timer
		TIMER_INFO::iterator it = pTimerInfo->begin();
		for ( ;it!=pTimerInfo->end();++it )
		{
			Timer & timer = *it;
			if ( timer.dwTimerID==timerID )
			{
				// ��ʱ������ɾ�����timer
				// ��Ϊ�����ڱ����Ĺ����е���KillTimer
				// Ϊ�˱���������������ﲻֱ��ɾ��timer,�������ó�0,������ɾ
				*timer.pos = 0;	

				pTimerInfo->erase(it);

				if ( pTimerInfo->empty() )
				{
					delete pTimerInfo;
					*ppTimerInfo = 0;
				}
				return true;
			}
		}

		assert(false);
		return false;
	}

	//////////////////////////////////////////////////////////////////////////
	void TimerAxis::CheckTimer()
	{
		DWORD now = GetTickCount();
		if ( now-m_dwLastCheckTick<CHECK_FREQUENCY )
			return;

		DWORD start_grid = ((m_dwLastCheckTick-m_dwInitializeTime) / TIME_GRID) % m_TimerAxis.size();
		DWORD cur_grid = ((now-m_dwInitializeTime) / TIME_GRID) % m_TimerAxis.size();

		m_dwLastCheckTick = now;

		DWORD i = start_grid;

		// ����ʱ��̶�
		do
		{
			// ������ǰʱ��̶��е����д�������ʱ��
			TIMER_LIST & TimerList = m_TimerAxis[i];
			TIMER_LIST::iterator it = TimerList.begin();
			for ( ;it!=TimerList.end();)
			{
				Timer * timer = *it;
				if ( timer==0 )
				{
					it = TimerList.erase(it);
					continue;
				}

				// ������ʱ��
				if ( now - timer->dwLastCallTick >= timer->dwInterval )
				{	
					static xs::Timer per4Timer; 
					per4Timer.reset();
					timer->handler->OnTimer(timer->dwTimerID);

					// ���һ�����Timer�Ƿ�ɾ����
					if ( *it==timer )
					{
						//commented by xxh,��Щ�������Ӱ����ִ��Ч�ʣ�����ע�͵�
						// ���ܲ��Դ���
						if ( per4Timer.getTime() > 30 )  // lilinll77
						{
							char msg[256];
							sprintf(msg,"��ʱ��ִ��ʱ����� id=%d interval=%d cost=%d %s",timer->dwTimerID,timer->dwInterval,per4Timer.getTime(),timer->debugInfo.c_str());
							ErrorLn(msg);
						}

						timer->dwLastCallTick = now;
						timer->dwCallTimes   -= 1;

						if ( timer->dwCallTimes==0 )
						{
							// ���ô����Ѿ�����
							KillTimer(timer->dwTimerID,timer->handler);
						}
						else
						{
							// ��Ǩ����һ�δ�����λ��
							timer->dwGridIndex = ((timer->dwLastCallTick + timer->dwInterval - m_dwInitializeTime) / TIME_GRID) % m_TimerAxis.size();
							it = TimerList.erase(it);
							m_TimerAxis[timer->dwGridIndex].push_back(timer);
							timer->pos = --m_TimerAxis[timer->dwGridIndex].end();

							continue;
						}
					}
					else
					{                                                                                                                                                                                                                                                                                                                       
						// timer�Լ���ɾ����
						assert(*it==0);
						it = TimerList.erase(it);
						continue;
					}
				}

				++it;
			}

			// �ݽ�����һ���̶�
			if ( i==cur_grid )
				break;

			i = (i+1)% m_TimerAxis.size();
		}while(i!=cur_grid);
	}

	//��FixTimeer�ķ�װ����
	bool TimerAxis::SetFixTimer( DWORD timerID,DWORD dwFixStartTime, DWORD intervalDays,ITimerHandler * handler,DWORD callTimes/*=INFINITY_CALL*/,const char * debugInfo/*=0 */ )
	{
		return m_FixTimerAxis.SetFixTimer(timerID, dwFixStartTime, intervalDays, handler, callTimes, debugInfo);
	}

	bool TimerAxis::KillFixTimer( DWORD timerID,ITimerHandler * handler )
	{
		return m_FixTimerAxis.KillFixTimer(timerID, handler);
	}

	void TimerAxis::CheckFixTimer()
	{
		return m_FixTimerAxis.CheckFixTimer();
	}
	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
#define  HOURS_ONE_DAY 24
#define  SECONDS_PER_DAY (60 * 60 * 24)
#define  SECONDS_PER_HOUR (60 * 60)
#define  SECONDS_PER_MINUTE (60)
	FixTimerAxis::FixTimerAxis()
	{
		//�̶�ʱ��㶨ʱ����ʱ���᳤�� 24
		m_FixTimerAxis.resize(HOURS_ONE_DAY);
		m_dwInitializeTime = GetSecondCount();
		m_dwLastCheckSecond = m_dwInitializeTime;

	}

	FixTimerAxis::~FixTimerAxis()
	{
		for ( DWORD i=0;i<m_FixTimerAxis.size();++i )
		{
			FIX_TIMER_LIST & TimerList = m_FixTimerAxis[i];
			FIX_TIMER_LIST::iterator it = TimerList.begin();
			for ( ;it!=TimerList.end();++it )
			{
				FixTimer * timer = *it;
				if( timer )
				{
					KillFixTimer(timer->dwTimerID,timer->handler);
				}
			}
		}

		m_FixTimerAxis.clear();
	}

	DWORD FixTimerAxis::GetSecondCount()
	{
		time_t timeSecond;
		time(&timeSecond);
		return timeSecond;
	}

	static inline DWORD GetMorningTime(DWORD dwNow)
	{
		return (dwNow / SECONDS_PER_DAY) * SECONDS_PER_DAY;
	}

	bool FixTimerAxis::SetFixTimer( DWORD timerID,DWORD dwFixStartTime, DWORD dwIntervalDays,ITimerHandler * handler
									,DWORD callTimes/*=INFINITY_CALL*/,const char * debugInfo/*=0 */ )
	{
		if( handler==0 )
		{
			return false;
		}

		//ת���ɸ�������ʱ��
		struct _timeb tstruct;
		_ftime( &tstruct ); 
		//timezone	Difference in minutes, moving westward, between UTC and local time
		dwFixStartTime += SECONDS_PER_DAY + tstruct.timezone * SECONDS_PER_MINUTE;

		dwFixStartTime %= SECONDS_PER_DAY;//ȡֵ��Χ[0,60*60*24)

		if ( dwIntervalDays==0 )
		{
			dwIntervalDays = 1;
		}
		void ** ppTimerInfo = handler->GetTimerInfoPtr();
		assert(ppTimerInfo);

		FIX_TIMER_INFO * pTimerInfo = *(FIX_TIMER_INFO **)ppTimerInfo;

		if ( pTimerInfo==0 )
		{
			pTimerInfo = new FIX_TIMER_INFO;
			*ppTimerInfo = pTimerInfo;
		}

		// ����Ƿ��Ѿ���������Timer
		FIX_TIMER_INFO::iterator it = pTimerInfo->begin();
		for ( ;it!=pTimerInfo->end();++it )
		{
			FixTimer & timer = *it;
			if ( timer.dwTimerID==timerID )
			{
				return false;
			}
		}

		FixTimer timer;
		timer.dwTimerID = timerID;
		timer.dwFixStartTime = dwFixStartTime;
		timer.dwIntervalDays = dwIntervalDays;
		timer.dwCallTimes = callTimes;
		timer.handler = handler;

		DWORD now = GetSecondCount();

		//Ϊ���ڽ������Ĺ̶�ʱ���������Ч������timer�ٵ�dwLastCallSecond
		DWORD dwNowDayTime  = now %SECONDS_PER_DAY;//ȡֵ��Χ[0,60*60*24)�ĵ�ǰʱ��
		if (dwNowDayTime > dwFixStartTime)
		{
			timer.dwLastCallSecond = GetMorningTime(now) + dwFixStartTime;
		}
		else
		{
			timer.dwLastCallSecond = GetMorningTime(now) - (dwIntervalDays * SECONDS_PER_DAY) + dwFixStartTime;
		}

		if ( debugInfo )
		{
			timer.debugInfo = debugInfo;
		}

		timer.dwGridIndex = dwFixStartTime / SECONDS_PER_HOUR;

		pTimerInfo->push_back(timer);

		FixTimer & timerRef = pTimerInfo->back();
		FixTimer * timerPtr = &timerRef;
		m_FixTimerAxis[timer.dwGridIndex].push_back(timerPtr);
		timerPtr->pos = --m_FixTimerAxis[timer.dwGridIndex].end();

		return true;
	}

	bool FixTimerAxis::KillFixTimer( DWORD timerID,ITimerHandler * handler )
	{
		void ** ppTimerInfo = handler->GetTimerInfoPtr();
		assert(NULL != ppTimerInfo);

		FIX_TIMER_INFO * pTimerInfo = *(FIX_TIMER_INFO **)ppTimerInfo;

		// ������û���
		if (NULL == pTimerInfo)
		{
			return false;
		}

		// ����Ƿ��Ѿ���������Timer
		FIX_TIMER_INFO::iterator it = pTimerInfo->begin();
		for ( ;it!=pTimerInfo->end();++it )
		{
			FixTimer & timer = *it;
			if ( timer.dwTimerID==timerID )
			{
				// ��ʱ������ɾ�����timer
				// ��Ϊ�����ڱ����Ĺ����е���KillTimer
				// Ϊ�˱���������������ﲻֱ��ɾ��timer,�������ó�0,������ɾ
				*timer.pos = NULL;	

				pTimerInfo->erase(it);

				if ( pTimerInfo->empty() )
				{
					delete pTimerInfo;
					*ppTimerInfo = NULL;
				}
				return true;
			}
		}

		assert(false);
		return false;
	}

	void FixTimerAxis::CheckFixTimer()
	{
		DWORD now = GetSecondCount();
		if (now - m_dwLastCheckSecond < 1 )
		{
			return;
		}

		DWORD start_grid = (m_dwLastCheckSecond % SECONDS_PER_DAY) / SECONDS_PER_HOUR;
		DWORD cur_grid = (now % SECONDS_PER_DAY) / SECONDS_PER_HOUR;

		m_dwLastCheckSecond = now;

		DWORD i = start_grid;

		// ����ʱ��̶�
		do
		{
			// ������ǰʱ��̶��е����д�������ʱ��
			FIX_TIMER_LIST & TimerList = m_FixTimerAxis[i];
			FIX_TIMER_LIST::iterator it = TimerList.begin();
			for ( ;it!=TimerList.end();)
			{
				FixTimer * timer = *it;
				if ( timer==0 )
				{
					it = TimerList.erase(it);
					continue;
				}

				// ������ʱ��
				if ( now - timer->dwLastCallSecond >= (timer->dwIntervalDays * SECONDS_PER_DAY) )
				{
					timer->handler->OnTimer(timer->dwTimerID);

					// ���һ�����Timer�Ƿ�ɾ����
					if ( *it==timer )
					{
						timer->dwLastCallSecond = GetMorningTime(now) + timer->dwFixStartTime;
						timer->dwCallTimes   -= 1;

						if ( timer->dwCallTimes==0 )
						{
							// ���ô����Ѿ�����
							KillFixTimer(timer->dwTimerID,timer->handler);
						}
					}
					else
					{
						// timer�Լ���ɾ����
						assert(*it==0);
						it = TimerList.erase(it);
						continue;
					}
				}

				++it;
			}

			// �ݽ�����һ���̶�
			if ( i==cur_grid )
				break;

			i = (i+1)% m_FixTimerAxis.size();
		}while(i!=cur_grid);
	}


} // namespace
