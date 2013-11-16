//==========================================================================
/**
* @file	  : VisualComponentMZ.h
* @author : 
* created : 2008-1-30   12:56
* purpose : ���ӻ����(MZ)
*/
//==========================================================================

#ifndef __VISUALCOMPONENTMZ_H__
#define __VISUALCOMPONENTMZ_H__

#include "VisualComponent.h"
#include "ActionList.h"
#include "MagicView.h"
#include "ShadowManager.h"
#include "Modifier.h"
#include "ConfigCreatures.h"
#include "ConfigCreatureRes.h"
#include "JumpManager.h"
#include "ISchemeCenter.h"
#include "VisualComponentState.h"
#include "RideManager.h"
#include "ChangePartManager.h"

struct ModelNodeStateRecorder //��¼����Ľڵ�ĸ���״̬
{
	//������
	ModelNode*	m_pRideNode;//���ڵ�
	std::string m_strBindPoint;//��˰󶨵�

	//��װ���
	ModelNode*	m_pBodyNode;//��װ�ڵ�

	//������Ⱦ�͸����õĽڵ�
	ModelNode*	m_pCompositeNode;//�ϳɺ�Ľڵ�

	//ͨ��״̬
	const ConfigCreature*	m_pConfig;			/// ��������
	const ConfigCreature*	m_pRideConfig;		/// �������
	float					m_fScale;			///ģ���ڳ�ʼ���ű����Ļ����ϵ��������ű���
	float					m_fAniSpeed;		///ģ�͵Ķ����ٶ�
	ulong					m_ulMoveSpeed;		/// �ƶ��ٶ�
	ulong					m_ulTilePerTile;	/// �ƶ�һ��TILE��ʱ��
	ulong					m_ulSitState;       /// ���£�0��û���£�1����������2�������£�
	bool					m_bMoveStyleChange; /// �ƶ���ʽ�Ƿ�ı�
	long					m_lCurAngle;		///��ǰ��ת�Ƕ�
	bool					m_bPetDie;//
	ulong					m_curActionId;	//��ǰ�Ķ���
	ulong					m_curRepActionId;//��ǰ�滻����id
	int						m_curActionLoops;//��ǰ����ѭ������

public: //���캯��
	ModelNodeStateRecorder():m_pRideNode(0),
		m_strBindPoint(),
		m_pBodyNode(0),
		m_pCompositeNode(0),
		m_pConfig(0),
		m_pRideConfig(0),
		m_fScale(1.0f),
		m_fAniSpeed(1.0f),
		m_ulMoveSpeed(EMOVESPEED_NORAML),
		m_ulTilePerTile(EMOVETIMEPERTILE_NORMAL),
		m_ulSitState(EN_SIT_NONE),
		m_bMoveStyleChange(false),
		m_bPetDie(false),
		m_lCurAngle(0),
		m_curActionId(EntityAction_Stand),
		m_curRepActionId(EntityAction_Walk),
		m_curActionLoops(-1)
	{
	}
};

class VisualComponentMZ : public VisualComponent, public IAnimationCallback, public IRideCallBack, public IChangePartCallBack
{
	ActionList						mActionList;		///�����б�
	ShadowManager*					mShadowManager;		///���ʱ��Ӱ�ӹ���
	CEffectObjHolder				mAttachObjHolder;	///��Ч��������
	ModifierList					mModifierList;		///�޸����б�
	CVisualComponentStateMgr		m_stateMgr;			//����״̬������
	RideManager						mRideManager;		//��˹�����
	ChangePartManager				mChangePartManager; //��װ������	
	ModelNodeStateRecorder			mModelNodeState;	//����ڵ�״̬
	JumpManager *					m_pJumpManager;		//��Ծ������
	bool							m_bUseBigTexture;
public:
	VisualComponentMZ();
	virtual ~VisualComponentMZ();

	virtual void create();
	virtual void close();

	virtual bool handleCommand(ulong cmd, ulong param1, ulong param2);
	virtual void onEnterViewport(int priority = 0);
	virtual void onLeaveViewport();
	virtual void drawPickObject(IRenderSystem* pRenderSystem);
	virtual void drawShadow(IRenderSystem* pRenderSystem);
	virtual void draw(IRenderSystem* pRenderSystem);
	virtual bool update(float tick, float deltaTick, IRenderSystem* pRenderSystem);	
	virtual size_t onLoad(Stream* stream, size_t len);
	virtual size_t onSave(Stream* stream) const;
	virtual void onRemoveEntity();
	virtual void handleMessage(ulong msgId, ulong param1, ulong param2);
	virtual const AABB& GetAABB();
	virtual const Matrix4& GetFullTransform();
	virtual const xs::Rect& getShowRect() const;

public:
	ulong getCurrentAction();

	//by yhc ,��ѡ���ɫ��ʱ��ʹ�ø߾�������
	//ѧ�Խ���ķ�ʽ��ʹ��ConfigCreature.xml����һ���߾��ȵ�����ID,����������һ�ű��߾��ȺͷǸ߾��ȱ��ID��Ӧ����,
	//���ַ�ʽ���ǲ߻���Ҫ���õĶ���̫��,���Ǵ��������ǰ�ĵ�һЩ�淶
	//����������ֱ���ô���ȥ������,���ַ�ʽ�ǱȽϱ�Ť,���ǲ��������κζ���
	void UseBigTexture();

	// �����ܱ���ң�
	bool ShieldAroundPlayer();

private:
	void requestRes(int priority);//������Դ
	void releaseRes();//�ͷ���Դ

private:
	bool setAnimate();//���ö���
	void setAniSpeed(float speed);
	bool setAction(ulong actionId, int loops, ulong replaceactionid = 0, /*�Ƿ����actionlist��ͬ��*/bool ignoreactionlistsyn = false, bool bForceStopStand = false);
	void setWeaponPos();//����������λ��
	void setWeaponAction();//������������
	bool changePartAttchEffect( SPersonAttachPartChangeContext & context);//����װ������Ч��
	bool deformPart(SPersonPartDeformationContext & context);//����װ������
	int CheckAngleDir(long & lFrom,long & lTo);
	inline void resetMoveAction(bool ignoreactionlistsyn = false );
	void GetBoneSpace(Vector3& v, const char *p);

	//�ص�����
	virtual void onOneCycle(const std::string& animation,int loopTimes);
	virtual void onRide(RideCallBackContext& context);
	virtual void onChangePart(ChangePartCallBackContext & context);

private:
	inline ModelNode* getModelNode(){ return mModelNodeState.m_pCompositeNode; };//��ȡģ�ͽڵ�

	// ��ȡģ�Ͷ����ľ�ȷʱ��
	int GetAnimationTime(int nActID);

	// ��ȡλ�Ƶ�ʱ��
	int GetJumpTime(xs::Point ptSrc, xs::Point ptTarget);

//��Ҫ��ɾ���ĺ���
private:
	//void onResLoaded(ModelNode* node);


};

#endif // __VISUALCOMPONENT_H__