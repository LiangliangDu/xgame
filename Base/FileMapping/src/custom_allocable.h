// ===========================================================================
//	filename: 	custom_allocable.h
//
//	author:		CHENTAO
//
//	created:	2008/01/11
//	
//	purpose:	�Զ���������
//
// ===========================================================================

#ifndef  __custom_allocable_h__
#define  __custom_allocable_h__

#include <new>
#include <string>
#include "alloc_debuger.h"

// ---------------------------------------------------------------------------
// Name	: �Զ���������
// Desc : ���ģ��ʵ����һ���࣬�����ڴ���������û��Զ����
// param: 
//        ALLOC         : �ڴ������
//        ALLOC_DEBUGER : �ڴ��������� 
// ---------------------------------------------------------------------------
template
<
    typename T,
	typename ALLOC = std::allocator<T>,
	typename ALLOC_DEBUGER = no_alloc_debuger
>
class custom_allocable
{
public:
	//static void * operator new(size_t size)
	//{
	//	ALLOC alloc;
	//	return alloc.allocate(size,0);
	//}

	static void operator delete(void * p)
	{
		ALLOC alloc;
		alloc.deallocate(p,0);

#		ifdef DEBUG_NEW
			ALLOC_DEBUGER alloc_debuger;
			alloc_debuger.unrecord(p);
#		endif
	}

	//static void* operator new [](size_t size)
	//{
	//	ALLOC alloc;
	//	return alloc.allocate(size,0);
	//}

	static void operator delete[](void *p,size_t size)
	{
		ALLOC alloc;
		alloc.deallocate(p,size);

#		ifdef DEBUG_NEW
			ALLOC_DEBUGER alloc_debuger;
			alloc_debuger.unrecord(p);
#		endif
	}

	// �õ���MFC������һ��Debug new
#	ifdef DEBUG_NEW
	static void * operator new(size_t n, const char * file, int line)
	{	
		void * p = operator new(n);

		ALLOC_DEBUGER alloc_debuger;
		alloc_debuger.record(p,n,file);

		return p;
	}
	
	static void * operator new[](size_t n, const char * file, int line)
	{	
		void * p = operator new[](n);

		ALLOC_DEBUGER alloc_debuger;
		alloc_debuger.record(p,n,file);

		return p;
	}

#	endif
	//static void * operator new(size_t size,const std::string name)
	//{
	//	ALLOC alloc;
	//	return alloc.allocate(size,&name);
	//}

};

#endif// __custom_allocable_h__
