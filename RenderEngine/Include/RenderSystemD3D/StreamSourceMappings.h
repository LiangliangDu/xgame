#ifndef __StreamSourceMappings_H__
#define __StreamSourceMappings_H__

namespace xs
{
	class RenderSystemD3D9;
	class StreamSourceMappings;

	class StreamSourceMappingsCreater
	{
	public:
		static StreamSourceMappings * create(RenderSystemD3D9 * pRenderSystem);
	};

	class StreamSourceMappings
	{
	public:
		/** �󶨶���λ��VBO
		*/
		void	setVertexVertexBuffer(IVertexBuffer* vertexBuffer,uint start);

		/** ��ɢ���VBO
		*/
		void	setDiffuseVertexBuffer(IVertexBuffer* vertexBuffer,uint start);

		/** �󶨾����VBO
		*/
		void	setSpecularVertexBuffer(IVertexBuffer* vertexBuffer,uint start);

		/** �󶨷�����VBO
		*/
		void	setNormalVertexBuffer(IVertexBuffer* vertexBuffer,uint start);
		
		/** ������VBO
		*/
		void	setTexcoordVertexBuffer(ushort unit,IVertexBuffer* vertexBuffer,uint start);

		/** �󶨶����ϵ�Ȩ��
		*/
		void		setBlendWeightVertexBuffer(IVertexBuffer* vertexBuffer, uint start);

		/** �󶨶����ϵľ�������
		*/
		void		setBlendIndicesVertexBuffer(IVertexBuffer* vertexBuffer, uint start);

		/** ������������
		*/
		void	setIndexBuffer(IIndexBuffer* indexBuffer);

		/** ��ȡ��Ӧ�ĵĶ�������
		*/
		IDirect3DVertexDeclaration9 * getVertexDeclaration();


		/** �ͷŸö���
		*/
		void release();

		/** ��ȡ�ж��ٸ�����
		*/
		UINT	getNumVertices();

	private:
		friend class StreamSourceMappingsCreater;
		StreamSourceMappings();
		~StreamSourceMappings();
	private:
		enum VertexDeclarationType
		{
			EVDT_Position =			0x00000001,		//λ��
			EVDT_Normal =			0x00000002,		//������
			EVDT_DiffuseColor =		0x00000004,		//diffuse��ɫ
			EVDT_SpecularColor =	0x00000008,		//specular��ɫ
			EVDT_Tex0 =				0x00000010,		//0������ӳ�䵥Ԫ
			EVDT_Tex1 =				0x00000020,		//1������ӳ�䵥Ԫ
			EVDT_Tex2 =				0x00000040,		//2������ӳ�䵥Ԫ
			EVDT_Tex3 =				0x00000080,		//3������ӳ�䵥Ԫ
			EVDT_Tex4 =				0x00000100,		//4������ӳ�䵥Ԫ
			EVDT_Tex5 =				0x00000200,		//5������ӳ�䵥Ԫ
			EVDT_Tex6 =				0x00000400,		//6������ӳ�䵥Ԫ
			EVDT_Tex7 =				0x00000800,		//7������ӳ�䵥Ԫ
			EVDT_BlendWeight =		0x00001000,		//������Ȩ��
			EVDT_BlendIndices =		0x00002000,		//�����ϵľ�������
			EVDT_TypeNum  =			14,				//����������	
		};
		DWORD m_dwStreamsFlag;						//����ʶ��
	private:
		uint getVertexType2StreamIndex(VertexDeclarationType type);
		struct VertexDeclarationRecord
		{
			bool m_bValid;//�Ƿ���Ч
			D3DVERTEXELEMENT9 m_element;//
		};
		VertexDeclarationRecord m_streamBindRecord[EVDT_TypeNum];


		typedef std::map<DWORD, IDirect3DVertexDeclaration9 * > VertexDeclarationContainer;
		typedef VertexDeclarationContainer::iterator		VertexDeclarationContainerIterator;
		VertexDeclarationContainer	m_vDecls; //������������;
		RenderSystemD3D9 *			m_pRenderSystem;//��Ⱦϵͳָ��

		UINT						m_uiNumVertices;//���������
	};
}

#endif