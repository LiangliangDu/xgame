// ===========================================================================
//	filename: 	custom_allocator.h
//
//	author:		CHENTAO
//
//	created:	2008/01/12
//	
//	purpose:	�Զ����ڴ���������
//
// ===========================================================================

#ifndef  __custom_allocator_h__
#define  __custom_allocator_h__

#include <map>
#include <set>
#include <string>

#define  ALIGN_SIZE          64             // 64�ֽڶ���
#define  EMPTY_BLOCK         0x00           // �տ��־
#define  ALLOCATED_BLOCK     0xAD           // �տ��־

// ---------------------------------------------------------------------------
// Name	: �Զ����ڴ���������
// Desc :
// ���� :
//        1.ά��һ����ڴ������Ժ�ÿ�η���/�ͷ��ڴ�Ӹ��������
//        2.֧�ֽ���δ��ڴ����л����Ժ�����ʱ���Ի�ԭ�ϴη�����Ķ���
// ---------------------------------------------------------------------------

class custom_allocator
{
public:
	//////////////////////////////////////////////////////////////////////////
	struct MEM_BLOCK
	{
		unsigned int  _size;            // �ڴ���С
		unsigned char _state;           // �ڴ��״̬,�Ƿ��ѷ���
		unsigned char _name_len;        // �ڴ��ʶ,����
		unsigned char _verify[2];       // У���Ƿ���һ���Ϸ����ڴ��ṹ

		void clear() 
		{
			_verify[0]='M';
			_verify[1]='B';
			_state = EMPTY_BLOCK;
			_name_len = 0;
		}
		bool is_valid() const { return _verify[0]=='M' && _verify[1]=='B'; } 
	};
	typedef  std::set<MEM_BLOCK *> FREE_LIST;
	typedef  std::map<std::string,void *> ALLOCATED_MAP;

	/**
	@purpose          : �����ڴ�ҳ�棬�Ժ�ÿ�η���/�ͷ��ڴ�Ӹ�ҳ�����
	@param  page      : �ڴ�ҳ���ַ
	@param  page_size : �ڴ�ҳ�泤��
	*/ 
	void set_mem_page(void * page,unsigned int page_size );

	/**
	@purpose          : �����ڴ�ҳ�棬���ָ�ҳ���ϵ��ڴ�������
	@param  page      : �ڴ�ҳ���ַ
	@param  page_size : �ڴ�ҳ�泤��
	@param  recover_map:�����ѷ�����ڴ漰���ʶ
	@return		      : �Ƿ�ָ��ɹ�
	*/
	bool recover_alloc_info(void * page,unsigned int page_size);

	/**
	@purpose          : ����һ���ѷ�����ڴ� (Ŀǰֻ�ܲ��Ҵ��ڴ�ҳ���лָ����ڴ�)
	@param	 mem_name : �ڴ��ʶ������
	@return		      : ����ҵ��򷵻ظ��ڴ�ĵ�ַ�����򷵻�0
	*/
	void * find_mem_block(const std::string mem_name);

	/**
	@purpose          : ����һ��ָ����С���ڴ�
	@param	size      : ��Ҫ��������ڴ�
	@param mem_name   : �����������ڴ���һ�����֣����ڵ��Ի�ָ��ڴ�
	@return		      : �������ɹ��򷵻ط�����ڴ��ַ�����򷵻�null
	*/
	void * allocate(size_t size,const std::string * mem_name = 0);

	/**
	@purpose         : �ͷ�һ���ѷ�����ڴ�
	@param	p	     : Ҫ�ͷŵ��ڴ��ַ
	@return		     : �����������������ڴ棬���ͷųɹ��������ͷ�ʧ��
	*/
	bool deallocate(void *p);

protected:
	FREE_LIST            _free_blocks;

public:
	ALLOCATED_MAP        _alloc_blocks;
};

#endif// __custom_allocator_h__
