/*******************************************************************
** �ļ���:	AsynFileWrapper.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	03/04/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __ASYN_FILE_WRAPPER_H__
#define __ASYN_FILE_WRAPPER_H__

#include "IAsynfile.h"
#include "AsynFileDevice.h"
#include "AsynIoFrame.h"

namespace xs
{

	/**
	@name : �첽�ļ���װ��
	@brief: ְ��:
			1.��װ�첽�ļ����ʽӿ�
			2.�����첽��ȡʱû�а����ݶ���ȫҲ�᷵��(�����100�ֽ�,���ܶ���50�ֽ�Ҳ�᷵��)
			  ��������Ҫ��װһ��,ʵ��������ȡ
	*/
	class AsynFileWrapper : public IAsynFile,public AsynIoHandler
	{
	public:
		virtual bool Open(const char * path,OPEN_MODE mode,IAsynFileHandler * handler);

		virtual unsigned __int64 Size();

		virtual bool Read(unsigned __int64 pos,unsigned long expect_bytes);

		virtual bool Write(unsigned __int64 pos,const char * data,unsigned long len);

		virtual void Release();

		virtual void HandleIoComplete( AsynIoResult * result );

		handle GetSafeHandle() const { return m_hHandle; }

		IAsynFileHandler * GetEventHandler() const { return m_pHandler; }

		AsynFileWrapper() : m_pDevice(0),m_pHandler(0),m_hHandle(0){}

		virtual ~AsynFileWrapper(){}

	protected:
		AsynFileDevice      *   m_pDevice;
		IAsynFileHandler    *   m_pHandler;
		handle                  m_hHandle;
	};

};

#endif//__ASYN_FILE_WRAPPER_H__