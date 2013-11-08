//==========================================================================
/**
* @file	  : GlobalClient.h
* @author : 
* created : 2008-1-14   15:51
* purpose : �ͻ���ȫ�ֶ���ʵ��
*/
//==========================================================================

#ifndef __GLOBALCLIENT_H__
#define __GLOBALCLIENT_H__

#include "IGlobalClient.h"

class GlobalClient : public IGlobalClient
{
	Timer			mTimer;					/// ʱ��
	std::string		mWorkDir;				/// ����Ŀ¼
	void*			mhWnd;					/// ���ھ��
	IFileSystem*	mFileSystemRoot;		/// Ŀ¼̬�ļ�ϵͳ��ָ����Ŀ¼
	uint			mTimeStampServer;		/// ������ͬ��������ʱ���
	uint			mTimeStampClient;		/// ������ʱ���ͬ�����ͻ���ʱ��tick
	handle			mPlayer;				/// ���ʵ��
	handle			mTarget;				/// ���ѡ���Ŀ��ʵ��

	// 3D
	IRenderEngine*	mRenderEngine;			/// ��Ⱦ����
	IFont*			mFonts[maxFontCount];	/// ϵͳԤ������
	Viewport*		mViewport;
	Camera*			mCamera;
	Light*			mLight;

	// service
	//MessageDispatch		mMsgDispatch;			/// ��Ϣ�ַ���
	IResourceManager*	mResourceManager;		/// ��Դ������
	IEntityFactory*		mEntityFactory;			/// ʵ�幤��
	ISceneManager2*		mSceneManager;			/// ����������
	IEventEngine*		mEventEngine;			/// �¼�����
	ISchemeEngine*		mSchemeEngine;			/// ���÷���
	//IConnection*		mNetConnection;			/// ��������
	IEntityClient*		mEntityClient;			/// ʵ�����
	//IEffectClient*		mEffectClient;			/// Ч���ͻ���
	//IBuffClient*		mBuffClient;			/// Buff�ͻ���
	//ISkillManager*		mSkillManager;			/// ���ܹ�����
	//IFreezeClient*		mFreezeClient;			/// ��ȴϵͳ
	//IChatClient*		mChatClient;			/// ����ͻ���
	//ISkepClient*		mSkepClient;			/// ͨ����Ʒ��
	//IFormManager*		mFormManager;			/// ������ 
	//IPKModeClient*		mPKModeClient;			/// PK�ͻ���
	//ITeamClient*		mTeamClient;			/// ��ӿͻ���
	//IFriendClient*		mFriendClient;			/// ���ѿͻ���
	//IGoodsFunctionClient*	mGoodsFunctionClient;
	//ITradeClient*		mTradeClient;			/// ���׿ͻ���
	IConfigManager*		mConfigManager;			/// �ͻ�������
	IServerListConfig*  mServerListConfig;      /// �������б�����
	IAudioEngine*       mAudioEngine;           /// ����
    //  �����������
	//ITaskClient* m_pTaskClient;

	TimerAxis*			mTimerAxis;				/// ʱ����
	ILuaEngine*			mLuaEngine;				/// Lua����

	//TxGuiRenderer*		mGuiRenderer;			/// GUI��Ⱦ��

		
	//IProgressManager *	mProgressManager;		//���ȹ�����


	//GameForm*			frmGame; // TODO remove!!!

public:
	GlobalClient();
	virtual ~GlobalClient();

	bool create(void* hwnd);
	void close();

	Viewport* getViewPort(){return mViewport;}
	Camera*	  getCamera(){return mCamera;}
	// IGlobalClient
public:
	/// ��ȡ����Ŀ¼(exe����Ŀ¼)
	virtual const std::string& getWorkDir() const
	{ return mWorkDir; }

	virtual void* getHWND() const
	{ return mhWnd; }

	/// ��ȡĿ¼̬�����ļ�ϵͳ
	virtual IFileSystem* getFileSystemRoot() const
	{ return mFileSystemRoot; }

	/// ��ȡʱ���
	virtual ulong getTimeStamp() const
	{ return (mTimer.getTime() - mTimeStampClient + mTimeStampServer); }

	/// ����ʱ���
	virtual void setTimeStamp(ulong ts)
	{ mTimeStampServer = ts; mTimeStampClient = mTimer.getTime(); }

    virtual ulong getTimeSecond() const
    {
        return 0;
    }
    
	/// ��ȡ����
	virtual handle getPlayer() const
	{ return mPlayer; }

	/// ��������
	virtual void setPlayer(handle entity)
	{ mPlayer = entity; }

	/// ��ȡĿ��ʵ�����
	virtual handle getTarget() const
	{ return mTarget; }

	/// ����Ŀ��ʵ�����
	virtual void setTarget(handle entity)
	{ mTarget = entity; }


	// -----------------------����ģ��----------------------
	/// ����
	virtual IAudioEngine* getAudioEngine() const
	{
		return mAudioEngine;
	}
	/// ��ȡ��Ⱦ����
	virtual IRenderEngine* getRenderEngine() const
	{ return mRenderEngine; }

	/// ��ȡ��Ⱦϵͳ
	virtual IRenderSystem* getRenderSystem() const
	{ return mRenderEngine ? mRenderEngine->getRenderSystem() : 0; }

	/// ��ȡĬ������
	virtual IFont* getFont(int type = fontDefault) const;
    
    
    virtual IEventEngine* getEventEngine() const
	{ return mEventEngine; }
    
	virtual ISchemeEngine* getSchemeEngine() const
	{ return mSchemeEngine; }
    
	virtual TimerAxis* getTimerAxis() const
	{ return mTimerAxis; }
    
    
    virtual IEntityClient* getEntityClient() const
	{ return mEntityClient; }
    
    
    virtual ILuaEngine* getLuaEngine() const
	{ return mLuaEngine; }
    
    
    virtual IMessageDispatch* getMessageDispatch() const
	//{ return const_cast<IMessageDispatch*>(static_cast<const IMessageDispatch*>(&mMsgDispatch)); }
	{
		return 0;
	}
    
	virtual IInputMessageManager* getInputMessageManager() const
	//{ return static_cast<IInputMessageManager*>(InputMessageManager::getInstancePtr()); }
	{
		return 0;
	}

	virtual IResourceManager* getResourceManager() const
	{ return mResourceManager; }

	virtual IEntityFactory* getEntityFactory() const
	{ return mEntityFactory; }

	virtual ISceneManager2* getSceneManager() const
	{ return mSceneManager; }

	
	virtual IConnection* getNetConnection() const
	{
        return 0;//mNetConnection;
    }
	
	virtual IEffectClient* getEffectClient() const
	{return 0;}//{ return mEffectClient; } 

	virtual IBuffClient* getBuffClient() const
	{return 0;}//{ return mBuffClient; }

	virtual ISkillManager* getSkillManager() const
	{return 0;}//{ return mSkillManager; }

	virtual IFreezeClient* getFreezeClient() const
	{return 0;}//{ return mFreezeClient; }
    
    virtual ICollectionClient* getCollectionClient() const
    {return 0;}

	virtual IChatClient* getChatClient() const
	{return 0;}//{ return mChatClient; }

	virtual ISkepClient* getSkepClient() const
	{return 0;}//{ return mSkepClient;}

	virtual IFormManager* getFormManager() const
	{return 0;}//{ return mFormManager;}

	virtual IPKModeClient* getPKModeClient() const
	{return 0;}//{ return mPKModeClient; }

	virtual ITeamClient* getTeamClient() const
	{return 0;}//{ return mTeamClient; }

	virtual IFriendClient* getFriendClient() const
	{return 0;}//{ return mFriendClient; }
    
    virtual IStallClient* getStallClient() const {return 0;}
    
    virtual IFamilyClient* getFamilyClient() const {return 0;}
    
    virtual IArmyClient* getArmyClient() const {return 0;}

	virtual IGoodsFunctionClient* getGoodsFunctionClient() const
	{return 0;}//{ return mGoodsFunctionClient; }

	virtual ITradeClient* getTradeClient() const
	{return 0;}//{ return mTradeClient; }

    virtual ITaskClient* GetTaskClient() const
    {return 0;}//{return m_pTaskClient;}

	virtual IConfigManager* getConfigManager() const
	{return 0;}//{return mConfigManager;}

	virtual IServerListConfig * getServerListConfig() const
	{return 0;}//{return mServerListConfig;}

	//�˳���¼
	virtual void Logout(void);

	//��λ��Ϸ�߼���ص��������ITaskClient , IFriendClient�ȵȵȵȣ���������ѡ�������
	virtual bool ResetCompentsForSelectServer(void);

	//��λ��Ϸ�߼���ص��������ITaskClient , IFriendClient�ȵȵȵȣ���������ѡ���ɫ
	virtual bool ResetCompentsForSelectActor(void);

	//��ȡ���ȹ�����
	virtual IProgressManager * getProgressManager() const
	{
		return 0;
		//return mProgressManager;
	}

    virtual IHardwareCursorCallBack* getHarewareCursorCallBack() const {return 0;}
private:
	bool init3D(void* hwnd);
	bool initUI();

};


#endif // __GLOBALCLIENT_H__