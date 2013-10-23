/*******************************************************************
** �ļ���:	SwappingList.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/25/2008
** ��  ��:	1.0
** ��  ��:	��ת����
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __SWAPPING_LIST_H__
#define __SWAPPING_LIST_H__

#include <list>
#include "Thread.h"
using namespace xs;

/**
@name : ��ת����
@brief: �ڶ��߳�������-������ģʽ���������߳��������Ӷ����������̴߳Ӷ���ȡ�߶���
        ��Ϊ�漰�����̷߳��ʣ�������б��������/ȡ�߶���ʱ���������ģ��ʵ�����ֶ��߳�
		��ȫ�Ķ��У�����ʹ���������з�ת�ļ��������Լ���ļ���������ļ���
*/

template<typename _OBJ>
class SwappingList
{
public:
	size_t Add(_OBJ & obj )
	{
		ResGuard<Mutex> lock(m_frontMutex);

		m_frontList->push_back(obj);
		return m_frontList->size();
	}

	bool Get(_OBJ & obj )
	{
        ResGuard<Mutex> lock(m_backMutex);

		if ( m_backList->empty() )
		{
			Swap();
		}

		if ( m_backList->empty() )
		{
			return false;
		}

		obj = m_backList->front();
		m_backList->pop_front();
		return true;
	}

	void Swap()
	{
		ResGuard<Mutex> lock(m_frontMutex);
		
		PRODUCT_LIST * p = m_backList;
		m_backList = m_frontList;
		m_frontList = p;
	}
	
	SwappingList()
	{
		m_frontList = new PRODUCT_LIST;
		m_backList  = new PRODUCT_LIST;
	}

	virtual ~SwappingList()
	{
		if ( m_frontList )
		{
			delete m_frontList;
			m_frontList = 0;
		}

		if ( m_backList )
		{
			delete m_backList;
			m_backList = 0;
		}
	}

protected:
	typedef  std::list<_OBJ>   PRODUCT_LIST;
	PRODUCT_LIST    *        m_frontList;
	PRODUCT_LIST    *        m_backList;

	Mutex                    m_frontMutex;
	Mutex                    m_backMutex;
};

#endif//__SWAPPING_LIST_H__