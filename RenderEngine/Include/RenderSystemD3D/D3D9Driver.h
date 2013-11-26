#ifndef __D3D9Driver_H__
#define __D3D9Driver_H__


namespace xs
{
	class D3D9Driver;
	class RenderSystemD3D9;

	struct D3D9DriverCreater
	{
		static D3D9Driver * create(RenderSystemD3D9 * pRenderSystem, uint uiAdapterOrdinal);//����d3d9 �����������
	};


	class D3D9Driver
	{
	public:
		inline const D3DADAPTER_IDENTIFIER9 & getIdentifier() { return m_AdapterIdentifier; } ;
		const D3DDISPLAYMODE & getCurrentDisplayMode()  { return m_DesktopDisplayMode;};
		void  release();
		inline uint getAdapterOrdinal() { return m_uiAdapterOrdinal;} 
		bool  getDisplayMode(UINT width, UINT height, D3DFORMAT format, D3DDISPLAYMODE & mode);

	public://�����豸��ʧ
		void	onDeviceLost();
		void	onDeviceReset();
	private:
		void enumerateDisplayMode();

	private:
		friend struct D3D9DriverCreater;
		bool create(RenderSystemD3D9 * pRenderSystem,uint uiAdapterOrdinal);
		D3D9Driver();
		D3DADAPTER_IDENTIFIER9	m_AdapterIdentifier;// �Կ���ʶ	
		D3DDISPLAYMODE			m_DesktopDisplayMode;//������ʾģʽ	
		uint m_uiAdapterOrdinal;						//�Կ����
		RenderSystemD3D9 *		m_pRenderSystem;//��Ⱦϵͳ
		std::vector<D3DDISPLAYMODE> m_displayModeList;//��ʾģʽ�б�
	};
}


#endif