/*******************************************************************
** �ļ���:	Connection.cpp 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/28/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#include "stdafx.h"
#include "Connection.h"
#include "CallbackDispatcher.h"
#include "AsynIoResultImp.h"
#include "SafeReleaseHelper.h"
#include "CallbackObject.h"
#include "Reactor.h"
#include <assert.h>

#ifdef WIN32

namespace xs{

#include <Mswsock.h>

bool CConnection::Create( SHORT dwBindPort )
{
	AsynStreamSocket * device = new AsynStreamSocket;
	m_pSocket = device;

	if ( !device->Create(this))
	{
		assert(false); // ���������Ϣ
		return false;
	}
	if ( !device->Bind(dwBindPort) )
	{
		assert(false); // ���������Ϣ
		return false;
	}

	return true;
}

bool CConnection::Listen()
{
	assert(m_pSocket);

	if ( m_hAcceptEvent==INVALID_HANDLE_VALUE )
	{
		m_hAcceptEvent = ::CreateEvent(NULL,FALSE,FALSE,0);
		assert(m_hAcceptEvent!=INVALID_HANDLE_VALUE);
	}

	::WSAEventSelect((SOCKET)m_pSocket->GetHandle(),m_hAcceptEvent,FD_ACCEPT);
	GetAsynIoReactor()->AddEvent(m_hAcceptEvent);
	GetAsynIoReactor()->RegisterEventHandler(m_hAcceptEvent,this);

	return m_pSocket->Acceptor()->accept(this);
}


 void CConnection::ChangePacker(DWORD CryptId,uchar *key,DWORD keylen)
{

}

void CConnection::OnEvent( HANDLE event )
{
	assert(m_pSocket);
	assert(event==m_hAcceptEvent);

	// ���������ڵȴ�,����һ��Accept����
	m_pSocket->Acceptor()->accept(this);
}

bool CConnection::Connect( const char * ip,unsigned short port )
{
	m_RemoteAddr.sin_family = AF_INET;
	m_RemoteAddr.sin_addr.s_addr = inet_addr( ip );
	m_RemoteAddr.sin_port = htons( port );

	assert(m_pSocket);
	return m_pSocket->Connector()->connect(&m_RemoteAddr,this);
}

bool CConnection::SendData( const char * pData,DWORD dwDataLen,DWORD dwFlag )
{
	assert(m_pSocket);
	assert(pData);
	assert(dwDataLen);

	return m_pSocket->Writer()->write((char *)pData,dwDataLen,this);
}

#if 0
bool CConnection::Disconnect()
{
	// closesocket���ú���ɶ˿ڻὫ����pending״̬������첽io��������
	// �������ڴ�������¼��Ĺ����̲߳�һ���͵���Close���߳���ͬһ��
	// �������ﲻ��ֱ��delete pending״̬�Ľ������,��ѡ��������
	// 1.Postһ����Ϣ�������߳�,�ù����߳�ȥRelease AsynIODevice
	// 2.��result����������һ����־,�ӳٵ��ò������ʱdelete��,��ȻҪȷ����Ҫ�����ڴ�й¶
	// ʹ�õ�һ�ַ�����Ϊ����.
	if ( m_pSocket )
	{
		m_pSocket->Release();
		m_pSocket = 0;
	}

	if ( m_hAcceptEvent!=INVALID_HANDLE_VALUE )
	{
		GetAsynIoReactor()->RemoveEvent(m_hAcceptEvent);
		::CloseHandle(m_hAcceptEvent);
		m_hAcceptEvent = INVALID_HANDLE_VALUE;
	}

	return true;
}
#endif

void CConnection::SetEventHandler( IConnectionEventHandler * pHandler )
{
	m_pHandler = pHandler;
}

IConnectionEventHandler * CConnection::GetEventHandler() const
{
	return m_pHandler;
}

/**
@name              : ȡ�öԷ��������ַ
@param dwRemoteIP  : ���ضԷ���IP [OUT]
@param wRemotePort : ���ضԷ��Ķ˿� [OUT]
@return            : ����Է��ĵ�ַ����ȷ���򷵻�ʧ��
*/
bool CConnection::GetRemoteAddr(DWORD &dwRemoteIP,WORD & wRemotePort)
{
	dwRemoteIP = m_RemoteAddr.sin_addr.S_un.S_addr;
	wRemotePort = m_RemoteAddr.sin_port;
	return true;
}

bool CConnection::GetRemoteAddr( const char ** ppRemoteIP,DWORD & dwRemotePort)
{
	*ppRemoteIP = inet_ntoa(m_RemoteAddr.sin_addr);
	dwRemotePort = ntohs(m_RemoteAddr.sin_port);
	return true;
}

bool  CConnection::IsPassive() const
{
	return m_bIsPassive;   
}

#if 1
void CConnection::Release()
{
	if ( m_hAcceptEvent!=INVALID_HANDLE_VALUE )
	{
		GetAsynIoReactor()->RemoveEvent(m_hAcceptEvent);
		::CloseHandle(m_hAcceptEvent);
		m_hAcceptEvent = INVALID_HANDLE_VALUE;
	}

	//crr mod ��ΪConnection ��AsynStreamSocket::CreateAsynIoResult��AsynIoHandler�������ɶ˿��߳������˱�Connectionָ��
	//���޸ı�Connection���ͷ�ʱ���� ��m_pSocket ��pendinglistΪ��,��m_iSendThreadRef ==0
	if ( m_pSocket )
	{
		// Post�������߳����ͷ�
		AsynIoResult * result = m_pSocket->CreateAsynIoResult(ASYN_IO_CLOSE,this);
		GetAsynIoProactor()->PostCompletion(result);
		m_pSocket->Release();
		//m_pSocket = 0;
	}
	else
	{
		delete this;
	}
}
#else
void CConnection::Release()
{
	if ( m_pSocket )
	{
		// Post�������߳����ͷ�
		AsynIoResult * result = m_pSocket->CreateAsynIoResult(ASYN_IO_CLOSE,this);
		GetAsynIoProactor()->PostCompletion(result);
	}else
	{
		ReleaseAux();
	}
}

void CConnection::ReleaseAux()
{
	Disconnect();

// 	if ( m_hSafeHandle!=INVALID_HANDLE )
// 	{
// 		rktCloseHandle(m_hSafeHandle);
// 		m_hSafeHandle = INVALID_HANDLE;
// 	}

	delete this;
}
#endif

void CConnection::HandleIoComplete( AsynIoResult * result )
{
	AsynIoDevice * device = result->GetAsynDevice();
	assert(device);
	assert(m_pHandler);

	DWORD dwError = result->GetErrorCode();

	if ( result->Success() )
	{
		switch(result->GetType())
		{
		case ASYN_IO_ACCEPT:                  // Incoming Connection
			{
				AsynStreamSocketAcceptResult * pAcceptResult = (AsynStreamSocketAcceptResult *)result;
				AsynIoDevice * incomingDevice = pAcceptResult->GetIncomingSocket();
				assert(incomingDevice);
				CConnection * incoming = this->Clone();
				incoming->m_bIsPassive = true;
				int nRemoteAddrLen = 0;
				incoming->SetSocketDevice(incomingDevice);
				pAcceptResult->GetRemoteAddr(incoming->m_RemoteAddr,nRemoteAddrLen);
				// ����accept��һ��
				device->Acceptor()->accept(this);
				//crr �����̰߳�ȫ�ŵ�ִ��CallBack���߳���ȥDeleteAsynIoResult
				// ɾ��result
				//device->DeleteAsynIoResult(result);
				// ֪ͨӦ�ò�
				CallbackDispatcher::getInstance().RequestCallback(new Callback_Accept(this,incoming,result));
				break;
			}
		case ASYN_IO_CONNECT:                // Connect OK
			RecvNextPackage();
			// ɾ��result
			//device->DeleteAsynIoResult(result);
			// ֪ͨӦ�ò�
			CallbackDispatcher::getInstance().RequestCallback(new Callback_Connect(this,result));
			break;
		case ASYN_IO_READ:                   // Data Recieve
			{
				AsynIoBuffer * pBuffer = result->GetBufferList();
				assert(pBuffer && result->GetBufferCount()==1);
				LPVOID pData = pBuffer->buf;
				DWORD dwTransferedBytes = result->GetTransferredBytes();

				if (dwTransferedBytes>0)
				{
					result->SetBuffer(0,0);          // Detach The Buff



					//crr mod,Ĭ�ϲ��õ�SimplePacker ���ڿ�ͷ�����ֽڼ�¼���η������ݵĴ�С
					//���������Ƿ�������ע�⣺�п��ܴ����������
					
					//��һ�ν��յ��İ��Ŀ�ͷ����
					dwTransferedBytes += result->GetLastRecievedLen();

					WORD wCurPacketSize = 0;
					DWORD dwRestDataLen = dwTransferedBytes;
					char* pCurPacket = (char*)pData;
					while (true)
					{
						if (dwRestDataLen < sizeof WORD)
						{
							//ErrorLn("��δ�������� δ����simple packer��ͷ2���ֽ�");
							break;
						}
						wCurPacketSize = *(WORD*)pCurPacket + sizeof WORD;	
						if (dwRestDataLen < wCurPacketSize)
						{
							//ErrorLn("��δ�������� ��С< " << wCurPacketSize);
							break;
						}

						pCurPacket = pCurPacket + wCurPacketSize;
						dwRestDataLen -= wCurPacketSize;
						if (0 == dwRestDataLen)
						{
							break;
						}
					}
					if (dwRestDataLen == 0)
					{
						//�������������ŵİ���������
						// ����һ����
						RecvNextPackage();
						// ɾ��result
						//device->DeleteAsynIoResult(result);
						// ֪ͨӦ�ò�
						CallbackDispatcher::getInstance().RequestCallback(new Callback_Recv(this,pData,dwTransferedBytes, result));

					}
					else
					{
						//���һ����δ��������
						// ���������������
						RecvThisPackageRestData((LPVOID)pCurPacket, dwRestDataLen,wCurPacketSize);
						// ɾ��result
						//device->DeleteAsynIoResult(result);
						// ֪ͨӦ�ò�
						CallbackDispatcher::getInstance().RequestCallback(new Callback_Recv(this,pData,dwTransferedBytes - dwRestDataLen,result));
					}

				}else
				{
					// ɾ��result
					//device->DeleteAsynIoResult(result);
					// ֪ͨӦ�ò�
					CallbackDispatcher::getInstance().RequestCallback(new Callback_TCP_Error(this,WSAECONNRESET, result));
				}
			}
			break;
		case ASYN_IO_WRITE:                  // Send OK
				// ɾ��result
				device->DeleteAsynIoResult(result);
			break;
		case ASYN_IO_CLOSE:
			//crr �����ͷŵ�connection����ЩCallback �����õ���this�����
			device->DeleteAsynIoResult(result);
			//CallbackDispatcher::getInstance().RequestCallback(new Callback_Release(this,WSAECONNRESET));
			//ReleaseAux();
			break;
		default:
			// ɾ��result
			device->DeleteAsynIoResult(result);
			break;
		}
	}else
	{
		// Ͷ�ݳ�����Ϣ
		// ɾ��result
		//device->DeleteAsynIoResult(result);
		CallbackDispatcher::getInstance().RequestCallback(new Callback_TCP_Error(this,dwError, result));
	}

	// ɾ��result(����������ɾ,Ҫ��ǰɾ,��Ϊcallback������ӿ����Ѿ�delete��)
	// device->DeleteAsynIoResult(result);
}

// ��ȡ��һ����
bool CConnection::RecvNextPackage()
{
	assert(m_pSocket);
	m_pSocket->Reader()->read(MAX_NET_PACKAGE_SIZE,this);
	return true;
}


//crr add,ĳ��tcp��û�н�������������ʣ�µ�����
bool CConnection::RecvThisPackageRestData(LPVOID pRecieved, DWORD dwRecievLen, DWORD dwRestLen)
{	
	assert(m_pSocket);
	((AsynStreamSocket_Reader *)(m_pSocket->Reader()))->read(MAX_NET_PACKAGE_SIZE,this, pRecieved, dwRecievLen, dwRestLen);
	return true;
}

};

#endif//WIN32