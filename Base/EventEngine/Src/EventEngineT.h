/*******************************************************************
** �ļ���:	e:\CoGame\EventEngine\src\EventEngine\EventEngineT.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2007/9/9  21:38
** ��  ��:	1.0
** ��  ��:	�¼�����ģ��
** Ӧ  ��:  	
	
**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once

#include <hash_map>
#include <list>
#include <string>
using namespace std;
using namespace stdext;

// ����������
#define FIRE_MAX_LAYERNUM			20

// ����������
#define REF_MAX_LAYERNUM			5

// �¼�key
struct __EventKey
{
	DWORD	dwSrcID;			// ����Դ��ʶ��UID��"���к�"���ݣ�	
	BYTE	bSrcType;			// ����Դ����
	WORD	wEventID;			// �¼�ID 
	BYTE	bReserve;			// ����
};

struct SEventKey
{
	union
	{
		__EventKey			_key;
		LONGLONG			_value;
	};

	SEventKey(void)
	{
		_value = 0;
	}

	bool operator == (const SEventKey &eventkey) const
	{
		return _value == eventkey._value;
	}

	bool operator < (const SEventKey &eventkey) const
	{
		return _value < eventkey._value;
	}
};

// �ػ�hash����
namespace stdext
{
	inline size_t hash_value(const SEventKey &eventkey)
	{
		DWORD k1 = (eventkey._key.dwSrcID & 0xFFFF) << 16;
		DWORD k2 = (eventkey._key.wEventID & 0xFF) << 8;
		DWORD k3 = eventkey._key.bSrcType;
		return k1 + k2 + k3;
	}
}

// �¼�����ģ��
template< class TSink, class TOnEventObject >
class TEventEngine
{	
private:	
	struct SSubscibeInfo
	{
		TSink *		pSink;
		char		szDesc[32];
		int			nCallCount;
		bool		bRemoveFlag;

		SSubscibeInfo(TSink * pPrameSink, LPCSTR pDesc)
		{
			pSink = pPrameSink;		
			nCallCount = 0;
			bRemoveFlag = false;
			if(pDesc != NULL)
			{
				lstrcpyn(szDesc, pDesc, sizeof(szDesc));
			}
			else
			{
				szDesc[0] = '\0';
			}
		}

		void Add(void)
		{
			nCallCount++;
		}

		void Sub(void)
		{
			nCallCount--;
		}
	};
	// һ���¼�KEY�Ķ������б�
	typedef std::list< SSubscibeInfo >							TLIST_SUBSCIBEINFO;

	// �����¼�KEY�Ķ������б�
	typedef stdext::hash_map<SEventKey, TLIST_SUBSCIBEINFO >	TMAP_SAFESINK;
public:
	/** 
	@param   
	@param   
	@return  
	*/
	TEventEngine()
	{
		m_nFireLayerNum = 0;
	}

	/** 
	@param   
	@param   
	@return  
	*/
	virtual ~TEventEngine()
	{
		typename TMAP_SAFESINK::iterator it = m_mapSafeSink.begin();
		for( ; it != m_mapSafeSink.end(); ++it)
		{
			TLIST_SUBSCIBEINFO * plisSubscibeInfo = &((*it).second);
			plisSubscibeInfo->clear();
		}

		m_mapSafeSink.clear();
	}

	/** 
	@param   
	@param   
	@return  
	*/
	bool Subscibe(TSink * pSink, WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszDesc)	
	{
		if(pSink == NULL)
		{
			return false;
		}

		// �¼�KEY
		SEventKey eventkey;
		eventkey._key.wEventID = wEventID;
		eventkey._key.bSrcType = bSrcType;
		eventkey._key.dwSrcID = dwSrcID;

		// ��������Ϣ
		SSubscibeInfo subscibeinfo(pSink, pszDesc);

		// ���뵽�����б�
		typename TMAP_SAFESINK::iterator it = m_mapSafeSink.find(eventkey);
		if(it == m_mapSafeSink.end())
		{
			TLIST_SUBSCIBEINFO listSubscibeInfo;
			listSubscibeInfo.push_front(subscibeinfo);

			// ���뵽�����б�					
			m_mapSafeSink.insert(TMAP_SAFESINK::value_type(eventkey, listSubscibeInfo));
		}
		else
		{
			TLIST_SUBSCIBEINFO * plistSubscibeInfo = &((*it).second);
			plistSubscibeInfo->push_front(subscibeinfo);
		}

		return true;		
	}

	/** 
	@param   
	@param   
	@return  
	*/
	bool UnSubscibe(TSink * pSink, WORD wEventID, BYTE bSrcType, DWORD dwSrcID)
	{
		if(pSink == NULL)
		{
			return false;
		}	

		SEventKey eventkey;
		eventkey._key.wEventID = wEventID;
		eventkey._key.bSrcType = bSrcType;
		eventkey._key.dwSrcID = dwSrcID;

		typename TMAP_SAFESINK::iterator it = m_mapSafeSink.find(eventkey);
		if(it != m_mapSafeSink.end())
		{
			TLIST_SUBSCIBEINFO * plistSubscibeInfo = &((*it).second);

			typename TLIST_SUBSCIBEINFO::iterator itList = plistSubscibeInfo->begin();
			for( ; itList != plistSubscibeInfo->end(); ++itList)
			{
				SSubscibeInfo * pSubscibeInfo = &(*itList);
				if(pSubscibeInfo->pSink == pSink)
				{
					if(pSubscibeInfo->nCallCount == 0)
					{
						plistSubscibeInfo->erase(itList);
					}
					else
					{
						pSubscibeInfo->bRemoveFlag = true;
					}

					break;
				}
			}				
		}

		return true;	
	}

	/** 
	@param   
	@param   
	@return  
	*/
	bool Fire(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen)
	{
		SEventKey eventkey;
		eventkey._key.wEventID = wEventID;
		eventkey._key.bSrcType = bSrcType;

		// �ȷ�����Դָ���
		eventkey._key.dwSrcID = dwSrcID;
		if(eventkey._key.dwSrcID != 0)
		{
			bool bResult = Fire(eventkey, wEventID, bSrcType, dwSrcID, pszContext, nLen);
			if(!bResult) 
			{
				return false;
			}
		}
		
		// Ȼ����Դָ���
		eventkey._key.dwSrcID = 0;
		bool bResult = Fire(eventkey, wEventID, bSrcType, dwSrcID, pszContext, nLen);
		if(!bResult)
		{
			return false;
		}

		return true;
	}

private:
	/** 
	@param   
	@param   
	@return  
	*/
	bool Fire(SEventKey &eventkey, WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen)
	{
		m_nFireLayerNum++;

		if(m_nFireLayerNum >= FIRE_MAX_LAYERNUM)
		{
			Error("�¼��������Ƿ�����ѭ������ EVENTID = " << wEventID << "SRCTYPE �� " << bSrcType << endl);
			memcpy(NULL, NULL, -1);
			m_nFireLayerNum--;
			return false;
		}

		typename TMAP_SAFESINK::iterator itMap = m_mapSafeSink.find(eventkey);
		if(itMap != m_mapSafeSink.end())
		{
			TLIST_SUBSCIBEINFO * plistSubscibeInfo = &((*itMap).second);
			
			typename TLIST_SUBSCIBEINFO::iterator itList = plistSubscibeInfo->begin();
			for( ; itList != plistSubscibeInfo->end(); )
			{
				SSubscibeInfo * pSubscibeInfo = &(*itList);

				if(pSubscibeInfo->nCallCount >= REF_MAX_LAYERNUM)
				{
					Error("�¼���������ͬһ�¼�ѭ�����ã��������⣡EVENTID = " << wEventID << "���� = " << pSubscibeInfo->szDesc << endl);
					m_nFireLayerNum--;
					return false;
				}

				if(!pSubscibeInfo->bRemoveFlag)
				{					
					bool bResult = false;

					// �Ƿ����汾�������쳣�������⾡�챩¶ [4/21/2011 zgz]
#if  !defined(RELEASEDEBUG) && !defined(_DEBUG)
					try
#endif
					{
						pSubscibeInfo->Add();
						bResult = m_FireEventObject(pSubscibeInfo->pSink, wEventID, bSrcType, dwSrcID, pszContext, nLen);
						pSubscibeInfo->Sub();						
					}
#if  !defined(RELEASEDEBUG) && !defined(_DEBUG)
					catch(...)
					{
						Error("�¼��������Ƿ���EVENTID = " << wEventID << "���� = " << pSubscibeInfo->szDesc << endl);
						return false;
					}
#endif

					if(pSubscibeInfo->bRemoveFlag && pSubscibeInfo->nCallCount == 0)
					{
						itList = plistSubscibeInfo->erase(itList);
					}					
					else
					{
						++itList;
					}

					if(!bResult) 
					{
						m_nFireLayerNum--;
						return false;
					}
				}
				else
				{
					if(pSubscibeInfo->nCallCount == 0)				
					{
						itList = plistSubscibeInfo->erase(itList);
					}
					else
					{
						++itList;
					}
				}
			}
		}

		m_nFireLayerNum--;

		return true;
	}
	
private:
	// �¼����Ͷ���
	TOnEventObject		m_FireEventObject;

	// �¼������б�
	TMAP_SAFESINK		m_mapSafeSink;

	// ���Ͳ���
	int					m_nFireLayerNum;	
};
