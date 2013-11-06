//==========================================================================
/**
* @file	  : MagicView.h
* @author : 
* created : 2008-4-3   10:58
* purpose : ħ����Ч����
*/
//==========================================================================

#ifndef __MAGICVIEW_H__
#define __MAGICVIEW_H__

/// ͨ��ħ��������
struct MagicContext_General
{
	ulong		magicId;/// ��ЧId
	int			loops;	/// ��Чѭ������
	int			nDuration;    //  ��Ч����ʱ�䣺���Ը��ݸ�ֵ��ȷ����Ч�ĳ���ʱ�䣻
	ulong		angle;	/// ��Ч�ĽǶ�(���ű��趨������Ч�Ƕ�ʱ��������)
	handle		owner;	/// ����ӵ����(��һ���Ǽ��ܷ�����)
	POINT		tile;	/// ����λ�ã�������ǰ󶨵�EntityView����Ļ���
	bool		bSceneMagic; /// ������Ϸ�������ŵ���Ч���������ꡢ��ѩ zgz
	MagicContext_General() : magicId(0), loops(0), angle(0), owner(0) , nDuration(0), bSceneMagic(false){ tile.x = tile.y = 0;}
};

class MagicView;
struct IEffectObserver
{
	virtual void onFinished(MagicView* ev) = 0;
};

/// ħ����Ч
class MagicView : public EntityView, public IAnimationCallback, public TimerHandler
{
    enum
    {
        //  �ӳ�ɾ����Ч�Ķ�ʱ����ID��
        DELAY_RELEASE_TIME_ID = 0,

        //  ��Ч����ʱ��Ķ�ʱ����ID��
        DURATION_TIME_ID = 1,

		// Ԥ���ض�ʱ��ID;
		PRELOAD_TIME_ID = 2,
    };

protected:
	handle				mResHandle;		/// ��Դ���
	ulong				mMagicId;		/// ��Ч��Id(MagicView���ID)
	ulong				mNewResId;		/// ����Id�������������Id
	handle				mOwner;			/// �ù�Чӵ����
	int					mLoops;			/// ѭ������
	RECT				mShowRect;		/// ʵ����Χ����
	bool				mResLoaded;		/// ��ʶ��Դ�Ѿ�����
	ulong				mUpdateOption;	/// ����ѡ�һ�㷢����λ�á��������������š��ٶȵȸı�ʱ��
	bool				mNeedDelete;	/// �Ƿ���Ҫɾ��
	Vector3				mOffset;		/// ��Чƫ��
	float				mScale;			/// ���ű���
	float				mAniSpeed;		/// �����ٶ�
	//IEffectObserver*	mObserver;		/// Ч�������۲���
	handle				mObserver;		/// Ч�������۲���(��Ϊ�������ȫ)
	float				mAlpha;			/// ���뵭��ʱ��alphaֵ
	bool				mTailSilence;	/// �Ƿ����һ֡��ֹ
	bool				mKillTimer;
	bool                m_bPetdie;      /// ��������(wan)

	Vector3				m_vStartPos;	// ���ֵ�
	ulong				m_nSpaceAngle;	// 3D�Ƕ�	
	Vector3				m_vRotNormal;	// ��ת��λ����

	// A
public:
	MagicView();
	MagicView(ulong entityType, ulong resType);
	virtual ~MagicView();

	void setUserData()
	{
		mHandle = createHandle((ulong)this);
	}
	virtual bool create(const MagicContext_General& context);
	virtual void close();

	virtual const AABB& GetAABB();
	virtual const Matrix4& GetFullTransform(); 

	// IEntityView
public:
	virtual void setTile(const POINT& ptTile);
	virtual bool onCommand(ulong cmd, ulong param1 = 0, ulong param2 = 0) {	return false; }
	virtual void onEnterViewport(int priority = 0);
	virtual void onLeaveViewport();
	virtual void drawPickObject(IRenderSystem* pRenderSystem);
	virtual void drawShadow(IRenderSystem* pRenderSystem)		{ }
	virtual void draw(IRenderSystem* pRenderSystem)				{ drawPickObject(pRenderSystem); }
	virtual void drawTopMost(IRenderSystem* pRenderSystem);
	virtual bool update(float tick, float deltaTick, IRenderSystem* pRenderSystem);
	virtual const RECT& getShowRect() const						{ return mShowRect; }
	virtual OccupantTileList* getOccupantTileList() const		{ return NULL; }
	virtual size_t onLoad(Stream* stream, size_t len);
	virtual size_t onSave(Stream* stream) const;
	virtual void onAddEntity();
	virtual void onRemoveEntity();
	virtual void release();
	virtual void OnTimer(unsigned long dwTimerID);
    virtual void SetAnchorOffset(const POINT& pointAnchorOffset);
	virtual void drawAlwayseTopMost(IRenderSystem* pRenderSystem) {};
	virtual void drawTopMostEffect(IRenderSystem* pRenderSystem) {};

public:
	void setResType(int type)				{ mResType = type; }
	void setResId(ulong id)					{ mResId = id; }
	void setArea(const RECT& rc)			{ m_rcArea = rc; }
	void setSortLeft(const POINT& pt)		{ m_ptLeft = pt; }
	void setSortRight(const POINT& pt)		{ m_ptRight = pt; }
	virtual void setAngle(long angle);
	virtual void setSpace(const Vector3& space);
	void setOccupantValue(ulong occVal)		{ mOccVal = occVal; }
	void setPosition(const Vector3& pos);
	void setTailSilence(bool b)				{ mTailSilence = b; }
	//const EffectContext_General& getContext() const	{ return mContext; }
	//void setOwner(EntityView* owner)			{ mOwner = owner; }
	void setEffectObserver(handle ob)	{ mObserver = ob; }

	ulong getMagicId() const				{ return mMagicId; }
	int getLoops() const					{ return mLoops; }
	bool needDelete() const					{ return mNeedDelete; }
	bool isNeedDelete() const				{ return mNeedDelete; }
	void setNeedDelete()					{ mNeedDelete = true; }
	void addUpdateOption(ulong option)		{ mUpdateOption |= option; }
	void setFadeIn();
	void setFadeOut();
	void setFadeDie();//��������(wan)
	void setScale(float scale);
	void SetGenerateParticle(bool bGenerate);
	int  GetParticleNum();
protected:
	void requestRes(int priority);
	void releaseRes();
	inline ModelNode* getModelNode();
	void onResLoaded(ModelNode* node);
	void onTileChanged();
	virtual void onOneCycle(const std::string& animation,int loopTimes);

protected:
	// ����3Χ�ռ��µļн�
	void setSpaceAngle(long angle)
	{
		m_nSpaceAngle = angle;
		mUpdateOption |= updateAngle;
	}
	void setRotNormal(Vector3 v)
	{
		m_vRotNormal = v;
	}
public:
	void preLoadRes();
};


/// ���ƶ��Ĺ�Ч
class MagicView_Move : public MagicView//, public TimerHandler
{
protected:
	// �ƶ����
	float			mMoveSpeed;				/// �ٶ�

	float			mDirTime;				/// �÷��������ʱ��
	ulong			mTicks;					/// ��ȥ��ʱ��
	ulong			mOldTicks;				/// �ϴε�tick��
	Vector3			mStartPos;				/// ��ʼ����λ��(����ı������)
	Vector3			mNextPos;				/// ��һ��λ��
	Vector3			mDirDistance;			/// ͬһ�����Ͽ�ʼ�����һ��ľ���

public:
	MagicView_Move();
	MagicView_Move(ulong entityType, ulong resType);
	virtual ~MagicView_Move();

	virtual void close();

	// �ƶ�
public:
	virtual void OnTimer(unsigned long dwTimerID)	{ }
	void stopMove();
	void setSpeed(float speed)	{ mMoveSpeed = speed; }

protected:
	void onPosChanged(const Vector3& pos);
};



/// �����ƶ���ħ��������
struct MagicContext_MoveRadial : public MagicContext_General
{
	float	moveSpeed;	/// �ƶ��ٶ�
	ulong	blockType;	/// �赲����

	MagicContext_MoveRadial() : moveSpeed(1.f), blockType(0) {}
};

/// �����ƶ�
class MagicViewWithMoveRadial : public MagicView_Move
{
protected:
	ulong			mBlockType;				/// �赲���� 0-�������赲��ʽ 1-�߶����赲��ʽ

public:
	MagicViewWithMoveRadial();
	MagicViewWithMoveRadial(ulong entityType, ulong resType);
	virtual ~MagicViewWithMoveRadial();

	virtual bool create(const MagicContext_MoveRadial& context);
	virtual bool onCommand(ulong cmd, ulong param1 = 0, ulong param2 = 0);
	virtual void OnTimer(unsigned long dwTimerID);
	virtual bool update(float tick, float deltaTick, IRenderSystem* pRenderSystem);
private:
	void moveStep(ulong period);
};




/// �����ƶ���ħ��������
struct MagicContext_MoveTrack : public MagicContext_General
{
	float		moveSpeed;	/// �ƶ��ٶ�
	handle		src;		/// Դʵ��
	handle		target;		/// Ŀ��ʵ��

	MagicContext_MoveTrack() : moveSpeed(1.f), src(0), target(0) { }
};

/// �����ƶ�
class MagicViewWithMoveTrack : public MagicView_Move
{
protected:
	handle			mSource;				/// ԴUID
	handle			mTarget;				/// Ŀ��UID
	POINT			mTargetTile;			/// Ŀ���TILE���꣬���仯ʱ���ᴥ��һЩ�����ļ���
	
	// add by zjp
	AABB			m_TargetAABB;			// ��¼Ŀ���AABB
	AABB			m_SourceAABB;			// �����AABB
	Matrix4			m_SourceMatrix;
	Matrix4			m_TargetMatrix;

public:
	MagicViewWithMoveTrack();
	MagicViewWithMoveTrack(ulong entityType, ulong resType);
	virtual ~MagicViewWithMoveTrack();

	virtual bool create(const MagicContext_MoveTrack& context);
	virtual bool onCommand(ulong cmd, ulong param1 = 0, ulong param2 = 0);
	virtual void OnTimer(unsigned long dwTimerID);
	virtual bool update(float tick, float deltaTick, IRenderSystem* pRenderSystem);
private:
	void moveStep(ulong period);
	void resetMoveInfo();
	void adjustStartInfo();

private:
	void _getStartPos();
};

//  ��Ч��������ߣ�
class CEffectObjHolder : public IEffectObserver
{
	handle			mHandle;
	typedef std::list< MagicView* > MagicViewList;
    //  �����ڳ����ߵĹ�Ч���б�
	MagicViewList m_AttachedEffectObjList;
    //  ���������ص�û�������ڳ����ߵĹ�Ч���б�
    MagicViewList m_RelativedEffectObjList;

public:
	CEffectObjHolder();
	~CEffectObjHolder();

	void addAttachObj(MagicView* obj);
	bool hasAttackObj(ulong magicID);
    void AddRelativedObj(MagicView* obj);	
	void removeAttachObj(ulong magicId, int loops);
    void RemoveRelativedObj(ulong magicId, int loops);
	void close();

	void draw(IRenderSystem* pRenderSystem);
	bool update(float tick, float deltaTick, IRenderSystem* pRenderSystem);
	void setPosition(const Vector3& pos);
	void onEnterViewport();
	void onLeaveViewport();
	void onAddEntity();
	void onRemoveEntity();

	void addUpdateOption(ulong option);
	void setScale(float scale);

	virtual void onFinished(MagicView* ev);

	handle	getHandle()
	{
		return mHandle; 
	}

private:
	void attach(MagicView* obj);
	void detach(const MagicView* obj);
};


#endif // __MAGICVIEW_H__