/*******************************************************************
** �ļ���:	ILoginServerProtocol.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** ������:	
** ��  ��:	03/08/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __INTERFACE_LOGIN_SERVER_PROTOCOL_H__
#define __INTERFACE_LOGIN_SERVER_PROTOCOL_H__

#pragma pack(1)
#pragma warning(disable:4200)

namespace xs
{
#	define  MAX_USERNAME_LEN      32
#	define  MAX_PASSWORD_LEN      32
#	define  MAX_ACTORNAME_LEN     32
#	define  APPERANCE_DATA_LEN    65
#	define	MAX_CREATE_ACTOR_NUM  10 //����ܴ���10����ɫ
#	define  MAX_ACTOR_NUM         30 //�������Ϳͻ����ܹ���¼�Ľ�ɫ��������������ڻ�Ϸ������������������10�� 

/**
@name : ��½������Э�鶨��
@brief: ��½����������:
		1.�ʺŹ���: ע��/��֤/ɾ�� (ע���ɾ��������WEB����)
		2.��ɫ����: ����/ѡ��/ɾ��
		3.��½�Ŷ�
		4.�����/��ȫ�ύ����

		��ȫ��½����:
		1.����ڶ������֮���л�ʱ�������֤���� 
		(���Ǩ����Ϣֻ���ڷ�����֮�䷢,��Ϊ�ͻ������ӱ����������ϲ���Ͽ�,���Բ������û��ʲô����,
		�������ݿ���Ҫ�Խ�ɫ��¼���мӽ���,��ֹ��������Խ�ɫ���ݽ��д�ȡʱ���ֻص�����)

		2.���밲ȫ����-��ֹ��������
		(��ֹ�����м��ְ취,����ͻ���ʹ�� RSA Public-key��������,������ʹ��private-key�⿪.
		��Public-keyʹ�ù���Ƶ��(����һ��һ��),���ܻ�Ӱ������㷨�Ľ�׳��
		����ķ�������ʹ��Diffie Hellman��ȫ��������,��������һ��һ��
		��������������ܵ��м��˹���,��A-B����ͨѶ,Cαװ��A��BͨѶ,ͬʱ��αװ��B��AͨѶ,�Ӷ���ȡ����,
		���ǵ�������ͨѶ��ͳһ����������,������ʱʹ��Diffie Hellman����һ��һ��,�����½�������ڽ��յ�½��Ϣʱʹ��RSA˽Կ���������ַ���)

		3.���밲ȫ����-��ֹ�ͻ������봰�ڱ�����
		������Բ�������̻���,����Ҫע������̵�ͼ��Ͳ��ֱ����ɷ�����������,�ͻ�����Զ�����������ַ���

		4.����ʹ������̻����Ǿ��԰�ȫ��,����ɾ����ɫ,�ߵȼ���װ��ת��ǿ��Ҫ��ʹ�����������2����������Խ����ŵ�Σ��������С
*/

	//////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************** ��½�������Ϳͻ���֮���ͨѶЭ�� **********************************/
	//////////////////////////////////////////////////////////////////////////////////////////////////

	enum
	{
		NoError     = 0 , // û�д���,�������ʾ��Ϣ
		LoginError      , // ��½����
		CreateActorError, // ������ɫ����
		DeleteActorError, // ɾ����ɫ����
		SelectActorError, // ѡ���ɫ����
		RecoverActorError,	//�ָ���ɫ����
	};

	/**
	@name         : ��½��ʾ
	@brief        : ��½������ͨ�õ���ʾ��Ϣ,����������ʾ��½ʧ��,�����ڵ�½ʱ�����ͻ��˵�½�����
	*/
#	define   MSG_LOGINSERVER_MESSAGE        1

	/**
	@name         : ��½��ʾ
	@brief        : ��½�����������Ա�������ʾ��Ϣ����Ϣ����MSG_LOGINSERVER_MESSAGE ͬ��SMsgLoginServer_Message
	*/
#	define   MSG_LOGINSERVER_ENTHRALLPROTECT_MESSAGE        2

	struct SMsgLoginServer_Message
	{
		DWORD  dwErrorCode;                   // ������
		WORD   wMsgLen;                       // ��ʾ��Ϣ����
        char   szMessage[];                   // ��ʾ��Ϣ����
	};


	/**
	@name         : �����¼
	@brief        : �ӷ������������
	*/
#	define    MSG_REGUESTLOGINSERVER_LOGIN         16
	struct SMsgReguestLoginServer_Login
	{
		DWORD          dwReserve;                     // �����ֶ�,��ʱ����,���������
		unsigned short nLength;
		unsigned char  nMsgId;
		unsigned char  token[32];

	};

#    define   MSG_SESSIONKEY                        17
	struct SMsgSessionKey
	{
		DWORD          dwReserve;                     // �����ֶ�,��ʱ����,���������
		unsigned short nLength;
		unsigned char  nMsgId;
		unsigned char  keyId;
		unsigned char  keyLen;
		unsigned char  sessionkey[64];

	};



	/**
	@name         : �����½
	@brief        : ���ⲻ��1��ͷ,���ⱻ�²�,��Ϣ����ΪRSA��Կ���ܹ��������,�����ݽ��ܺ�ΪSMsgLoginServer_Login�ṹ
	@return       : ��½�ɹ��򷵻ؽ�ɫ��Ϣ(MSG_LOGINSERVER_ACTOR_INFO),���򷵻ش�����ʾ(MSG_LOGINSERVER_MESSAGE)
	*/
#	define    MSG_LOGINSERVER_LOGIN         25

	struct SMsgLoginServer_Login
	{
		DWORD          dwReserve;                     // �����ֶ�,��ʱ����,���������
		unsigned short nLength;
		unsigned char  nMsgId;
		//unsigned char  g_srandKey[8];
		unsigned short userLength;
		char           szUserName[MAX_USERNAME_LEN];  // �û��ʺ�
		unsigned short pwLength;
		char           szPassword[MAX_PASSWORD_LEN];  // �û�����

	};

	/**
	@name         : ��ɫ��Ϣ
	@brief        : ��½�ɹ�������ɾ��ɫ����½�ɫ��Ϣ
	*/
#	define   MSG_LOGINSERVER_ACTOR_INFO     27

	struct SMsgLoginServer_ActorInfo
	{
		struct ActorInfo
		{
			DWORD dwNakedResId;						//����������Դid
			DWORD dwFaceID;                        // ͷ��
			char  szActorName[MAX_ACTORNAME_LEN];  // ��ɫ��			
			BYTE  nLevel;                          // �ȼ�
			BYTE  nSex;                            // �Ա�
			BYTE  nNation;                         // ����
			BYTE  nProfession;                     // ְҵ	
			char  pAppearance[APPERANCE_DATA_LEN]; // װ���б�	
			int   nCreateTime;						//��ɫ����ʱ��
			BYTE  nDeleteFlag;						//ɾ����־�������0���ʾ��ɫ�Ѿ�ɾ
			int   nDeleteTime;				//ɾ��ʱ��,�����1970��
			int	  nAccessTmie;				//��ɫ����ʱ�䣬�����1970�꣬��ɾ��ʱ��֮��õ�ɾ�����
		};
		time_t tSeverTimer;                 // ������ʱ��
		WORD   wActorNum;						// ��ɫ����
        ActorInfo  m_ActorInfo[MAX_ACTOR_NUM]; // ��ɫ��Ϣ
	};

	/**
	@name         : ������ɫ
	@brief        : ��Ϣ�ṹ��SMsgLoginServer_CreateActor
	@return       : �����ɹ��򷵻ؽ�ɫ��Ϣ(MSG_LOGINSERVER_ACTOR_INFO),�����ʹ�����ʾ(MSG_LOGINSERVER_MESSAGE)
	*/
#	define    MSG_LOGINSERVER_CREATE_ACTOR  28

	struct SMsgLoginServer_CreateActor
	{
		char  szActorName[MAX_ACTORNAME_LEN];  // ��ɫ��
		DWORD dwFaceID;                        // ͷ��ID
		BYTE  nSex;                            // �Ա�
		BYTE  nNation;                         // ����
		BYTE  nProfession;                     // ְҵ
		DWORD	dwNakedResId;					//����������Դid����Ӧcreature���ñ�
	};
 
	/**
	@name         : ɾ����ɫ 
	@brief        : ��Ϣ�ṹ��SMsgLoginServer_DeleteActor
	@return       : ɾ���ɹ��򷵻ؽ�ɫ��Ϣ(MSG_LOGINSERVER_ACTOR_INFO),�����ʹ�����ʾ(MSG_LOGINSERVER_MESSAGE)
	*/
#	define   MSG_LOGINSERVER_DELETE_ACTOR  29

	struct SMsgLoginServer_DeleteActor
	{
		char szActorName[MAX_ACTORNAME_LEN];  // Ҫɾ���Ľ�ɫ��
	};

	/**
	@name         : ѡ���ɫ
	@brief        : ��Ϣ�ṹ��SMsgLoginServer_SelectActor
	@return       : ѡ��ɫ�ɹ�,��Ⱥ���������������ͼ����Ϣ,����������ᷢ�ʹ�����ʾ(MSG_LOGINSERVER_MESSAGE)
	*/
#	define  MSG_LOGINSERVER_SELECT_ACTOR   30

	struct SMsgLoginServer_SelectActor
	{
		char szActorName[MAX_ACTORNAME_LEN];  // Ҫɾ���Ľ�ɫ��
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////
	/**************************** ��½�������ͳ���������֮���ͨѶЭ�� ******************************/
	//////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	@name         : ��½������֪ͨ����������������ɫ
	@brief        : ע��: ������Ϣ�ǵ�½����������������������,���ݽṹ��SMsgLoginServer_EnterGameWorld
	*/
#	define MSG_LOGINSERVER_ENTER_GAMEWORLD      31

	struct SMsgLoginServer_EnterGameWorld
	{
		DWORD    dwActorDBID;             // ��ɫ���ݿ�ID
		DWORD    dwClientID;              // �ͻ���ID(����)
		char	 szClientIP[16];		  // �ͻ���IP
	};

	/**
	@name         : ����֪ͨĳ���û�����
	@brief        : ���ݰ��ṹSMsgLoginServer_Reconnect
	*/
#	define MSG_LOGINSERVER_RECONNECT            32

	struct SMsgLoginServer_Reconnect
	{
		DWORD    dwClientID;              // �ͻ���ID(����)
		DWORD    dwServerID;              // ������ID
	};
};

//////////////////////////////////////////////////////////////////////////////////////////////////
/**************************** ��½�������Ϳͻ���֮���ͨѶЭ�� **********************************/
//////////////////////////////////////////////////////////////////////////////////////////////////

/**
@name         : �ͻ��˻ָ���ɫ
@brief        : ��Ϣ�ṹ��SMsgLoginServer_ClientRecoverActor
@return       : �ָ��ɹ������½�ɫ�б�ֻ���ڿͻ��˻ָ�������������ᷢ�ʹ�����ʾ(MSG_LOGINSERVER_MESSAGE)
*/
#	define  MSG_LOGINSERVER_RECOVER_ACTOR   33

struct SMsgLoginServer_RecoverActor
{
	char szActorName[MAX_ACTORNAME_LEN];  // Ҫ�ָ��Ľ�ɫ��
};


// ����Ϣ�����Ƶ�DGlobalMessage.h ��������������µĺ꣬�ǵò�Ҫ��MSG_CLIENT_LOGOUT�ȵ�ֵ��ͬ
// /**				�ͻ������������˳���¼��			
// @name         : �˳���¼
// ע�⣬���ݵ�ǰ�������ļܹ�������Ϣ��ʵ�Ƿ�������MSG_ENDPOINT_GATEWAY�����������������Ϣ���Ա�Ͽ���ͻ��˵�����
// @brief        : 
// @return       : 
// **/
// #	define    MSG_CLIENT_LOGOUT           34
// 
// 
// /* �ͻ�����������Ϸ���ؽ�ɫѡ�����еĽ�ɫ��Ϸ�߼����жϣ����·��ؽ�ɫ��Ϣ
// */
// #	define   MSG_RE_SELECT_ACTOR         35
// struct SMsgReSelectActor_SS
// {
//	DWORD dwClientID; //�ͻ������ش�ID
// };


/**
@name         : ��¼�Ŷ�֪ͨ
@brief        : ��Ϣ�ṹ��SMsgLoginServer_QueueUpdate
*/
#	define  MSG_LOGINSERVER_QUEUEUPDATE      36

struct SMsgLoginServer_QueueUpdate
{
	int nPlace; //������λ��
	int nRestTime; //Ԥ���Ŷ�ʱ��
};

// /* �ͻ��˼��ص�ͼ�ɹ���������������ɫPerson��ϣ�ת�뵽PLAY״̬
// */
 #	define   MSG_ACTOR_GO_TO_PLAY_STATE   37
 struct SMsgActorGotoPlayState_SS
 {
 	DWORD dwClientID; //�ͻ������ش�ID
 };

/*	��������������gm�ͻ���
*/
#define	MSG_ACTOR_SHOW_CLIENT_COUNT		40
struct SMsgActorShowClientCount_SC
{
	DWORD dwClientCount;
};

#define MSG_ACTOR_RENAME_RESULT			41
struct SMsgActorReNameResult_SC			
{
	WORD wMsgLen;						//��ʾ��Ϣ����
	char  szResult[];					//��ʾ��Ϣ
};

#pragma pack()

#endif//__INTERFACE_LOGIN_SERVER_PROTOCOL_H__