#ifndef __STREAMSYSTEM_H__
#define __STREAMSYSTEM_H__

#include "Stream.h"

namespace xs{
	/*! \addtogroup FileSystem
	*  �ļ�ϵͳ
	*  @{
	*/


/// ö����Callback
struct IListFileCallback;

/// �ļ�ϵͳ�ӿ�
struct IFileSystem
{
	/**���ļ�ϵͳ���߰�ϵͳ
	@param streamSysPath �ļ�ϵͳ·�����߰��ļ���
	*/
	virtual bool open(const char* streamSysPath) = 0;

	/**ĳ���ļ��Ƿ�λ�ڴ��ļ�ϵͳ��
	@param streamName �ļ���
	@return �Ƿ��ҵ�
	*/
	virtual bool find(const char* streamName) = 0;
	
	/**��ĳ���ļ�
	@param streamName �ļ���
	@return �ļ����������Ǵ����ļ�Ҳ�����ǰ��ļ�
	@remarks
	*/
	virtual Stream* get(const char* streamName) = 0;

	/**ö�ٴ��ļ�ϵͳ�µ������ļ�
	@param pCallback �ص��ӿڣ��������ղ��ҵ����ļ���
	@param p �Զ������
	*/
	virtual void list(IListFileCallback* pCallback,void *p) = 0;

	/**�ر��ļ�ϵͳ
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool close() = 0;

	/**�ͷ��ļ�ϵͳ
	*/
	virtual void release() = 0;


	/*
	//��ȡ�ļ�ϵͳ���֣��������
	*/
	virtual const char * getFileSystemName(void) = 0;
};


	/** @} */
}


#endif // __STREAMSYSTEM_H__
