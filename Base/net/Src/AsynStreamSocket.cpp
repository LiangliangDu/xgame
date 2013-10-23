/*******************************************************************
** �ļ���:	AsynStreamSocket.cpp 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/24/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#include "stdafx.h"
#include <assert.h>
#include "AsynStreamSocket.h"
#include "AsynIoResult.h"
#include "Proactor.h"
#include "Reactor.h"
#include "AsynIoResultImp.h"
#include "SafeReleaseHelper.h"
#include "Connection.h"

#ifdef WIN32

#include <Mswsock.h>

namespace xs{

//////////////////////////////////////////////////////////////////////////
	bool AsynStreamSocket::Create(xs::CConnection* pConn)
{	
	m_hSocketHandle = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if ( INVALID_SOCKET==m_hSocketHandle )
	{
		assert(false);  // ���������Ϣ
		return false;
	}

	m_pReader = new AsynStreamSocket_Reader(this);
	m_pWriter = new AsynStreamSocket_Writer(this);
	m_pAcceptor = new AsynStreamSocket_Acceptor(this);
	m_pConnector = new AsynStreamSocket_Connector(this);
	//InfoLn(" AsynStreamSocket::Create m_pConnector " << (DWORD)m_pConnector);
	m_pConnection = pConn;
	GetAsynIoProactor()->RegisterDevice(this);
	
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool AsynStreamSocket::Bind( unsigned short port )
{
	sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons( port );
	sock_addr.sin_addr.s_addr = htonl( INADDR_ANY );
	int ret = ::bind( m_hSocketHandle, (const sockaddr*)&sock_addr, sizeof(sockaddr_in) );
	if( ret == SOCKET_ERROR )
	{
		DWORD dwError = GetLastError();
		assert(false);  // ���������Ϣ
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool AsynStreamSocket::Listen()
{
	if ( ::listen(m_hSocketHandle,SOMAXCONN)==SOCKET_ERROR )
	{
		assert(false);  // ���������Ϣ
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
AsynIoResult * AsynStreamSocket::CreateAsynIoResult(int iotype,AsynIoHandler * handler)
{
	ResGuard<Mutex>  guard(m_Locker);

	//socket �Ѿ��ر��ˣ�����NULL��Ҫ�ٶ����socket����
	if (INVALID_SOCKET == m_hSocketHandle)
	{
		return NULL;
	}

	AsynIoResult * result = 0;

	switch(iotype)
	{
	case ASYN_IO_ACCEPT:
		result = new AsynStreamSocketAcceptResult(handler);
		break;
	default:
		result = new AsynIoResultImp((AsynIoType)iotype,handler);
		break;
	}

	m_pendingList.insert(result);
	result->SetAsynDevice(this);

	return result;
}

//////////////////////////////////////////////////////////////////////////
void AsynStreamSocket::DeleteAsynIoResult(AsynIoResult * result)
{
	bool bRelease = false;
	do{
			ResGuard<Mutex>  guard(m_Locker);

			RESULT_LIST::iterator it = m_pendingList.find(result);
			assert(it!=m_pendingList.end());
			
			m_pendingList.erase(it);

			delete (AsynIoResultImp *)result;

			if (m_bWaitingClosed && m_pendingList.empty() && 0 == m_iSendThreadRef)
			{
				bRelease = true;
			}
	
	}while(0);
	if (bRelease)
	{
		//InfoLn("DeleteAsynIoResult release socket ok!");
		if (NULL != m_pConnection)
		{
			delete m_pConnection;
		}
		delete this;
	}
}

//////////////////////////////////////////////////////////////////////////
bool AsynStreamSocket::Close()
{
	if ( m_hSocketHandle!=INVALID_SOCKET )
	{
		::closesocket(m_hSocketHandle);
		m_hSocketHandle = INVALID_SOCKET;
	}
	
	assert(m_pendingList.empty());

	safeDelete(m_pReader);
	safeDelete(m_pWriter);
	safeDelete(m_pAcceptor);

	if(m_pConnector)
	{
		//crr mod ��Ϊ Connector ��connect��ʱ����Ӧ���߳�ע�����¼��������Լ�thisָ����Ϊhandler
		//ֱ���ͷ�m_pConnector ������Ƿ�, ��ΪSafeRelease

		//TraceLn("AsynStreamSocket::Close()  " << (DWORD)m_pConnector);

		// ���͹���������Ҫǿתһ��
		//delete (AsynStreamSocket_Connector*)m_pConnector;
		((AsynStreamSocket_Connector*)m_pConnector)->SafeRelease();
		m_pConnector = 0;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
#if 0
void AsynStreamSocket::Release()
{
	while(1)
	{
		// �����и��ݾ�,����ʹ�õ���������
		// ��guard��ʱ�����͹�֮��ͻ����m_Locker����
		// ���ǵ�ִ�е������delete thisʱm_Locker�Ѿ��͹���
		// ����guard�͹�ʱ������ڴ汻�ƻ�
		ResGuard<Mutex>  guard(m_Locker);

		if ( m_hSocketHandle!=INVALID_SOCKET )
		{
			RESULT_LIST::iterator it = m_pendingList.begin();
			for ( ;it!=m_pendingList.end();++it )
			{
				AsynIoResult * result = (*it);
				result->SetHandler(&SafeReleaseHelper::getInstance());
			}

			((AsynStreamSocket_Connector*)m_pConnector)->cancel();

			::closesocket(m_hSocketHandle);
			m_hSocketHandle = INVALID_SOCKET;
		}

		if ( !m_pendingList.empty())
		{
			TraceLn("Delay release socket!");
			SafeReleaseHelper::getInstance().ReleaseAsynIoDevice(this);
			return;
		}

		break;
	}

	TraceLn("release socket ok!");
	delete this;
}
#else
void AsynStreamSocket::Release()
{
	//crr mod ��ΪConnection ��AsynStreamSocket::CreateAsynIoResult��AsynIoHandler�������ɶ˿��߳������˱�Connectionָ��
	//���޸ı�Connection���ͷ�ʱ���� ��m_pSocket ��pendinglistΪ��,��m_iSendThreadRef ==0
	bool bRelease = false;
	do{
		ResGuard<Mutex>  guard(m_Locker);

		if ( m_hSocketHandle!=INVALID_SOCKET )
		{
			::closesocket(m_hSocketHandle);
			m_hSocketHandle = INVALID_SOCKET;
		}

		if ( !m_pendingList.empty() || m_iSendThreadRef != 0)
		{
			m_bWaitingClosed = true;
			//TraceLn("Delay release socket!");
			//SafeReleaseHelper::getInstance().ReleaseAsynIoDevice(this);
			return;
		}
		else
		{
			bRelease = true;
		}
	}while(0);

		if (bRelease)
		{
			InfoLn("AsynStreamSocket::Release release socket ok!");
			//�������������ͷ�this ���ͷ�m_pConnection
			CConnection	* pConnection = m_pConnection;

			delete this;
			
			if (NULL != pConnection)
			{
				delete pConnection;
			}
		}
}

bool AsynStreamSocket::IncreaseSendRef(void) 
{
	ResGuard<Mutex>  guard(m_Locker);
	if (m_bWaitingClosed)
	{
		return false;
	}
	++m_iSendThreadRef;
	return true;
}
void AsynStreamSocket::DecreaseSendRef(int iCount)
{
	bool bRelease = false;
	do 
	{
		ResGuard<Mutex>  guard(m_Locker);
		m_iSendThreadRef -= iCount;

		if (m_bWaitingClosed && m_pendingList.empty() && 0 == m_iSendThreadRef)
		{
			bRelease = true;
		}
	} while (0);

	if (bRelease)
	{
		InfoLn("DecreaseSendRef release socket ok!");
		if (NULL != m_pConnection)
		{
			delete m_pConnection;
		}
		delete this;
	}
}
#endif

//////////////////////////////////////////////////////////////////////////
bool AsynStreamSocket_Reader::read(DWORD expect_bytes,AsynIoHandler * handler)
{
	AsynIoResult * result = m_pDevice->CreateAsynIoResult(ASYN_IO_READ,handler);
	//socket �Ѿ��ر�
	if (NULL == result)
	{
		return false;
	}
	result->PrepareBuffer(expect_bytes);

	DWORD dwTransferredBytes = 0;
	DWORD dwFlag = 0;

	int ret = ::WSARecv((SOCKET)m_pDevice->GetHandle(),(LPWSABUF)result->GetBufferList(),result->GetBufferCount(),&dwTransferredBytes,&dwFlag,result,0);

	if ( ret==SOCKET_ERROR )
	{
		DWORD error_code = ::WSAGetLastError();
		if ( error_code==WSA_IO_PENDING )
			return true;

		ErrorLn("Recv Stream Data Failed! Error Code = " << error_code << "\r\n");
		result->SetErrorCode(error_code);
		GetAsynIoProactor()->PostCompletion(result);
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
//ĳ��tcp��û�н�������������ʣ�µ�����
bool AsynStreamSocket_Reader::read(DWORD expect_bytes,AsynIoHandler * handler, LPVOID pRecieved, DWORD dwRecievedLen, DWORD dwRestLen)
{
	AsynIoResult * result = m_pDevice->CreateAsynIoResult(ASYN_IO_READ,handler);
	//socket �Ѿ��ر�
	if (NULL == result)
	{
		return false;
	}
	result->PrepareBuffer(expect_bytes, pRecieved, dwRecievedLen, dwRestLen);
	AsynIoBuffer * pBuff = result->GetBufferList();
	//PrepareBuffer�Ѿ����յ��������ȱ������������ڴ�Ŀ�ͷλ��

	AsynIoBuffer RestBuff;
	RestBuff.buf = pBuff->buf + dwRecievedLen;
	RestBuff.len = pBuff->len - dwRecievedLen;

	DWORD dwTransferredBytes = 0;
	DWORD dwFlag = 0;

	int ret = ::WSARecv((SOCKET)m_pDevice->GetHandle(),(LPWSABUF)&RestBuff, 1,&dwTransferredBytes,&dwFlag,result,0);

	if ( ret==SOCKET_ERROR )
	{
		DWORD error_code = ::WSAGetLastError();
		if ( error_code==WSA_IO_PENDING )
			return true;

		ErrorLn("Recv Stream Data Failed! Error Code = " << error_code << "\r\n");
		result->SetErrorCode(error_code);
		GetAsynIoProactor()->PostCompletion(result);
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool AsynStreamSocket_Writer::write(const char * data,DWORD len,AsynIoHandler * handler)
{
	if ( (SOCKET)m_pDevice->GetHandle()==INVALID_SOCKET )
	{
		return false;
	}

	AsynIoResult * result =m_pDevice->CreateAsynIoResult(ASYN_IO_WRITE,handler);
	//socket �Ѿ��ر�
	if (NULL == result)
	{
		return false;
	}
	result->PrepareBuffer(len);
	
	LPWSABUF sendBuf = (LPWSABUF)result->GetBufferList();
	memcpy(sendBuf->buf,data,len);

	DWORD dwTransferredBytes = 0;
	DWORD dwFlag = 0;

	int ret = ::WSASend((SOCKET)m_pDevice->GetHandle(),sendBuf,1,&dwTransferredBytes,dwFlag,result,0);

	if ( ret==SOCKET_ERROR )
	{
		DWORD error_code = ::WSAGetLastError();
		if ( error_code==WSA_IO_PENDING )
			return true;

		Error("Send Stream Data Failed! Error Code = " << error_code << "\r\n");
		result->SetErrorCode(error_code);
		GetAsynIoProactor()->PostCompletion(result);
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool AsynStreamSocket_Writer::writeEx( AsynIoBuffer * pBuffList,DWORD dwBuffCount,AsynIoHandler * handler)
{
	if ( (SOCKET)m_pDevice->GetHandle()==INVALID_SOCKET )
	{
		return false;
	}

	
	AsynIoResult * result =m_pDevice->CreateAsynIoResult(ASYN_IO_WRITE,handler);
	//socket �Ѿ��ر�
	if (NULL == result)
	{
		return false;
	}
	result->SetBuffer(pBuffList,dwBuffCount);

	LPWSABUF sendBuf = (LPWSABUF)result->GetBufferList();

	DWORD dwTransferredBytes = 0;
	DWORD dwFlag = 0;

	int ret = ::WSASend((SOCKET)m_pDevice->GetHandle(),sendBuf,result->GetBufferCount(),&dwTransferredBytes,dwFlag,result,0);

	if ( ret==SOCKET_ERROR )
	{
		DWORD error_code = ::WSAGetLastError();
		if ( error_code==WSA_IO_PENDING )
			return true;

		//Error("Send Stream Datas Failed! Error Code = " << error_code << "\r\n");
		InfoLn("Send Stream Datas Failed! Error Code = " << error_code << "\r\n");
		result->SetErrorCode(error_code);
		GetAsynIoProactor()->PostCompletion(result);
		return false;
	}

	return true;		
}

//////////////////////////////////////////////////////////////////////////
bool AsynStreamSocket_Acceptor::accept(AsynIoHandler * handler)
{
	//�����û�������ȼ���һ��
	if ( m_bListen==false)
	{
		((AsynStreamSocket*)m_pDevice)->Listen();
		m_bListen = true;
	}

	AsynStreamSocketAcceptResult * result = (AsynStreamSocketAcceptResult*)m_pDevice->CreateAsynIoResult(ASYN_IO_ACCEPT,handler);
	//socket �Ѿ��ر�
	if (NULL == result)
	{
		return false;
	}
	//���յ�������ָ�����Buffer�ĺ���
	//��Buff������ = �յ��ĵ�һ������ + �Լ��ĵ�ַ + �Է��ĵ�ַ + ��Socketָ��
	AsynStreamSocket * accept_socket = new AsynStreamSocket;
	if ( !accept_socket->Create(NULL) )
	{
		assert(false); // ������
		return false;
	}

	result->SetIncomingSocket(accept_socket);

	DWORD dwTransferredBytes = 0;

	//@Warning : �������ÿ�ε��ö����ѯ������ַ,Ч�ʱȽϵ�.���������
	//         : 1.��̬����mswsock.lib
	//         : 2.�Ѻ���ָ�뱣�����ڡ�ָ���÷���WSAIoctl(SIO_GET_EXTENSION_FUNCTION_POINTER)
	//@Warning : AcceptEx��ͬʱ���Խ��յ�һ������,������Ҫ��ֹֻ���Ӳ������ݵĹ���
	//@Warning : �������������������յ�������+���ص�ַ+Զ�̵�ַ
	//@Warning : Ϊ��Ӧ���ģ����,��Ҫͬʱ��֤�ж��Accept�����ڵȴ�,���Խ���FD_ACCEPT�¼���֪���ӽ�ȱ���
	BOOL ret = ::AcceptEx((SOCKET)m_pDevice->GetHandle(),
		                  (SOCKET)accept_socket->GetHandle(),
						  result->GetAcceptBuffer(),
						  0,
						  AsynStreamSocketAcceptResult::SOCKET_ADDRESS_LEN,
						  AsynStreamSocketAcceptResult::SOCKET_ADDRESS_LEN,
						  &dwTransferredBytes,
						  result);

	if ( !ret )
	{
		DWORD error_code = ::WSAGetLastError();
		if ( error_code==ERROR_IO_PENDING )
			return true;

		Error("Accept Failed! Error Code = " << error_code << "\r\n");
		result->SetErrorCode(error_code);
		GetAsynIoProactor()->PostCompletion(result);
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
AsynStreamSocket_Connector::AsynStreamSocket_Connector(AsynIoDevice * device) : 
                                       m_pDevice(device),
                                       m_pHandler(0),
									   m_hConnectEvent(INVALID_HANDLE_VALUE),
									   m_lThreadRef(1)
{}

AsynStreamSocket_Connector::~AsynStreamSocket_Connector()
{
	if ( INVALID_HANDLE_VALUE!=m_hConnectEvent )
	{
		GetAsynIoReactor()->RemoveEvent(m_hConnectEvent);
		::CloseHandle(m_hConnectEvent);
		m_hConnectEvent=INVALID_HANDLE_VALUE;

		//TraceLn("~AsynStreamSocket_Connector");
	}

	//TraceLn("AsynStreamSocket_Connector::~AsynStreamSocket_Connector " << (DWORD)this);
}

//////////////////////////////////////////////////////////////////////////
bool AsynStreamSocket_Connector::connect( sockaddr_in * addr,AsynIoHandler * handler )
{
	m_pHandler = handler;

	// �������ӳɹ���Ҫ֪ͨ���¼�
	if(m_hConnectEvent==INVALID_HANDLE_VALUE)
	{
		m_hConnectEvent = ::CreateEvent( NULL, FALSE, FALSE, NULL );
		assert(m_hConnectEvent!=INVALID_HANDLE_VALUE);

		//TraceLn("AsynStreamSocket_Connector::connect WSAEventSelect  " << (DWORD)this);

		if ( SOCKET_ERROR==::WSAEventSelect((SOCKET)m_pDevice->GetHandle(),m_hConnectEvent,FD_CONNECT) )
		{
			ErrorLn("WSAEventSelect");
			assert(false);  // ���������Ϣ
			return false;
		}
		
	}

	// ���¼�ע�ᵽ��Ӧ��
	GetAsynIoReactor()->AddEvent(m_hConnectEvent);
	
	//��Ӧ��ע���¼���RegisterEventHandler(m_hConnectEvent,this);
	//֮��thisָ��ͱ����߳����� ����this������ͷ�ʱ����m_lThreadRefΪ0
	ResGuard<Mutex>  guard(m_ThreadRefLocker);
	if (GetAsynIoReactor()->RegisterEventHandler(m_hConnectEvent,this))
	{
		m_lThreadRef ++;
	}

	// ��������
	int ret = ::connect((SOCKET)m_pDevice->GetHandle(),(sockaddr*)addr,sizeof(sockaddr_in));

	if ( ret==SOCKET_ERROR )
	{
		DWORD error_code = ::WSAGetLastError();
		if ( error_code==WSAEWOULDBLOCK )
			return true;

		Error("Connect Failed! Error Code = " << error_code << "\r\n");
		GetAsynIoReactor()->RemoveEvent(m_hConnectEvent);
		AsynIoResult * result = m_pDevice->CreateAsynIoResult(ASYN_IO_CONNECT,m_pHandler);
		//socket �Ѿ��ر�
		if (NULL == result)
		{
			return false;
		}
		result->SetErrorCode(error_code);
		// ����Reactor��Proactor������ͬһ���̹߳�����,������ҪPost��Proactor
		GetAsynIoProactor()->PostCompletion(result);
		m_pHandler = 0;
		return false;
	}

	ErrorLn("AsynStreamSocket_Connector WSAEventSelect");
	return true;
}

//////////////////////////////////////////////////////////////////////////
void AsynStreamSocket_Connector::OnEvent( HANDLE event )
{

	bool bReleaseFlag = false;
	do 
	{
		ResGuard<Mutex>  guard(m_ThreadRefLocker);
		m_lThreadRef --;

		//���߳��Ѿ�ϣ���ͷű������ˣ���ʱm_pDevice m_pHandler �ȵ��Ѿ���Ч
		if (0 >= m_lThreadRef)
		{
			bReleaseFlag = true;
			break;
		}

		//TraceLn("AsynStreamSocket_Connector::OnEvent " << (DWORD)this);
		if ( m_pHandler )
		{
			unsigned int error_code =ERROR_SUCCESS;
			WSANETWORKEVENTS network_events;
			int ret = WSAEnumNetworkEvents( (SOCKET)m_pDevice->GetHandle(), m_hConnectEvent, &network_events );

			if( SOCKET_ERROR == ret )
			{
				error_code = WSAGetLastError();
			}else
			{
				assert( network_events.lNetworkEvents & FD_CONNECT );
				error_code = network_events.iErrorCode[FD_CONNECT_BIT];
			}

			AsynIoResult * result = m_pDevice->CreateAsynIoResult(ASYN_IO_CONNECT,m_pHandler);
			//socket �Ѿ��ر�
			if (NULL != result)
			{
				result->SetErrorCode(error_code);

				// ����Reactor��Proactor������ͬһ���̹߳�����,������ҪPost��Proactor
				GetAsynIoProactor()->PostCompletion(result);
			}
			m_pHandler = 0;
		}

		GetAsynIoReactor()->RemoveEvent(m_hConnectEvent);


	} while (0);

	if (bReleaseFlag)
	{
		delete this;
	}
}
};

#endif//WIN32