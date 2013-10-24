//==========================================================================
/**
* @file	  : MemObj.h
* @author : 
* created : 2008-4-11   15:40
* purpose : 
*/
//==========================================================================

#ifndef RKT_MEMOBJ_H
#define RKT_MEMOBJ_H

#include "Common.h"
#include "Thread.h"

namespace xs {


	/** �ڴ����ʹ��ʾ��

	���������Ϊ�ڴ������ôÿ��newһ����ʱ��ʵ��������new��n����ռ䣨nĬ��Ϊ64���û������Լ�ѡ��������Ƽ�64��
	ÿ���ͷ�һ������ʱ��û��������free��ֻ�ǽ����˻��գ������´�����ʱ���������ض������ڴ���䣬֧�ּ̳����ϵĸ�
	��֧������ڴ�������
	@code
	//test.h
	class CMyTest
	{
		DECLARE_MEMOBJ // or IMPLEMENT_MEMOBJ_SINGLETHREAD
	public:
		CMyTest();
		~CMyTest();
		void foo();
	private:
		ulong m_myVar;
	};

	// test.cpp
	IMPLEMENT_MEMOBJ(CMyTest, 64) // or IMPLEMENT_MEMOBJ_SINGLETHREAD(CMyTest, 64)
		CMyTest::CMyTest()
	{
	}
	CMyTest::~CMyTest()
	{
	}
	void foo()
	{
	}
	@endcode
	*/

	/// ������
	struct RKT_EXPORT DataChain
	{
		DataChain* prev;	/// ǰһ��������

		void* data()		{ return this + 1; }

		static DataChain* create(DataChain*& head, ulong blockCount, ulong blockSize)
		{
			Assert(blockCount > 0 && blockSize > 0);

			DataChain* p = (DataChain*) new uchar[sizeof(DataChain) + blockCount * blockSize];
			p->prev = head;
			return head = p;
		}

		void close()
		{
			DataChain* p = this;
			while (p != NULL)
			{
				uchar* bytes = (uchar*)p;
				DataChain* prev = p->prev;
				delete[] bytes;
				p = prev;
			}
		}
	};

	/// �ڴ����
	template<class ThreadModel>
	class MemObjT
	{
		struct Node
		{
			Node* next;	/// �����ڿ����ڴ�����Ч
		};

		ulong		mBlockSize;		/// ÿ����Ĵ�С���������Ĵ�С��
		ulong		mBlockCount;	/// ÿ����������Ŀ���������������
		DataChain*	mChainList;		/// ��¼ÿ����������Ŀ�
		Node*		mFreeNode;		/// ��ǰ���еĿ�ڵ�
		typename ThreadModel::mutex	mMutex;	/// ��Ӧ�߳�ģ�͵Ļ�����
	public:
		MemObjT(ulong blockSize, ulong blockCount = 64)
		{
			Assert(blockSize >= sizeof(Node));
			Assert(blockCount >= 1);

			if (blockSize < sizeof(Node)) blockSize = sizeof(Node);
			if (blockCount <= 1) blockCount = 64;

			mBlockSize = blockSize;
			mBlockCount = blockCount;
			mFreeNode = 0;
			mChainList = 0;
		}

		~MemObjT()
		{
			freeAll();
		}

		ulong getBlockSize() const		{ return mBlockSize; }

	public:
		void* alloc()
		{
			typename ThreadModel::scopelock guard(mMutex);

			if (!mFreeNode)
			{
				DataChain* newBlock = DataChain::create(mChainList, mBlockCount, mBlockSize); // �����µ�������
				Node* node = (Node*)newBlock->data(); // ��λ��������
				(uchar*&)node += (mBlockSize * mBlockCount) - mBlockSize; // ��λ�����һ���ڵ�

				// ���ڵ㽨�����ӹ�ϵ
				for (int i=mBlockCount-1; i>=0; i--, (uchar*&)node-=mBlockSize)
				{
					node->next = mFreeNode;
					mFreeNode = node;
				}
			}

			Assert(mFreeNode);

			void* node = mFreeNode;
			mFreeNode = mFreeNode->next;
			return node;
		}

		void freeObj(void* ptr)
		{
			typename ThreadModel::scopelock guard(mMutex);

			if (ptr)
			{
				Node* node = (Node*)ptr;
				node->next = mFreeNode;
				mFreeNode = node;
			}
		}

		void freeAll()
		{
			typename ThreadModel::scopelock guard(mMutex);

			mChainList->close();
			mChainList = 0;
			mFreeNode = 0;
		}
	};

	typedef  MemObjT<SingleThread>	SingleThreadMemObj;
	typedef  MemObjT<MultiThread>	MultiThreadMemObj;

	// ����
	template class RKT_EXPORT MemObjT<SingleThread>;
	template class RKT_EXPORT MemObjT<MultiThread>;


	/** DECLARE_MEMOBJ_SINGLETHREAD -- ���߳�ͬ���ڴ��������������������ʹ�� */
#define DECLARE_MEMOBJ_SINGLETHREAD \
public:\
	void* operator new(size_t)						{ return sAlloc.alloc();}\
	void* operator new(size_t, void* p)				{ return p; }\
	void* operator new(size_t, const char*, int)	{ return sAlloc.alloc();}\
	void operator delete(void* p)					{ sAlloc.freeObj(p); }\
	void operator delete(void* p, const char*, int)	{ sAlloc.freeObj(p);}\
protected:\
	static SingleThreadMemObj sAlloc;


	/** IMPLEMENT_MEMOBJ_SINGLETHREAD -- ���߳�ͬ���ڴ����ʵ�֣���ʵ���ļ���ʹ�� */
#define IMPLEMENT_MEMOBJ_SINGLETHREAD(classname, blockcount)	SingleThreadMemObj classname::sAlloc(sizeof(classname), blockcount);


	/** DECLARE_MEMOBJ -- �߳�ͬ���ڴ��������������������ʹ�� */
#define DECLARE_MEMOBJ \
public:\
	void* operator new(size_t)						{ return sAlloc.alloc();}\
	void* operator new(size_t, void* p)				{ return p; }\
	void* operator new(size_t, const char*, int)	{ return sAlloc.alloc(); }\
	void operator delete(void* p) 					{ sAlloc.freeObj(p); }\
	void operator delete(void* p, const char*, int)	{ sAlloc.freeObj(p); }\
protected:\
	static MultiThreadMemObj sAlloc;


	/** IMPLEMENT_MEMOBJ -- �߳�ͬ���ڴ����ʵ�֣���ʵ���ļ���ʹ�� */
#define IMPLEMENT_MEMOBJ(classname, blockcount)					MultiThreadMemObj classname::sAlloc(sizeof(classname), blockcount);

} // namespace

#endif // RKT_MEMOBJ_H