//==========================================================================
/**
* @file	  : IMessageDispatch.h
* @author : 
* created : 2008-1-15   16:58
* purpose : ������Ϣ�ַ���
*/
//==========================================================================

#ifndef __IMESSAGEDISPATCH_H__
#define __IMESSAGEDISPATCH_H__

#include "IMessageHandler.h"

/**
	������Ϣ�ַ�������ӵײ��ȡ������Ϣ��Ȼ���ɷ���ָ����ģ����д���
*/


/// ��Ϣ�ַ���
struct IMessageDispatch
{
	/** �ַ�ָ������Ϣ
	@param buf ������������Ϣ����
	@param len ����������
	*/
	virtual void dispatchMessage(void* buf, size_t len) = 0;


	/** ע����Ϣ������
	@param moduleId ģ��ID���ο�InputMessage.h�е�ö�ٶ���
	@param hander ��Ϣ������ʵ��
	*/
	virtual void registerMessageHandler(ulong moduleId, IMessageHandler* handler) = 0;


	/** ע����Ϣ������
	@param moduleId ģ��ID���ο�DGlobalMessage.h�е�ö�ٶ���
	*/
	virtual void unregisterMessageHandler(ulong moduleId) = 0;
};



#endif // __IMESSAGEDISPATCH_H__