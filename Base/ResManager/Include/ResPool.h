//==========================================================================
/**
* @file	  : ResPool.h
* @author : 
* created : 2008-1-18   13:46
* purpose : 
*/
//==========================================================================

#ifndef __RESPOOL_H__
#define __RESPOOL_H__

#include"IResourceManager.h"
#include "Common.h"
#include <list>


/**
	��Դ�أ����ڻ���ϵͳ����Դ����Щ��Դһ���������ܶ࣬����������ʱ�������޸�
*/



namespace xs {
    

	/// �ؽڵ�
	template<class KeyType>
	class PoolNode
	{
		KeyType			mId;
		int				mRefs;
	
	public:
		PoolNode(){ mRefs = 0; }
		/// ��ȡ������ռ�ڴ�Ĵ�С
		virtual ulong getSize() const = 0;

		/// ÿ��������һ����ֵ��֮��Ӧ
		virtual KeyType getKey() const = 0;

		/// �ͷŶ���(���������ü���)
		virtual void release() = 0;

		virtual ResourceState getState() const = 0 ;

		/// �õ��ڵ�����ô���
		int getRefCount() const							{ return mRefs; }

		/// ���һ������
		int incRef()									{ return ++mRefs; }

		/// ��ȥһ������(���ǵ�����صĿɻ����ԣ������������ü���Ϊ0ʱ������release����)
		int decRef()									{ if(--mRefs<=0) mRefs=0;return mRefs; }
	};

	/** ��Դ��
	* ���룺
	* ��	PoolNodeType	������̳���PoolNode��ʵ��PoolNode�����й���
	*		KeyType			�������ͣ���ulong,__int64��

	* ˼·��
	* �������ü���, ����ص����������ⲿ��̬����(Ĭ��128M)
	* ���� list : һ����׼�б���¼����ʹ�õĽڵ㣻һ���ɻ����б���¼���ӵ��Ľڵ�, ������list�Ŀ�����ɾ����
	* �ڵ�Ĳ�ѯͨ��hash_map���ٲ�ѯ��hash_map��¼�˸��ڵ�������list�е�λ�ã�������hash_map�Ŀ�����������
	* ������Ϊ0ʱ����ɾ�����ŵ��ɻ���list��
	* 2011.3.24 zgz
	* �޸�Ϊ3��list�� һ����׼�б���¼����ʹ�õĽڵ㣻һ���ɻ����б���¼���ӵ��Ľڵ㣻һ���ӳٻ����б����б�
	* �еĽڵ����ٱ���2���ӣ�����Ƶ��ʹ�õ���Դ���ͷ�
	*/
	template <class PoolNodeType, class KeyType>
	class ResPool
	{
	private:
		typedef  typename std::list<PoolNodeType>				NodeList;
		typedef HashMap<KeyType, typename NodeList::iterator>		    NodeMap;
		typedef HashMap<KeyType, DWORD>							DelayNodeTick;

		ulong		mMemSize;			/// ��ǰ���ж�����ռ���ڴ��� 
		NodeList	mNodeList;			/// ��׼�ڵ��б�
		NodeList	mRecycledNodeList;	/// �ɻ��սڵ��б�
		NodeList	mDelayRecycledNodeList;	/// �ӳٵĿɻ��սڵ��б�
		NodeMap		mNodeMap;			/// �ڵ�ӳ��
		ulong		mMaxPoolSize;		/// ������ܹ����ɵ�����ڴ���

		DelayNodeTick mDelyNodeTick;    /// ��¼�ӳٻ��սڵ����ʼʱ��

	public:
		ResPool()
		{
			close();
#ifdef RKT_WIN32
			MEMORYSTATUS ms;
			GlobalMemoryStatus(&ms);
			mMaxPoolSize = ms.dwTotalPhys/2;
			if (mMaxPoolSize > 64*1024*1024) // Ĭ�����100M
				mMaxPoolSize = 64*1024*1024;
#else
			mMaxPoolSize = 64*1024*1024;
#endif
		}

		~ResPool()
		{
			close();
		}

		void checkSize();

		inline void grow(ulong size)
		{
			mMemSize += size;

#ifdef  RKT_TEST
			if (mMemSize> mMaxPoolSize)
			{
				WarningOnce("object pool overflow! mNodeList.size()="<<mNodeList.size()
					<<", mRecycledNodeList.size()="<<mRecycledNodeList.size()<<endl);
			}
#endif


#ifdef  RKT_TEST
			//Info("mem="<<_ff("%.02f", ((float)mMemSize/1024))<<"K"<<endl);
#endif
		}

		void close()
		{
			for (typename NodeList::iterator it=mNodeList.begin(); it!=mNodeList.end(); ++it)
			{
				(*it)->release();						
			}

			for (typename NodeList::iterator it=mRecycledNodeList.begin(); it!=mRecycledNodeList.end(); ++it)
				(*it)->release();

			for (typename NodeList::iterator it=mDelayRecycledNodeList.begin(); it!=mDelayRecycledNodeList.end(); ++it)
				(*it)->release();

			mNodeList.clear();
			mRecycledNodeList.clear();
			mDelayRecycledNodeList.clear();
			mDelyNodeTick.clear();

			mNodeMap.clear();
			mMemSize = 0;
		}

		/// �жϻ�����Ƿ��Ѿ����
		inline bool isOverflow() const
		{
			return (mMemSize > mMaxPoolSize);
		}

		/// ���û���صĴ�С
		inline void setMaxPoolSize(ulong dwMaxPoolSize)
		{
			// �ռ��С����С�ڵ�ǰ�������л������ĳߴ�,ɾ���ɻ��ն���,��ͷ��βɾ
			if (dwMaxPoolSize < mMaxPoolSize && mMemSize > dwMaxPoolSize)
			{
				checkSize();
			}
			mMaxPoolSize = dwMaxPoolSize;
		}

		/// ���һ���½ڵ㣬ע������½ڵ�ʱ���ܻ��������������
		//modified by xxh
		//���Ӳ���bIncMemSize��Ŀ���ǿ��ǵ������߳�Ҳ�������ڴ��С��Ϊ��׼ȷ�����ڴ��С�����������˲���bIncMemSize
		inline bool addNode(PoolNodeType& node)
		{
#if  0 /*RKT_TEST*/
			if (mMemSize + node->getSize() > mMaxPoolSize)
			{
				WarningOnce("object pool overflow! mNodeList.size()="<<mNodeList.size()
					<<", mRecycledNodeList.size()="<<mRecycledNodeList.size()<<endl);
			}
#endif

			// ���һ������,����¼����ϣ��
			node->incRef();
			mNodeList.push_back(node);
			mNodeMap[node->getKey()] = --mNodeList.end();
			//modified by xxh , ��Ϊload��ʱ�������MemSize,�������ﲻ��Ҫ�����������ڴ�ӱ���ͬʱmMemSize�Ƿ�Ҫ������Ҳ�Ǹ�����
			//mMemSize += node->getSize();

			//removeNode(node->getKey());

#if  0 /*RKT_TEST*/
			Info(
				"addNode: key="<<node->getKey()
				<<",ref="<<node->getRefCount()
				<<",size="<<_ff("%.02f", ((float)node->getSize()/1024))
				<<"K,count="<<mNodeList.size()
				<<",mem="<<_ff("%.02f", ((float)mMemSize/1024))<<"K"<<endl);
#endif
			checkSize();

			return true;
		}

		/// �Ƴ��ڵ㣬������ü���Ϊ0��������ػ��пռ��򽫶����ӵ�����Ͱ��������������ɾ��
		inline bool removeNode(KeyType idKey, bool bDelayRecycle)
		{
			typename NodeMap::iterator it = mNodeMap.find(idKey);
			if (it != mNodeMap.end()) // exist!
			{
				typename NodeList::iterator list_it = (*it).second;

				//Info("removeNode:"<<(LONGLONG)idKey<<endl);

				if((*list_it)->decRef() == 0)
				{
						//Info("�ӵ��ɻ����б��β��:"<<(LONGLONG)idKey<<endl);
						//Info("removeNode: recycle object, id="<<(*list_it)->getKey()<<endl);

						//PoolNodeType pNode = (*list_it);
						/*if(pNode->getSize() == 0xfeeefeee)
						{
							breakable;
						}
						mNodeMap.erase(idKey);
						mNodeList.erase(list_it);
						pNode->release();
						return true;*/
						if (bDelayRecycle)
						{
							//�����ӳٻ����б�
							mDelayRecycledNodeList.push_back(*list_it);
							mNodeMap[idKey] = --mDelayRecycledNodeList.end();
							// ��¼��ǰʱ��
							mDelyNodeTick[idKey] = getTickCount();
						}
						else
						{
							//����ɻ����б�
							mRecycledNodeList.push_back(*list_it);
							mNodeMap[idKey] = --mRecycledNodeList.end();
						}
						
						mNodeList.erase(list_it);
						checkSize();
				}
				else
				{
					//Info("�޷��ӵ��ɻ����б��β��:"<<(LONGLONG)idKey<<endl);
				}

				return true;
			}
			return false;
		}


		/// ���Ҷ�Ӧ��ֵ�Ľڵ㣬�ҵ���������ü���������ڻ����б��У��������׼�б���
		PoolNodeType find(KeyType idKey)
		{
			typename NodeMap::iterator it = mNodeMap.find(idKey);
			if (it != mNodeMap.end()) // exist!
			{
				typename NodeList::iterator list_it = (*it).second;

				// ����ڿɻ����б��У���ŵ���׼�б���
				if ((*list_it)->getRefCount() == 0)
				{
					//Info("find: get object from recycle bin, id="<<idKey<<endl);
					mNodeList.push_back(*list_it);			// push to back
					mNodeMap[idKey] = --mNodeList.end();	// reset pointer
					if (mDelyNodeTick.find(idKey) != mDelyNodeTick.end())
					{
						mDelayRecycledNodeList.erase(list_it);
					}
					else
					{
						mRecycledNodeList.erase(list_it);		// delete node
					}					
					list_it = --mNodeList.end();			// update pointer					
				}

				(*list_it)->incRef();

				return (*list_it);
			}

			return 0;
		}
	};
}


#endif // __RESPOOL_H__