#include "StdAfx.h"
#include "ShaderProgramD3D9.h"
#include "ShaderFragmentD3D9.h"
#include "ShaderManagerD3D9.h"
#include "ShaderProgramManagerD3D9.h"


namespace xs
{

	ShaderProgramD3D9::ShaderProgramD3D9(ShaderProgramManagerD3D9 * pProgramMgr, ShaderManagerD3D9 * pShaderMgr):m_pVertexShader(0),
		m_pPixelShader(0),
		m_pShaderManager(pShaderMgr),
		m_pShaderProgramManager(pProgramMgr)
	{
	}

	/** �ͷ���ɫ������
	*/
	void ShaderProgramD3D9::release()
	{
		if( m_pVertexShader) m_pShaderManager->releaseShader( m_pVertexShader );
		if( m_pPixelShader ) m_pShaderManager->releaseShader( m_pPixelShader  );

		delete this;
	}

	/** �󶨵�����ɫ������
	@return �Ƿ�ɹ�
	*/
	bool ShaderProgramD3D9::bind()
	{
		if( m_pVertexShader)
			m_pVertexShader->bind();
		if( m_pPixelShader)
			m_pPixelShader->bind();

		m_pShaderProgramManager->onShaderProgramBinded( this);
		return true;
	}

	/** ȡ���󶨵�����ɫ��
	*/
	void ShaderProgramD3D9::unbind()
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
	bool ShaderProgramD3D9::addShaderFromFile(ShaderType st,const std::string& fn)
	{
		IShader * pShader = m_pShaderManager->createShaderFromFile(st, fn);
		if( 0 == pShader ) return false;

		if( ST_VERTEX_PROGRAM == st) m_pVertexShader = static_cast< xs::ShaderFragmentD3D9 *>(pShader);
		else m_pPixelShader = static_cast< xs::ShaderFragmentD3D9 *>(pShader);
		return true;
	}

	/** ���ڴ������������ɫ��
	@param ShaderType ��ɫ������
	@param pBuffer ���ݵ�ַ
	@param len ���ݳ���
	@return ��ɫ���ӿ�ָ��
	@see ShaderType
	*/
	bool ShaderProgramD3D9::addShaderFromMemory(ShaderType st,const uchar *pBuffer,uint len)
	{
		IShader * pShader = m_pShaderManager->createShaderFromMemory(st, pBuffer, len);
		if( 0 == pShader ) return false;

		if( ST_VERTEX_PROGRAM == st) m_pVertexShader = static_cast< xs::ShaderFragmentD3D9 *>(pShader);
		else m_pPixelShader = static_cast< xs::ShaderFragmentD3D9 *>(pShader);	
		return true;
	}


	/** ���������ɫ������
	@return �Ƿ�ɹ�
	*/
	bool ShaderProgramD3D9::link()	
	{
		return true;
	}

	/** ��ȡ��ɫ����������
	*/
	ShaderProgramType ShaderProgramD3D9::getProgramType()
	{
		return SPT_LOWLEVEL;
	}

	/** ����ͳһ������ά����
	@param startRegister	��ʼ�ĸ��㳣���Ĵ������
	@param pData			��������ָ��
	@param countVector4		��ά���������ĸ���
	*/
	bool ShaderProgramD3D9::setUniformFloatVector4(uint startRegister, float * pData, uint countVector4)
	{
		bool vertex_ret = false;
		if( m_pVertexShader)
		{
			vertex_ret = m_pVertexShader->setUniformFloatVector4(startRegister, pData, countVector4);
		}
		if( vertex_ret) return true;
		bool pixel_ret = false;
		if( m_pPixelShader)
		{
			pixel_ret = m_pPixelShader->setUniformFloatVector4(startRegister, pData, countVector4);
		}

		return pixel_ret;
	}

	/** ����ͳһ������ά����
	@param startRegister	��ʼ�����ͳ����Ĵ������
	@param pData			��������ָ��
	@param countVector4		��ά���������ĸ���
	*/
	bool ShaderProgramD3D9::setUniformIntVector4(uint startRegister, int * pData, uint countVector4)
	{
		bool vertex_ret = false;
		if( m_pVertexShader)
		{
			vertex_ret = m_pVertexShader->setUniformIntVector4(startRegister, pData, countVector4);
		}
		if( vertex_ret) return true;

		bool pixel_ret = false;
		if( m_pPixelShader)
		{
			pixel_ret = m_pPixelShader->setUniformIntVector4(startRegister, pData, countVector4);
		}

		return pixel_ret;
	}

	/** ����ͳһ��������
	@param startRegister	��ʼ�Ĳ��������Ĵ������
	@param pData			��������ָ�룬0��ʾfalse����0��ʾtrue
	@param countBool		�������ݵĸ���
	*/
	bool ShaderProgramD3D9::setUniformBool(uint startRegister, int * pData, uint countBool)
	{
		bool vertex_ret = false;
		if( m_pVertexShader)
		{
			vertex_ret = m_pVertexShader->setUniformBool(startRegister, pData, countBool);
		}
		if( vertex_ret) return true;

		bool pixel_ret = false;
		if( m_pPixelShader)
		{
			pixel_ret = m_pPixelShader->setUniformBool(startRegister, pData, countBool);
		}
		return pixel_ret;
	}

	/** �����磬�������ͶӰ�Ⱦ���󶨵�shader�ĳ���,�ʺϵ�shader��ֻ��ͬʱ��һ������
	*/
	void ShaderProgramD3D9::bindTransformMatrix(uint index, uint type, uint bindRow)
	{
		//ֻ��vertex shader��Ч
		if( m_pVertexShader)
		{
			m_pVertexShader->bindTransformMatrix(index, type, bindRow);
		}
	}
}