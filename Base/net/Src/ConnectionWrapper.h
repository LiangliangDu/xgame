/*******************************************************************
** �ļ���:	ConnectionWrapper.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/29/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __NET_CONNECTION_WRAPPER_H__
#define __NET_CONNECTION_WRAPPER_H__

#include "Connection.h"
#include "IPacker.h"
#include "SenderThread.h"
#include "dns.h"

namespace xs{

	/**
	@name : Connection��װ��
	@brief: ��Connection�ٰ�װһ��,����֧��һЩ��չ����,����:
			1.�������
			2.���ܹ���
			3.֧������
	*/
	class CConnectionWrapper : public CConnection,public IConnectionEventHandler,public DNS_Queryer
	{
	public:
		virtual bool SendData( const char * pData,DWORD dwDataLen,DWORD dwFlag );

		virtual void SetEventHandler( IConnectionEventHandler * pHandler );
	
		virtual bool Connect( const char * ip,unsigned short port );

		virtual void OnAccept( IConnection * pIncomingConn,IConnectionEventHandler ** ppHandler );

		virtual void OnConnected( IConnection * conn );

		virtual void OnDisconnected( IConnection * conn,DWORD reason );

		virtual void OnRecv( IConnection * conn,LPVOID pData,DWORD dwDataLen );

		virtual void OnError( IConnection * conn,DWORD dwErrorCode );

		virtual void Release();

		virtual void Handle_DNS_Response( const char * szDomain,const char ** ppIPList,unsigned int nIPNum);

		virtual void Handle_DNS_Error( const char * szDomain,DWORD dwErrorCode );

		virtual bool Create( SHORT dwBindPort );

		// �����������
		void SetPacker(IPacker * packer);

		virtual void  ChangePacker(DWORD CryptId,uchar *key,DWORD keylen) ;

		/**
		@name         : ��¡һ�����Լ�ͬ�����͵�����,Acceptʱ��Ҫ�õ�
		@brief        : ��Ҫ��¡����Ϣ����: Socketѡ������,�����ʽ,���ܷ�ʽ��
		@return       :
		*/
		virtual CConnection * Clone();

		CConnectionWrapper() : m_pRealHandler(0),m_pPacker(0),m_dwSenderID(0){}
	private:
		virtual ~CConnectionWrapper();

	protected:
		IConnectionEventHandler  *       m_pRealHandler; // �û������Ĵ���ӿ�
		IPacker                  *       m_pPacker;      // ����ӿ�
		DWORD                            m_dwSenderID;   // ����ID,�ɷ����̷߳���
	};
};

#endif//__NET_CONNECTION_WRAPPER_H__