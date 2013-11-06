//==========================================================================
/**
* @file	  : UserInfoDef.h
* @author : pk <pk163@163.com>
* created : 2008-6-11   21:48
* purpose : ���������û���Ϣ����
*/
//==========================================================================

#ifndef __USERINFODEF_H__
#define __USERINFODEF_H__

#include "DGlobalGame.h" // for MAX_PERSONNAME_LEN

/// �ҽ����û�������������û�����
enum UserDataType
{
	UserData_Chat,		/// ����ϵͳ����
	UserData_Friend,	/// ����ϵͳ����
	UserData_Team,		/// ���ϵͳ����
	UserData_Nation,	/// ����ϵͳ����
	UserData_Tribe,		/// ����ϵͳ����

	MaxUserDataCount,
};

///�û�����������
enum UerPropData
{
	User_Prop_Level = 1,      /// �û��ĵȼ�  
	User_Prop_Army ,          /// �û��ľ���ID
	User_Prop_Family,         /// �û�������ID
	User_Prop_Team,           /// �û��Ķ���ID
	User_Prop_Mapid,          /// �û��ĵ�ͼID
	User_Prop_Right,          /// �û���Ȩ��

	User_Prop_MAX,            /// ���
}; 
#pragma pack(push)
#pragma pack(1)

typedef ulong dbid;

const static int PERSON_SAVE_INTERVAL_DEAFULT = 3600000; //1000*60*60 60���� 

/// �����û�����
struct UserInfo
{
	dbid		id;							/// �û���DBID
	UID			uid;						/// �û���UID
	ulong		clientId;					/// �ͻ���Id
	ulong		svrId;						/// ������Id

	char		name[MAX_PERSONNAME_LEN];	/// �û�������
	ulong		level;						/// �û��ȼ�
	ulong       faceid;                     /// �û�ͷ��id
	ulong		army;						/// �û����ھ���id
	ulong		family;						/// �û���������id
	ulong		team;						/// �û����ڶ���id
	ulong       mapid;                      /// �û����ڵ�ͼid
	ulong		right;						/// �û�Ȩ��
	ulong       index;                      /// �û�����Ҫ���µ���������
	int         nCreatureVocation;          /// ְҵ
	int			nSex;                       /// �Ա�
	int         nCamp;						/// ��Ӫ

};

#pragma pack(pop)

#endif // __USERINFODEF_H__