/**
* Created by pk 2008.01.03
*/

#ifndef RKT_TIMER_H
#define RKT_TIMER_H

#include "Common.h"
#include "Api.h"

namespace xs {
/*
	/// ������ʱ��
	class RKT_EXPORT CTimer
	{
		int64 mBeginTime;	/// ʱ�ӿ�ʼʱ���
		int64 mEndTime;		/// ʱ�ӽ���ʱ���

	public:
		CTimer();

		/// ����ʱ��
		void begin();

		/// ֹͣʱ��
		void end();

		/// ���غ������������ͣ�
		ulong getTime() const;

		/// ���غ�������Double�ͣ�
		double getTimeByDouble() const;
	};*/

	class RKT_EXPORT Timer
	{
		int64 mBeginCount;	/// ʱ�ӿ�ʼʱ�ļ���

	public:
		Timer();

		/// ����ʱ��
		void reset();

		/// ���غ������������ͣ�
		ulong getTime() const;

		/// ���غ�������Double�ͣ�
		double getTimeByDouble() const;
	};

}

#endif // RKT_TIMER_H