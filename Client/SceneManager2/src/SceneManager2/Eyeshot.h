#ifndef __Eyeshot_H__
#define __Eyeshot_H__

struct IEyeshotCallback
{
	virtual void onChanged(int nMoveDirection, int nDx, int nDy) = 0;
	virtual void onFound(int nGridX,int nGridY) = 0;
	virtual void onLost(int nGridX,int nGridY) = 0;
};

//add by yhc
//Ŀǰ���ڹ����ر��ʱ���õ�
//��������ͼ���ֳ�256*256�ĸ���,�������ִ�8800*6600�Ĵ�С���ֳ�34*24���ر��
//�ƶ�ʱ�����¾��ͺ������,��Ҫ�Ľ��ж�������,�µĽ��з��ִ���

class Eyeshot
{
public:
	bool scroll2Center(const RECT& rcView);
	Eyeshot()
	{
		m_pScrollSheetSink = 0;

		m_nMapWidth = 0;
		m_nMapHeight = 0;
		m_nViewWidth = 0;
		m_nViewHeight = 0;
		m_nViewTopX = 0;
		m_nViewTopY = 0;

		m_nGridHeight = 0;
		m_nGridWidth = 0;

		memset(&m_rcCurViewGrid,0,sizeof(RECT));
		memset(&m_rcMapGrid,0,sizeof(RECT));
		memset(&m_rcLastDirty,0,sizeof(RECT));
		memset(&m_rcViewportRect,0,sizeof(RECT));
		memset(&m_rcMap,0,sizeof(RECT));
	}
	~Eyeshot()
	{
	
	}

	int getViewTopX() const
	{
		return m_nViewTopX;
	}

	int getViewTopY() const
	{
		return m_nViewTopY;
	}

	int getViewWidth() const
	{
		return m_nViewWidth;
	}
	int getViewHeight() const
	{
		return m_nViewHeight;
	}
	bool create(IEyeshotCallback* pSink,int nMapWidth,int nMapHeight,
		int nGridWidth,int nGridHeight,LPRECT lprcViewport,bool bDynamic);
	void close();
	bool moveViewportTo(int x,int y);
	bool scrollViewport(int dx,int dy);
	bool viewportSizeChanged(int nWidth,int nHeight);
	RECT getViewportRect()
	{
		return m_rcViewportRect;
	}

private:
	void setViewTileRect(RECT rc);
	void updateScrollSheet(const RECT& rcNew);

	IEyeshotCallback *m_pScrollSheetSink;

	int m_nMapWidth;
	int m_nMapHeight;

	int m_nViewWidth;
	int m_nViewHeight;
	int m_nViewTopX;
	int m_nViewTopY;
	RECT m_rcViewportRect;
	RECT m_rcMap;

	int m_nGridWidth;
	int m_nGridHeight;		
	
	RECT m_rcCurViewGrid;
	RECT m_rcMapGrid;
	RECT m_rcLastDirty;
};

#endif
