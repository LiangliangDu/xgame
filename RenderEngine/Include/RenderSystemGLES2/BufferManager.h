#ifndef __BufferManager_H__
#define __BufferManager_H__

namespace xs
{
	class BufferManager : public IBufferManager
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
	protected:
		BufferManager(){}
	public:
		static IBufferManager*	Instance()
		{
			static BufferManager bm;
			return &bm;
		}
	public:
		static GLenum BufferManager::getGLUsage(uint usage);
		static GLenum BufferManager::getGLType(VertexElementType type);
	private:
		xs::Mutex m_mutex;
	};

}
#endif