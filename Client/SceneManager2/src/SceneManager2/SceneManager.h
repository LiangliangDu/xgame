#ifndef __SceneManager_H__
#define __SceneManager_H__

#include "Eyeshot.h"
#include "SceneCoord.h"
#include "GroundEyeshot.h"
#include "SceneMgr.h"
#include "IEntityView.h"
#include "ISceneManager2.h"
#include "SceneEyeshot.h"
#include "MinimapEyeshot.h"
#include "WayPointMgr.h"
#include "PathFindAStar.h"
#include "PathFinder.h"
#include <list>

#define CMP_LT	-1
#define CMP_EQ	0
#define CMP_GT	1
//
//struct EntityViewPtr
//{
//	EntityView* pEntity;
//	int				nCount;
//	EntityViewPtr() : pEntity(0), nCount(0){}
//	bool operator == (const EntityViewPtr * const pEntity)
//	{
//		return (DWORD)pEntity == (DWORD)pEntity->pEntity;
//	}
//	bool operator == (const EntityViewPtr& item)
//	{
//		return pEntity == item.pEntity;
//	}/*
//	bool operator < (const EntityViewPtr& item)
//	{
//		return *pEntity < *item.pEntity;
//	}*/
//	EntityView* operator ->()
//	{
//		return pEntity;
//	}
//	bool isPoint()
//	{
//		return (pEntity->getSortLeft().x == pEntity->getSortRight().x && pEntity->getSortLeft().y == pEntity->getSortRight().y);
//	}
//	int compare(EntityViewPtr& item)
//	{
//		return 0;
//	}
//	bool isValid()
//	{
//		return (pEntity != 0);
//	}
//};
//
//bool operator==(const EntityViewPtr& a,const EntityViewPtr& b);

class SceneManager : public ISceneManager2
{
public:
	/**
	@param ptTile Tile����
	@param pEntity ʵ�����
	@param dwParam �����Ĳ���
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool addEntity(const xs::Point& ptTile, EntityView* pEntity, DWORD dwParam=0);

	/**
	@param ptFrom ��ʼTile����
	@param ptTo Ŀ��Tile����
	@param pEntity ʵ�����
	@param dwParam �����Ĳ���
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool moveEntity(const xs::Point& ptFrom, const xs::Point& ptTo, EntityView* pEntity, DWORD dwParam=0);

	/**
	@param ptTile ʵ�����ڵ�Tile����
	@param pEntity ʵ�����
	@param dwParam �����Ĳ���
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool removeEntity(const xs::Point& ptTile, EntityView* pEntity, DWORD dwParam=0);

	/**
	@param ptTile ʵ���Tile����
	@param pEntity ʵ�����
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool addEntityOccupant(const xs::Point& ptTile, EntityView* pEntity);

	/**
	@param ptTile ʵ���Tile����
	@param pEntity ʵ�����
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool removeEntityOccupant(const xs::Point& ptTile, EntityView* pEntity);

	virtual bool createScene(int nMapWidth,int nMapHeight,xs::Rect* lprcViewport);

	virtual bool loadScene(const char* szFilename,const char* szWpFilename,xs::Rect* lprcViewport,IEntityFactory *pEntityFactory,bool bDynamic,const xs::Point* pTileCenter = 0,bool oldVersion = false);

	/**
	@param pEntity ʵ�����
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool addGlobalSceneMagic(EntityView* pEntity);

	/**
	@param pEntity ʵ�����
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool removeGlobalSceneMagic(EntityView* pEntity);


	/**
	*/
	virtual bool save(const char* szFilename,bool writeOccupants);

	/**
	@return �����Ŀ��
	*/
	virtual int getSceneWidth() const;

	/**
	@return �����ĸ߶�
	*/
	virtual int getSceneHeight() const;

	/**
	@return �ӿڵľ���
	*/
	virtual const xs::Rect& getViewportRect() const;

	/**
	@param nViewWidth �ӿڵĿ��
	@param nViewHeight �ӿڵĸ߶�
	@remarks ���ӿڴ�С�����仯ʱ����
	*/
	virtual void onViewportSizeChanged(int nViewWidth, int nViewHeight);

	/**
	@param dx �����ӿڵ�x����ֵ
	@param dy �����ӿڵ�y����ֵ
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool scrollViewport(int dx, int dy);

	/**
	@param ptWorld �����ӿڵ��Դ˵�Ϊ����,��������
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool scroll2Center(xs::Point ptWorld);

	/**
	*/
	virtual void update(float tick,float deltaTick,IRenderSystem *pRenderSystem);

	/**
	*/
	virtual void draw(IRenderSystem* pRenderSystem,bool bWholeGround = false);

	/**
	*/
	virtual void drawTopMost(IRenderSystem* pRenderSystem);

	/** ȡ�õ�ǰ�ӿ����Ͻǵ���������X
	@return ��������X
	*/
	virtual int getViewTopLeftX() const;

	/** ȡ�õ�ǰ�ӿ����Ͻǵ���������Y
	@return ��������Y
	*/
	virtual int getViewTopLeftY() const;

	/**
	@param ptScreen ��Ļ����
	@param ptTile Tile����
	@remarks ����Ļ����ת��ΪTile����
	*/
	virtual void screen2Tile(IN const xs::Point& ptScreen, OUT xs::Point& ptTile) const;

	/**
	@param ptTile
	@param ptScreen
	@remarks ��Tile����ת��Ϊ��Ļ����
	*/
	virtual void tile2Screen(IN const xs::Point& ptTile, OUT xs::Point& ptTileCenter) const;

	/**
	@param ptScreen ��Ļ����
	@param ptWorld World����
	@remarks ����Ļ����ת��ΪWorld����
	*/
	virtual void screen2World(IN const xs::Point& ptScreen, OUT xs::Point& ptWorld) const;

	/**
	@param ptWorld World����
	@param ptScreen ��Ļ����
	@remarks ��World����ת��Ϊ��Ļ����
	*/
	virtual void world2Screen(IN const xs::Point& ptWorld, OUT xs::Point& ptScreen) const;

	/**
	@param ptWorld ��������
	@param ptTile Tile����
	@remarks ����������ת��ΪTile����
	*/
	virtual void world2Tile(IN const xs::Point& ptWorld, OUT xs::Point& ptTile) const;

	/**
	@param ptTile Tile����
	@param ptTileCenter ��������
	@remarks ��Tile����ת��Ϊ��������
	*/
	virtual void tile2World(IN const xs::Point& ptTile, OUT xs::Point& ptTileCenter) const;

	/**
	@param ptTile Tile����
	@return ����Tile����
	*/
	virtual Tile* getTile(const xs::Point& ptTile) const;

	/**  A* �Զ�Ѱ·ʱ ������getTile()ȥ�ж�title���赲��Ϣ����Ϊ�ϵļ���Title�ķ�Χ�������ὫTitle���赲��Ϣ����Ϊtrue;
	// ��˱�¶�˷���������ģ�����ȥ�ж�Title���赲��Ϣ;��WZH 2010.7.26��
	@param ptTile Tile����
	@return �����Ƿ��赲
	*/
	virtual bool IsAllBlock(const xs::Point& ptTile);

	/**
	@param ptScreen ��Ļ����
	@return ������Ļ���귵��Tile����
	*/
	virtual Tile* getTileFromScreen(xs::Point ptScreen) const;

	virtual bool isValid();
	/**
	@param ptTile Tile����
	@return ptTile����Tile�Ƿ�Ϊ��Ч��Tile
	*/
	virtual bool isValidTile(const xs::Point& ptTile);

	/**
	@param dwFlag Ҫ���õı�־λ
	@param dwClearFlag ����ı�־λ
	@param pParam �����Ĳ���
	@see eDrawGrid
	*/
	virtual void setDrawFlag(DWORD dwFlag, DWORD dwClearFlag, void* pParam = 0);

	/**
	@return ��־λ
	*/
	virtual DWORD getDrawFlag();

	/**
	@remarks �ͷŶ���
	*/
	virtual void release();

	/** ȡ��һ�����ο��ڵ�����Tiles
	@param rcWorld ���ο�����
	@param nListCount �б��С
	@param pListBuf ȡ�õ�Tiles�ɴ˷���
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool enumTileByWorldRect(IN const xs::Rect& rcWorld, IN OUT int& nListCount, OUT SnapshotTileInfo* pListBuf);

	/** ȡ��һ�����ο��ڵ�����Entities
	@param rcWorld ���ο�����
	@param nListCount �б��С
	@param pListBuf ȡ�õ�Entities�ɴ˷���
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool enumEntityByWorldRect(IN const xs::Rect& rcWorld, IN OUT int& nListCount, OUT SnapshotItemInfo* pListBuf);

	/** Ѱ·(��A*)
	@param ptFrom ·������ʼ��
	@param ptTo ·���Ľ�����
	@param ppBuffer ·���ɴ˷���
	@param nPathLen ·���ĳ����ɴ˷���
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool findPathEX(xs::Point ptFrom, xs::Point ptTo, xs::Point** ppBuffer, int& nPathLen);

	/** Ѱ·(A*_2)
	@param ptFrom ·������ʼ��
	@param ptTo ·���Ľ�����
	@param ppBuffer ·���ɴ˷���
	@param nPathLen ·���ĳ����ɴ˷���
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool findPath(xs::Point ptFrom, xs::Point ptTo, xs::Point** ppBuffer, int& nPathLen);

	/** Ѱ·(A*)
	@param ptFrom ·������ʼ��
	@param ptTo ·���Ľ�����
	@param ppBuffer ·���ɴ˷���
	@param nPathLen ·���ĳ����ɴ˷���
	@param isNoBlock �Ƿ�����赲
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool findPathAStar(xs::Point ptFrom, xs::Point ptTo, xs::Point** ppBuffer, int& nPathLen ,bool isNoBlock = false);

	/** ·��Ѱ·
	@param ptFrom ·������ʼ��
	@param ptTo ·���Ľ�����
	@param ppBuffer ·���ɴ˷���
	@param nPathLen ·���ĳ����ɴ˷���
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool findPathViaWaypoint(xs::Point ptFrom, xs::Point ptTo, xs::Point** ppBuffer, int& nPathLen);

	/**
	@param pt ��Ļ����
	@param dwFlag ֻ�о���dwFlag��EntityView�Żᱻѡ��
	@return ���ص�EntityView
	*/
	virtual EntityView*	hitTest(const xs::Point& pt);
	virtual void hitTest(const xs::Point& pt,EntityView** ppEntityViews,int& nNum);

	/** ȡ�õر����
	@return �ر����
	*/
	virtual IGround*	getGround();

	/**ȡ��Tile���ݵĿ�ȣ�����Զ����Ѱ·
	@return ���
	*/
	virtual int getMapTileWidth();

	/**ȡ��Tile���ݵĸ߶ȣ�����Զ����Ѱ·
	@return �߶�
	*/
	virtual int getMapTileHeight();

	/**����������������������С��ͼ
	@param pRenderSystem ��Ⱦϵͳ
	@param flags ��ʵ��&flags == true�Ż���
	*/
	virtual void drawEntireGround(IRenderSystem *pRenderSystem);

	/**����ͶӰ����ͼ����
	*/
	virtual void setupMatrix(bool wholeScene = false);

	/**ȡ��ͶӰ����
	@return ͶӰ����
	*/
	virtual Matrix4	getProjectionMatrix();

	/**ȡ����ͼ����
	@return ��ͼ����
	*/
	virtual Matrix4 getViewMatrix();

	/**Tile����ת����3D����
	@param ptTile Tile����
	@param vSpace 3D��������
	*/
	virtual void tile2Space(const xs::Point& ptTile,Vector3& vSpace);

	/**Space����ת����World����
	*/
	virtual void space2World(const Vector3& vSpace,xs::Point& ptWorld);

	/**World����ת����Space����
	*/
	virtual void world2Space(const xs::Point& ptWorld,Vector3& vSpace);

	/**Space����ת����Tile����
	*/
	virtual void space2Tile(const Vector3& vSpace,xs::Point& ptTile);

	virtual int tileDistance(const xs::Point& ptTile1, const xs::Point& ptTile2);

	virtual void setLightDirection(const Vector3& v);
	//����
	virtual void vibrate(int nVibrateRange/*�񶯵�������,����Ϊ��λ,��ΧΪ10-40֮��*/);

	/**��ȡС��ͼ�ӿ�
	@see IMinimap
	*/
	virtual IMinimap* getMinimap();

	/**
	*/
	virtual EntityView*	getFirstEntity();

	virtual EntityView*	getNextEntity();

	virtual const char*	getMapFileName();

	virtual ulong test();

	virtual void setRunType(RunType rt);

    //  ����Զ����
    virtual void SetDistanceTexture(const char *szFilename);

	virtual void SetAllEntityVisible();
	virtual RunType getRunType();
	virtual bool scroll2CenterByTime(xs::Point ptScreenCenter,ulong delta);

	//added by xxh 
	//�ж�EntityView�Ƿ񱣴���displaylist����fadeoutlist����
	//���¼��ص�ͼʹ��
	//ɾ��ʵ��ʱ��飬����ʹʵ��©ɾ zgz
	virtual bool	IsReferencedBySceneManager(EntityView * pEntity);

	virtual void   LockScene();

	virtual void   UnLockScene();
private:
	DWORD				m_dwDrawFlag;
	SceneMgr		m_Map;
	SceneCoord		m_SceneCo;
	CPathFindAStar   m_PathFindAStar;
	GroundEyeshot			m_GroundEyeshot;
	SceneEyeshot			m_SceneEyeshot;
	MinimapEyeshot			m_MinimapEyeshot;
	std::string				m_strMapFilename;

	typedef list<EntityView*> DisplayList;
	typedef list<EntityView*>::iterator DisplayListPtr;
	typedef list<EntityView*>::reverse_iterator DisplayListReversePtr;
	DisplayList			m_DisplayList;
	DisplayList			m_FadeOutList;
	DisplayListPtr		m_iteratorCurItem;

	DisplayList			m_VisibleListGround;
	DisplayList			m_VisibleListObj;	
	DisplayList			m_VisibleListMultiOcc;
	DisplayList			m_VisibleListGlobalSceneMagic;// ȫ�ֳ�����Ч�б��������ꡢ��ѩ [4/19/2011 zgz]

	xs::Point				m_ptSave;
	xs::MemoryStream		m_mapStream;
	WayPointMgr			m_WayPointManager;

	Matrix4				m_mtxProjection;
	Matrix4				m_mtxView;

	Vector3				m_lightDirection;
	uint				m_numModels;
public:
	typedef list<EntityView*> LogicList;
	typedef list<EntityView*>::iterator LogicListPtr;
	LogicList			m_LogicItemList;
	bool					m_bOldVersion;

	//���Ա���
	std::vector<DWORD>	m_flagsD;
	std::vector<DWORD>	m_flagsF;
public:
	bool isItemInViewArea(const xs::Point &ptTile, EntityView *pItemView);
	bool isItemInLogicArea(const xs::Point &ptTile, EntityView *pItemView);
	bool isItemVisible(const xs::Point& ptTile,EntityView *pItemView);
	bool createGroundEyeshot(xs::Stream* pMapFile,xs::Rect* lprcViewport, IEntityFactory* pEntityFactory,bool bDynamic);
	void createSceneCo(int nMapWidth,int nMapHeight);

	SceneMgr& getSceneMgr()
	{
		return m_Map;
	}

	SceneCoord& getSceneCoord()
	{
		return m_SceneCo;
	}

	SceneManager(xs::IResourceManager *pResourceManager);
	~SceneManager();
	void close();

	virtual int OnDrawSortPoint(const xs::Point& ptTile, EntityView *pEntity);
	virtual int OnDrawAnchor(const xs::Point& ptTile, EntityView *pEntity);
	virtual int OnDrawOccupant(const xs::Point& ptTile,Tile* pTile,void* pParam);
	virtual void OnEntityEnterViewport(const xs::Point& ptTile,EntityView* pEntity);
	virtual void OnEntityLeaveViewport(const xs::Point& ptTile,EntityView* pEntity);

	

private:
	void AddItemToDisplayList(EntityView* pEntity);
	void RemoveItemFromDisplayList(EntityView* pEntity);
	void AddItemToFadeOutList(EntityView* pEntity);
	void RemoveItemFromFadeOutList(EntityView* pEntity);

	void updateDisplayList(DisplayList& list,float tick,float deltaTick,IRenderSystem *pRenderSystem);
	void updateGlobalSceneMagic(float tick, float deltaTick, IRenderSystem* pRenderSystem);
	void drawGlobalSceneMagic(IRenderSystem* pRenderSystem); 
	//�������Ʊ���
	//��������
	int m_nVibrateRange;
	//�����񶯵��ۼ�ʱ��
	int m_nVibrateTime;
	//�������Ƿ����
	bool m_bVibrateFinish;
public:
	bool IsIntersect(EntityView& item1, EntityView& item2, xs::Rect& rc);
	int cmpPP(EntityView& item1, EntityView& item2);
	int cmpPL(EntityView& item1, EntityView& item2);
	int cmpLL(EntityView& item1, EntityView& item2);
	int compare(EntityView& item1, EntityView& item2);
	void addSortingEntitiesAll(EntityView* pEntity, DisplayList& _DisplayList);
	void addSortingEntities(EntityView* pEntity, DisplayList& _DisplayList);
	void sortVisibleEntities();


private:
	ImageRect*			m_pOccupantImageRect;
	xs::IResourceManager*	m_pResourceManager;

private:
	IShaderProgram	*	m_pShadowProgram;//������ȾӰ��


	// add by zjp;������Ⱦ���ܸ���
public:
	void ShowSkillTile(const xs::Point& ptTile);
	void ClearSkillTile();
private:
	list<xs::Point>			m_ListSkillTile;

	// ���ڵر�����볡���ͷż��ͬ�� [4/15/2011 zgz]
	xs::Mutex			m_mutex;
};

// ������������
class CSceneLock
{
public:
	CSceneLock();
	~CSceneLock();
private:
	CSceneLock(const CSceneLock& rhs);
	CSceneLock& operator=(const CSceneLock& rhs);
};
#endif
