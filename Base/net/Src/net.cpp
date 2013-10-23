/*******************************************************************
** �ļ���:	net.cpp 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/26/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/


#include "stdafx.h"
#include "net.h"
#include "ConnectionWrapper.h"
#include "CallbackDispatcher.h"
#include "SimplePacker.h"
#include "DataPacker.h"
#include "senderthread.h"
#include "WorkerThreadPool.h"
#include "UDPSocket.h"
#include "DNS_Resolver.h"
#include "HTTP_Requester.h"

#include "http.h"
#include "dns.h"

using namespace xs;

/// ͨѶ���Ƿ��ѳ��Ի�
bool g_bInitNetwork = false;

/**
@name         : ��ʼ��ͨѶ��
@brief        : ��ʼ������:
              : 1.��ʼ���첽IO���
@return       : 0 ... OK
			    -1... �첽IO��ܳ�ʼ��ʧ��
*/
NET_API int  InitializeNetwork(DWORD dwThreadNum)
{
	if ( g_bInitNetwork )
		return 0;

	if ( InitializeAsynIoFrame(dwThreadNum)<0 )
		return -1;

	// ��ʼ��ȫ�ֱ���
	new CallbackDispatcher;
	new SenderThread;
	new DNS_Resolver;
	new HTTP_Requester;

	if ( !DNS_Resolver::getInstance().Create() )
	{
		return -2;
	}

	// ���������߳�
	WorkerThreadPool::getInstance().add(SenderThread::getInstancePtr());

	g_bInitNetwork = true;

	return 1;
}

/**
@name         : �ͷ�ͨѶ��
@brief        : ����ڳ����˳�ʱӦ�ò㻹û�е��øú���,ͨѶ����Լ��ͷ�
@brief        : ��������������Բ�����
*/
NET_API int  UninitializeNetwork()
{
	if ( g_bInitNetwork )
	{
		delete HTTP_Requester::getInstancePtr();
		delete DNS_Resolver::getInstancePtr();
		delete SenderThread::getInstancePtr();
		delete CallbackDispatcher::getInstancePtr();

		UninitializeAsynIoFrame();

		g_bInitNetwork = false;
	}

	return 1;
}

/**
@name            : ��ȡ�ص�����
@brief           : ͨѶ��ĸ����¼�������ͨѶ�̴߳�����,���û�ϣ���յ���ͨѶ�¼��������û��߳�
            	 : �����ϲ����Ͳ���Ҫ���⴦���߳�ͬ���Ĳ���,�������û��̵߳���ѭ����,��Ҫ����
 				 : ����DispatchNetworkEvents����������ͨѶ�¼����ɷ�,��������ѭ����ȡ������Ϣһ��
*/
NET_API void DispatchNetworkEvents()
{
	if ( !g_bInitNetwork )
	{
		InitializeNetwork();
	}

	CallbackDispatcher::getInstance().DispatchCallback();
}


/**
@name            : ����һ��TCP���Ӷ���
@param dwBindPort: �󶨶˿�,��0��Ҫ������������������ʱ���ѡ��һ�����ö˿�
@param pHandler  : �¼�����ӿ�ָ��
@brief:
*/
NET_API IConnection * RKT_CDECL CreateTCPConnection(USHORT dwBindPort,IConnectionEventHandler * pHandler,IPacker * pPacker)
{
	if ( !g_bInitNetwork )
	{
		InitializeNetwork();
	}

	CConnectionWrapper * conn = new CConnectionWrapper;
	if ( !conn->Create(dwBindPort))
	{
		assert(false);  // ������
		return 0;
	}

	conn->SetEventHandler(pHandler);

	if ( pPacker==DEFAULT_PACK )
		pPacker = new DataPacker;

	if ( pPacker!=NO_PACK )
	    conn->SetPacker(pPacker);

	return conn;
}


/**
@name            : ȡ�������¼���֪ͨ���
@brief           : Ӧ�ò���Լ�������¼�Ȼ�����DispatchNetworkEvents��ȡ������Ϣ
@return          : �����¼����
*/
NET_API HANDLE GetNetworkEventHandle()
{
	return CallbackDispatcher::getInstance().GetEventHandle();
}

/**
@name            : ����һ��UDP�׽��ֶ���
@param dwBindPort: �󶨶˿�
@param pHandler  : �¼�����ӿ�ָ��
@brief:
*/
NET_API IUDPSocket * CreateUDPSocket(USHORT dwBindPort,IUDPHandler * pHandler)
{
	if ( !g_bInitNetwork )
	{
		InitializeNetwork();
	}

	UDPSocket * socket = new UDPSocket;
	if ( socket->Create(dwBindPort,pHandler) )
	{
		return socket;
	}else
	{
		delete socket;
		return 0;
	}
}

/**
@name         : ����HTTP����
@brief        : ʹ��GET��ʽ
@param   url  : Ҫ�����url,������������http://www.carfax.com/register.php?username=no1
@param httpver: Ҫʹ�õ�httpЭ��,Ŀǰ��1.0��1.1
@param data_rng:Ҫ��������ݶ�,���Ϊ����ָ��
@param handler: ����http��Ӧ�Ļص��ӿ�,Ϊ�˰�ȫ�����ʹ�þ��,�þ��ָ��HTTP_Response_Handler��ָ��
@return       :
*/
NET_API bool HTTP_Request( const char * url,HTTP_VERSION httpver,__int64 range_begin,__int64 range_end,handle handler)
{
	return HTTP_Requester::getInstance().Request(url,httpver,range_begin,range_end,handler);
}

/**
@name         : ��ѯһ������
@brief        :
@param domain : ����ѯ������
@param queryer: ��ѯ��,���ڲ�ѯ�ɹ����֪ͨ
@note         : �ڲ�ѯ�����и�ָ����뱣����Ч,�����ָ�뱻�ͷ�,��Ҫ��������Cancel_DNS_Queryȡ����ѯ
@return       :
*/
NET_API bool DNS_Query( const char * domain,DNS_Queryer * queryer )
{
	return DNS_Resolver::getInstance().DNS_Query(domain,queryer);
}

/**
@name         : ȡ��һ��������ѯ����
@brief        :
@param domain : ����ѯ������
@param queryer: ��ѯ��,���ڲ�ѯ�ɹ����֪ͨ
@return       :
*/
NET_API bool Cancel_DNS_Query( const char * domain,DNS_Queryer * queryer )
{
	return DNS_Resolver::getInstance().Cancel_DNS_Query(domain,queryer);
}