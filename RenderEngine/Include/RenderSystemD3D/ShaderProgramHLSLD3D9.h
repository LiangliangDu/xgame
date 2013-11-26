#ifndef __ShaderProgramHLSLD3D9_H__
#define __ShaderProgramHLSLD3D9_H__

namespace xs
{
	class ShaderFragmentHLSLD3D9;
	class ShaderProgramManagerD3D9;
	class ShaderManagerHLSLD3D9;

	class ShaderProgramHLSLD3D9 : public IHighLevelShaderProgram
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

		/** ����ͳһ�����ͱ���
		@param	strPara ������
		@param	value   ����ֵ
		@return	�Ƿ����óɹ�
		*/
		virtual bool			setUniformBool(const std::string & strPara,  int value);

		/** ����ͳһ���ͱ���
		@param	strPara ������
		@param	value	����ֵ
		@return	�Ƿ����óɹ�
		*/
		virtual bool			setUniformInt(const std::string & strPara, int value);

		/** ����ͳ�����ͱ���
		@param	strPara ������
		@param	value	����ֵ
		@return	�Ƿ����óɹ�
		*/
		virtual bool			setUniformFloat(const std::string & strPara, float value);

		/** ����ͳһ��������
		@param	strPara ������
		@param	value	����ֵ
		@return	�Ƿ����óɹ�
		*/
		virtual bool			setUniformVector4(const std::string & strPara, const Vector4 & value);

		/** ����һ��ľ���
		@param	strPara ������
		@param	value	����ֵ����������ݣ����������
		@return			�Ƿ����óɹ�
		*/
		virtual bool			setUniformMatrix(const std::string & strPara, const Matrix4 &  value,bool normal = true);


		/** ����ͳһ����������
		@param	strPara ������
		@param	count	�����С
		@param	pValue  �����ַ
		@return	�Ƿ����óɹ�
		*/
		virtual bool			setUniformBoolArray(const std::string & strPara, uint count,  int * pValue);

		/** ����ͳһ��������
		@param	strPara ������
		@param	count	�����С
		@param	pValue  �����ַ
		@return	�Ƿ����óɹ�
		*/
		virtual bool			setUniformIntArray(const std::string & strPara, uint count,  int * pValue);

		/** ����ͳһ����������
		@param	strPara ������
		@param	count	�����С
		@param	pValue  �����ַ
		@return	�Ƿ����óɹ�
		*/
		virtual bool			setUniformFloatArray(const std::string & strPara, uint count,  float * pValue);

		/** ����ͳһ����������
		@param	strPara ������
		@param	count	�����С
		@param	pValue  �����ַ
		@return	�Ƿ����óɹ�
		*/
		virtual bool			setUniformVector4Array(const std::string & strPara, uint count,  xs::Vector4 * pValue);

		/** ����ͳһ����������
		@param	strPara ������
		@param	count	�����С
		@param	pValue  �����ַ
		@return	�Ƿ����óɹ�
		*/
		virtual bool			setUniformMatrixArray(const std::string & strPara, uint count,  xs::Matrix4 * pValue);


		////////////////////////////////////////////////////////////////////////////////////

		///** ����һ��ľ���
		//@param	strPara ������
		//@param	row ���������
		//@param	column ���������
		//@param	pData ��������ݣ����������
		//*/
		//virtual bool			setUniformMatrix(const std::string strPara,  const Matrix4 &  mtx);

		///** ����ͳһ���ͱ�����ֵ
		//@param strPara	��������
		//@param count	���ͱ����ĸ���
		//@param pData	������ֵ
		//*/
		//virtual bool 			setUniformIntArray(const std::string& strPara, uint count, int * pData );

		///** ����ͳһ����������ֵ
		//@param strPara	��������
		//@param count	���������ĸ���
		//@param pData	������ֵ
		//*/
		//virtual bool 			setUniformBoolArray(const std::string& strPara,uint count, bool * pData );

		///** ����ͳһ���������ֵ
		//@param strPara ��������
		//@param count	��������ĸ���
		//@param pData ������ֵ
		//*/
		//virtual bool 			setUniformFloatArray(const std::string& strPara,uint count, float * pData );

		///** ����ͳһ�������
		//@param strPara	��������
		//@param count	��������ĸ���
		//@param pData	������ֵ
		//*/
		//virtual bool 			setUniformMatrixArray(const std::string& strPara,uint count, xs::Matrix4 * pData );


		/** ���������󶨵�shader�ĳ���
		*/
		virtual void			bindSampler( uint smaplerNum );

		/** �����磬�������ͶӰ����󶨵�shader�ĳ���
		*/
		virtual void			bindTransformMatrix( uint flag );


	public:
		ShaderProgramHLSLD3D9(ShaderProgramManagerD3D9 * pProgramMgr, ShaderManagerHLSLD3D9 * pShaderMgr);
	private:
		~ShaderProgramHLSLD3D9() {};

	private:
		ShaderFragmentHLSLD3D9 *	m_pVertexShader;
		ShaderFragmentHLSLD3D9 *	m_pPixelShader;
		ShaderManagerHLSLD3D9 *		m_pShaderManager;
		ShaderProgramManagerD3D9*	m_pShaderProgramManager;
	};
}

#endif