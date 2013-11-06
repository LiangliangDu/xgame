#ifndef __GroundEyeshot_H__
#define __GroundEyeshot_H__

#include "GroundTile.h"
#include "Eyeshot.h"
#include "SceneCoord.h"
#include "GroundRenderQueue.h"

class SceneMgr;
class ResourceLoaderGT;

class GroundEyeshot : public IEyeshotCallback,public IGround
{
public:
	/**������������ȡ�õر��
	@param ptWorld ��������
	@return �ر��ָ��
	*/
	virtual IGroundTile*	getGroundTile(const POINT& ptWorld);

	/**�����±�ȡ�õر��
	@param x �ر��X�±�
	@param y �ر��Y�±�
	@return �ر��ָ��
	*/
	virtual IGroundTile*	getGroundTile(int x,int y);

	/**����Ĭ����ͼ(��û����ͼ��ʱ��)
	@param szFileName ��ͼ�ļ���
	*/
	virtual void			setDefaultTexture(const char* szFileName);

	/**ȡ��Ĭ����ͼ��ָ��
	@return ��ͼָ��
	*/
	virtual ITexture*		getDefaultTexture();

	/**ȡ���ӿ��ڵر��е�X,Y����
	@return ����
	*/
	virtual POINT			getViewLeftTop();

	/**ȡ�õر��Ŀ��
	@return �ر����
	*/
	virtual int				getGroundTileWidth();

	/**ȡ�õر��ĸ߶�
	@return �ر��߶�
	*/
	virtual int				getGroundTileHeight();

	/**ȡ���ܹ��ĺ���ر������
	@return �ر������
	*/
	virtual int				getTotalTileX();

	/**ȡ���ܹ�������ر������
	@return �ر������
	*/
	virtual int				getTotalTileY();

	/**�����Ƿ���Ƶر��ı߿�
	@param bDraw �Ƿ����
	*/
	virtual void			setDrawTileLine(bool bDraw);

	/**ȡ���Ƿ���Ƶر��ı߿�
	@return �Ƿ����
	*/
	virtual bool			isDrawTileLine();

	/**ʹ����ͼ������������ͼ
	@param szFilename ��ͼ�ļ���
	@return �Ƿ�ɹ�
	@remarks ���ڵ�ͼ�༭��
	*/
	virtual bool			fillMap(const char* szFilename);

	/**ĳ���ر�����Դʱ���Ѿ�����
	@param x �ر������X
	@param y �ر������Y
	@return �Ƿ����
	*/
	virtual bool			_isLoaded(int x,int y);

	/**����ĳ���ر�����Դ
	@param x �ر������X
	@param y �ر������Y
	@remarks ���ڵ�ͼ�༭��
	*/
	virtual void			_load(int x,int y);

	/**ж��ĳ���ĵر�����Դ
	@param x �ر������X
	@param y �ر������Y
	@remarks ���ڵ�ͼ�༭��
	*/
	virtual void			_unload(int x,int y);

    //  ����Զ����ͼ��
    //  @param szFileName ��ͼ�ļ�����
    virtual void SetDistanceTexture(const char* szFileName);

    //  ȡ��Զ����ͼ��ָ�룻
    //  @return ��ͼָ�룻
    virtual ITexture* GetDistanceTexture();

	int m_nMapWidth;
	int m_nMapHeight;
	RECT m_rcMapRect;
	
	int m_nViewWidth;
	int m_nViewHeight;
	
	int m_nGridWidth;
	int m_nGridHeight;
	
	int	m_nTotalGridX;
	int	m_nTotalGridY;

	RECT m_rcViewportRect;
	RECT m_rcViewportTileRect;
	
	SceneCoord	m_SceneCo;
	Eyeshot	m_Eyeshot;
	std::string	m_defaultTexture;
	ITexture*	m_pDefaultTexture;
	bool	m_bDrawTileLine;
	SceneMgr*	m_pSceneMgr;
	xs::Stream*	m_pMapStream;
	std::vector<std::string>	m_vTextures;
	DWORD*		m_pGroundTileTable;

    //  Զ����ͼ��
    std::string	m_strDistanceTextureFileName;
    ITexture* m_pDistanceTexture;

	GroundRenderQueue		m_groundRenderQueue;

	// ����ģʽ
    int    m_RunType;
public:
	void drawTileLine();
	void pixel2Tile(const POINT &ptScreen, POINT &ptTile) const;
	void pixelToViewTop(const POINT &ptTile, POINT &ptTileCenter) const;
	void tile2Pixel(const POINT &ptTile, POINT &ptTileCenter) const;
	void scrollViewport(int dx, int dy);
	void onDraw(bool bWholeGround);

	void save(xs::DataChunk *pDataChunk);
	void load(xs::Stream* pMapFile);


	const RECT& getViewportRect() const
	{
		return m_rcViewportRect;
	}
	const RECT& getViewportTileRect() const
	{
		return m_rcViewportTileRect;
	}
	const SceneCoord& getSceneCoord() const
	{
		return m_SceneCo;
	}

	int getSceneWidth() const
	{
		return m_nMapWidth;
	}
	int getSceneHeight() const
	{
		return m_nMapHeight;
	}

	const RECT& getMapRect() const
	{
		return m_rcMapRect;
	}

	int getViewTopX() const
	{
		return m_Eyeshot.getViewTopX();
	}

	int getViewTopY() const
	{
		return m_Eyeshot.getViewTopY();
	}

	int getViewWidth() const
	{
		return m_nViewWidth;
	}
	int getViewHeight() const
	{
		return m_nViewHeight;
	}
	// ȡ�õ�ǰ����ģʽ
	int  getRunType() const
	{
		return m_RunType;
	}
	void  setRunType(int runType) 
	{
		 m_RunType = runType;
	}
	void close();
	bool create(SceneMgr *pSceneMgr,int nMapWidth,int nMapHeight,int nGridWidth,int nGridHeight,LPRECT lprcViewport,xs::IResourceManager *pResourceManager,xs::Stream *pMapFile,const std::string& mapFilename,bool bDynamic);
	bool moveViewportTo(int x,int y);
	bool viewportSizeChanged(int nWidth,int nHeight);

	GroundEyeshot()
	{
		m_nMapWidth = 0;
		m_nMapHeight = 0;
		m_nViewWidth = 0;
		m_nViewHeight = 0;

		m_nTotalGridX = 0;
		m_nTotalGridY = 0;

		m_nGridHeight = 256;
		m_nGridWidth = 256;

		m_pGroundTile = 0;
		m_pDefaultTexture = 0;

		memset(&m_rcViewportTileRect,0,sizeof(m_rcViewportTileRect));
		memset(&m_rcMapRect,0,sizeof(m_rcMapRect));

		m_bDrawTileLine = false;
		m_pSceneMgr = 0;
		m_pMapStream = 0;
		m_pGroundTileTable = 0;

		m_pResourceManager = 0;

		m_hash = 0;

		m_ResourceLoader = 0;

        m_strDistanceTextureFileName.clear();
        m_pDistanceTexture = NULL;
		m_RunType = 0;
		m_bFirstEnterArea =false;
	}

	~GroundEyeshot()
	{
		close();
	}

private:
	virtual void onChanged(int nMoveDirection, int nDx, int nDy){}
	virtual void onFound(int nGridX,int nGridY);
	virtual void onLost(int nGridX,int nGridY);

	GroundTile*		m_pGroundTile;
	xs::IResourceManager*	m_pResourceManager;
	ulong	m_hash;
	ResourceLoaderGT*		m_ResourceLoader;

	bool	m_bDynamic;

	//add by yhc����ֹ��ͼ����ʱ����ֻ���,�ڴ�����ʱ��ʹ��ͬ������
	//�Ƿ��Ǹս��������
	bool m_bFirstEnterArea;
protected:
	void calcViewTileRect();
	void getNameList(std::vector<std::string> &v,char *pFileNames,uint size);
	void _drawTile(int i,int j);
};

#endif
