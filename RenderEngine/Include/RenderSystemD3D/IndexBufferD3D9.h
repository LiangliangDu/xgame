#ifndef __IndexBufferD3D9_H__
#define __IndexBufferD3D9_H__

#include "D3D9ResourceManager.h"

namespace xs
{
	class IndexBufferD3D9;
	class BufferManagerD3D9;

	class IndexBufferD3D9Creater
	{
	public:
		static IndexBufferD3D9 * create(BufferManagerD3D9 * pMgr,IndexType itype,uint numIndices,BufferUsage usage, CreateBufferFlag flag );
	};

	class IndexBufferD3D9 : public IIndexBuffer,  public D3D9Resource
	{
		//IIndexBuffer�ӿ�
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

		//D3D9Resource�ص��ӿڣ���Ҫ��������Щ������ʹ��D3D9ResourceManager�ķ�������
	public:

		// �豸��ʧ���������ͷ�Default Pool�������Դ
		virtual void notifyOnDeviceLost();

		//�豸�ָ�, �������ؽ�Default Pool �������Դ
		virtual void notifyOnDeviceReset();

	public:
		inline IDirect3DIndexBuffer9 * getD3DIndexBuffer9() { return m_pIB; }

	private:
		friend class IndexBufferD3D9Creater;
		IndexBufferD3D9();
		~IndexBufferD3D9();
		bool create(BufferManagerD3D9 * pMgr,IndexType itype,uint numIndices,BufferUsage usage, CreateBufferFlag flag );
	private:
		BufferManagerD3D9 *		m_pBufferMgr;	//buffer������
		IDirect3DIndexBuffer9 * m_pIB;			//index buffer
		IndexType				m_eIndexType;	//��������
		uint					m_uiNumIndices;	//��������
		uint					m_uiIndexSize;	//�����Ĵ�С
		BufferUsage				m_eUsage;		//bufferʹ�÷�ʽ
		D3DINDEXBUFFER_DESC		m_bufferDesc;	//buffer����
		bool					m_bIsLocked;	//�Ƿ�����
	};
}
#endif