//==========================================================================
/**
* @file	  : IEntityFactory.h
* @author : 
* created : 2008-1-19   12:53
* purpose : ʵ�幤���ӿ�
*/
//==========================================================================

#ifndef __IENTITYFACTORY_H__
#define __IENTITYFACTORY_H__

#include "IEntityView.h"

/// ���ָ���ʱ�˶�������
enum FlowType
{
	FlowType_Liner,			/// �����˶�
	FlowType_Accelerative,	/// �ȼ����˶�
	MaxFlowTypeCount,
};

/// ���궨λ����
enum CoordAlign
{
	CoordAlign_Screen,		/// ����Ļλ�ö�λ
	CoordAlign_World,		/// ���������궨λ
	MaxCoordAlignCount,
};

enum FlowAreaType
{
	FlowArea_Top,			/// ��ɫ�Ϸ�
	FlowArea_Bottom,		/// ��ɫ�·�
	FlowArea_Right,			/// ��ɫ�ҷ�
	FlowArea_Mouse,			/// ��굱ǰλ��
	MaxFlowAreaCount		/// �����
};

/// ��������������
struct FlowTextContext
{
	struct EFFECTSCALE
	{
		float		firstScale;
		float		finalScale;	
		ulong		effectTime;	/// ����Ч��ʱ�䣬���ʱ��һ��̣ܶ��������ķŴ���С
	};

	POINT		pos;		/// ��ʼλ��(����align����д)
	union{
		POINT		posOffset;	/// ��Գ�ʼλ�õ�ƫ����
		struct{
			float		v0_x;		/// x�����ϵĳ�ʼ�ٶ�
			float		v0_y;		/// y�����ϵĳ�ʼ�ٶ�
			float		a_x;		/// x�����ϵļ��ٶ�
			float		a_y;		/// y�����ϵļ��ٶ�
		};
	};
	std::string	text;		/// ��������
	ColorValue	color;		/// ������ɫ   
	float		lastAlpha;	/// ���յ�alphaֵ
	ulong		totalTime;	/// ���ָ�����ʱ��
	FlowType	flowType;	/// ���ָ������ͣ������ٸ����������߸���(Ŀǰ�����alpha)
	CoordAlign	align;		/// ���궨λ����

	DWORD		font;		/// ����
	EFFECTSCALE scale;	
};

class MagicView;
/// ʵ�幤���ӿ�
struct IEntityFactory
{
	/** ����ʵ�����
	@param entityType	ʵ�����ͣ��ο�ö��EntityType
	@param resType		��Դ���ͣ��ο�ResourceTypeö��
	@param stream		ʵ�崴��ʱ��������
	@param len			�����ĳ���
	*/
	virtual EntityView* createEntity(ulong entityType, ulong resType, Stream* stream, size_t len) = 0;

	/** ����ʵ�����
	@param entityType	ʵ�����ͣ��ο�ö��EntityType
	@param resType		��Դ���ͣ��ο�ResourceTypeö��
	@param buf			ʵ�崴��ʱ��������
	@param len			�����ĳ���
	*/
	virtual EntityView* createEntity(ulong entityType, ulong resType, const uchar* buf, size_t len) = 0;

	/** ��������
	@param ptScreen		�������ֿ�ʼ������Ļ����
	@param text			��������������
	@param totalTime	���ָ�����ʱ������
	@param lastX		������������xλ�ã�����ڿ�ʼ�㣩
	@param lastY		������������yλ�ã�����ڿ�ʼ�㣩
	@param flowType		�������ͣ�����:0 ������:1��
	*/
	virtual void flowText(const FlowTextContext& context) = 0;


	/** ��ָ������Ư�����֣����ڽ�ɫ�Աߵ���Ϣ��ʾ��
	@param area		ָ�������򣬲ο� FlowArea ö�ٶ���
	@param text		Ҫ��ʾ���ı�
	@param color	���ı�����ɫ
	*/
	virtual void flowAreaText(int area, const std::string& text, const ColorValue& color = ColorValue(1,1,1),const DWORD font = 0) = 0;

	virtual const std::string GetLastFlowString(FlowAreaType area) = 0;

	/** ���¸�������
	@param deltaTime	����ϴθ���֮���ʱ���
	*/
	virtual void updateFlowText(ulong deltaTime) = 0;

	/** ����ϵͳ��ʾ��Ϣ
	@param deltaTime	����ϴθ���֮���ʱ���
	*/
	virtual void updateSystemTips(ulong deltaTime) = 0;

	/** ��Ⱦ��������
	@param pRenderSystem	��Ⱦϵͳ
	*/
	virtual void renderFlowText(IRenderSystem* pRenderSystem) = 0;

	/** ��Ⱦϵͳ��ʾ��Ϣ
	@param pRenderSystem	��Ⱦϵͳ
	*/
	virtual void renderSystemTips(IRenderSystem* pRenderSystem) = 0;

	/** ����ħ������
	@param type		ħ���������ͣ�����ͨ�࣬������ȵ�
	@param context	����������
	@param len		�����ĳ���
	*/
	//virtual bool createEffect(ulong type, const void* context, size_t len) = 0;
	virtual EntityView* createMagic(ulong type, const void* context, size_t len) const = 0;

	//////////////////////////////////////////////////////////////////////////
	// ����4���ӿ��Ƕ�EntityView�����䣬ʹ����ĵ��ø�����
	/** ����BuffЧ��
	@param view		ӵ�и�BuffЧ����EntityView����
	@param effId	��EffectView.xls�ű��ж����BuffЧ��id
	*/
	virtual bool createBuffEffect(EntityView* view, ulong effId) = 0;
	virtual bool createEffect(ulong effId, const POINT& ptTile) = 0;

	/** �ر�BuffЧ��
	@param view		ӵ�и�BuffЧ����EntityView����
	@param effId	��EffectView.xls�ű��ж����BuffЧ��id
	*/
	virtual void closeBuffEffect(EntityView* view, ulong effId) = 0;

	/** ��������׼��Ч��
	@param context �Ǽ���׼��������
	*/
	virtual bool createSkillReadyEffect(const SkillEffectContext& context, bool bPlayAction, bool bHasInterval) = 0;

	/** �رռ���׼��ʱ�Ĺ�Ч
	@param view ����ʹ����
	@param id	������Skill.xls�е���ͼID
	*/
	virtual void closeSkillReadyEffect(EntityView* pSourceView, EntityView* pDestView, ulong id) = 0;

    /** ������������Ч��
    @param context �Ǽ���׼��������
    */
    virtual bool CreateSkillBootEffect(const SkillEffectContext& context) = 0;

    /** �رռ�������ʱ�Ĺ�Ч
    @param view ����ʹ����
    @param id	������Skill.xls�е���ͼID
    */
    virtual void CloseSkillBootEffect(EntityView* pSourceView, ulong ulSkillViewID) = 0;

	/** �����ܻ���Ч
	@param   
	@param   
	@return  
	*/
	virtual bool CreateBeHitEffect(const SkillEffectContext& context) = 0;

	/** �����ܻ�Դ��Ŀ�������Ч
	@param   
	@param   
	@return  
	*/
	virtual bool CreateBeHitFlyEffect(const SkillEffectContext& context) = 0;

	/** ����������Ч
	@param   
	@param   
	@return  
	*/
	virtual bool createSkillTrackEffect(const SkillEffectContext& context) = 0;


	/** �������ܹ���Ч��
	@param context �Ǽ��ܹ���������
	*/
	virtual bool createSkillAttackEffect(const SkillEffectContext& context) = 0;

	/** �رռ��ܹ���ʱ�Ĺ�Ч
	@param view		����ʹ����
	@param viewId	������SkillView.xls�е���ͼID
	*/
	virtual void closeSkillAttackEffect(EntityView* view, ulong viewId) = 0;

	// ������Ϸ�������ŵ���Ч���������ꡢ��ѩ��ͬһ��ID�ĳ�����Ч�����ظ����ڡ� zgz [4/18/2011 zgz]
	virtual MagicView* CreateSceneMagic(const SceneMagicContext& context) = 0;
	// ɾ����Ϸ�������ŵ���Ч 
	virtual bool CloseSceneMagic(MagicView* mv) = 0;

	/// �ͷ�ʵ�幤��
	virtual void release() = 0;

	//Ԥ������Դģ������
	//add by yhc 2009.11.11
	virtual std::string GetFileNameByCreatureId(long id) = 0;
	virtual std::string GetFileNameByResId(long id) = 0;

	// ��ȡģ�Ͷ���׼ȷʱ��
	virtual int GetAnimationTime(const RequestAnimationContext& context) = 0;

	/** ��������Ч��
	@param   
	@param   
	@return  
	*/
	virtual void CreateVibrate(ulong ulViewID) = 0;

	// Ԥ���ؼ�����Ч
	virtual void PreLoadSkillEffect(int nViewID) = 0;

	//��ȡSkill������� add wangtao
	virtual uint GetSkillViewDataId(uint array, uint set) = 0;
	virtual const std::string& GetSkillViewDataName(uint id) = 0;
	virtual bool GetSkillViewDataArrayIsValid(uint array) = 0;
	virtual bool GetSkillViewDataRowIsValid(uint array, uint set) = 0;
	virtual uint GetMagicDataId(uint array, uint set) = 0;
	virtual const std::string& GetMagicDataName(uint id) = 0;
	virtual bool GetMagicDataArrayIsValid(uint array) = 0;
	virtual bool GetMagicDataRowIsValid(uint array, uint set) = 0;
	virtual const uint GetConfigCreatureResMaxId() = 0;
	virtual const uint GetConfigCreatureResId(uint id) = 0;
	virtual const std::string GetConfigCreatureResName(uint id) = 0;
	virtual const std::string GetSkillViewAttackAct(uint id) = 0;
	virtual const uint GetSkillViewSwing(uint id) = 0;
	virtual const float GetSkillViewFlySpeed(uint id) = 0;
	virtual const uint GetSkillViewEmitEffect(uint id) = 0;
	virtual const uint GetSkillViewBlastEffect(uint id) = 0;
	virtual const uint GetSkillViewHitEffect(uint id) = 0;
	virtual const uint GetSkillViewFlyEffect(uint id) = 0;
	virtual const uint GetSkillViewHitFlyEffect(uint id) = 0;
	virtual const uint GetSkillViewReadyEffect(uint id) = 0;
	virtual const float GetMagicAniSpeed(uint id) = 0;
	virtual const uint GetMagicAniTrans(uint id) = 0;
	virtual const std::string GetMagicAniOffset(uint id) = 0;
	virtual const float GetMagicAniScale(uint id) = 0;
	virtual const uint GetMagicResId(uint id) = 0;
	virtual void SetSkillViewData(uint id, std::string attackAct, uint swing, float flySpeed, 
		uint emitEffect, uint blastEffect, uint hitEffect, uint flyEffect,
		uint hitFlyEffect, uint readyEffect) = 0;
	virtual void SetMagicData(uint id, float aniSpeed, uint aniTrans, std::string aniOffset,
		float aniScale, uint resId) = 0;
	virtual void SaveMagicDataToCsv(const char* szFileName) = 0;
	virtual void SaveSkillViewDataToCsv(const char* szFileName) = 0;
};


#if defined(_LIB) || defined(ENTITYVIEW_STATIC_LIB)/// ��̬��汾
#	pragma comment(lib, MAKE_LIB_NAME(xs_cev))
extern "C" IEntityFactory* LoadCEV(void);
#	define	CreateEntityFactoryProc	LoadCEV
#	define  CloseEntityFactory()
#else /// ��̬��汾
typedef IEntityFactory* (RKT_CDECL *procCreateEntityFactory)(void);
#	define	CreateEntityFactoryProc	DllApi<procCreateEntityFactory>::load(MAKE_DLL_NAME(xs_cev), "LoadCEV")
#	define  CloseEntityFactory()	DllApi<procCreateEntityFactory>::freelib()
#endif


#endif // __IENTITYFACTORY_H__
