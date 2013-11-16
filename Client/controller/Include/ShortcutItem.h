/******************************************************************
** �ļ���:	ShortcutItem.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008-4-9
** ��  ��:	1.0
** ��  ��:	�����ĿITem			
** Ӧ  ��:  
******************************************************************/
#pragma once

class ShortcutItem
{
public:
    //  Item���ͣ�
    enum EItemType
    {
        EIT_LOWER_BOUND = -1,

        EIT_Skill,
        EIT_NO_Skill,

		EIT_RIDEPET,   // ��� zgz

        EIT_UPPER_BOUND,
    };

public:
	ShortcutItem(int pos, EItemType type, ulong id, int index);
	ShortcutItem(ShortcutItem* item);
	ShortcutItem();
	~ShortcutItem(){}

	/************************************************************************/
	/* operate functions                                                    */
	/************************************************************************/
public:
	void setPos(int pos)	
	{ 
		m_pos		= pos;	
	}

	void setType(EItemType type)
	{ 
		m_eItemType = type; 
	}

	void setID(ulong id)
	{ 
		m_id		= id;	
	}

	void setIndex(const int& idx)
	{ 
		m_index = idx;
	}

	//����(wzh09.12.08)
	void setUserUid(LONGLONG uid)
	{
		m_lUserUid = uid;
	}

	void setShine() 
	{
		m_isShine = true;
	}

	const int getPos() const 
	{ 
		return m_pos;
	}

	const EItemType getType() const 
	{ 
		return m_eItemType;
	}

	const int getIndex() const 
	{ 
		return m_index;
	}

	// �õ�ʹ����UID(WZH.09.12.08)
	const LONGLONG getUserUid() const
	{
		return m_lUserUid;
	}

	ulong getID();

	ulong getSubID();

	ulong getCoolingId();

	std::string getTooltip();

	void cooling();

	void ShortcutItemDragCooling(void);

	void ShortcutEndCooling(/*int nPlace*/);

	void GetCoolingInfo(ulong& uCoolingTime, ulong& uLiveTime);

	void clear();

    inline bool IsValidItem() const
    {
        return ((m_eItemType > EIT_LOWER_BOUND) && (m_eItemType < EIT_UPPER_BOUND));
    }

	
	/************************************************************************/
	/* Item�¼�                                                             */
	/************************************************************************/
public:
	void Use();
	void setEnable(bool enable);
	bool getEnable() const 
	{ 
		return m_enable;
	}

	void Init();

	void onUpdate(bool bPetSkill = false);//����

	void select();
	void deselect();

	// add by zjp��
	void SetPetSkill(bool bPetSkill){m_bPetSkill = bPetSkill;}
	bool IsPetSkill(){return m_bPetSkill;}
	void SetPetSkillPetIndex(int nSkillPetIndex)
	{
		m_nSkillPetIndex = nSkillPetIndex;
	}
	int  GetPetSkillPetIndex()
	{
		return m_nSkillPetIndex;
	}

protected:
    int		m_pos;		//����λ��,���п�ݹ��ܲ�ͳһ����,ͳһ���
    EItemType m_eItemType;		//���ܻ�����Ʒ 0---���� 1--�Ǽ��� 2--��� -1 ��Ч
    ulong	m_id;		//��ƷID���߼�����ID
    bool	m_enable;	//�ܲ���ʹ��
    int		m_index;	//��Ʒ�������߼�������
    bool	m_isShine;  //����
	LONGLONG m_lUserUid; // ��������ܶ�Ӧ�ļ��ܵ�ʹ����UID(WZH 09.12.08); ����������¼������UID(zgz 2011.01.26)

	// add by zjp�������Ƿ�Ϊ���＼��
	bool    m_bPetSkill; // �Ƿ�Ϊ���＼�� 
	int     m_nSkillPetIndex; // ���ܶ�Ӧ�ĳ���λ������
	string  m_sToolTip;	 // ��ʾ
};
