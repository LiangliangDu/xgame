/*******************************************************************
** ��  Ȩ:	(C) 
** ������:
** ��  ��:	2008/5/5  15:56
** ��  ��:	1.0
** ��  ��:
** Ӧ  ��:  	
	
**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#ifndef __DTradeMessage_H__
#define __DTradeMessage_H__

#include "DGlobalGame.h"
#include "DGlobalMessage.h"

#pragma pack(1)

/******************************************************************/
// �ϲ����Ϣ��ض���MSG_MODULEID_TRADE
/******************************************************************/

///////////////////////////////////////////////////////////////////
//������
#define	MSG_TRADE_REQUEST											1
// ��Ϣ��
///////////////////////////////////////////////////////////////////
//
struct SMsgTradeRequest_CS
{
	LONGLONG	uidTarget;
};

struct SMsgTradeRequest_SC
{
	LONGLONG	uidDemander;
};

///////////////////////////////////////////////////////////////////
//���ܽ���
#define	MSG_TRADE_ACCEPT											2
// ��Ϣ��
///////////////////////////////////////////////////////////////////
//
struct SMsgTradeAccept_CS
{
	LONGLONG	uidTarget;
};

///////////////////////////////////////////////////////////////////
//�ܾ�����
#define	MSG_TRADE_REFUSE											3
// ��Ϣ��
///////////////////////////////////////////////////////////////////
//
struct SMsgTradeRefuse_CS
{
	LONGLONG uidTarget;
};

struct SMsgTradeRefuse_SC
{
};

///////////////////////////////////////////////////////////////////
//��ʼ����
#define	MSG_TRADE_GO												4
// ��Ϣ��
///////////////////////////////////////////////////////////////////
//
struct SMsgTradeGo_SC
{
	//�Է���UID
	LONGLONG	uidTarget;

	//�Լ��Ľ�����Ʒ��ID
	ulong		skepId;

	//�Է��Ľ�����Ʒ��ID
	ulong		skepIdTarget;
};

///////////////////////////////////////////////////////////////////
//�ı��Ǯ
#define	MSG_TRADE_UPDATE_MONEY										5
// ��Ϣ��
///////////////////////////////////////////////////////////////////
//
struct SMsgTradeUpdateMoney_CS
{
	ulong money;
};

struct SMsgTradeUpdateMoney_SC
{
	ulong money;
};

///////////////////////////////////////////////////////////////////
//ȡ������
#define	MSG_TRADE_CANCEL											6
// ��Ϣ��
///////////////////////////////////////////////////////////////////
//
struct SMsgTradeCancel_CS
{
};

struct SMsgTradeCancel_SC
{
	//��˭ȡ���˽��ף��п������Լ�
	LONGLONG	uid;
};

///////////////////////////////////////////////////////////////////
//��������
#define	MSG_TRADE_LOCK												7
// ��Ϣ��
///////////////////////////////////////////////////////////////////
//
struct SMsgTradeLock_CS
{
};

struct SMsgTradeLock_SC
{
	//�Լ���״̬���ǶԷ���״̬
	bool	myself;
	//�������ǽ���
	bool	lock;
};

///////////////////////////////////////////////////////////////////
//ȷ�Ͻ���
#define	MSG_TRADE_CONFIRM											8
// ��Ϣ��
///////////////////////////////////////////////////////////////////
//
struct SMsgTradeConfirm_CS
{
	ulong	skepId;
	ulong	money;
	ulong	gold;
};

struct SMsgTradeConfirm_SC
{
	bool myself;
};

///////////////////////////////////////////////////////////////////
//��ɽ���
#define	MSG_TRADE_FINISH											9
// ��Ϣ��
///////////////////////////////////////////////////////////////////
//
struct SMsgTradeFinish_SC
{
};

///////////////////////////////////////////////////////////////////
//��������
#define	MSG_TRADE_UNLOCK												10
// ��Ϣ��
///////////////////////////////////////////////////////////////////
//
struct SMsgTradeUnLock_CS
{
};

struct SMsgTradeUnLock_SC
{
	//�Լ���״̬���ǶԷ���״̬
	bool	myself;
	//�������ǽ���
	bool	lock;
};

///////////////////////////////////////////////////////////////////
//�ı�Ԫ��
#define	MSG_TRADE_UPDATE_GOLD											11
// ��Ϣ��
///////////////////////////////////////////////////////////////////
struct SMsgTradeUpdateGold_CS
{
	ulong gold;
};

struct SMsgTradeUpdateGold_SC
{
	ulong gold;
};

#pragma pack()

#endif