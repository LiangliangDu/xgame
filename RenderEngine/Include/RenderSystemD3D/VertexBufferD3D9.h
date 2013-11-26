#ifndef __VertexBufferD3D9_H__
#define __VertexBufferD3D9_H__

#include "D3D9ResourceManager.h"

namespace xs
{

	class BufferManagerD3D9;
	class VertexBufferD3D9;

	class VertexBufferD3D9Creater
	{
	public:
		static VertexBufferD3D9 * create(BufferManagerD3D9 * pBufferMgr, uint vertexSize, uint numVertices, BufferUsage usage, CreateBufferFlag flag);
	};

	class VertexBufferD3D9: public IVertexBuffer, public D3D9Resource
	{
		//IVertexBuffer�ӿ�
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
		virtual void *	lock(uint offset,uint length,LockOptions options) ;

		/** ��������������lock����ʹ��
		*/
		virtual void 	unlock();

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
		virtual IVertexBuffer*	clone();

		//D3D9Resource �ӿ�
	public:

		// �豸��ʧ���������ͷ�Default Pool�������Դ
		virtual void notifyOnDeviceLost();

		//�豸�ָ�, �������ؽ�Default Pool �������Դ
		virtual void notifyOnDeviceReset();

	public:
		inline IDirect3DVertexBuffer9 * getD3DVertexBuffer9() { return m_pVB; }

	private:
		friend class VertexBufferD3D9Creater;
		bool create(BufferManagerD3D9 * pBufferMgr, uint vertexSize, uint numVertices, BufferUsage usage, CreateBufferFlag flag );
		VertexBufferD3D9();
		~VertexBufferD3D9();
		
	private:
		IDirect3DVertexBuffer9 *	m_pVB;				//����buffer
		uint						m_uiVertexSize;		//�����С	
		uint						m_uiNumVertices;	//��������
		uint						m_uiSizeInBytes;	//buffer�Ĵ�С
		BufferUsage					m_eUsage;			//buffer���ʹ��
		BufferManagerD3D9 *			m_pBufferMgr;		//buffer������
		D3DVERTEXBUFFER_DESC		m_bufferDesc;		//buffer������
		bool						m_bIsLocked;		//�Ƿ�Locked
	};
}
#endif