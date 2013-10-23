/*******************************************************************
** �ļ���:	HTTP_Requester.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	02/10/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#include "singleton.h"
#include "DNS_Resolver.h"
#include "HTTP_Connection.h"
#include "Handle.h"

#include <string>
#include <list>
#include <map>

/**
@name : ��װHTTP������
@brief: GET��ʽ
*/
class HTTP_Requester : public DNS_Queryer,public SingletonEx<HTTP_Requester>
{
public:
	//////////////////////////////////////////////////////////////////////////
    /**
    @name         : ����HTTP����
    @brief        : ʹ��GET��ʽ
    @param   url  : Ҫ�����url,������������http://www.carfax.com/register.php?username=no1
	@param httpver: Ҫʹ�õ�httpЭ��,Ŀǰ��1.0��1.1
	@param data_rng:Ҫ��������ݶ�,���Ϊ����ָ��
	@param handler: ����http��Ӧ�Ļص��ӿ�,Ϊ�˰�ȫ�����ʹ�þ��,�þ��ָ��HTTP_Response_Handler��ָ��
    @return       :
    */
	bool Request( const std::string & url,HTTP_VERSION httpver,__int64 range_begin,__int64 range_end,handle handler);

	//////////////////////////////////////////////////////////////////////////
	/*********************** DNS_Queryer ************************************/
	virtual void Handle_DNS_Response( const char * szDomain,const char ** ppIPList,unsigned int nIPNum);

	virtual void Handle_DNS_Error( const char * szDomain,DWORD dwErrorCode );

	HTTP_Requester();

	virtual ~HTTP_Requester();

protected:
	//////////////////////////////////////////////////////////////////////////
	struct REQUEST
	{
		std::string    m_ServerHost;      // ����������
		std::string    m_ServerIP;        // ������IP
		unsigned short m_ServerPort;      // �������˿�
		std::string    m_szURL;           // �����URL
		HTTP_VERSION   m_Version;         // ����İ汾��
		__int64        m_RangeBegin;	  // ����ķֿ���Ϣ
		__int64        m_RangeEnd;		  // ����ķֿ���Ϣ
		handle         m_pHandler;        // ��Ӧ������
	};

	typedef std::list<REQUEST> REQUEST_LIST;
	typedef std::map<std::string,REQUEST_LIST> DNS_QUERYING_LIST;

	typedef std::list<HTTP_Connection *> CONNECTION_POOL;

	/**
	@name         : ��URL��ȡ�������� 
	@brief        : ����:url=http://www.carfax.com/register.php?username=aaa ����www.carfax.com
	@param  url   : ����url��ַ
	@param  host  : ����������
	@param  port  : ���ط������˿�
	@param trim_url:���زü������url
	@return       : ���url��ʽ���Ϸ��򷵻�false	*/
	bool  GetURLHostName( const std::string & url,std::string & host,unsigned short & port,std::string & trim_url );

	bool SendHTTPRequest(const REQUEST & request);

protected:
	CONNECTION_POOL              m_ConnectionPool;    // �������ӵķ������б�
	DNS_QUERYING_LIST            m_DNSQueryingList;   // �ȴ�DNS������б�
};

#endif//__HTTP_REQUEST_H__