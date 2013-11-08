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
	xs::Rect				m_rcMapGrid;

	//�����ж��Լ����ڵĵ��ڲ������������,��ҵ��µ��Ƿ��¸��ӱ仯,�����ڵ�ͼ���ز������¸���
	xs::Rect				m_rcPlayerGrid;
	//�Լ����ڵĸ�������x,y
	xs::Point				m_ptPlayerGrid;

	//�¾ɷ�Χ�Աȿɵó��ƶ�����
	xs::Rect				m_rcOldPreReadGrid;
	//���Լ����ڵĸ�������(m_ptPlayerGrid)Ϊ����,TILE_GRID_COL*TILE_GRID_ROW��С
	//Ԥ��ȡ�����жϸü�����Щ���ݵ�
	xs::Rect				m_rcPreReadGrid;

	//�����жϲ��ھ��ӿ��ڵ����
	xs::Rect				m_rcOldViewGrid;

	//���Լ����ڵĸ�������(m_ptPlayerGrid)Ϊ����,OBJECT_GRID_COL*OBJECT_GRID_ROW��С
	//��Ұ������Ҫ����Ϊ���ж�����Ƿ�ɼ�
	xs::Rect				m_rcViewGrid;

	IEyeshotCallback*	m_pScrollSheetSink;
	bool				m_bDynamic;
	bool				m_bFirstTimeLoad;
public:
	SceneGrid();
	~SceneGrid() {}

	bool create(IEyeshotCallback* pSink, int nMapWidth, int nMapHeight, 
		xs::Point& ptPlayerPos,bool bDynamic);
	void close();

	bool scrollViewport(int dx, int dy);
	bool viewportSizeChanged(int nWidth, int nHeight);
	bool scroll2Center(xs::Point& ptPlayerPos);

	void getGridRectBelowViewport(xs::Rect& rcCoveredRect);
	void getGridRectBelowPreRead(xs::Rect& rcCoveredRect);
	xs::Rect& getPreReadGrid()			{return m_rcPreReadGrid;}
	xs::Rect& getViewGrid()				{return m_rcViewGrid;}
	xs::Rect& getMapGrid()				{return m_rcMapGrid;}
	xs::Point getPlayerGrid()			{return m_ptPlayerGrid;}
	bool	isDynamic()				{return m_bDynamic;}
	bool	isFirstTimeLoad()		{return m_bFirstTimeLoad;}
	
	void snapshotLeftTop(int& nRows, int& nCols, BlockInfo* pBlockInfo, int nMoveDirection);
	int getBlockIndex(xs::Point& ptLeftTop);


private:
	void setPreReadTileRect(xs::Rect rc);
	void closePreReadTileRect();
	void setViewTileRect(xs::Rect rc);
	void closeViewTileRect();
	int  getMoveDirection(xs::Point& ptFrom, xs::Point& ptTo, int& nDx, int& nDy);
	void limitRect(xs::Rect& rcSmall, const xs::Rect& rcBig);
	void resetPlayerRect();
};

#endif // __GRIDMGR_H__

