#ifndef __DefaultBufferManager_H__
#define __DefaultBufferManager_H__

namespace xs 
{
	struct IBufferManager;

	class DefaultBufferManager : public IBufferManager
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
		DefaultBufferManager(){}
	public:
		static IBufferManager*	Instance()
		{
			static DefaultBufferManager bm;
			return &bm;
		}
	};

	class DefaultIndexBuffer : public IIndexBuffer
	{
	public:
		/** ����������������ͣ��ο�IndexTypeö������
		@see IndexType
		@return ����������
		*/
		virtual IndexType	getType(void ) const ;							

		/** ��ȡ����������
		@return ����������
		*/
		virtual uint		getNumIndices(void ) const ;						

		/** ��������ĳ���(�ֽ�)
		@return ÿ�������ĳ��ȣ�һ��Ϊ2,4
		*/
		virtual uint		getIndexSize(void ) const ;						

		/** ���������������ʹ�÷�ʽ���ο�BufferUsage
		@see BufferUsage
		@return ������������ʹ�÷�ʽ
		*/
		virtual BufferUsage	getUsage() const ;

		/** ��������������������ֱ�Ӵ�ȡ����
		@param offset �����ݿ�ʼ��ƫ�ƣ��ֽڣ�
		@param length Ҫ�������������ĳ���
		@param options �����ķ�ʽ
		@see LockOptions
		@return ֱ�����ݵĵ�ַ
		*/
		virtual void *		lock(uint offset,uint length,LockOptions options) ;						

		/** ��������������lock����ʹ��
		*/
		virtual void 		unlock() ;		

		/** ��ȡ�����������Ƿ��ڼ���״̬
		@return true��ʾ���ڼ���״̬��false��δ����
		*/
		virtual bool		isLocked() ;		

		/** �ͷŻ���������
		*/
		virtual void 		release() ;		

		/** �ӻ�������ȡ���ݣ��ŵ�ָ���Ļ���
		@param offset �����ݿ�ʼ��ƫ��ֵ
		@param length Ҫ��ȡ�����ݳ���
		@param pDest Ŀ�껺������ַ
		*/
		virtual void 	readData(uint offset,uint length,void * pDest) ;	

		/** ������д�뻺����
		@param offset �����ݿ�ʼ��ƫ��ֵ
		@param length Ҫд��ĵ����ݳ���
		@param pSource Ҫд������ݵ�ַ
		@param discardWholeBuffer �Ƿ�Ҫ��������buffer������(������ٶ�)
		*/
		virtual void 	writeData(																			
			uint offset,																	
			uint length,																	
			const void * pSource,															
			bool discardWholeBuffer = false) ;
	protected:
		uchar* mpData;
		uint m_ui32NumIndexes;
		uint m_ui32IndexSize;
		uint		m_ui32SizeInBytes;
	public:
		DefaultIndexBuffer(IndexType idxType, uint numIndexes,BufferUsage usage);
		~DefaultIndexBuffer();
		void* getDataPtr(size_t offset) const { return (void*)(mpData + offset); }
	};

	class DefaultVertexBuffer : public IVertexBuffer
	{
	public:
		/** �ͷŶ��㻺��������
		*/
		virtual void 	release() ;

		/** ��ö����С��ÿ������ռ�õ��ֽ���
		@return �����С
		*/
		virtual uint	getVertexSize() const ;

		/** ��ö��������
		@return ��������
		*/
		virtual uint	getNumVertices() const ;

		/** Buffer��ʹ�÷�ʽ
		@return Buffer��ʹ�÷�ʽ
		@see BufferUsage
		*/
		virtual BufferUsage	getUsage() const ;

		/** ������������������ݵ�ָ�룬�Ӷ����Բ�������
		@param offset �����ݿ�ʼ��ƫ��ֵ
		@param length ���������򳤶�
		@param options �����ķ�ʽ
		@see LockOptions
		@return ������ָ��
		*/
		virtual void *	lock(uint offset,uint length,LockOptions options) ;

		/** ��������������lock����ʹ��
		*/
		virtual void 	unlock() ;

		/** ��ȡ�������Ƿ��ڱ�����״̬
		@return true��������������falseδ����
		*/
		virtual bool	isLocked() ;

		/** �ӻ�������ȡ���ݣ��ŵ�ָ���Ļ���
		@param offset �����ݿ�ʼ��ƫ��ֵ
		@param length Ҫ��ȡ�����ݳ���
		@param pDest Ŀ�껺������ַ
		*/
		virtual void 	readData(uint offset,uint length,void * pDest) ;	

		/** ������д�뻺����
		@param offset �����ݿ�ʼ��ƫ��ֵ
		@param length Ҫд��ĵ����ݳ���
		@param pSource Ҫд������ݵ�ַ
		@param discardWholeBuffer �Ƿ�Ҫ��������buffer������(������ٶ�)
		*/
		virtual void 	writeData(																			
			uint offset,																	
			uint length,																	
			const void * pSource,															
			bool discardWholeBuffer = false) ;

		/** ��¡���㻺���������ݣ��û����𷵻صĶ��㻺�����������������
		@return ��¡�����Ķ��㻺����
		*/
		virtual IVertexBuffer*	clone() ;
	protected:
		uchar* mpData;
		uint		m_ui32NumVertices;
		uint		m_ui32VertexSize;
		uint		m_ui32SizeInBytes;
		IBufferManager*	m_pBufferManager;
	public:
		DefaultVertexBuffer(IBufferManager *pBufferManager,uint vertexSize,uint numVertices,BufferUsage usage);
		~DefaultVertexBuffer();

		void* getDataPtr(size_t offset) const { return (void*)(mpData + offset); }
	};

}

#endif
