#ifndef __RenderTargetManagerD3D9_H__
#define __RenderTargetManagerD3D9_H__

/*
�л���ȾĿ��ʱ��Ҫ�趨m_pcsBeginEndPrimitiveProxy�ĵ�ǰ����
*/

namespace xs
{

	class RenderTargetD3D9;
	class RenderSystemD3D9;
	class RenderTargetManagerD3D9;

	class RenderTargetManagerD3D9Creater
	{
	public:
		static RenderTargetManagerD3D9 * create(RenderSystemD3D9 * pRenderSystem);
	};

	class RenderTargetManagerD3D9
	{
	public:

		/**���Overlay RenderTarget��ֻ�����һ��
		*/
		bool addOverlayRenderTarget();

		/**ɾ��Overlay RenderTarget
		*/
		void removeOverlayRenderTarget();

		/** ����overlay render target Ϊ��ǰ��ȾĿ��
		*/
		bool setOverlayRenderTarget();


		/**�����Ⱦ�����ڵ���ȾĿ��
		@param hwnd ��Ⱦ���ھ��
		*/
		bool addRenderTarget(uint hwnd);


		/**�����Ⱦ���������ȾĿ��
		@param width ���
		@param height �߶�
		@param alpha ��ȾĿ���Ƿ���alphaͨ��
		@param min ��С�˲���
		@param mag ����˲���
		@param mip mipmap�˲���ʽ
		@param s ����sѰַ��ʽ
		@param t ����tѰַ��ʽ
		@return ���ɵ�RTT�ľ��
		*/
		uint addRTT(
			int width,
			int height, 
			bool alpha = false,
			FilterOptions min = FO_LINEAR, 
			FilterOptions mag = FO_LINEAR, 
			FilterOptions mip = FO_NONE,
			TextureAddressingMode s = TAM_WRAP,											
			TextureAddressingMode t = TAM_WRAP);

		/**ɾ����ȾĿ��
		@param hwnd ���ھ��
		@return �Ƿ�ɹ�
		*/
		bool removeRenderTarget(uint hwnd);


		/**���߳����RenderTarget,���߳������ȾĿ��ֻ�������첽����
		@param hwnd ���ھ��
		@return �Ƿ�ɹ�
		*/
		uint MTaddRenderTarget();

		/**���߳�ɾ����ȾĿ��,���߳������ȾĿ��ֻ�������첽����
		@param hwnd ���ھ��
		@return �Ƿ�ɹ�
		*/
		bool MTremoveRenderTarget(uint key);

		/**���õ�ǰ����ȾĿ��
		@param hwnd ���ھ������RTT���
		@return �Ƿ�ɹ�
		*/
		bool setCurrentRenderTarget(uint hwnd);

		/**��õ�ǰ����ȾĿ��id
		@return ��ǰ����ȾĿ��Ĵ��ھ����������RTT�ľ��
		*/
		uint getCurrentRenderTargetID();
		
		/**��õ�ǰ����ȾĿ��
		@return ��ǰ����ȾĿ��Ĵ��ھ����������RTT�ľ��
		*/
		RenderTargetD3D9 * getCurrentRenderTarget() { return m_pCurrentRenderTarget; }

		/** ��ȡ��ȾĿ��
		@return ��ȾĿ��
		*/
		RenderTargetD3D9 * getRenderTarget(uint id);

	public:
		/**�ͷ���ȾĿ�������
		*/
		void release();

	public:
		/** �豸��ʧ�������豸����ǰ���ô˺����ͷ���Դ
		*/
		void onDeviceLost();


		/** �豸���ú���ô˺����ͷ���Դ
		*/
		void onDeviceReset();

	private:
		friend class RenderTargetManagerD3D9Creater;
		RenderTargetManagerD3D9();
		~RenderTargetManagerD3D9();
		bool create(RenderSystemD3D9 * pRenderSystem);

	private:
		RenderSystemD3D9 * m_pRenderSystem;//��Ⱦϵͳ
		typedef stdext::hash_map<uint, RenderTargetD3D9*> RenderTargetContainer;
		typedef RenderTargetContainer::iterator RenderTargetContainerIterator;
		RenderTargetContainer m_vRenderTargets;//��ȾĿ��
		uint m_currentRenderTargetID;//��ǰ��ȾĿ��id
		RenderTargetD3D9 * m_pCurrentRenderTarget;//��ǰ��ȾĿ��
		uint			   m_uiRTTID;//RTT��id
	};
}


#endif