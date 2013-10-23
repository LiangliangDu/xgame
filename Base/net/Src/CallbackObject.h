/*******************************************************************
** �ļ���:	CallbackObject.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	03/05/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __CALLBACK_OBJECT_H__
#define __CALLBACK_OBJECT_H__

#include "Handle.h"
#include "CallbackDispatcher.h"
#include "Connection.h"
#include "UDPSocket.h"
#include "AsynFileWrapper.h"

using namespace xs;

/**
@name : ֪ͨAccept�ɹ�
@brief:
*/
class Callback_Accept : public CallbackDispatcher::CallbackObject
{
public:
	virtual void run()
	{
		CConnection * conn = m_hConnection;//(CConnection *)getHandleData(m_hConnection);
		CConnection * incoming = m_hIncomingConn;//(CConnection *)getHandleData(m_hIncomingConn);

		if ( conn && incoming )
		{
			IConnectionEventHandler * handler = conn->GetEventHandler();
			if ( handler )
			{
				IConnectionEventHandler * pIncomingHandler = 0;
				handler->OnAccept(incoming,&pIncomingHandler);
				assert(pIncomingHandler);
				incoming->SetEventHandler(pIncomingHandler);
				incoming->RecvNextPackage();  // Ҫ��Handler���ú��˲����հ�
			}

			//m_pResult->GetAsynDevice()->DeleteAsynIoResult(m_pResult);
			conn->GetSocketDevice()->DeleteAsynIoResult(m_pResult);
		}
	}

	virtual void release()
	{	
		delete this;
	}

	Callback_Accept(CConnection * pListenConn,CConnection * pIncomingConn,AsynIoResult * pResult)
	{
		m_hConnection = pListenConn;//pListenConn->GetSafeHandle();
		m_hIncomingConn = pIncomingConn;//pIncomingConn->GetSafeHandle();
		m_pResult = pResult;
	}

protected:
	//crr �����װ������һ�٣�����̰߳�ȫ������ʹ��
	//handle        m_hConnection;
	//handle        m_hIncomingConn;

	CConnection*        m_hConnection;
	CConnection*        m_hIncomingConn;
	
	AsynIoResult   * m_pResult;
};

/**
@name : ֪ͨ���ӳɹ�
@brief:
*/
class Callback_Connect : public CallbackDispatcher::CallbackObject
{
public:
	Callback_Connect(CConnection * pConn,AsynIoResult * result)
	{
		m_hConnection = pConn;//pConn->GetSafeHandle();
		m_pResult = result;
	}

	virtual void run()
	{
		CConnection * conn = m_hConnection;//(CConnection *)getHandleData(m_hConnection);
		if ( conn )
		{

			IConnectionEventHandler * handler = conn->GetEventHandler();
			if ( handler )
			{
				handler->OnConnected(conn);
			}
			
			conn->GetSocketDevice()->DeleteAsynIoResult(m_pResult);
		}
	}

	virtual void release()
	{
		delete this;
	}

protected:
	//crr �����װ������һ�٣�����̰߳�ȫ������ʹ��
	//handle        m_hConnection;
	CConnection*    m_hConnection;

	AsynIoResult   * m_pResult;
};

/**
@name : ֪ͨ�յ�����
@brief:
*/
class Callback_Recv : public CallbackDispatcher::CallbackObject
{
public:
	Callback_Recv(CConnection * pConn,LPVOID pData,DWORD dwDataLen,AsynIoResult   * pResult) : m_pData(pData),m_dwDataLen(dwDataLen)
	{
		m_hConnection = pConn;//pConn->GetSafeHandle();
		m_pResult = pResult;
	}

	virtual void run()
	{
		CConnection * conn = m_hConnection;//(CConnection *)getHandleData(m_hConnection);
		if ( conn )
		{

			IConnectionEventHandler * handler = conn->GetEventHandler();
			if ( handler )
			{
				//�����������
				DWORD dwRestDataLen = m_dwDataLen;
				LPVOID pCurPacket = m_pData;


				while (dwRestDataLen > 0)
				{
					//handler->OnRecv(conn,m_pData,m_dwDataLen);
					//Ĭ�ϲ��õ�SimplePacker ���ڿ�ͷ�����ֽڼ�¼���η������ݵĴ�С
					
					if (dwRestDataLen < sizeof WORD)
					{
						ErrorLn("Callback_Recv��δ�������� δ����simple packer��ͷ2���ֽ�");
						break;
					}
					WORD wCurPacketSize = *(WORD*)pCurPacket + sizeof WORD;	
					if (dwRestDataLen < wCurPacketSize)
					{
						ErrorLn("Callback_Recv��δ�������� ��С< " << wCurPacketSize);
						break;
					}
					
					handler->OnRecv(conn,pCurPacket,wCurPacketSize);
					
					pCurPacket = (LPVOID)((char*)pCurPacket + wCurPacketSize);
					dwRestDataLen -= wCurPacketSize;

				}

				
			}

			conn->GetSocketDevice()->DeleteAsynIoResult(m_pResult);
		}

		DeallocateAsynIoBuffer(m_pData);     // �ͷ�result������ڴ�

	}

	virtual void release()
	{
		delete this;
	}

protected:
	//handle        m_hConnection;
	CConnection*	m_hConnection;
	LPVOID        m_pData;
	DWORD         m_dwDataLen;

	AsynIoResult   * m_pResult;
};

/**
@name : ֪ͨUDP�յ����ݰ�
@brief:
*/
class Callback_RecvFrom : public CallbackDispatcher::CallbackObject
{
public:
	Callback_RecvFrom(UDPSocket * sock,sockaddr_in * addr,LPVOID pData,DWORD dwDataLen) : m_pData(pData),m_dwDataLen(dwDataLen)
	{
		m_hSocket = sock;//sock->GetSafeHandle();
		m_addr = addr;
	}

	virtual void run()
	{
		UDPSocket * sock = m_hSocket;//(UDPSocket *)getHandleData(m_hSocket);
		if ( sock )
		{
			IUDPHandler * handler = sock->GetEventHandler();
			if ( handler )
			{
				handler->OnRecv(sock,m_pData,m_dwDataLen,inet_ntoa(m_addr->sin_addr),ntohs(m_addr->sin_port));
			}
		}

		DeallocateAsynIoBuffer(m_addr);     // �ͷ�result������ڴ�,ע��result������ڴ���ʵ������addrһ������,�������ﴫ��addr��ָ��
	}

	virtual void release()
	{
		delete this;
	}

protected:
	//handle        m_hSocket;
	UDPSocket *		m_hSocket;
	sockaddr_in * m_addr;
	LPVOID        m_pData;
	DWORD         m_dwDataLen;
};

/**
@name : ֪ͨTCP���Ӵ���
@brief:
*/
class Callback_TCP_Error : public CallbackDispatcher::CallbackObject
{
public:
	Callback_TCP_Error(CConnection * pConn,DWORD dwErrorCode, AsynIoResult   * pResult) : m_dwErrorCode(dwErrorCode)
	{
		m_hConnection = pConn;//pConn->GetSafeHandle();
		m_pResult = pResult;
	}

	virtual void run()
	{
		CConnection * conn = m_hConnection;//(CConnection *)getHandleData(m_hConnection);
		if ( conn )
		{
			
			IConnectionEventHandler * handler = conn->GetEventHandler();
			if ( handler )
			{
				handler->OnError(conn,m_dwErrorCode);
			}
			conn->GetSocketDevice()->DeleteAsynIoResult(m_pResult);
		}		
	}

	virtual void release()
	{
		delete this;
	}

protected:
	//handle        m_hConnection;
	CConnection*	m_hConnection;
	DWORD         m_dwErrorCode;

	AsynIoResult   * m_pResult;
};

/**
@name : ֪ͨUDP���Ӵ���
@brief:
*/
class Callback_UDP_Error : public CallbackDispatcher::CallbackObject
{
public:
	Callback_UDP_Error(UDPSocket * sock,DWORD dwErrorCode) : m_dwErrorCode(dwErrorCode)
	{
		m_hSocket = sock->GetSafeHandle();
	}

	virtual void run()
	{
		UDPSocket * sock = (UDPSocket *)getHandleData(m_hSocket);
		if ( sock )
		{
			IUDPHandler * handler = sock->GetEventHandler();
			if ( handler )
			{
				handler->OnError(sock,m_dwErrorCode);
			}
		}
	}

	virtual void release()
	{
		delete this;
	}

protected:
	handle        m_hSocket;
	DWORD         m_dwErrorCode;
};

/**
@name : �ļ���ȡ�ɹ�
@brief:
*/
class Callback_Read : public CallbackDispatcher::CallbackObject
{
public:
	Callback_Read(AsynFileWrapper * file,unsigned __int64 pos,LPVOID pData,DWORD dwDataLen) : m_Position(pos),m_pData(pData),m_dwDataLen(dwDataLen)
	{
		m_hFile = file->GetSafeHandle();
	}

	virtual void run()
	{
		AsynFileWrapper * file = (AsynFileWrapper *)getHandleData(m_hFile);
		if ( file )
		{
			IAsynFileHandler * handler = file->GetEventHandler();
			if ( handler )
			{
				handler->HandleReadSuccess(m_Position,(const char *)m_pData,m_dwDataLen);
			}
		}

		DeallocateAsynIoBuffer(m_pData);     // �ͷ�result������ڴ�
	}

	virtual void release()
	{
		delete this;
	}

protected:
	handle        m_hFile;
	LPVOID        m_pData;
	DWORD         m_dwDataLen;
	unsigned __int64 m_Position;
};

/**
@name : �ļ�����
@brief:
*/
class Callback_Read_Error : public CallbackDispatcher::CallbackObject
{
public:
	Callback_Read_Error(AsynFileWrapper * file,DWORD dwErrorCode,unsigned __int64 pos,DWORD len) : m_dwReadLen(len),m_Position(pos),m_dwErrorCode(dwErrorCode)
	{
		m_hFile = file->GetSafeHandle();
	}

	virtual void run()
	{
		AsynFileWrapper * file = (AsynFileWrapper *)getHandleData(m_hFile);
		if ( file )
		{
			IAsynFileHandler * handler = file->GetEventHandler();
			if ( handler )
			{
				handler->HandleReadFailed(m_dwErrorCode,m_Position,m_dwReadLen);
			}
		}
	}

	virtual void release()
	{
		delete this;
	}

protected:
	handle        m_hFile;
	DWORD         m_dwErrorCode;
	DWORD         m_dwReadLen;
	unsigned __int64 m_Position;
};

/**
@name : �ļ�д�����
@brief:
*/
class Callback_Write : public CallbackDispatcher::CallbackObject
{
public:
	Callback_Write(AsynFileWrapper * file,DWORD dwError,unsigned __int64 pos,DWORD dwDataLen) : m_Position(pos),m_dwError(dwError),m_dwDataLen(dwDataLen)
	{
		m_hFile = file->GetSafeHandle();
	}

	virtual void run()
	{
		AsynFileWrapper * file = (AsynFileWrapper *)getHandleData(m_hFile);
		if ( file )
		{
			IAsynFileHandler * handler = file->GetEventHandler();
			if ( handler )
			{
				if ( m_dwError==ERROR_SUCCESS )
				{
					handler->HandleWriteSuccess(m_Position,m_dwDataLen);
				}else
				{
					handler->HandleWriteFailed(m_dwError,m_Position,m_dwDataLen);
				}
			}
		}
	}

	virtual void release()
	{
		delete this;
	}

protected:
	handle        m_hFile;
	DWORD         m_dwError;
	DWORD         m_dwDataLen;
	unsigned __int64 m_Position;
};

#endif//__CALLBACK_OBJECT_H__