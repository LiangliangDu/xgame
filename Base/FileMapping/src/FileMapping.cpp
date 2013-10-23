/*******************************************************************
** �ļ���:	FileMapping.cpp
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#include "stdafx.h"
#include "FileMapping.h"
#include "sharemem_allocator.h"

/**
@purpose         : ����ӳ���ļ�����ʼ�������ڴ�
@param	file_name: ӳ���ļ��ڴ����ϵ�λ��
@param share_name: ������̹����ڴ�ʱʹ�õ�����
@param page_size : �ڴ�ӳ���ܹ��ж��
@param recover   : �Ƿ���ڴ��лָ���������Ķ��� 
*/
FM_API bool InitializeFileMapping(const std::string & file_name,const std::string & share_name,size_t page_size,bool recover)
{
	return filemapping_allocator::getInstance().create(file_name,share_name,page_size,recover);
}

/**
@purpose         : ȡ�ù����ڴ�ӳ��ĵ�ַ
@return          :
*/
FM_API void * GetFileMappingAddr()
{
	return filemapping_allocator::getInstance()._mapping_addr;
}

/**
@purpose         : �ڹ����ڴ������з���һ�������ڴ�
@param   size    : Ҫ����Ĵ�С
@param   name    : ���ÿ��ڴ�����.Ĭ��Ϊ��,��������������������ڴ�,Ҳ���������ڵ����ָ�ʱ�һ���Ҫ������
@return          : �����ڴ��ַ
*/
FM_API void * ShareMemAlloc( int size,const char * name=0 )
{
	return filemapping_allocator::getInstance().allocate(size,name?&std::string(name):0);
}

/**
@purpose         : �ͷ���ǰ�ӹ����ڴ��з�����ڴ�
@param   p       : �����ַ
*/
FM_API void ShareMemDealloc( void * p )
{
	filemapping_allocator::getInstance().deallocate(p);
}

/**
@purpose         : ����һ���ѷ�����ڴ�
@param   name    : �ڴ�����
@return          : �����ڴ��ַ
*/
FM_API void * FindRecoveredMemory(const char * name)
{
	std::map<std::string,void *> & mem_list =  filemapping_allocator::getInstance()._alloc_blocks;
	std::map<std::string,void *>::iterator it = mem_list.find(name); 
	if ( it !=mem_list.end() )
	{
		return it->second;
	}

	return 0;
}

/**
@purpose         : ȡ�����е��ѻָ����ڴ��
*/
FM_API bool GetAllRecoveredMemory(std::map<std::string,void *> & mem_list)
{
	mem_list =  filemapping_allocator::getInstance()._alloc_blocks;
	return true;
}