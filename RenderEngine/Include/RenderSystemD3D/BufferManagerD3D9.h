#ifndef __BufferManagerD3D9_H__
#define __BufferManagerD3D9_H__
#include <set>

namespace xs
{
	class BufferManagerD3D9;
	class RenderSystemD3D9;

	class BufferManagerD3D9Creater //buffer manager ����
	{
	public:
		static BufferManagerD3D9 * create( RenderSystemD3D9 * pRenderSystem);
	};

	class BufferManagerD3D9 : public IBufferManager
	{
	public:
		/** �������㻺����
		@param vertexSize ÿ����������ݳ���(�ֽ�)
		@param numVertices ���������
		@param usage ��������ʹ�÷�ʽ���ο�BufferUsage
		@see BufferUsage
		@return ���㻺�����ӿ�
		*/
		virtual IVertexBuffer*	createVertexBuffer(uint vertexSize,uint numVertices,BufferUsage usage, CreateBufferFlag flag = CBF_DEFAULT);

		/** ��������������
		@param itype ��������
		@see IndexType
		@param numIndices ����������
		@param usage ��������ʹ�÷�ʽ
		@see BufferUsage
		@return �����������ӿ�
		*/
		virtual IIndexBuffer*	createIndexBuffer(IndexType itype,uint numIndices,BufferUsage usage, CreateBufferFlag flag = CBF_DEFAULT);	

		/** ��������Ķ���
		@param itype ��������
		@see IndexType
		@param numIndices ����������
		@param usage ��������ʹ�÷�ʽ
		@see BufferUsage
		@return �����������ӿ�
		*/
		virtual VertexDeclaration* createVertexDeclaration();				

		/** �������㻺������
		@return ���㻺������ָ��
		*/
		virtual VertexBufferBinding* createVertexBufferBinding();			

		/** ���ٶ��㶨��
		@param decl ���㶨��
		*/
		virtual void  destroyVertexDeclaration(VertexDeclaration* decl);		

		/** ���ٶ��㻺������
		@param binding ���㻺������
		*/
		virtual void  destroyVertexBufferBinding(VertexBufferBinding* binding);

	public:
		void	addIndexBuffer( IIndexBuffer * pIB);
		void	removeIndexBuffer( IIndexBuffer * pIB);
		void	addVertexBuffer( IVertexBuffer * pVB);
		void	removeVertexBuffer( IVertexBuffer * pVB);

	public:
		/** �ͷ�Buffer������
		*/
		void release();

		/** ��ȡ��������Ⱦϵͳ
		*/
		inline RenderSystemD3D9 * getRenderSystem() { return m_pRenderSystem; }

	private:
		friend class BufferManagerD3D9Creater;
		BufferManagerD3D9();
		~BufferManagerD3D9();	
	private:
		RenderSystemD3D9	*	m_pRenderSystem;//��������Ⱦϵͳ
		std::set< IIndexBuffer * >			m_vIndexBufferContainer;
		std::set< IVertexBuffer * >			m_vVertexBufferContainer;
		std::set< VertexDeclaration * >		m_vVertexDeclarationContainer;
		std::set< VertexBufferBinding * >	m_vVertexBufferBindingContainer;
		xs::Mutex							m_mutex;
	};

}
#endif