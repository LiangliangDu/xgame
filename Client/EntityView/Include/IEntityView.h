//==========================================================================
/**
* @file	  : IEntityView.h
* @author : 
* created : 2008-1-21   9:54
* purpose : ʵ����ͼ����ӿ�
*/
//==========================================================================

#ifndef __IENTITYVIEW_H__
#define __IENTITYVIEW_H__

#include <string>

#include "EntityDef.h"
#include "Occupant.h"

class xs::RenderQueue;

class EntityView;

/// ����ʵ��Ļص�֪ͨ
struct IEntityViewObserver
{
	virtual void onTileChanged(EntityView* owner, const xs::Point& curTile) {}
	virtual void onMoveFinished(EntityView* owner)						{}
	virtual void onMoveBreak(EntityView* owner)							{}
};


/// ʵ����ͼ
class EntityView
{
protected:
	handle			mHandle;		/// ʵ����
	ulong			mFlags;			/// ʵ��ı�־λ
	ulong			mLayer;			/// �����Σ���������
	ulong			mOccVal;		/// ռλֵ
	ulong			mData;			/// �û�����

	ulong			mResId;			/// �������ԴID(ֻ����������������������Id)
	ulong			mSaveId;		/// ��ȡ����ǰ�����ģ����Դ
	ulong			mResType;		/// ��Դ����(ֻ��)
	ulong			mEntityType;	/// ʵ������(�߼����棬�羲̬�����NPC)

	xs::Point			m_ptTile;		/// �����ڵ�ͼ�ϵ�TILEλ��
	xs::Rect			m_rcArea;		/// ռλ����
	xs::Point			m_ptWorld;		/// ����ê���ڵ�ͼ�϶�Ӧ����������
	xs::Point			m_ptLeft;		/// ��������
	xs::Point			m_ptRight;		/// �ұ������
	ulong			mAngle;			/// ʵ��ķ���[0,360)
	Vector3			mSpace;			/// ʵ����3D�����е�Space����
	IEntityViewObserver* mObserver;	/// ʵ��۲���

public:
	AABB			m_AABB;
	Matrix4			m_FullTransform;

public:
	EntityView() : mHandle(INVALID_HANDLE), mData(0), mFlags(0), mLayer(lvlMidle), mOccVal(0x2000), mAngle(0), mEntityType(typeUnknow), mObserver(0)
	{
		m_ptTile.x = m_ptTile.y = 0;
        
		//SetRectEmpty(&m_rcArea);
        m_rcArea.left = m_rcArea.right = m_rcArea.top = m_rcArea.bottom = 0;
		
        m_ptWorld.x = m_ptWorld.y = 0;
		m_ptLeft.x = m_ptLeft.y = 0;
		m_ptRight.x = m_ptRight.y = 0;
        m_pointAnchorOffset.x = 0;
        m_pointAnchorOffset.y = 0;
		mSaveId = 0;
	}

	virtual ~EntityView()							
	{ if (mHandle != INVALID_HANDLE) closeHandle(mHandle); 
#ifdef MEM_LEAK_TEST
		gGlobalClient->ReleaseEntityView(this);
#endif
	}


	/// �ͷ�
	virtual void release() = 0;

	virtual const AABB& GetAABB() = 0;

	virtual const Matrix4& GetFullTransform() = 0;

	//////////////////////////////////////////////////////////////////////////
	// �����������
	//////////////////////////////////////////////////////////////////////////
	/// ��ȡʵ��ľ����ֻ���߼���������þ����
	inline handle getHandle() const					{ return mHandle; }

	/// ��ȡ�������ԴID
	inline ulong getResId() const					{ return mResId; }

	// ���ñ���ǰ��ID
	//add by zjp���������ǰ�ĳ���
	ulong getsaveId()								{return mSaveId;}
	void saveResId(ulong id)						{ mSaveId = id; } 

	/// �����û�����(Ŀǰ�������ڼ�¼�߼������ָ��)
	inline void setUserData(ulong data)
	{
		if (mHandle == INVALID_HANDLE && data) mHandle = createHandle((ulong)this);
		mData = data;
		//if (mData && mHandle) { closeHandle(mHandle); mHandle=INVALID_HANDLE;}
		//if (mData = data) mHandle = createHandle((ulong)this);
	}

	/// ����û�����
	inline ulong getUserData() const				{ return mData; }

	/// ����ʵ������
	inline void setEntityType(ulong entityType)		{ mEntityType = entityType; }

	/// ��ȡʵ������
	inline ulong getEntityType() const				{ return mEntityType; }

	/// ��ȡ��Դ����
	inline ulong getResType() const					{ return mResType; }

	/// ����ʵ��۲���
	inline void setEntityViewObserver(IEntityViewObserver* ob)	{ mObserver = ob; }

	/// ��ȡʵ��۲���
	inline IEntityViewObserver* getEntityViewObserver() const	{ return mObserver; }




	//////////////////////////////////////////////////////////////////////////
	// ����/λ�����
	//////////////////////////////////////////////////////////////////////////
	/// ���õ�ǰTile(ֻ���ɳ�������������)
	virtual void setTile(const xs::Point& ptTile) = 0;

	/// ��õ�ǰTile����
	inline const xs::Point& getTile() const				
	{ 
		return m_ptTile; 
	}

	/// ���ö������������
	inline void setWorld(const xs::Point& ptWorld)		{ m_ptWorld = ptWorld; };

	/// ��ȡʵ�����������
	inline const xs::Point& getWorld() const			{ return m_ptWorld; }

	/// ��ȡʵ���ռλ������
	inline const xs::Rect& getArea() const				{ return m_rcArea; }

	/// ��ȡ�������
	inline const xs::Point& getSortLeft() const			{ return m_ptLeft; }

	/// ��ȡ�������
	inline const xs::Point& getSortRight() const		{ return m_ptRight; }

	/// ����ʵ������ĽǶ�
	virtual void setAngle(long angle) = 0;

	/// ��ȡʵ������ĽǶ�
	inline long getAngle() const					{ return mAngle; }

	/// ����Space����
	virtual void setSpace(const Vector3& space) = 0;

	/// ��ȡSpace����
	inline const Vector3& getSpace() const			{ return mSpace; }

    //  �������űȣ���MagicView����д������������Ч���űȣ�
    inline virtual void setScale(float /*scale*/)
    {
    }

	// add by zjp����ȡ�ܻ���
	virtual xs::Point getAttackPos()
	{
		xs::Point pt(0,0);
		return pt;
	}


	//////////////////////////////////////////////////////////////////////////
	// ��ͼ���
	//////////////////////////////////////////////////////////////////////////
	/// ���ʵ��ľ��ο�(2D��Χ��)����Ҫ���ھ��߶����Ƿ�����Ļ��Χ֮��
	virtual const xs::Rect& getShowRect() const = 0;

	/// ����ʵ��
	virtual void draw(IRenderSystem* pRenderSystem) = 0;

	/// ���ƿ�ѡȡ�Ķ���(һ��ʵ������ж�����֣���ֻ��ĳЩ�����ǿ��Ա�ѡȡ��)
	virtual void drawPickObject(IRenderSystem* pRenderSystem) = 0;

	/// ����Ӱ��
	virtual void drawShadow(IRenderSystem* pRenderSystem) = 0;

	/// ���ƶ�����󣬱���Ѫ�������Ƶȵ�
	virtual void drawTopMost(IRenderSystem* pRenderSystem) = 0;

    /// ����������ʾ�Ķ�����󣬱�������ͼ��ȵ�
	virtual void drawAlwayseTopMost(IRenderSystem* pRenderSystem) = 0;

	/// ���ƶ�����Ч
	virtual void drawTopMostEffect(IRenderSystem* pRenderSystem) = 0;
	/** ����ʵ��
	@param tick				��ǰ��ʱ��Ƭ
	@param deltaTick		2��update�����ʱ���
	@param pRenderSystem	��Ⱦϵͳ
	@param pCamera			�����
	@param retval			����false��ʾ�ö������ͷţ����򷵻�true
	*/
	virtual bool update(float tick, float deltaTick, IRenderSystem* pRenderSystem) = 0;

	/** ��ʵ������ӿ�
	@param priority			��Դ���ص����ȼ�����
	*/
	virtual void onEnterViewport(int priority = 0) = 0;

	/// ��ʵ���뿪�ӿ�
	virtual void onLeaveViewport() = 0;

	/// �ж�ĳ���������ʾ���ε�λ���Ƿ�͸������Ҫ���������
	virtual bool isTransparent(int x, int y)	{ return false; }

	/// ��ʵ����ӵ���ͼ�����ʱ��Ļص�
	virtual void onAddEntity()					{ }

	/// ��ʵ��ӵ�ͼ�����Ƴ���ʱ��Ļص�
	virtual void onRemoveEntity()				{ }




	//////////////////////////////////////////////////////////////////////////
	// ���л����
	//////////////////////////////////////////////////////////////////////////
	/** �����м�������
	@param stream ���ڶ�ȡ��������
	@param len ���ƶ�ȡ����󳤶�
	@retval �ɹ�����ʵ�ʶ�ȡ�ĳ��ȣ�ʧ�ܷ���0
	*/
	virtual size_t onLoad(Stream* stream, size_t len) = 0;

	/** д���ݵ�ָ����������
	@param stream ���ڱ������ݵ�������
	@retval �ɹ�����ʵ��д������ݳ��ȣ�ʧ�ܷ���0
	*/
	virtual size_t onSave(Stream* stream) const = 0;




	//////////////////////////////////////////////////////////////////////////
	// �������
	//////////////////////////////////////////////////////////////////////////
	/** ��ʵ�巢������
	@param cmd ������
	@param param1 �������1
	@param param2 �������2
	*/
	virtual bool onCommand(ulong cmd, ulong param1 = 0, ulong param2 = 0) = 0;



	//////////////////////////////////////////////////////////////////////////
	// ��־���
	//////////////////////////////////////////////////////////////////////////
	/** ���ñ�־
	@param flag ��־ֵ
	*/
	inline void setFlag(ulong flag = 0)					{ mFlags = flag; }

	/// ȡ�ñ�־λ
	inline ulong getFlag() const						{ return mFlags; }

	/** ���ӱ�־
	@param flag ��־λ���ͣ��ο� EntityFlags ö��
	*/
	inline void addFlag(ulong flag)						{ mFlags |= flag; }

	/**ɾ����־
	@param flag ��־λ���ͣ��ο� EntityFlags ö��
	*/
	inline void removeFlag(ulong flag)					{ mFlags &= ~flag; }

	/// �ж��Ƿ����ĳЩ��־
	inline bool hasFlag(ulong flag) const				{ return (mFlags & flag) == flag; }




	//////////////////////////////////////////////////////////////////////////
	// �������
	//////////////////////////////////////////////////////////////////////////
	/// ���ʵ��㼶�𣨲ο� SortLevel ö�٣�
	inline ulong getLayer() const						{ return mLayer; }

	/// ���ò㼶��
	inline void setLayer(ulong layer)					{ mLayer = layer; }

	/// ��ȡռλֵ���ο�ռλ���Ͷ��壬�߼��������Ƿ���ָ����ֵ��
	inline ulong getOccupantValue() const				{ return hasFlag(flagNoLogic) ? mOccVal : mOccVal | 0x70000; }

	/// ����ռλֵ
	inline void setOccupantValue(ulong occ)				{ mOccVal = occ; }

	/// ��ȡռλ�б�
	virtual OccupantTileList* getOccupantTileList() const { return NULL; }

    //  ��ȡê��ƫ�ƣ�
    inline xs::Point GetAnchorOffset() const
    {
        return m_pointAnchorOffset;
    }

    //  ����ê��ƫ�ƣ�
    inline virtual void SetAnchorOffset(const xs::Point& pointAnchorOffset)
    {
        m_pointAnchorOffset.x = pointAnchorOffset.x;
        m_pointAnchorOffset.y = pointAnchorOffset.y;
    }

protected:
    //  ê��ƫ�Ƶļ�¼��ê��ƫ����ָ�ڳ��������з������ʱ����������ê������tile�У������tile������λ�õ�ƫ�ƣ�
    //  ��¼��ֵ����ʹ�������������Ϊ��λ�����ƶ��ͷ��ã�
    xs::Point m_pointAnchorOffset;
};

#endif // __IENTITYVIEW_H__
