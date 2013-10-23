#ifndef __I_BufferManager_H__
#define __I_BufferManager_H__

namespace xs
{
	/*! addtogroup RenderEngine
	*  ��Ⱦ����
	*  @{
	*/

/** ���㻺�����ӿ�
*/
struct IVertexBuffer
{
	/** �ͷŶ��㻺��������
	*/
	virtual void 	release() = 0;

	/** ��ö����С��ÿ������ռ�õ��ֽ���
	@return �����С
	*/
	virtual uint	getVertexSize() const = 0;

	/** ��ö��������
	@return ��������
	*/
	virtual uint	getNumVertices() const = 0;

	/** Buffer��ʹ�÷�ʽ
	@return Buffer��ʹ�÷�ʽ
	@see BufferUsage
	*/
	virtual BufferUsage	getUsage() const = 0;

	/** ������������������ݵ�ָ�룬�Ӷ����Բ�������
	@param offset �����ݿ�ʼ��ƫ��ֵ
	@param length ���������򳤶�
	@param options �����ķ�ʽ
	@see LockOptions
	@return ������ָ��
	*/
	virtual void *	lock(uint offset,uint length,LockOptions options) = 0;

	/** ��������������lock����ʹ��
	*/
	virtual void 	unlock() = 0;

	/** ��ȡ�������Ƿ��ڱ�����״̬
	@return true��������������falseδ����
	*/
	virtual bool	isLocked() = 0;

	/** �ӻ�������ȡ���ݣ��ŵ�ָ���Ļ���
	@param offset �����ݿ�ʼ��ƫ��ֵ
	@param length Ҫ��ȡ�����ݳ���
	@param pDest Ŀ�껺������ַ
	*/
	virtual void 	readData(uint offset,uint length,void * pDest) = 0;	

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
	bool discardWholeBuffer = false) = 0;

	/** ��¡���㻺���������ݣ��û����𷵻صĶ��㻺�����������������
	@return ��¡�����Ķ��㻺����
	*/
	virtual IVertexBuffer*	clone() = 0;
};																	

/** �����������ӿ�
*/

struct IIndexBuffer
{
	/** ����������������ͣ��ο�IndexTypeö������
	@see IndexType
	@return ����������
	*/
	virtual IndexType	getType(void ) const = 0;							

	/** ��ȡ����������
	@return ����������
	*/
	virtual uint		getNumIndices(void ) const = 0;						

	/** ��������ĳ���(�ֽ�)
	@return ÿ�������ĳ��ȣ�һ��Ϊ2,4
	*/
	virtual uint		getIndexSize(void ) const = 0;						

	/** ���������������ʹ�÷�ʽ���ο�BufferUsage
	@see BufferUsage
	@return ������������ʹ�÷�ʽ
	*/
	virtual BufferUsage	getUsage() const = 0;

	/** ��������������������ֱ�Ӵ�ȡ����
	@param offset �����ݿ�ʼ��ƫ�ƣ��ֽڣ�
	@param length Ҫ�������������ĳ���
	@param options �����ķ�ʽ
	@see LockOptions
	@return ֱ�����ݵĵ�ַ
	*/
	virtual void *		lock(uint offset,uint length,LockOptions options) = 0;						

	/** ��������������lock����ʹ��
	*/
	virtual void 		unlock() = 0;		

	/** ��ȡ�����������Ƿ��ڼ���״̬
	@return true��ʾ���ڼ���״̬��false��δ����
	*/
	virtual bool		isLocked() = 0;		

	/** �ͷŻ���������
	*/
	virtual void 		release() = 0;		

	/** �ӻ�������ȡ���ݣ��ŵ�ָ���Ļ���
	@param offset �����ݿ�ʼ��ƫ��ֵ
	@param length Ҫ��ȡ�����ݳ���
	@param pDest Ŀ�껺������ַ
	*/
	virtual void 	readData(uint offset,uint length,void * pDest) = 0;	

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
		bool discardWholeBuffer = false) = 0;
};

class VertexDeclaration;
class VertexBufferBinding;

/** ����������ӿ�
*/
enum	CreateBufferFlag
{
	CBF_DEFAULT = 0x0,//Ĭ��
	CBF_IMMEDIATE = 0x1,//����������������Ⱦѭ��Ӱ��
};

struct IBufferManager
{
	/** �������㻺����
	@param vertexSize ÿ����������ݳ���(�ֽ�)
	@param numVertices ���������
	@param usage ��������ʹ�÷�ʽ���ο�BufferUsage
	@param flag ����ѡ��
	@see BufferUsage
	@return ���㻺�����ӿ�
	*/
	virtual IVertexBuffer*	createVertexBuffer(uint vertexSize,uint numVertices,BufferUsage usage, CreateBufferFlag flag = CBF_DEFAULT) = 0;

	/** ��������������
	@param itype ��������
	@see IndexType
	@param numIndices ����������
	@param usage ��������ʹ�÷�ʽ
	@param flag	����ѡ��
	@see BufferUsage
	@return �����������ӿ�
	*/
	virtual IIndexBuffer*	createIndexBuffer(IndexType itype,uint numIndices,BufferUsage usage, CreateBufferFlag flag = CBF_DEFAULT) = 0;	

	/** ��������Ķ���
	@param itype ��������
	@see IndexType
	@param numIndices ����������
	@param usage ��������ʹ�÷�ʽ
	@see BufferUsage
	@return �����������ӿ�
	*/
	virtual VertexDeclaration* createVertexDeclaration() = 0;				

	/** �������㻺������
	@return ���㻺������ָ��
	*/
	virtual VertexBufferBinding* createVertexBufferBinding() = 0;			

	/** ���ٶ��㶨��
	@param decl ���㶨��
	*/
	virtual void  destroyVertexDeclaration(VertexDeclaration* decl) = 0;		

	/** ���ٶ��㻺������
	@param binding ���㻺������
	*/
	virtual void  destroyVertexBufferBinding(VertexBufferBinding* binding) = 0;
};
	/** @} */

}
#endif