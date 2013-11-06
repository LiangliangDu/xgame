//==========================================================================
/**
* @file	  : ChatMsgDef.h
* @author : 
* created : 2008-3-7   18:50
* purpose : ������Ϣ����
*/
//==========================================================================

#ifndef __CHATMSGDEF_H__
#define __CHATMSGDEF_H__

/**
	����ģ�����������ҵ������¼���

	��¼/�ǳ�/Ǩ��
	����/�˳�����
	����/�˳�����
	����/�˳�����
	������Ϣ
	Ȩ�޸ı���Ϣ
*/

#define MAX_CHAT_MSG_LENGTH		3072
#define MAX_CHAT_PAOPAO_DIS       18

/// ϵͳ��Ϣ����������Ϣ��λ�ö���
enum InfoPos
{
	InfoPos_ChatWindow,				/// �����(������Ϣ)
	InfoPos_FightChatWindow,		/// �����(ս����Ϣ)
	InfoPos_ScreenTopAD,			/// ��Ļ�ö���Ϣ��ʾ(�ö�������Ϣ)
	InfoPos_ScreenAboveTip,			/// ��Ļ�Ϸ���Ϣ��ʾ(�Ƚ�ɫ�Ϸ��ߵ� ��Ϣ��ʾ)
	InfoPos_ScreenRightAboveTip_1,	 /// ��Ļ���Ϸ���Ϣ��ʾ
	InfoPos_ScreenRightAboveTip_2,   /// ��Ļ���Ϸ���Ϣ��ʾ2
	InfoPos_ActorAbove,		 /// ��ɫ�Ϸ�
	InfoPos_ActorUnder,		 /// ��ɫ�·�
	InfoPos_ActorRight,		 /// ��ɫ�ҷ�
	InfoPos_ScreenRight,	 /// ��Ļ�ҷ�
	InfoPos_MouseInfo,		 /// ��������Ϣ
	MaxInfoPosCount,		/// ���λ����
};

/// ����Ƶ������
enum ChatChannelType
{
	ChatChannel_Map = 1,	/// ��ͼƵ��
	ChatChannel_Around,		/// ��ΧƵ��
	ChatChannel_Army,		/// ����Ƶ��
	ChatChannel_Family,		/// ����Ƶ��
	ChatChannel_Team,		/// ����Ƶ��
	ChatChannel_Private,	/// ����Ƶ��
	ChatChannel_Tips,		/// ϵͳ��ʾƵ����ֻ�����Լ��Ŀͻ���
	ChatChannel_System,	    /// ϵͳƵ��
	ChatChannel_World,	    /// ����Ƶ��

	MaxChatChannelCount,	/// ���Ƶ����
};

/// ������Ϣ����
enum
{
	//////////////////////////////////////////////////////////////////////////
	// �ͻ��� -> ���������(ע�������ط�������ת)
	//////////////////////////////////////////////////////////////////////////

	/// ����������Ϣ	�����ģ�(dbid sender, ulong channelType, [dbid target,] const char* chatText)
	/// �����˽��Ƶ������Ҫ���target
	ChatMsg_Send,


	/// �޸��������ã����˶�ĳƵ����Ϣ �����ģ�(dbid user, ulong channelType, bool val)
	ChatMsg_Config,




	//////////////////////////////////////////////////////////////////////////
	// ����������򳡾������� -> �ͻ���(ע�������ط�������ת)
	//////////////////////////////////////////////////////////////////////////

	/// ������Ϣ����	�����ģ�(dbid sender, UID uid, ulong channelType, const char* name, const char* chatText)
	ChatMsg_Arrived,

	/// ����ʧ��		�����ģ�(dbid uid, const char* failReason)
	ChatMsg_Failed,

	/// ϵͳ��ʾ��Ϣ����(�ȷ�����ģ����ʵ��)	�����ģ�(ulong pos, const char* tips, ulong userData)
	ChatMsg_SystemInfo,

	/// ϵͳ�㲥��Ϣ����()
	ChatMsg_SystembroadcastInfo,

	/// ϵͳ��ʾ��Ϣ�رղ���(�߻����󣬷���˿��ƹر�ĳЩ�ض�λ�õ���ʾ��Ϣ��)
	ChatMsg_CloseSystemInfo,

	//////////////////////////////////////////////////////////////////////////
	// ���������� -> ���������(ע�������ķ�������ת)
	//////////////////////////////////////////////////////////////////////////

	///	�û���¼	�����ģ�(UseraInfo* info)
	ChatMsg_UserLogin,

	///	�û��ǳ�	�����ģ�(dbid user)
	ChatMsg_UserLogoff,

	///	�û��л�������¼	�����ģ�(UseraInfo* info)
	ChatMsg_UserChangeServerLogin,

	///	�û��л������ǳ�	�����ģ�(dbid user)
	ChatMsg_UserChangeServerLogoff,

	/// �û���Ϣ�ı�	�����ģ�(UseraInfo* info) ��Ҫ������������ң�������壬�����������飬�û�������Ȩ�ޱ���������л�
	ChatMsg_InfoChanged,

	/// ϵͳ��ָ�����û��б�㲥��Ϣ������Ѽ���Ʒ��Ϣ	�����ģ�(dbid user, ulong chatChannelType, ulong infoPos, const char* text, ulong userData)
	ChatMsg_Broadcast,


	/// ϵͳ�㲥֪ͨ������ң�Bossˢ���ˣ�
	ChatMsg_NoticeBossRefresh,

	//////////////////////////////////////////////////////////////////////////
	// ��������� -> ����������
	//////////////////////////////////////////////////////////////////////////

	/// 9����㲥��Ϣ���ʺ���ͨƵ����	�����ģ�(dbid id, const char* chatText)
	ChatMsg_Broadcast_9,

	/// �������������û��б���������������������������Ҫ�� �����ģ���
	ChatMsg_OnlineUserInfo,

	/// �۳��������е�������Ҫ�շѣ����ԡ�������
	/// TODO 

	ChatMsg_Shield,
	ChatMsg_Shield_UserState,
	ChatMsg_Update_AmusementBoss, // ֪ͨҰ��Boss
};


struct SMsgChat_Shield_cs
{
	ulong userPID;	 
	ulong playerPID;
	short bShield;
	char  szName[MAX_PERSONNAME_LEN];
	SMsgChat_Shield_cs()
	{
		memset(this, 0, sizeof(SMsgChat_Shield_cs));
	}
};

struct SMsgChat_Shield_sc
{
	ulong playerPID;
	short bShield;
};

struct SMsgChat_Shield_UserState_sc
{
	ulong playerPID;
	bool  bOnline;
};


struct SShieldRecord
{
	ulong playerPID;
	char  szName[MAX_PERSONNAME_LEN];		
	bool  Online;	
	SShieldRecord()
	{
		playerPID= 0;
		szName[0] = '\0';
		Online = false;
	}
};
#endif // __CHATMSGDEF_H__