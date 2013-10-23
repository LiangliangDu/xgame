//==========================================================================
/**
* @file	  : Handle.h
* @author : 
* created : 2008-1-12   11:09
* purpose : �������Ĭ������Ϊ֧���̰߳�ȫ
*/
//==========================================================================

#ifndef __HANDLE_H__
#define __HANDLE_H__

#include "Common.h"

namespace xs {

/** 
 ����ԭ�������ԭ���е�������С�ڴ�����ԭ������������һ�������ľ��ϵ
 �й�ʹ�ã��������һ�����꣬������realloc������������ÿ��е��û������򣬸�
 ���ǳ�ʼ���������ϵ�������ͼ��������ڱ����������������ҿ��еľ���ڵ㣬ϵ
 ͳ���Ǽ�¼һ����ǰ���еĽڵ���������һ������رպ������ǵ�ǰ�Ŀ��нڵ����
 ��������ÿ�����нڵ�����ָ����һ�����нڵ㣬���Ի�������˼·������Ĵ����͹�
 �ղ����Ƿǳ���ģ�ʱ�临�Ӷ�ΪO(1)���ٿ����������Ч�����⣬ǰ�潲����ÿ����
 ���������д���������Create Count������һ�����о����һ�δ���ʱ��Count=1����
 ʱ������رոþ����Count���ǵ���1������һ��������������������ôCount�͵�
 ��Ϊ2��ÿ������������Count�Դӳ�ʼ����ͻ�һֱ�����������������ֵ�����´�
 ����ʱ���ὫCount���л��ơ�
 */

#define INVALID_HANDLE					(handle)0 /// ��Ч������壬�����жϷ��صľ���Ƿ�����Ч��,����isValidHandle��ͬ
	

	typedef ulong handle;


#ifdef RKT_DEBUG
#	define rktCreateHandle(userData)	createHandle((ulong)(userData), __FILE__, __LINE__)	/// ��������Ϣ�Ĵ���
#	define rktCloseHandle(h)			closeHandle(h, __FILE__, __LINE__)					/// ��������Ϣ�Ĺر�
#else
#	define rktCreateHandle(userData)	createHandle((ulong)(userData))	/// ��������Ϣ�Ĵ���
#	define rktCloseHandle(h)			closeHandle(h)					/// ��������Ϣ�Ĺر�
#endif


	/** �������
	 @param userData ����ϸ��ӵ��û�����
	 @return �ɹ����ش����ľ�������򷵻�NULL
	 @note �����˾��Ҫ�ǵùرոþ��������һ����ϰ�ߣ������ @c fclCreateHandle�괴��������������Դ��ϵ�����Ϣ
	 @see closeHandle
	 */
	#ifdef RKT_DEBUG
	RKT_API handle createHandle(ulong userData, const char* file = 0, uint line = 0);
	#else
	RKT_API handle createHandle(ulong userData);
	#endif


	/** �رվ��
	 @param h Ҫ�رյľ��
	 @return ��������Ч�򷵻�true�����򷵻�false
	 @note ����� @c fclCloseHandle��رվ�����������Դ��ϵ�����Ϣ
	 @see createHandle
	 */
	#ifdef RKT_DEBUG
	RKT_API bool closeHandle(handle h, const char* file = 0, uint line = 0);
	#else
	RKT_API bool closeHandle(handle h);
	#endif


	/** ��þ���ϸ��ӵ��û�����
	 @param h ����ľ��
	 @return ��������Ч�򷵻ظþ�����û����ݣ����򷵻�0
	 */
	RKT_API ulong getHandleData(handle h);


	/** ���þ���ϸ��ӵ��û�����
	 @param h Ҫ�����û����ݵľ��
	 @param userData Ҫ���õ��û�����
	 @return ��������Ч����true�����򷵻�false
	 */
	RKT_API bool setHandleData(handle h, ulong userData);


	/** �жϾ���Ƿ���Ч
	 @param h Ҫ�ж���Ч�Եľ��
	 @return ��Ч����true�����򷵻�false
	 */
	RKT_API bool isValidHandle(handle h);


	/** dump������еľ����Ϣ
	 */
	RKT_API void dumpHandleTable();


	/// �������ľ��ģ�壬����ָ��İ�ȫ�洢
	template<typename T>
	class Handle
	{
	public:
		handle h;	/// ��ָ��ľ��

		Handle()
		{ h = createHandle(0); }
/*
		explicit Handle(handle _h) : h(_h)
		{ }*/
		
		Handle(const T* ptr)
		{ h = createHandle((ulong)ptr); }

		~Handle()
		{ closeHandle(h); }


		/** Ϊ�����һ��ָ��
		 @param ptr �����ָ�룬����ΪNULL
		 @remark �ú���һ������Ĭ�Ϲ����°�һ��ָ��򽫾���󶨵�ָ����и���
		 */
		Handle& operator = (const T* ptr)
		{ setHandleData(h, (ulong)ptr); return *this; }


		/// ָ�������������
		T* operator->() const
		{ return (T*)getHandleData(h); }


		/// ֱ�ӻ�ȡ����󶨵�ָ��
		T* getPointer() const
		{ return (T*)getHandleData(h); }


		/// ֱ�ӻ�ȡ���
		operator handle() const
		{ return h; }


		/// �жϾ���Ƿ���Ч
		inline operator bool() const
		{ return isValidHandle(h); }
	};



} // namesapce

#endif // __HANDLE_H__
