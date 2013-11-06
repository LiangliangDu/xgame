#ifndef __GroundTile_H__
#define __GroundTile_H__

#include "ISceneManager2.h"

class GroundEyeshot;

struct GroundTileResource
{
	GroundTileResource()
	{
		m_pTextures[0] = 0;
		m_pTextures[1] = 0;
		m_pTextures[2] = 0;
		m_pTextures[3] = 0;
		m_pAlphaMaps[0] = 0;
		m_pAlphaMaps[1] = 0;
		m_pAlphaMaps[2] = 0;
		m_pShaderMap = 0;
	}

	ITexture*	m_pTextures[4];
	ITexture*	m_pAlphaMaps[3];
	ITexture*	m_pShaderMap;
};

class GroundTile : public IGroundTile
{
	friend class GroundRenderQueue;
public:
	/**��õ�index����ͼ
	@param index ��(0-3)
	@return ��ͼָ��
	*/
	virtual ITexture*	getTexture(uint index);

	/**��õ�index����ͼ���ļ���
	@param index ��
	@return ��ͼ�ļ���
	*/
	virtual const char*		getTextureFileName(uint index);

	/**���õ�index�����ͼ�ļ���
	@param index ��
	@param szFileName ��ͼ�ļ���
	@param bLoad2GPU �Ƿ�����������ͼ
	*/
	virtual void		setTextureFileName(uint index,const char* szFileName,bool bLoad2GPU);

	/**��õ�index��Alpha��ͼ����
	@param index ��(0-2)
	@return ��ͼ����
	*/
	virtual	uchar*		getAlphaMap(uint index);

	/**����Alpha��ͼ
	@param index ��
	*/
	virtual void		updateAlphaMap(uint index);

	/**�����Ӱ��ͼ������
	@return ��ͼ����
	*/
	virtual uchar*		getShadowMap();

	/**������Ӱ��ͼ����
	*/
	virtual void		updateShadowMap();

	/**�����ͼ�Ĳ���
	@return ��ͼ����
	*/
	virtual uint		getTextureLayerNum();

	/**������ͼ�Ĳ���
	@param num ����(0-4)
	*/
	virtual void		setTextureLayerNum(uint num);

	/**ȡ�ð�Χ��
	@return ��Χ��
	*/
	virtual RECT		getRect(); // ��ȡ�ر����Ե�ͼ����������

	/**ȡ�õر��X�±�
	@param x X�±�
	*/
	virtual int			getX(); // ��ȡ�ر���Ӧ�Ĺ������ֵ

	/**ȡ�õر��Y�±�
	@param y Y�±�
	*/
	virtual int			getY();	// ��ȡ�ر���Ӧ�Ĺ������ֵ

public:
	GroundTile();
	~GroundTile();

	const Matrix4& getWorldMatrix();
	void loadAlphaMaps(xs::Stream* pStream);
	void setResHandle(handle h)
	{
		m_handle = h;
		if(isValidHandle(h))
		{
			//Info("ooo handle = "<<(ulong)m_handle<<endl);
		}
		else
		{
			//Info("xxx handle = "<<(ulong)m_handle<<endl);
		}
	}
	handle getResHandle(){return m_handle;}
	GroundTileResource *getResource();
	ITexture*	getShaderMapTexture();
	ITexture*	getAlphaMapTexture(uint index);

private:
	uint		m_textureLayerNum;
	std::string	m_textureLayerFileName[4];
	uchar*		m_alphaMap[3];
	uchar*		m_shadowMap;
	bool		m_bLoaded;
	Matrix4		m_mtxWorld;
	handle		m_handle;
	bool		m_bAlphaMapLoaded;
	bool		m_basicInfoLoad;

private:
	IRenderSystem*	m_pRenderSystem;

public:
	GroundEyeshot*	m_pGround;
	POINT		m_ptCoord;	//�ر�����꣬ÿ������512*512

private:
	void _draw(const RECT& rect);
	void _updateAlphaMap(uint index,bool updateShaderMap = true);

public:
	bool isLoaded();
	void setLoaded(bool bLoaded){m_bLoaded = bLoaded;}
	void loadBasicInfo(xs::Stream *pMapStream,std::vector<std::string>& vTextures);
	void load(xs::Stream *pMapStream);
	void save(xs::Stream *pDataStream,stdext::hash_map<std::string,int>& mTextures);
};

#endif