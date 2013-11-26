#ifndef __ShaderProgram_H__
#define __ShaderProgram_H__

namespace xs
{
	class ShaderManager;
	class ShaderProgramManagerOGL;

	class ShaderProgram : public ILowLevelShaderProgram
	{
	public:
		/** �ͷ���ɫ������
		*/
		virtual void 			release();

		/** �󶨵�����ɫ������
		@return �Ƿ�ɹ�
		*/
		virtual bool			bind();	

		/** ȡ���󶨵�����ɫ��
		*/
		virtual void 			unbind();

		/** ���ļ��������ɫ��
		@param ShaderType ��ɫ������
		@param fn �ļ���
		@return ��ɫ���ӿ�ָ��
		*/
		virtual bool			addShaderFromFile(ShaderType st,const std::string& fn);	

		/** ���ڴ������������ɫ��
		@param ShaderType ��ɫ������
		@param pBuffer ���ݵ�ַ
		@param len ���ݳ���
		@return ��ɫ���ӿ�ָ��
		@see ShaderType
		*/
		virtual bool		addShaderFromMemory(ShaderType st,const uchar *pBuffer,uint len);

		/** ���������ɫ������
		@return �Ƿ�ɹ�
		*/
		virtual bool			link();

		/** ��ȡ��ɫ����������
		*/
		virtual ShaderProgramType getProgramType();

		/** ����ͳһ������ά����
		@param startRegister	��ʼ�ĸ��㳣���Ĵ������
		@param pData			��������ָ��
		@param countVector4		��ά���������ĸ���
		*/
		virtual	bool		setUniformFloatVector4(uint startRegister, float * pData, uint countVector4);

		/** ����ͳһ������ά����
		@param startRegister	��ʼ�����ͳ����Ĵ������
		@param pData			��������ָ��
		@param countVector4		��ά���������ĸ���
		*/
		virtual	bool		setUniformIntVector4(uint startRegister, int * pData, uint countVector4);

		/** ����ͳһ��������
		@param startRegister	��ʼ�Ĳ��������Ĵ������
		@param pData			��������ָ�룬0��ʾfalse����0��ʾtrue
		@param countBool		�������ݵĸ���
		*/
		virtual	bool		setUniformBool(uint startRegister, int * pData, uint countBool);


		/** �����磬�������ͶӰ�Ⱦ���󶨵�shader�ĳ���,�ʺϵ�shader��ֻ��ͬʱ��һ������
		*/
		virtual void			bindTransformMatrix(uint index, uint type, uint bindRow=4);

	public:
		ShaderProgram(ShaderProgramManagerOGL* pProgramMgr, ShaderManager * pShaderMgr):m_pShaderManager(pShaderMgr),
			m_pShaderProgramManager(pProgramMgr) {};
		~ShaderProgram(){};

	private:
		typedef std::vector<IShader *>		ShaderContainer;
		typedef ShaderContainer::iterator	ShaderContainerIterator;
		ShaderContainer						m_vShaders;
		ShaderManager*						m_pShaderManager;
		ShaderProgramManagerOGL*			m_pShaderProgramManager;
	};
}

#endif