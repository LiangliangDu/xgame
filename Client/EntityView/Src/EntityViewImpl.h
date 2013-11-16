//==========================================================================
/**
* @file	  : EntityViewImpl.h
* @author : 
* created : 2008-1-30   13:34
* purpose : ʵ������ʵ��
*/
//==========================================================================

#ifndef __ENTITYVIEWIMPL_H__
#define __ENTITYVIEWIMPL_H__

#include "IEntityView.h"
#include "EntityComponent.h"

enum ComponentMessage
{
	msgTileChanged,		/// TILEλ�øı� (0,0)
	msgDirChanged,		/// ����ı� (0,0)
	msgPosChanged,		/// spaceλ�øı� (0, 0)
	msgStateChanged,	/// ״̬�ı� (int state, 0)
	msgMoveStart,		/// �ƶ���ʼ (0,0)
	msgMoveFinished,	/// �ƶ���� (0,0)
	msgAniFinished,		/// ����������� (0,0)
	msgMoveSpeedChanged,/// �ƶ��ٶȸı� (const float* moveSpeed,0)
	msgMoveStyleChanged,/// �ƶ����͸ı� (0,0)
	msgMountChanged,	/// ������͸ı�

	MaxComponentMessage,
};

class EntityViewImpl : public EntityView
{
	EntityComponent*	mComps[MaxComponentIDCount]; /// ����б�,����ʱȷ������Ч
	bool				mNeedDelete;
public:
	bool				mCalcWorld;

public:
	EntityViewImpl();
	virtual ~EntityViewImpl();

public:
	void setComponent(ComponentID id, EntityComponent* comp)
	{ 
		Assert(id < MaxComponentIDCount); 
		if (id >= ComponentIDVisual && id < MaxComponentIDCount)
		{
			mComps[id] = comp; 
		}		
	}

	template <class T>
	inline T* getComponent(ComponentID id) const
	{ Assert(id < MaxComponentIDCount); return static_cast<T*>(mComps[id]); }

	// IEntityView
public:
	virtual void release(){
		//if (hasFlag(flagInMap))
		//	gGlobalClient->getSceneManager()->removeEntity(getTile(), this);
		//setUserData(0);

		// ԭ�ȵ�ͼ�ϵ����������ͼʱ�����ӳ��ͷţ����ǳ��������Ѿ�����˻�����޷���ȷ�ͷţ����������ͷŵ�  [5/5/2011 zgz]
		if (hasFlag(flagReleaseImmediate))
		{
			delete this;
			return;
		}

		// zgz ԭ������ֻ���Fade����ǲ����ģ����ʵ�岻�ڳ����������ʾ�б�򵭳��б�����п����޷�����ɾ������ڴ�й¶
		ISceneManager2* pSceneManager = gGlobalClient->getSceneManager();
		if (NULL != pSceneManager && pSceneManager->IsReferencedBySceneManager(this) && hasFlag(flagFade))
		{
			setNeedDelete();
		}
		else
			delete this;
	}
	virtual void setTile(const xs::Point& ptTile);
	virtual bool onCommand(ulong cmd, ulong param1 = 0, ulong param2 = 0);
	virtual void onEnterViewport(int priority = 0);
	virtual void onLeaveViewport();
	virtual void drawPickObject(IRenderSystem* pRenderSystem);
	virtual void drawShadow(IRenderSystem* pRenderSystem);
	virtual void draw(IRenderSystem* pRenderSystem);
	virtual void drawTopMost(IRenderSystem* pRenderSystem);
	virtual bool update(float tick, float deltaTick, IRenderSystem* pRenderSystem);
	virtual const xs::Rect& getShowRect() const;
	virtual OccupantTileList* getOccupantTileList() const;
	virtual size_t onLoad(Stream* stream, size_t len);
	virtual size_t onSave(Stream* stream) const;
	virtual bool isTransparent(int x, int y);
	virtual void onAddEntity();
	virtual void onRemoveEntity();
	virtual void drawAlwayseTopMost(IRenderSystem* pRenderSystem);
	/// ���ƶ�����Ч
	virtual void drawTopMostEffect(IRenderSystem* pRenderSystem);

	// ��ȡ�ܻ���
	virtual xs::Point getAttackPos();

public:
	void setResType(int type)				{ mResType = type; }
	void setResId(ulong id)					{ mResId = id; }
	void setArea(const xs::Rect& rc)			{ m_rcArea = rc; }
	void setSortLeft(const xs::Point& pt)		{ m_ptLeft = pt; }
	void setSortRight(const xs::Point& pt)		{ m_ptRight = pt; }
	virtual void setAngle(long angle);
	virtual void setSpace(const Vector3& space);
	void setOccupantValue(ulong occVal)		{ mOccVal = occVal; }
	void setNeedDelete(bool del = true)					{ mNeedDelete = del; }
	bool isNeedDelete() const				{ return mNeedDelete; }

	// �����Ϣ
	void onMessage(ulong msgId, ulong param1 = 0, ulong param2 = 0);

	bool isMainPlayer() const { return this == (EntityView*)getHandleData(gGlobalClient->getPlayer()); }

	virtual const AABB& GetAABB();
	virtual const Matrix4& GetFullTransform();
};

#endif // __ENTITYVIEWIMPL_H__