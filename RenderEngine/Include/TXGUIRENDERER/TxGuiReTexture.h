#ifndef __TxGuiReTexture_H__
#define __TxGuiReTexture_H__

#include "TxGuiReRenderer.h"
namespace xs
{


class TxGuiRendererAPI TxGuiTexture : public xsgui::Texture
{
public:
	TxGuiTexture(xsgui::Renderer* pRenderer,IRenderSystem *pRenderSystem);
	TxGuiTexture(xsgui::Renderer* pRenderer,IRenderSystem *pRenderSystem,uint size,xsgui::Texture::PixelFormat pf, bool createNoWait);
	virtual ~TxGuiTexture();
public:
	/// �������ĵ�ǰ���ؿ��
	virtual	ushort getWidth() const;


	/// �������ĵ�ǰ���ظ߶�
	virtual	ushort getHeight() const;


	/** ���ļ�����ͼ���������
	@param filename �ļ���
	*/
	virtual bool loadFromFile(const xsgui::String& filename, const xsgui::String& resourceGroup);


	/** ���ڴ����ͼ���������
	@param buffPtr ͼ������ָ��
	@param width ͼ��Ŀ��
	@param height ͼ��ĸ߶�
	*/
	virtual bool loadFromMemory(const void* buffPtr, uint width, uint height,xsgui::Texture::PixelFormat pixelFormat);

	/** ������ͼ��������,���ظ�ʽ��Ҫ�û��Լ���֤����
	@param level Ҫ�������ݵ�ͼ��Mipmaps�ȼ�,��0��ʼ
	@param left ��߿�ʼ�±�
	@param top �ϱ߿�ʼ�±�
	@param width ���
	@param height �߶�
	@param pData ���õ���ͼ����
	@return true��ʾ�����ɹ���false��ʾʧ��
	*/
	virtual bool			setSubData(uint level,uint left,uint top,uint width,uint height,void  *pData);
public:
	void	destroyTexture();

	ITexture*		m_pTexture;
	IRenderSystem*	m_pRenderSystem;
};

}
#endif