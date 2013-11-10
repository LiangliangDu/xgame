#include "StdAfx.h"
#include "HighLevelShaderProgram.h"
#include "HighLevelShader.h"
#include "HighLevelShaderManager.h"
#include "ShaderProgramManagerOGL.h"

namespace xs
{

//----------------------д��attrb��----------------------------
	
	
	static const AttrInfo g_binding_attrs[EVA_MAX] = 
	{
		{VES_POSITION,0,"position",VET_FLOAT3},
		{VES_COLOR,0,"color0",VET_COLOR},
		{VES_TEXTURE_COORDINATES,0,"texcoord0",VET_FLOAT2},
		{VES_TEXTURE_COORDINATES,1,"texcoord1",VET_FLOAT2},
		{VES_NORMAL,0,"normal",VET_FLOAT3},

		//and so on...
	};

	const AttrInfo* getAttrInfo(VetextAttr attr)
	{
		return &g_binding_attrs[attr];
	}

	static GLuint						  s_nLastAttrIndex;
	static std::map<unsigned int, GLuint> s_AttrIndexMap;

	GLuint getAttrLocation(unsigned int usage,unsigned int index)
	{
		unsigned int nKey = (unsigned int)(((usage & 0xFF) << 8) | (index & 0xFF));
		std::map<unsigned int, GLuint>::const_iterator itr = s_AttrIndexMap.find(nKey);
		if (itr == s_AttrIndexMap.end())
		{
			s_AttrIndexMap[nKey] = s_nLastAttrIndex;
			return s_nLastAttrIndex++;
		}
		else
		{
			return itr->second;
		}
	}

	bool getAttrGLInfo(VertexElementType type,GLenum&  glType,GLint& components,GLboolean& normalized)
	{
		glType = GL_FLOAT;
		normalized = GL_FALSE;
		switch (type)
		{
		case VET_FLOAT1:
			components = 1;
			break;
		case VET_FLOAT2:
			components = 2;
			break;
		case VET_FLOAT3:
			components = 3;
			break;
		case VET_FLOAT4:
			components = 4;
			break;
		case VET_COLOR :
			components = 4;
			glType = GL_UNSIGNED_BYTE;
			normalized = GL_TRUE;
			break;
		case VET_UBYTE4:
			components = 4;
			glType = GL_UNSIGNED_BYTE;
			break;
		case VET_SHORT2:
			components = 2;
			glType = GL_SHORT;
			break;
		case VET_SHORT4:
			components = 4;
			glType = GL_SHORT;
			break;

		case VET_SHORT1:
			components = 1;
			glType = GL_SHORT;
			break;

		case VET_SHORT3:
			components = 3;
			glType = GL_SHORT;
			break;
		default:
			assert(0);
			return false;
			break;
		}
		return true;
	}
//--------------------------------------------------------

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
		//Ĭ�ϰ�attribute
		for(int i = 0;i < EVA_MAX ;++i)
		{
			glBindAttribLocation(m_handle
				, getAttrLocation(g_binding_attrs[i].usage, g_binding_attrs[i].index)  
				, g_binding_attrs[i].name);

		}

		glLinkProgram(m_handle);
		GLint bLinked;
		glGetProgramiv(m_handle,GL_LINK_STATUS,&bLinked);
		if (!bLinked)
		{
			int i32InfoLogLength, i32CharsWritten;
			glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
			char* pszInfoLog = new char[i32InfoLogLength];
			glGetProgramInfoLog(m_handle, i32InfoLogLength, &i32CharsWritten, pszInfoLog);
			printf("Failed to link program! err : %s \n",pszInfoLog);
			delete[] pszInfoLog;
			glDeleteProgram(m_handle);
			return false;
		}
		return true;
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
			//д��
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
		//�ڲ��Ѿ�����?????
	}
}