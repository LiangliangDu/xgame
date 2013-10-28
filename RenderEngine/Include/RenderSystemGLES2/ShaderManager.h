#ifndef __ShaderManager_H__
#define __ShaderManager_H__

#include "RenderEngine/Manager.h"

namespace xs
{
	class ShaderManager : public IShaderManager,public Manager<IShader*>
	{
	public:
		/** ���ļ��д�����ɫ��
		@param ShaderType ��ɫ������
		@param fn �ļ���
		@return ��ɫ���ӿ�ָ��
		*/
		virtual IShader*		createShaderFromFile(ShaderType st,const std::string& fn);	


		/** ���ڴ������д�����ɫ��
		@param ShaderType ��ɫ������
		@param pBuffer ���ݵ�ַ
		@param len ���ݳ���
		@return ��ɫ���ӿ�ָ��
		@see ShaderType
		*/
		virtual IShader*		createShaderFromMemory(ShaderType st,const uchar *pBuffer,uint len);




		/** ����һ����ɫ��
		@param IShader* ��ɫ��ָ��
		*/
		virtual void 			releaseShader(IShader*);	


		/** �������е���ɫ��
		*/
		virtual void 			releaseAllShader();


		/** �ͷ��Լ�
		*/
		virtual void			release();


	public:
		static ShaderManager*	Instance()
		{
			static ShaderManager sm;
			return &sm;
		}

	private:
		IShader*	_createShaderFromMemory(ShaderType st,const uchar* pBuffer,uint len,const std::string& name);
		void doDelete(IShader* pShader);
		const char* getUniqueString();

	protected:
		ShaderManager() : m_ui32Num(0)/*,m_pCurrentShaderProgram(0) */{}
	
	private:
		uint	m_ui32Num;
		//IShaderProgram * m_pCurrentShaderProgram;	
	};
}

#endif