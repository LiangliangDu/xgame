#ifndef __SceneGrid_H__
#define __SceneGrid_H__

#include "SceneMgr.h"

//add by yhc ��ע��
//�������ĸ���,ÿ��������1024*512Ϊ��С.
//
struct IEyeshotCallback;
class SceneGrid
{
	//������ͼ�ж��
	RECT				m_rcMapGrid;

	//�����ж��Լ����ڵĵ��ڲ������������,��ҵ��µ��Ƿ��¸��ӱ仯,�����ڵ�ͼ���ز������¸���
	RECT				m_rcPlayerGrid;
	//�Լ����ڵĸ�������x,y
	POINT				m_ptPlayerGrid;

	//�¾ɷ�Χ�Աȿɵó��ƶ�����
	RECT				m_rcOldPreReadGrid;
	//���Լ����ڵĸ�������(m_ptPlayerGrid)Ϊ����,TILE_GRID_COL*TILE_GRID_ROW��С
	//Ԥ��ȡ�����жϸü�����Щ���ݵ�
	RECT				m_rcPreReadGrid;

	//�����жϲ��ھ��ӿ��ڵ����
	RECT				m_rcOldViewGrid;

	//���Լ����ڵĸ�������(m_ptPlayerGrid)Ϊ����,OBJECT_GRID_COL*OBJECT_GRID_ROW��С
	//��Ұ������Ҫ����Ϊ���ж�����Ƿ�ɼ�
	RECT				m_rcViewGrid;

	IEyeshotCallback*	m_pScrollSheetSink;
	bool				m_bDynamic;
	bool				m_bFirstTimeLoad;
public:
	SceneGrid();
	~SceneGrid() {}

	bool create(IEyeshotCallback* pSink, int nMapWidth, int nMapHeight, 
		POINT& ptPlayerPos,bool bDynamic);
	void close();

	bool scrollViewport(int dx, int dy);
	bool viewportSizeChanged(int nWidth, int nHeight);
	bool scroll2Center(POINT& ptPlayerPos);

	void getGridRectBelowViewport(RECT& rcCoveredRect);
	void getGridRectBelowPreRead(RECT& rcCoveredRect);
	RECT& getPreReadGrid()			{return m_rcPreReadGrid;}
	RECT& getViewGrid()				{return m_rcViewGrid;}
	RECT& getMapGrid()				{return m_rcMapGrid;}
	POINT getPlayerGrid()			{return m_ptPlayerGrid;}
	bool	isDynamic()				{return m_bDynamic;}
	bool	isFirstTimeLoad()		{return m_bFirstTimeLoad;}
	
	void snapshotLeftTop(int& nRows, int& nCols, BlockInfo* pBlockInfo, int nMoveDirection);
	int getBlockIndex(POINT& ptLeftTop);


private:
	void setPreReadTileRect(RECT rc);
	void closePreReadTileRect();
	void setViewTileRect(RECT rc);
	void closeViewTileRect();
	int  getMoveDirection(POINT& ptFrom, POINT& ptTo, int& nDx, int& nDy);
	void limitRect(RECT& rcSmall, const RECT& rcBig);
	void resetPlayerRect();
};

#endif // __GRIDMGR_H__

