//==========================================================================
/**
* @file	  : IMessageHandler.h
* @author : 
* created : 2008-1-15   16:51
* purpose : ������Ϣ������
*/
//==========================================================================

#ifndef __IMESSAGEHANDLER_H__
#define __IMESSAGEHANDLER_H__

#include "DGlobalMessage.h"


/// ������Ϣ������
struct IMessageHandler
{
	/** ��Ϣ����
	@param msg ������Ϣ
	*/
	virtual void onMessage(ulong actionId, SGameMsgHead* head, void* data, size_t len) = 0;
};


#endif // __IMESSAGEHANDLER_H__