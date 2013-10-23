#ifndef __VirtualFileSystem_H__
#define __VirtualFileSystem_H__

#include <vector>
#include "Thread.h"

namespace xs{
	/*! \addtogroup FileSystem
	*  �ļ�ϵͳ
	*  @{
	*/


	struct IListFileCallback;
	class Stream;

	/**�ļ�ϵͳ
	@param
	@param
	@return
	@remarks
	*/
	class RKT_EXPORT FileSystem
	{
		typedef std::vector<IFileSystem*>		StreamSystemVector;
	public:

		/**��Ӳ���·��
		@param pPath ·��
		@return �ļ�ϵͳ
		@remarks
		*/
		IFileSystem*		addFindPath(const char* pPath);

		/**��һ���ļ�
		@param pFileName �ļ���
		@param mode �򿪷�ʽ
		@return ��ָ��
		@remarks
		*/
		Stream*	open(const char* pFileName,const char* mode = "rb");

		/**ͨ��һ���ļ�ϵͳ��һ���ļ�
		@param pStreamSystem �ļ�ϵͳ
		@param pFileName �ļ���
		@param mode �򿪷�ʽ
		@return ��ָ��
		@remarks
		*/
		Stream*	open(IFileSystem* pStreamSystem,const char* pFileName,const char* mode = "rb");

		/**�Ƿ����ҵ�ĳ���ļ�
		@param pFileName �ļ���
		@return �ļ��Ƿ�����ڵ�ǰ����·��
		@remarks
		*/
		bool		isExist(const char* pFileName);

		/**�оٵ�ǰ����·���µ������ļ�
		@param pCallback �ص�
		@param p �Զ������
		@return
		@remarks
		*/
		void		list(IListFileCallback *pCallback,void *p);
	private:
		StreamSystemVector		m_vStreamSystem;
		Mutex	m_mutex;
	public:
		FileSystem(){}
		~FileSystem();
	};

		RKT_API FileSystem*	getFileSystem();
		RKT_API IFileSystem*	openFileSystem(const char* szPath);

	class RKT_EXPORT CStreamHelper
	{
	public:
		CStreamHelper();
		CStreamHelper(Stream*);
		~CStreamHelper();
		Stream* operator->();
		operator Stream*();
		bool isNull();
		const CStreamHelper& operator=(Stream* pStream);
		void close();
		//operator bool();
	private:
		Stream*	m_pStream;
	};


	/** @} */
}

#endif