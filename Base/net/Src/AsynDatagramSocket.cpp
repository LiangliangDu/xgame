/*******************************************************************
** �ļ���:	AsynDatagramSocket.cpp 
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
#include "AsynDatagramSocket.h"
#include "AsynIoResult.h"
#include "Proactor.h"
#include "Reactor.h"
#include "SafeReleaseHelper.h"

#ifdef WIN32

namespace xs{

//////////////////////////////////////////////////////////////////////////
bool AsynDatagramSocket::Create(unsigned short port)
{
	m_hSocketHandle = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if ( INVALID_SOCKET==m_hSocketHandle )
	{
		assert(false);  // ���������Ϣ
		return false;
	}

	m_pReader = new AsynDatagramSocket_Reader(this);
	m_pWriter = new AsynDatagramSocket_Writer(this);

	GetAsynIoProactor()->RegisterDevice(this);

	sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons( port );
	sock_addr.sin_addr.s_addr = htonl( INADDR_ANY );
	int ret = ::bind( m_hSocketHandle, (const sockaddr*)&sock_addr, sizeof(sockaddr_in) );
	if( ret == SOCKET_ERROR )
	{
		assert(false);  // ���������Ϣ
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool AsynDatagramSocket::Close()
{
	if ( m_hSocketHandle!=INVALID_SOCKET )
	{
		::closesocket(m_hSocketHandle);
		m_hSocketHandle = INVALID_SOCKET;
	}

	assert(m_pendingList.empty());

	m_pendingList.clear();

	safeDelete(m_pReader);
	safeDelete(m_pWriter);

	return true;
}

//////////////////////////////////////////////////////////////////////////
void AsynDatagramSocket::Release()
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

			::closesocket(m_hSocketHandle);
			m_hSocketHandle = INVALID_SOCKET;
		}

		if ( !m_pendingList.empty())
		{
			SafeReleaseHelper::getInstance().ReleaseAsynIoDevice(this);
			return;
		}

		break;
	}

	delete this;
}

//////////////////////////////////////////////////////////////////////////
AsynIoResult * AsynDatagramSocket::CreateAsynIoResult(int iotype,AsynIoHandler * handler)
{
	ResGuard<Mutex>  guard(m_Locker);

	AsynIoResult * result = new AsynIoResultImp((AsynIoType)iotype,handler);
	m_pendingList.insert(result);

	result->SetAsynDevice(this);

	return result;
}

//////////////////////////////////////////////////////////////////////////
void AsynDatagramSocket::DeleteAsynIoResult(AsynIoResult * result)
{
	ResGuard<Mutex>  guard(m_Locker);

	RESULT_LIST::iterator it = m_pendingList.find(result);
	assert(it!=m_pendingList.end());

	m_pendingList.erase(it);

	delete (AsynIoResultImp *)result;
}

//////////////////////////////////////////////////////////////////////////
bool AsynDatagramSocket_Reader::read(DWORD expect_bytes,AsynIoHandler * handler)
{
	/// UDP���豸��Ϊ��������ʱ��Ҫָ���Է��ĵ�ַ����ʵ�ֱȽ�����,Ĭ�ϵ�ַ(sockaddr_in)���ڻ���������ǰ��
	DWORD dwAppendLen = ((sizeof(sockaddr_in)+sizeof(int)+63)/64)*64; // Ҫ64�ֽڶ���

	assert(m_pDevice);
	AsynIoResult * result = m_pDevice->CreateAsynIoResult(ASYN_IO_READFROM,handler);
	result->PrepareBuffer(expect_bytes+dwAppendLen);

	DWORD dwTransferredBytes = 0;
	DWORD dwFlag = 0;

	AsynIoBuffer * pBuffer = result->GetBufferList();

	sockaddr * remote_addr = (sockaddr *)(pBuffer->buf);
	int * dwAddressLen = (int*)(pBuffer->buf+sizeof(sockaddr_in));
	*dwAddressLen = sizeof(sockaddr_in);

	WSABUF buff;
	buff.buf = pBuffer->buf + dwAppendLen;
	buff.len = expect_bytes;

	int ret = ::WSARecvFrom((SOCKET)m_pDevice->GetHandle(),
		                    &buff,
							1,
							&dwTransferredBytes,
							&dwFlag,
							remote_addr,
							dwAddressLen,
							result,
							NULL);

	if ( ret==SOCKET_ERROR )
	{
		DWORD error_code = ::WSAGetLastError();
		if ( error_code==WSA_IO_PENDING )
			return true;

		Error("Recv Datagram Failed! Error Code = " << error_code << "\r\n");
		result->SetErrorCode(error_code);
		GetAsynIoProactor()->PostCompletion(result);
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool AsynDatagramSocket_Writer::write(const char * data,DWORD len,AsynIoHandler * handler)
{
	/// UDP���豸��Ϊ��������ʱ��Ҫָ���Է��ĵ�ַ����ʵ�ֱȽ�����,Ĭ�ϵ�ַ(sockaddr_in)���ڻ���������ǰ��
	DWORD dwAppendLen = ((sizeof(sockaddr_in)+63)/64)*64; // Ҫ64�ֽڶ���
	assert(len > dwAppendLen);

	AsynIoResult * result =m_pDevice->CreateAsynIoResult(ASYN_IO_WRITETO,handler);
	result->PrepareBuffer(len-dwAppendLen);

	LPWSABUF sendBuf = (LPWSABUF)result->GetBufferList();
	memcpy(sendBuf->buf,data+dwAppendLen,len-dwAppendLen);

	DWORD dwTransferredBytes = 0;
	DWORD dwFlag = 0;

	sockaddr * remote_addr = (sockaddr *)data;
	DWORD dwAddressLen = sizeof(sockaddr_in);

	int ret = ::WSASendTo((SOCKET)m_pDevice->GetHandle(),
		                   sendBuf,
						   1,
						   &dwTransferredBytes,
						   dwFlag,
						   remote_addr,
						   dwAddressLen,
						   result,
						   0);

	if ( ret==SOCKET_ERROR )
	{
		DWORD error_code = ::WSAGetLastError();
		if ( error_code==WSA_IO_PENDING )
			return true;

		Error("Send Datagram Failed! Error Code = " << error_code << "\r\n");
		result->SetErrorCode(error_code);
		GetAsynIoProactor()->PostCompletion(result);
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool AsynDatagramSocket_Writer::writeEx( AsynIoBuffer * pBuffList,DWORD dwBuffCount,AsynIoHandler * handler)
{
	/// UDP���豸��Ϊ��������ʱ��Ҫָ���Է��ĵ�ַ����ʵ�ֱȽ�����,Ĭ�ϵ�һ��Buff�����ŵ�ַ(sockaddr_in)
	assert(dwBuffCount>1);
	assert(pBuffList[0].len == sizeof(sockaddr_in));

	AsynIoResult * result =m_pDevice->CreateAsynIoResult(ASYN_IO_WRITETO,handler);
	result->SetBuffer(pBuffList+1,dwBuffCount-1);

	DWORD dwTransferredBytes = 0;
	DWORD dwFlag = 0;

	sockaddr * remote_addr = (sockaddr*)pBuffList[0].buf;
	DWORD dwAddressLen = sizeof(sockaddr_in);

	int ret = ::WSASendTo((SOCKET)m_pDevice->GetHandle(),
		                  (LPWSABUF)result->GetBufferList(),
						  result->GetBufferCount(),
						  &dwTransferredBytes,
						  dwFlag,
						  remote_addr,
						  dwAddressLen,
						  result,
						  0);

	// ���ٴ�ŵ�ַ��buff
	DeallocateAsynIoBuffer(pBuffList[0].buf);

	if ( ret==SOCKET_ERROR )
	{
		DWORD error_code = ::WSAGetLastError();
		if ( error_code==WSA_IO_PENDING )
			return true;

		Error("Send Datagrams Failed! Error Code = " << error_code << "\r\n");
		result->SetErrorCode(error_code);
		GetAsynIoProactor()->PostCompletion(result);
		return false;
	}

	return true;
}

};

#endif//WIN32