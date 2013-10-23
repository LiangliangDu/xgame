#ifndef __I_MPK_MANIP_H__
#define __I_MPK_MANIP_H__

#include <string>

namespace xs{
	/*! \addtogroup FileSystem
	*  �ļ�ϵͳ
	*  @{
	*/


/** Mpk file�����ӿ� */
struct IMpkFileManip
{
	/**�ͷ��Լ�
	*/
	virtual void release() = 0;

	/**��ȡ����
	@param pBuffer ���ݻ�����
	@param size Ҫ��ȡ�����ݳ���
	@return �Ƿ��ȡ�ɹ�
	@remarks
	*/
	virtual bool read(void *pBuffer,uint size) = 0;

	/**��λ�ļ�λ��
	@param length ƫ����
	@param from �����￪ʼ,SEEK_SET��
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool seek(uint length,uint from) = 0;

	/**��õ�ǰ�ļ�ָ��
	*/
	virtual uint getPos() = 0;

	/**�ļ���С
	@return �ļ���С
	@remarks
	*/
	virtual uint size() = 0;

	/**���ԭʼ�ļ���С
	@return ԭʼ�ļ���С
	@remarks
	*/
	virtual uint getOriginSize() = 0;

	/**���ѹ������ļ���С
	@return ѹ������ļ���С
	@remarks
	*/
	virtual uint getCompressedSize() = 0;

	/**�Ƿ����
	@return �Ƿ����
	@remarks
	*/
	virtual bool isEncrypted() = 0;
};

struct IMpkManipCallback
{
	/**Mpk�����Ļص�
	@param strFilename �ļ���
	@param p �Զ������
	@return
	@remarks
	@see IMpkManip
	*/
	virtual void onProcessFile(const std::string& strFilename,void *p) = 0;
};

/** Mpk�����ӿ� */
struct IMpkManip
{
	/**�ͷ��Լ�
	*/
	virtual void release() = 0;

	/**��һ�����ļ�
	@param mpkFilename �ļ���
	@param bCreateNew �Ƿ񴴽����ļ�
	@return �Ƿ�ɹ����ļ�
	@remarks
	*/
	virtual bool open(const char* mpkFilename,bool bCreateNew) = 0;

	/**�ر��ļ�
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool close() = 0;

	/**�Ƿ��и��ļ���filename
	@return �ļ��Ƿ����
	@remarks
	*/
	virtual bool hasFile(const char* filename) = 0;

	/**��һ���ļ�
	@param filename �ļ���
	@return �ļ���������ָ��
	@remarks
	*/
	virtual IMpkFileManip* openFile(const char* filename) = 0;

	/**��ѹĿ¼
	@param source Դ·�� "Data\\Creatures\\char"
	@param targetDir Ŀ��·�� "C:\\Creatures"
	@param replaceExist �Ƿ��滻�Ѿ����ڵ��ļ�
	@param pCallback �ص��ӿڣ����ϲ��л�����������
	@param p �Զ�������
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool extractDir(const char* source,const char* targetDir,bool replaceExist,IMpkManipCallback *pCallback,void *p) = 0;

	/**��ѹ�ļ�
	@param source Դ·�� "Data\\Creatures\\char\\1.m2"
	@param targetFilename Ŀ���ļ��� "C:\\Creatures\\1.m2"
	@param replaceExist �Ƿ��滻�Ѿ����ڵ��ļ�
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool extractFile(const char* source,const char* targetFilename,bool replaceExist) = 0;

	/**ɾ��Ŀ¼
	@param dir ·�� "Data\\Creatures\\char"
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool removeDir(const char* dir) = 0;

	/**ɾ���ļ�
	@param filename �ļ���
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool removeFile(const char* filename) = 0;

	/**�������ļ�,����Ѿ��и�dest�ļ�����ô��ʧ��
	@param source Դ�ļ���
	@param dest Ŀ���ļ���
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool renameFile(const char* source,const char* dest) = 0;

	/**���һ���ļ�������
	@param sourceFilename �ļ��� "C:\\1.txt"
	@param targetFilename Ŀ���ļ� "Data\\1.txt"
	@param replaceExist �Ƿ��滻�����ļ�
	@param compress �Ƿ�ѹ��
	@param encrypt �Ƿ����
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool addFile(const char* sourceFilename,const char* targetFilename,bool replaceExist = true,bool compress = true,bool encrypt =false) = 0;

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
	virtual bool addDir(const char* sourceDir,const char* targetDir,bool replaceExist = true,bool compress = true,bool encrypt =false,IMpkManipCallback *pCallback = 0,void *p = 0) = 0;

	/**��λ����һ���ļ�
	@param szMask ͨ���"*.txt"
	@return �ļ���
	*/
	virtual const char* findFirstFile(const char* szMask) = 0;

	/**��λ����һ���ļ�
	@return �ļ���
	*/
	virtual const char* findNextFile() = 0;

	/**�رղ����ļ�
	*/
	virtual void findClose() = 0;

	/**Dump�����ļ�
	@param
	@param
	@return
	@remarks
	*/
	virtual void dumpListFile() = 0;

	/**ȡ�ð�ʹ���ʣ���������ܴ�����Ƭ
	@param mpkFilename ���ļ���
	@return �ٷֱȣ�88
	@remarks
	*/
	virtual uint getUseRate(const char* mpkFilename) = 0;

	/**������ļ���Ƭ
	@param mpkFilename ���ļ���
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool cleanupFragment(const char* mpkFilename) = 0;

	/**ȡ���б��ļ��������ڴ������
	@return �б��ļ���(listfile)
	@remarks���ڴ������
	*/
	virtual const std::string& getListFileName() = 0;
};

/// ����Mpk�ļ���������
RKT_API IMpkManip* createMpkManip();

	/** @} */
}

#endif