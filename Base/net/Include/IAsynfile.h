/*******************************************************************
** �ļ���:	IAsynFile.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	03/04/2008
** ��  ��:	1.0
** ��  ��:	�첽�ļ����ʽӿ�
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __ASYN_FILE_H__
#define __ASYN_FILE_H__

//////////////////////////////////////////////////////////////////////////
// �����궨��
#ifndef NET_API
#	ifdef NET_EXPORTS
#		define NET_API		extern "C" __declspec(dllexport)
#	else
#		define NET_API		extern "C" __declspec(dllimport)
#	endif
#endif//NET_API

//////////////////////////////////////////////////////////////////////////

namespace xs
{
	/// �첽�ļ�IO����ӿ�
	struct IAsynFileHandler;

	enum OPEN_MODE
	{
		READ  = 0    ,  // ���ļ�
		WRITE        ,  // д�ļ�
		OPEN         ,  // ���ļ�,��������ھʹ���
		ONLY_OPEN    ,  // �������ļ�,��������ڲ�Ҫ����
		ALWAYS_CREATE,  // ÿ�ζ����´���
	};

	/**
	@name : �첽�ļ��ӿ�
	@brief: ��װ���ļ����첽��д
	*/
	struct IAsynFile
	{
		/**
		@name               : ���ļ� 
		@brief              :
		@param      path    : �ļ�·��
		@param      mode    : �򿪷�ʽ
		@param      handler : �������ӿ�
		@return             : ����򿪳ɹ�����true,���򷵻�false,GetLastError�ɲ�ѯ���������
		*/
		virtual bool Open(const char * path,OPEN_MODE mode,IAsynFileHandler * handler) = 0;

		/**
		@name		        : ��ȡ�ļ���С 
		@brief              :  
		@return             : �����ļ���С
		*/
		virtual unsigned __int64 Size() = 0;

		/**
		@name               : ���ļ��ж�ȡ����
		@brief              : ��ȡ�Ľ��ͨ���ص�IAsynFileHandler֪ͨ
		@param     pos      : ��ʼλ��,Ҫ��ȡ���������ļ��е�ƫ��
		@param expect_bytes : ������ȡ�����ݳ���
		@return             : �����ȡʧ���򷵻�false,�ɹ���ʼ��ȡ�򷵻�true
		*/
		virtual bool Read(unsigned __int64 pos,unsigned long expect_bytes) = 0;

		/**
		@name               : д�����ݵ��ļ���
		@brief              : ��ȡ�Ľ��ͨ���ص�IAsynFileHandler֪ͨ
		@param     pos      : ��ʼλ��,Ҫд����������ļ��е�ƫ��
		@param     data     : Ҫд�����������
		@param     len      : Ҫд������ݳ���
		@return             : ���д��ʧ���򷵻�false,�ɹ���ʼд�򷵻�true
		*/
		virtual bool Write(unsigned __int64 pos,const char * data,unsigned long len) = 0;

		/**
		@name         : ���ٶ���
		@brief        : ͬʱ��ر��ļ�
		*/
		virtual void Release() = 0;
	};

	/**
	@name : �첽�ļ���д����ӿ�
	@brief: �����ļ���д�ɹ�����¼�
	*/
	struct IAsynFileHandler
	{
		/**
		@name               : ��ȡ���ݳɹ�
		@brief              :
		@param     pos      : ��ʼλ��,Ҫ��ȡ���������ļ��е�ƫ��
		@param     data     : ��������
		@param     len      : ���ݳ���
		*/
		virtual void HandleReadSuccess(unsigned __int64 pos,const char * data,unsigned long len) = 0;

		/**
		@name               : д�����ݳɹ�
		@brief              :
		@param     pos      : ��ʼλ��,Ҫд����������ļ��е�ƫ��
		@param     len      : Ҫд������ݳ���
		*/
		virtual void HandleWriteSuccess(unsigned __int64 pos,unsigned long len) = 0;

		/**
		@name               : ��ȡ���ݳɹ�
		@brief              :
		@param     err      : �������
		@param     pos      : ��ʼλ��,Ҫ��ȡ���������ļ��е�ƫ��
		@param expect_bytes : ������ȡ�����ݳ���
		*/
		virtual void HandleReadFailed(unsigned long err,unsigned __int64 pos,unsigned long expect_bytes) = 0;

		/**
		@name               : д�����ݳɹ�
		@brief              :
		@param     err      : �������
		@param     pos      : ��ʼλ��,Ҫд����������ļ��е�ƫ��
		@param     data     : Ҫд�����������
		@param     len      : Ҫд������ݳ���
		*/
		virtual void HandleWriteFailed(unsigned long err,unsigned __int64 pos,unsigned long len) = 0;
	};

	/**
	@name         : �����첽�ļ�����
	@brief        :
	@param path   : �ļ�·��
	@param mode   : �򿪷�ʽ
	@return       : �����ʧ�ܷ���0,���򷵻ض���ָ��
	*/
	NET_API IAsynFile * CreateAsynFile();
};

#endif//__ASYN_FILE_H__