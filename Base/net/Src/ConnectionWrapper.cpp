/*******************************************************************
** �ļ���:	ConnectionWrapper.cpp 
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

#include "stdafx.h"
#include "ConnectionWrapper.h"
#include "SimplePacker.h"
#include "DataPacker.h"
#include "Proactor.h"

namespace xs{

//////////////////////////////////////////////////////////////////////////
CConnectionWrapper::~CConnectionWrapper()
{
	if ( m_pPacker )
	{
		m_pPacker->Release();
		m_pPacker = 0;
	}
}

void CConnectionWrapper::Release()
{
	m_pRealHandler = 0;
	CConnection::Release();
}

//////////////////////////////////////////////////////////////////////////
bool CConnectionWrapper::Create( SHORT dwBindPort )
{
	if ( !CConnection::Create(dwBindPort))
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CConnectionWrapper::Connect( const char * ip,unsigned short port )
{
	// ������
	if ( isalpha(ip[0]))
	{
		m_RemoteAddr.sin_port = htons( port );
		return DNS_Query(ip,this);
	}else
	{
		return CConnection::Connect(ip,port);
	}
}

//////////////////////////////////////////////////////////////////////////
bool CConnectionWrapper::SendData( const char * pData,DWORD dwDataLen,DWORD dwFlag )
{
	char * pBuffer = 0;

	if ( dwFlag & NO_COPY )
	{
		pBuffer = (char *)pData;
	}else
	{
		pBuffer = (char *)AllocateAsynIoBuffer(dwDataLen);   // ����ڴ�Ҫ�����ͳɹ��Ż���Result����������
		memcpy(pBuffer,pData,dwDataLen);
	}

	if ( m_pPacker )
	{
		std::vector<AsynIoBuffer> packed;
		m_pPacker->Pack(pBuffer,dwDataLen,packed);
		assert(!packed.empty());
		assert(m_pSocket);

		// ���������̷߳���
		for ( size_t i=0;i<packed.size();++i )
		{
			//SenderThread::getInstance().RequestSendData(m_pSocket,this,m_hSafeHandle,packed[i]);
			SenderThread::getInstance().RequestSendData(m_pSocket,this,packed[i]);
		}
		return true;
	}else
	{
		AsynIoBuffer buff;
		buff.buf = pBuffer;
		buff.len = dwDataLen;

		assert(m_pSocket);

		//SenderThread::getInstance().RequestSendData(m_pSocket,this,m_hSafeHandle,buff);
		SenderThread::getInstance().RequestSendData(m_pSocket,this,buff);
		return true;
	}
}

//////////////////////////////////////////////////////////////////////////
void CConnectionWrapper::SetEventHandler( IConnectionEventHandler * pHandler )
{
	m_pHandler = this;
	m_pRealHandler = pHandler;
}

//////////////////////////////////////////////////////////////////////////
void CConnectionWrapper::OnAccept( IConnection * pIncomingConn,IConnectionEventHandler ** ppHandler )
{
	if ( m_pRealHandler )
	{
		m_pRealHandler->OnAccept(pIncomingConn,ppHandler);
	}
}

//////////////////////////////////////////////////////////////////////////
void CConnectionWrapper::OnConnected( IConnection * conn )
{
	if ( m_pRealHandler )
	{
		m_pRealHandler->OnConnected(conn);
	}
}

//////////////////////////////////////////////////////////////////////////
void CConnectionWrapper::OnDisconnected( IConnection * conn,DWORD reason )
{
	if ( m_pRealHandler )
	{
		m_pRealHandler->OnDisconnected(conn,reason);
	}
}

//////////////////////////////////////////////////////////////////////////
void CConnectionWrapper::OnError( IConnection * conn,DWORD dwErrorCode )
{
	if ( m_pRealHandler )
	{
		m_pRealHandler->OnError(conn,dwErrorCode);
	}	
}

//////////////////////////////////////////////////////////////////////////
void CConnectionWrapper::OnRecv( IConnection * conn,LPVOID pData,DWORD dwDataLen )
{
	if ( m_pRealHandler==0 )
		return;
	
	if ( m_pPacker )
	{
		std::vector<AsynIoBuffer> unpacked;
		if ( !m_pPacker->UnPack((const char *)pData,dwDataLen,unpacked) )
		{
			m_pRealHandler->OnDisconnected(this,CONN_ERROR_PACKER);
			return;
		}

		// ע��: Ӧ�ò�����ڴ���OnRecv�Ĺ�����Release�Լ�
		for (size_t i=0;i<unpacked.size() && m_pRealHandler;++i )
		{
			AsynIoBuffer & buff = unpacked[i];
			m_pRealHandler->OnRecv(conn,buff.buf,buff.len);
		}
	}else
	{
		m_pRealHandler->OnRecv(conn,pData,dwDataLen);
	}
}

//////////////////////////////////////////////////////////////////////////
CConnection * CConnectionWrapper::Clone()
{
	CConnectionWrapper * conn = new CConnectionWrapper;
	if ( m_pPacker )
	{
		IPacker * packer = m_pPacker->Clone();
		conn->SetPacker(packer);
	}

	return conn;
}

//////////////////////////////////////////////////////////////////////////
void CConnectionWrapper::Handle_DNS_Response( const char * szDomain,const char ** ppIPList,unsigned int nIPNum)
{
	CConnection::Connect(ppIPList[0],ntohs(m_RemoteAddr.sin_port));
}

void CConnectionWrapper::Handle_DNS_Error( const char * szDomain,DWORD dwErrorCode )
{
	assert ( m_pSocket );

	AsynIoResult * result = m_pSocket->CreateAsynIoResult(ASYN_IO_CONNECT,this);
	assert(result);
	result->SetErrorCode(CONN_ERROR_DNS);

	GetAsynIoProactor()->PostCompletion(result);
}

void  CConnectionWrapper::ChangePacker(DWORD CryptId,uchar *key,DWORD keylen) 
{
	IPacker* m_pPacker=new DataPacker(CryptId,key,keylen);
	assert(m_pPacker);
	SetPacker(m_pPacker);
}

void CConnectionWrapper::SetPacker(IPacker * packer) 
{ 
	if (m_pPacker)
	{
		delete m_pPacker;
		m_pPacker=NULL;
	}
	m_pPacker = packer; 
}


};