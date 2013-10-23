#include "TxGuiReTexture.h"
#include "stringhelper\StringConv.h"
namespace xs
{


TxGuiTexture::TxGuiTexture(xsgui::Renderer* pRenderer,IRenderSystem *pRenderSystem) 
	: m_pRenderSystem(pRenderSystem),
	Texture(pRenderer)
{
	//m_pTexture = m_pRenderSystem->getTextureManager()->createEmptyTexture(FO_LINEAR,FO_LINEAR,FO_NONE,TAM_CLAMP,TAM_CLAMP);
	//by yhc uiͼƬģ�������Բ�ֵ���µ�
	m_pTexture = m_pRenderSystem->getTextureManager()->createEmptyTexture(FO_POINT,FO_POINT,FO_NONE,TAM_CLAMP,TAM_CLAMP);
}

TxGuiTexture::TxGuiTexture(xsgui::Renderer* pRenderer,IRenderSystem *pRenderSystem,uint size,xsgui::Texture::PixelFormat pf, bool createNoWait)
	: m_pRenderSystem(pRenderSystem),
	Texture(pRenderer)
{
	if( createNoWait)
	{
		switch( pf )
		{
		case xsgui::Texture::PF_RGBA:
			m_pTexture = m_pRenderSystem->getTextureManager()->createEmptyTextureNoWait(size,size,PF_R8G8B8A8,FO_POINT,FO_POINT);
			return;
		case xsgui::Texture::PF_BGR:
			m_pTexture = m_pRenderSystem->getTextureManager()->createEmptyTextureNoWait(size,size,PF_B8G8R8,FO_POINT,FO_POINT);
			return;
		case xsgui::Texture::PF_ARGB:
			//����gdi bitmap�ĸ�ʽ,����ѭ��ÿ�����ؽ���ת��
			m_pTexture = m_pRenderSystem->getTextureManager()->createEmptyTextureNoWait(size,size,PF_A8R8G8B8,FO_POINT,FO_POINT);
			return;
		default:// never get here
			m_pTexture = 0;
			return;
		}
	}
	else
	{
		switch( pf )
		{
		case xsgui::Texture::PF_RGBA:
			m_pTexture = m_pRenderSystem->getTextureManager()->createEmptyTexture(size,size,PF_R8G8B8A8,FO_POINT,FO_POINT);
			return;
		case xsgui::Texture::PF_BGR:
			m_pTexture = m_pRenderSystem->getTextureManager()->createEmptyTexture(size,size,PF_B8G8R8,FO_POINT,FO_POINT);
			return;
		case xsgui::Texture::PF_ARGB:
			//����gdi bitmap�ĸ�ʽ,����ѭ��ÿ�����ؽ���ת��
			m_pTexture = m_pRenderSystem->getTextureManager()->createEmptyTexture(size,size,PF_A8R8G8B8,FO_POINT,FO_POINT);
			return;
		default:// never get here
			m_pTexture = 0;
			return;
		}
	}
}

TxGuiTexture::~TxGuiTexture()
{
	m_pRenderSystem->getTextureManager()->releaseTexture(m_pTexture);
}

/// �������ĵ�ǰ���ؿ��
ushort TxGuiTexture::getWidth() const
{
	return m_pTexture->width();
}


/// �������ĵ�ǰ���ظ߶�
ushort TxGuiTexture::getHeight() const
{
	return m_pTexture->height();
}

void	TxGuiTexture::destroyTexture()
{
	m_pRenderSystem->getTextureManager()->releaseTexture(m_pTexture);
	delete this;
}


/** ���ļ�����ͼ���������
@param filename �ļ���
*/
bool TxGuiTexture::loadFromFile(const xsgui::String& filename, const xsgui::String& resourceGroup)
{
	
	char *p = xsgui::StringConv::Utf8ToChar((char*)filename.c_str());
	bool ret = m_pTexture->loadFromFile(p);
	xsgui::StringConv::DeletePtr(p);

	return ret;
}


/** ���ڴ����ͼ���������
@param buffPtr ͼ������ָ��
@param width ͼ��Ŀ��
@param height ͼ��ĸ߶�
*/
bool TxGuiTexture::loadFromMemory(const void* buffPtr, uint width, uint height, xsgui::Texture::PixelFormat pixelFormat)
{
	bool ret = true;
	if(pixelFormat == xsgui::Texture::PF_RGBA)
		ret = m_pTexture->loadFromRawData((uchar*)buffPtr,width,height,PF_R8G8B8A8);
	else
		ret = m_pTexture->loadFromRawData((uchar*)buffPtr,width,height,PF_B8G8R8);

	return ret;
}
/** ������ͼ��������,���ظ�ʽ��Ҫ�û��Լ���֤����
@param level Ҫ�������ݵ�ͼ��Mipmaps�ȼ�,��0��ʼ
@param left ��߿�ʼ�±�
@param top �ϱ߿�ʼ�±�
@param width ���
@param height �߶�
@param pData ���õ���ͼ����
@return true��ʾ�����ɹ���false��ʾʧ��
*/
bool TxGuiTexture::setSubData(uint level,uint left,uint top,uint width,uint height,void  *pData)
{
	return m_pTexture->setSubData(level,left,top,width,height,pData);
}
}