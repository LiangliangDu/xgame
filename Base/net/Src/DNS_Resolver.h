/*******************************************************************
** �ļ���:	DNS_Resolver.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	02/11/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __DNS_RESOLVER_H__
#define __DNS_RESOLVER_H__

#include "dns.h"
#include "Thread.h"
#include "Reactor.h"
#include "Singleton.h"
using namespace xs;

#include <list>
#include <map>

/**
@name : DNS����� (������ѯ��)
@brief: ��ѯ�����Ĺ������첽��,Ҫ��DNS����������
*/
class DNS_Resolver : public EventHandler,public SingletonEx<DNS_Resolver>
{
public:
	/**
	@name         : ��ѯһ������
	@brief        :
	@param domain : ����ѯ������
	@param queryer: ��ѯ��,���ڲ�ѯ�ɹ����֪ͨ
	@note         : �ڲ�ѯ�����и�ָ����뱣����Ч,�����ָ�뱻�ͷ�,��Ҫ��������Cancel_DNS_Queryȡ����ѯ
	@return       :
	*/
	virtual bool DNS_Query( const std::string & domain,DNS_Queryer * queryer );

	/**
	@name         : ȡ��һ��������ѯ����
	@brief        :
	@param domain : ����ѯ������
	@param queryer: ��ѯ��,���ڲ�ѯ�ɹ����֪ͨ
	@return       :
	*/
	virtual bool Cancel_DNS_Query( const std::string & domain,DNS_Queryer * queryer );

	/**
	@name         : ��Ӧ������ѯ�ɹ�ʱ�������¼�
	*/
	virtual void OnEvent( HANDLE event );


	virtual void Release() { delete this; }

	/**
	@name         : ��ȡ��һ����ѯ����
	@brief        : ��ѯ�߳��ڿ���ʱ����,��Ҫ����
	@param  domain: Ҫ��ѯ���߳�
	@return       : ���û�������˷���false
	*/
    bool GetNextDNSQuery(std::string & domain);

    /**
    @name         : ���DNS���������صĽ��
    @brief        : ��Ϊ����������ѯ�̷߳��ص�����Ҫ����
	@param domain : Ҫ��ѯ������
    @param dwError: ������,��������������
	@param ipset  : ������Ӧ��IP�б�
    @return       :
    */
	void AddDNSResult(const std::string & domain,DWORD dwError,const std::vector<std::string> & ipset);

	bool Create();

	void Close();

	DNS_Resolver() : m_hDNSEvent(0){}

	virtual ~DNS_Resolver() { Close();}

protected:
	struct DNS_Result  // DNS���صĽ��
	{
		DWORD                    m_dwError;
		std::string              m_szDomain;
		std::vector<std::string> m_IPSet;
	};

	struct DNS_Queryer_List
	{
		std::list<DNS_Queryer*>  m_QueryerList;  
		BOOL                     m_bIsQuerying;
		DNS_Queryer_List() : m_bIsQuerying(FALSE){}
	};

	typedef   std::list<DNS_Result>   RESULT_LIST;
    typedef   std::map<std::string,DNS_Result>  HISTORY_LIST;
	typedef   std::map<std::string,DNS_Queryer_List> QUERY_LIST;

	HANDLE       m_hDNSEvent;          // DNS��ѯ�ɹ��������¼�
	RESULT_LIST  m_ResultList;         // ��ѯ����б�
	HISTORY_LIST m_HistoryList;        // ��ѯ��ʷ�б������ظ���ѯ
    QUERY_LIST   m_QueryList;          // ��ѯ�����б�
    Mutex        m_ResultMutex;        // ����б���
	Thread       m_QueryThread;        // ��ѯ�߳�
};

/**
@name : ������ѯ�߳�
@brief: 
*/
class DNS_Query_Thread : public IRunnable
{
public:
	virtual void run();
	virtual void release(){ delete this;}

	DNS_Query_Thread(DNS_Resolver * resolver) : m_pResolver(resolver){}

protected:
	DNS_Resolver   *    m_pResolver;
};

#endif//__DNS_RESOLVER_H__