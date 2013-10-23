#ifndef __MPKMANIP_H__
#define __MPKMANIP_H__

#include "IMpkManip.h"
#include "MpkLib.h"

namespace xs{

class MpkManip : public IMpkManip
{
	struct _Data
	{
		MpkManip *pThis;
		bool bReplaceExist;
		IMpkManipCallback *pCallback;
		void *pCallbackData;
		bool compress;
		bool encrypt;
	};
	static bool dirProc(const char* path, const char* relativePath, uint userData);
	static bool fileProc(const char* path, const char* relativePath, uint userData);
public:
	/**�ͷ��Լ�
	@param
	@param
	@return
	@remarks
	*/
	virtual void release();

	/**��һ�����ļ�
	@param mpkFilename �ļ���
	@param bCreateNew �Ƿ񴴽����ļ�
	@return �Ƿ�ɹ����ļ�
	@remarks
	*/
	virtual bool open(const char* mpkFilename,bool bCreateNew);

	/**�ر��ļ�
	@param
	@param
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool close();

	/**�Ƿ��и��ļ���filename
	@param
	@param
	@return �ļ��Ƿ����
	@remarks
	*/
	virtual bool hasFile(const char* filename);

	/**��һ���ļ�
	@param filename �ļ���
	@param
	@return �ļ���������ָ��
	@remarks
	*/
	virtual IMpkFileManip* openFile(const char* filename);

	/**��ѹĿ¼
	@param source Դ·�� "Data\\Creatures\\char"
	@param targetDir Ŀ��·�� "C:\\Creatures"
	@param replaceExist �Ƿ��滻�Ѿ����ڵ��ļ�
	@param pCallback �ص��ӿڣ����ϲ��л�����������
	@param p �Զ�������
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool extractDir(const char* source,const char* targetDir,bool replaceExist,IMpkManipCallback *pCallback,void *p);

	/**��ѹ�ļ�
	@param source Դ·�� "Data\\Creatures\\char\\1.m2"
	@param targetFilename Ŀ���ļ��� "C:\\Creatures\\1.m2"
	@param replaceExist �Ƿ��滻�Ѿ����ڵ��ļ�
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool extractFile(const char* source,const char* targetFilename,bool replaceExist);

	/**ɾ��Ŀ¼
	@param dir ·�� "Data\\Creatures\\char"
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool removeDir(const char* dir);

	/**ɾ���ļ�
	@param filename �ļ���
	@param
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool removeFile(const char* filename);

	/**�������ļ�,����Ѿ��и�dest�ļ�����ô��ʧ��
	@param source Դ�ļ���
	@param dest Ŀ���ļ���
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool renameFile(const char* source,const char* dest);

	/**���һ���ļ�������
	@param sourceFilename �ļ��� "C:\\1.txt"
	@param targetFilename Ŀ���ļ� "Data\\1.txt"
	@param replaceExist �Ƿ��滻�����ļ�
	@param compress �Ƿ�ѹ��
	@param encrypt �Ƿ����
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool addFile(const char* sourceFilename,const char* targetFilename,bool replaceExist = true,bool compress = true,bool encrypt =false);

	/**���һ��Ŀ¼������
	@param sourceDir Ŀ¼�� "C:\\Data"
	@param targetDir Ŀ��Ŀ¼ "Data\\char"
	@param replaceExist �Ƿ��滻�����ļ�
	@param compress �Ƿ�ѹ��
	@param encrypt �Ƿ����
	@param pCallback �ص�������ÿ���ļ��ص�һ��
	@param p �Զ���ص�����
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool addDir(const char* sourceDir,const char* targetDir,bool replaceExist = true,bool compress = true,bool encrypt =false,IMpkManipCallback *pCallback = 0,void *p = 0);

	/**��λ����һ���ļ�
	@param szMask ͨ���"*.txt"
	@param
	@return �ļ���
	@remarks
	*/
	virtual const char* findFirstFile(const char* szMask);

	/**��λ����һ���ļ�
	@param
	@param
	@return �ļ���
	@remarks
	*/
	virtual const char* findNextFile();

	/**�رղ����ļ�
	@param
	@param
	@return
	@remarks
	*/
	virtual void findClose();

	/**Dump�����ļ�
	@param
	@param
	@return
	@remarks
	*/
	virtual void dumpListFile();

	/**ȡ�ð�ʹ���ʣ���������ܴ�����Ƭ
	@param mpkFilename ���ļ���
	@param
	@return �ٷֱȣ�88
	@remarks
	*/
	virtual uint getUseRate(const char* mpkFilename);

	/**������ļ���Ƭ
	@param mpkFilename ���ļ���
	@param
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool cleanupFragment(const char* mpkFilename);

	/**ȡ���б��ļ��������ڴ������
	@param
	@param
	@return �б��ļ���(listfile)
	@remarks���ڴ������
	*/
	virtual const std::string& getListFileName();
	MpkManip() : m_hMpk(0),m_hFind(0){}
private:
	HANDLE m_hMpk;
	HANDLE m_hFind;
	SFILE_FIND_DATA	m_FileFindData;
};

}

#endif