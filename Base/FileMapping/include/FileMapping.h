/*******************************************************************
** �ļ���:	FileMapping.h
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#pragma once

#include <map>
#include <string>

// �����궨��
#ifndef FM_API
#	ifdef FM_EXPORTS
#		define FM_API		extern "C" __declspec(dllexport)
#	else
#		define FM_API		extern "C" __declspec(dllimport)
#	endif
#endif//NET_API

namespace xs
{
	/**
	@purpose         : ����ӳ���ļ�����ʼ�������ڴ�
	@param	file_name: ӳ���ļ��ڴ����ϵ�λ��
	@param share_name: ������̹����ڴ�ʱʹ�õ�����
	@param page_size : �ڴ�ӳ���ܹ��ж��
	@param recover   : �Ƿ���ڴ��лָ���������Ķ��� 
	*/
	FM_API bool InitializeFileMapping(const std::string & file_name,const std::string & share_name,size_t page_size,bool recover);

	/**
	@purpose         : ȡ�ù����ڴ�ӳ��ĵ�ַ
	@return          :
	*/
	FM_API void * GetFileMappingAddr();

	/**
	@purpose         : �ڹ����ڴ������з���һ�������ڴ�
	@param   size    : Ҫ����Ĵ�С
	@param   name    : ���ÿ��ڴ�����.Ĭ��Ϊ��,��������������������ڴ�,Ҳ���������ڵ����ָ�ʱ�һ���Ҫ������
	@return          : �����ڴ��ַ
	*/
	FM_API void * ShareMemAlloc( int size,const char * name=0 );

	/**
	@purpose         : �ͷ���ǰ�ӹ����ڴ��з�����ڴ�
	@param   p       : �����ַ
	*/
	FM_API void ShareMemDealloc( void * p );

	/**
	@purpose         : ����һ���ѷ�����ڴ�
	@param   name    : �ڴ�����
	@return          : �����ڴ��ַ
	*/
	FM_API void * FindRecoveredMemory(const char * name);

	/**
	@purpose         : ȡ�����е��ѻָ����ڴ��
	*/
	FM_API bool GetAllRecoveredMemory(std::map<std::string,void *> & mem_list);
}