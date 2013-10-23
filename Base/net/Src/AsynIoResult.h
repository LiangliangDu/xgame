/*******************************************************************
** �ļ���:	AsynIoResult.h 
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

#ifndef __ASYN_IO_RESULT_H__
#define __ASYN_IO_RESULT_H__

#include "AsynIoFrame.h"

namespace xs {

#ifdef  WIN32

	/**
	@name : Window�µ���ɶ���ʵ��
	@brief: Windows�µ���ɶ���̳�һ���ص��ṹ�������첽IO
	*/
	class AsynIoResultImp : public AsynIoResult
	{
	public:
		//////////////////////////////////////////////////////////////////////////
		virtual void SetHandler( AsynIoHandler * handler);

		virtual void SetEventHandle( HANDLE event );

		virtual void Complete();

		virtual void PrepareBuffer( unsigned long len );
		//crr add Ϊ����ʣ������׼���첽IOҪ�õĻ�����
		virtual	void PrepareBuffer( unsigned long len, LPVOID pRecieved, DWORD dwRecievedLen, DWORD dwRestLen);
		//��һ�ν��յ������ݰ��������������ѽ��յ������ݳ���
		virtual DWORD GetLastRecievedLen(void) const;

		virtual void  SetBuffer(AsynIoBuffer * pBuffList,DWORD dwBuffCount);

		virtual AsynIoBuffer * GetBufferList();

		virtual DWORD GetBufferCount() const;

		virtual DWORD GetTransferredBytes() const;

		virtual void  SetTransferredBytes( DWORD bytes);

		virtual ULONG64 GetOffsetBytes();

		virtual void  SetOffsetBytes(ULONG64 offset);

		virtual BOOL  Success() const;

		virtual DWORD GetErrorCode() const;

		virtual void  SetErrorCode( DWORD err );

		virtual AsynIoDevice * GetAsynDevice() const;

		virtual void SetAsynDevice( AsynIoDevice * device);

		virtual AsynIoType GetType() const;

		virtual void SetType( AsynIoType op_type );

		virtual bool IsSimulation() { return m_bSimulation;}

		virtual void SetSimulation(bool is_simulation) {m_bSimulation=is_simulation;}

		AsynIoResultImp(); 

		AsynIoResultImp(AsynIoType opType,AsynIoHandler * handler);

		virtual ~AsynIoResultImp();

	protected:
		//////////////////////////////////////////////////////////////////////////
		AsynIoHandler *   m_pHandler;
		AsynIoDevice  *   m_pDevice;
		AsynIoBuffer      m_BuffList[MAX_ASYN_IO_BUFF_COUNT];
		DWORD             m_dwBuffCount;
		DWORD             m_dwTransferredBytes;
		DWORD             m_dwErrorCode;
		ULONG64           m_OffsetBytes;
		AsynIoType        m_Type;
		bool              m_bSimulation;

		//��һ�ν��յ������ݰ���һ���֣�������m_BuffList[0].buf��ͷλ�ã����ѽ��յ����ݳ���
		DWORD			  m_dwLastPacketRecievedLen;
	};

#endif
};

#endif//__ASYN_IO_RESULT_H__