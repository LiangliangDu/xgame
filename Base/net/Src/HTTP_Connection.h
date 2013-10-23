/*******************************************************************
** �ļ���:	HTTP_Connection.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	02/12/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __HTTP_CONNECTION_H__
#define __HTTP_CONNECTION_H__

#include "net.h"
#include "Handle.h"
using namespace xs;

#include <list>

#include "http.h"

/**
@name : ά��һ��HTTP����
@brief: ά������һ���߼�:
        �����1.0�汾��HTTPЭ�飬ÿ�η���һ����������½���һ������
        �����1.1�汾��HTTPЭ�飬ͬһ�������Ͽ��Է��Ͷ������
*/
class HTTP_Connection : public IConnectionEventHandler
{
public:
	//////////////////////////////////////////////////////////////////////////
	virtual void OnAccept( IConnection * pIncomingConn,IConnectionEventHandler ** ppHandler );

	virtual void OnConnected( IConnection * conn );

	virtual void OnDisconnected( IConnection * conn,DWORD reason );

	virtual void OnRecv( IConnection * conn,LPVOID pData,DWORD dwDataLen );

	virtual void OnError( IConnection * conn,DWORD dwErrorCode );

	const std::string & GetServerIP() const { return m_ip;}

	unsigned short GetServerPort() const { return m_port;}

	HTTP_VERSION GetServerVersion() const { return m_version; }

	bool Connect( const std::string & ip,unsigned short port,HTTP_VERSION ver);

	bool Request( const std::string & url,const std::string & host,__int64 range_begin,__int64 range_end,handle hander);

	void Close();

	HTTP_Connection() : m_port(0),
		                m_version(HTTP_VER_1_1),
						m_bConnected(false),
						m_pConnection(0),
						m_bServerActive(false),
						m_pContentBuffer(0),
						m_nContentLen(0),
						m_nCurrentLen(0),
						m_pHeaderBuffer(0),
						m_nHeaderLen(0)
	{
	}

	virtual ~HTTP_Connection()
	{
		Close();
	}

protected:
	/**
	@name         : ������û���͵�����ȫ�����ͳ�ȥ
	@brief        :
	@param resend : �Ƿ�û�ɹ����ص����·���
	@return       :
	*/
	void SendAllRequest(bool resend);

	/**
	@name         : ����HTTP��Ӧ״̬��
	@brief        : ͨ��Ϊ HTTP/1.1 200 OK
	*/
	bool Handle_Response_State(char * state_line,DWORD len );

protected:
	//////////////////////////////////////////////////////////////////////////
	struct REQUEST
	{
		std::string             m_szServerHost; // ������������
		std::string             m_szURL;		// �����URL
		__int64                 m_RangeBegin;	// ����ķֿ���Ϣ
		__int64                 m_RangeEnd;		// ����ķֿ���Ϣ
		handle                  m_pHander;		// ��Ӧ������
		bool                    m_bSended;		// �������Ƿ��Ѿ�����
	};
	typedef std::list<REQUEST> REQUEST_LIST;

	std::string              m_ip;                // ������IP
	unsigned short           m_port;              // �������˿�
	HTTP_VERSION             m_version;           // HTTP�汾��
	IConnection      *       m_pConnection;       // ��ǰ�ͷ��������ֵ�����
	REQUEST_LIST             m_RequestList;       // �����б�
	bool                     m_bConnected;        // �Ƿ�������
	bool                     m_bServerActive;     // �������Ƿ������
	HTTP_Response_Header     m_HttpHeader;        // ���յ���HTTPͷ
	char             *       m_pHeaderBuffer;     // HTTPͷ������
	int                      m_nHeaderLen;        // �����httpͷ����
	char             *       m_pContentBuffer;    // ��ҳ���ݻ�����
	int                      m_nContentLen;       // ��������
	int                      m_nCurrentLen;       // �����յ��ĳ���
};

#endif//__HTTP_CONNECTION_H__