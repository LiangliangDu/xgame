#ifndef __MinimapTile_H__
#define __MinimapTile_H__

class MinimapEyeshot;

class MinimapTile
{
public:
	MinimapTile();
	~MinimapTile();

	void setResHandle(handle h)
	{
		m_handle = h;
	}
	handle getResHandle()
	{
		return m_handle;
	}
	ITexture* loadResource();
	ITexture* getTexture();

private:
	handle		m_handle;

public:
	xs::Point		m_ptCoord;	//�ڵ�ͼ�ϵ�MinimapTile����
	MinimapEyeshot*	m_pParent;
};

#endif