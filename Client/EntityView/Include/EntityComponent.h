//==========================================================================
/**
* @file	  : EntityComponent.h
* @author : 
* created : 2008-1-25   17:40
* purpose : ʵ�����
*/
//==========================================================================

#ifndef __ENTITYCOMPONENT_H__
#define __ENTITYCOMPONENT_H__



typedef ulong ComponentID;

enum
{
	ComponentIDVisual,	/// ���ӻ����
	ComponentIDMove,	/// �ƶ����
	ComponentIDState,	/// ״̬���

	MaxComponentIDCount,
};


class EntityViewImpl;

class EntityComponent
{
	EntityViewImpl* mOwner; /// ���ӵ���߶���
public:
	EntityComponent() : mOwner(NULL)		{ }
	virtual ~EntityComponent()				{ }

	inline void setOwner(EntityViewImpl* owner)	{ mOwner = owner; }
	inline EntityViewImpl* getOwner() const	{ return mOwner; };

	/// ���﷢����new�����ĳ�ʼ������
	virtual void create()					{}

	/// ���﷢����delete����ǰ���������
	virtual void close()					{}

	/// ���������������ˣ��ͷ���true�����򷵻�false
	virtual bool handleCommand(ulong cmd, ulong param1, ulong param2)	{ return false; }

	/// ������������Ϣ
	virtual void handleMessage(ulong msgId, ulong param1, ulong param2)	{ }
};


#endif // __ENTITYCOMPONENT_H__