#ifndef __ChangePartManager_H__
#define __ChangePartManager_H__

#include "ISchemeCenter.h"

class VisualComponentMZ;

struct ChangePartCallBackContext
{
	ModelNode* pNode;//���Ϊ0����ʾȡ���ڵ�
};

struct IChangePartCallBack
{
	virtual void onChangePart(ChangePartCallBackContext & context)=0;
};

class ChangePartManager
{
public:
	//�߼����
	void changePart(SPersonMainPartChangeContext & context);//��������
	void showPart( ulong ulPart, bool bShow);//��ʾ����
	void setPartScale(ulong part, float scale);//���ò���������
	void setPartColor(ulong	part, const ColorValue& color);//���ò�����ɫ
	void setBodyColor(const ColorValue & color);//����������ɫ
	const ColorValue & getBodyColor();//��ȡ������ɫ
	void update();//����

	//��Դ���
	void setCanRequestRes(bool canRequest);//�����ܷ�������Դ
	void requestRes(int priority);//������Դ
	void releaeRes();//�ͷ���Դ

	//״̬
	EWeaponClass getWeaponClass();//��ȡװ������������
	enum WeaponPosition { WeaponPos_Hands, WeaponPos_Back, }; //����λ��
	void		setWeaponPos(WeaponPosition);//�����������õ�λ��
	void		showRibbonSystem(bool show);//��ʾƮ��ϵͳ
	void		setWeaponAnimation(std::string ani);//������������
	bool		getPart(uint part, SEventPersonPerform_C& c);//��ȡ����
	bool		getPartShow(uint part, SEventPersonPerformShow_C& c);//��ȡ��������ʾ
	int			getCurrentCreatureId();//��ȡ��ǰ��������Դid

public:
	ChangePartManager();
	void create(VisualComponentMZ* pOwner, IChangePartCallBack* pCallBack);
	~ChangePartManager();

private:
	//��װ
	void changeArmet(SPersonMainPartChangeContext & context);//��ͷ��
	void changeSuitArmet(SPersonMainPartChangeContext & context);//��ʱװͷ��
	void changeArmor(SPersonMainPartChangeContext & context);//����ͨ����
	void changeSuitArmor(SPersonMainPartChangeContext& context);//��ʱװ����
	void changeWeapon(SPersonMainPartChangeContext & context);//������

	//���Ʋ�����ʾ
	void showArmet( bool bShow);	
	void showSuitArmet(bool bShow);
	void showBody( bool normal);//normalΪtrue����ʾ��ͨװ����Ϊfalse����ʾʱװ
	void showWeapon( bool bShow);//����ʱ����Ҫ����������by cjl

	//
	void onResLoad(ModelNode* pNode);
	
private:
	ulong getCurrentBody();//��ȡ��ǰ��ʾ����ģ��

private:
	//���ڻ�װ
	SPersonMainPartChangeContext	m_CurrentPart[EEntityPart_Max];//��ǰ��װ������ʱװ������ʱװ�����壬��ͨ��������ͨװ�������塣
	bool							m_bShowPart[EEntityPart_Max];	//��ǰ������ʾ����
	WeaponPosition					m_weaponBindPos;//�����İ�λ��
	bool							m_bShowRibbonSystem;//�Ƿ���ʾ������Ʈ��ϵͳ
	float							m_fWeaponScale;///����������
	ColorValue						m_vWeaponColor;//��������ɫ
	ColorValue						m_vArmetColor;//��ͨͷ������ɫ
	ColorValue						m_vSuitArmetColor;//ʱװͷ������ɫ
	ColorValue						m_vBodyColor;//������ɫ

	VisualComponentMZ*				m_pOwner;//������
	IChangePartCallBack*			m_pCallBack;//�ص�

	//������Դ�ļ���
	ulong							m_ulCurResId;//��ǰ��Դid,EntityViewImpl��resId,��ʱװ���׺���ͨ���׵�Ĭ����Դid
	bool							m_bCanRequestRes;//�ܷ�������Դ
	ulong							m_ulNewResId;//��Դidӳ������������Դid
	xs::handle						m_handle;//��Դ���
	bool							m_bLoaded;//��Դ�Ƿ��Ѿ�����
	ModelNode*						m_pModelNode;//��ǰ�ڵ�
};


#endif