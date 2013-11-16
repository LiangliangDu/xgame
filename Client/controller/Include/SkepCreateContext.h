/******************************************************************
** �ļ���:	SkepCreateContext.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008-3-19
** ��  ��:	1.0
** ��  ��:	��Ʒ����Ϣ��װ			
** Ӧ  ��:  
******************************************************************/
#pragma once

class SkepCreateContext
{
	std::string m_skepTitle;					// ��Ʒ��������
	std::string m_customInfo;					// �ͻ���Ϣ,���浽UI��Ʒ����Ϣ���
	ulong		m_ulSkepID;						// ��Ʒ��ID
	ulong		m_ulSkepType;					// ��Ʒ������
	ulong		m_ulSkepName;					// ��Ʒ������
	ulong		m_ulMaxSize;					// ��Ʒ����С
	ulong		m_ulUsableBags;					// ��������
	std::string m_UnifiedPosition;				// ������ʾ�ο�λ��("{{0,0},{0,0}}")

public:
	SkepCreateContext(SBuildSkepClientContext* pContext):
	  m_skepTitle(pContext->szSkepName),
	  m_ulSkepID(pContext->dwSkepID),
	  m_ulSkepType(pContext->dwSkepType),
	  m_ulSkepName(pContext->dwSkepName),
	  m_ulMaxSize(pContext->dwMaxSize),
	  m_ulUsableBags(pContext->dwUsableBags)
	  {
		  char szBuf[256];
		  sprintf(szBuf,"%d",m_ulSkepID);
		  m_customInfo = szBuf;
	  }
	  SkepCreateContext(const std::string& skepTitle,ulong skepID,ulong skepType,ulong skepName,ulong maxSize,ulong usableBags):
	  m_skepTitle(skepTitle),
	  m_ulSkepID(skepID),
	  m_ulSkepType(skepType),
	  m_ulSkepName(skepName),
	  m_ulMaxSize(maxSize),
	  m_ulUsableBags(usableBags)
	  {

	  }
	  ~SkepCreateContext(){}

	  void setUnifiedPosition(const std::string& strUnifiedPosition) { m_UnifiedPosition = strUnifiedPosition; }

	  const std::string& getUnifiedPostion() const { return m_UnifiedPosition; }

	
	  const std::string&		getSkepTitle()	const	{ return m_skepTitle;}
	  const unsigned long&		getSkepSize()	const	{ return m_ulMaxSize;}
	  const std::string&		getCustomInfo()	const	{ return m_customInfo;}
	  const unsigned long&		getUsableBags()	const	{ return m_ulUsableBags;}

	  const bool isPacket() const { return m_ulSkepName == ESkepName_Packet;}	// ������
	  const bool isEquip() const { return m_ulSkepName == ESkepName_Equip;}		// װ����
	  const bool isLib() const { return m_ulSkepName == ESkepName_WareHouse;}	// �ֿ���
	  const bool isTrade() const { return m_ulSkepName == ESkepName_Trade;}		// ������
	  const bool isStall() const { return m_ulSkepName == ESkepName_Stall;}		// ̯λ��
	  const bool isShop() const { return m_ulSkepName == ESkepName_Shop;}		// �̵���
	  const bool isHock() const { return m_ulSkepName == ESkepName_Hock;}		// ������
	  const bool isBox() const { return m_ulSkepName == ESkepName_Box;}			// ������
	  const bool isAuction() const { return m_ulSkepName == ESkepName_Auction;}	// ������
	  const bool isPet() const {return m_ulSkepName == ESkepName_Pets;}         // ������
	  const bool isPetLib() const {return m_ulSkepName == ESkepName_PetLib;}    // ����ֿ���
	  const bool isEquipSmeltSoul() const { return m_ulSkepName == ESkepName_EquipSmeltSoul; }	// װ��������Ʒ��
	  const bool isEquipEmbedGems() const { return m_ulSkepName == ESkepName_EquipEmbedGems; }	// װ����ʯ��Ƕ��Ʒ��
	  const bool isEquipRebuild() const { return m_ulSkepName == ESkepName_EquipRebuild; }		// װ��������Ʒ��
	  const bool isComposePill() const { return m_ulSkepName == ESkepName_Compose; }// �ڵ��ϳ�  //by cjl ,����û���ϴ����Ҳ�һ��
	  const bool isPetIntensify() const {return m_ulSkepName == ESkepName_Intensify;}	//�꽫ʥ�� by ldy
};