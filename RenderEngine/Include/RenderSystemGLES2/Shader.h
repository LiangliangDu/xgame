#ifndef __Shader_H__
#define __Shader_H__

#include "RenderEngine/Manager.h"

namespace xs
{
	class Shader : public ManagedItem,public IShader
	{
	public:
		/** �����ɫ�����Ͷ�����ɫ������������ɫ��
		@return ��ɫ������
		@see ShaderType
		*/
		virtual ShaderType		getType();

		/** ������ɫ��
		@return �Ƿ�ɹ�
		*/
		virtual bool			compile();

		/** �󶨵�����ɫ��
		@return �Ƿ�󶨳ɹ�
		*/
		virtual bool			bind();	

		/** ȡ���󶨴���ɫ������bind����ʹ��
		*/
		virtual void 			unbind();

	public:

		/** ����ͳһ���������ֵ
		@param startRegister	�����Ĵ������
		@param pData			������ֵ
		@param countVector4		��������ĸ���	
		*/
		bool				setProgramLocalFloatVector4(uint startRegister, float * pData, uint countVector4);

	public:
		Shader(const std::string& name) : m_id(0),ManagedItem(name){}
		bool create(ShaderType st,const uchar *pBuffer,uint len);
		GLuint	getGLShaderID();

	private:
		GLuint	m_id;
		ShaderType	m_type;
		GLenum		m_GLType;
	};
}

#endif