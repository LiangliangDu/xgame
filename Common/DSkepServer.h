/*******************************************************************
** �ļ���:	e:\Rocket\Server\SkepServer\Include\DSkepServer.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2008/3/3  22:28
** ��  ��:	1.0
** ��  ��:	ͨ��������Ʒ������
** Ӧ  ��:  	
	
**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once

#include "DGlobalGame.h"
#include "DGlobalMessage.h"

#pragma pack(1)

// ����ͨ����Ʒ���ֳ�
#define SKEPNAME_MAX_LEN	32
struct SBuildSkepClientContext
{
	DWORD		dwSkepID;						// ��Ʒ��ID
	DWORD		dwSkepType;						// ��Ʒ������
	DWORD		dwSkepName;						// ��Ʒ������
	DWORD		dwMaxSize;						// ��Ʒ����С
	DWORD		dwPopedom;						// ��Ʒ��Ȩ��
	DWORD		dwUsableBags;					// ����������--�ֿ�,����		
	char		szSkepName[SKEPNAME_MAX_LEN];	// ��Ʒ������

	// .....									// �ϲ�������չ����

	SBuildSkepClientContext(void)
	{
		memset(this, 0, sizeof(SBuildSkepClientContext));
	}
};

/******************************************************************/
///////////////////// ����������Ϊ�����Ϣ��////////////////////////
// �ϲ����Ϣ��ض���MSG_MODULEID_SKEP
/******************************************************************/
// ��������ͻ���֮����Ϣ������̳д���Ϣͷ
struct SMsgSkepCSCHead
{
	DWORD		dwSkepID;			// ��Ʒ��ID
};

///////////////////////////////////////////////////////////////////
// ������Ʒ�����ӣ����ӣ�
#define	MSG_SKEP_LINK												1
// ��Ϣ��
struct SMsgSkepLink_CS
{
	DWORD		dwSrcSkepID;		// Դ��Ʒ��ID
	DWORD		dwSrcPlace;			// Դλ��

	LONGLONG	uidGoods;			// ��ƷUID
	int			nNewPlace;			// ��λ�ã����Ϊ-1�����Զ���λ�ã�	

	SMsgSkepLink_CS(void)
	{
		memset(this, 0, sizeof(SMsgSkepLink_CS));
	};
};

///////////////////////////////////////////////////////////////////
// �����Ʒ
#define MSG_SKEP_SPLIT												2
// ��Ϣ��
struct SMsgSkepSplit_CS
{
	DWORD		dwPlace;			// λ��
	LONGLONG	uidGoods;			// ��ƷUID

	int			nSplitNum;			// ��ֳ���������

	SMsgSkepSplit_CS(void)
	{
		memset(this, 0, sizeof(SMsgSkepSplit_CS));
	}
};

///////////////////////////////////////////////////////////////////
// ʹ����Ʒ
#define MSG_SKEP_USE												3
// ��Ϣ��
struct SMsgSkepUse_CS
{
	DWORD		dwPlace;			// λ��
	LONGLONG	uidGoods;			// ��ƷUID
    LONGLONG    uidUser;            // ʹ����UID
	SMsgSkepUse_CS(void)
	{
		memset(this, 0, sizeof(SMsgSkepUse_CS));
	}
};

///////////////////////////////////////////////////////////////////
// �۲���
#define MSG_SKEP_OBSERVER											4
// ��Ϣ��
struct SMsgSkepObserver_CS
{
	bool		bOpen;				// true���۲� flase��ȡ���۲�

	SMsgSkepObserver_CS(void)
	{
		memset(this, 0, sizeof(SMsgSkepObserver_CS));
	}
};

// ��Ϣ��
struct SMsgSkepObserver_SC
{
	bool		bSuccess;			// true���۲�ɹ� flase���۲�ʧ��

	SMsgSkepObserver_SC(void)
	{
		memset(this, 0, sizeof(SMsgSkepObserver_CS));
	}
};


///////////////////////////////////////////////////////////////////
// ͬ���ͻ���
#define MSG_SKEP_SYNC												5
// ��Ϣ��
struct SMsgSkepSync_SC
{
	struct SMsgSyncSkepGoods
	{
		DWORD	dwPlace;			// λ��
		LONGLONG uidGoods;			// ��ƷUID��Ϊ��ЧUID����ʾɾ����λ�ã�
		DWORD   dwRelaySkepID;		// ��������Ʒ��ID
		bool	bLink;				// �Ƿ�����
	};

	// ................				// ���SMsgSyncSkepGoods
};

///////////////////////////////////////////////////////////////////
// ��Ʒ���޸Ĵ�С
#define MSG_SKEP_CHANGESIZE											6
// ��Ϣ��
struct SMsgSkepChangeSize_SC
{
	int			nMaxSize;			// ��Ʒ����С
};

///////////////////////////////////////////////////////////////////
// ͬ����Ʒ��Ȩ��
#define MSG_SKEP_SYNCPOPEDOM										7
// ��Ϣ��
struct SMsgSkepSyncPopedom_SC
{
	DWORD		dwPopedom;			// ��Ȩ��
};

///////////////////////////////////////////////////////////////////
// ������Ʒ��
#define MSG_SKEP_REALIGNMENT										8
// ��Ϣ��
struct SMsgSkepReAlignment_SC
{
	DWORD		dwPopedom;			// ���� lilinll77
};

///////////////////////////////////////////////////////////////////
//��Ʒ��������Ʒ������ʾ������ ����װ���ĸ��꣬��ʯ��Ƕ��������
#define MSG_SKEP_SETCURSUBSKEP                                      9
//��Ϣ��
struct SMsgSkepSetCurSubskep_SC
{
	ushort ucSubskepName; //����Ʒ������
	bool bShow;//��ʾ��������
	//һ����Ϣ�����ܹ����������������Ϣ�ṹ
};
///////////////////////////////////////////////////////////////////
//������Ʒ(����)
#define MSG_SKEP_DROPOUT											10
//��Ϣ��
struct SMsgSkepDropOut_CS
{
	DWORD		dwPlace;			// λ��
	LONGLONG	uidGoods;			// ��ƷUID
	bool		bDestroy;			// by cjl�Ƿ�ֱ������

	SMsgSkepDropOut_CS(void)
	{
		memset(this,0,sizeof(SMsgSkepDropOut_CS));
	};
};

// ʹ�ø������
#define  MSG_SKEP_USE_RELIVE_BOOK									11

///////////////////////////////////////////////////////////////////
//��������
#define MSG_SKEP_OPENBAG		                                    12
//��Ϣ��
struct SMsgSkepOpenBag_CS
{
	DWORD		dwPlace;			// λ��
};
struct SMsgSkepOpenBag_SC
{
	DWORD		dwPlace;			// λ��
};

// �������������ñ��е���Ʒ����ID
#define  RELIVE_BOOK_GOOD_ID								4000

#pragma pack()