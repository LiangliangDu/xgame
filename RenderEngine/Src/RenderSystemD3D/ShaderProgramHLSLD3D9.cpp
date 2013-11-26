#include "StdAfx.h"
#include "ShaderProgramHLSLD3D9.h"
#include "ShaderFragmentHLSLD3D9.h"
#include "ShaderProgramManagerD3D9.h"
#include "ShaderManagerHLSLD3D9.h"


namespace xs
{

	ShaderProgramHLSLD3D9::ShaderProgramHLSLD3D9(ShaderProgramManagerD3D9 * pProgramMgr, ShaderManagerHLSLD3D9 * pShaderMgr):m_pVertexShader(0),
		m_pPixelShader(0),
		m_pShaderProgramManager(pProgramMgr),
		m_pShaderManager(pShaderMgr)
	{
	}

	/** �ͷ���ɫ������
	*/
	void ShaderProgramHLSLD3D9::release()
	{
		if( m_pVertexShader ) m_pShaderManager->releaseShader(m_pVertexShader);
		if( m_pPixelShader)   m_pShaderManager->releaseShader(m_pPixelShader);
		delete this;
	}

	/** �󶨵�����ɫ������
	@return �Ƿ�ɹ�
	*/
	bool ShaderProgramHLSLD3D9::bind()
	{
		if( m_pVertexShader)
			m_pVertexShader->bind();
		if( m_pPixelShader)
			m_pPixelShader->bind();
		m_pShaderProgramManager->onShaderProgramBinded(this);

		return true;
	}

	/** ȡ���󶨵�����ɫ��
	*/
	void ShaderProgramHLSLD3D9::unbind()
	{
		if( m_pVertexShader)
			m_pVertexShader->unbind();
		if( m_pPixelShader)
			m_pPixelShader->unbind();

		m_pShaderProgramManager->onShaderProgramUnbinded(this);
	}

	/** ���ļ��������ɫ��
	@param ShaderType ��ɫ������
	@param fn �ļ���
	@return ��ɫ���ӿ�ָ��
	*/
	bool ShaderProgramHLSLD3D9::addShaderFromFile(ShaderType st,const std::string& fn)
	{
		IShader * pShader = m_pShaderManager->createShaderFromFile(st, fn);
		if( 0 == pShader ) return false;

		if( ST_VERTEX_PROGRAM == st) m_pVertexShader = static_cast<ShaderFragmentHLSLD3D9 *>(pShader);
		else  m_pPixelShader = static_cast<ShaderFragmentHLSLD3D9 *>(pShader);

		return true;
	}

	/** ���ڴ������������ɫ��
	@param ShaderType ��ɫ������
	@param pBuffer ���ݵ�ַ
	@param len ���ݳ���
	@return ��ɫ���ӿ�ָ��
	@see ShaderType
	*/
	bool ShaderProgramHLSLD3D9::addShaderFromMemory(ShaderType st,const uchar *pBuffer,uint len)
	{
		IShader * pShader = m_pShaderManager->createShaderFromMemory(st, pBuffer, len);
		if( 0 == pShader ) return false;

		if( ST_VERTEX_PROGRAM == st) m_pVertexShader = static_cast<ShaderFragmentHLSLD3D9 *>(pShader);
		else  m_pPixelShader = static_cast<ShaderFragmentHLSLD3D9 *>(pShader);

		return true;	
	}


	/** ���������ɫ������
	@return �Ƿ�ɹ�
	*/
	bool ShaderProgramHLSLD3D9::link()	
	{
		return true;
	}

	/** ��ȡ��ɫ����������
	*/
	ShaderProgramType ShaderProgramHLSLD3D9::getProgramType()
	{
		return SPT_HIGHLEVEL;
	}


	/** ����ͳһ�����ͱ���
	@param	strPara ������
	@param	value   ����ֵ
	@return	�Ƿ����óɹ�
	*/
	bool ShaderProgramHLSLD3D9::setUniformBool(const std::string & strPara,  int value)
	{
		bool vertex_ret = false;
		if( m_pVertexShader)
		{
			vertex_ret = m_pVertexShader->setUniformBool(strPara, value);
		}
		if( vertex_ret) return true;

		bool pixel_ret = false;
		if( m_pPixelShader)
		{
			pixel_ret = m_pPixelShader->setUniformBool(strPara, value);
		}
		return pixel_ret;
	}

	/** ����ͳһ���ͱ���
	@param	strPara ������
	@param	value	����ֵ
	@return	�Ƿ����óɹ�
	*/
	bool ShaderProgramHLSLD3D9::setUniformInt(const std::string & strPara, int value)
	{
		bool vertex_ret = false;
		if( m_pVertexShader)
		{
			vertex_ret = m_pVertexShader->setUniformInt(strPara, value);
		}
		if( vertex_ret) return true;

		bool pixel_ret = false;
		if( m_pPixelShader)
		{
			pixel_ret = m_pPixelShader->setUniformInt(strPara, value);
		}
		return pixel_ret;
	}

	/** ����ͳ�����ͱ���
	@param	strPara ������
	@param	value	����ֵ
	@return	�Ƿ����óɹ�
	*/
	bool ShaderProgramHLSLD3D9::setUniformFloat(const std::string & strPara, float value)
	{
		bool vertex_ret = false;
		if( m_pVertexShader)
		{
			vertex_ret = m_pVertexShader->setUniformFloat(strPara, value);
		}
		if( vertex_ret) return true;

		bool pixel_ret = false;
		if( m_pPixelShader)
		{
			pixel_ret = m_pPixelShader->setUniformFloat(strPara, value);
		}
		return pixel_ret;
	}

	/** ����ͳһ��������
	@param	strPara ������
	@param	value	����ֵ
	@return	�Ƿ����óɹ�
	*/
	bool			ShaderProgramHLSLD3D9::setUniformVector4(const std::string & strPara, const Vector4 & value)
	{
		bool vertex_ret = false;
		if( m_pVertexShader)
		{
			vertex_ret = m_pVertexShader->setUniformVector4(strPara, value);
		}
		if( vertex_ret) return true;

		bool pixel_ret = false;
		if( m_pPixelShader)
		{
			pixel_ret = m_pPixelShader->setUniformVector4(strPara, value);
		}
		return pixel_ret;
	}

	/** ����һ��ľ���
	@param	strPara ������
	@param	value	����ֵ����������ݣ����������
	@return			�Ƿ����óɹ�
	*/
	bool			ShaderProgramHLSLD3D9::setUniformMatrix(const std::string & strPara, const Matrix4 &  value,bool normal)
	{
		bool vertex_ret = false;
		if( m_pVertexShader)
		{
			vertex_ret = m_pVertexShader->setUniformMatrix(strPara, value);
		}
		if( vertex_ret) return true;

		bool pixel_ret = false;
		if( m_pPixelShader)
		{
			pixel_ret = m_pPixelShader->setUniformMatrix(strPara, value);
		}
		return pixel_ret;
	}


	/** ����ͳһ����������
	@param	strPara ������
	@param	count	�����С
	@param	pValue  �����ַ
	@return	�Ƿ����óɹ�
	*/
	bool ShaderProgramHLSLD3D9::setUniformBoolArray(const std::string & strPara, uint count,  int * pValue)
	{
		bool vertex_ret = false;
		if( m_pVertexShader)
		{
			vertex_ret = m_pVertexShader->setUniformBoolArray(strPara, count, pValue);
		}
		if( vertex_ret) return true;

		bool pixel_ret = false;
		if( m_pPixelShader)
		{
			pixel_ret = m_pPixelShader->setUniformBoolArray(strPara, count, pValue);
		}
		return pixel_ret;
	}

	/** ����ͳһ��������
	@param	strPara ������
	@param	count	�����С
	@param	pValue  �����ַ
	@return	�Ƿ����óɹ�
	*/
	bool			ShaderProgramHLSLD3D9::setUniformIntArray(const std::string & strPara, uint count,  int * pValue)
	{
		bool vertex_ret = false;
		if( m_pVertexShader)
		{
			vertex_ret = m_pVertexShader->setUniformIntArray(strPara, count, pValue);
		}
		if( vertex_ret) return true;

		bool pixel_ret = false;
		if( m_pPixelShader)
		{
			pixel_ret = m_pPixelShader->setUniformIntArray(strPara, count, pValue);
		}
		return pixel_ret;
	}

	/** ����ͳһ����������
	@param	strPara ������
	@param	count	�����С
	@param	pValue  �����ַ
	@return	�Ƿ����óɹ�
	*/
	bool			ShaderProgramHLSLD3D9::setUniformFloatArray(const std::string & strPara, uint count,  float * pValue)
	{
		bool vertex_ret = false;
		if( m_pVertexShader)
		{
			vertex_ret = m_pVertexShader->setUniformFloatArray(strPara, count, pValue);
		}
		if( vertex_ret) return true;

		bool pixel_ret = false;
		if( m_pPixelShader)
		{
			pixel_ret = m_pPixelShader->setUniformFloatArray(strPara, count, pValue);
		}
		return pixel_ret;
	}

	/** ����ͳһ����������
	@param	strPara ������
	@param	count	�����С
	@param	pValue  �����ַ
	@return	�Ƿ����óɹ�
	*/
	bool			ShaderProgramHLSLD3D9::setUniformVector4Array(const std::string & strPara, uint count,  xs::Vector4 * pValue)
	{
		bool vertex_ret = false;
		if( m_pVertexShader)
		{
			vertex_ret = m_pVertexShader->setUniformVector4Array(strPara, count, pValue);
		}
		if( vertex_ret) return true;

		bool pixel_ret = false;
		if( m_pPixelShader)
		{
			pixel_ret = m_pPixelShader->setUniformVector4Array(strPara, count, pValue);
		}
		return pixel_ret;
	}

	/** ����ͳһ����������
	@param	strPara ������
	@param	count	�����С
	@param	pValue  �����ַ
	@return	�Ƿ����óɹ�
	*/
	bool			ShaderProgramHLSLD3D9::setUniformMatrixArray(const std::string & strPara, uint count,  xs::Matrix4 * pValue)
	{
		bool vertex_ret = false;
		if( m_pVertexShader)
		{
			vertex_ret = m_pVertexShader->setUniformMatrixArray(strPara, count, pValue);
		}
		if( vertex_ret) return true;

		bool pixel_ret = false;
		if( m_pPixelShader)
		{
			pixel_ret = m_pPixelShader->setUniformMatrixArray(strPara, count, pValue);
		}
		return pixel_ret;
	}


	/** ���������󶨵�shader�ĳ���
	*/
	void ShaderProgramHLSLD3D9::bindSampler(  uint smaplerNum  )
	{
		//shader �ڲ���
	}

	/** �����磬�������ͶӰ����󶨵�shader�ĳ���
	*/
	void ShaderProgramHLSLD3D9::bindTransformMatrix(  uint flag  )
	{
		//ֻ��vertex shader ��Ч
		if(m_pVertexShader) m_pVertexShader->bindTransformMatrix( flag );
	}
}