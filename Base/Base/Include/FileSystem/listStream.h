#ifndef __ListStream_H__
#define __ListStream_H__

namespace xs{
	/*! \addtogroup FileSystem
	*  �ļ�ϵͳ
	*  @{
	*/


/// ö����Callback
struct IListFileCallback
{
	/**ö�������ļ��Ļص�
	@param strFilename �ļ���
	@param p �Զ������
	@see IMpkManip
	*/
	virtual void onGetStreamName(const char* strName,void *p) = 0;
};

	/** @} */
}

#endif