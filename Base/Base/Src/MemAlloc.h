//==========================================================================
/**
* @file	  : MemAlloc.h
* @author : 
* created : 2008-4-11   15:40
* purpose : 
*/
//==========================================================================

#ifndef RKT_MEMALLOC_H
#define RKT_MEMALLOC_H

#include "Common.h"
#include "Singleton.h"
#include "Thread.h"
#include "ostrbuf.h"
#include <stdio.h>


#ifdef RKT_COMPILER_MSVC
#	pragma warning(push)
#	pragma warning(disable:4200)
#endif

#define MEMORY_THREAD

#ifdef MEMORY_THREAD
#	ifdef RKT_DEBUG
#		define MEM_LOCK		MultiThread::scopelock lock(mMutex FILE_LINE_PARAM)
#	else
#		define MEM_LOCK		MultiThread::scopelock lock(mMutex)
#	endif
#else
#	define MEM_LOCK			((void)0)
#endif

enum
{
	SB_SHIFT = 2,								/// ����ʱ������λ���������˳ߴ����Ĵ�С��
	SMALL_MEMORY_SIZE =	256,					/// С�ڴ��С����
	MEM_ALIGN = (1<<SB_SHIFT),					/// �ڴ�����С
	POOL_SIZE = (SMALL_MEMORY_SIZE>>SB_SHIFT),	/// С�ڴ�ص�Ͱ��
	NODE_GROW = 32,								/// С�ڴ�ÿ�η��䲻��ʱ��һ���Ե����Ľڵ���
};

#define round(s)					( ((s) + MEM_ALIGN - 1) & ~(MEM_ALIGN - 1) )
#define getSmallBlockIndex(s)		( (round((s)) - 1) >> SB_SHIFT )
#define getSM_NodeSize(s)			( (s) + sizeof(SM_Node) )
#define getLM_NodeSize(s)			( (s) + sizeof(LM_Node) )
#define ptr2DataNode(p)				( (DataNode*) ( (uchar*)(p) - sizeof(DataNode) ) )
#define ptr2LM_Node(p)				( (LM_Node*) ( (uchar*)(p) - sizeof(LM_Node) ) )
#define ptr2SM_Node(p)				( (SM_Node*) ( (uchar*)(p) - sizeof(SM_Node) ) )
#define getPtrSize(p)				( ptr2DataNode(p)->size )

namespace xs {

	/// ���ݽڵ㣬����������Ϣ 4 bytes
	struct DataNode
	{
		size_t	size;		/// �û����������ڴ��С(��������û��Ĵ�С)
		char	ptr[];		/// �û��ڴ��ָ��
	};


	/// С�ڴ�ڵ� 24 bytes
	struct SM_Node
	{
		//crr add SM_Node * pNext;2010-06-30 
		//���������һ��ָ�룬������truct FreeNode�����nextָ��ռλ!!!
		SM_Node * pNext;
#ifdef MEMORY_DEBUG // 20
		ulong		mask;
		const char* file;	/// �ļ�
		int			line;	/// �к�
		ulong		crc;	/// crcֵ�������ڴ�У��
		size_t		state;	/// 0-δʹ�� 1-ʹ���� 2-������
#endif
		DataNode	data;
	};


	/// ���ڴ�ڵ� 28 bytes
	struct LM_Node
	{
#ifdef MEMORY_DEBUG // 24
		ulong		mask;
		const char* file;	/// �ļ�
		int			line;	/// �к�
		ulong		crc;	/// crcֵ�������ڴ�У��
		LM_Node*	prev;	/// ǰһ���ڵ�
		LM_Node*	next;	/// ��һ���ڵ�
#endif
		DataNode	data;
	};


	/// С�� 8 bytes
	struct SmallBlock
	{
		SmallBlock* prev;	/// ǰһ��С��
		ulong		blocks;	/// ����

		void* data()		{ return this + 1; }
	};


	/// ���нڵ�(��ռ���ڴ�ռ�)
	struct FreeNode
	{
		FreeNode* next;	/// ��һ�����нڵ�
	};


	/// �ڴ������
	class MemAllocator
	{
#ifdef MEMORY_THREAD
		MultiThread::mutex	mMutex;
#endif
		SmallBlock*	mSBHead[POOL_SIZE];
		FreeNode*	mFreeNode[POOL_SIZE];

#ifdef MEMORY_DEBUG
		size_t		mTotalAllocSize;		/// ����ͨ���÷�����������ڴ��С����������Ϣ
		size_t		mTotalLargeMemorySize;	/// ���ڴ�ʵ�ʳߴ磨����������Ϣ���ڳߴ磩
		size_t		mTotalSmallMemorySize;	/// С�ڴ�ʵ�ʳߴ磨����������Ϣ���ڳߴ磩
		ulong		mSmallMemoryRequestCount;	/// С�ڴ��������
		size_t		mSmallMemoryRequestSize;	/// С�ڴ����������Ӧ�ĳߴ�

		// С�ڴ�ͳ��
		ulong		mSmallMemoryNodeCountPeak[POOL_SIZE];		/// С�ڴ�ڵ�ʹ�÷�ֵ
		ulong		mSmallMemoryNodeCountRequest[POOL_SIZE];	/// С�ڴ�ڵ�������
		ulong		mSmallMemoryNodeCountRelease[POOL_SIZE];	/// С�ڴ�ڵ��ͷ���

		// ���ڴ�ͳ��
		ulong		mLargeMemoryNodeCountPeak;		/// ���ڴ�ڵ�����ֵ
		ulong		mLargeMemoryNodeCountRequest;	/// ���ڴ�ڵ�������
		ulong		mLargeMemoryNodeCountRelease;	/// ���ڴ�ڵ��ͷ���
		size_t		mLargeMemoryNodeSizePeak;		/// ���ڴ�ڵ�ߴ��ֵ
		size_t		mLargeMemoryNodeSizeRequest;	/// ���ڴ�ڵ�����ߴ�
		size_t		mLargeMemoryNodeSizeRelease;	/// ���ڴ�ڵ��ͷųߴ�
		size_t		mMaxMemoryAllocSize;			/// ����һ���ڴ����ߴ�

		ulong		mMemoryDebugFlag;				/// �ڴ���Ա�־
		FILE*		mFileHandle;					/// д���ļ��õ��ļ�ָ��

		LM_Node		mLMHead;
#endif

	public:
		MemAllocator();
		~MemAllocator();

		static MemAllocator& getInstance()			{ static MemAllocator ma; return ma; }

		void* alloc(size_t s FILE_LINE_ARGS);
		void dealloc(void* p FILE_LINE_ARGS);
		void* _realloc(void* p, size_t s FILE_LINE_ARGS);

	private:
		LM_Node* requestLargeMemory(size_t s FILE_LINE_ARGS);
		void releaseLargeMemory(void* p FILE_LINE_ARGS);

		SM_Node* requestSmallMemory(size_t s FILE_LINE_ARGS);
		void releaseSmallMemory(void* p FILE_LINE_ARGS);

		SmallBlock* requestSmallBlock(SmallBlock*& head, size_t s FILE_LINE_ARGS);
		void releaseSmallBlock(SmallBlock* head FILE_LINE_ARGS);
		
		inline void* sysAlloc(size_t s);
		inline void sysFree(void* p);

		void log(ostrbuf& osb);
	public:
		ulong setMemoryDebugFlag(ulong flag);
		void reportMemoryLeak();
		void reportMemoryStatistics();

	};


} // namespace

#ifdef RKT_COMPILER_MSVC
#	pragma warning(pop)
#endif

#endif // RKT_MEMALLOC_H