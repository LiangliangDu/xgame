/******************************************************************
** �ļ���:	SKillTrain.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008-4-22
** ��  ��:	1.0
** ��  ��:	����ѧϰ			
** Ӧ  ��:  
******************************************************************/
#pragma once

class SKillTrain : public SingletonEx<SKillTrain>
{
	struct _SkillItem_
	{
		SkillId id;
		std::string name;
		int maxLevel; //��߼���
	};

	/************************************************************************/
	/* event define                                                          */
	/************************************************************************/
	static std::string EventOnSkillTrainEnter; //�򿪼��ܴ���
	static std::string EventOnSkillTrainLeave; //�رռ��ܴ���
	static std::string EventOnAddSkillTainItem;//��Ӽ�����
	static std::string EventOnUpdateSkillTainItem;//���¼�����
	static std::string EventOnDeleteSkillTrainItem;//ɾ��������
	static std::string EventOnSelectSkillTrainItem;//ѡ���������ѡ���ȡ��ѡ��

	typedef std::vector<_SkillItem_>			LTrainSkillList;

	LTrainSkillList							m_vlist;

	int		m_currentCurrent;

public:
	SKillTrain();
	~SKillTrain();


	void create();

	void open();
	void close();

	void select(ulong idx);

	void train();

	void readSkillList();


	void upgrade(const ushort& mainId);

	/************************************************************************/
	/* event handler                                                         */
	/************************************************************************/
	void onSkillTrainEnter(EventArgs& args); //�򿪼��ܴ���
	void onSkillTrainLeave(EventArgs& args); //�رռ��ܴ���
	void onAddSkillTainItem(EventArgs& args);//��Ӽ�����
	void onDeleteSkillTrainItem(EventArgs& args);//ɾ��������
	void onSelectSkillTrainItem(EventArgs& args);//ѡ���������ѡ���ȡ��ѡ��
	void onUpdateSkillTainItem(EventArgs& args);

};