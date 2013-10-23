/*******************************************************************
** �ļ���:	AsynIoFrame.cpp 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/25/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#include "stdafx.h"
#include "AsynIoFrame.h"
#include "Proactor_Win32.h"
#include "Reactor_Win32.h"
#include "WorkerThreadPool.h"
#include "safereleasehelper.h"
#include <list>

bool g_bInitializeAsynIoFrame = false;

/// ��ʼ���첽IO���
NET_API int InitializeAsynIoFrame(DWORD dwProactorThreadNum)
{
	// ��Ҫ�ظ�����
	if ( g_bInitializeAsynIoFrame )
	{
		return 1;
	}

	// ��ʼ��SOCKET
#	ifdef WIN32
		WORD wVersionRequested;
		WSADATA wsaData;
		int err;

		wVersionRequested = MAKEWORD( 2, 2 );

		err = WSAStartup( wVersionRequested, &wsaData );
		if ( err != 0 ) {
			return -3;
		}
#	endif

	// ��ʼ��ȫ�ֱ���
	new Proactor_Win32;
	new Reactor_Win32;
	new WorkerThreadPool;

	// ����ǰ����
	if ( !Proactor_Win32::getInstance().Create(0) )
		return -1;

	// ���������߳�
	for ( int i=0;i<dwProactorThreadNum;++i )
	{
		WorkerThreadPool::getInstance().add(new ProactorWorker);
	}

	// ������Ӧ���߳�
	WorkerThreadPool::getInstance().add(new ReactorWorker);

	g_bInitializeAsynIoFrame = true;

	return 1;
}

/**
@name         : �ͷ��첽IO���
@brief        :
*/
NET_API int UninitializeAsynIoFrame()
{
	if ( g_bInitializeAsynIoFrame )
	{
		delete WorkerThreadPool::getInstancePtr();
		delete Proactor_Win32::getInstancePtr();
		delete Reactor_Win32::getInstancePtr();

#	ifdef WIN32
		WSACleanup();
#	endif

		g_bInitializeAsynIoFrame = false;
	}

	return 1;
}

/**
@name         : ȡ�������첽IO��ǰ����ָ��
@brief        : ������Щ�ط������õõ�
*/
NET_API Proactor * GetAsynIoProactor()
{
	return Proactor_Win32::getInstancePtr();
}

/**
@name         : ȡ�������첽IO�ķ�Ӧ��ָ��
@brief        : ������Щ�ط������õõ�
*/
NET_API Reactor * GetAsynIoReactor()
{
	return Reactor_Win32::getInstancePtr();
}

/**
@name         : ����һ����Ӧ��
@brief        : ͨ��GetAsynIoReactor��õķ�Ӧ������IO�̼߳�����,���
              : ����Ҫ�����¼��ֲ�����IO�߳̿����Լ�����һ��Reactorȥ����
*/
NET_API Reactor * CreateReactor()
{
	return new Reactor_Win32;
}

/**
@name         : ����һ���ڴ�,�����첽IO
@brief        : Ӧ�ò���ǰ����ÿ��Լ���һ�ζ�����ڴ濽�������Ч��
@param dwSize : ��Ҫ������ڴ��С
@return       :
*/
NET_API void * AllocateAsynIoBuffer(DWORD dwSize)
{
	return malloc(dwSize);
}

/**
@name         : �ͷ�һ�������첽IO���ڴ�
@brief        : Ӧ�ò���ǰ����ÿ��Լ���һ�ζ�����ڴ濽�������Ч��
@param   buf  : ָ����Ҫ�ͷŵ��ڴ���ָ��
@return       :
*/
NET_API void   DeallocateAsynIoBuffer(void * buf)
{
	free(buf);
}