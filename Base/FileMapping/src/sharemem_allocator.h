// ===========================================================================
//	filename: 	sharemem_allocator.h
//
//	author:		CHENTAO
//
//	created:	2008/01/12
//	
//	purpose:	ӳ���ļ��ڴ������
//
// ===========================================================================

#ifndef  __sharemem_allocator_h__
#define  __sharemem_allocator_h__

#include "custom_allocator.h"
#include "custom_allocable.h"
#include <windows.h>
#include "Singleton.h"
using namespace xs;

// ---------------------------------------------------------------------------
// Name	: ӳ���ļ��ڴ������
// Desc : ʹ���ļ�ӳ��ķ�ʽ�����ڴ棬Ȼ����ڴ���䵽�����ڴ���
// ---------------------------------------------------------------------------
class filemapping_allocator : public custom_allocator,public Singleton<filemapping_allocator>
{
public:
	/**
	@purpose         : ����ӳ���ļ�����ʼ�������ڴ�
	@param	file_name: ӳ���ļ��ڴ����ϵ�λ��
	@param share_name: ������̹����ڴ�ʱʹ�õ�����
	@param page_size : �ڴ�ӳ���ܹ��ж��
	@param recover   : �Ƿ���ڴ��лָ���������Ķ��� 
	@return		     : ��ʼ���ɹ�����true,���򷵻�false
	*/
	
	bool create( const std::string & file_name,const std::string & share_name,size_t page_size,bool recover );

	void close();

	filemapping_allocator() : _file_handle(0),_mapping_handle(0),_mapping_addr(0),_mapping_size(0)
	{
	}

	virtual ~filemapping_allocator() 
	{
		close();
	}

public:
	HANDLE         _file_handle;
	HANDLE         _mapping_handle;
	void   *       _mapping_addr;
	size_t         _mapping_size;
};


// ---------------------------------------------------------------------------
// Name	: �����ڴ������
// Desc : 
//        1.��ѭstl��׼,���Դ�����׼����,����std::list<T,sharemem_allocator<T>)
//        2.�����Ҫ�ӹ�һ������ڴ����,������������ class A : public custom_allocable<A,sharemem_allocator<A>>
// ---------------------------------------------------------------------------
template<typename T>
class sharemem_allocator : public std::allocator<T>
{
public:
	pointer allocate(size_type _N, const void * _Name)
	{
		// ����c++��׼
		if ( _N==0 )
			_N = 1;

		while(1)
		{
			pointer ret = (pointer)filemapping_allocator::get_instance()->allocate(_N,(const std::string *)_Name);
			if ( ret )
				return ret;

			new_handler global_handler = set_new_handler(0);
			set_new_handler(global_handler);
			if ( global_handler )
				global_handler();
			else
				throw(std::bad_alloc());
		}

		return 0;
	}
	
	void deallocate(void _FARQ *_P, size_type)
	{
		// ����c++��׼
		if ( _P==0 )
			return;

		if ( !filemapping_allocator::get_instance()->deallocate(_P) )
			throw(std::bad_alloc());
	}
};

//// ������д
//template<typename T>
//class share_alloc : public custom_allocable<T,sharemem_allocator<T> // ? vc6������һ��Ҫ��һ��> ����ʶ�������˿�Ц����
//{
//};


#endif// __sharemem_allocator_h__
