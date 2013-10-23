#ifndef __MPKSTREAMSYSTEM_H__
#define __MPKSTREAMSYSTEM_H__

#include <vector>
#include "FileStream.h"
#include "IMpkManip.h"
#include "IFileSystem.h"

namespace xs{

/// ����ϵͳ
class  MpkFileSystem : public IFileSystem
{
public:
	MpkFileSystem();
	~MpkFileSystem();

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

private:
	IMpkManip* m_pMpkManip;

	std::string m_strMpkFileName;

};

}


#endif // __PKGSTREAMSYSTEM_H__
