#include "StdAfx.h"
#include "HighLevelShaderProgram.h"
#include "HighLevelShader.h"
#include "HighLevelShaderManager.h"
#include "ShaderProgramManagerOGL.h"
namespace xs
{
	void	HighLevelShaderProgram::release()
	{
		ShaderContainerIterator it = m_vShaders.begin();
		for( ; it != m_vShaders.end(); ++it)
			m_pShaderManger->releaseShader( *it);

		m_vShaders.clear();
		glDeleteProgram(m_handle);
		delete this;
	}
	
	bool	HighLevelShaderProgram::bind()
	{
		glUseProgram(m_handle);
		m_pShaderProgramManager->onShaderProgramBinded(this);
		return true;
	}

	void	HighLevelShaderProgram::unbind()
	{
		glUseProgram(0);
		m_pShaderProgramManager->onShaderProgramUnbinded(this);
	}

	bool HighLevelShaderProgram::addShaderFromFile(ShaderType st,const std::string& fn)
	{
		IShader * pShader = m_pShaderManger->createShaderFromFile(st, fn);
		if( 0 == pShader ) return false;

		m_vShaders.push_back(pShader);
		glAttachShader(m_handle,static_cast<HighLevelShader*>(pShader)->getHandle());
		return true;
	}

	bool HighLevelShaderProgram::addShaderFromMemory(ShaderType st,const uchar *pBuffer,uint len)
	{
		IShader * pShader = m_pShaderManger->createShaderFromMemory(st, pBuffer, len);
		if( 0 == pShader ) return false;

		m_vShaders.push_back(pShader);
		glAttachShader(m_handle,static_cast<HighLevelShader*>(pShader)->getHandle());
		return true;
	}

	bool	HighLevelShaderProgram::link()
	{
		glLinkProgram(m_handle);
		GLint bLinked;
		glGetProgramiv(m_handle,GL_LINK_STATUS,&bLinked);
		return bLinked != 0;
	}

	/** ��ȡ��ɫ����������
	*/
	ShaderProgramType HighLevelShaderProgram::getProgramType()
	{
		return SPT_HIGHLEVEL;
	}

	bool HighLevelShaderProgram::create()
	{
		m_handle = glCreateProgram();
		return m_handle != 0;
	}



	/** ����ͳһ�����ͱ���
	@param	strPara ������
	@param	value   ����ֵ
	@return	�Ƿ����óɹ�
	*/
	bool HighLevelShaderProgram::setUniformBool(const std::string & strPara,  int value)
	{
		GLint loc = glGetUniformLocation(m_handle, strPara.c_str() );
		if( loc < 0 ) return false;

		glUniform1i(loc,(GLint)value);

		return true;
	}

	/** ����ͳһ���ͱ���
	@param	strPara ������
	@param	value	����ֵ
	@return	�Ƿ����óɹ�
	*/
	bool HighLevelShaderProgram::setUniformInt(const std::string & strPara, int value)
	{
		GLint loc = glGetUniformLocation(m_handle, strPara.c_str() );
		if( loc < 0 ) return false;

		glUniform1i(loc,(GLint)value);

		return true;
	}

	/** ����ͳ�����ͱ���
	@param	strPara ������
	@param	value	����ֵ
	@return	�Ƿ����óɹ�
	*/
	bool HighLevelShaderProgram::setUniformFloat(const std::string & strPara, float value)
	{
		GLint loc = glGetUniformLocation(m_handle, strPara.c_str() );
		if( loc < 0 ) return false;

		glUniform1f(loc,(GLfloat)value);

		return true;	
	}

	/** ����ͳһ��������
	@param	strPara ������
	@param	value	����ֵ
	@return	�Ƿ����óɹ�
	*/
	bool			HighLevelShaderProgram::setUniformVector4(const std::string & strPara, const Vector4 & value)
	{
		GLint loc = glGetUniformLocation(m_handle, strPara.c_str() );
		if( loc < 0 ) return false;

		glUniform4f(loc,value.x, value.y, value.z, value.w);

		return true;
	}

	/** ����һ��ľ���
	@param	strPara ������
	@param	value	����ֵ����������ݣ����������
	@return			�Ƿ����óɹ�
	*/
	bool HighLevelShaderProgram::setUniformMatrix(const std::string & strPara, const Matrix4 &  value)
	{
		GLint loc = glGetUniformLocation(m_handle, strPara.c_str() );
		if( loc < 0) return false;

		glUniformMatrix4fv(loc, 1, GL_TRUE, &value[0][0]);
		return true;
	}


	/** ����ͳһ����������
	@param	strPara ������
	@param	count	�����С
	@param	pValue  �����ַ
	@return	�Ƿ����óɹ�
	*/
	bool HighLevelShaderProgram::setUniformBoolArray(const std::string & strPara, uint count,  int * pValue)
	{
		if( count <= 0 || 0 == pValue) return false;
		GLint loc = glGetUniformLocation(m_handle, strPara.c_str() );
		if( loc < 0 ) return false;

		glUniform1iv(loc, (GLsizei)count, (GLint*)pValue);

		return true;	
	}

	/** ����ͳһ��������
	@param	strPara ������
	@param	count	�����С
	@param	pValue  �����ַ
	@return	�Ƿ����óɹ�
	*/
	bool HighLevelShaderProgram::setUniformIntArray(const std::string & strPara, uint count,  int * pValue)
	{
		if( count <= 0 || 0 == pValue) return false;
		GLint loc = glGetUniformLocation(m_handle, strPara.c_str() );
		if( loc < 0 ) return false;

		glUniform1iv(loc, (GLsizei)count, (GLint*)pValue);

		return true;
	}

	/** ����ͳһ����������
	@param	strPara ������
	@param	count	�����С
	@param	pValue  �����ַ
	@return	�Ƿ����óɹ�
	*/
	bool HighLevelShaderProgram::setUniformFloatArray(const std::string & strPara, uint count,  float * pValue)
	{
		if( count <= 0 || 0 == pValue) return false;
		GLint loc = glGetUniformLocation(m_handle, strPara.c_str() );
		if( loc < 0 ) return false;

		glUniform1fv(loc, (GLsizei)count, (const GLfloat*)pValue);

		return true;
	}

	/** ����ͳһ����������
	@param	strPara ������
	@param	count	�����С
	@param	pValue  �����ַ
	@return	�Ƿ����óɹ�
	*/
	bool HighLevelShaderProgram::setUniformVector4Array(const std::string & strPara, uint count,  xs::Vector4 * pValue)
	{
		if( count <= 0 || 0 == pValue) return false;
		GLint loc = glGetUniformLocation(m_handle, strPara.c_str() );
		if( loc < 0 ) return false;

		glUniform4fv(loc, (GLsizei)count, (const GLfloat*)pValue->val);

		return true;
	}

	/** ����ͳһ����������
	@param	strPara ������
	@param	count	�����С
	@param	pValue  �����ַ
	@return	�Ƿ����óɹ�
	*/
	bool			HighLevelShaderProgram::setUniformMatrixArray(const std::string & strPara, uint count,  xs::Matrix4 * pValue)
	{
		if( count <= 0 || 0 == pValue) return false;
		GLint loc = glGetUniformLocation(m_handle, strPara.c_str() );
		if( loc < 0) return false;

		glUniformMatrix4fv(loc, count, GL_TRUE, &pValue[0][0][0]);
		return true;
	}

	/** ���������󶨵�shader�ĳ���
	*/
	void HighLevelShaderProgram::bindSampler( uint smaplerNum )
	{
		const static char * s_pSamplerName [8] = 
		{
			"texture0",
			"texture1",
			"texture2",
			"texture3",
			"texture4",
			"texture5",
			"texture6",
			"texture7",
		};

		if( smaplerNum > 8 ) smaplerNum =  8;
		for( uint i=0; i < smaplerNum; ++i)
		{
			GLint loc = glGetUniformLocation( m_handle, s_pSamplerName[i]);
			if( loc < 0) continue;
			glUniform1i(loc,i);
		}
	}

	/** �����磬�������ͶӰ����󶨵�shader�ĳ���
	*/
	void HighLevelShaderProgram::bindTransformMatrix( uint flag )
	{
		//�ڲ��Ѿ�����
	}
}