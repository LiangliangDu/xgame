//==========================================================================
/**
* @file	  : ActionList.h
* @author : 
* created : 2008-3-19   21:30
* purpose : �������б�
*/
//==========================================================================

#ifndef __ACTIONLIST_H__
#define __ACTIONLIST_H__

struct ActionInfo
{
	ulong actionId;
	int loops;
};

class ActionList
{
	enum { MaxActionCount = 8 };

	ActionInfo	mActionList[MaxActionCount];
	int			mCur, mCount;
	bool		mIsMoving;	/// �Ƿ������ƶ�

public:
	ActionList()
	{
		memset(mActionList, 0, sizeof(mActionList));
		mActionList[0].actionId = EntityAction_Stand;
		mActionList[0].loops = -1;
		mCur = 0;
		mCount = 1;
		mIsMoving = false;
	}

	
	// ����1�������޸Ķ���
	//int setAction(ulong actionId, int loops, bool bForceStop = false)
	//{
	//	Assert(loops != 0);
	//	if (mCount > 0)
	//	{
	//		//if (mActionList[mCur].actionId == actionId && actionId == EntityAction_Stand) return 0; // ֻ��վ�����������жϣ���������ʹ��������ͬ�ļ��ܣ���һ�λ�û�ж���
	//		if (mActionList[mCur].actionId == EntityAction_Death) 
	//			return 0;
	//		//if (mIsMoving && actionId != EntityAction_Walk && actionId != EntityAction_Run )return 0; 
	//		//if (mActionList[mCur].actionId == EntityAction_JumpStart||mActionList[mCur].actionId == EntityAction_JumpMidway||mActionList[mCur].actionId == EntityAction_JumpEnd) return 0;//��Ծ�����ȼ�
	//	}

	//	// ���ܶ����������ܻ�ʱ�����ܶ������ܱ���ϣ������ܻ�����
	//	if (actionId == EntityAction_CombatWound && mActionList[mCur].actionId >= EntityAction_Attack)
	//	{
	//		return 0;
	//	}

	//	// �ƶ������У���ʱ�����ܻ���������Ϊ�������������
	//	if (actionId == EntityAction_CombatWound && mIsMoving)
	//	{
	//		return 0;
	//	}


	//	if (loops > 0) // ���һ����ѭ���Ķ������������¶���
	//	{
	//		if (mActionList[mCur].actionId == EntityAction_Stun && actionId!=EntityAction_Death) return 0;

	//		// add by zjp
	//		//�ƶ������ܻ�ʱ�����
	//		//if (actionId == EntityAction_CombatWound && mActionList[mCur].actionId == EntityAction_Run)
	//		//{
	//		//	mCount = 0;

	//		//	mActionList[mCount].actionId = actionId;
	//		//	mActionList[mCount].loops = loops;
	//		//	mCount++;

	//		//	if (actionId != EntityAction_Death && actionId != EntityAction_Stand)
	//		//	{
	//		//		mActionList[mCount].actionId = EntityAction_Run;
	//		//		mActionList[mCount].loops = -1;
	//		//		mCount++;
	//		//	}

	//		//	mCur = 0;
	//		//	return 1;
	//		//}
	//		//else
	//		{
	//			mCount = 0;

	//			mActionList[mCount].actionId = actionId;
	//			mActionList[mCount].loops = loops;
	//			mCount++;

	//			// û��Ҫ���վ�������������վ��NPC�Ķ�������Ӱ�죬����NPC�Ῠ����������Щ
	//			if (actionId != EntityAction_Death && actionId != EntityAction_Stand)
	//			{
	//				mActionList[mCount].actionId = EntityAction_Stand;
	//				mActionList[mCount].loops = -1;
	//				mCount++;
	//			}

	//			mCur = 0;
	//			return 1;
	//		}
	//	}
	//	else // ���һ��ѭ������
	//	{
	//		// ʹ�ý���˷���ʱ�򣬿����ƶ������ǲ�Ҫ����䶯��
	//		if ( !bForceStop && (actionId == EntityAction_Run || actionId == EntityAction_Walk || actionId == EntityAction_Stand) && mActionList[mCur].actionId == EntityAction_Skill_16)
	//		{
	//			return 2;
	//		}

	//		mCur = mCount = 0;
	//		mActionList[mCount].actionId = actionId;
	//		mActionList[mCount].loops = loops;
	//		mCount++;
	//		return 1;


	//		//if (mActionList[mCur].loops <= 0 ||
	//		//	actionId == EntityAction_Walk || // �ƶ����ȼ��Ƚϸ�
	//		//	actionId == EntityAction_Run) // clear and set
	//		//{
	//		//	mCur = mCount = 0;

	//		//	mActionList[mCount].actionId = actionId;
	//		//	mActionList[mCount].loops = loops;
	//		//	mCount++;

	//		//	return 1;
	//		//}
	//		//else // add
	//		//{
	//		//	if (mCount > mCur + 1 && mActionList[mCur].loops > 0) // ��ǰ�ǲ�ѭ���ģ�ȥ���м�ѭ���Ķ���
	//		//	{
	//		//		int next = mCur + 1;
	//		//		while (mActionList[next].loops > 0)
	//		//			next++;
	//		//		mCount = next;
	//		//	}

	//		//	mActionList[mCount].actionId = actionId;
	//		//	mActionList[mCount].loops = loops;
	//		//	mCount++;

	//		//	if (mCount <= 1) return 1;
	//		//}
	//	}

	//	return 0;
	//}

	int setAction(ulong actionId, int loops, bool bForceStop = false)
	{
		Assert(loops != 0);
		if (mCount > 0)
		{
			if (mActionList[mCur].actionId == EntityAction_Death) 
				return 0;
		}

		// ���ܶ����������ܻ�ʱ�����ܶ������ܱ���ϣ������ܻ�����
		if (actionId == EntityAction_CombatWound && mActionList[mCur].actionId >= EntityAction_Attack)
		{
			return 0;
		}

		// �ƶ������У���ʱ�����ܻ���������Ϊ�������������
		if (actionId == EntityAction_CombatWound && mIsMoving)
		{
			return 0;
		}


		if (loops > 0) // ���һ����ѭ���Ķ������������¶���
		{
			if (mActionList[mCur].actionId == EntityAction_Stun && actionId!=EntityAction_Death) return 0;
			mCount = 0;
			mActionList[mCount].actionId = actionId;
			mActionList[mCount].loops = loops;
			mCount++;
			// û��Ҫ���վ�������������վ��NPC�Ķ�������Ӱ�죬����NPC�Ῠ����������Щ
			if (actionId != EntityAction_Death && actionId != EntityAction_Stand)
			{
				mActionList[mCount].actionId = EntityAction_Stand;
				mActionList[mCount].loops = -1;
				mCount++;
			}

			mCur = 0;
			return 1;
		}
		else // ���һ��ѭ������
		{
			mCur = mCount = 0;
			mActionList[mCount].actionId = actionId;
			mActionList[mCount].loops = loops;
			mCount++;
			return 1;
		}

		return 0;
	}

	const ActionInfo& getCurActionInfo() const { return mActionList[mCur]; }

	const ActionInfo& nextAction()
	{
		if (mCur + 1 < mCount)
			mCur++;
		return mActionList[mCur];
	}

	bool hasNextAction()
	{
		return mCur + 1 < mCount;
	}

	inline ulong getCount() const
	{
		return mCount;
	}

	inline void setIsMoving(bool moving)
	{
		mIsMoving = moving;
	}

	inline bool isMoving() const
	{
		return mIsMoving;
	}

	// �����ʱ������
	void clear()
	{
		mCur = mCount = 0;
	}
	bool getAction(int index, ulong & actionId, int & loops)
	{
		if(index <0 || index >= mCount || index >= MaxActionCount ) return false;
		actionId = mActionList[index].actionId;
		loops = mActionList[index].loops;
		return true;
	}
};

#endif // __ACTIONLIST_H__