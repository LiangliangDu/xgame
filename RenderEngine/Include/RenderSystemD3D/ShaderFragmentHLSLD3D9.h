#ifndef __ShaderFragmentHLSLD3D9_H__
#define __ShaderFragmentHLSLD3D9_H__

#include "RenderEngine/Manager.h"
#include "D3D9ResourceManager.h"

namespace xs
{
	class RenderSystemD3D9;

	class ShaderFragmentHLSLD3D9: public ManagedItem, public IShader, public D3D9Resource
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
		
		//<<D3D9Resource�ӿ�>>
	public:
		// �豸��ʧ���������ͷ�Default Pool�������Դ
		virtual void notifyOnDeviceLost() {}

		//�豸�ָ�, �������ؽ�Default Pool �������Դ
		virtual void notifyOnDeviceReset() {}

	public:

		/** ����ͳһ�����ͱ���
		@param	strPara ������
		@param	value   ����ֵ
		@return	�Ƿ����óɹ�
		*/
		bool			setUniformBool(const std::string & strPara,  int value);

		/** ����ͳһ���ͱ���
		@param	strPara ������
		@param	value	����ֵ
		@return	�Ƿ����óɹ�
		*/
		bool			setUniformInt(const std::string & strPara, int value);

		/** ����ͳ�����ͱ���
		@param	strPara ������
		@param	value	����ֵ
		@return	�Ƿ����óɹ�
		*/
		bool			setUniformFloat(const std::string & strPara, float value);

		/** ����ͳһ��������
		@param	strPara ������
		@param	value	����ֵ
		@return	�Ƿ����óɹ�
		*/
		bool			setUniformVector4(const std::string & strPara, const Vector4 & value);

		/** ����һ��ľ���
		@param	strPara ������
		@param	value	����ֵ����������ݣ����������
		@return			�Ƿ����óɹ�
		*/
		bool			setUniformMatrix(const std::string & strPara, const Matrix4 &  value);


		/** ����ͳһ����������
		@param	strPara ������
		@param	count	�����С
		@param	pValue  �����ַ
		@return	�Ƿ����óɹ�
		*/
		bool			setUniformBoolArray(const std::string & strPara, uint count,  int * pValue);

		/** ����ͳһ��������
		@param	strPara ������
		@param	count	�����С
		@param	pValue  �����ַ
		@return	�Ƿ����óɹ�
		*/
		bool			setUniformIntArray(const std::string & strPara, uint count,  int * pValue);

		/** ����ͳһ����������
		@param	strPara ������
		@param	count	�����С
		@param	pValue  �����ַ
		@return	�Ƿ����óɹ�
		*/
		bool			setUniformFloatArray(const std::string & strPara, uint count,  float * pValue);

		/** ����ͳһ����������
		@param	strPara ������
		@param	count	�����С
		@param	pValue  �����ַ
		@return	�Ƿ����óɹ�
		*/
		bool			setUniformVector4Array(const std::string & strPara, uint count,  xs::Vector4 * pValue);

		/** ����ͳһ����������
		@param	strPara ������
		@param	count	�����С
		@param	pValue  �����ַ
		@return	�Ƿ����óɹ�
		*/
		bool			setUniformMatrixArray(const std::string & strPara, uint count,  xs::Matrix4 * pValue);


		/** �����磬�������ͶӰ����󶨵�shader�ĳ���
		*/
		void			bindTransformMatrix( uint flag );


	public:
		ShaderFragmentHLSLD3D9(const std::string& name);
		~ShaderFragmentHLSLD3D9();
		bool create(RenderSystemD3D9 * pRenderSystem, ShaderType st,const uchar *pBuffer,uint len);
		void release();

	private:
		ShaderType	m_type;
		RenderSystemD3D9 * m_pRenderSystem;
		void	*	m_pShader;//m_pShader �����shader����ת���ɶ���shader��������shaderָ��
		ID3DXConstantTable * m_pConstantTable; 
	};
}

#endif