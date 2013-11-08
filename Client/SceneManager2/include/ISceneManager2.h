
	/*! \addtogroup SceneManager
	*  ��������
	*  @{
	*/
#ifndef __I_SceneManager2_H__
#define __I_SceneManager2_H__

#include "Tile.h"

struct IEntityFactory;
/**�ӵ�ͼ��ö��һ�������ڵ�����Tile�Ľṹ��
*/
struct SnapshotTileInfo
{
	xs::Point		ptTile;
	Tile*		pTile;
};

/**�ӵ�ͼ��ö��һ�������ڵ�����EntityView�Ľṹ��
*/
struct SnapshotItemInfo 
{
	xs::Point		ptTile;
	EntityView*	pEntity;
};

enum
{
	/// �Ƿ����Tile����
	eDrawGrid = 0x00000001,

	/// �Ƿ����ռλ��
	eDrawOccupant = 0x00000002,

	/// �Ƿ���Ƶر�
	eDrawGround = 0x00000004,

	/// �Ƿ���������
	eDrawSortPoint = 0x00000008,

	/// �Ƿ����ê��
	eDrawAnchor = 0x00000010,

	/// �Ƿ����2D����
	eDraw2D = 0x000000020,

	///�Ƿ����3D����
	eDraw3D = 0x00000040,

	///�Ƿ����Grid����(�ͻ��˹���ر���������С����)
	eDrawMapGrid = 0x00000080,

	///�Ƿ���Ʒ���������
	eDraw9Grid = 0x00000100,

    //  �Ƿ����ʵ����Ϣ��Ѫ����������������
    //  ע��˴���ӵĴ���Ƚϼ򵥣���û�ж�ʵ�����ͽ��з����жϣ�Ҳû�н�Ѫ���������������ֿ���
    //  �����жϣ�����Ҳû�п���ʵ������Ļ��Ʊ�־����Ӧ����Щ�����ڲ߻�ȷ��ʵ�ʱ��ֺ��ٽ��ж�Ӧ
    //  ��ʵ�֣�
    eDrawEntityInfo = 0x00000200,

	//  ���Ʊ������Ϣ����ǰ����ֻ�����֡�
	eDrawEntityBoxInfo = 0x00000400	
};

/**�ر�飬256 * 256�����4����ͼ
*/
struct IGroundTile
{

	/**��õ�index����ͼ
	@param index ��(0-3)
	@return ��ͼָ��
	*/
	virtual ITexture*	getTexture(uint index) = 0;

	/**��õ�index����ͼ���ļ���
	@param index ��
	@return ��ͼ�ļ���
	*/
	virtual const char*		getTextureFileName(uint index) = 0;

	/**���õ�index�����ͼ�ļ���
	@param index ��
	@param szFileName ��ͼ�ļ���
	@param bLoad2GPU �Ƿ�����������ͼ
	*/
	virtual void		setTextureFileName(uint index,const char* szFileName,bool bLoad2GPU) = 0;

	/**��õ�index��Alpha��ͼ����
	@param index ��(0-2)
	@return ��ͼ����
	*/
	virtual	uchar*		getAlphaMap(uint index) = 0;

	/**����Alpha��ͼ
	@param index ��
	*/
	virtual void		updateAlphaMap(uint index) = 0;

	/**�����Ӱ��ͼ������
	@return ��ͼ����
	*/
	virtual uchar*		getShadowMap() = 0;

	/**������Ӱ��ͼ����
	*/
	virtual void		updateShadowMap() = 0;

	/**�����ͼ�Ĳ���
	@return ��ͼ����
	*/
	virtual uint		getTextureLayerNum() = 0;

	/**������ͼ�Ĳ���
	@param num ����(0-4)
	*/
	virtual void		setTextureLayerNum(uint num) = 0;

	/**ȡ�ð�Χ��
	@return ��Χ��
	*/
	virtual xs::Rect		getRect() = 0;

	/**ȡ�õر��X�±�
	@param x X�±�
	*/
	virtual int			getX() = 0;

	/**ȡ�õر��Y�±�
	@param y Y�±�
	*/
	virtual int			getY() = 0;
};

/**�ر�
*/
struct IGround
{

	/**������������ȡ�õر��
	@param ptWorld ��������
	@return �ر��ָ��
	*/
	virtual IGroundTile*	getGroundTile(const xs::Point& ptWorld) = 0;

	/**�����±�ȡ�õر��
	@param x �ر��X�±�
	@param y �ر��Y�±�
	@return �ر��ָ��
	*/
	virtual IGroundTile*	getGroundTile(int x,int y) = 0;

	/**����Ĭ����ͼ(��û����ͼ��ʱ��)
	@param szFileName ��ͼ�ļ���
	*/
	virtual void			setDefaultTexture(const char* szFileName) = 0;

	/**ȡ��Ĭ����ͼ��ָ��
	@return ��ͼָ��
	*/
	virtual ITexture*		getDefaultTexture() = 0;

	/**ȡ���ӿ��ڵر��е�X,Y����
	@return ����
	*/
	virtual xs::Point			getViewLeftTop() = 0;

	/**ȡ�õر��Ŀ��
	@return �ر����
	*/
	virtual int				getGroundTileWidth() = 0;

	/**ȡ�õر��ĸ߶�
	@return �ر��߶�
	*/
	virtual int				getGroundTileHeight() = 0;

	/**ȡ���ܹ��ĺ���ر������
	@return �ر������
	*/
	virtual int				getTotalTileX() = 0;

	/**ȡ���ܹ�������ر������
	@return �ر������
	*/
	virtual int				getTotalTileY() = 0;

	/**�����Ƿ���Ƶر��ı߿�
	@param bDraw �Ƿ����
	*/
	virtual void			setDrawTileLine(bool bDraw) = 0;

	/**ȡ���Ƿ���Ƶر��ı߿�
	@return �Ƿ����
	*/
	virtual bool			isDrawTileLine() = 0;

	/**ʹ����ͼ������������ͼ
	@param szFilename ��ͼ�ļ���
	@return �Ƿ�ɹ�
	@remarks ���ڵ�ͼ�༭��
	*/
	virtual bool			fillMap(const char* szFilename) = 0;

	/**ĳ���ر�����Դʱ���Ѿ�����
	@param x �ر������X
	@param y �ر������Y
	@return �Ƿ����
	@remarks ���ڵ�ͼ�༭��
	*/
	virtual bool			_isLoaded(int x,int y) = 0;

	/**����ĳ���ر�����Դ
	@param x �ر������X
	@param y �ر������Y
	@remarks ���ڵ�ͼ�༭��
	*/
	virtual void			_load(int x,int y) = 0;

	/**ж��ĳ���ĵر�����Դ
	@param x �ر������X
	@param y �ر������Y
	@remarks ���ڵ�ͼ�༭��
	*/
	virtual void			_unload(int x,int y) = 0;

    //  ����Զ����ͼ��
    //  @param szFileName ��ͼ�ļ�����
    virtual void SetDistanceTexture(const char* szFileName) = 0;

    //  ȡ��Զ����ͼ��ָ�룻
    //  @return ��ͼָ�룻
    virtual ITexture* GetDistanceTexture() = 0;
};

class MinimapTile;
struct IMinimap
{
	/**
	*/
	virtual void drawWorldMap(IRenderSystem *pRenderSystem,const xs::Rect& rcDraw) = 0;

	/**
	*/
	virtual void draw(IRenderSystem *pRenderSystem,const xs::Rect& rcDraw) = 0;

	/**
	*/
	virtual xs::Rect getViewport() = 0;

	/** �ı��ӿڴ�С
	*  ����
	*/
	virtual bool ViewportSizeChanged(int nMultiple) = 0;

	/**
	@param x ��X�±�
	@param y ��Y�±�
	@return ��ָ��
	*/
	virtual MinimapTile*	getMiniMapTile(int x,int y) = 0;
};

enum RunType
{
	RUN_TYPE_GAME,
	RUN_TYPE_EDITOR
};

struct ISceneManager2
{
	/**
	@param ptTile Tile����
	@param pEntity ʵ�����
	@param dwParam �����Ĳ���
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool addEntity(const xs::Point& ptTile, EntityView* pEntity, DWORD dwParam=0) = 0;

	/**
	@param ptFrom ��ʼTile����
	@param ptTo Ŀ��Tile����
	@param pEntity ʵ�����
	@param dwParam �����Ĳ���
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool moveEntity(const xs::Point& ptFrom, const xs::Point& ptTo, EntityView* pEntity, DWORD dwParam=0) = 0;

	/**
	@param ptTile ʵ�����ڵ�Tile����
	@param pEntity ʵ�����
	@param dwParam �����Ĳ���
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool removeEntity(const xs::Point& ptTile, EntityView* pEntity, DWORD dwParam=0) = 0;

	/**
	@param ptTile ʵ���Tile����
	@param pEntity ʵ�����
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool addEntityOccupant(const xs::Point& ptTile, EntityView* pEntity) = 0;

	/**
	@param ptTile ʵ���Tile����
	@param pEntity ʵ�����
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool removeEntityOccupant(const xs::Point& ptTile, EntityView* pEntity) = 0;

	/**
	*/
	virtual bool createScene(int nMapWidth,int nMapHeight,xs::Rect* lprcViewport) = 0;

	/**
	*/
	virtual bool loadScene(const char* szFilename,const char* szWpFilename,xs::Rect* lprcViewport,IEntityFactory *pEntityFactory,bool bDynamic,const xs::Point* pTileCenter = 0,bool oldVersion = false) = 0;

	/**�����ͼ
	@param writeOccupants �Ƿ��ռλ��д����ͼ��
	*/
	virtual bool save(const char* szFilename,bool writeOccupants = false) = 0;

	/**
	@return �����Ŀ��
	*/
	virtual int getSceneWidth() const = 0;

	/**
	@return �����ĸ߶�
	*/
	virtual int getSceneHeight() const = 0;

	/**
	@return �ӿڵľ���
	*/
	virtual const xs::Rect& getViewportRect() const = 0;

	/**
	@param nViewWidth �ӿڵĿ��
	@param nViewHeight �ӿڵĸ߶�
	@remarks ���ӿڴ�С�����仯ʱ����
	*/
	virtual void onViewportSizeChanged(int nViewWidth, int nViewHeight) = 0;

	/**
	@param dx �����ӿڵ�x����ֵ
	@param dy �����ӿڵ�y����ֵ
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool scrollViewport(int dx, int dy) = 0;

	/**
	@param ptScreenCenter �����ӿڵ��Դ˵�Ϊ����,Ϊ��Ļ����
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool scroll2Center(xs::Point ptScreenCenter) = 0;

	/**
	*/
	virtual void update(float tick,float deltaTick,IRenderSystem *pRenderSystem) = 0;

	/**
	*/
	virtual void draw(IRenderSystem* pRenderSystem,bool bWholeGround = false) = 0;

	/**
	*/
	virtual void drawTopMost(IRenderSystem* pRenderSystem) = 0;

	/** ȡ�õ�ǰ�ӿ����Ͻǵ���������X
	@return ��������X
	*/
	virtual int getViewTopLeftX() const = 0;

	/** ȡ�õ�ǰ�ӿ����Ͻǵ���������Y
	@return ��������Y
	*/
	virtual int getViewTopLeftY() const = 0;

	/**
	@param ptScreen ��Ļ����
	@param ptTile Tile����
	@remarks ����Ļ����ת��ΪTile����
	*/
	virtual void screen2Tile(IN const xs::Point& ptScreen, OUT xs::Point& ptTile) const = 0;

	/**
	@param ptTile
	@param ptScreen
	@remarks ��Tile����ת��Ϊ��Ļ����
	*/
	virtual void tile2Screen(IN const xs::Point& ptTile, OUT xs::Point& ptTileCenter) const = 0;

	/**
	@param ptScreen ��Ļ����
	@param ptWorld World����
	@remarks ����Ļ����ת��ΪWorld����
	*/
	virtual void screen2World(IN const xs::Point& ptScreen, OUT xs::Point& ptWorld) const = 0;

	/**
	@param ptWorld World����
	@param ptScreen ��Ļ����
	@remarks ��World����ת��Ϊ��Ļ����
	*/
	virtual void world2Screen(IN const xs::Point& ptWorld, OUT xs::Point& ptScreen) const = 0;

	/**
	@param ptWorld ��������
	@param ptTile Tile����
	@remarks ����������ת��ΪTile����
	*/
	virtual void world2Tile(IN const xs::Point& ptWorld, OUT xs::Point& ptTile) const = 0;

	/**
	@param ptTile Tile����
	@param ptTileCenter ��������
	@remarks ��Tile����ת��Ϊ��������
	*/
	virtual void tile2World(IN const xs::Point& ptTile, OUT xs::Point& ptTileCenter) const = 0;

	/**
	@param ptTile Tile����
	@return ����Tile����
	*/
	virtual Tile* getTile(const xs::Point& ptTile) const = 0;

	/**  A* �Զ�Ѱ·ʱ ������getTile()ȥ�ж�title���赲��Ϣ����Ϊ�ϵļ���Title�ķ�Χ�������ὫTitle���赲��Ϣ����Ϊtrue;
	// ��˱�¶�˷���������ģ�����ȥ�ж�Title���赲��Ϣ;��WZH 2010.7.26��
	@param ptTile Tile����
	@return �����Ƿ��赲
	*/
	virtual bool IsAllBlock(const xs::Point& ptTile) = 0;

	/**
	@param ptScreen ��Ļ����
	@return ������Ļ���귵��Tile����
	*/
	virtual Tile* getTileFromScreen(xs::Point ptScreen) const = 0;

	/**
	@param ptTile Tile����
	@return ptTile����Tile�Ƿ�Ϊ��Ч��Tile
	*/
	virtual bool isValidTile(const xs::Point& ptTile) = 0;

	/**
	@param dwFlag Ҫ���õı�־λ
	@param dwClearFlag ����ı�־λ
	@param pParam �����Ĳ���
	@see eDrawGrid
	*/
	virtual void setDrawFlag(DWORD dwFlag, DWORD dwClearFlag, void* pParam = 0) = 0;

	/**
	@return ��־λ
	*/
	virtual DWORD getDrawFlag() = 0;

	virtual bool isValid() = 0;
	/**
	@remarks �ͷŶ���
	*/
	virtual void release() = 0;

	/** ȡ��һ�����ο��ڵ�����Tiles
	@param rcWorld ���ο�����
	@param nListCount �б��С
	@param pListBuf ȡ�õ�Tiles�ɴ˷���
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool enumTileByWorldRect(IN const xs::Rect& rcWorld, IN OUT int& nListCount, OUT SnapshotTileInfo* pListBuf) = 0;

	/** ȡ��һ�����ο��ڵ�����Entities
	@param rcWorld ���ο�����
	@param nListCount �б��С
	@param pListBuf ȡ�õ�Entities�ɴ˷���
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool enumEntityByWorldRect(IN const xs::Rect& rcWorld, IN OUT int& nListCount, OUT SnapshotItemInfo* pListBuf) = 0;

	/** Ѱ·(��A*)
	@param ptFrom ·������ʼ��
	@param ptTo ·���Ľ�����
	@param ppBuffer ·���ɴ˷���
	@param nPathLen ·���ĳ����ɴ˷���
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool findPathEX(xs::Point ptFrom, xs::Point ptTo, xs::Point** ppBuffer, int& nPathLen) = 0;

	/** Ѱ·(A*)
	@param ptFrom ·������ʼ��
	@param ptTo ·���Ľ�����
	@param ppBuffer ·���ɴ˷���
	@param nPathLen ·���ĳ����ɴ˷���
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool findPath(xs::Point ptFrom, xs::Point ptTo, xs::Point** ppBuffer, int& nPathLen) = 0;

	/** Ѱ·(A*)
	@param ptFrom ·������ʼ��
	@param ptTo ·���Ľ�����
	@param ppBuffer ·���ɴ˷���
	@param nPathLen ·���ĳ����ɴ˷���
	@param isNoBlock �Ƿ�����赲
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool findPathAStar(xs::Point ptFrom, xs::Point ptTo, xs::Point** ppBuffer, int& nPathLen,bool isNoBlock = false) = 0;


	/** ·��Ѱ·
	@param ptFrom ·������ʼ��
	@param ptTo ·���Ľ�����
	@param ppBuffer ·���ɴ˷���
	@param nPathLen ·���ĳ����ɴ˷���
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	@note Ѱ�ҵ���·��Ϊ���е�·��
	*/
	virtual bool findPathViaWaypoint(xs::Point ptFrom, xs::Point ptTo, xs::Point** ppBuffer, int& nPathLen) = 0;

	/**
	@param pt ��Ļ����
	@param dwFlag ֻ�о���dwFlag��EntityView�Żᱻѡ��
	@return ���ص�EntityView
	*/
	virtual EntityView*	hitTest(const xs::Point& pt) = 0;

	/**
	@param pt ��Ļ����
	@param dwFlag ֻ�о���dwFlag��EntityView�Żᱻѡ��
	@param ppEntityViews ���ص�EntityView*����
	@param nNum �����ppEntityViews�Ĵ�С������ѡ�е����������
	*/
	virtual void hitTest(const xs::Point& pt,EntityView** ppEntityViews,int& nNum) = 0;

	/** ȡ�õر����
	@return �ر����
	*/
	virtual IGround*	getGround() = 0;

	/**ȡ��Tile���ݵĿ�ȣ�����Զ����Ѱ·
	@return ���
	*/
	virtual int getMapTileWidth() = 0;

	/**ȡ��Tile���ݵĸ߶ȣ�����Զ����Ѱ·
	@return �߶�
	*/
	virtual int getMapTileHeight() = 0;

	/**���������ر���������С��ͼ
	@param pRenderSystem ��Ⱦϵͳ
	*/
	virtual void drawEntireGround(IRenderSystem *pRenderSystem) = 0;

	/**����ͶӰ����ͼ����
	*/
	virtual void setupMatrix(bool wholeScene = false) = 0;

	/**ȡ��ͶӰ����
	@return ͶӰ����
	*/
	virtual Matrix4	getProjectionMatrix() = 0;

	/**ȡ����ͼ����
	@return ��ͼ����
	*/
	virtual Matrix4 getViewMatrix() = 0;

	/**Tile����ת����3D����
	@param ptTile Tile����
	@param vSpace 3D��������
	*/
	virtual void tile2Space(const xs::Point& ptTile,Vector3& vSpace) = 0;

	/**Space����ת����World����
	*/
	virtual void space2World(const Vector3& vSpace,xs::Point& ptWorld) = 0;

	/**World����ת����Space����
	*/
	virtual void world2Space(const xs::Point& ptWorld,Vector3& vSpace) = 0;

	/**Space����ת����Tile����
	*/
	virtual void space2Tile(const Vector3& vSpace,xs::Point& ptTile) = 0;

	/**ptTile1��ptTile2֮��ľ���
	*/
	virtual int tileDistance(const xs::Point& ptTile1, const xs::Point& ptTile2) = 0;

	/**���ù��ߵķ���,��������Ӱ��
	*/
	virtual void setLightDirection(const Vector3& v) = 0;

	/**��ȡС��ͼ�ӿ�
	@see IMinimap
	*/
	virtual IMinimap* getMinimap() = 0;

	/**
	*/
	virtual EntityView*	getFirstEntity() = 0;

	virtual EntityView*	getNextEntity() = 0;

	virtual const char*	getMapFileName() = 0;

	virtual ulong test() = 0;

	virtual void setRunType(RunType rt) = 0;

    //  ����Զ����
    virtual void SetDistanceTexture(const char *szFilename) = 0;

	//�ṩ���༭��ʹ��
	//ʹ���е�����ɼ�
	virtual void SetAllEntityVisible() = 0;
	virtual RunType getRunType() = 0;
	/**
	@param ptScreenCenter ����ʱ�佥��Ĺ����ӿڵ��Դ˵�Ϊ����,Ϊ��Ļ����
	@return �ɹ�Ϊtrue��ʧ��Ϊfalse
	*/
	virtual bool scroll2CenterByTime(xs::Point ptScreenCenter,ulong delta) = 0;

	virtual void vibrate(int nVibrateRange/*�񶯵�������,����Ϊ��λ,��ΧΪ10-40֮��*/) = 0;

	virtual bool	IsReferencedBySceneManager(EntityView * pEntity) = 0;

	virtual void ShowSkillTile(const xs::Point& ptTile) = 0;
	virtual void ClearSkillTile() = 0;

	// �������������ڵر�����볡���ͷż��ͬ�� [4/15/2011 zgz]
	virtual void   LockScene() = 0;
	
	// �������������ڵر�����볡���ͷż��ͬ�� [4/15/2011 zgz]
	virtual void   UnLockScene() = 0;
};

#if defined(_LIB) || defined(SCENEMANAGER_STATIC_LIB)/// ��̬��汾
#	pragma comment(lib, MAKE_LIB_NAME(xs_csm))
extern "C" ISceneManager2* LoadCSM2(xs::IResourceManager *pResourceManager);
#	define	CreateSceneManagerProc	LoadCSM2)
extern "C" ISceneManager2* LoadCSM2(xs::IResourceManager *pResourceManager);
#	define	CreateSceneManagerProc	LoadCSM2
#else /// ��̬��汾
typedef ISceneManager2* (RKT_CDECL *procCreateSceneManager)(xs::IResourceManager *pResourceManager);
#	define	CreateSceneManagerProc	DllApi<procCreateSceneManager>::load(MAKE_DLL_NAME(xs_csm), "LoadCSM2")
#	define  CloseSceneManagerProc()	DllApi<procCreateSceneManager>::free()
#endif


#endif

	/** @} */