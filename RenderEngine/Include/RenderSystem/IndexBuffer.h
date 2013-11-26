#ifndef __IndexBuffer_H__
#define __IndexBuffer_H__

namespace xs
{
	class IndexBuffer : public IIndexBuffer
	{
	public:
		/** ����������������ͣ��ο�IndexTypeö������
		@see IndexType
		@return ����������
		*/
		virtual IndexType	getType(void ) const;							

		/** ��ȡ����������
		@return ����������
		*/
		virtual uint		getNumIndices(void ) const;						

		/** ��������ĳ���(�ֽ�)
		@return ÿ�������ĳ��ȣ�һ��Ϊ2,4
		*/
		virtual uint		getIndexSize(void ) const;						

		/** ���������������ʹ�÷�ʽ���ο�BufferUsage
		@see BufferUsage
		@return ������������ʹ�÷�ʽ
		*/
		virtual BufferUsage	getUsage() const;

		/** ��������������������ֱ�Ӵ�ȡ����
		@param offset �����ݿ�ʼ��ƫ�ƣ��ֽڣ�
		@param length Ҫ�������������ĳ���
		@param options �����ķ�ʽ
		@see LockOptions
		@return ֱ�����ݵĵ�ַ
		*/
		virtual void *		lock(uint offset,uint length,LockOptions options);						

		/** ��������������lock����ʹ��
		*/
		virtual void 		unlock();		

		/** ��ȡ�����������Ƿ��ڼ���״̬
		@return true��ʾ���ڼ���״̬��false��δ����
		*/
		virtual bool		isLocked();		

		/** �ͷŻ���������
		*/
		virtual void 		release();		

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
	protected:
		IndexType m_IndexType;
		uint m_ui32NumIndexes;
		uint m_ui32IndexSize;
	private:
		uint m_ui32BufferID;
		BufferUsage	m_Usage;
		bool	m_bLocked;
	public:
		IndexBuffer(IndexType idxType, uint numIndexes,BufferUsage usage);
		~IndexBuffer();
	public:
		GLint		getGLBufferId();
	};

}
#endif