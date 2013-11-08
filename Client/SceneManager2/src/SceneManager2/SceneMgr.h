#ifndef __SceneMgr_H__
#define __SceneMgr_H__

#include "IEntityView.h"
#include "SceneCoord.h"
#include "Tile.h"
#include <list>
#include <map>

#include "PathFinder.h"
#include "SceneBlock.h"
#include "ISceneManager2.h"
#include "CPathFinderByAStar.h"
//  Ĭ�ϵĵ�ͼ�汾�ţ�
#define ORIGIN_MAP_VERSION 0

//  ֧����Ч���ź���ת�Ƕȵİ汾�İ汾�ţ�
#define SUPPORT_EFFECT_SCALE_AND_ANGLE_ADJUST_MAP_VERSION 1

#define SHIFT_WIDTH			10
#define SHIFT_HEIGHT		9
#define GRID_WIDTH			1024
#define GRID_HEIGHT			512
#define TILE_GRID_ROW		5
#define TILE_GRID_COL		3
#define OBJECT_GRID_ROW		5
#define OBJECT_GRID_COL		3

#define TILES_PREREAD_WIDTH		GRID_WIDTH * TILE_GRID_COL
#define TILES_PREREAD_HEIGHT	GRID_HEIGHT * TILE_GRID_ROW

enum
{
	mdNorth = 0,
	mdEastNorth,
	mdEast,
	mdEastSouth,
	mdSouth,
	mdWestSouth,
	mdWest,
	mdWestNorth,
	mdAll,

	mdMaxUpdateType
};

class GroundEyeshot;

struct EnumItem
{
	xs::Point		ptTile;
	EntityView*	pEntity;
};

struct EnumTile
{
	xs::Point		ptTile;
	Tile*		pTile;
};

struct BlockInfo
{
	xs::Point	ptLeftTop;
	int		nIndex;
};

#define MAX_EnumItem_COUNT		4096
#define MAX_SNAP_BUF_SIZE		(MAX_EnumItem_COUNT * sizeof(EnumItem))

struct SceneFileLineHeader
{
	int		nFromX;
	int		nTileCount;
};

using namespace std;
typedef list<EntityView*>  SceneEntityList;

class SceneMgr :public CPathFinderByAStar<SceneMgr>,public PathFinder<SceneMgr>
{
	ISceneManager2*	m_pSceneManager;
	//ÿ��1024*512�Ĵ��仯��ʱ��tileԴ�㶼��ı�
	xs::Point	m_ptTileOrigin;

	//��������������tile��ص�
	int		m_nMatrixWidth;
	int		m_nMatrixHeight;
	xs::Rect	m_rcMapTileRect;
	//tile ��������
	Tile*	m_pTiles;

	//�����ҵ�����ĵ�ͼ�ļ�ƫ��
	DWORD*	m_pMapTable;	// ��¼1024*512���������
	
	//��������ĵ�ͼ��С
	int		m_nMapWidth;
	int		m_nMapHeight;
	xs::Rect	m_rcMap;
	
	//����ת����
	SceneCoord m_SceneCo;
	//��ͼ�ļ�������
	xs::Stream* m_pStream;
	//ʵ�幤��
	IEntityFactory* m_pItemCF;
	
	VariableLengthArrayCache<DWORD,EntityView*> m_LayerListCache;
	DWORD* m_pMultiValueTable;
	SceneEntityList m_EntityList;
	typedef void (SceneMgr::*ProcScrollTilesInfo)(BlockInfo* pBlockInfo, int nRows, int nCols, int nTileRow, int nTileCol, xs::Point& ptNewTileOrigin, int dx, int dy);
	static ProcScrollTilesInfo m_fnScrollTileInfo[mdMaxUpdateType];

	GroundEyeshot*		m_pGround;

	bool m_bDynamic;

	SceneBlock		m_MapBlockBuffer;

	//�����ͼʱ���Ƿ��ռλ��ֱ�Ӵ洢����ͼ��
	bool			m_bWriteOccupants;
	
	////��־����ֹ��Ч��Ԥ�����б������ظ���
	bool	m_VectorPreLoad[MAP_MAXCOUNT];
private:
	static Tile m_EmptyTile;
public:
	bool IsBlock(xs::Point ptPos)
	{
		Tile& tile = getTile(ptPos.x, ptPos.y);
		return (!tile.isValid() || tile.isBlock());
	}
	// �Զ�Ѱ·�����ķ�ΧΪ��ͼ���赲��Ϣ
	bool  IsAllBlock(xs::Point ptPos)
	{
		Tile& tile = getTileArray(ptPos.x, ptPos.y);
		return (!tile.isValid() || tile.isBlock());
	}

	/** �ж�һ��tile�Ƿ���Ч������·ģ��ʹ��
	@param   
	@param   
	@return  
	*/
	bool IsInValidTile(xs::Point ptTile)
	{
		Tile& tile = getTileArray(ptTile.x, ptTile.y);
		if(!tile.isValid())
		{
			return true;
		}
		return false;
	}
	bool isMovableForMultiOcc(EntityView* pEntity, xs::Point ptFrom, xs::Point ptTo);	
	int getSceneWidth()const		{return m_nMapWidth;}
	int getSceneHeight()const		{return m_nMapHeight;}
	void moveTop(BlockInfo* pBlockInfo, int nRows, int nCols, int nTileRow, int nTileCol, xs::Point& ptNewTileOrigin, int dx, int dy);
	void moveRightTop(BlockInfo* pBlockInfo, int nRows, int nCols, int nTileRow, int nTileCol, xs::Point& ptNewTileOrigin, int dx, int dy);
	void moveRight(BlockInfo* pBlockInfo, int nRows, int nCols, int nTileRow, int nTileCol, xs::Point& ptNewTileOrigin, int dx, int dy);
	void moveRightDown(BlockInfo* pBlockInfo, int nRows, int nCols, int nTileRow, int nTileCol, xs::Point& ptNewTileOrigin, int dx, int dy);
	void moveDown(BlockInfo* pBlockInfo, int nRows, int nCols, int nTileRow, int nTileCol, xs::Point& ptNewTileOrigin, int dx, int dy);
	void moveLeftDown(BlockInfo* pBlockInfo, int nRows, int nCols, int nTileRow, int nTileCol, xs::Point& ptNewTileOrigin, int dx, int dy);
	void moveLeft(BlockInfo* pBlockInfo, int nRows, int nCols, int nTileRow, int nTileCol, xs::Point& ptNewTileOrigin, int dx, int dy);
	void moveleftTop(BlockInfo* pBlockInfo, int nRows, int nCols, int nTileRow, int nTileCol, xs::Point& ptNewTileOrigin, int dx, int dy);
	void moveAll(BlockInfo* pBlockInfo, int nRows, int nCols, int nTileRow, int nTileCol, xs::Point& ptNewTileOrigin, int dx, int dy);
	void scrollTilesInfo(BlockInfo* pBlockInfo, int nRows, int nCols, int nTileRow, int nTileCol, int nDirection, xs::Point& ptNewTileOrigin, int dx, int dy);
	void initBlockInfo(xs::Point& ptLeftTop, int nTileRow, int nTileCol,int realRow,int realCol);
	void loadBlockInfo(xs::Point& ptLeftTop, int nIndex, int nTileRow, int nTileCol);
	void copyBlockInfo(xs::Point& ptSrcLeftTop, xs::Point& ptDstLeftTop, int nTileRow, int nTileCol);
	void copyBlockInfoForSurface(xs::Point& ptSrcLeftTop, xs::Point& ptDstLeftTop, int nTileRow, int nTileCol);
	void setOriginTile(xs::Point& ptTileOrigin);
	xs::Point GetOriginTile()		{return m_ptTileOrigin;}
	bool isValid(){	return m_pTiles != 0;}
	bool AdjustTileRect(xs::Rect &rc);
	bool IsTileInMap(int tx,int ty) const
	{
		xs::Point ptOff (tx - m_ptTileOrigin.x, ty - m_ptTileOrigin.y);
		return (ptOff.x >= 0 && ptOff.x < m_nMatrixWidth && ptOff.y >= 0 && ptOff.y < m_nMatrixHeight);
	}
	bool IsTileInMap(const xs::Point& ptTile) const
	{
		xs::Point ptOff (ptTile.x - m_ptTileOrigin.x, ptTile.y - m_ptTileOrigin.y);
		return (ptOff.x >= 0 && ptOff.x < m_nMatrixWidth && ptOff.y >= 0 && ptOff.y < m_nMatrixHeight);
	}
	bool isValidTile(const xs::Point& ptTile)
	{
		xs::Point ptOff (ptTile.x - m_ptTileOrigin.x, ptTile.y - m_ptTileOrigin.y);
		if (ptOff.x >= 0 && ptOff.x < m_nMatrixWidth && ptOff.y >= 0 && ptOff.y < m_nMatrixHeight)
			return m_pTiles[m_pMultiValueTable[ptOff.y] + ptOff.x].isValid();
		else
			return false;
	}
	bool isValidTile(int tx,int ty)
	{
		xs::Point ptOff (tx - m_ptTileOrigin.x, ty - m_ptTileOrigin.y);
		if (ptOff.x >= 0 && ptOff.x < m_nMatrixWidth && ptOff.y >= 0 && ptOff.y < m_nMatrixHeight)
			return m_pTiles[m_pMultiValueTable[ptOff.y] + ptOff.x].isValid();
		else
			return false;
	}

	Tile& getTile(const xs::Point& ptTile) const
	{
		if (NULL == m_pTiles || NULL == m_pMultiValueTable)
		{
			return m_EmptyTile;
		}

		xs::Point ptOff (ptTile.x - m_ptTileOrigin.x, ptTile.y - m_ptTileOrigin.y);
		if (ptOff.x >= 0 && ptOff.x < m_nMatrixWidth && ptOff.y >= 0 && ptOff.y < m_nMatrixHeight)
			return m_pTiles[m_pMultiValueTable[ptOff.y] + ptOff.x];
		else
			return m_EmptyTile;
	}

	Tile& getTile(int tx, int ty) const
	{
		if (NULL == m_pTiles || NULL == m_pMultiValueTable)
		{
			return m_EmptyTile;
		}

		xs::Point ptOff (tx - m_ptTileOrigin.x, ty - m_ptTileOrigin.y);
		if (ptOff.x >= 0 && ptOff.x < m_nMatrixWidth && ptOff.y >= 0 && ptOff.y < m_nMatrixHeight)
			return m_pTiles[m_pMultiValueTable[ptOff.y] + ptOff.x];
		else
			return m_EmptyTile;
	}

	// �Զ�Ѱ·�����ķ�ΧΪ��ͼ���赲��Ϣ
	Tile& getTileArray(int tx, int ty) const
	{
		xs::Point ptOff (tx, ty);
		if (ptOff.x >= 0 && ptOff.x < m_nMatrixWidth && ptOff.y >= 0 && ptOff.y < m_nMatrixHeight)
			return m_pTiles[m_pMultiValueTable[ptOff.y] + ptOff.x];
		else
			return m_EmptyTile;
	}
	/*inline Tile& _GetTile(const xs::Point& ptTile) const
	{
		xs::Point ptOff = {ptTile.x - m_ptTileOrigin.x, ptTile.y - m_ptTileOrigin.y};
		assert(ptOff.x >= 0 && ptOff.x < m_nMatrixWidth && ptOff.y >= 0 && ptOff.y < m_nMatrixHeight);
		return m_pTiles[m_pMultiValueTable[ptOff.y] + ptOff.x];
	}

	inline Tile& _GetTile(int tx, int ty) const
	{
		xs::Point ptOff = {tx - m_ptTileOrigin.x, ty - m_ptTileOrigin.y};
		assert(ptOff.x >= 0 && ptOff.x < m_nMatrixWidth && ptOff.y >= 0 && ptOff.y < m_nMatrixHeight);
		return m_pTiles[m_pMultiValueTable[ptOff.y] + ptOff.x];
	}*/

	Tile* getTilePtr(const xs::Point& ptTile) const
	{
		xs::Point ptOff (ptTile.x - m_ptTileOrigin.x, ptTile.y - m_ptTileOrigin.y);
		if (ptOff.x >= 0 && ptOff.x < m_nMatrixWidth && ptOff.y >= 0 && ptOff.y < m_nMatrixHeight)
		{
			Tile* pTile = &m_pTiles[m_pMultiValueTable[ptOff.y] + ptOff.x];
			if (pTile->isValid())
				return pTile;
		}
		return 0;
	}

	inline Tile* getMapArray()						{return m_pTiles;}
	int getMapArrayWidth() const					{return m_nMatrixWidth;}
	int getMapArrayHeight() const					{return m_nMatrixHeight;}
	const SceneCoord& getSceneCoord() const	{return m_SceneCo;}
	SceneCoord GetSceneCoordNormal() {return m_SceneCo;}
	SceneBlock*	getMapBlockBuffer(){return &m_MapBlockBuffer;}

	bool create(GroundEyeshot *pGround,int nMapWidth, int nMapHeight, xs::Rect& rcPreRead,ISceneManager2 *pSceneManager);
	void close();

	bool save(xs::DataChunk* pDataChunk,bool writeOccupants);
	bool load(GroundEyeshot *pGround,xs::Stream* pStream,IEntityFactory* pEntityFactory, xs::Rect* pViewport,const xs::Point* pTileCenter,bool bDynamic,ISceneManager2 *pSceneManager);

	virtual bool addEntity(const xs::Point& ptTile, EntityView* pEntity);
	virtual bool moveEntity(const xs::Point& ptFrom, const xs::Point& ptTo, EntityView* pEntity);
	virtual bool removeEntity(const xs::Point& ptTile, EntityView* pEntity);

	virtual bool addEntityOccupant(const xs::Point& ptTile, EntityView* pEntity);
	virtual bool removeEntityOccupant(const xs::Point& ptTile, EntityView* pEntity);

	bool addLayerItem(const xs::Point &pt, EntityView *pEntity);

	bool snapshotRectItem(const xs::Rect& rc,/*in out*/int& nListCount,/*out*/EnumItem* pListBuf);
	bool enumEntityByWorldRect(const xs::Rect &rcWorld, /*in out*/int& nListCount,/*out*/EnumItem* pListBuf);
	bool enumTileByWorldRect(const xs::Rect &rcWorld, /*in out*/int& nListCount,/*out*/EnumTile* pListBuf);

	SceneMgr();
	virtual ~SceneMgr();
	void viewRectToPreReadRect(xs::Rect& rcView, xs::Rect& rcPreRead, int nMapWidth, int nMapHeight);
	
private:
	bool _LoadBlock(xs::Stream* pStream, xs::Point ptTileLeftTop, int nTileRow, int nTileCol, IEntityFactory* pEntityFactory);
	bool _LoadTileInfo(xs::Stream* pStream, Tile* pTile, xs::Point& ptTile, IEntityFactory* pEntityFactory);
	bool _LoadTileInfoOld(xs::Stream* pStream, Tile* pTile, xs::Point& ptTile, IEntityFactory* pEntityFactory);
	bool _SaveBlock(xs::Stream* pStream, xs::Point ptTileLeftTop, int nTileRow, int nTileCol);
	bool _SaveMultiEmptyTileInfo(xs::Stream* pStream, int nCount);
	bool _SaveMultiTileInfo(xs::Stream* pStream, xs::Point* ptTileList, int nCount);
	bool _SaveTileInfo(xs::Stream* pStream, Tile* pTile);
	void addMultiOccupantValue(xs::Point pt, EntityView *pEntity);
	void removeMultiOccupantValue(xs::Point pt, EntityView *pEntity);
	bool testIntersect(xs::Point pt, EntityView* pEntity);
	
	//add by yhc
	//��ȡ����ͼ����Ч��Ϣ
	bool GetBlockEf(xs::Stream* pStream, xs::Point ptTileLeftTop, int nTileRow, int nTileCol);
	bool GetTileEf(xs::Stream* pStream, Tile* pTile, xs::Point& ptTile);
protected:
	bool createMapArray(xs::Rect& rcPreRead);
	
protected:
    //  �汾�ţ�
    int m_nMapVersion;


#if defined(RELEASEDEBUG) || defined(_DEBUG)
private:
	void AddTileInfo(xs::Point ptTile, string strFileName);

	typedef list<string> TLIST_NAME;
	typedef map<DWORD, TLIST_NAME> TMAP_TILEINFO;
	TMAP_TILEINFO m_mapTileInfo;
#endif

};


#endif
