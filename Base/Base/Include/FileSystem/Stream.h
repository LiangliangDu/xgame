#ifndef __STREAM_H__
#define __STREAM_H__

#include <stdio.h>
#include "Common.h"
#include "Path.h"

namespace xs{
	/*! \addtogroup FileSystem
	*  �ļ�ϵͳ
	*  @{
	*/


/// �������ࣩ
class RKT_EXPORT Stream
{
protected:
	CPathA	m_path;		/// ��·��

	// ���죨������
public:
	Stream() { m_path.isFile(true); }
	Stream(const char* path);
	virtual ~Stream();

	// �ӿڷ���
public:
	/** ����(�ļ���Ĭ����ֻ������������ʽ�򿪣����������Ͳ����Ĵ�ģʽ)
	 @param mode ����ģʽ
	 @return �ɹ�����true�����򷵻�false
	 @note �й��ļ�����ģʽ����Ϣ��<br>

	- "r"	��    ,�ļ���������ʧ��<br>
	- "w"	д    ,�ļ��������򴴽�,�������������<br>
	- "a"	���  ,�ļ��������򴴽�<br>
	- "r+"	��д  ,�ļ���������ʧ��<br>
	- "w+"	��д  ,�ļ��������򴴽�,�������������<br>
	- "a+"	�����,�ļ��������򴴽�<br>
	- "t"	�ı���ʽ<br>
	- "b"	�����Ʒ�ʽ<br>
	 */
	virtual bool open(const char* mode = "rb") { return false; }

	/// �ر�������open��Ӧ��
	virtual bool close() { return false; }


	/** �����ж�ȡ���ݣ����ڰ��ļ��е��ļ�����ܾ�����Խ��Ķ�д��
	 @param buffer ��������ַ
	 @param toRead Ҫ��ȡ���ֽڴ�С
	 @return �ɹ�����true�����򷵻�false
	 */
	virtual bool read(IN OUT void* buffer, uint toRead) { return false; }

	/** �����ж�ȡ�ַ��������ڰ��ļ��е��ļ�����ܾ�����Խ��Ķ�д��
	@param str ��������ַ
	@param length ����������󳤶ȣ�ʵ�ʷ��صĳ���Ҳ�������������
	@return �ɹ�����true�����򷵻�false
	*/
	virtual bool readString(IN OUT char* str,IN OUT uint& length) { return false; }
	
	/** ������д�����ݣ����ڰ��ļ��е��ļ�����ܾ�����Խ��Ķ�д��
	 @param buffer ��������ַ
	 @param toWrite Ҫд����ֽڴ�С
	 @return �ɹ�����true�����򷵻�false
	 */
	virtual bool write(const void* bufer, uint toWrite)  { return false; }

	/** �ļ���дλ�ö�λ
	 @param offset ƫ����
	 @param from ������ָ����λ�ÿ�ʼ����ƫ�ƣ��ο�: SEEK_SET �ļ�ͷ; SEEK_CUR �ļ���ǰλ��; SEEK_END �ļ�β
	 @return 
	 */ 
	virtual bool seek(int offset, uint from = SEEK_SET) = 0;

	/// �ļ���дλ�ö�λ���ļ�ͷ
	virtual bool seekToBegin()  = 0;

	/// �ļ���дλ�ö�λ���ļ�β
	virtual bool seekToEnd()  = 0;

	/// ����ļ�ָ���λ��
	virtual int getPosition() const = 0;


	/// ���ļ��Ļ���������д�����(���ļ���֧��)
	virtual bool flush()  { return false; }


	/// ��ȡ�ļ�����(�ļ�û��ʱҲ�ܻ�ȡ����),����ǰ��ļ�,����ָѹ����ĳ���
	virtual uint getLength()  = 0;

	/// �������ĳ���
	virtual bool setLength(uint newLen)  { return false; }

	/** ������·��
	 @param path ����·����
	 @return �ɹ�����true�����򷵻�false
	 */ 
	virtual bool setPath(const char* path);


	/// ���Ƿ����(ע: ������֧��,����ʱ��ͨ��get(Handle, name)�ķ���ֵ���ж��Ƿ����)
	virtual bool isExist() const { return false; }

	/// ���Ƿ��ڿ���״̬
	virtual bool isOpen() const	{ return false; }


	/// ɾ����
	virtual bool remove() { return false; }

	/** ��������
	 @param newName �µ�����
	 @return �ɹ�����true�����򷵻�false
	 */ 
	virtual bool rename(const char* newName) { return false; }

	/** ���洢Ϊ�ļ�
	 @param newName Ҫ������ļ���
	 @return �ɹ�����true�����򷵻�false
	 */
	virtual bool save(const char* newName) { return false; }

	/// �ͷ�������
	virtual void release();
};


//////////////////////////////////////////////////////////////////////////

/** �л����ļ���ȫ·����
 @param path Ҫת�����ļ����������ǵ�ǰĿ¼�����·����
 @note ������ļ����ļ����ڵĸ���Ŀ¼�Ƿ���ڣ�����Ƿ����ʹ��@c checkPath
 */
 RKT_API void toggleFullPath(CPathA& path);

/** ���·���Ƿ���ڣ�����Ŀ¼·�����ļ�·����
 @param path ·����
 @param isAbsolutePath �Ƿ��Ǿ���·��
 @param attrib �����ļ�����Ŀ¼��������
 @return �ɹ�����true�����򷵻�false
 */
RKT_API bool checkPath(IN const char* path, IN OUT bool& isAbsolutePath, IN OUT uint& attrib);

/** ���·���Ƿ����ļ�
 @param path Ҫ����·������������·�������Զ���exe��������Ŀ¼Ϊ��ǰĿ¼���д���
 @return �ɹ�����true���������·�������ڻ�����Ŀ¼�򷵻�false
 */
RKT_API bool isFile(const char* path);

/** ���·���Ƿ���Ŀ¼
 @param path Ҫ����·������������·�������Զ���exe��������Ŀ¼Ϊ��ǰĿ¼���д���
 @return �ɹ�����true���������·�������ڻ������ļ��򷵻�false
 */
RKT_API bool isDirectory(const char* path);

/** ���ָ����·���Ƿ��Ǿ���·��
 @param path Ҫ����·��
 @return ����·������true�����򷵻�false
 */
RKT_API bool isAbsolutePath(const char* path);

/** �ݹ鴴��Ŀ¼
 @param absolutePath Ҫ�����ľ���·��
 @return �ɹ�����Ŀ¼�Ѵ��ڷ���true�����򷵻�false��ʧ�ܺ󲻴�����ܴ����˵�Ŀ¼
 */
RKT_API bool createDirectoryRecursive(const char* absolutePath);

/** �ݹ�ɾ��Ŀ¼
 @param absolutePath Ҫɾ���ľ���·��
 @return �ɹ�����Ŀ¼�����ڷ���true�����򷵻�false
 */
RKT_API bool removeDirectoryRecursive(const char* absolutePath);

/// Ŀ¼���mask
enum BrowseDirMask{bdm_file=0x1, bdm_dir=0x2};

/** ���Ŀ¼
 @param absoluteDir ����Ŀ¼·��
 @param relativeDir ���Ŀ¼�����ڼ�¼����Ŀ¼�������е���Ŀ¼�����λ��
 @param DIRPROC Ŀ¼�ص�����
 @param FILEPROC �ļ��ص�����
 @param userData �û��ṩ��˽������
 @param mask ��������ļ���Ŀ¼��mask��mask��0x1��ʾֻ���Ŀ¼��mask=0x2��ʾֻ����ļ����ɽ���or����
 @return �ɹ�����true�����򷵻�false
 @note �磺browseDirectory("e:\\mytestdir", "", CPkgOperation::dirProc, CPkgOperation::fileProc, (uint)this, 3);
 */
RKT_API bool browseDirectory(const char* absoluteDir, const char* relativeDir, bool (*DIRPROC)(const char*, const char*, uint), 
					  bool (*FILEPROC)(const char*, const char*, uint), uint userData, uint mask = bdm_file|bdm_dir,bool recursive = true);

	/** @} */
}

#endif // __STREAM_H__
