#include "StdAfx.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "ShaderProgramManagerOGL.h"

namespace xs
{
	void ShaderProgram::release()
	{	
		ShaderContainerIterator it = m_vShaders.begin();
		for( ; it != m_vShaders.end(); ++it)
			m_pShaderManager->releaseShader( (*it) );

		delete this;
	}

	bool ShaderProgram::bind()
	{
		std::vector<IShader *>::iterator b = m_vShaders.begin(),e = m_vShaders.end();
		while(b != e)
		{
			IShader *pShader = (*b);
			pShader->bind();
			++b;
		}
		m_pShaderProgramManager->onShaderProgramBinded(this);
		return true;
	}

	void ShaderProgram::unbind()
	{
		std::vector<IShader *>::iterator b = m_vShaders.begin(),e = m_vShaders.end();
		while(b != e)
		{
			IShader *pShader = (*b);
			pShader->unbind();
			++b;
		}
		m_pShaderProgramManager->onShaderProgramUnbinded(this);
	}

	bool ShaderProgram::addShaderFromFile(ShaderType st,const std::string& fn)
	{
		IShader * pShader = m_pShaderManager->createShaderFromFile( st, fn);
		if( 0 == pShader ) return false;
		m_vShaders.push_back(pShader);
		return true;
	}

	bool ShaderProgram::addShaderFromMemory(ShaderType st,const uchar *pBuffer,uint len)
	{
		IShader * pShader = m_pShaderManager->createShaderFromMemory( st, pBuffer, len);
		if( 0 == pShader ) return false;
		m_vShaders.push_back(pShader);
		return true;	
	}

	bool ShaderProgram::link()
	{
		return true;
	}

	/** ��ȡ��ɫ����������
	*/
	ShaderProgramType ShaderProgram::getProgramType()
	{
		return SPT_LOWLEVEL;
	}

	/** ����ͳһ������ά����
	@param startRegister	��ʼ�ĸ��㳣���Ĵ������
	@param pData			��������ָ��
	@param countVector4		��ά���������ĸ���
	*/
	bool ShaderProgram::setUniformFloatVector4(uint startRegister, float * pData, uint countVector4)
	{
		ShaderContainerIterator it = m_vShaders.begin();
		for( ; it != m_vShaders.end(); ++it)
		{
			if( static_cast<Shader*>( *it)->setProgramLocalFloatVector4( startRegister, pData, countVector4) )
				return true;
		}
		return false;
	}

	/** ����ͳһ������ά����
	@param startRegister	��ʼ�����ͳ����Ĵ������
	@param pData			��������ָ��
	@param countVector4		��ά���������ĸ���
	*/
	bool ShaderProgram::setUniformIntVector4(uint startRegister, int * pData, uint countVector4)
	{
		//��֧�����͵�
		return false;	
	}

	/** ����ͳһ��������
	@param startRegister	��ʼ�Ĳ��������Ĵ������
	@param pData			��������ָ�룬0��ʾfalse����0��ʾtrue
	@param countBool		�������ݵĸ���
	*/
	bool ShaderProgram::setUniformBool(uint startRegister, int * pData, uint countBool)
	{
		//��֧�����͵�
		return false;
	}

	/** �����磬�������ͶӰ�Ⱦ���󶨵�shader�ĳ���,�ʺϵ�shader��ֻ��ͬʱ��һ������
	*/
	void ShaderProgram::bindTransformMatrix(uint index, uint type, uint bindRow)
	{
		//�ڲ��Ѿ�����
	}
}