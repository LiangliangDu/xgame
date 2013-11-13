#include "stdafx.h"
#include "SceneManager.h"
#include "IGlobalClient.h"
#include "IEntityClient.h"
#include "IProgressManager.h"
#include "IConfigManager.h"
#include "IChatClient.h"
#include "ITeamClient.h"
#include "DEntityProp.h"


extern RunType g_runtype;
SceneManager::SceneManager(xs::IResourceManager *pResourceManager)
{
	m_dwDrawFlag = eDrawGround | eDraw2D | eDraw3D | eDrawEntityInfo;

    m_ptSave.x = 0;
	m_ptSave.y = 0;
	m_VisibleListGround.clear();
	m_VisibleListObj.clear();

	//by yhc ����λ�������������,���Ҳ�������������,���ǲ��Ҹ���,��Ϊ�����Ժ�Ҫ����ȫ���ذ�
	// note by zjp�������ͼ�����趨�󣬻Ὣ������µķ�������ƽ��ͶӰΪ���εĵ�����Ѱ·ʹ�õ�tile�������ͶӰ���γɵ�����tile��
	Matrix4 mtxView;
	mtxView.PrecisionRotationX(-30);
	Matrix4 mtxView1;
	mtxView1.PrecisionRotationY(45);
	mtxView = mtxView * mtxView1;
	m_mtxView = mtxView;

	m_pOccupantImageRect = 0;

	m_lightDirection = Vector3(-1.0f,2.5f,0.0f);
	m_numModels = 0;

	m_bOldVersion = false;
	m_pResourceManager = pResourceManager;

	m_pShadowProgram = 0;
	IRenderSystem * pRenderSystem = getRenderEngine()->getRenderSystem();
	if( pRenderSystem->getRenderSystemType() == RS_D3D9 )
	{
		m_pShadowProgram = pRenderSystem->getShaderProgramManager()->createShaderProgram(SPT_HIGHLEVEL);
		m_pShadowProgram->addShaderFromFile(ST_VERTEX_PROGRAM, "data\\Shader\\D3D9\\plainShadow.hlsl" );
		m_pShadowProgram->link();
	}
	m_nVibrateRange = 20;
	//�������Ƿ����
	m_bVibrateFinish = true;
	m_nVibrateTime = 0;
}

SceneManager::~SceneManager()
{
	if( m_pShadowProgram)
	{
		m_pShadowProgram->release();
		m_pShadowProgram = 0;
	}
}

void SceneManager::close()
{
	//added by xxh 2010.04.06
	//���¼��ص�ͼ���߹رճ���ʱ�ͷŵ�������ʵ����ͼ
	EntityView * pHeroView = NULL;
	if( gGlobalClient->getEntityClient() 
		&&  gGlobalClient->getEntityClient()->GetHero() )
	{
		pHeroView = gGlobalClient->getEntityClient()->GetHero()->GetEntityView();
	}

	// ��ɾ��EntityView�б� [5/13/2011 zgz]
	DisplayList listRelease;
	for( DisplayList::iterator it = m_DisplayList.begin(); it != m_DisplayList.end(); ++it)
	{
		if( !(*it) || (*it) == pHeroView ) continue;
		(*it)->removeFlag(flagFade|flagInScreen);

		//ʬ�岻Ҫ�ͷ�,�Ѿ��ж�ʱ���ͷ�
		if(((*it)->getFlag() & flagDie) == flagDie)
		   continue;

		listRelease.push_back(*it);
	}
	for( DisplayList::iterator it = m_FadeOutList.begin(); it != m_FadeOutList.end(); ++it)
	{
		if( !(*it) || (*it) == pHeroView ) continue;
		(*it)->removeFlag(flagFade|flagInScreen);
		//ʬ�岻Ҫ�ͷ�,�Ѿ��ж�ʱ���ͷ�
		if(((*it)->getFlag() & flagDie) == flagDie)
			continue;

		listRelease.push_back(*it);
	}

	// �����ɾ����EntityView [5/13/2011 zgz]
	for( DisplayList::iterator it = listRelease.begin(); it != listRelease.end(); ++it)
	{
		removeEntity((*it)->getTile(), (*it));	
		// �����ͷ� [5/5/2011 zgz]
		(*it)->addFlag(flagReleaseImmediate);
		(*it)->release();	
	}

	m_DisplayList.clear();
	m_FadeOutList.clear();
    SetDistanceTexture("");


	m_bOldVersion = false;
	if(m_pOccupantImageRect)
	{
		m_pOccupantImageRect->finalize();
		delete m_pOccupantImageRect;
		m_pOccupantImageRect = 0;
	}
	m_WayPointManager.close();
	m_MinimapEyeshot.close();
	m_SceneEyeshot.close();
	m_GroundEyeshot.close();
	m_Map.close();
	uchar *pStream = m_mapStream.detach();
	safeDeleteArray(pStream);
	m_VisibleListMultiOcc.clear();
	m_VisibleListObj.clear();
	m_VisibleListGround.clear();


	//ɾ��Ԥ����ģ���ļ�
	/*IEntityClient * pIEntityClient = ((IGlobalClient*)::xs::getGlobal())->getEntityClient();
	if(pIEntityClient)
	{
		DWORD dwMapID = pIEntityClient->GetMapID();
		pIEntityClient->ReleaseMapMonster(dwMapID);
	}*/

	m_ListSkillTile.clear();
}

bool SceneManager::scrollViewport(int dx, int dy)
{
	if (dx == 0 && dy == 0) 
		return false;
	m_GroundEyeshot.scrollViewport(dx, dy);
	m_MinimapEyeshot.scrollViewport(dx, dy);
	// Ϊ��ֹ�༭��������
	if (g_runtype == RUN_TYPE_GAME)
	{
		IEntityClient* pEntityClient = gGlobalClient->getEntityClient();
		if(pEntityClient)
		{
			IPerson* pHero = pEntityClient->GetHero();
			if (!pHero)
			{
				return false;
			}
			xs::Point ptWorld;
			xs::Point ptTitle = pHero->GetMapLoc();
			tile2World(ptTitle,ptWorld);	
			m_MinimapEyeshot.moveViewportTo(ptWorld.x,ptWorld.y,dx,dy);
		}
	}
	const xs::Rect& rc = getViewportRect();
	m_ptSave.x = (rc.left + rc.right) / 2;
	m_ptSave.y = (rc.top + rc.bottom) / 2;

	return m_SceneEyeshot.scroll2Center(m_ptSave);
}

int SceneManager::OnDrawOccupant(const xs::Point& ptTile, Tile* pTile, void* pParam)
{
	xs::Point ptCenter;
	m_GroundEyeshot.tile2Pixel(ptTile,ptCenter);

    xs::Rect rc;
	if (pTile->isBlock())
	{
		rc.left = 0;
		rc.top = 32 * 2;
		rc.right = rc.left + 64 - 1;
		rc.bottom = rc.top + 32 - 1;
		m_pOccupantImageRect->render(ptCenter.x-32, ptCenter.y-16 ,0,&rc);
	}
	if (pTile->isFlyBlock())
	{
		rc.left = 0;
		rc.top = 32 * 0;
		rc.right = rc.left + 64 - 1;
		rc.bottom = rc.top + 32 - 1;
		m_pOccupantImageRect->render(ptCenter.x-32, ptCenter.y-16 ,0,&rc);
	}
	if (pTile->isSpreadBlock())
	{
		rc.left = 0;
		rc.top = 32 * 1;
		rc.right = rc.left + 64 - 1;
		rc.bottom = rc.top + 32 - 1;
		m_pOccupantImageRect->render(ptCenter.x-32, ptCenter.y-16 ,0,&rc);
	}

	return -1;
}

int SceneManager::OnDrawSortPoint(const xs::Point& ptTile, EntityView *pEntity)
{
	const xs::Point& pt1 = pEntity->getSortLeft();
	const xs::Point& pt2 = pEntity->getSortRight();
	xs::Point ptLeft,ptRight;
	world2Tile(pt1,ptLeft);
	world2Tile(pt2,ptRight);
	xs::Point ptCenter;
	m_GroundEyeshot.tile2Pixel(ptLeft,ptCenter);
	xs::Rect rc;
	rc.left = 0;
	rc.top = 32 * 3;
	rc.right = rc.left + 64 - 1;
	rc.bottom = rc.top + 32 - 1;
	m_pOccupantImageRect->render(ptCenter.x-32, ptCenter.y-16 ,0,&rc);
	m_GroundEyeshot.tile2Pixel(ptRight,ptCenter);
	rc.left = 0;
	rc.top = 32 * 4;
	rc.right = rc.left + 64 - 1;
	rc.bottom = rc.top + 32 - 1;
	m_pOccupantImageRect->render(ptCenter.x-32, ptCenter.y-16 ,0,&rc);

	return -1;
}

int SceneManager::OnDrawAnchor(const xs::Point& ptTile, EntityView *pEntity)
{
	xs::Point ptCenter;
	m_GroundEyeshot.tile2Pixel(ptTile,ptCenter);
	xs::Rect rc;
	rc.left = 0;
	rc.top = 32 * 5;
	rc.right = rc.left + 64 - 1;
	rc.bottom = rc.top + 32 - 1;
	m_pOccupantImageRect->render(ptCenter.x-32, ptCenter.y-16 ,0,&rc);

	return -1;
}

void SceneManager::onViewportSizeChanged(int nViewWidth, int nViewHeight)
{
	if (!m_GroundEyeshot.viewportSizeChanged(nViewWidth, nViewHeight))
		return;
	const xs::Rect& rc = getViewportRect();
	xs::Point ptPlayerPos;
	ptPlayerPos.x = (rc.left + rc.right) >> 1;
	ptPlayerPos.y = (rc.top + rc.bottom) >> 1;
	m_SceneEyeshot.viewportSizeChanged(nViewWidth, nViewHeight);
	m_SceneEyeshot.scroll2Center(ptPlayerPos);
}

void SceneManager::createSceneCo(int nMapWidth,int nMapHeight)
{
	int w = nMapWidth;
	int h = nMapHeight;
	w &= ~63;
	h &= ~31;

	m_SceneCo.create(w, h);
}

// ����lprcViewport��ʾ����
bool SceneManager::createGroundEyeshot(xs::Stream* pMapFile,xs::Rect* lprcViewport,IEntityFactory* pEntityFactory,bool bDynamic)
{
	// ��������ģ��
	m_GroundEyeshot.setRunType(g_runtype);

	if (!m_GroundEyeshot.create(&m_Map,m_Map.getSceneWidth(), m_Map.getSceneHeight(),
		256,256,
		lprcViewport,m_pResourceManager,pMapFile,m_strMapFilename,bDynamic))
		return false;

	/*if(pMapFile)
	{
		m_GroundEyeshot.load(pMapFile);
	}*/

	return true;
}

bool SceneManager::createScene(int nMapWidth,int nMapHeight,xs::Rect* lprcViewport)
{
	close();

	int w = nMapWidth, h = nMapHeight;

	createSceneCo(w,h);

	xs::Rect rcTilesPreRead (0, 0, w, h);
	if (!m_Map.create(&m_GroundEyeshot,w, h, rcTilesPreRead,this))
		return false;

	if (!createGroundEyeshot(0,lprcViewport,0,false))
		return false;

	xs::Rect rc(0, 0, w, h);
	xs::Point ptPlayerPos (0, 0);
	if (!m_SceneEyeshot.create(w, h, ptPlayerPos, this,false))
		return false;
	if(!m_MinimapEyeshot.create(this,w, h, 1024, 1024,ptPlayerPos,0))
		return false;

	return true;
}

// �����lprcViewport��ʾ�ӿڣ�
bool SceneManager::loadScene(
							   const char* szFilename,
							   const char* szWayPointFilename,
							   xs::Rect* lprcViewport,
							   IEntityFactory* pEntityFactory,bool bDynamic,const xs::Point* pTileCenter,bool oldVersion)
{
	CSceneLock sceneLock;
	//�ܽ���Ϊ12
	IProgressManager * pProMgr = gGlobalClient->getProgressManager();
	//�ر���ǰ�����Ľ���Ϊ1
	if( pProMgr)
		pProMgr->AdvanceLoadingScenceProgressLength(1);

	close();

	m_strMapFilename = szFilename;
	m_bOldVersion = oldVersion;

	xs::CStreamHelper	pMapStream = xs::getFileSystem()->open(szFilename);
	if(!pMapStream)return false;
	

	uint length = pMapStream->getLength();
	uchar* pBuffer = new uchar[length];
	pMapStream->read(pBuffer,length);

	m_mapStream.attach(pBuffer,length);

	//��ͼ���صĽ��Ƚ���Ϊ6
	xs::Rect rcViewport = *lprcViewport;
	if(!m_Map.load(&m_GroundEyeshot,&m_mapStream,pEntityFactory,&rcViewport,pTileCenter,bDynamic,this))
	{
		ErrorLn("m_Map.load Failed!");
		return false;
	}

	//��ʼ��Ѱ·��Ϣ�Ľ���Ϊ1
	if( pProMgr)
		pProMgr->AdvanceLoadingScenceProgressLength(1);
    //  ��ʼ��Ѱ·��ͼ��Ϣ
	m_PathFindAStar.SetMapInfo(getSceneMgr());


	//Ԥ����ģ�͵ĵĽ���Ϊ3
	if( pProMgr)
		pProMgr->AdvanceLoadingScenceProgressLength(3);
	//Ԥ����ģ���ļ�
	IEntityClient * pIEntityClient = ((IGlobalClient*)::xs::getGlobal())->getEntityClient();
	if(pIEntityClient)
	{
		DWORD dwMapID = pIEntityClient->GetMapID();
		pIEntityClient->LoadMapMonster(dwMapID);
	}

	int w = getSceneWidth();
	int h = getSceneHeight();
	w &= ~63;
	h &= ~31;

	// ·��Ѱ·���ܱ�����������ظ�������Ϣ
	//char *wp = "maps\\xhw01_wp.xml";
	//if(!m_WayPointManager.loadConfig(szWayPointFilename,m_Map.getMapBlockBuffer(),this))
	//{
	//	return false;
	//}

    //  ��������ŵ�m_Map.load()��ȥ�����Ա�֤��m_Map.load()�Ĺ�����Ҳ����ʹ������ϵͳ��
	//if (!createGroundEyeshot(&m_mapStream,&rcViewport, pEntityFactory,bDynamic))
	//{
	//	return false;
	//}

	xs::Point ptPlayerPos;
	ptPlayerPos.x = (rcViewport.left + rcViewport.right) / 2;
	ptPlayerPos.y = (rcViewport.top + rcViewport.bottom) / 2;

	//����С��ͼ�͹��쳡���۲����Ľ����ܹ�Ϊ1
	if( pProMgr)
		pProMgr->AdvanceLoadingScenceProgressLength(1);

	CPath path ;
    path = szFilename;
	std::string title = path.getFileTitle();
	if(!m_MinimapEyeshot.create(this,w,h,1024,1024,ptPlayerPos,m_pResourceManager,title))
		return false;

	if(bDynamic)
	{
		xs::Rect rcPreRead;
		m_Map.viewRectToPreReadRect(rcViewport, rcPreRead, w, h);
		if(!m_SceneEyeshot.create(w, h, ptPlayerPos, this, bDynamic))
		{
			return false;
		}
	}
	else
	{
		xs::Rect rc ( 0, 0, w, h );
		if(!m_SceneEyeshot.create(w, h, ptPlayerPos, this, bDynamic))
		{
			return false;
		}
	}

	return true;
}
void SceneManager::vibrate( int nVibrateRange/*�񶯵�������,����Ϊ��λ,��ΧΪ10-40֮��*/)
{

	m_nVibrateRange = nVibrateRange;
	//�������Ƿ����
	m_bVibrateFinish = false;;
	m_nVibrateTime = 0;
	
}
bool SceneManager::scroll2Center(xs::Point ptScreenCenter)
{
	int dx = ptScreenCenter.x - m_GroundEyeshot.getViewWidth() / 2;
	int dy = ptScreenCenter.y - m_GroundEyeshot.getViewHeight() / 2;	

	if (dx == 0 && dy == 0)
		return false;

	//Info("ScrollTo:"<<dx<<","<<dy<<endl);
	return scrollViewport(dx, dy);


#define VERT_CONST	2
	int ddx, ddy;
	ddx = ddy = 0;
	int halfW = m_GroundEyeshot.getViewWidth() / 2;
	int halfH = m_GroundEyeshot.getViewHeight() / 2;
	if (dx < 0)
	{
		if (dx < -halfW)
			ddx = dx;
		else
		{
			ddx = (-dx) >> (VERT_CONST+1);
			ddx = -ddx;
			if (ddx == 0)
				ddx = -1;
		}

	}
	else if (dx > 0)
	{
		if (dx > halfW)
			ddx = dx;
		else
		{
			ddx = dx >> (VERT_CONST+1);
			if (ddx == 0)
				ddx = 1;
		}
	}

	if (dy < 0)
	{
		if (dy < -halfH)
			ddy = dy;
		else
		{
			ddy = (-dy) >> VERT_CONST;
			ddy = -ddy;
			if (ddy == 0)
				ddy = -1;
		}
	}
	else if (dy > 0)
	{
		if (dy > halfH)
			ddy = dy;
		else
		{
			ddy = dy >> VERT_CONST;
			if (ddy == 0)
				ddy = 1;
		}
	}
	
	//Info("Scroll:"<<ddx<<","<<ddy<<endl);
	return scrollViewport(ddx, ddy);
}
bool SceneManager::scroll2CenterByTime(xs::Point ptScreenCenter,ulong delta)
{

	int dx = ptScreenCenter.x - m_GroundEyeshot.getViewWidth() / 2;
	int dy = ptScreenCenter.y - m_GroundEyeshot.getViewHeight() / 2;

	//��
	if(m_bVibrateFinish==false)
	{
		//�����˶���ʽ��x(t) = A * exp(-1 * �� * t) * cos(sprt(��^2 - ��^2 * t) + ��) , �����������ӣ����ǹ��н�Ƶ�ʡ�
		//��Ϊ�����ᣬ ��ΪǷ���ᣬ ���Ϊ�ٽ�����
		m_nVibrateTime+=delta;
		float fRange = m_nVibrateRange*Math::Exp(-1*0.004*m_nVibrateTime);

		//���С��1ʱ�����
		if(fRange<1)
		{
			m_bVibrateFinish = true;
			m_nVibrateTime = 0;
			m_nVibrateRange = 0;
			//vibrate();//���Դ���,����һ����
		}
		else
		{
			dy-=fRange*Math::Cos( Math::Sqrt(m_nVibrateTime),true );
		}
	}

	if (dx == 0 && dy == 0)
		return false;

	//Info("ScrollTo:"<<dx<<","<<dy<<endl);
	return scrollViewport(dx, dy);


	/*
	int dx = ptScreenCenter.x - m_GroundEyeshot.getViewWidth() / 2;
	int dy = ptScreenCenter.y - m_GroundEyeshot.getViewHeight() / 2;
	static int s_xSpeed = 0;
	static int s_ySpeed = 0;
	if (dx == 0 && dy == 0)
	{
		s_xSpeed = 0;
		s_ySpeed = 0;
		return false;
	}

	//Info("ScrollTo:"<<dx<<","<<dy<<endl);
	//return scrollViewport(dx, dy);

	//Ϊ�˷�ֹ��������,ʹ�������ƽ��,������һ���ٶȽ���Ĺ���,��ʼ��һ�����ٹ���(����Ŀ���ԽԶ���ٶ�Խ��),������һ�����ٹ���.
	//�е����Ƶ����˳�����׷���㷨,ֻ�������ﲻʹ�ø�����,ֻʹ������,û����ô��ȷ
	
	
	//ȷ�������ٶ�,�ٶ��Ǳƽ�Ŀ������һ������ֵ
	//���ٶ�
	if(dx>1||dx<-1)
	{
		if(s_xSpeed<dx)
			s_xSpeed+=2;
		else
			s_xSpeed-=2;
	}
	
	if(dy>1||dy<-1)
	{
		if(s_ySpeed<dy)
			s_ySpeed++;
		else
			s_ySpeed--;
	}

	int ddx = 0;
	int ddy = 0;
	//�ٸ����ٶ�*ʱ��ȥ��
	if(delta>5)
	{
		if(dx>=1)
		{
			ddx = s_xSpeed*(int)delta/100;

			if(ddx<1)
				ddx = 1;
			if(ddx>dx)
				ddx =dx;
		}
		if(dx<=-1)
		{
			ddx = s_xSpeed*(int)delta/100;
			if(ddx>-1)
				ddx = -1;
			if(ddx<dx)
				ddx =dx;
		}
		if(dy>=1)
		{
			ddy = s_ySpeed*(int)delta/100;
			if(ddy<1)
				ddy = 1;
			if(ddy>dy)
				ddy =dy;
			//if(dy>5)
			//	dy = 5;
		}
		if(dy<=-1)
		{
			ddy = s_ySpeed*(int)delta/100;
			if(ddy>-1)
				ddy = -1;
			if(ddy<dy)
				ddy =dy;
			//if(dy<-5)
			//	dy = -5;
		}
	}

	//Info("Scroll:"<<ddx<<","<<ddy<<endl);
	return scrollViewport(ddx, ddy);*/
}
bool SceneManager::save(const char* szFilename,bool writeOccupants)
{
	xs::DataChunk chunk;
	if(m_Map.save(&chunk,writeOccupants))
	{
		chunk.save(szFilename);
		return true;
	}
	
	return false;
}

bool SceneManager::addEntity(const xs::Point& ptTile, EntityView* pEntity, DWORD dwParam)
{
	if (!pEntity)
		return false;

	if (pEntity->hasFlag(flagGlobalSceneMagic))
	{	
		return addGlobalSceneMagic(pEntity);
	}

	pEntity->setTile(ptTile);

	if (!pEntity->hasFlag(flagNoLogic) && dwParam == 0)
	{
		pEntity->setTile(ptTile);
		m_SceneEyeshot.AddItemToList(pEntity, ptTile);
	}

	bool bAddMap = false;
	if(m_Map.addEntity(ptTile, pEntity))
	{
		pEntity->onAddEntity();
		_Info("addEntity: ok"<<_fi("0x%08x", (ulong)pEntity)<<endl);
		bAddMap = true;
	}
	else
	{
		_Info("addEntity: fail"<<_fi("0x%08x", (ulong)pEntity)<<endl);
		//debugBreak
	}

	//modify by yhc
	//����жϻᵼ��NPC����ﲻ����ʾ,��Ϊ�˶��е��ӿڷ�Χ�����ŷ���仯,�п��ܲ����ӿڷ�Χ��,����һ��Ҫ����ʾ�б�������Ӳ�����ʾ
	//
	if (isItemInViewArea(ptTile, pEntity))
	{
		OnEntityEnterViewport(ptTile, pEntity);
	}
	else
	{
		breakable;
	}

	// ����MagicView�Ⱦ���NoLogic��־��ʵ�壬���û����ɹ���Ӧ����false֪ͨ�ϲ㣬���������ڴ�й¶
	if (getRunType() == RUN_TYPE_GAME && pEntity->hasFlag(flagNoLogic))
	{		
		if (!this->IsReferencedBySceneManager(pEntity) && !bAddMap)
		{
			return false;
		}
	}
	return true;
}

bool SceneManager::removeEntity(const xs::Point&, EntityView* pEntity, DWORD dwParam)
{
	if (!pEntity)
		return false;

	if (pEntity->hasFlag(flagGlobalSceneMagic))
	{
		return removeGlobalSceneMagic(pEntity);
	}

	xs::Point ptTile = pEntity->getTile();
	if (!pEntity->hasFlag(flagNoLogic) && dwParam == 0)
	{
		m_SceneEyeshot.RemoveItemFromList(pEntity, ptTile);
	}

	//by yhc 2010.3.29
	//ȷ���ڱ༭��״̬��ɾ����Чָ��
	if(getRunType() == RUN_TYPE_EDITOR)
	{
		RemoveItemFromDisplayList(pEntity);
	}

	// ����Ƴ�ʵ�壻��Ҫ�Ƴ���ʵ����ص��������ݣ�
    if (getRunType() == RUN_TYPE_GAME)
    {
		ulong ulEntityType = pEntity->getEntityType();
		if(ulEntityType == typePerson || ulEntityType == typeMonster)
		{
			IChatClient* pChatClient = gGlobalClient->getChatClient();
			IEntity* pEntiyData = (IEntity*) pEntity->getUserData();
			if (pChatClient && pEntiyData)
				pChatClient->ClosePaoPaoFadeOutScreen(pEntiyData->GetUID());
		}
    }
	if (isItemInViewArea(ptTile, pEntity))
	{
		//if(pEntity->hasFlag(flagFade))
		{
			RemoveItemFromDisplayList(pEntity);
			if(g_runtype == RUN_TYPE_GAME && pEntity->hasFlag(flagFade))
				AddItemToFadeOutList(pEntity);
		}
	}

	if(m_Map.removeEntity(ptTile, pEntity))
	{
		pEntity->onRemoveEntity();
		_Info("removeEntity: ok"<<_fi("0x%08x", (ulong)pEntity)<<endl);
	}
	else
	{
		_Info("removeEntity: failed"<<_fi("0x%08x", (ulong)pEntity)<<endl);
	}

	// ʬ��Remove��ʱ��Ҫȷ��remove�ɾ��� [5/31/2011 zgz]
	if(g_runtype == RUN_TYPE_GAME && pEntity->hasFlag(flagDie))
	{
		RemoveItemFromDisplayList(pEntity);
		RemoveItemFromFadeOutList(pEntity);
	}
		
	return true;
}

bool SceneManager::moveEntity(const xs::Point&, const xs::Point& ptTileTo, EntityView* pEntity, DWORD dwParam)
{
	if (!pEntity)
		return false;

	xs::Point ptTileFrom = pEntity->getTile();
	if(ptTileFrom.x == ptTileTo.x && ptTileTo.y == ptTileFrom.y)
		return true;

	if (!pEntity->hasFlag(flagNoLogic))
	{
		pEntity->setTile(ptTileTo);
		m_SceneEyeshot.MoveItemInList(pEntity, ptTileFrom, ptTileTo);
	}

	m_Map.removeEntity(ptTileFrom,pEntity);
	m_Map.addEntity(ptTileTo,pEntity);

	if(pEntity->hasFlag(flagVisible))
	{
		if (!isItemInViewArea(ptTileTo, pEntity))
		{
			OnEntityLeaveViewport(ptTileFrom, pEntity);
			//if(pEntity->hasFlag(flagFade))
			{
				RemoveItemFromDisplayList(pEntity);
				AddItemToFadeOutList(pEntity);
			}
		}
		else
		{
			breakable;
		}
	}
	else
	{
		if(isItemInViewArea(ptTileTo,pEntity))
		{
			OnEntityEnterViewport(ptTileTo, pEntity);
		}
	}

	pEntity->setTile(ptTileTo);

	return true;
}

bool SceneManager::addEntityOccupant(const xs::Point& ptTile, EntityView* pEntity)
{
	return m_Map.addEntityOccupant(ptTile, pEntity);
}
bool SceneManager::removeEntityOccupant(const xs::Point& ptTile, EntityView* pEntity)
{
	return m_Map.removeEntityOccupant(ptTile, pEntity);
}

void SceneManager::AddItemToFadeOutList(EntityView* pEntity)
{
	if(getRunType() == RUN_TYPE_EDITOR)
		return;

	//����һ����pEntityΪ�Ƿ�����»ᵼ�·Ƿ��ĺ���
	isItemVisible(pEntity->getTile(),pEntity);

	m_FadeOutList.remove(pEntity);
	m_FadeOutList.push_back(pEntity);
}

void SceneManager::RemoveItemFromFadeOutList(EntityView* pEntity)
{
	m_FadeOutList.remove(pEntity);
}

void SceneManager::AddItemToDisplayList(EntityView* pEntity)
{
	//����һ����pEntityΪ�Ƿ�����»ᵼ�·Ƿ��ĺ���
	isItemVisible(pEntity->getTile(),pEntity);
	if(!pEntity->hasFlag(flagVisible))
	{
		pEntity->addFlag(flagVisible);
	/*	m_DisplayList.remove(pEntity);
		m_DisplayList.push_back(pEntity);*/
		if(find(m_DisplayList.begin(),m_DisplayList.end(),pEntity) == m_DisplayList.end())
			m_DisplayList.push_back(pEntity);
	}
	RemoveItemFromFadeOutList(pEntity);
}

void SceneManager::RemoveItemFromDisplayList(EntityView* pEntity)
{
	//�ڱ༭��״̬��һ��ɾ��
	if(getRunType() == RUN_TYPE_EDITOR)
		m_DisplayList.remove(pEntity);

	if(pEntity->hasFlag(flagVisible))
	{
		pEntity->removeFlag(flagVisible);
		m_DisplayList.remove(pEntity);
	}
}

void SceneManager::OnEntityEnterViewport(const xs::Point& ptTile, EntityView* pEntity)
{
	if (!pEntity)
		return;

	int priority = 0;
	if(isItemVisible(ptTile,pEntity))
		priority = -80;
	else
		priority = -60;

	EntityView* pItemView = (EntityView*)pEntity;
	pItemView->onEnterViewport(priority);

	AddItemToDisplayList(pEntity);
}

bool SceneManager::IsReferencedBySceneManager(EntityView * pEntity)
{
	if( !pEntity) return false;
	if( find(m_DisplayList.begin(),m_DisplayList.end(), pEntity) != m_DisplayList.end() )
		return true;
	if( find(m_FadeOutList.begin(), m_FadeOutList.end(), pEntity) != m_FadeOutList.end() )
		return true;
	return false;
}

void SceneManager::LockScene()
{
	m_mutex.Lock();
}

void SceneManager::UnLockScene()
{
	m_mutex.Unlock();
}

void SceneManager::OnEntityLeaveViewport(const xs::Point& ptTile, EntityView* pEntity)
{
	if (!pEntity)
		return;

	EntityView* pItemView = (EntityView*)pEntity;

	pItemView->onLeaveViewport();
	//if(pItemView->hasFlag(flagFade))
	{
		RemoveItemFromDisplayList(pItemView);
		AddItemToFadeOutList(pEntity);
	}
}

// ���������1024*768һ���ӿڵ�����
bool SceneManager::isItemVisible(const xs::Point& ptTile, EntityView* pItemView)
{
	xs::Point ptCenter;
	ptCenter = pItemView->getWorld();
	xs::Rect rcItem = pItemView->getShowRect();

	OffsetRect(&rcItem, ptCenter.x, ptCenter.y);
	return IntersectRect(&rcItem, &rcItem, &m_GroundEyeshot.getViewportRect()) != FALSE;
}

// �����������3*5��1024*512��������
bool SceneManager::isItemInViewArea(const xs::Point& ptTile, EntityView* pItemView)
{
	xs::Point ptCenter;
	ptCenter = pItemView->getWorld();
	xs::Rect rcPreRead;
	m_SceneEyeshot.GetViewCoveredGridRect(rcPreRead);
	return PtInRect(&rcPreRead, ptCenter) != FALSE;
}

bool SceneManager::isItemInLogicArea(const xs::Point& ptTile, EntityView* pItemView)
{
	xs::Point ptCenter;
	ptCenter = pItemView->getWorld();
	xs::Rect rcPreRead;
	m_SceneEyeshot.GetPreReadCoveredGridRect(rcPreRead);
	return PtInRect(&rcPreRead, ptCenter) != FALSE;
}

void SceneManager::drawEntireGround(IRenderSystem *pRenderSystem)
{
	bool bDrawGroundTile = m_GroundEyeshot.isDrawTileLine(); 
	m_GroundEyeshot.setDrawTileLine(false);

	m_GroundEyeshot.onDraw(true);

	m_GroundEyeshot.setDrawTileLine(bDrawGroundTile);
}

void SceneManager::updateDisplayList(DisplayList& list,float tick,float deltaTick,IRenderSystem *pRenderSystem)
{	
	DisplayListPtr end, it;
	end = list.end();
	for (it=list.begin(); it!=end;)
	{
		EntityView *pItemViewPtr = *it;

		const xs::Point& ptTile = pItemViewPtr->getTile();

		//by yhc 2010.3.29
		//ȷ���ڱ༭��״̬��ɾ����Чָ��
		if((ptTile.x<0||ptTile.y<0)&&getRunType() == RUN_TYPE_EDITOR)
		{
			RemoveItemFromDisplayList(pItemViewPtr);
		}

		bool inScreen = false;
		bool itemVisible = false;
		try
		{
			itemVisible = isItemVisible(ptTile, pItemViewPtr);
		}
		catch(...)
		{
			*(int*)0 = 0;
		}
		if (itemVisible)
		{
			inScreen = true;
			pItemViewPtr->addFlag(flagInScreen);
			// �˴�˵��ʵ�崦����Ļ�⣻�����������߹��ȥ�ر���Ӧ���������ݣ�
			ulong ulEntityType = pItemViewPtr->getEntityType();
			if(getRunType() == RUN_TYPE_GAME && (ulEntityType == typePerson || ulEntityType == typeMonster))
			{
				IChatClient* pChatClient = gGlobalClient->getChatClient();
				IEntity* pEntiyData = (IEntity*) pItemViewPtr->getUserData();
				if (pChatClient && pEntiyData)
					pChatClient->ShowPaoPaoFadeInScreen(pEntiyData->GetUID());
		}
		}
		else
		{
			pItemViewPtr->removeFlag(flagInScreen);
			// �˴�˵��ʵ�崦����Ļ�⣻�����������߹��ȥ�ر���Ӧ���������ݣ�
			ulong ulEntityType = pItemViewPtr->getEntityType();
			if(getRunType() == RUN_TYPE_GAME && (ulEntityType == typePerson || ulEntityType == typeMonster))
			{
				IChatClient* pChatClient = gGlobalClient->getChatClient();
				IEntity* pEntiyData = (IEntity*) pItemViewPtr->getUserData();
				if (pChatClient && pEntiyData)
					pChatClient->ClosePaoPaoFadeOutScreen(pEntiyData->GetUID());
		}
		}

		if((pItemViewPtr->getFlag() & flag2D) && !(m_dwDrawFlag & eDraw2D))
		{
			++it;
			continue;
		}
		if(inScreen)
		{
			if(pItemViewPtr->getFlag() & flag3D)
			{
				if(!(m_dwDrawFlag & eDraw3D))
				{
					++it;
					continue;
				}
				m_numModels++;
			}
		}

		//����ܿ��ܻᵼ�µ�������Ч,���Խ�����������
		DisplayListPtr tempit = it;
		tempit++;
		//�����п����޸���list,���µ�������Ч
		//if(player==pItemViewPtr&&getRunType()==RUN_TYPE_GAME)
		//	continue;
		PP_BY_NAME_START("SceneManager::updateDisplayList::pItemViewPtr->update");
		bool ok = pItemViewPtr->update(tick,deltaTick,pRenderSystem);
		PP_BY_NAME_STOP();
		it = tempit;
		if(!ok)
		{
			/*_Info("delete-ev:"<<_fi("0x%08x", (ulong)pItemViewPtr)<<endl);
			_Info("Before Erase Start"<<endl);
			{
				DisplayListPtr it = list.begin();
				while(it != list.end())
				{
					EntityView *pItem = *it;
					_Info("EnumEntities:"<<_fi("0x%08x", (ulong)pItem)<<endl);
					++it;
				}
			}
			_Info("Before Erase End"<<endl);*/
			
			//�п��ܶ�Ӧ��list����
			//��ȫ��������б����涼�Ƴ�,���ǵ��·Ƿ���ԭ��.�п�����update��ʱ�����б�
			m_DisplayList.remove(pItemViewPtr);
			m_FadeOutList.remove(pItemViewPtr);

			//it = list.erase(it);
			/*_Info("After Erase Start"<<endl);
			{
				DisplayListPtr it = list.begin();
				while(it != list.end())
				{
					EntityView *pItem = *it;
					_Info("EnumEntities:"<<_fi("0x%08x", (ulong)pItem)<<endl);
					++it;
				}
			}
			_Info("After Erase End"<<endl);*/
			continue;
		}

		if(inScreen)
		{
			//Error("displayListSize = "<<size<<endl);
			if(pItemViewPtr->getLayer() <= lvlSpecificBlock)
			{
				m_VisibleListGround.push_back(pItemViewPtr);
			}
			else
			{
				PP_BY_NAME_START("SceneManager::updateDisplayList::addSortingEntitiesAll");
				if(pItemViewPtr->getEntityType()==typeStatic || pItemViewPtr->getEntityType()==typeBox)
					m_VisibleListMultiOcc.push_front(pItemViewPtr);
				else
					m_VisibleListMultiOcc.push_back(pItemViewPtr);
				PP_BY_NAME_STOP();
			}
		}
		
	}
}

void SceneManager::update(float tick,float deltaTick,IRenderSystem *pRenderSystem)
{
	if (!m_Map.isValid())
		return;

	//������Ⱦѭ���д���
	if(!m_pOccupantImageRect && pRenderSystem )
	{
		m_pOccupantImageRect = new ImageRect;
		ColorValue c = ColorValue(1,0,1);
		m_pOccupantImageRect->initialize(pRenderSystem,"mask.bmp",false,&c);
	}

	m_numModels = 0;

	m_VisibleListGround.clear();
	m_VisibleListObj.clear();
	m_VisibleListMultiOcc.clear();

	PP_BY_NAME_START("SceneManager::update::updateDisplayList");
	//������Ϣ
	m_flagsD.clear();
	DisplayListPtr begin = m_DisplayList.begin();
	DisplayListPtr end = m_DisplayList.end();
	while(begin != end)
	{
		EntityView *pEntity = (*begin);
		m_flagsD.push_back(pEntity->getFlag());
		++begin;
	}
	updateDisplayList(m_DisplayList,tick,deltaTick,pRenderSystem);
	PP_BY_NAME_STOP();

	PP_BY_NAME_START("SceneManager::update::updateFadeOutList");
    m_flagsF.clear();
	begin = m_FadeOutList.begin();
	end = m_FadeOutList.end();
	while(begin != end)
	{
		EntityView *pEntity = (*begin);
		m_flagsF.push_back(pEntity->getFlag());
		++begin;
	}
	updateDisplayList(m_FadeOutList,tick,deltaTick,pRenderSystem);
	PP_BY_NAME_STOP();

	PP_BY_NAME_START("SceneManager::update::sortVisibleEntities");
	sortVisibleEntities();
	PP_BY_NAME_STOP();

	updateGlobalSceneMagic(tick, deltaTick, pRenderSystem);
	return;
}

void SceneManager::draw(IRenderSystem* pRenderSystem, bool bWholeGround)
{
	if (!m_Map.isValid())
		return;

	DisplayListPtr end, it;

    Matrix4 mtxWorld = pRenderSystem->getWorldMatrix();
    bool depthCheck = pRenderSystem->isDepthBufferCheckEnabled();
    bool depthWrite = pRenderSystem->isDepthBufferWriteEnabled();
    bool lighting = pRenderSystem->isLightingEnabled();
    SceneBlendFactor src,dst;
    pRenderSystem->getSceneBlending(src,dst);

	PP_BY_NAME_START("SceneManager::draw::m_GroundEyeshot.onDraw");
	pRenderSystem->switchTo2D();
    pRenderSystem->setSceneBlending(SBF_SOURCE_ALPHA,SBF_ONE_MINUS_SOURCE_ALPHA);
	if(m_dwDrawFlag & eDrawGround)m_GroundEyeshot.onDraw(bWholeGround);
	pRenderSystem->switchTo3D();
	PP_BY_NAME_STOP();

	PP_BY_NAME_START("SceneManager::draw::m_VisibleListGround.onDraw");
    pRenderSystem->setSceneBlending(SBF_SOURCE_ALPHA,SBF_ONE_MINUS_SOURCE_ALPHA);
    pRenderSystem->setDepthBufferCheckEnabled(false);
    pRenderSystem->setDepthBufferWriteEnabled(false);
    pRenderSystem->setLightingEnabled(false);

	if(!m_VisibleListGround.empty())
	{
		end = m_VisibleListGround.end();
		for (it = m_VisibleListGround.begin(); it!=end; ++it)
		{
			EntityView *pEntity = *it;
			if (pEntity->hasFlag(flagUnRender))
			{
				continue;
			}
			pEntity->draw(pRenderSystem);
		}
	}
	PP_BY_NAME_STOP();

	
	// ������Ӱ
	if(m_numModels && gGlobalClient->getConfigManager() && gGlobalClient->getConfigManager()->getSystemSetShadow())
	{
		PP_BY_NAME_START("SceneManager::draw::drawShadow");

		Matrix4 mtxWorld = pRenderSystem->getWorldMatrix();
		Matrix4 mtxShadow = Matrix4::IDENTITY;
		mtxShadow[0][1] = -m_lightDirection.x / m_lightDirection.y;
		mtxShadow[1][1] = 0;
		mtxShadow[2][1] = -m_lightDirection.z / m_lightDirection.y;

		ColorValue c = pRenderSystem->getColor();
		pRenderSystem->setColor(ColorValue(0.0,0.0,0.0,0.3));
		//
		pRenderSystem->setStencilCheckEnabled(true);
		pRenderSystem->setStencilBufferParams(CMPF_EQUAL,0,0xFFFFFFFF,SOP_KEEP,SOP_KEEP,SOP_INCREMENT);

		pRenderSystem->setWorldMatrix(mtxWorld * mtxShadow);

		if( m_pShadowProgram ) 
		{
			//�������ͱ任����İ����ڻ��ƴ�������
			m_pShadowProgram->bind();
		}

		end = m_VisibleListObj.end();
		for (it=m_VisibleListObj.begin(); it!=end; ++it)
		{
			EntityView* pEntity = *it;
			if(pEntity->getFlag() == 0xfeeefeee)
			{
				int i = 0;
			}
			if (pEntity->hasFlag(flagUnRender) || pEntity->hasFlag(flagUnRenderShadow))
			{
				continue;
			}

			if(pEntity->getFlag() & flag3D)
			{
				pEntity->drawShadow(pRenderSystem);
			}
		}

		if( m_pShadowProgram ) 
		{
			m_pShadowProgram->unbind();
		}

		pRenderSystem->setWorldMatrix(mtxWorld);
		pRenderSystem->setStencilCheckEnabled(false);
		pRenderSystem->setStencilBufferParams();
		pRenderSystem->setColor(c);	

		PP_BY_NAME_STOP();
	}
	
	

	// ����2D��Ʒ 3Dģ��(��������)
	PP_BY_NAME_START("SceneManager::draw::m_VisibleListObj.onDraw");
	end = m_VisibleListObj.end();
	for (it=m_VisibleListObj.begin(); it!=end; ++it)
	{
		EntityView *pEntity = *it;
		if (pEntity->hasFlag(flagUnRender))
		{
			continue;
		}

		if(pEntity->getFlag() & flag2D)
		{
			pRenderSystem->setDepthBufferCheckEnabled(false);
			pRenderSystem->setDepthBufferWriteEnabled(false);
			pRenderSystem->setLightingEnabled(false);
			pRenderSystem->setSceneBlending(SBF_SOURCE_ALPHA,SBF_ONE_MINUS_SOURCE_ALPHA);
		}
		else
		{
			pRenderSystem->setLightingEnabled(true);
			pRenderSystem->setDepthBufferCheckEnabled(true);
			pRenderSystem->setDepthBufferWriteEnabled(true);
			pRenderSystem->setSceneBlending(SBF_ONE,SBF_ZERO);
		}

		pEntity->draw(pRenderSystem);		
	}
	PP_BY_NAME_STOP();
	
	drawGlobalSceneMagic(pRenderSystem);

	pRenderSystem->setSceneBlending(src,dst);
	pRenderSystem->setLightingEnabled(lighting);
	pRenderSystem->setDepthBufferCheckEnabled(depthCheck);
	pRenderSystem->setDepthBufferWriteEnabled(depthWrite);
	pRenderSystem->setWorldMatrix(mtxWorld);
}

void SceneManager::drawTopMost(IRenderSystem* pRenderSystem)
{
	DisplayListPtr end, it;

	// ��������ͼ��
	PP_BY_NAME_START("SceneManager::drawTopMost::pEntity->drawAlwayseTopMost(��������ͼ��)");
	end = m_VisibleListObj.end();
	for (it=m_VisibleListObj.begin(); it!=end; ++it)
	{
		if( (*it)->getEntityType() == typeMonster)
		{	
			EntityView *pEntity = *it;
			pEntity->drawAlwayseTopMost(pRenderSystem);		
		}
	}
	PP_BY_NAME_STOP();

    //  ʵ����Ϣ�Ļ��ƣ��ų����䣻
	PP_BY_NAME_START("SceneManager::drawTopMost::pEntity->drawTopMost(ʵ����Ϣ�Ļ��ƣ��ų�����)");
    if (m_dwDrawFlag & eDrawEntityInfo)
    {
        end = m_VisibleListGround.end();
        for (it = m_VisibleListGround.begin(); it!=end; ++it)
        {
            EntityView *pEntity = *it;
            pEntity->drawTopMost(pRenderSystem);
        }

        end = m_VisibleListObj.end();
        for (it=m_VisibleListObj.begin(); it!=end; ++it)
        {
			if( (*it)->getEntityType() == typeBox)
				continue;

            EntityView *pEntity = *it;
			if (pEntity->hasFlag(flagUnRender))
			{
				continue;
			}
            pEntity->drawTopMost(pRenderSystem);
        }
    }
	PP_BY_NAME_STOP();

	//	���Ʊ�����Ϣ
	PP_BY_NAME_START("SceneManager::drawTopMost::pEntity->drawTopMost(���Ʊ�����Ϣ)")
	
	//  ����Ļ��ƺ����⣬�����ͣʱҪһֱ���ƣ������eDrawEntityBoxInfo
	{
		end = m_VisibleListObj.end();
		for (it=m_VisibleListObj.begin(); it!=end; ++it)
		{
			if( (*it)->getEntityType() != typeBox)
				continue;

			EntityView *pEntity = *it;
			
			if (m_dwDrawFlag & eDrawEntityBoxInfo || pEntity->hasFlag(flagDrawBoxMouseMove))
			{
				pEntity->drawTopMost(pRenderSystem);
			}		
		}
	}
	PP_BY_NAME_STOP();

    // ����ͷ����Ч
	PP_BY_NAME_START("SceneManager::drawTopMost::pEntity->drawTopMostEffect")
	end = m_VisibleListObj.end();
	for (it=m_VisibleListObj.begin(); it!=end; ++it)
	{
		if( (*it)->getEntityType() == typePerson)
		{
			EntityView *pEntity = *it;
			if (pEntity->hasFlag(flagUnRender))
			{
				continue;
			}
			pEntity->drawTopMostEffect(pRenderSystem);
		}
	}
	PP_BY_NAME_STOP();

	PP_BY_NAME_START("SceneManager::drawTopMost::m_GroundEyeshot.drawTileLine");
    if (m_dwDrawFlag & eDrawGrid)
	{
		m_GroundEyeshot.drawTileLine();
	}
	PP_BY_NAME_STOP();


	PP_BY_NAME_START("SceneManager::drawTopMost::OnDrawOccupant");
	if (m_dwDrawFlag & eDrawOccupant)
	{
		//if(!m_pOccupantImageRect)
		//{
		//	m_pOccupantImageRect = new ImageRect;
		//	ColorValue c = ColorValue(1,0,1);
		//	m_pOccupantImageRect->initialize(getRenderEngine()->getRenderSystem(),"mask.bmp",false,&c);
		//}

		xs::Rect rcWorld = m_GroundEyeshot.getViewportRect();
		InflateRect(&rcWorld, 64 * 2, 32 * 2);
		IntersectRect(&rcWorld, &rcWorld, &m_SceneCo.getMapRect());
		EnumTile ListBuf[MAX_EnumItem_COUNT];
		int nListCount = MAX_EnumItem_COUNT;
		if (m_Map.enumTileByWorldRect(rcWorld, nListCount, ListBuf))
		{
			for (int i=0; i<nListCount; i++)
			{
				OnDrawOccupant(ListBuf[i].ptTile, ListBuf[i].pTile,0);
			}
		}
	}
	PP_BY_NAME_STOP();


	PP_BY_NAME_START("SceneManager::drawTopMost::OnDrawSortPoint&OnDrawAnchor");
	if ((m_dwDrawFlag & eDrawSortPoint) || (m_dwDrawFlag & eDrawAnchor))
	{
		xs::Rect rcWorld = m_GroundEyeshot.getViewportRect();
		InflateRect(&rcWorld, 64 * 2, 32 * 2);
		IntersectRect(&rcWorld, &rcWorld, &m_SceneCo.getMapRect());
		EnumItem ListBuf[MAX_EnumItem_COUNT];
		int nListCount = MAX_EnumItem_COUNT;
		if (m_Map.enumEntityByWorldRect(rcWorld, nListCount, ListBuf))
		{
			if(m_dwDrawFlag & eDrawSortPoint)
			{
				for (int i=0; i<nListCount; i++)
				{
					OnDrawSortPoint(ListBuf[i].ptTile, ListBuf[i].pEntity);
				}
			}
			if(m_dwDrawFlag & eDrawAnchor)
			{
				for(int i = 0;i < nListCount;i++)
				{
					OnDrawAnchor(ListBuf[i].ptTile,ListBuf[i].pEntity);
				}
			}
		}

		list<xs::Point>::iterator it = m_ListSkillTile.begin();
		for (it; it!=m_ListSkillTile.end(); it++)
		{
			xs::Point pt = (*it);
			OnDrawAnchor(pt, NULL);
		}
	}
	PP_BY_NAME_STOP();

	PP_BY_NAME_START("SceneManager::drawTopMost::DrawMapGrid");
	if(m_dwDrawFlag & eDrawMapGrid)
	{
		xs::Rect rcWorld = m_GroundEyeshot.getViewportRect();
		int lx = rcWorld.left / GRID_WIDTH;
		int ly = rcWorld.top / GRID_HEIGHT;
		int nx = (rcWorld.right - rcWorld.left + (GRID_WIDTH - 1)) / GRID_WIDTH;
		int ny = (rcWorld.bottom - rcWorld.top + (GRID_HEIGHT - 1)) / GRID_HEIGHT;
		for(int x = lx;x <= lx + nx;x++)
		for(int y = ly;y <= ly + ny;y++)
		{
			ColorValue c = pRenderSystem->getColor();
			pRenderSystem->setColor(ColorValue::Green);
			pRenderSystem->beginPrimitive(PT_LINE_LOOP);
			pRenderSystem->sendVertex(Vector2(x * GRID_WIDTH - rcWorld.left,y * GRID_HEIGHT - rcWorld.top));
			pRenderSystem->sendVertex(Vector2(x * GRID_WIDTH - rcWorld.left,(y + 1) * GRID_HEIGHT - rcWorld.top));
			pRenderSystem->sendVertex(Vector2((x + 1) * GRID_WIDTH - rcWorld.left,(y + 1) * GRID_HEIGHT - rcWorld.top));
			pRenderSystem->sendVertex(Vector2((x + 1) * GRID_WIDTH - rcWorld.left,y * GRID_HEIGHT - rcWorld.top));
			pRenderSystem->endPrimitive();
			pRenderSystem->setColor(c);
		}
	}
	PP_BY_NAME_STOP();


	PP_BY_NAME_START("SceneManager::drawTopMost::Draw9Grid");
	if(m_dwDrawFlag & eDraw9Grid)
	{
		const xs::Rect& rc = getViewportRect();
		xs::Point ptCenter;
		ptCenter.x = (rc.right + rc.left) >> 1;
		ptCenter.y = (rc.bottom + rc.top) >> 1;
		Vector3 vSpace;
		world2Space(ptCenter,vSpace);
		static float w = 512 * Math::fSqrt2;
		int x = vSpace.x / w;
		int z = vSpace.z / w;
		Vector3 vCenter = Vector3(x * w,0,z * w);
		for(int i = -2;i <= 2;i++)
		for(int j = -2;j <= 2;j++)
		{
			Vector3 v1 = vCenter + Vector3(i * w,0,j * w);
			Vector3 v2 = v1 + Vector3(w,0,0);
			Vector3 v3 = v1 + Vector3(w,0,w);
			Vector3 v4 = v1 + Vector3(0,0,w);
			xs::Point pt1,pt2,pt3,pt4;
			space2World(v1,pt1);
			space2World(v2,pt2);
			space2World(v3,pt3);
			space2World(v4,pt4);
			xs::Point ptS1,ptS2,ptS3,ptS4;
			world2Screen(pt1,ptS1);
			world2Screen(pt2,ptS2);
			world2Screen(pt3,ptS3);
			world2Screen(pt4,ptS4);

			ColorValue c = pRenderSystem->getColor();
			pRenderSystem->setColor(ColorValue::Red);
			pRenderSystem->beginPrimitive(PT_LINE_LOOP);
			pRenderSystem->sendVertex(Vector2(ptS1.x,ptS1.y));
			pRenderSystem->sendVertex(Vector2(ptS2.x,ptS2.y));
			pRenderSystem->sendVertex(Vector2(ptS3.x,ptS3.y));
			pRenderSystem->sendVertex(Vector2(ptS4.x,ptS4.y));
			pRenderSystem->endPrimitive();
			pRenderSystem->setColor(c);
		}
	}
	PP_BY_NAME_STOP();
}
// 
bool SceneManager::findPathEX(xs::Point ptFrom, xs::Point ptTo, xs::Point** ppBuffer, int& nPathLen)
{
	if (m_Map.FindPath(ptFrom,ptTo,*ppBuffer, nPathLen))
	{
		return true;
	}
	return false;
}

bool SceneManager::findPath(xs::Point ptFrom, xs::Point ptTo, xs::Point** ppBuffer, int& nPathLen)
{
	return m_Map.FindPathByASatr(ptFrom, ptTo, *ppBuffer, nPathLen);
}

bool SceneManager::findPathAStar(xs::Point ptFrom, xs::Point ptTo, xs::Point** ppBuffer, int& nPathLen,bool isNoBlock)
{
	//�����ǰ�ҵ��������ٽ���Ѱ��
	int nTempPathLen = CPathFindAStar::s_aResultAStar.size();
	if (nTempPathLen != 0 )
	{
		for(int i = 0; i < nTempPathLen; i++ )
		{
			// ˵��������ԭ��·���� ����Ҫ�ٴ���A*����
			if (CPathFindAStar::s_aResultAStar[i].x == ptFrom.x && CPathFindAStar::s_aResultAStar[i].y == ptFrom.y
				&& CPathFindAStar::s_aResultAStar[nTempPathLen-1].x == ptTo.x &&  CPathFindAStar::s_aResultAStar[nTempPathLen-1].y == ptTo.y)
			{
				nPathLen = nTempPathLen - i;
				*ppBuffer = &CPathFindAStar::s_aResultAStar[i];
				return true;
			}
		}
		
	}
	// �������������Ҫ����A*Ѱ·��
	//int time_1 = getTickCount();
	if (m_PathFindAStar.FindPath(ptFrom,ptTo,true,getSceneMgr(),isNoBlock))
	{
		m_PathFindAStar.QueryResult();
		nPathLen = CPathFindAStar::s_aResultAStar.size();
	/*	int time_2 = getTickCount();
		int time = time_2 - time_1;
		Info("A*Ѱ·��ʱ:"<<time<<endl);;*/
		if (nPathLen == 0 )
		{
			return false;
		}
		*ppBuffer = &CPathFindAStar::s_aResultAStar[0];
		return true;
	}
	return false;
}
bool SceneManager::findPathViaWaypoint(xs::Point ptFrom, xs::Point ptTo, xs::Point** ppBuffer, int& nPathLen)
{
	static std::vector<xs::Point> vPath;
	static std::list<xs::Point> lPath;
	vPath.clear();
	lPath.clear();
	if(m_WayPointManager.findPath(ptFrom.x,ptFrom.y,ptTo.x,ptTo.y,lPath))
	{
		if (lPath.size() == 0)
		{
			return false;
		}
		vPath.reserve(lPath.size());
		for(std::list<xs::Point>::iterator it = lPath.begin();it != lPath.end();++it)
		{
			xs::Point pt ((*it).x,(*it).y);
			vPath.push_back(pt);
		}
		*ppBuffer = &vPath[0];
		nPathLen = vPath.size();
		return true;
	}
	return false;
}

void SceneManager::hitTest(const xs::Point& pt,EntityView** ppEntityViews,int& nNum)
{
	if(nNum == 0)return;

	IRenderSystem *pRenderSystem = getRenderEngine()->getRenderSystem();

	//int pick[32];
	int num = 32;
	//pRenderSystem->beginSelection(pt.x,pt.y,3);
	int index = 1;
	int currIndex = 0;

	Matrix4 mtxWorld = pRenderSystem->getWorldMatrix();

	DisplayListReversePtr end = m_VisibleListObj.rend();
	for (DisplayListReversePtr it=m_VisibleListObj.rbegin(); it!=end; ++it)
	{
		EntityView *pEntity = *it;
		ulong flag = pEntity->getFlag();
		if(flag & flagSelectable)
		{
			if(flag & flag2D)
			{
				xs::Rect rect = pEntity->getShowRect();
				if( pEntity->getEntityType() == typeBox)
				{
					// ����box�İ�Χ��
					rect.top -= 25;
				}
				xs::Point ptWorld = pEntity->getWorld();
				OffsetRect(&rect,ptWorld.x,ptWorld.y);
				xs::Point ptMouse;
				screen2World(pt,ptMouse);
				if(PtInRect(&rect,ptMouse) && !pEntity->isTransparent(ptMouse.x - rect.left,ptMouse.y - rect.top))
				{
					if(currIndex < nNum)ppEntityViews[currIndex++] = pEntity;
				}
			}
		}
	}

	end = m_VisibleListObj.rend();
	for (DisplayListReversePtr it=m_VisibleListObj.rbegin(); it!=end; ++it)
	{
		EntityView *pEntity = *it;
		ulong flag = pEntity->getFlag();
		if(flag & flagSelectable)
		{
			if(flag & flag3D)
			{
				//pRenderSystem->setSelectionIndex(index);
				//pItemViewPtr.pEntity->drawPickObject(pRenderSystem,false);
				//index++;
				//m_selectableEntities.push_back(pItemViewPtr);
				xs::Rect rect = pEntity->getShowRect();
				xs::Point ptWorld = pEntity->getWorld();
				OffsetRect(&rect,ptWorld.x,ptWorld.y);
				xs::Point ptMouse;
				screen2World(pt,ptMouse);
				if(PtInRect(&rect,ptMouse))
				{
					ulong ulEntityType =  pEntity->getEntityType();
					if(currIndex < nNum)
					{
						ppEntityViews[currIndex++] = pEntity;
					}
					else if(currIndex == nNum && ulEntityType == typeMonster)  // ����������ֵ����һ��Ŀ��㣻
					{
						ulong ulppEntityType = ppEntityViews[0]->getEntityType();
						if ( ulppEntityType == typePerson || ulppEntityType == typePet)
						{
							ppEntityViews[0] = pEntity;
						}
					}
				}
			}
		}
	}

	end = m_VisibleListGround.rend();
	for (DisplayListReversePtr it = m_VisibleListGround.rbegin(); it!=end; ++it)
	{
		EntityView *pEntity = *it;
		if(pEntity->getFlag() & flagSelectable)
		{
			xs::Rect rect = pEntity->getShowRect();
			xs::Point ptWorld = pEntity->getWorld();
			OffsetRect(&rect,ptWorld.x,ptWorld.y);
			xs::Point ptMouse;
			screen2World(pt,ptMouse);
			if(PtInRect(&rect,ptMouse) && !pEntity->isTransparent(ptMouse.x - rect.left,ptMouse.y - rect.top))
			{
				if(currIndex < nNum)ppEntityViews[currIndex++] = pEntity;
			}
		}
	}

	//pRenderSystem->endSelection(num,pick);
	pRenderSystem->setWorldMatrix(mtxWorld);

	//for(int i = 0;i < num && currIndex < nNum;i++)
	//{
	//	ppEntityViews[currIndex++] = m_selectableEntities[pick[i] - 1].pEntity;
	//}

	nNum = currIndex;
}

EntityView*	SceneManager::hitTest(const xs::Point& pt)
{
	EntityView *pEntity = 0;
	int nNum = 1;
	hitTest(pt,&pEntity,nNum);

	return pEntity;
}

bool SceneManager::IsIntersect(EntityView& item1, EntityView& item2, xs::Rect& rc)
{
	xs::Point ptTileWorld;
	ptTileWorld = item1.getWorld();
	xs::Rect rc1 = item1.getShowRect();
	OffsetRect(&rc1, ptTileWorld.x, ptTileWorld.y);
	
	ptTileWorld = item2.getWorld();
	xs::Rect rc2 = item2.getShowRect();
	OffsetRect(&rc2, ptTileWorld.x, ptTileWorld.y);
	return IntersectRect(&rc, &rc1, &rc2) != FALSE;

	return false;
}

int SceneManager::cmpPP(EntityView& item1, EntityView& item2)
{
	xs::Rect rc;
	if (IsIntersect(item1, item2, rc))
	{
		//��ʾ
		if (item1.getSortLeft().y == item2.getSortLeft().y)
			return CMP_EQ;
		return (item1.getSortLeft().y < item2.getSortLeft().y) ? CMP_LT : CMP_GT;
	}

	//����Ļ�Ҫ����һ���Ⱥ������
	if(item1.getEntityType()==typeStatic&&item2.getEntityType()==typeStatic)
		return (item1.getSortRight().y < item2.getSortRight().y) ? CMP_LT : CMP_GT;

	return CMP_EQ;
}

int SceneManager::cmpPL(EntityView& item1, EntityView& item2)
{
	xs::Rect rc;
	if (IsIntersect(item1, item2, rc))
	{
		if (item2.getSortLeft().y == item2.getSortRight().y)
			return (item1.getSortLeft().y < item2.getSortLeft().y) ? CMP_LT : CMP_GT;

		//Unnamed
		if(item2.getSortRight().x == item2.getSortLeft().x)return CMP_EQ;
		//
		
		//�����ߵĽ���,��ֱͶӰ
		int Ycross = (item1.getSortLeft().x - item2.getSortLeft().x) * (item2.getSortRight().y - item2.getSortLeft().y )
					/ (item2.getSortRight().x - item2.getSortLeft().x) + item2.getSortLeft().y;
		if ((Ycross > item1.getSortLeft().y) || 
			(Ycross == item1.getSortLeft().y && Ycross <= item2.getSortLeft().y && Ycross <= item2.getSortRight().y)) 
			return CMP_LT;
		return CMP_GT;
	}

	//����Ļ�Ҫ����һ���Ⱥ������
	if(item1.getEntityType()==typeStatic&&item2.getEntityType()==typeStatic)
		return (item1.getSortRight().y < item2.getSortRight().y) ? CMP_LT : CMP_GT;

	return CMP_EQ;
}

int SceneManager::cmpLL(EntityView& item1, EntityView& item2)
{
	xs::Rect rc;
	if (IsIntersect(item1, item2, rc))
	{
		int Xcross = (rc.left + rc.right ) /2;

		//Unnamed
		if(item1.getSortRight().x == item1.getSortLeft().x || item2.getSortRight().x == item2.getSortLeft().x)return CMP_EQ;
		//

		int Ycross1 = (Xcross - item1.getSortLeft().x) * (item1.getSortRight().y - item1.getSortLeft().y ) 
			/ (item1.getSortRight().x - item1.getSortLeft().x) + item1.getSortLeft().y;
		int Ycross2 = (Xcross - item2.getSortLeft().x) * (item2.getSortRight().y - item2.getSortLeft().y ) 
			/ (item2.getSortRight().x - item2.getSortLeft().x) + item2.getSortLeft().y;
		if (Ycross1 == Ycross2)
		{
			int dy_center = (item1.getSortLeft().y + item1.getSortRight().y) - (item2.getSortLeft().y + item2.getSortRight().y);
			return (dy_center < 0) ? CMP_LT : CMP_GT;
		}
		return (Ycross1 < Ycross2) ? CMP_LT : CMP_GT;
	}

	//����Ļ�Ҫ����һ���Ⱥ������
	if(item1.getEntityType()==typeStatic&&item2.getEntityType()==typeStatic)
		return (item1.getSortRight().y < item2.getSortRight().y) ? CMP_LT : CMP_GT;

	return CMP_EQ;
}

int SceneManager::compare(EntityView& item1, EntityView& item2)
{
	int nL1 = item1.getLayer();
	int nL2 = item2.getLayer();
	if (nL1 != nL2)
		return (nL1 < nL2) ? CMP_LT : CMP_GT;

	//�����box���ȴ���,Ϊ��ײ�
	if(item1.getEntityType()==typeBox)
		return CMP_LT;
	if(item2.getEntityType()==typeBox)
		return CMP_GT;
	
	//û���赲��Ϣ�������getSortRight == getSortLeft
	int nRtn = 0;
	if (item1.getSortLeft().x == item1.getSortRight().x && item1.getSortLeft().y == item1.getSortRight().y) // this is point
	{
		if (item2.getSortLeft().x == item2.getSortRight().x && item2.getSortLeft().y == item2.getSortRight().y) // item is point
			nRtn = cmpPP(item1, item2);
		else
			nRtn = cmpPL(item1, item2);
	}
	else
	{
		if (item2.getSortLeft().x == item2.getSortRight().x && item2.getSortLeft().y == item2.getSortRight().y) // item is point
			nRtn = -cmpPL(item2, item1);
		else
			nRtn = cmpLL(item1, item2);
	}
	
	return nRtn;
}

void SceneManager::addSortingEntitiesAll(EntityView* pEntity, DisplayList& _DisplayList)
{
	xs::Point ptTileCenter;
	ptTileCenter = pEntity->getWorld();
	
	bool bFound = false;
	DisplayListPtr it = _DisplayList.begin();
	DisplayListPtr _end = _DisplayList.end();
	
	xs::Point ptTempTileCenter;
	while (it != _end)
	{
		ptTempTileCenter = (*it)->getWorld();
		if (ptTileCenter.y < ptTempTileCenter.y || 
			(ptTileCenter.y == ptTempTileCenter.y && ptTileCenter.x < ptTempTileCenter.x))
		{
			bFound = true;
			_DisplayList.insert(it, pEntity);
			break;
		}
		else ++it;
	}
	if (!bFound)
		_DisplayList.push_back(pEntity);
}

void SceneManager::addSortingEntities(EntityView* pEntity, DisplayList& _DisplayList)
{
	bool bFound = false;
	DisplayListPtr it = _DisplayList.begin();
	DisplayListPtr _end = _DisplayList.end();
	DisplayListPtr it_ptr = it;
	DisplayListPtr it_tmp;
	
	while (it != _end)
	{
		// ������С���Ծ ����������
		IEntity* pEntityData = (IEntity*)pEntity->getUserData();
		if (getRunType() == RUN_TYPE_GAME)
		{
			if (pEntityData && pEntityData->GetEntityClass()->IsPerson())
			{
				IPerson* pPerson = (IPerson*) pEntityData;

				if (pPerson)
				{
					DWORD dwCurState = pPerson->GetCurState();
					bool  bfly = pPerson->GetFLyState();
					if (((bfly == true) && (pPerson->GetNumProp(CREATURE_PROP_IGNO_BLCOK) > 0)) || dwCurState == CREATURE_CONTROLSTATE_JUMP)
					{
						break;
					}
				}
			}
		}
		if (compare(*pEntity, *(*it)) == CMP_LT)
		{
			bFound = true;
			if (it == _DisplayList.begin())
			{
				_DisplayList.push_front(pEntity);
				it = _DisplayList.begin();
				++it;
			}
			else
			{
				_DisplayList.insert(it, pEntity);
			}
			it_ptr = it;
			--it_ptr;
			break;
		}
		else ++it;
	}
	if (!bFound)
		_DisplayList.push_back(pEntity);

	//�˾����������С,�ֱȺ���Ĵ�,������˵�ǲ����ܳ��ֵ�,��Ϊ�ж��������������������Ĵ���,�ر�������ص���ʱ��
	//�����������ȡ��������ں���,Ҳ����ȡС��,ȡ����˾������������.
	//��������Ĵ����ڲ����ʱ��Ҳ������

	//if (bFound)
	//{
	//	_end = _DisplayList.end();
	//	int nErrNum = 0;
	//	for (++it; it!=_end; ++it)
	//	{
	//		//if(!(*it).valid);
	//		//else
	//		if (compare(*pEntity, *(*it)) == CMP_GT)
	//		{
	//			nErrNum++;
	//			it_tmp = it;
	//			--it_tmp;
	//			_DisplayList.insert(it_ptr, *it);
	//			_DisplayList.erase(it);
	//			it = it_tmp;
	//			_end = _DisplayList.end();
	//		}
	//	}
	//}
}

void SceneManager::sortVisibleEntities()
{
	m_VisibleListObj.clear();
	DisplayListPtr it =m_VisibleListMultiOcc.begin();
	DisplayListPtr _end = m_VisibleListMultiOcc.end();
	for (; it!=_end; ++it)
	{
		addSortingEntities((*it), m_VisibleListObj);
	}
}

void SceneManager::setDrawFlag(DWORD dwFlag, DWORD dwClearFlag, void* pParam)
{
	m_dwDrawFlag &= ~dwClearFlag;
	m_dwDrawFlag |= dwFlag;
}

DWORD SceneManager::getDrawFlag()
{
	return m_dwDrawFlag;
}

bool SceneManager::enumTileByWorldRect(const xs::Rect& rcWorld, IN OUT int& nListCount, OUT SnapshotTileInfo* pListBuf)
{
	return m_Map.enumTileByWorldRect(rcWorld,nListCount, (EnumTile*)pListBuf);
}

bool SceneManager::enumEntityByWorldRect(const xs::Rect& rcWorld, IN OUT int& nListCount, OUT SnapshotItemInfo* pListBuf)
{
	return m_Map.enumEntityByWorldRect(rcWorld,nListCount, (EnumItem*)pListBuf);
}

int SceneManager::getViewTopLeftX() const
{
	return m_GroundEyeshot.getViewTopX();
}

int SceneManager::getViewTopLeftY() const
{
	return m_GroundEyeshot.getViewTopY();
}

void SceneManager::screen2Tile(const xs::Point& ptScreen, xs::Point &ptTile) const
{
	m_GroundEyeshot.pixel2Tile(ptScreen,ptTile);
}

void SceneManager::tile2Screen(const xs::Point &ptTile, xs::Point &ptTileCenter) const
{
	m_GroundEyeshot.tile2Pixel(ptTile,ptTileCenter);
}

void SceneManager::screen2World(IN const xs::Point& ptScreen, OUT xs::Point& ptWorld) const
{
	ptWorld.x = ptScreen.x + m_GroundEyeshot.getViewTopX();
	ptWorld.y = ptScreen.y + m_GroundEyeshot.getViewTopY();
}

void SceneManager::world2Screen(IN const xs::Point& ptWorld, OUT xs::Point& ptScreen) const
{
	ptScreen.x = ptWorld.x - m_GroundEyeshot.getViewTopX();
	ptScreen.y = ptWorld.y - m_GroundEyeshot.getViewTopY();
}

void SceneManager::tile2World(const xs::Point &ptTile, xs::Point &ptTileCenter) const
{
	m_SceneCo.tile2Pixel(ptTile,ptTileCenter);
}

void SceneManager::world2Tile(const xs::Point& ptWorld, xs::Point &ptTile) const
{
	m_SceneCo.pixel2Tile(ptWorld,ptTile);
}

Tile* SceneManager::getTile(const xs::Point& ptTile) const
{
	return &m_Map.getTile(ptTile);
}

Tile* SceneManager::getTileFromScreen(xs::Point ptScreen) const
{
	xs::Point ptTile;
	m_GroundEyeshot.pixel2Tile(ptScreen,ptTile);
	return &m_Map.getTile(ptTile);
}

bool SceneManager::isValidTile(const xs::Point& ptTile)
{
	return m_Map.getTile(ptTile).isValid();
}


bool SceneManager::isValid()
{
	return m_Map.isValid();
}

void SceneManager::release()
{
	close();
	delete this;
}
int SceneManager::getSceneWidth()const		{return m_Map.getSceneWidth();}
int SceneManager::getSceneHeight()const		{return m_Map.getSceneHeight();}
const xs::Rect& SceneManager::getViewportRect() const
{
	return m_GroundEyeshot.getViewportRect();
}

IGround*	SceneManager::getGround()
{
	return &m_GroundEyeshot;
}

int SceneManager::getMapTileWidth()
{
	return m_SceneCo.getMatrixWidth();
}

int SceneManager::getMapTileHeight()
{
	return m_SceneCo.getMatrixHeight();
}

void SceneManager::setupMatrix(bool wholeScene)
{
	if(!wholeScene)
	{
		xs::Rect rc = getViewportRect();
		OffsetRect(&rc,-rc.left,-rc.top);

		xs::Point ptWorld (0,0);
		xs::Point ptTile;
		world2Tile(ptWorld,ptTile);
		OffsetRect(&rc,((ptTile.y + 1) << 5) + getViewTopLeftX(),(ptTile.y << 4) - (rc.bottom - rc.top) - getViewTopLeftY());
		// note by zjp��
		// �������ͶӰ�������������Ⱦ3D����ģ���������ģ�ͣ�
		// 3Dģʽ�µ���ͼ������SceneManager�Ĺ��캯�����Ѿ��趨���ˣ���x��ת-30�ȣ���y��ת45�ȡ�
		m_mtxProjection = Matrix4::orthogonalProjection(rc.left,rc.right,rc.top,rc.bottom,-20000,20000);
	}
	else
	{
		uint width = getSceneWidth();
		uint height = getSceneHeight();
		xs::Rect rc (0,0,width,height);

		xs::Point ptWorld (0,0);
		xs::Point ptTile;
		world2Tile(ptWorld,ptTile);
		OffsetRect(&rc,((ptTile.y + 1) << 5),(ptTile.y << 4) - (rc.bottom - rc.top));
		m_mtxProjection = Matrix4::orthogonalProjection(rc.left,rc.right,rc.top,rc.bottom,-20000,20000);
	}
}

Matrix4	SceneManager::getProjectionMatrix()
{
	return m_mtxProjection;
}

Matrix4 SceneManager::getViewMatrix()
{
	return m_mtxView;
}

void SceneManager::tile2Space(const xs::Point& ptTile,Vector3& vSpace)
{
	vSpace.x = (((ptTile.y << 1) + 1) << 4) * Math::fSqrt2;
	vSpace.z = (((ptTile.x << 1) + 1) << 4) * Math::fSqrt2;
	vSpace.y = 0;
}

void SceneManager::world2Space(const xs::Point& ptWorld,Vector3& vSpace)
{
	xs::Point ptTile;
	world2Tile(ptWorld,ptTile);
	xs::Point ptW;
	tile2World(ptTile,ptW);
	Vector3 v;
	tile2Space(ptTile,v);

	xs::Point ptDelta (ptWorld.x - ptW.x,ptWorld.y - ptW.y);
	ptDelta.y <<= 1;

	static float sinN45 = Math::Sin(-Math::PI / 4.0f);
	static float cosN45 = Math::Cos(-Math::PI / 4.0f);

	Vector2 vDelta;
	vDelta.x = ptDelta.x * cosN45 + ptDelta.y * sinN45;
	vDelta.y = ptDelta.x * -sinN45 + ptDelta.y * cosN45;

	vSpace.x = v.x + vDelta.x;
	vSpace.z = v.z + vDelta.y;
	vSpace.y = 0;
}

void SceneManager::space2World(const Vector3& vSpace,xs::Point& ptWorld)
{
	xs::Point ptTile;
	space2Tile(vSpace,ptTile);
	Vector3 vS;
	tile2Space(ptTile,vS);		//Tile���ĵ�Ŀռ�����
	xs::Point ptW;
	tile2World(ptTile,ptW);		//Tile���ĵ����������

	Vector3 vDelta = vSpace - vS;

	static float sin45 = Math::Sin(Math::PI / 4.0f);
	static float cos45 = Math::Cos(Math::PI / 4.0f);
	static float halfSin45 = sin45 / 2.0f;
	static float halfCos45 = cos45 / 2.0f;

	float x = vDelta.x * cos45 + vDelta.z * sin45;
	float y = vDelta.x * -halfSin45 + vDelta.z * halfCos45;

	ptWorld.x = ptW.x + Math::Round(x);
	ptWorld.y = ptW.y + Math::Round(y);
}

void SceneManager::space2Tile(const Vector3& vSpace,xs::Point& ptTile)
{
	static float spaceWidth = 32 * Math::fSqrt2;
	ptTile.x = vSpace.z / spaceWidth;
	ptTile.y = vSpace.x / spaceWidth;
}

#include "CountDistance.h"

extern CCountDistance	g_countDistance;
int SceneManager::tileDistance(const xs::Point& ptTile1, const xs::Point& ptTile2)
{
	return g_countDistance.Distance(ptTile1,ptTile2);
}

void SceneManager::setLightDirection(const Vector3& v)
{
	m_lightDirection = v;
}

IMinimap* SceneManager::getMinimap()
{
	return &m_MinimapEyeshot;
}
/**
*/
EntityView*	SceneManager::getFirstEntity()
{
	return m_SceneEyeshot.getFirstEntity();
}

EntityView*	SceneManager::getNextEntity()
{
	return m_SceneEyeshot.getNextEntity();
}

const char*	SceneManager::getMapFileName()
{
	return m_strMapFilename.c_str();
}

ulong SceneManager::test()
{
	return 0;
}

RunType g_runtype = RUN_TYPE_GAME;
void SceneManager::setRunType(RunType rt)
{
	g_runtype = rt;
}

void SceneManager::SetDistanceTexture(const char *szFilename)
{
    m_GroundEyeshot.SetDistanceTexture(szFilename);
}

void SceneManager::SetAllEntityVisible()
{
	m_VisibleListGround.clear();

	xs::Rect rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = rc.left + GRID_WIDTH*100;
	rc.bottom = rc.top + GRID_HEIGHT*100;
	EnumItem ListBuf[4096];
	int nListCount = 4096;
	if (enumEntityByWorldRect(rc, nListCount, (SnapshotItemInfo*)ListBuf))
	{
		for (int i=0; i<nListCount; i++)
		{
			m_VisibleListGround.push_back(ListBuf[i].pEntity);
			//m_pSceneManager->OnEntityLeaveViewport(ListBuf[i].ptTile, );
		}
	}
	//m_VisibleListGround = m_DisplayList;
}

RunType SceneManager::getRunType()
{
	return g_runtype;
}

/**  A* �Զ�Ѱ·ʱ ������getTile()ȥ�ж�title���赲��Ϣ����Ϊ�ϵļ���Title�ķ�Χ�������ὫTitle���赲��Ϣ����Ϊtrue;
// ��˱�¶�˷���������ģ�����ȥ�ж�Title���赲��Ϣ;��WZH 2010.7.26��
@param ptTile Tile����
@return �����Ƿ��赲
*/
bool SceneManager::IsAllBlock(const xs::Point& ptTile)
{
	return getSceneMgr().IsAllBlock(ptTile);
}

void SceneManager::ShowSkillTile(const xs::Point& ptTile)
{
	m_ListSkillTile.push_back(ptTile);
}

void SceneManager::ClearSkillTile()
{
	m_ListSkillTile.clear();
}

bool SceneManager::addGlobalSceneMagic(EntityView* pEntity)
{
	if (NULL == pEntity)
	{
		return false;
	}
	Vector3 vecPos;
	world2Space(m_ptSave, vecPos);
	pEntity->setSpace(vecPos);
	pEntity->onEnterViewport(-80);
	pEntity->onAddEntity();
	// ����ȫ�ֳ�����Ч�б�
	m_VisibleListGlobalSceneMagic.push_back(pEntity);
	return true;
}


bool SceneManager::removeGlobalSceneMagic(EntityView* pEntity)
{
	if (NULL == pEntity)
	{
		return false;
	}

	pEntity->onRemoveEntity();
	if (!pEntity->hasFlag(flagFade) && !pEntity->hasFlag(flagFallMagic))
	{
		m_VisibleListGlobalSceneMagic.remove(pEntity);
	}
	
	return true;
}

void SceneManager::updateGlobalSceneMagic(float tick, float deltaTick, IRenderSystem* pRenderSystem)
{
	Vector3 vecPos;
	world2Space(m_ptSave, vecPos);

	EntityView* pEntityView = NULL;
	DisplayList::iterator end = m_VisibleListGlobalSceneMagic.end();
	for (DisplayList::iterator iter = m_VisibleListGlobalSceneMagic.begin(); iter != end; )
	{
		pEntityView = *iter;
		if (NULL != pEntityView)
		{
			pEntityView->setSpace(vecPos);
			if (!pEntityView->update(tick, deltaTick, pRenderSystem))
			{
				iter = m_VisibleListGlobalSceneMagic.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}

void SceneManager::drawGlobalSceneMagic(IRenderSystem* pRenderSystem)
{
	EntityView* pEntityView = NULL;
	DisplayList::iterator end = m_VisibleListGlobalSceneMagic.end();
	for (DisplayList::iterator iter = m_VisibleListGlobalSceneMagic.begin(); iter != end; ++iter)
	{
		pEntityView = *iter;
		if (NULL != pEntityView)
		{
			pEntityView->draw(pRenderSystem);
		}
	}
}

//������������
CSceneLock::CSceneLock()
{
	ISceneManager2* pSceneManger = gGlobalClient->getSceneManager();
	if (NULL != pSceneManger)
	{
		pSceneManger->LockScene();
	}	
}

CSceneLock::~CSceneLock()
{
	ISceneManager2* pSceneManger = gGlobalClient->getSceneManager();
	if (NULL != pSceneManger)
	{
		pSceneManger->UnLockScene();
	}	
}