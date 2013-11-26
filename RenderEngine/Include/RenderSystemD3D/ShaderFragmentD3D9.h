#ifndef __ShaderFragmentD3D9_H__
#define __ShaderFragmentD3D9_H__

#include "RenderEngine/Manager.h"
#include "D3D9ResourceManager.h"

namespace xs
{
	class RenderSystemD3D9;

	class ShaderFragmentD3D9: public ManagedItem, public IShader, public D3D9Resource
	{
		// IShader�ӿ�
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

		//D3D9Resource�ӿ�
		public:
		// �豸��ʧ���������ͷ�Default Pool�������Դ
		virtual void notifyOnDeviceLost() {}

		//�豸�ָ�, �������ؽ�Default Pool �������Դ
		virtual void notifyOnDeviceReset() {}

	public:

		/** ����ͳһ������ά����
		@param startRegister	��ʼ�ĸ��㳣���Ĵ������
		@param pData			��������ָ��
		@param countVector4		��ά���������ĸ���
		*/
		bool		setUniformFloatVector4(uint startRegister, float * pData, uint countVector4);

		/** ����ͳһ������ά����
		@param startRegister	��ʼ�����ͳ����Ĵ������
		@param pData			��������ָ��
		@param countVector4		��ά���������ĸ���
		*/
		bool		setUniformIntVector4(uint startRegister, int * pData, uint countVector4);

		/** ����ͳһ��������
		@param startRegister	��ʼ�Ĳ��������Ĵ������
		@param pData			��������ָ�룬0��ʾfalse����0��ʾtrue
		@param countBool		�������ݵĸ���
		*/
		bool		setUniformBool(uint startRegister, int * pData, uint countBool);

		/** �����磬�������ͶӰ�Ⱦ���󶨵�shader�ĳ���,�ʺϵ�shader��ֻ��ͬʱ��һ������
		*/
		void				bindTransformMatrix(uint index, uint type, uint bindRow = 4);

	public:
		ShaderFragmentD3D9(const std::string& name);
		~ShaderFragmentD3D9();
		bool create(RenderSystemD3D9 * pRenderSystem, ShaderType st,const uchar *pBuffer,uint len);
		void release();

	private:
		ShaderType	m_type;
		RenderSystemD3D9 * m_pRenderSystem;
		void	*	m_pShader;//m_pShader �����shader����ת���ɶ���shader��������shaderָ��
	};
}

#endif