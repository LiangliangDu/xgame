//==========================================================================
/**
* @file	  : FlowText.h
* @author : 
* created : 2008-2-29   10:24
* purpose : �������ּ������
*/
//==========================================================================

#ifndef __FLOWTEXT_H__
#define __FLOWTEXT_H__

#include "IEntityFactory.h"

struct Interpolate
{
	virtual void create(float first, float last, ulong total_time) = 0;
	virtual float getFrame(ulong time) const = 0;
};

// �����˶�
class InterpolateLiner : public Interpolate
{
	float _first;
	float _last;
	ulong _time;
	float _v;
public:
	virtual void create(float first, float last, ulong total_time)
	{
		_first = first;
		_last = last;
		_time = total_time;
		_v = (total_time == 0) ? 0.f :(last - first) / (float)total_time;
	}
	virtual float getFrame(ulong time) const
	{
		if (time < _time)
			return _first + _v * (float)time;
		return _last;
	}
};

// �ȼ����˶�
//vt = v + a*t
//s = v0*t + a*t*t/2
class InterpolateAccelerative : public Interpolate
{
	float _v0;
	float _a;
	ulong _time;
	float _last;
public:
	virtual void create(float first, float last, ulong total_time)
	{
		_v0 = first;
		_a = last;
		_time = total_time;
		_last = _v0*_time + 0.5f*_a*_time*_time;
	}
	virtual float getFrame(ulong time) const
	{
		if (time < _time)
			return  _v0*time + 0.5f*_a*time*time;
		return _last;
	}
};


/// ��������
class FlowText : public TimerHandler
{
public:	
	autostring		mText;		/// �ַ���
	ColorValue		mColor;		/// ������ɫ
	xs::Point			mPos;		/// ��Ļλ��
	ulong			mTotalTime;	/// ��ʱ��
	CoordAlign		mCoordAlign;/// ������뷽ʽ

	bool			mRunning;	/// �Ƿ���������
	ulong			mCurTime;	/// ��ǰʱ��
	SysFont			mFont;		/// ����


	Interpolate*	mPosX;		/// λ��X
	Interpolate*	mPosY;		/// λ��Y
	Interpolate*	mAlpha;		/// ��ɫ��alphaֵ
	Interpolate*	mSize;		/// ���ִ�С

	FlowText();
	~FlowText();

	bool create(const FlowTextContext& context);
	void close();

	bool isRunning() const			{ return mRunning; }
	void update(ulong deltaTime);
	void render(IRenderSystem* pRenderSystem);

	virtual void OnTimer( unsigned long dwTimerID );
};
/*
struct ColorItem
{
	const wchar_t*	mText;
	ColorValue		mColor;
};

// e.g: <color:FFFF00>FlowTextItem<br><color:FF0000>���Ƕ����й���</color>haha</color>
struct FlowTextItem
{
	typedef std::list<ColorItem>	ColorItemList;
	ColorItemList	mList;
	float			mScale;
	float			mPosX, mPosY;
	float			mAlpha;

	void update(ulong deltaTime)
	{
	}

	void render(IRenderSystem* pRenderSystem)
	{

	}
};

class FlowTextArea
{
	typedef std::list<FlowTextItem*>	FlowTextItemList;
	FlowTextItemList	mList;
	ulong				mAlign;			/// �����е���Ŀ���䷽ʽ,0-�����,1-���ж���,2-�Ҷ���
	xs::Rect				mRect;			/// ��ʾ����(�����������Ļ�����ƫ��)
public:
	void add(const std::string& text);
	void update(ulong deltaTime);
	void render(const xs::Point& pos, IRenderSystem* pRenderSystem);
private:
	inline int getWidth() const		{ return mRect.right - mRect.left; }
	inline int getHeight() const	{ return mRect.bottom - mRect.top; }
};*/

struct FlowItem
{
	const wchar_t*	text;
	ColorValue	color;
	float offY;
	float scale;
	SysFont font;
};
typedef std::list<FlowItem>	FlowItemList;

/// �������������ж���������֣����ڽ�ɫ�Աߵ���Ϣ��ʾ��
class FlowArea
{
	xs::Rect	mRect;			/// ��ʾ����(�����������Ļ�����ƫ��)
	float	mSpeed;			/// �����ٶȻ���alpha�������ٶ�
	float	mScale;			/// �������ű���
	bool	mScroll;		/// �Ƿ������Զ�����
	bool    mIsCover;		/// �Ƿ��������ָ���
	bool	mIsEffect;		/// �Ƿ���Ҫ����Ч�����������������
	bool	mIsChangeA;		/// �Ƿ�ı�alpha
	FlowItemList mList;
	
public:
	FlowArea();
	~FlowArea();

	bool create(const xs::Rect& rc, float speed, float scale, bool scroll = true,bool isCover = false,bool isEffect = false,bool isChangeA = true);
	void close();
	void add(const std::string& text, const ColorValue& color,const DWORD font = 0);
	void update(ulong deltaTime);
	void render(const xs::Point& pt, IRenderSystem* pRenderSystem);
	bool needRender() const			{ return !mList.empty(); }

	FlowItem* GetLastFlowItem(void)
	{
		if (mList.empty())
		{
			return NULL;
		}
		else
		{
			return &(mList.back());
		}
	}
private:
	bool changePos();
	void update(float offY);
	inline int getWidth() const		{ return mRect.right - mRect.left; }
	inline int getHeight() const	{ return mRect.bottom - mRect.top; }
};



class FlowTextManager : public SingletonEx<FlowTextManager>
{
	typedef std::list<FlowText*>	FlowTextList;
	FlowTextList	mList;				/// ��Ļ�еĸ��������б���Ҫ����ƮѪ
	FlowArea		mFlowArea[MaxFlowAreaCount-1];
	FlowTextList	mMouseTipsList;		/// ��������ʾ�б�

public:
	FlowTextManager();
	~FlowTextManager();

	void flowText(const FlowTextContext& context);
	void flowAreaText(int area, const std::string& text, const ColorValue& color,const DWORD font = 0);

	const std::string GetLastFlowString(FlowAreaType area);

	void updateFlowText(ulong deltaTime);
	void updateSystemTips(ulong deltaTime);

	void renderFlowText(IRenderSystem* pRenderSystem);
	void renderSystemTips(IRenderSystem* pRenderSystem);
};

#endif // __FLOWTEXT_H__