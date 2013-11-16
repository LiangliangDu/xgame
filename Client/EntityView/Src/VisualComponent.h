//==========================================================================
/**
* @file	  : VisualComponent.h
* @author : 
* created : 2008-1-30   12:56
* purpose : ���ӻ����
*/
//==========================================================================

#ifndef __VISUALCOMPONENT_H__
#define __VISUALCOMPONENT_H__

#include "EntityViewImpl.h"
#include "EntityComponent.h"
#include "PacketFormat.h"
//#include "TxSysGui.h"
#include "ITaskClient.h"

class VisualComponent : public EntityComponent
{
protected:
	// ��Դ���
	handle			mHandle;

	// ��ʶ��Դ�Ѿ�����
	bool			mResLoaded;

	// ʵ����Χ����
	xs::Rect			mShowRect;

	// ʵ�������
	autostring		mName;

	// ������ɫ
	ColorValue		mNameColor;

	// �������ʵ��ĸ߶�ƫ��
	float			mNameOffset;

	// �Ƿ���Ҫ���£�һ�㷢����λ�á��������������š��ٶȵȸı�ʱ��
	ulong			mUpdateOption;

	// �Ƿ��ƶ���ʽΪ����
	bool			mIsRun;

	// ���ڵ��뵭����alphaֵ
	float			mAlpha;

	// ��ǰHP��MP����ǰ���HP��MP
	ulong			mCurHP, mMaxHP, mCurMP, mMaxMP;

	// ��·��ʼ���������·�ٶ�
	ulong           m_ulInitWalkSpeed;

	// ��·��ʼ��������ܲ��ٶ�
	ulong           m_ulInitRunSpeed;

	// �ƺ�
	autostring		mTitleName;
	
	// ������ʾ��ͼƬ������
	list<TextLine>	m_listText;

	// ��Ч����ļ�ʱ��
	long			mTextEffectTickCount;

protected:
	//  ��ǰ��Ҫ���Ƶ������ǣ�
	EEntityTaskSign m_CurrentTaskSign;

	//  ��ǰ����ͼ���λ��
	float    m_foffset;

	//  �Ƿ�����λ��
	bool     m_bRset;

	//crr add����������ͼ�Ƿ��Ѿ����أ�����VisualComponent::drawAlwayseTopMostʹ��static������������
	ITexture* m_pTaskSignTexture;

private:
	// ����ɳ�Ա�������������ѡ���ɫʱ����������
	ITexture* m_pHPTexture;
	//xsgui::Imageset* m_pHPImageSet;

	//Сͼ��
	ITexture * m_pIconTexture;
	//xsgui::Imageset * m_pIconImageSet;
	
	// ����ɳ�Ա�������������ѡ���ɫʱ����������
	ITexture* m_pTeamTexture;
	//xsgui::Imageset* m_pTeamImageSet;

private:

	// ������Чģ��
	ModelNode * m_pFinshTaskEffect;
	// ������Чģ��
	ModelNode * m_pAutoMoveEffect;
	// ������Чģ��
	ModelNode * m_pFinshAutoMoveEffect;

public:
	//static ITexture*		mSelectedTexture;	/// ʵ��ѡ��ʱ����ͼ

public:
	VisualComponent();
	virtual ~VisualComponent();

	virtual bool handleCommand(ulong cmd, ulong param1, ulong param2);
	virtual void handleMessage(ulong msgId, ulong param1, ulong param2);

	virtual void onEnterViewport(int priority = 0)				{ }
	virtual void onLeaveViewport()								{ }
	virtual void drawPickObject(IRenderSystem* pRenderSystem)	{ }
	virtual void drawShadow(IRenderSystem* pRenderSystem)		{ }
	virtual void draw(IRenderSystem* pRenderSystem)				{ }
	virtual void drawTopMost(IRenderSystem* pRenderSystem);
	//���������Ҫ���²ŵ��ø��º�����Ŀǰ�������඼�����ˣ���ֹ��bug
	virtual bool update(float tick, float deltaTick, IRenderSystem* pRenderSystem);
	virtual OccupantTileList* getOccupantTileList() const		{ return NULL; }
	virtual size_t onLoad(Stream* stream, size_t len)			{ return 0; }
	virtual size_t onSave(Stream* stream) const					{ return 0; }
	virtual bool isTransparent(int x, int y)					{ return false; }
	virtual void onAddEntity();
	virtual void onRemoveEntity();
	virtual const xs::Rect& getShowRect() const						{ return mShowRect; }
	virtual void drawAlwayseTopMost(IRenderSystem* pRenderSystem);

	// ���ƶ�����Ч
	virtual void drawTopMostEffect(IRenderSystem* pRenderSystem);
	virtual const AABB& GetAABB(){return  getOwner()->m_AABB;};
	virtual const Matrix4& GetFullTransform(){return getOwner()->m_FullTransform;}

protected:
	void updateWorldCoord();
	void setFadeIn();
	void setFadeOut();
	void setFadeDie(); //��������(wan)
};


#endif // __VISUALCOMPONENT_H__
