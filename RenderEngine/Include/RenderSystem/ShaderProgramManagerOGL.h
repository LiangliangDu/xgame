#ifndef __ShaderProgramManagerOGL_H__
#define __ShaderProgramManagerOGL_H__

namespace xs
{
	class ShaderManager;
	class HighLevelShaderManager;

	class ShaderProgramManagerOGL: public IShaderProgramManager
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
		void	onShaderProgramBinded(IShaderProgram * pProgram);
		void	onShaderProgramUnbinded(IShaderProgram * pProgram);
		ShaderManager*			getLowLevelShaderManager();
		HighLevelShaderManager*	getHighLevelShaderManager();

	public:
		static ShaderProgramManagerOGL*	Instance()
		{
			static ShaderProgramManagerOGL spm;
			return &spm;
		}
	protected:
		ShaderProgramManagerOGL():m_pCurrentShaderProgram(0) {};

	private:
		IShaderProgram * m_pCurrentShaderProgram;
	};

}
#endif