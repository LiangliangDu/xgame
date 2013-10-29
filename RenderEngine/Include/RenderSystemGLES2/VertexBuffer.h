#ifndef __VertexBuffer_H__
#define __VertexBuffer_H__

namespace xs
{
	struct IBufferManager;

	class VertexBuffer : public IVertexBuffer
	{
	public:
		/** �ͷŶ��㻺��������
		*/
		virtual void 	release();

		/** ��ö����С��ÿ������ռ�õ��ֽ���
		@return �����С
		*/
		virtual uint	getVertexSize() const;

		/** ��ö��������
		@return ��������
		*/
		virtual uint	getNumVertices() const;

		/** Buffer��ʹ�÷�ʽ
		@return Buffer��ʹ�÷�ʽ
		@see BufferUsage
		*/
		virtual BufferUsage	getUsage() const;

		/** ������������������ݵ�ָ�룬�Ӷ����Բ�������
		@param offset �����ݿ�ʼ��ƫ��ֵ
		@param length ���������򳤶�
		@param options �����ķ�ʽ
		@see LockOptions
		@return ������ָ��
		*/
		virtual void *	lock(uint offset,uint length,LockOptions options);

		/** ��������������lock����ʹ��
		*/
		virtual void 	unlock();

		/** ��ȡ�������Ƿ��ڱ�����״̬
		@return true��������������falseδ����
		*/
		virtual bool	isLocked();

		/** �ӻ�������ȡ���ݣ��ŵ�ָ���Ļ���
		@param offset �����ݿ�ʼ��ƫ��ֵ
		@param length Ҫ��ȡ�����ݳ���
		@param pDest Ŀ�껺������ַ
		*/
		virtual void 	readData(uint offset,uint length,void * pDest);

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
			bool discardWholeBuffer = false);

		/** ��¡���㻺���������ݣ��û����𷵻صĶ��㻺�����������������
		@return ��¡�����Ķ��㻺����
		*/
		virtual IVertexBuffer*	clone();
	protected:
		uint m_ui32NumVertices;
		uint m_ui32VertexSize;
	private:
		uint			m_ui32BufferID;
		BufferUsage		m_Usage;
		bool			m_bLocked;
		IBufferManager*	m_pBufferManager
			;
		char*			m_pbuffer;	 //lock��ʱbuffer
		unsigned int	m_bufferSize;//lock��ʱbuffer size
		unsigned int	m_offset;	 //lockƫ��
	public:
		VertexBuffer(IBufferManager *pBufferManager,uint vertexSize,uint numVertices,BufferUsage usage);
		~VertexBuffer();
	public:
		GLint		getGLBufferId();
	};

}

#endif