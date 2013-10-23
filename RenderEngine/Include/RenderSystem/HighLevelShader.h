#ifndef __HighLevelShader_H__
#define __HighLevelShader_H__

#include "RenderEngine/Manager.h"

namespace xs
{
	class HighLevelShader : public ManagedItem,public IShader
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
		HighLevelShader(const std::string& name) : ManagedItem(name){}

		bool create(ShaderType st,const uchar *pBuffer,uint len);
		GLhandleARB getHandle();
	private:
		ShaderType	m_type;
		GLenum		m_GLType;
		GLhandleARB	m_handle;
	};
}

#endif