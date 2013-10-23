/*******************************************************************
** �ļ���:	AsynDatagramSocket.h 
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

#ifndef __ASYN_DATAGRAM_SOCKET_H__
#define __ASYN_DATAGRAM_SOCKET_H__

#include "AsynIoFrame.h"
#include "Reactor.h"
#include "AsynIoResult.h"
#include "AsynIoDevice.h"
#include "AsynIoOperation.h"
#include "Thread.h"

#include <set>

namespace xs{

	/**
	@name : UDPЭ����׽��ַ�װ
	@brief: 
	*/
	class AsynDatagramSocket : public AsynIoDevice
	{
	public:
		//////////////////////////////////////////////////////////////////////////
		/*********************** AsynIoDevice ***********************************/

		virtual HANDLE GetHandle() const{return (HANDLE)m_hSocketHandle;}

		virtual AsynIoOperation_Reader * Reader() { return m_pReader;}

		virtual AsynIoOperation_Writer * Writer() { return m_pWriter; }

		virtual AsynIoOperation_Acceptor * Acceptor() { return 0;}

		virtual AsynIoOperation_Connector * Connector(){ return 0;}

		AsynIoResult * CreateAsynIoResult(int iotype,AsynIoHandler * handler);

		virtual void DeleteAsynIoResult(AsynIoResult * result);

		virtual void Release();

		bool Create(unsigned short port);

		bool Close();

		AsynDatagramSocket() : m_hSocketHandle(INVALID_SOCKET),m_pReader(0),m_pWriter(0){}

		virtual ~AsynDatagramSocket() { Close(); }

	protected:
		//////////////////////////////////////////////////////////////////////////
		SOCKET                 m_hSocketHandle;  // �׽��־��

		AsynIoOperation_Reader *    m_pReader;   // ��ȡ��
		AsynIoOperation_Writer *    m_pWriter;   // д����

		typedef std::set<AsynIoResult *> RESULT_LIST;
		RESULT_LIST                 m_pendingList;// δ��ɵĲ���

		Mutex                       m_Locker;    // �߳���
	};

	/**
	@name : �첽���׽��ֶ�����
	@brief:
	*/
	class AsynDatagramSocket_Reader : public AsynIoOperation_Reader
	{
	public:
		virtual bool read(DWORD expect_bytes,AsynIoHandler * handler);

		AsynDatagramSocket_Reader(AsynIoDevice* device) : m_pDevice(device){}

	protected:
		AsynIoDevice *   m_pDevice;
	};

	/**
	@name : �첽���׽���д����
	@brief:
	*/
	class AsynDatagramSocket_Writer : public AsynIoOperation_Writer
	{
	public:
		/// UDP���豸��Ϊ��������ʱ��Ҫָ���Է��ĵ�ַ����ʵ�ֱȽ�����,Ĭ�ϵ�ַ(sockaddr_in)���ڻ���������ǰ��
		virtual bool write(const char * data,DWORD len,AsynIoHandler * handler);

		/// UDP���豸��Ϊ��������ʱ��Ҫָ���Է��ĵ�ַ����ʵ�ֱȽ�����,Ĭ�ϵ�һ��Buff�����ŵ�ַ(sockaddr_in)
		virtual bool writeEx( AsynIoBuffer * pBuffList,DWORD dwBuffCount,AsynIoHandler * handler);

		AsynDatagramSocket_Writer(AsynIoDevice * device) : m_pDevice(device){}

	protected:
		AsynIoDevice *   m_pDevice;
	};
};

#endif//__ASYN_DATAGRAM_SOCKET_H__