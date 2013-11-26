#ifndef __ShaderManagerD3D9_H__
#define __ShaderManagerD3D9_H__

#include "RenderEngine/Manager.h"

namespace xs
{

	class RenderSystemD3D9;
	class ShaderManagerD3D9;

	class ShaderManagerD3D9Creater
	{
	public:
		static ShaderManagerD3D9 * create(RenderSystemD3D9 * pRenderSystem);
	};

	class ShaderManagerD3D9 : public IShaderManager,public Manager<IShader*>
	{
		//IShaderManager�ӿ�
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

		///** ������ɫ������
		//@return ��ɫ������ӿ�ָ��
		//*/
		//virtual IShaderProgram*	createShaderProgram();

		///**	 ��ȡ����������Ⱦ����ɫ������
		//@return ��ɫ������ӿ�ָ��
		//*/
		//virtual IShaderProgram *	getCurrentShaderProgam();

		///**	 ���õ�ǰ������Ⱦ����ɫ�����򣬱�IShaderProgram����
		//@return ��ɫ������ӿ�ָ��
		//*/
		//virtual void setCurrentShaderProgram(IShaderProgram *  pProgram);

		/** �ͷŹ�����
		*/
		virtual void	release();

		//Manager�ӿ�
	private:
		void doDelete(IShader* pShader);
		
	private:
		friend class ShaderManagerD3D9Creater;
		ShaderManagerD3D9();
		~ShaderManagerD3D9();
		bool create( RenderSystemD3D9 * pRenderSystem);

	private:
		const char* getUniqueString();
		IShader * _createShaderFromMemory(RenderSystemD3D9 * pRenderSystem, const std::string & name, ShaderType st,const uchar *pBuffer,uint len);

	private:
		uint	m_ui32Num;
		RenderSystemD3D9 * m_pRenderSystem;
		//IShaderProgram * m_pCurrentShaderProgram;
	};
}

#endif