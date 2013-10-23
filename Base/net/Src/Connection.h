/*******************************************************************
** �ļ���:	Connection.h 
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

#ifndef __NET_CONNECTION_H__
#define __NET_CONNECTION_H__

#include "net.h"
#include "AsynStreamSocket.h"
#include "Handle.h"

#include <assert.h>

namespace xs{

	/**
	@name : ��Ӧ�ò�ʹ�õ����Ӷ���
	@brief: ������AsynStreamSocket������һ�°�װ
	��Ҫ�������¼�������:
			1.AsynStreamSocket��ʹ���첽IO��ܷ�ʽ���õ�,�û����ܲ�̫ϰ��
			2.һ�����ӽ������Զ�ȥ��ȡ����,�������û���ʾȥ��
			3.��Ϊ�շ���������ͨѶ�߳���ɵ�,���û���Ҫ���û��߳̽��ջص�
			֪ͨ,�����ϲ�Ҫ������߳�ͬ���߼���ǳ��鷳,����Ҳ��Ҫ���߳�
			ת��һ��
			4.��һ���������ӷǳ�Ƶ����ϵͳ��,û��ֻ��һ��Accept�����ڵȴ���
			ԶԶ������,��������ע��FD_ACCEPT�¼�,һ�����¼�����������һ����
			����Accept����
	*/
	class CConnection : public AsynIoHandler,public EventHandler,public IConnection
	{
	public:
		//////////////////////////////////////////////////////////////////////////
		virtual bool Listen();

		virtual bool Connect( const char * ip,unsigned short port );

		virtual bool SendData( const char * pData,DWORD dwDataLen,DWORD dwFlag );

		//virtual bool Disconnect();

		virtual void SetEventHandler( IConnectionEventHandler * pHandler );

		virtual IConnectionEventHandler * GetEventHandler() const;


		virtual bool GetRemoteAddr(DWORD &dwRemoteIP,WORD & wRemotePort);

		virtual bool GetRemoteAddr( const char ** ppRemoteIP,DWORD & dwRemotePort);

		virtual bool  IsPassive() const;

		virtual void Release();

		virtual void HandleIoComplete( AsynIoResult * result );

		virtual void OnEvent( HANDLE event );

		virtual void ChangePacker(DWORD CryptId,uchar *key,DWORD keylen);

		//////////////////////////////////////////////////////////////////////////
		virtual bool Create( SHORT dwBindPort );

		/**
		@name         : ��¡һ�����Լ�ͬ�����͵�����,Acceptʱ��Ҫ�õ�
		@brief        : ��Ҫ��¡����Ϣ����: Socketѡ������,�����ʽ,���ܷ�ʽ��
		@return       :
		*/
		virtual CConnection * Clone() { return new CConnection; }

		virtual void SetSocketDevice(AsynIoDevice * device) {m_pSocket=device;}

		virtual AsynIoDevice* GetSocketDevice(void) {return m_pSocket;}

		// ��ȡ��һ����
		bool RecvNextPackage();

		//crr add,ĳ��tcp��û�н�������������ʣ�µ�����
		bool RecvThisPackageRestData(LPVOID pRecieved, DWORD dwRecievLen, DWORD dwRestLen);


		//crr mod ��ΪConnection ��AsynStreamSocket::CreateAsynIoResult��AsynIoHandler�������ɶ˿��߳������˱�Connectionָ��
		//���޸ı�Connection���ͷ�ʱ���� ��m_pSocket ��pendinglistΪ��ʱ
		//void ReleaseAux();

		
		//handle GetSafeHandle() const { return m_hSafeHandle; }

		CConnection() : m_pSocket(0),m_pHandler(0),m_hAcceptEvent(INVALID_HANDLE_VALUE)//,m_hSafeHandle(INVALID_HANDLE)
		{
			m_bIsPassive  = false;
			//m_hSafeHandle = rktCreateHandle((ulong)this);
			memset(&m_RemoteAddr,0,sizeof(m_RemoteAddr));
		}

	protected:
		//����AsynStreamSocket����ֹ��������ʽ����delete
		friend AsynStreamSocket;
		virtual ~CConnection()
		{
			//Disconnect();
		}

	protected:
		AsynIoDevice             *   m_pSocket;
		IConnectionEventHandler  *   m_pHandler;
		HANDLE                       m_hAcceptEvent;
		//crr mod, ����ľ����װ,������һ�٣���������̰߳�ȫ������ʹ��
		//handle                       m_hSafeHandle;        // �Լ��ľ��,��ֹ�����ط���¼�Լ���ָ�벻��ȫ
		bool                         m_bIsPassive;         // �Ƿ��Ǳ�������
		sockaddr_in                  m_RemoteAddr;         // �Է���ַ
	};
};

#endif//__NET_CONNECTION_H__