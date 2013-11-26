#ifndef __MappingsD3D9_H__
#define __MappingsD3D9_H__

namespace xs
{
	/** ����Ⱦ���������ӳ�䵽D3D9 �����������ӳ��
	*/
	struct MappingsD3D9 
	{
		//��ȡbuffer��Ӧ��D3D9ʹ�÷�ʽ
		static	DWORD	getBufferUsage( BufferUsage usage);
		//����buffer����;����ʹ�����ֳع���
		static	D3DPOOL	getPoolTypeByBufferUsage( BufferUsage usage);
		//�����������ͻ�ȡ��Ӧ�ĸ�ʽ
		static D3DFORMAT getIndexTypeFormat(IndexType type);
		//�����������ͻ�ȡ��Ӧ��������С
		static UINT		getIndexTypeSize(IndexType type);
		//��ȡD3D9��Ӧ��ͼԪ����,��֧�ֻ����ı��Σ��ı��δ���������ߣ������ߴ���ʾ)
		static D3DPRIMITIVETYPE getPrimptiveType( PrimitiveType type);
		//��ȡD3D9ͼԪ���ͺͶ���������Ӧ��ͼԪ����
		static UINT	getPrimitiveCount(PrimitiveType type, uint indexCount);
		//��ȡ��Ӧ��D3D9����
		static D3DXMATRIX	getMatrix( const xs::Matrix4 & mat);
		//��ȡD3D9�����Ӧ�ı��������
		static xs::Matrix4 getMatrix(const D3DXMATRIX & mat);
		//����ת��
		static void getMatrix(const xs::Matrix4 & in, D3DXMATRIX & out);
		//����ת��
		static void getMatrix(const D3DXMATRIX & in, xs::Matrix4 & out);
		//��ȡD3D9���ղ���
		static void getLight(/*const*/ xs::Light & lit, D3DLIGHT9 & d3d9lit);
		//��ȡ������ղ���
		static void getLight(const D3DLIGHT9 & d3d9lit, xs::Light & lit);
		//��D3D9ȡ���ģʽ
		static D3DFILLMODE getFillMode( FillMode fm);
		//��ȡD3D9�����ѡģʽ
		static D3DCULL getCullingMode(CullingMode cm);
		//��ȡD3D9���ģʽ
		static D3DFOGMODE getFogMode(FogMode fm);
		//��ȡD3D9��ȼ�⺯��
		static D3DCMPFUNC getDepthFunc(CompareFunction cf);
		//��ȡD3D9Alpha��⺯��
		static D3DCMPFUNC getAlphaFunc(CompareFunction cf);
		//��ȡD3D9ģ���⺯��
		static D3DCMPFUNC getStencilFunc(CompareFunction cf);
		//��ȡD3D9ģ�������ʽ
		static D3DSTENCILOP  getStencilOp( StencilOperation so);
		//��ȡD3D9 alpha��Ϸ�ʽ
		static D3DBLEND  getBlendFactor(SceneBlendFactor factor);
		//��ȡD3D9��ʽ
		static D3DFORMAT getFormat(PixelFormat pf);
		//��ȡ�ӽ���D3D9��ʽ
		static PixelFormat getClosestSupportedFormat(PixelFormat pf);
		//��ȡD3D9�Ĺ���������
		static D3DTEXTUREFILTERTYPE getFilterType(FilterOptions fo);
		//��ȡ����Ĺ���������
		static FilterOptions		getFilterType( D3DTEXTUREFILTERTYPE texf);
		//��ȡD3D9��Ѱַģʽ
		static D3DTEXTUREADDRESS	getAddressMode( TextureAddressingMode addr);
		//��ȡ�����Ѱַģʽ
		static TextureAddressingMode getAddressMode( D3DTEXTUREADDRESS addr);
		//��ȡ����Stage�Ĳ�������
		static D3DTEXTUREOP		getTextureStageOperator(TextureStageOperator op);
		//��ȡ�����Stage�Ĳ�����
		static DWORD			getTextureStageArgument(TextureStageArgument arg);

	};
}

#endif