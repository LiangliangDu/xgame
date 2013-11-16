/******************************************************************
** �ļ���:	CoolingMgr.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008-4-18
** ��  ��:	1.0
** ��  ��:	��ȴ����			
** Ӧ  ��:  
******************************************************************/

#include "CoolingObject.h"
#include "CoolingSubscriber.h"

#pragma once

class CoolingMgr :public SingletonEx<CoolingMgr>
{
	typedef HashMap<ulong,CoolingObject*> CoolingObjectMap;
	CoolingObjectMap		m_coolingObjectMap[EFreeze_ClassID_Max];
	ulong					m_coolingObjectMax;

	CoolingSubscriber*		m_pCoolingSubscriber;

public:
	CoolingMgr();
	~CoolingMgr();


	void addCoolingObject(ulong type,ulong id,ulong ltime);
	//�ж�ĳ�������Ƿ��Ѿ���ȴ���
	bool isCompleted(ulong id,ulong type);

	/**ȡ����Ʒ����ȴ��Ϣ
	@param id ��ƷID������ȴID
	@param type ����,�ο���ȴ����
	@param ltime ��ȴʱ��
	@param liveTime ʣ�µ�ʱ��
	@return ����ɹ���ѯ������true,����false
	*/
	bool getCoolingInfo(const ulong id,const ulong type,ulong& ltime,ulong& liveTime);

	void update();

	void init();
	void clear();
};