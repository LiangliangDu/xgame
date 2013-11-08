//==========================================================================
/**
* @file	  : IChatClient.h
* @author : 
* created : 2008-3-6   11:20
* purpose : ����ģ��ͻ��˽ӿڶ���
*/
//==========================================================================

#ifndef __ICHATCLIENT_H__
#define __ICHATCLIENT_H__

#include "ChatMsgDef.h"
#include "UserInfoDef.h"
#include <list>

/// ����ͻ���
struct IChatClient
{
	/** ����������Ϣ
	@param channelType	Ƶ�����ͣ��ο�ChatChannelType����
	@param msg			Ҫ���͵���������
    @param msg			Ҫ���͵�����ʱ�Ƿ���װ������ 
	@param target		˽��ʱ��Ŀ�����ݿ�ID����˽��ʱ���ò���û�����壬����0
	*/
	virtual void sendChatMessage(ulong channelType, const char* msg, const char* goodsTip, dbid target = 0,bool bOpen = false,ulong ulDuration = 0) const = 0;

	/** ����������Ϣ
	@param channelType	Ƶ�����ͣ��ο�ChatChannelType����
	@param msg			Ҫ���͵���������
	@param msg			Ҫ���͵�����ʱ�Ƿ���װ������
	@param target		˽��ʱ��Ŀ�����ݿ�ID����˽��ʱ���ò���û�����壬����0
	*/
	virtual void sendChatMessageByName(ulong channelType, const char* msg,const char* goodsTip,const char* name,ulong ulDuration = 0) const = 0;

	/** ���Ͷ�����Ϣ����
	@param channelType	Ƶ�����ͣ��ο�ChatChannelType����
	@param bSelected    �Ƿ�ѡ��		
	*/
	virtual void sendChatConfig(ulong channelType, bool bSelected) = 0;

	/** ��������λ��
	@param
	@param 
	@param 
	*/
	virtual void UpdatePaoPaoPlace(int nLeft,int nBottom,LONGLONG uid) = 0;

	/** Close����
	@param
	@param 
	@param 
	*/
	virtual void ClosePaoPaoFadeOutScreen(LONGLONG uid) = 0;

	/** Show����
	@param
	@param 
	@param 
	*/
	virtual void ShowPaoPaoFadeInScreen(LONGLONG uid) = 0;


	/** ���ϵͳ��Ϣ
	@param pos	ϵͳ��Ϣ��ʾλ��
	@param tips ��ʾ��Ϣ
	@param userData �û�����(������ʱ������0)
	*/
	virtual void addSystemInfo(ulong pos, const char* tips, ulong userData = 0, bool bErrMsg = false) const = 0;

	/** ���ϵͳ��Ϣ
	@param pos	ϵͳ��Ϣ��ʾλ��
	@param tips ��ʾ��Ϣ
	@param userData �û�����(������ʱ������0)
	*/
	virtual void addSystembroadcastInfo(ulong pos, ulong channelType,const char* tips, ulong userData = 0) const = 0;

	/** �������
	@param dbidPerson	���PID
	*/
	virtual void shieldPerson(dbid dbidPerson, bool bShield, const string& name) = 0;

	/** �Ƿ�����
	@param dbidPerson	���PID
	*/
	virtual bool isShield(dbid dbidPerson) = 0;

	virtual std::list<dbid> GetShieldList() = 0;

	virtual int GetShieldPlayerOnlineNum() = 0;

	virtual int GetShieldPlayerNum() = 0;

	virtual SShieldRecord GetShieldRecord(unsigned long dbidPerson) = 0;

	virtual		void  FilterChatMessage(char* lpchat) = 0; 

	virtual void release() = 0;

	virtual void Reset() = 0;

	// �Ƴ����������б��ڵ�����
	virtual void RemoveChatPaoPaoList(int nPaoPaoID) = 0;
};


#if defined(_LIB) || defined(CHATCLIENT_STATIC_LIB)/// ��̬��汾
#	pragma comment(lib, MAKE_LIB_NAME(xs_cct))
extern "C" IChatClient* LoadCCT(void);
#	define	CreateChatClientProc	LoadCCT
#	define  CloseChatClient()
#else /// ��̬��汾
typedef IChatClient* (RKT_CDECL *procCreateChatClient)(void);
#	define	CreateChatClientProc	DllApi<procCreateChatClient>::load(MAKE_DLL_NAME(xs_cct), "LoadCCT")
#	define  CloseChatClient()		DllApi<procCreateChatClient>::freelib()
#endif


#endif // __ICHATCLIENT_H__