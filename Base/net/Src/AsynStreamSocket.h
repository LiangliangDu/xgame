/*******************************************************************
** �ļ���:	AsynStreamSocket.h 
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

#ifndef __ASYN_STREAM_SOCKET_H__
#define __ASYN_STREAM_SOCKET_H__

#ifdef WIN32

#include "AsynIoFrame.h"
#include "Reactor.h"
#include "AsynIoResult.h"
#include "AsynIoDevice.h"
#include "AsynIoOperation.h"
#include "Thread.h"

#include <set>

namespace xs{

class CConnection;

	/**
	@name : �첽���׽��ַ�װ(TCP)
	@brief: 
	*/
	class AsynStreamSocket : public AsynIoDevice
	{
	public:
		//////////////////////////////////////////////////////////////////////////
		/*********************** AsynIoDevice ***********************************/

		virtual HANDLE GetHandle() const
		{
			return (HANDLE)m_hSocketHandle;
		}

		virtual AsynIoOperation_Reader * Reader() 
		{ 
			return m_pReader; 
		}

		virtual AsynIoOperation_Writer * Writer() 
		{ 
			return m_pWriter; 
		}

		virtual AsynIoOperation_Acceptor * Acceptor() 
		{ 
			return m_pAcceptor; 
		}

		virtual AsynIoOperation_Connector * Connector() 
		{ 
			return m_pConnector; 
		}

		AsynIoResult * CreateAsynIoResult(int iotype,AsynIoHandler * handler);

		virtual void DeleteAsynIoResult(AsynIoResult * result);

		virtual void Release();

		bool Create(CConnection* pConn);

		bool Bind( unsigned short port );

		bool Listen();

		bool Close();

		bool IncreaseSendRef(void);
		void DecreaseSendRef(int iCount = 1);

		AsynStreamSocket() : m_hSocketHandle(INVALID_SOCKET),
							 m_pReader(0),
							 m_pWriter(0),
							 m_pAcceptor(0),
							 m_pConnector(0),
							 m_iSendThreadRef(0),
							 m_bWaitingClosed(false)
		{
		}

		virtual ~AsynStreamSocket() { Close(); }

	protected:
		//////////////////////////////////////////////////////////////////////////
		int					 m_iSendThreadRef;//�����̵߳����ô���
		bool				 m_bWaitingClosed;
		CConnection			* m_pConnection;
		SOCKET                 m_hSocketHandle;  // �׽��־��

		AsynIoOperation_Reader *    m_pReader;   // ��ȡ��
		AsynIoOperation_Writer *    m_pWriter;   // д����
		AsynIoOperation_Acceptor*   m_pAcceptor; // ������
		AsynIoOperation_Connector*  m_pConnector;// ������
		
		typedef std::set<AsynIoResult *> RESULT_LIST;
		RESULT_LIST                 m_pendingList;// δ��ɵĲ���

		Mutex                       m_Locker;    // �߳���
	};

	/**
	@name : �첽���׽��ֶ�����
	@brief:
	*/
	class AsynStreamSocket_Reader : public AsynIoOperation_Reader
	{
	public:
		virtual bool read(DWORD expect_bytes,AsynIoHandler * handler);
		virtual bool read(DWORD expect_bytes,AsynIoHandler * handler, LPVOID pRecieved, DWORD dwRecievedLen, DWORD dwRestLen);
		AsynStreamSocket_Reader(AsynIoDevice* device) : m_pDevice(device){}

	protected:
		AsynIoDevice *   m_pDevice;
	};

	/**
	@name : �첽���׽���д����
	@brief:
	*/
	class AsynStreamSocket_Writer : public AsynIoOperation_Writer
	{
	public:
		virtual bool write(const char * data,DWORD len,AsynIoHandler * handler);

		virtual bool writeEx( AsynIoBuffer * pBuffList,DWORD dwBuffCount,AsynIoHandler * handler);

		AsynStreamSocket_Writer(AsynIoDevice * device) : m_pDevice(device){}

	protected:
		AsynIoDevice *   m_pDevice;
	};

	/**
	@name : �첽���׽��ֽ��ղ���
	@brief:
	*/
	class AsynStreamSocket_Acceptor : public AsynIoOperation_Acceptor
	{
	public:
		virtual bool accept(AsynIoHandler * handler);

		AsynStreamSocket_Acceptor(AsynIoDevice * device) : m_pDevice(device),m_bListen(false){}

	protected:
		AsynIoDevice *   m_pDevice;
		bool             m_bListen;
	};

	/**
	@name : �첽���׽������Ӳ���
	@brief:
	*/
	class AsynStreamSocket_Connector : public AsynIoOperation_Connector,public EventHandler
	{
	public:
		virtual bool connect( sockaddr_in * addr,AsynIoHandler * handler );

		virtual void OnEvent( HANDLE event );

		void cancel() { m_pHandler = 0; }

		void SafeRelease(void)
		{
			bool bReleaseFlag = false;
			do 
			{
				ResGuard<Mutex>  guard(m_ThreadRefLocker);
				m_lThreadRef --;
				if (0 >= m_lThreadRef)
				{
					bReleaseFlag = true;
				}
				

			} while (0);

			if (bReleaseFlag)
			{
				delete this;
			}
		}

		AsynStreamSocket_Connector(AsynIoDevice * device);

		virtual ~AsynStreamSocket_Connector();

	protected:
		AsynIoDevice *   m_pDevice;
		HANDLE           m_hConnectEvent;
		AsynIoHandler *  m_pHandler;

		//crr ad ��Ϊ Connector ��connect��ʱ����Ӧ���߳�ע�����¼��������Լ�thisָ����Ϊhandler
		//ֱ���ͷ�m_pConnector ������Ƿ�, ���ӱ���m_iThreadRef��¼�߳����ü���
		//ֻ��m_iThreadRef = 0 ʱ�������ͷ�
		//�����net���ʱ Ҫ�ر�ע��m_pDevice m_pHandler������ָ��ָ������Ƿ��Ѿ��ͷ���͹ ͹

		volatile LONG	m_lThreadRef;
		Mutex m_ThreadRefLocker;
				
	};
};

#endif//WIN32

#endif//__ASYN_STREAM_SOCKET_H__