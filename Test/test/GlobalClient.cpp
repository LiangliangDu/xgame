//==========================================================================
/**
* @file	  : GlobalClient.cpp
* @author : 
* created : 2008-1-14   15:52
*/
//==========================================================================

//#include "stdafx.h"

#include "Base.h"
//#include "Common.h"
//#include "Handle.h"
//#include "FileSystem/IFileSystem.h"

using namespace xs;
#include "Re.h"
#include "IRenderSystem.h"
#include "IRenderEngine.h"

#include "GlobalClient.h"
//#include "InputMessageManager.h"
#include "Config.h"
//#include "IProgressManager.h"
#include "ILuaEngine.h"
#include "ISchemeEngine.h"
#include "IEventEngine.h"
#include "IEntityFactory.h"
#include "IAudioEngine.h"

#include "IResourceManager.h"
#include "ISceneManager2.h"
//#include "net.h"

extern int tolua_app_open(lua_State* tolua_S);


ostrbuf myosb;
static DWORD g_startTick,g_endTick;

#define CREATE_BEGIN(s)		g_startTick = getTickCount(); myosb.clear();myosb<<s
#define CREATE_ERROR()		//myosb<<"Failed LastError=" << GetLastError() <<endl;Error(myosb.c_str())
#define CREATE_SUCCESS()	g_endTick = getTickCount(); myosb<<"OK, timing " << (g_endTick - g_startTick) << "ms"<<endl;Trace(myosb.c_str())

#if (TARGET_PLATFORM != PLATFORM_WIN32)
extern bool GetClientRect(HWND hwnd,RECT* rc); 
#endif

// TODO �����Trace���ڵ�����Ϣ��ʾ����Ҫɾ��
class ScreenTrace : public TraceListener
{
public:
	virtual void onTrace(const char* msg, const char* time, TraceLevel level)
	{
		/*
		FlowTextContext ftc;
		ftc.flowType = FlowType_Liner;
		ftc.align = CoordAlign_Screen;
		if (level == levelInfo)
			ftc.color = ColorValue(1,1,1,1);
		else if (level == levelTrace)
			ftc.color = ColorValue(0,1,0,1);
		else if (level == levelWarning)
			ftc.color = ColorValue(1,0,1,1);
		else if (level == levelError)
			ftc.color = ColorValue(1,0,0,1);
		ftc.lastAlpha = 0.5f;
		ftc.pos.x = 300;
		ftc.pos.y = 400;
		ftc.posOffset.x = 0;
		ftc.posOffset.y = -400;
		ftc.text = msg;
		ftc.totalTime = 4000;
		if (gGlobalClient->getEntityFactory())
			gGlobalClient->getEntityFactory()->flowText(ftc);
			*/
		printf("\n %s : %s",time,msg);
	}
};

TraceListener* mytrace = 0;

GlobalClient::GlobalClient()
: mResourceManager(0), mhWnd(0),
mRenderEngine(0), mViewport(0), mCamera(0), mLight(0), 
mEntityFactory(0), mSceneManager(0)//,mNetConnection(0)
,mEventEngine(0), mSchemeEngine(0), mLuaEngine(0),mAudioEngine(0),
//mGuiRenderer(0),frmGame(0),
//mEffectClient(0), mBuffClient(0), mEntityClient(0),mSkillManager(0),
//mFreezeClient(0), mChatClient(0), mSkepClient(0),mFormManager(0),mPKModeClient(0),mTeamClient(0), mFriendClient(0),
//mGoodsFunctionClient(0),mTradeClient(0),
mConfigManager(0),mServerListConfig(0)
//,mProgressManager(0)
{
	setGlobal(static_cast<IGlobalClient*>(this));

	mWorkDir = xs::getWorkDir();
	mFileSystemRoot = openFileSystem(mWorkDir.c_str());
	memset(&mFonts, 0, sizeof(mFonts));
	mTimeStampClient = mTimeStampServer = getTickCountEx();
}

GlobalClient::~GlobalClient()
{
	close();
	setGlobal(NULL);
}


bool GlobalClient::create(void* hwnd)
{

	try{
		mhWnd = hwnd;

		
		//�������ȹ�����
		/*
		registerImageCodec();
		CREATE_BEGIN(" CreateProgressManager.........");
		if( (mProgressManager = CreateProgressManager()) == NULL )
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();
		

		mProgressManager->StartInitGameProgress( 30);//����30�����ȱ任
		*/

		//new InputMessageManager();

		// ��ʼ����Ⱦ����
		CREATE_BEGIN(" init3D.........................");
		if (!init3D(hwnd))
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();


		// ����
		CREATE_BEGIN("CreateDefaultFont..............");
		IFontManager* fontManager = mRenderEngine->getFontManager();
        /*
		mFonts[fontDefault] = fontManager->createFont(mRenderEngine->getRenderSystem(), 
			mRenderEngine->getRenderSystem()->getTextureManager(), "Default", "Data\\Fonts\\msyh.ttf", 18);

		mFonts[fontEffect] =  fontManager->createFont(mRenderEngine->getRenderSystem(), 
			mRenderEngine->getRenderSystem()->getTextureManager(), "Effect", "Data\\Fonts\\msyh2.ttf", 48);
*/
		if (!mFonts[fontDefault])
		{
			CREATE_ERROR();
			//return false;
		}
		CREATE_SUCCESS();


		// ��Դ������
		CREATE_BEGIN("CreateResourceManager..........");
		//if ((mResourceManager = CreateResourceManagerProc(1)) == NULL)
		if ((mResourceManager = CreateResourceManagerProc(0)) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();

		// ��������
		CREATE_BEGIN("CreateSchemeEngine.............");
		if ((mSchemeEngine = CreateSchemeEngineProc()) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();

		/*
		Config *pConfigManager = new Config;
		pConfigManager->load("config.xml");
		mConfigManager = pConfigManager;

		ServerListConfig * pServerListConfig = new ServerListConfig;
		pServerListConfig ->load("ServerList.xml");
		mServerListConfig = pServerListConfig;
		*/

        /*
		// �¼�����
		CREATE_BEGIN("CreateEventEngine..............");
		if ((mEventEngine = CreateEventEngineProc()) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();
        */


		// ʱ����
		CREATE_BEGIN("CreateTimerAxis................");
		mTimerAxis = new TimerAxis();
		if (!mTimerAxis)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();


        /*
		// Lua����
		CREATE_BEGIN("CreateLuaEngine................");
		if ((mLuaEngine = CreateLuaEngineProc(true)) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();
         */


        /*
		// ʵ�幤��
		CREATE_BEGIN("CreateEntityFactory............");
		if ((mEntityFactory = CreateEntityFactoryProc()) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();
         */


		// ʵ�����
		/*
		CREATE_BEGIN("CreateEntityClient.............");
		if ((mEntityClient = CreateEntityClientProc()) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();
		


		// Ч������
		CREATE_BEGIN("CreateEffectClient.............");
		if ((mEffectClient = CreateEffectClientProc()) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();


		// ��ȴϵͳ
		CREATE_BEGIN("CreateFreezeClient.............");
		if ((mFreezeClient = CreateFreezeClientProc()) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();


		// Buff����
		CREATE_BEGIN("CreateBuffClient...............");
		if ((mBuffClient = CreateBuffClientProc()) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();


		// ����ϵͳ
		CREATE_BEGIN("CreateChatClient...............");
		if ((mChatClient = CreateChatClientProc()) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();


		// ͨ����Ʒ��
		CREATE_BEGIN("CreateSkepClient...............");
		if ((mSkepClient = CreateSkepClientProc()) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();
		*/


		// ����������
		CREATE_BEGIN("CreateSceneManager.............");
		if ((mSceneManager = CreateSceneManagerProc(mResourceManager)) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();


		//����������
        CREATE_BEGIN("CreateAudioEngine..............");
		if ((mAudioEngine = CreateAudioEngineProc(32,32)) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();

		/*
		// ���ܹ�����
		CREATE_BEGIN("CreateSkillManager.............");
		if ((mSkillManager = CreateSkillManagerProc()) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();


		// PK������
		CREATE_BEGIN("CreatePKModeClient.............");
		if ((mPKModeClient = CreatePKModeClientProc()) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();


		// ��ӿͻ���
		CREATE_BEGIN("CreateTeamClient...............");
		if ((mTeamClient = CreateTeamClientProc()) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();


		// ���ѿͻ���
		CREATE_BEGIN("CreateFriendClient.............");
		if ((mFriendClient = CreateFriendClientProc()) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();
	

		// ��װ������Ʒ������
		CREATE_BEGIN("CreateGoodsFunctionClient......");
		if ((mGoodsFunctionClient = CreateGoodsFunctionClientProc()) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();
		*/

        /*
		// ����
		CREATE_BEGIN("CreateTCPConnection............");
		InitializeNetwork();
		if ((mNetConnection = CreateTCPConnectionProc(0, 0, DEFAULT_PACK)) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();
         */

		/*
		// ������
		CREATE_BEGIN("CreateFormManager .............");
		if ((mFormManager = CreateFormManagerProc()) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();

        // ����ϵͳ
		CREATE_BEGIN("CreateTradeClient..............");
		if ((mTradeClient = CreateTradeClientProc()) == NULL)
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();



        //  �����������
        CREATE_BEGIN("CreateTaskClient...............");
        if ((m_pTaskClient = CreateTaskClientProc()) == NULL)
        {
            CREATE_ERROR();
            return false;
        }
        CREATE_SUCCESS();


        // ��ʼ��UI
        CREATE_BEGIN("initUI.........................");
        if (!initUI())
        {
            CREATE_ERROR();
            return false;
        }
        CREATE_SUCCESS();


#ifdef USE_UI
		rktgui::EventArgs ea;
		rktgui::System::getSingletonPtr()->getRenderer()->fireEvent(rktgui::Renderer::EventDisplaySizeChanged,ea);
#endif
		*/

		int left,top,width,height;
		mRenderEngine->getRenderSystem()->getViewport(left,top,width,height);

		/*
		//��ʼ����������
		 CREATE_BEGIN("mProgressManager->InitScheme().........................");
		if ( !mProgressManager->InitScheme())
		{
			CREATE_ERROR();
			return false;
		}
		CREATE_SUCCESS();

		//��������
		mProgressManager->StopInitGameProgress();
		*/

		//	ת���½���棻
        //mFormManager->toLogin();
        return true;
	}
	catch (...)
	{
		myosb<<endl;
		Trace(myosb.c_str());
		Error("GlobalClient::create, catch exception"<<endl);
	}

	return false;
}

#define MyRelease(ptr)		if ((ptr)) {(ptr)->Release(); (ptr) = 0;}
void GlobalClient::close()
{
#ifdef RKT_WIN32
	::ShowWindow((HWND)mhWnd, SW_HIDE);
#endif
	//if (!InputMessageManager::getInstancePtr()) return;

	Trace("unregisterTrace"<<endl);
	unregisterTrace(mytrace);
	
	mhWnd = 0;
	//try{
	//////////////////////////////////////////////////////////////////////////

		Trace("�رս��ȹ�����"<<endl);
		//MyRelease(mProgressManager);
		
		Trace("�ر�����"<<endl);
		// �ͷŸ���ģ��
		if (mRenderEngine)
		{
			for (int i=0; i<maxFontCount; i++)
				mRenderEngine->getFontManager()->releaseFont(mFonts[i]);
		}
		Trace("ֹͣ��Դ����"<<endl);
		//mResourceManager->stop();

		// ����ģ���ͷ�
		/*
		Trace("�رս���"<<endl);
		safeRelease(mTradeClient);
		Trace("�رշ�װ������Ʒ"<<endl);
		MyRelease(mGoodsFunctionClient);
		Trace("�ر�Ч��"<<endl);
		MyRelease(mEffectClient);
		Trace("�ر�Buff"<<endl);
		MyRelease(mBuffClient);
		Trace("�ر�����"<<endl);
		safeRelease(mChatClient);
		Trace("�ر����"<<endl);
		MyRelease(mTeamClient);

		Trace("�رպ���"<<endl);
		safeRelease(mFriendClient);
		Trace("�ر�EntityClient"<<endl);
		MyRelease(mEntityClient); //mEntityClient��ʹ��formManager

		Trace("�ر�Controller"<<endl);
		safeRelease(mFormManager); //formManager��ʹ��gameform��gameformʹ����skep�������ͷ�formManager

		Trace("�ر�mSkepClient"<<endl);
		MyRelease(mSkepClient);

		Trace("�ر�PK"<<endl);
		MyRelease(mPKModeClient);
		*/

		Trace("�رճ���"<<endl);
		safeRelease(mSceneManager);
		Trace("�ر�ʵ�幤��"<<endl);
		safeRelease(mEntityFactory);
		Trace("�ر���Դ����"<<endl);
		safeRelease(mResourceManager);
		
		/*
		Trace("�رռ���"<<endl);
		safeRelease(mSkillManager);
		*/
		Trace("�ر�����"<<endl);
		MyRelease(mAudioEngine); //not safeDelete !!!

		/*
        Trace("�ر����������"<<endl);
        safeDelete(m_pTaskClient);
		*/

		//safeDelete(frmGame);

// 		Trace("�ر�Controller"<<endl);
// 		safeRelease(mFormManager); //formManager��ʹ��gameform��gameformʹ����skep�������ͷ�formManager

		/*
#ifdef USE_UI
		Trace("�ر�UI"<<endl);
		delete rktgui::System::getSingletonPtr();
		safeDelete(mGuiRenderer);
#endif
		*/

		Trace("�ر���Ⱦ����"<<endl);
		safeDelete(mLight);
		safeRelease(mCamera);
		safeRelease(mViewport);
		safeRelease(mRenderEngine);

		Trace("�ر�������Ϣ������"<<endl);
		//delete InputMessageManager::getInstancePtr();

		/*
		Trace("�ر����ù�����"<<endl);
		if(mConfigManager)
		{
			static_cast<Config*>(mConfigManager)->save();
			delete static_cast<Config*>(mConfigManager);
			mConfigManager = 0;
		}

		if (NULL != mServerListConfig)
		{
			mServerListConfig->release();
			mServerListConfig = NULL;
		}
		*/

		// ȫ���Ե�ģ��
		Trace("�ر�����"<<endl);
		//MyRelease(mNetConnection);
		Trace("�ر���������"<<endl);
		MyRelease(mSchemeEngine);
		Trace("�ر�Lua����"<<endl);
		MyRelease(mLuaEngine);
		Trace("�ر��¼�����"<<endl);
		MyRelease(mEventEngine);
		Trace("�ر��¼���"<<endl);
		safeDelete(mTimerAxis); // TODO �ͷ�̫������ע��
		Trace("�ر�Trace"<<endl);
		closeTrace();

		//////////////////////////////////////////////////////////////////////////
		// �ͷ�Dll��Դ
		//CloseEntityFactory();
		//CloseSkillManager();
	//}
	//catch (...)
	{
	}
}

IFont* GlobalClient::getFont(int type) const
{
	Assert(type >= fontDefault && type < maxFontCount);
	return mFonts[type];
}


bool GlobalClient::init3D(void* hwnd)
{
	RenderEngineCreationParameters params;
	params.hwnd = hwnd;

	RECT rc;
	GetClientRect((HWND)hwnd, &rc);
	params.w = rc.right - rc.left;
	params.h = rc.bottom - rc.top;
	params.colorDepth = 32;
	params.fullscreen = false;
	params.refreshRate = 85;
	params.rst = RS_OPENGLES2;
	params.stencilBuffer = true;

	// ������Ⱦ����
	mRenderEngine = LoadRenderEngine(&params);
	if (!mRenderEngine)
	{
		Error("[3D]Create render engine failed"<<endl);
		return false;
	}

	GetClientRect((HWND)params.hwnd, &rc);
	// ��ȡ��Ⱦϵͳ
	IRenderSystem* renderSystem = mRenderEngine->getRenderSystem();

	// �����ӿ�
	mViewport = mRenderEngine->createViewport();
	Assert(mViewport != NULL);
	if (!mViewport)
	{
		Error("[3D]Create mViewport failed"<<endl);
		return false;
	}
	mViewport->setValues(0, 0, rc.right - rc.left, rc.bottom - rc.top);
	mViewport->setBackgroundColor(ColorValue(0.223f, 0.427f, 0.647f));
	mViewport->setClearEveryFrame(true);
	renderSystem->setViewport(0, 0, rc.right - rc.left, rc.bottom - rc.top);

	// �������
	mCamera = mRenderEngine->createCamera(mViewport);
	Assert(mCamera != NULL);
	if (!mCamera)
	{
		Error("[3D]Create mCamera failed"<<endl);
		return false;
	}
	mCamera->setPosition(0,10,0);
	mCamera->lookAt(0,0,0);
	mCamera->setFillMode(FM_SOLID);
	mCamera->setNearDistance(1);
	mCamera->setFarDistance(1000);
	mCamera->update();

	// ��ȼ��
	renderSystem->setDepthBufferCheckEnabled(true);
	renderSystem->setDepthBufferWriteEnabled(true);
	renderSystem->setVerticalSync(true);

	// ����
	mLight = new Light;
	mLight->setSpecularColor(ColorValue(1,1,1,1));
	mLight->setType(LT_DIRECTIONAL);
	mLight->setDirection(1,1,1);
	renderSystem->setLight(0,mLight);
	renderSystem->setLightingEnabled(true);
	renderSystem->setSurfaceParams(ColorValue(0.8,0.8,0.8),ColorValue(0.7,0.7,0.7),ColorValue(0.0,0.0,0.0),ColorValue::Black,128);
	renderSystem->setAmbientLight(ColorValue::White);

	ParticleSystem::set25dMode(true);

	return true;
}

bool GlobalClient::initUI()
{
#ifdef USE_UI

//  	char szUiDataDir[][24] = 
//  	{
// // 		"animal",
//  // 		"animationset",
// 		"font",
// 		"image",
// 		"imageset",
// 		"layout",
// 		"lua",
// 		"setting",
// 		"ui_effect"
//  	};

	tolua_app_open(mLuaEngine->GetLuaState());
	using namespace rktgui;
	PROFILE("initUI");
	IRenderSystem* renderSystem = mRenderEngine->getRenderSystem();
	mGuiRenderer = new TxGuiRenderer(renderSystem);
	new System(mGuiRenderer, mTimerAxis);
	System::getSingleton().setScriptingModule(mLuaEngine);	

// 	std::string strBaseUiDir = "Data\\UI\\";
// 	for(int i = 0 ; i< sizeof(szUiDataDir)/sizeof(szUiDataDir[0]); i++)
// 	{
// 		std::string strPath = strBaseUiDir;
// 		strPath += szUiDataDir[i];
// 		rkt::getFileSystem()->addFindPath(strPath.c_str());
// 	}

	//fire display size changed event.
	rktgui::EventArgs ea;
	rktgui::System::getSingletonPtr()->getRenderer()->fireEvent(rktgui::Renderer::EventDisplaySizeChanged,ea);


		System::getSingleton().executeScriptFile("init.lua");	
	
		Tooltip* tip = (Tooltip*) WindowManager::getSingleton().createWindow("UNLLook/HtmlTooltip","rocket-tooltip");
		System::getSingleton().setDefaultTooltip(tip);
		tip->setPosition(UVector2(UDim(0.0f,20.0f), UDim(0.0f,20.0f)));
		tip->setSize(UVector2(UDim(0.0f,20.0f), UDim(0.0f,20.0f)));
		tip->setFadeTime(0.0f);
		tip->setHoverTime(0.0f);
		tip->setAlwaysOnTop(true);
		tip->setTooltipText("<html><body></body></html>");
	
#endif
	return true;
}



bool  GlobalClient::ResetCompentsForSelectServer(void)
{
	void* hWnd = mhWnd;
	close();
	return create(hWnd);
}


//��λ��Ϸ�߼���ص��������ITaskClient , IFriendClient�ȵȵȵȣ���������ѡ���ɫ
bool GlobalClient::ResetCompentsForSelectActor(void)
{
// 	Trace("unregisterTrace"<<endl);
// 	unregisterTrace(mytrace);

	//////////////////////////////////////////////////////////////////////////

	Trace("�رս��ȹ�����"<<endl);
	//MyRelease(mProgressManager);

	Trace("�ر�����"<<endl);
	// �ͷŸ���ģ��
	if (mRenderEngine)
	{
		for (int i=0; i<maxFontCount; i++)
			mRenderEngine->getFontManager()->releaseFont(mFonts[i]);
	}
//	Trace("ֹͣ��Դ����"<<endl);
	//mResourceManager->stop();

	// ����ģ���ͷ�
	/*
	Trace("�رս���"<<endl);
	safeRelease(mTradeClient);
	Trace("�رշ�װ������Ʒ"<<endl);
	MyRelease(mGoodsFunctionClient);
	Trace("�ر�Ч��"<<endl);
	MyRelease(mEffectClient);
	Trace("�ر�Buff"<<endl);
	MyRelease(mBuffClient);
	Trace("�ر�����"<<endl);
	safeRelease(mChatClient);
	Trace("�ر����"<<endl);
	MyRelease(mTeamClient);
	Trace("�رպ���"<<endl);
	safeRelease(mFriendClient);
	Trace("�ر�EntityClient"<<endl);
		MyRelease(mEntityClient); //mEntityClient��ʹ��formManager

 	Trace("�ر�Controller"<<endl);
 	safeRelease(mFormManager); //formManager��ʹ��gameform��gameformʹ����skep�������ͷ�formManager

	Trace("�ر�mSkepClient"<<endl);
	MyRelease(mSkepClient);

	Trace("�ر�PK"<<endl);
	MyRelease(mPKModeClient);
*/
	Trace("�رճ���"<<endl);
	safeRelease(mSceneManager);
	Trace("�ر�ʵ�幤��"<<endl);
	safeRelease(mEntityFactory);
	Trace("�ر���Դ����"<<endl);
	safeRelease(mResourceManager);
	//Trace("�رռ���"<<endl);
	//safeRelease(mSkillManager);
	Trace("�ر�����"<<endl);
	MyRelease(mAudioEngine); //not safeDelete !!!
	//Trace("�ر����������"<<endl);
	//safeDelete(m_pTaskClient);        

	//safeDelete(frmGame);

	/*
 	Trace("�ر�Controller"<<endl);
 		safeRelease(mFormManager); //formManager��ʹ��gameform��gameformʹ����skep�������ͷ�formManager

#ifdef USE_UI
	Trace("�ر�UI"<<endl);
	delete rktgui::System::getSingletonPtr();
	safeDelete(mGuiRenderer);
#endif
	*/

	Trace("�ر���Ⱦ����"<<endl);
	safeDelete(mLight);
	safeRelease(mCamera);
	safeRelease(mViewport);
	safeRelease(mRenderEngine);
// 
// 	Trace("�ر�������Ϣ������"<<endl);
// 	delete InputMessageManager::getInstancePtr();

// 	Trace("�ر����ù�����"<<endl);
// 	if(mConfigManager)
// 	{
// 		static_cast<Config*>(mConfigManager)->save();
// 		delete static_cast<Config*>(mConfigManager);
// 		mConfigManager = 0;
// 	}
// 
// 	if (NULL != mServerListConfig)
// 	{
// 		mServerListConfig->release();
// 		mServerListConfig = NULL;
// 	}
// 	// ȫ���Ե�ģ��
// 	Trace("�ر�����"<<endl);
// 	MyRelease(mNetConnection);

	Trace("�ر���������"<<endl);
 	MyRelease(mSchemeEngine);

	Trace("�ر�Lua����"<<endl);
	MyRelease(mLuaEngine);

	Trace("�ر��¼�����"<<endl);
	MyRelease(mEventEngine);

	Trace("�ر��¼���"<<endl);
	safeDelete(mTimerAxis); // TODO �ͷ�̫������ע��
	
	Trace("�ر�Trace"<<endl);
	closeTrace();

////////////////////////////////////////////

 /*
	new InputMessageManager();

	CREATE_BEGIN(" CreateProgressManager.........");
	if( (mProgressManager = CreateProgressManager()) == NULL )
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();

	//mProgressManager->StartInitGameProgress( 30);//����30�����ȱ任
*/
	// ��ʼ����Ⱦ����
	CREATE_BEGIN(" init3D.........................");
	if (!init3D(mhWnd))
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();

	// ����
	CREATE_BEGIN("CreateDefaultFont..............");
	IFontManager* fontManager = mRenderEngine->getFontManager();
    /*
	mFonts[fontDefault] = fontManager->createFont(mRenderEngine->getRenderSystem(), 
		mRenderEngine->getRenderSystem()->getTextureManager(), "Default", "Data\\Fonts\\msyh.ttf", 18);

	mFonts[fontEffect] =  fontManager->createFont(mRenderEngine->getRenderSystem(), 
		mRenderEngine->getRenderSystem()->getTextureManager(), "Effect", "Data\\Fonts\\msyh2.ttf", 48);

	if (!mFonts[fontDefault])
	{
		CREATE_ERROR();
		//return false;
	}
	CREATE_SUCCESS();
    */

	// ��Դ������
	CREATE_BEGIN("CreateResourceManager..........");
	if ((mResourceManager = CreateResourceManagerProc(1)) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();

	// ��������
	CREATE_BEGIN("CreateSchemeEngine.............");
	if ((mSchemeEngine = CreateSchemeEngineProc()) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();

// 	Config *pConfigManager = new Config;
// 	pConfigManager->load("config.xml");
// 	mConfigManager = pConfigManager;
// 
// 	ServerListConfig * pServerListConfig = new ServerListConfig;
// 	pServerListConfig ->load("ServerList.xml");
// 	mServerListConfig = pServerListConfig;

    /*
	// �¼�����
	CREATE_BEGIN("CreateEventEngine..............");
	if ((mEventEngine = CreateEventEngineProc()) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();
     */


	// ʱ����
	CREATE_BEGIN("CreateTimerAxis................");
	mTimerAxis = new TimerAxis();
	if (!mTimerAxis)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();


    /*
	// Lua����
	CREATE_BEGIN("CreateLuaEngine................");
	if ((mLuaEngine = CreateLuaEngineProc(true)) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();


	// ʵ�幤��
	CREATE_BEGIN("CreateEntityFactory............");
	if ((mEntityFactory = CreateEntityFactoryProc()) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();
*/
    
    

/*
	// ʵ�����
	CREATE_BEGIN("CreateEntityClient.............");
	if ((mEntityClient = CreateEntityClientProc()) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();


	// Ч������
	CREATE_BEGIN("CreateEffectClient.............");
	if ((mEffectClient = CreateEffectClientProc()) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();


	// ��ȴϵͳ
	CREATE_BEGIN("CreateFreezeClient.............");
	if ((mFreezeClient = CreateFreezeClientProc()) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();



	// Buff����
	CREATE_BEGIN("CreateBuffClient...............");
	if ((mBuffClient = CreateBuffClientProc()) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();


	// ����ϵͳ
	CREATE_BEGIN("CreateChatClient...............");
	if ((mChatClient = CreateChatClientProc()) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();


	// ͨ����Ʒ��
	CREATE_BEGIN("CreateSkepClient...............");
	if ((mSkepClient = CreateSkepClientProc()) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();
*/

	// ����������
	CREATE_BEGIN("CreateSceneManager.............");
	if ((mSceneManager = CreateSceneManagerProc(mResourceManager)) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();

	//����������
	CREATE_BEGIN("CreateAudioEngine..............");
	if ((mAudioEngine = CreateAudioEngineProc(32,32)) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();
/*
	// ���ܹ�����
	CREATE_BEGIN("CreateSkillManager.............");
	if ((mSkillManager = CreateSkillManagerProc()) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();

	// PK������
	CREATE_BEGIN("CreatePKModeClient.............");
	if ((mPKModeClient = CreatePKModeClientProc()) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();

	// ��ӿͻ���
	CREATE_BEGIN("CreateTeamClient...............");
	if ((mTeamClient = CreateTeamClientProc()) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();

	// ���ѿͻ���
	CREATE_BEGIN("CreateFriendClient.............");
	if ((mFriendClient = CreateFriendClientProc()) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();

	// ��װ������Ʒ������
	CREATE_BEGIN("CreateGoodsFunctionClient......");
	if ((mGoodsFunctionClient = CreateGoodsFunctionClientProc()) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();
*/
// 	// ����
// 	CREATE_BEGIN("CreateTCPConnection............");
// 	InitializeNetwork();
// 	if ((mNetConnection = CreateTCPConnectionProc(0, 0, DEFAULT_PACK)) == NULL)
// 	{
// 		CREATE_ERROR();
// 		return false;
// 	}
// 	CREATE_SUCCESS();

	/*
	// ������
	CREATE_BEGIN("CreateFormManager .............");
	if ((mFormManager = CreateFormManagerProc()) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();

	// ����ϵͳ
	CREATE_BEGIN("CreateTradeClient..............");
	if ((mTradeClient = CreateTradeClientProc()) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();

	//  �����������
	CREATE_BEGIN("CreateTaskClient...............");
	if ((m_pTaskClient = CreateTaskClientProc()) == NULL)
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();

	// ��ʼ��UI
	CREATE_BEGIN("initUI.........................");
	if (!initUI())
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();

#ifdef USE_UI
	rktgui::EventArgs ea;
	rktgui::System::getSingletonPtr()->getRenderer()->fireEvent(rktgui::Renderer::EventDisplaySizeChanged,ea);
#endif
	*/

	int left,top,width,height;
	mRenderEngine->getRenderSystem()->getViewport(left,top,width,height);

/*
	//��ʼ����������
	CREATE_BEGIN("mProgressManager->InitScheme().........................");
	if ( !mProgressManager->InitScheme())
	{
		CREATE_ERROR();
		return false;
	}
	CREATE_SUCCESS();


	//��������
	//mProgressManager->StopInitGameProgress();
*/
	//	ת���½���棻
	//mFormManager->toLogin();

	return true;
}


//�˳���¼
void GlobalClient::Logout(void)
{
	//ʵ�ַ�ʽ�ǣ�ֱ�ӶϿ�����
	//MyRelease(mNetConnection);

	//mNetConnection = CreateTCPConnectionProc(0, 0, DEFAULT_PACK);
}
