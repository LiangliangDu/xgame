/*******************************************************************
** �ļ���:	AsynIoResultImp.h 
** ��  Ȩ:	(C) ����δ�����缼�����޹�˾ 2008 - All Rights Reserved
** ������:	achen
** ��  ��:	02/03/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __ASYN_IO_RESULT_IMP_H__
#define __ASYN_IO_RESULT_IMP_H__

#include "AsynIoResult.h"
#include "AsynIoDevice.h"

#ifdef WIN32

#include <Mswsock.h>

namespace xs{

	/**
	@name : TCP Accept�����ķ��ؽ��
	@brief: 1.��¼Accept���������ӵ�ָ��
	        2.ά��Accept�����յ��ĶԷ���ַ����Ϣ
	*/
	class AsynStreamSocketAcceptResult : public AsynIoResultImp
	{
	public:
		enum
		{
			SOCKET_ADDRESS_LEN = (sizeof(sockaddr_in)+16) ,  // �����ַ����
			ACCEPT_BUFFER_LEN  = SOCKET_ADDRESS_LEN * 2   ,  // ���ջ������ĳ���
		};

		/**
		@name         : ȡ�ý��ջ�������ַ
		@brief        : ���ջ�������ɺ������ = �յ��ĵ�һ������ + �Լ��ĵ�ַ + �Է��ĵ�ַ
		              : Ŀǰ���ǵ���AcceptExʱĬ�ϲ����յ�һ������,�����䳤��Ϊ0
		*/ 
		char * GetAcceptBuffer() { return m_AcceptBuffer; };

		/// ȡ�ý��ջ���������
		DWORD GetAcceptBufferLen() const { return ACCEPT_BUFFER_LEN; }

		/// ȡ��Զ��������ַ
		bool GetRemoteAddr( sockaddr_in & remoteAddr,int & nAddLen )
		{
			sockaddr * pLocalAddr = 0;
			int nLocalAddrLen = 0;
			sockaddr * pRemoteAddr = 0;
			int nRemoteAddrLen = 0;

			::GetAcceptExSockaddrs(m_AcceptBuffer,0,SOCKET_ADDRESS_LEN,SOCKET_ADDRESS_LEN,&pLocalAddr,&nLocalAddrLen,&pRemoteAddr,&nRemoteAddrLen);

			if ( pRemoteAddr==0 || nRemoteAddrLen==0 )
				return false;
			
			memcpy(&remoteAddr,pRemoteAddr,nRemoteAddrLen);
			nAddLen = nRemoteAddrLen;
			return true;
		}

		/// ���������������ָ��
		void SetIncomingSocket(AsynIoDevice * socket) { m_pIncomingSocket=socket;}

		/// ��ȡ�����������ָ��
		AsynIoDevice  *   GetIncomingSocket() const { return m_pIncomingSocket; }

		AsynStreamSocketAcceptResult() : m_pIncomingSocket(0){}

		AsynStreamSocketAcceptResult(AsynIoHandler * pHandler) : AsynIoResultImp(ASYN_IO_ACCEPT,pHandler) , m_pIncomingSocket(0){}

	protected:
		AsynIoDevice  *   m_pIncomingSocket;
		char              m_AcceptBuffer[ACCEPT_BUFFER_LEN];
	};
};

#endif//WIN32

#endif//__ASYN_IO_RESULT_IMP_H__