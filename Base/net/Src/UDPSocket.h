/*******************************************************************
** �ļ���:	UDPSocket.h 
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

#ifndef __NET_UDP_SOCKET_H__
#define __NET_UDP_SOCKET_H__

#include "net.h"
#include "handle.h"
#include "AsynIoDevice.h"
#include "AsynIoFrame.h"

namespace xs{

	/**
	@name : ��Ӧ�ò�ʹ�õ�UDP�׽��ֶ���
	@brief: ������AsynDatagranSocket������һ�°�װ
			��Ҫ�������¼�������:
			1.AsynStreamSocket��ʹ���첽IO��ܷ�ʽ���õ�,�û����ܲ�̫ϰ��
			2.һ�����ӽ������Զ�ȥ��ȡ����,�������û���ʾȥ��
			3.��Ϊ�շ���������ͨѶ�߳���ɵ�,���û���Ҫ���û��߳̽��ջص�
			֪ͨ,�����ϲ�Ҫ������߳�ͬ���߼���ǳ��鷳,����Ҳ��Ҫ���߳�
			ת��һ��
	*/
	class UDPSocket : public AsynIoHandler,public IUDPSocket
	{
	public:
		virtual void HandleIoComplete( AsynIoResult * result );

		virtual bool SendData( const char * szRemoteIP,WORD nRemotePort,const char * pData,DWORD dwDataLen,DWORD dwFlag=0 );

		virtual void SetEventHandler( IUDPHandler * pHandler );

		virtual IUDPHandler * GetEventHandler() const;

		virtual void Release();

		handle GetSafeHandle() const { return m_hSafeHandle; }

		bool Create( WORD dwBindPort,IUDPHandler * pHandler );

		bool Close();

		UDPSocket() : m_pSocket(0),m_pHandler(0),m_hSafeHandle(INVALID_HANDLE){}

		virtual ~UDPSocket() { Close(); }

	protected:
		AsynIoDevice             *   m_pSocket;
		IUDPHandler              *   m_pHandler;
		handle                       m_hSafeHandle;  // �Լ��ľ��,��ֹ�����ط���¼�Լ���ָ�벻��ȫ
	};
};

#endif//__NET_UDP_SOCKET_H__