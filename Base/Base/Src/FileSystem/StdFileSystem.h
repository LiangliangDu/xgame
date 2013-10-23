#ifndef __FILESTREAMSYSTEM_H__
#define __FILESTREAMSYSTEM_H__

#include "IFileSystem.h"

namespace xs{

/// �ļ���ϵͳ
class StdFileSystem : public IFileSystem
{
protected:
	CPathA	m_path;		/// �������ϵͳ�Ķ���Ŀ¼·�����磺e:\myGame\game001

public:
	StdFileSystem();
	~StdFileSystem();

	// IFileSystem
public:
	/**���ļ�ϵͳ���߰�ϵͳ
	@param streamSysPath �ļ�ϵͳ·�����߰��ļ���
	*/
	virtual bool open(const char* streamSysPath);

	/**ĳ���ļ��Ƿ�λ�ڴ��ļ�ϵͳ��
	@param streamName �ļ���
	@return �Ƿ��ҵ�
	*/
	virtual bool find(const char* streamName);

	/**��ĳ���ļ�
	@param streamName �ļ���
	@param
	@return �ļ����������Ǵ����ļ�Ҳ�����ǰ��ļ�
	@remarks
	*/
	virtual Stream* get(const char* streamName);

	/**ö�ٴ��ļ�ϵͳ�µ������ļ�
	@param pCallback �ص��ӿڣ��������ղ��ҵ����ļ���
	@param p �Զ������
	@return
	@remarks
	*/
	virtual void list(IListFileCallback* pCallback,void *p);

	/**�ر��ļ�ϵͳ
	@param
	@param
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool close();

	/**�ͷ��ļ�ϵͳ
	@param
	@param
	@return
	@remarks
	*/
	virtual void release();


	/*
	//��ȡ�ļ�ϵͳ���֣��������
	*/
	virtual const char * getFileSystemName(void);
};

}


#endif // __FILESTREAMSYSTEM_H__
