//==========================================================================
/**
* @file	  : IGlobalClient.h
* @author : 
* created : 2008-1-14   15:47
* purpose : �ͻ���ȫ�ֶ���
*/
//==========================================================================

#ifndef __IGLOBALCLIENT_H__
#define __IGLOBALCLIENT_H__

#include <string>

//���ڵĿͻ��˸�ģ�������̫ǿ���޷�ͨ����������ʵ��ҳ�����ת
//Ŀǰ�뵽�ķ�����ͨ�����ʹ�����Ϣ����Ϊϵͳ�˵���ʵ�ֻ���
enum
{
	WM_BACK_TO_SELECT_SERVER = WM_USER + 0,
	WM_BACK_TO_RE_LOGIN = WM_USER + 1,			//�����߻�����Ҫ��ת����¼����
	WM_BACK_TO_SELECT_ACTOR = WM_USER + 2,
};

namespace xs {
	struct IEventEngine;
	struct ISchemeEngine;
	struct ILuaEngine;
	struct IResourceManager;
	struct IConnection;
}

struct ISceneManager2;
struct IMessageDispatch;
struct IInputMessageManager;
struct IEntityFactory;
struct IEntityClient;
struct IEffectClient;
struct IBuffClient;
struct ISkillManager;
struct IFreezeClient;
struct IChatClient;
struct ISkepClient;
struct IFormManager;
struct IPKModeClient;
struct IGoodsFunctionClient;
struct ITradeClient;
struct IConfigManager;
struct IServerListConfig;
struct ITeamClient;
struct IFriendClient;
struct IAudioEngine;
class ITaskClient;
struct IProgressManager;
struct IStallClient;
struct ICollectionClient;
struct IHardwareCursorCallBack;
struct IFamilyClient;
struct IArmyClient;


//#define MEM_LEAK_TEST
#ifdef MEM_LEAK_TEST
	// �����ڴ�й¶ [5/5/2011 zgz]
	enum EMemCreateType
	{
		MemType_MapEffect = 1, // �ر���Ч(��flagMapItem���)
		MemType_MapStatic = 2, // ��̬ʵ��
		MemType_Occupant  = 3, // ռλ��Ϣ
	};
	class EntityView;
#endif

/// Ϊϵͳ����ļ���Ԥ������
enum SysFont
{
	fontDefault = 0,
	fontEffect,			// ��Ч����
	fontHeadEffect,		// ͷ����Ч
	fontEffect_XK,      // ��Ч����2
	maxFontCount,
};

struct IGlobalClient
{

#ifdef RKT_UI_TEST
	//virtual bool isUITest() const = 0;
#endif
	/// ��ȡ����Ŀ¼(exe����Ŀ¼)
	virtual const std::string& getWorkDir() const = 0;

	/// ��ȡ���ھ��
	virtual void* getHWND() const = 0;

	/// ��ȡĿ¼̬�����ļ�ϵͳ
	virtual IFileSystem* getFileSystemRoot() const = 0;

	/// ��ȡʱ���
	virtual ulong getTimeStamp() const = 0;

	/// ����ʱ���
	virtual void setTimeStamp(ulong ts) = 0;

	/// ��ȡʱ�䣨��Ϊ��λ��
	virtual ulong getTimeSecond() const = 0;

	/// ����ʱ�䣨��Ϊ��λ����������ʱ�䣩
	virtual void setTimeSecond(ulong ts) = 0;

	/// ��ȡ����
	virtual handle getPlayer() const = 0;

	/// ��������
	virtual void setPlayer(handle entity) = 0;

	/// ��ȡĿ��ʵ�����
	virtual handle getTarget() const = 0;

	/// ����Ŀ��ʵ�����
	virtual void setTarget(handle entity) = 0;


	// -----------------------����ģ��----------------------
	///����
	virtual IAudioEngine* getAudioEngine() const = 0;
	/// ��ȡ��Ⱦ����
	virtual IRenderEngine* getRenderEngine() const = 0;

	/// ��ȡ��Ⱦϵͳ
	virtual IRenderSystem* getRenderSystem() const = 0;

	/// ��ȡϵͳԤ������
	virtual xs::IFont* getFont(int type = fontDefault) const = 0;


	/// ��ȡ�¼�������
	virtual IEventEngine* getEventEngine() const = 0;

	/// ��ȡ��������
	virtual ISchemeEngine* getSchemeEngine() const = 0;

	/// ��ȡʱ����
	virtual TimerAxis* getTimerAxis() const = 0;

	/// ��ȡʵ�������
	virtual IEntityClient* getEntityClient() const = 0;

	/// ��ȡ�ű�����
	virtual ILuaEngine* getLuaEngine() const = 0;

	/// ��ȡ��Ϣ�ַ���
	virtual IMessageDispatch* getMessageDispatch() const = 0;

	/// ��ȡ������Ϣ������
	virtual IInputMessageManager* getInputMessageManager() const = 0;

	/// ��ȡ��Դ������
	virtual IResourceManager* getResourceManager() const = 0;

	/// ��ȡʵ����ͼ����
	virtual IEntityFactory* getEntityFactory() const = 0;

	/// ��ȡ����������
	virtual ISceneManager2* getSceneManager() const = 0;

	/// ��ȡ��������
	virtual IConnection* getNetConnection() const = 0;

	/// ��ȡЧ���ͻ���
	virtual IEffectClient* getEffectClient() const = 0;

	/// ��ȡBuff�ͻ���
	virtual IBuffClient* getBuffClient() const = 0;

	/// ��ȡ���ܹ�����
	virtual ISkillManager* getSkillManager() const = 0;

	/// ��ȡ��ȴϵͳ
	virtual IFreezeClient* getFreezeClient() const = 0;

	/// ��ȡ�ɼ�ϵͳ
	virtual ICollectionClient* getCollectionClient() const = 0;

	/// ��ȡ����ͻ���
	virtual IChatClient* getChatClient() const = 0;

	/// ��ȡͨ����Ʒ��
	virtual ISkepClient* getSkepClient() const = 0;

	/// ���Form������ 
	virtual IFormManager* getFormManager() const = 0;

	/// ���PK�ͻ���
	virtual IPKModeClient* getPKModeClient() const = 0;

	/// �����ӿͻ���
	virtual ITeamClient* getTeamClient() const = 0;

	/// ��ú��ѿͻ���
	virtual IFriendClient* getFriendClient() const = 0;

	/// ��ð�̯�ͻ���
	virtual IStallClient* getStallClient() const = 0;

	/// ��ü���ͻ���
	virtual IFamilyClient* getFamilyClient() const = 0;

	/// ��þ��ſͻ���
	virtual IArmyClient* getArmyClient() const = 0;

	/// 
	virtual IGoodsFunctionClient* getGoodsFunctionClient() const = 0;

	/// ��ý��׿ͻ���
	virtual ITradeClient* getTradeClient() const = 0;

    //  �������ͻ��ˣ�
    virtual ITaskClient* GetTaskClient() const = 0;

	// �ͻ������ã����Ʊ����û�������Ļ�ֱ��ʵȵ�
	virtual IConfigManager* getConfigManager() const = 0;

	//��ȡ�������б�
	virtual IServerListConfig * getServerListConfig() const = 0;

	//�˳���¼
	virtual void Logout(void) = 0;

	//��λ��Ϸ�߼���ص��������ITaskClient , IFriendClient�ȵȵȵȣ���������ѡ�������
	virtual bool ResetCompentsForSelectServer(void) = 0;

	//��λ��Ϸ�߼���ص��������ITaskClient , IFriendClient�ȵȵȵȣ���������ѡ���ɫ
	virtual bool ResetCompentsForSelectActor(void) = 0;

	//��ȡ���ȹ�����
	virtual IProgressManager * getProgressManager() const = 0;

	//��ȡӲ�������Ϣ�ص�
	virtual IHardwareCursorCallBack* getHarewareCursorCallBack() const = 0;

#ifdef MEM_LEAK_TEST
	virtual void CreateEntityView(EntityView* entityView, EMemCreateType type) const = 0;	
	virtual void ReleaseEntityView(EntityView* entityView) const = 0;	
#endif

};

#define gGlobalClient	((IGlobalClient*)::xs::getGlobal())



#endif // __IGLOBALCLIENT_H__