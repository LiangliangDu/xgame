#ifndef __ShaderProgramManagerD3D9_H__
#define __ShaderProgramManagerD3D9_H__

namespace xs
{
	class ShaderProgramManagerD3D9;
	class ShaderManagerD3D9;
	class ShaderManagerHLSLD3D9;
	class RenderSystemD3D9;

	class ShaderProgramManagerD3D9Creater
	{
	public:
		static ShaderProgramManagerD3D9* create(RenderSystemD3D9* pRenderSystem);
	};

	class ShaderProgramManagerD3D9: public IShaderProgramManager
	{
		//<<IShaderProgramManager>>
	public:

		/** ������ɫ������
		@return ��ɫ������ӿ�ָ��
		*/
		virtual IShaderProgram*		createShaderProgram(ShaderProgramType type);

		/**	 ��ȡ����������Ⱦ����ɫ������
		@return ��ɫ������ӿ�ָ��
		*/
		virtual IShaderProgram*		getCurrentShaderProgam();

		/** �ͷ��Լ�
		*/
		virtual void			release();

	public:
		void onShaderProgramBinded(IShaderProgram * pProgram);
		void onShaderProgramUnbinded(IShaderProgram * pProgram);
		IShaderManager* getLowLevelShaderManager();
		IShaderManager* getHighLevelShaderManager();

	private:
		friend class ShaderProgramManagerD3D9Creater;
		ShaderProgramManagerD3D9();
		bool create(RenderSystemD3D9 * pRenderSystem);
		~ShaderProgramManagerD3D9();

	private:
		ShaderManagerD3D9*	m_pLowLevelShaderMgr;
		ShaderManagerHLSLD3D9* m_pHighLevelShaderMgr;
		IShaderProgram* m_pCurrentShaderProgram;
	};

}

#endif