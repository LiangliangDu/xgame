#ifndef __RideManager_H__
#define __RideManager_H__

class VisualComponentMZ;

struct RideCallBackContext
{
	ModelNode* pRideNode;//pRideNode=0,��ʾ����pRideNode!=0,��ʾ����
	std::string strBindPoint;//��˰󶨵�
	ulong		ulRideResId;//�����Դid
};

struct IRideCallBack
{
	virtual void onRide(RideCallBackContext& context)=0;
};

class RideManager
{
public:
	bool ride(bool bRide, ulong resId);//���
	void update();//����
	void releaseRes();//�ͷ���Դ
	void requestRes(int priority);//������Դ
	void setCanRequestRes(bool canRequest);//�ܷ�������Դ
	bool isRide();	//�Ƿ������״̬
public:
	RideManager();
	void create(VisualComponentMZ* pOwner, IRideCallBack* pCallBack);
	~RideManager();

private:
	//�����߼�
	IRideCallBack*		m_pRideCallBack;//��˻ص�����
	VisualComponentMZ*	m_pOwner;		//������VisualComponentMZ
	bool				m_bIsRide;		//�Ƿ������״̬
	ulong				m_ulResId;		//�����Դid�����m_bIsRide=false��m_ulResId=0�����m_bIsRide=true��m_ulResId!=0;

	//������Դ
	bool				m_bCanRequestRes;//�ܷ������Դ
	ModelNode*			m_pRideNode;	//��˽ڵ㣬�������״̬��������Դ�Ѿ����غ��ˣ��ŷ�0������Ϊ0
	ulong				m_ulNewResId;	//������Դ�������������ԴID
	xs::handle			m_handle;		//��Դhandle	
	bool				m_bLoaded;		//��Դ�Ƿ������
};

#endif