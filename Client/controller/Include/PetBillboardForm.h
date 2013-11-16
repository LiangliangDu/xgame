/******************************************************************
** �ļ���:	PetBillboardForm.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2009-11-2
** ��  ��:	1.0
** ��  ��:	�������а񴰿�			
** Ӧ  ��:  
******************************************************************/
#pragma once
#include "IGlobalClient.h"

class CPetBillboardForm : public SingletonEx<CPetBillboardForm>
{
	typedef vector<SMsgActionPetBillboardTable_SC> BillboardTop100;
public:

	void RequestSinglePetPropBillboard(LONGLONG uidPet);

	void RequestPetPropBillboard(DWORD petProp);

	// UI��ҳ
	void OpenBillboardRangePage(int pageIndex);

	// ������������
	void OnBillboardReturn(DWORD dwMsgID, SGameMsgHead * pGameMsgHead, LPCSTR pszMsg, int nLen);

public:
	CPetBillboardForm();

	~CPetBillboardForm();

private:
	// �Ƿ��ǳɳ������а񣬳ɳ������а�Ҫ��ʾ������
	bool IsGrowthBillboard();

	// ����һ��html�ı�
	void WriteHtmlRow(string& retStr,const SMsgActionPetBillboardTable_SC& billboardItem,string fontColor);

private:
	static const std::string	EventOnOpenPetBillboard;			//open pet properties billboard event
	LONGLONG uid_CurPet;
	BillboardTop100	m_PetBillboard_Top100;
	int lua_CurPageIndex;
	DWORD lua_CurBillboardType;
};
