#ifndef	__HardwareCursorManagerD3D9_H__
#define __HardwareCursorManagerD3D9_H__

#include "IHardwareCursorManager.h"

namespace xs
{

	class HardwareCursorManagerD3D9;
	class RenderSystemD3D9;

	class HardwareCursorManagerD3D9Creater
	{
	public:
		static HardwareCursorManagerD3D9 * create(RenderSystemD3D9 * pRenderSystem);
	};

	class	HardwareCursorManagerD3D9: public IHardwareCursorManager
	{
		//<<interface>>
	public:

		/************************************************************************/
		/* �����Ƿ���ʾ���
		@param show �Ƿ���ʾ���
		*/
		/************************************************************************/
		virtual void	showCursor( bool show);


		/************************************************************************/
		/*   ���ù���λ��  
		@param	x ��Ļ������
		@param	y ��Ļ������
		@param	updateImmediate �Ƿ������ػ���
		*/
		/************************************************************************/
		virtual	void	setCursorPosition( int x, int y, bool updateImmediate);	

		/************************************************************************/
		/* ��������ȵ�                                                         */
		/************************************************************************/
		virtual void	setCursorHotspot(uint x, uint y);

		/************************************************************************/
		/* �������ͼƬ
		@param pTexture ���ͼƬ��Ҫ�ͷ�pTexure����ȡ��ͼƬ����
		*/
		/************************************************************************/
		virtual void	setCursorImage(ITexture* pTexture);

		/************************************************************************/
		/*�����Ƿ����                                                         */
		/************************************************************************/
		virtual bool	isAvailable();

		
		//�����豸��ʧ
	public:
		void notifyOnDeviceLost();
		void notifyOnDeviceReset();

	private:
		void setCursorProperties();
		void setDefaultCursor();

	public:
		HardwareCursorManagerD3D9();
		~HardwareCursorManagerD3D9(){};
		bool	create(RenderSystemD3D9 * pRenderSystem);
		void	release();

	private:
		RenderSystemD3D9 * m_pRenderSystem;
		IDirect3DDevice9 * m_pD3D9device;

		ITexture*		m_pCurTexture;//��ǰ���
		uint			m_uiXHotspot;//x�����ȵ�
		uint			m_uiYHotspot;//y�����ȵ�
		ITexture*		m_pDefaultTexture;//Ĭ�Ϲ��
	};
}

#endif