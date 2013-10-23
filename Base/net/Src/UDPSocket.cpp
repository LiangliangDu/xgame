/*******************************************************************
** �ļ���:	UDPSocket.cpp 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/31/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#include "stdafx.h"
#include "UDPSocket.h"
#include "CallbackDispatcher.h"
#include "AsynDatagramSocket.h"
#include "CallbackObject.h"
#include "SafeReleaseHelper.h"
#include "senderthread.h"

#ifdef WIN32

namespace xs{

//////////////////////////////////////////////////////////////////////////
bool UDPSocket::Create( WORD dwBindPort,IUDPHandler * pHandler)
{
	AsynDatagramSocket * device = new AsynDatagramSocket;
	m_pSocket = device;

	if ( !device->Create(dwBindPort) )
	{
		assert(false); // ���������Ϣ
		return false;
	}

	m_hSafeHandle = rktCreateHandle((DWORD)this);

	SetEventHandler(pHandler);

	// ��ʼ������
	if ( !m_pSocket->Reader()->read(MAX_NET_PACKAGE_SIZE,this) )
	{
		assert(false); // ���������Ϣ
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool UDPSocket::Close()
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
	
	if ( m_hSafeHandle!=INVALID_HANDLE )
	{
		closeHandle(m_hSafeHandle);
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
void UDPSocket::HandleIoComplete( AsynIoResult * result )
{
	AsynIoDevice * device = result->GetAsynDevice();
	assert(device);
	assert(m_pHandler);

	DWORD dwError = result->GetErrorCode();

	AsynIoBuffer * pBuffer = result->GetBufferList();

	if ( result->Success() )
	{
		switch(result->GetType())
		{
		case ASYN_IO_READFROM:                
			{
				assert(pBuffer && result->GetBufferCount()==1);
				// ������ַ
				char * pData = pBuffer->buf;
				DWORD  dwDataLen = result->GetTransferredBytes();
				DWORD dwAppendLen = ((sizeof(sockaddr_in)+sizeof(int)+63)/64)*64; // Ҫ64�ֽڶ���
				sockaddr_in * addr = (sockaddr_in *)(pData);
				// �ص�Ӧ�ò�
				result->SetBuffer(0,0);
				Callback_RecvFrom * callback = new Callback_RecvFrom(this,addr,pData+dwAppendLen,dwDataLen);
				CallbackDispatcher::getInstance().RequestCallback(callback);

				// ����һ����
				m_pSocket->Reader()->read(MAX_NET_PACKAGE_SIZE,this);
			}
			break;
		case ASYN_IO_WRITETO:                   // Send OK
			break;
		default:
			break;
		}
	}else
	{
		// ����һ����
		switch(result->GetType())
		{
		case ASYN_IO_READFROM:
			m_pSocket->Reader()->read(MAX_NET_PACKAGE_SIZE,this);
			break;
		default:
			break;
		}

		// ɾ��result
		device->DeleteAsynIoResult(result);	

		// Ͷ�ݳ�����Ϣ
		CallbackDispatcher::getInstance().RequestCallback(new Callback_UDP_Error(this,dwError));
	}
}

//////////////////////////////////////////////////////////////////////////
bool UDPSocket::SendData( const char * szRemoteIP,WORD nRemotePort,const char * pData,DWORD dwDataLen,DWORD dwFlag )
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

	sockaddr_in * remote_addr = (sockaddr_in *)AllocateAsynIoBuffer(sizeof(sockaddr_in));
	remote_addr->sin_family = AF_INET;
	remote_addr->sin_port = htons( nRemotePort );
	remote_addr->sin_addr.s_addr = inet_addr(szRemoteIP);

	AsynIoBuffer buffList[2];
	buffList[0].buf = (char *)remote_addr;
	buffList[0].len = sizeof(sockaddr_in);
	buffList[1].buf = pBuffer;
	buffList[1].len = dwDataLen;

	//SenderThread::getInstance().RequestSendData(m_pSocket,this,m_hSafeHandle,buffList[0]);
	//SenderThread::getInstance().RequestSendData(m_pSocket,this,m_hSafeHandle,buffList[1]);
	SenderThread::getInstance().RequestSendData(m_pSocket,this,buffList[0]);
	SenderThread::getInstance().RequestSendData(m_pSocket,this,buffList[1]);
	return true;
}

//////////////////////////////////////////////////////////////////////////
void UDPSocket::SetEventHandler( IUDPHandler * pHandler )
{
	m_pHandler = pHandler;
}

//////////////////////////////////////////////////////////////////////////
IUDPHandler * UDPSocket::GetEventHandler() const
{
	return m_pHandler;
}

//////////////////////////////////////////////////////////////////////////
void UDPSocket::Release()
{
	delete this;
}

};

#endif//WIN32