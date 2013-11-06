//==========================================================================
/**
* @file	  : EffectControl.h
* @author : 
* created : 2008-4-6   17:06
* purpose : 
*/
//==========================================================================

#ifndef __EFFECTCONTROL_H__
#define __EFFECTCONTROL_H__

#include "MagicView.h"
#include "IEntityFactory.h"
#include "OffsetArray.h"
#include "ShadowManager.h"
#include "JumpManager.h"
#include "SkillViewData.h"

class EffectControl;
struct IEffectControlObserver
{
	virtual void onDestroy(EffectControl*) = 0;
};

class EffectControl : public IEffectObserver
{
	IEffectControlObserver*	mObserver;
	handle					mSrc;
	ulong					mViewId;
protected:
	handle					mHandle;

public:
	EffectControl() : mObserver(0), mSrc(INVALID_HANDLE), mViewId(0) {}
	virtual ~EffectControl()
	{
	}
	virtual void release()
	{
		if (mObserver)
		{
			mObserver->onDestroy(this);
		}

		if (mHandle != INVALID_HANDLE) 
			closeHandle(mHandle); 
		delete this;
	}
	void CreateHandle()
	{
		mHandle = createHandle((ulong)this);
	}
	void setObserver(IEffectControlObserver* ob)	{ mObserver = ob; }
	void setSrc(handle src)			{ mSrc = src; }
	handle getSrc() const			{ return mSrc; }
	void setViewId(ulong viewId)	{ mViewId = viewId; }
	ulong getViewId() const			{ return mViewId; }
	virtual void onFinished(MagicView* ev) {}
	MagicView* createGeneralEffect(const MagicContext_General& context);
};


class EffectControlManager : public IEffectControlObserver, public SingletonEx<EffectControlManager>
{
	typedef std::list<EffectControl*>	EffectControlList;
	EffectControlList	mList;
public:
	~EffectControlManager()
	{
		for (EffectControlList::iterator it=mList.begin(); it!=mList.end(); ++it)
		{
			(*it)->setObserver(NULL);
			(*it)->release();
		}
		mList.clear();
	}
	void add(EffectControl* ctrl)
	{
		if (ctrl)
		{
			ctrl->setObserver(this);
			mList.push_back(ctrl);
		}
	}

	// ɾ��һ����Ч������Ч�Ĵ�����Ϊsrc��IDΪviewId
	void remove(handle src, ulong viewId)
	{
		for (EffectControlList::iterator it=mList.begin(); it!=mList.end(); ++it)
		{
			if ((*it)->getSrc() == src && (*it)->getViewId() == viewId)
			{
				EffectControl* ctrl = (*it);
				mList.erase(it);
				ctrl->setObserver(NULL);
				ctrl->release();
				return;
			}
		}
	}

	// �������ܴ��������Ч���˳�����״̬ʱҪȫ��ɾ��
	void removeAll(handle src, ulong viewId)
	{
		struct EffectControlComparison: binary_function<EffectControl*, pair<handle,ulong>, bool>
		{
			bool operator()(EffectControl*& val,pair<handle,ulong> key) const
			{
				bool bResult = (val->getSrc() == key.first && val->getViewId() == key.second );
				if (bResult)
				{
					val->setObserver(NULL);
					val->release();
				}
				return bResult;
			}
		};

		pair<handle,ulong>(src,viewId);
		EffectControlList::iterator newEnd = std::remove_if(mList.begin(),mList.end(),bind2nd(EffectControlComparison(), pair<handle,ulong>(src,viewId)));
		mList.erase(newEnd, mList.end());	
	}

	virtual void onDestroy(EffectControl* ctrl)
	{
		EffectControlList::iterator it = std::find(mList.begin(), mList.end(), ctrl);
		if (it != mList.end())
		{
			mList.erase(it);
			return;
		}
	}
};

/// ͨ����Ч��������
struct EffectContext_General
{
	ulong		magicId;/// ��ЧId
	int			loops;	/// ��Чѭ������
	ulong		angle;	/// ��Ч�ĽǶ�(���ű��趨������Ч�Ƕ�ʱ��������)
	handle		owner;	/// ����ӵ����(��һ���Ǽ��ܷ�����)
	POINT		tile;	/// ����λ�ã�������ǰ󶨵�EntityView����Ļ���

	EffectContext_General() : magicId(0), loops(0), angle(0), owner(0) { tile.x = tile.y = 0;}
};

/// ͨ���������
//template<class TAttackView, class TAttackContext, class TDamageView, class TDamageContext>
class EffectControl_General : public EffectControl
{
public:
	EffectControl_General() { }
	virtual ~EffectControl_General() 
	{
	}

	bool create(const EffectContext_General& context)
	{
		MagicContext_General mc;
		mc.magicId = context.magicId;
		mc.loops = context.loops;
		mc.angle = context.angle;
		mc.owner = context.owner;
		mc.tile = context.tile;
		MagicView* magic = (MagicView*)gGlobalClient->getEntityFactory()->createMagic(MagicType_General, &mc, sizeof(mc));
		if (!magic)
		{
			return false;
		}
		CreateHandle();
		magic->setEffectObserver(mHandle);

		return true;
	}

	void close() { }

	virtual void onFinished(MagicView* ev)
	{
		if (ev != NULL)
		{
			ev->release();
		}
		
		/*
		�����ڴ˴��������º�����ɾ����Ч���������е�ֹͣ���ŵ���Ч������ᵼ��ͨ�ö���Ч��
		��MagicView���Ѿ��ͷŵ���û������Ч��������(EffectControlManager mList)��ɾ��������mList
		Խ��Խ�� BUG Fixed by zhangjie 20100520
		*/
		release();
	}
};

/// ������Ч��������
struct EffectContext_Fly : public EffectContext_General
{
	float		moveSpeed;		/// �ƶ��ٶ�
	handle		src;			/// Դ
	handle		target;			/// Ŀ��
	ulong		idExplode;		/// ��ը��Ч��Id
    //  ��ը��Ч��Ŀ�꣺���Ϊ0����ը��Ч����target����λ�õĵ����ϣ�
    handle		hExplodeTarget;
	int			loopsExplode;	/// ��ը��Ч��ѭ������
    //  ���������ģ�����ը��Чʹ�ã�
    SkillEffectContext ExplodeEffectContext;
};

/// ˲����Ч��������
struct EffectContext_RapidMove : public EffectContext_General
{
    AttackContext ac;	/// ����������
};

/// �����������
//template<class TAttackView, class TAttackContext, class TDamageView, class TDamageContext>
class EffectControl_Fly : public EffectControl
{
	MagicViewWithMoveTrack*		mFly;
    ulong mAngle;
	ulong						mIdExplode;
	int							mLoopsExplode;
	handle						mTarget;
    //  ����ʱ��Ŀ��ͱ�ը��Ч�İ�Ŀ������ǲ�ͬ�ģ�
    handle                      mExplodeTarget;
    //  ��ը��Чʹ�õĹ��������ģ�
    SkillEffectContext mExplodeEffectContext;

public:
	EffectControl_Fly() : mFly(0) { }
	virtual ~EffectControl_Fly() { close(); }

	bool create(const EffectContext_Fly& context)
	{
		if (context.magicId == 0 || !context.src || !context.target)
			return false;

        mAngle = context.angle;
		mIdExplode = context.idExplode;
		mLoopsExplode = context.loopsExplode;
		mTarget = context.target;
        mExplodeTarget = context.hExplodeTarget;
        mExplodeEffectContext = context.ExplodeEffectContext;

		Assert(mLoopsExplode == 1);

		EntityView* src = (EntityView*)getHandleData(context.src);
		EntityView* target = (EntityView*)getHandleData(context.target);
		if (!src || !target) return false;

		MagicContext_MoveTrack mc;
		mc.magicId = context.magicId;
		mc.loops = context.loops;
		mc.angle = 0; // ��������
		mc.owner = 0;
		mc.tile = src->getTile();
		mc.moveSpeed = context.moveSpeed;
		mc.src = context.src;
		mc.target = context.target;
		mFly = (MagicViewWithMoveTrack*)gGlobalClient->getEntityFactory()
			->createMagic(MagicType_MoveTrack, &mc, sizeof(mc));
		if (!mFly)
			return false;

		CreateHandle();
		mFly->setEffectObserver(mHandle);

		return mFly->onCommand(EntityCommand_MoveTrack);
	}

	void close() ;//{ if (mFly) mFly->release(); }
	void onFinished(MagicView* ev);
};




/// ��������Ч��������
struct EffectContext_LifeTime : public EffectContext_General
{
	ulong	life;		/// ������(����)
};

/// �������������
//template<class TAttackView, class TAttackContext, class TDamageView, class TDamageContext>
class EffectControl_LifeTime : public EffectControl, public TimerHandler
{
	MagicView*				mEffect;
public:
	EffectControl_LifeTime() : mEffect(0) { }
	virtual ~EffectControl_LifeTime() { close(); }

	bool create(const EffectContext_LifeTime& context)
	{
		if (context.magicId == 0 || context.life == 0)
			return false;

		Assert(context.loops <= 0);

		MagicContext_General mc;
		mc.magicId = context.magicId;
		mc.loops = context.loops;
		mc.angle = context.angle;
		mc.owner = context.owner;
		mc.tile = context.tile;

		mEffect = (MagicView*)gGlobalClient->getEntityFactory()
			->createMagic(MagicType_General, &mc, sizeof(mc));
		if (mEffect)
			gGlobalClient->getTimerAxis()->SetTimer(0, context.life, this, 1, __FILE__);

		CreateHandle();
		return mEffect != 0;
	}

	void close()
	{
		gGlobalClient->getTimerAxis()->KillTimer(0, this);
		if (mEffect) mEffect->release();
	}
	virtual void OnTimer(unsigned long dwTimerID)
	{
		if (mEffect)
			mEffect->release();
		release();
	}
};

//  ��β�����Ч�������ģ�
template< class TEffectControlContext >
struct EffectContext_MultiTimes : public EffectContext_General
{
    //  ��ʱ�䣬��λ��ms��
    ulong m_ulDuration;
    //  ÿ��֮��ļ������λ��ms��
	ulong m_ulInterval;
    TEffectControlContext m_EffectControlContext;
};

/// ����������
//template<class TAttackView, class TAttackContext, class TDamageView, class TDamageContext>
template< class TEffectControlContext, class TEffectControlType >
class EffectControl_MultiTimes : public EffectControl, public TimerHandler
{
#if 0
	MagicContext_General	mContext;
	ulong	mTimes;
#endif
    EffectContext_MultiTimes< TEffectControlContext > m_Context;

public:
    EffectControl_MultiTimes()
    {
    }
	virtual ~EffectControl_MultiTimes()
    {
        close();
    }

public:
	bool create(const EffectContext_MultiTimes< TEffectControlContext >& context)
	{
#if 0
		if (context.magicId == 0 || context.times == 0 || 
			(context.times > 1 && context.interval == 0))
			return false;

		mContext.magicId = context.magicId;
		mContext.loops = context.loops;
		mContext.angle = context.angle;
		mContext.owner = context.owner;
		mContext.tile = context.tile;
		mTimes = context.times;

		Assert(context.loops >= 1);

		if (context.times > 1)
			gGlobalClient->getTimerAxis()->SetTimer(0, context.interval, this, context.times-1, __FILE__);

		OnTimer(0);

#endif
        m_Context = context;

        //  �ȴ���һ����Ч��
        CreateEffect();

        //  �������ƶ�δ�����Ч�Ķ�ʱ����
        if (m_Context.m_ulDuration > 0)
        {
            gGlobalClient->getTimerAxis()->SetTimer(0, m_Context.m_ulInterval, this);
        }
		return true;
	}

	void close()
	{
		gGlobalClient->getTimerAxis()->KillTimer(0, this);
	}

	virtual void OnTimer(unsigned long dwTimerID)
	{
        //  ����һ����Ч��
        CreateEffect();
	}

    void CreateEffect()
    {
        TEffectControlType* pEffectControl = new TEffectControlType();
        if (!pEffectControl->create(m_Context.m_EffectControlContext))
        {
            ASSERT(false);
            delete pEffectControl;
            return;
        }

        //pEffectControl->setSrc(m_Context.m_EffectControlContext.src);
        //pEffectControl->setViewId(m_Context.m_nEffectID);
        //EffectControlManager::getInstance().add(pEffectControl);
    }
};



/// ������Ч��������
struct EffectContext_Area : public EffectContext_General
{
	const IntArray* arr;/// ����
	ulong	interval;	/// ÿ��֮��ļ��
	ulong	life;		/// ������(����)
};

/// �����������
//template<class TAttackView, class TAttackContext, class TDamageView, class TDamageContext>
class EffectControl_Area : public EffectControl, public TimerHandler
{
	EffectContext_Area	mContext;
	ulong mCounts;
	ulong mMaxLoopCount;	/// ��ֹdo-while��ѭ��
public:
	EffectControl_Area() : mCounts(0), mMaxLoopCount(400) { }
	virtual ~EffectControl_Area()	{ close(); }

public:
	bool create(const EffectContext_Area& context)
	{
		if (context.magicId == 0 || context.arr->count == 0 
			|| context.interval == 0 || context.life == 0/* || context.owner != 0*/)
			return false;

		if (context.arr->count == 1)
		{
			if (context.arr->data[0] < 3 || context.arr->data[0] > 12)
				return false;
		}

		memcpy(&mContext, &context, sizeof(EffectContext_Area));

		if (mContext.arr->count == 1) // Բ��
			mMaxLoopCount = arrSizeCircle[mContext.arr->data[0]];
		else if (mContext.arr->count == 2) // ����
			mMaxLoopCount = mContext.arr->data[0] * mContext.arr->data[1];

		mCounts = mContext.life / mContext.interval;
		gGlobalClient->getTimerAxis()->SetTimer(0, mContext.interval, this, INFINITY_CALL, __FILE__);
		gGlobalClient->getTimerAxis()->SetTimer(1, mContext.life, this, 1, __FILE__);
		OnTimer(0);

		return true;
	}
	void close()
	{
		gGlobalClient->getTimerAxis()->KillTimer(0, this);
		gGlobalClient->getTimerAxis()->KillTimer(1, this);
	}

	virtual void OnTimer(unsigned long dwTimerID)
	{
		if (dwTimerID == 1)
		{
			release();
			return;
		}

		POINT pt;
		Tile* tile = 0;
		ulong loops = 0;

		do
		{
			loops++;
			if (mContext.arr->count == 1) // Բ��
			{
				const TileOffset* arr = arrOffsetCircle[mContext.arr->data[0]];
				const ulong size = arrSizeCircle[mContext.arr->data[0]];
				TileOffset offset = arr[rand() % size];
				pt.x = mContext.tile.x + offset.x;
				pt.y = mContext.tile.y + offset.y;
			}
			else if (mContext.arr->count == 2) // ����
			{
				pt.x = mContext.tile.x - (mContext.arr->data[0]/2) + rand() % mContext.arr->data[0];
				pt.y = mContext.tile.y - (mContext.arr->data[1]/2) + rand() % mContext.arr->data[1];
			}
			tile = gGlobalClient->getSceneManager()->getTile(pt);
		} while (loops < mMaxLoopCount && (!tile || !tile->isValid() || tile->isBlock()));

		MagicContext_General mc;
		mc.magicId = mContext.magicId;
		mc.loops = mContext.loops;
		mc.angle = mContext.angle;
		mc.owner = 0;
		mc.tile = pt;

		if (gGlobalClient->getEntityFactory()->createMagic(MagicType_General, &mc, sizeof(mc)))
			mCounts--;
	}/*
	virtual void onFinished(MagicView* ev)
	{
		if (ev)
			ev->release();

		if (--mCounts == 0)
			release();
	}*/
};





/// ������Ч��������
struct EffectContext_MultiDir: public EffectContext_General
{
	ulong	dirs;		/// ������
	float	moveSpeed;	/// �ƶ��ٶ�
	POINT	pt;			/// ��ʼλ��
	ulong	width;		/// ������
	ulong	maxDist;	/// ������
	ulong	blockType;	/// �赲����
};

/// �����������
//template<class TAttackView, class TAttackContext, class TDamageView, class TDamageContext>
class EffectControl_MultiDir : public EffectControl
{
	ulong	mDirs;
	ulong	mWidth;
	ulong	mCount;
public:
	EffectControl_MultiDir() { }
	virtual ~EffectControl_MultiDir(){ close(); }

public:
	bool create(const EffectContext_MultiDir& context)
	{
		if (context.magicId == 0 || context.owner == 0 
			|| context.dirs == 0 || context.moveSpeed <= 0.f
			|| context.pt.x == 0 || context.pt.y == 0
			|| context.maxDist == 0)
			return false;

		mDirs = context.dirs;
		mWidth = context.width;
		mCount = mDirs * mWidth;

		if (mWidth > 5) mWidth = 5;
		if (mWidth == 0) mWidth = 1;
		if (!(mWidth & 1)) return false;

		static POINT offset[eDirectionCount] = {
			{ 1,  0}, { 1,  1}, { 0,  1}, {-1,  1},
			{-1,  0}, {-1, -1}, { 0, -1}, { 1, -1},
		};

		EntityView* owner = (EntityView*)getHandleData(context.owner);
		if (!owner) return false;

		// ʩ��������
		ulong dir = angle2Dir(owner->getAngle()); //calcDir8_tile(owner->getTile(), context.tile);
		MagicContext_MoveRadial mc;
		mc.magicId = context.magicId;
		mc.loops = context.loops;
		mc.angle = 0; // �ڲ�����
		mc.owner = 0;
		mc.tile = context.tile;
		mc.moveSpeed = context.moveSpeed;
		mc.blockType = context.blockType;

		POINT ptTarget;
		switch (mDirs)
		{
		case 1: // ���ĵ�ǰ��
			{
				const TileOffset* arrOff = 0;
				if (mWidth == 1)
					arrOff = &arrOffsetRadial[dir];
				else if (mWidth == 3)
					arrOff = &arrOffsetRadialOrigin_3[dir][0];
				else if (mWidth == 5)
					arrOff = &arrOffsetRadialOrigin_5[dir][0];

				ptTarget.x = mc.tile.x + offset[dir].x * (context.maxDist - 1);
				ptTarget.y = mc.tile.y + offset[dir].y * (context.maxDist - 1);

				POINT ptFrom, ptTo;
				for (ulong j=0; j<mWidth; j++)
				{
					ptFrom.x = context.tile.x + arrOff[j].x;
					ptFrom.y = context.tile.y + arrOff[j].y;
					ptTo.x = ptTarget.x + arrOff[j].x;
					ptTo.y = ptTarget.y + arrOff[j].y;
					MagicViewWithMoveRadial* magic = (MagicViewWithMoveRadial*)gGlobalClient->getEntityFactory()->createMagic(MagicType_MoveRadial, &mc, sizeof(mc));
					if (magic)
						magic->onCommand(EntityCommand_MoveRadial, (ulong)&ptFrom, (ulong)&ptTo);
				}
			}
			break;		
		case 3: // ���ĵ�ǰ��3����
			for (ulong i=0; i<mDirs; i++)
			{
				int newDir = dir + i - 1;
				if (newDir < 0) newDir += eDirectionCount;
				if (newDir >= eDirectionCount) newDir -= eDirectionCount;

				const TileOffset* arrOff = 0;
				if (mWidth == 1)
					arrOff = &arrOffsetRadial[newDir];
				else if (mWidth == 3)
					arrOff = &arrOffsetRadialOrigin_3[newDir][0];
				else if (mWidth == 5)
					arrOff = &arrOffsetRadialOrigin_5[newDir][0];

				ptTarget.x = mc.tile.x + offset[newDir].x * (context.maxDist - 1);
				ptTarget.y = mc.tile.y + offset[newDir].y * (context.maxDist - 1);

				POINT ptFrom, ptTo;
				for (ulong j=0; j<mWidth; j++)
				{
					ptFrom.x = context.tile.x + arrOff[j].x;
					ptFrom.y = context.tile.y + arrOff[j].y;
					ptTo.x = ptTarget.x + arrOff[j].x;
					ptTo.y = ptTarget.y + arrOff[j].y;
					MagicViewWithMoveRadial* magic = (MagicViewWithMoveRadial*)gGlobalClient->getEntityFactory()->createMagic(MagicType_MoveRadial, &mc, sizeof(mc));
					if (magic)
						magic->onCommand(EntityCommand_MoveRadial, (ulong)&ptFrom, (ulong)&ptTo);
				}
			}
			break;
		case 4: // ���ĵ�4����
			for (ulong i=0; i<mDirs; i++)
			{
				int newDir = dir + i * 2;
				if (newDir < 0) newDir += eDirectionCount;
				if (newDir >= eDirectionCount) newDir -= eDirectionCount;

				const TileOffset* arrOff = 0;
				if (mWidth == 1)
					arrOff = &arrOffsetRadial[newDir];
				else if (mWidth == 3)
					arrOff = &arrOffsetRadialOrigin_3[newDir][0];
				else if (mWidth == 5)
					arrOff = &arrOffsetRadialOrigin_5[newDir][0];

				ptTarget.x = mc.tile.x + offset[newDir].x * (context.maxDist - 1);
				ptTarget.y = mc.tile.y + offset[newDir].y * (context.maxDist - 1);

				POINT ptFrom, ptTo;
				for (ulong j=0; j<mWidth; j++)
				{
					ptFrom.x = context.tile.x + arrOff[j].x;
					ptFrom.y = context.tile.y + arrOff[j].y;
					ptTo.x = ptTarget.x + arrOff[j].x;
					ptTo.y = ptTarget.y + arrOff[j].y;
					MagicViewWithMoveRadial* magic = (MagicViewWithMoveRadial*)gGlobalClient->getEntityFactory()->createMagic(MagicType_MoveRadial, &mc, sizeof(mc));
					if (magic)
						magic->onCommand(EntityCommand_MoveRadial, (ulong)&ptFrom, (ulong)&ptTo);
				}
			}
			break;
		case 8: // ���ĵ�8����
			for (ulong i=0; i<mDirs; i++)
			{
				const TileOffset* arrOff = 0;
				if (mWidth == 1)
					arrOff = &arrOffsetRadial[i];
				else if (mWidth == 3)
					arrOff = &arrOffsetRadialOrigin_3[i][0];
				else if (mWidth == 5)
					arrOff = &arrOffsetRadialOrigin_5[i][0];

				ptTarget.x = mc.tile.x + offset[i].x * (context.maxDist - 1);
				ptTarget.y = mc.tile.y + offset[i].y * (context.maxDist - 1);

				POINT ptFrom, ptTo;
				for (ulong j=0; j<mWidth; j++)
				{
					ptFrom.x = context.tile.x + arrOff[j].x;
					ptFrom.y = context.tile.y + arrOff[j].y;
					ptTo.x = ptTarget.x + arrOff[j].x;
					ptTo.y = ptTarget.y + arrOff[j].y;
					MagicViewWithMoveRadial* magic = (MagicViewWithMoveRadial*)gGlobalClient->getEntityFactory()->createMagic(MagicType_MoveRadial, &mc, sizeof(mc));
					if (magic)
						magic->onCommand(EntityCommand_MoveRadial, (ulong)&ptFrom, (ulong)&ptTo);
				}
			}
			break;
		default:
			return false;
		}

		return true;
	}
	void close() { }
	virtual void onFinished(MagicView* ev)
	{
		if (ev) ev->release();

		if (--mCount == 0)
			release();
	}
};

/// ˲���������
class EffectControl_RapidMove : public EffectControl, public IShadowObserver
{
	ShadowManager*	mShadowManager;
	handle			mOwner;
	POINT			mTargetTile;
	AttackContext	mAttackContext;
public:
	bool create(const EffectContext_RapidMove& context)
	{
		if (context.owner == 0 || context.tile.x == 0 || context.tile.y == 0)
			return false;

		mOwner = context.owner;
		EntityView* owner = (EntityView*)getHandleData(context.owner);
		if (!owner)
			return false;

		mAttackContext = context.ac;
		mTargetTile = context.tile;

		mShadowManager = new ShadowManager();
		mShadowManager->setObserver(this);
		if (!mShadowManager->create(owner, owner->getTile(), mTargetTile))
		{
			delete mShadowManager;
			return false;
		}

		return owner->onCommand(EntityCommand_RapidMoveStart, (ulong)mShadowManager);
	}
	void close() { }
	virtual void onFinished()
	{
		EntityView* owner = (EntityView*)getHandleData(mOwner);
		gGlobalClient->getSceneManager()->moveEntity(owner->getTile(), mTargetTile, owner);
		// ֹͣ�ƶ�
		owner->onCommand(EntityCommand_Stand);
		owner->onCommand(EntityCommand_RapidMoveEnd);
		if (mAttackContext.actionId != 0)
		{
			owner->onCommand(EntityCommand_Attack, (ulong)&mAttackContext);
		}
		release();
	}

};

//��Ծ��Ч��
class EffectControl_Jump : public EffectControl, public IJumpObserver
{
	POINT			mTargetTile;
	handle			mOwner;
	JumpManager*	pJumpManager;
public:
	bool create(const EffectContext_RapidMove& context)
	{
		if (context.owner == 0 || context.tile.x == 0 || context.tile.y == 0)
			return false;
		
		mOwner = context.owner;
		EntityView* owner = (EntityView*)getHandleData(context.owner);
		if (!owner)
			return false;

		mTargetTile = context.tile;

		pJumpManager = new JumpManager();
		pJumpManager->setObserver(this);
		if (!pJumpManager->create(owner->getTile(), mTargetTile))
		{
			delete pJumpManager;
			return false;
		}
		owner->onCommand(EntityCommand_SetMount, 0);
		return owner->onCommand(EntityCommand_Jump, (ulong)pJumpManager);		
	}
	void close() { }
	virtual void onFinished()
	{
		//��Ծ����
		//EntityView* owner = (EntityView*)getHandleData(mOwner);
		//gGlobalClient->getSceneManager()->moveEntity(owner->getTile(), mTargetTile, owner);
		release();
	}
};
//

#endif // __EFFECTCONTROL_H__