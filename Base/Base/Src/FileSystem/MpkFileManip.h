#ifndef __MPKFILEMANIP_H__
#define __MPKFILEMANIP_H__

#include "IMpkManip.h"
#include "MpkLib.h"

namespace xs{

class MpkFileManip : public IMpkFileManip
{
public:
	/**�ͷ��Լ�
	@param
	@param
	@return
	@remarks
	*/
	virtual void release();

	/**��ȡ����
	@param pBuffer ���ݻ�����
	@param size Ҫ��ȡ�����ݳ���
	@return �Ƿ��ȡ�ɹ�
	@remarks
	*/
	virtual bool read(void *pBuffer,uint size);

	/**��λ�ļ�λ��
	@param length ƫ����
	@param from �����￪ʼ,SEEK_SET��
	@return �Ƿ�ɹ�
	@remarks
	*/
	virtual bool seek(uint length,uint from);

	/**��õ�ǰ�ļ�ָ��
	*/
	virtual uint getPos();

	/**�ļ���С
	@param
	@param
	@return �ļ���С
	@remarks
	*/
	virtual uint size();

	/**���ԭʼ�ļ���С
	@param
	@param
	@return ԭʼ�ļ���С
	@remarks
	*/
	virtual uint getOriginSize();

	/**���ѹ������ļ���С
	@param
	@param
	@return ѹ������ļ���С
	@remarks
	*/
	virtual uint getCompressedSize();

	/**�Ƿ����
	@param
	@param
	@return �Ƿ����
	@remarks
	*/
	virtual bool isEncrypted();
private:
	HANDLE m_hFile;
public:
	MpkFileManip(void* hFile);
};

}

#endif