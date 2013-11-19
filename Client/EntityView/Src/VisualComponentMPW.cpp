//==========================================================================
/**
* @file	  : VisualComponentMPW.cpp
* @author : 
* created : 2008-1-30   12:57
*/
//==========================================================================

#include "stdafx.h"
#include "VisualComponentMPW.h"
#include "IGlobalClient.h"
#include "IResourceManager.h"
#include "ISceneManager2.h"
#include "RenderEngine/Entity2DAniPack.h"
#include "RenderEngine/shaderdeclare.h"
#include "MWDLoader.h"


VisualComponentMPW* flag = 0;
VisualComponentMPW::VisualComponentMPW()  : mMwdInfo(0)
{
}

VisualComponentMPW::~VisualComponentMPW()
{
	close();
}

void VisualComponentMPW::create()
{
	getOwner()->setFlag(flag2D | flagInScreen | flagFade);
	//Info("create-mpw:"<<_fi("0x%08x", (ulong)getOwner())<<endl);
}

void VisualComponentMPW::close()
{
	getOwner()->removeFlag(flagFade);
	onLeaveViewport();
}

void VisualComponentMPW::onEnterViewport(int priority)
{
	requestRes(priority);
	if (getOwner()->hasFlag(flagFade|flagInScreen))
		setFadeIn();
}

void VisualComponentMPW::onLeaveViewport()
{
	if (isValidHandle(mHandle))
	{
		if (getOwner()->hasFlag(flagFade|flagInScreen))
			setFadeOut();
		else
		{
			//add by yhc,�ڱ༭��״̬�²��ͷ���Դ
			ISceneManager2* scene = gGlobalClient->getSceneManager();
			if(scene&&scene->getRunType() != RUN_TYPE_EDITOR)
				releaseRes();
		}
	}
}

void VisualComponentMPW::requestRes(int priority)
{
	if (!isValidHandle(mHandle))
	{
		if (getOwner()->getUserData() != 0)
			priority -= 2;
		if (getOwner()->isMainPlayer())
			priority--;

		Assert(getOwner()->getResId() != 0);
		mHandle = gGlobalClient->getResourceManager()->requestResource(getOwner()->getResId(), 
			(ResourceType)getOwner()->getResType(), false, priority);
		getRes();
	}
}

void VisualComponentMPW::releaseRes()
{
	if (isValidHandle(mHandle))
	{
		gGlobalClient->getResourceManager()->releaseResource(mHandle);
		mResLoaded = false;
		mHandle = INVALID_HANDLE;
		getOwner()->setNeedDelete();
	}
}

inline Entity2DAniPack* VisualComponentMPW::getRes()
{
	IResourceNode* node = (IResourceNode*)getHandleData(mHandle);
	if (node)
	{
		IResource* res = node->getResource();
		if (res)
		{
			Entity2DAniPack* n = (Entity2DAniPack*)res->getInnerData();
			if (n && !mResLoaded) onResLoaded(n);
			return n;
		}
	}
	return NULL;
}

void VisualComponentMPW::onResLoaded(Entity2DAniPack* node)
{
	mResLoaded = true;
}

void VisualComponentMPW::drawPickObject(IRenderSystem* pRenderSystem)
{
	Entity2DAniPack* pPack = getRes();;
	if (pPack)
	{
		int w = (*pPack->m_itlistImageRes).pMpwFrame->getWidth();
		int h = (*pPack->m_itlistImageRes).pMpwFrame->getHeight();

		Matrix4 mtxWorld;
		int nX,nY;
		if(mMwdInfo==NULL)
		{
			//û�ж�ȡ��mwd��Ϣ,������.2010.3.25
			//Trace("û�ж�ȡ��mwd��Ϣ: "<<pPack<<endl);
			return;
		}
		nX = mMwdInfo->anchorOffset.x - (*pPack->m_itlistImageRes).m_nOffsetX;
		nY = mMwdInfo->anchorOffset.y - (*pPack->m_itlistImageRes).m_nOffsetY;
		//mAniInfo->GetAnchorOffset(nX,nY);

        //  ��ê��ƫ�ƵĴ���ʹ����ܹ�������Ϊ��λ�����ƶ��ͷ��ã�
        xs::Point pointAnchorOffset = getOwner()->GetAnchorOffset();
        nX += pointAnchorOffset.x;
        nY += pointAnchorOffset.y;

        mtxWorld.makeTrans(getOwner()->getSpace());

		//by yhc ����λ�������������,���Ҳ�������������,
		static bool init = false;
		static Matrix4 mtxView;
		static Matrix4 mtxViewOld;
		if(!init)
		{
			//��ͬ������ʱ�����������mtxView��ͬ�����ڸ�Ϊֱ�Ӹ�ֵ
			//���������Ҫ���°ڷŵ���,����ʹ�õľ�ȷ�����������ֵ,��ʹ�ò�������ֵ
			//xs::Matrix4 mtxView1;
			//mtxView.PrecisionRotationX(30);
			//mtxView1.PrecisionRotationY(-45);
			//mtxView = mtxView1 * mtxView;
			mtxView[0][0] = 0.70710677f;
			mtxView[0][1] = 0.35355338f;
			mtxView[0][2] = -0.61237240f;
			mtxView[0][3] = 0.0f;

			mtxView[1][0] = 0.0f;
			mtxView[1][1] = 0.86602539f;
			mtxView[1][2] = 0.50000000f;
			mtxView[1][3] = 0.0f;

			mtxView[2][0] = 0.70710677f;
			mtxView[2][1] = -0.35355338f;
			mtxView[2][2] = 0.61237240f;
			mtxView[2][3] = 0.0f;

			mtxView[3][0] = 0.0f;
			mtxView[3][1] = 0.0f;
			mtxView[3][2] = 0.0f;
			mtxView[3][3] = 1.0f;

			//xs::Matrix4 mtxView2;
			//mtxViewOld.PrecisionRotationX(-30);
			//mtxView2.PrecisionRotationY(45);
			//mtxViewOld = mtxViewOld*mtxView2;
			mtxViewOld[0][0] = 0.70710677f;
			mtxViewOld[0][1] = 0.0f;
			mtxViewOld[0][2] = 0.70710677f;
			mtxViewOld[0][3] = 0.0f;

			mtxViewOld[1][0] = 0.35355338f;
			mtxViewOld[1][1] = 0.86602539f;
			mtxViewOld[1][2] = -0.35355338f;
			mtxViewOld[1][3] = 0.0f;

			mtxViewOld[2][0] = -0.61237240f;
			mtxViewOld[2][1] = 0.50000000f;
			mtxViewOld[2][2] = 0.61237240f;
			mtxViewOld[2][3] = 0.0f;

			mtxViewOld[3][0] = 0.0f;
			mtxViewOld[3][1] = 0.0f;
			mtxViewOld[3][2] = 0.0f;
			mtxViewOld[3][3] = 1.0f;
			
			init = true;
		}
		mtxWorld = mtxWorld * mtxView;

		Matrix4 mtxW;
		mtxW.makeTrans(-nX,-h + nY,0);
		mtxWorld = mtxWorld * mtxW;

		Matrix4 mtxSave = pRenderSystem->getWorldMatrix();

		Matrix4 mtxViewNow = pRenderSystem->getViewMatrix();

		//add by kevin.chen-----------------
		IShaderProgram* pShader = pRenderSystem->getShaderProgram(ESP_V3_UV_GC);
		pRenderSystem->bindCurrentShaderProgram(pShader);
		//--------------------------------
		pRenderSystem->setViewMatrix(mtxViewOld);
		pRenderSystem->setWorldMatrix(mtxWorld);
		pPack->Draw(mAlpha);
		pRenderSystem->setWorldMatrix(mtxSave);
		pRenderSystem->setViewMatrix(mtxViewNow);
	}
}

void VisualComponentMPW::draw(IRenderSystem* pRenderSystem)
{
	drawPickObject(pRenderSystem);
}

bool VisualComponentMPW::update(float tick, float deltaTick, IRenderSystem* pRenderSystem)
{
	//���¸���
	//VisualComponent::update( tick, deltaTick, pRenderSystem);

	if (flag == this)
	{
		breakable;
	}

	if (getOwner()->isNeedDelete()/* && mUpdateOption == 0*/)
	{
		if (!getOwner()->hasFlag(flagFade) || (mUpdateOption & updateFadeOut) == 0)
		{
			getOwner()->setNeedDelete(false);
			getOwner()->removeFlag(flagVisible);

			ISceneManager2* pSceneManager = gGlobalClient->getSceneManager();
			if (NULL != pSceneManager)
			{
				getOwner()->removeFlag(flagFade);
				// by yhc��ȫ���,�ӳ�������ȥ�� 2010.3.28
				pSceneManager->removeEntity(getOwner()->getTile(), getOwner());
				// end

				//zgz ��������͵ر�һ��������ViewPortʱ�����¼��أ����Դ˴���Ҫ�ͷ�
				if (pSceneManager->getRunType() == RUN_TYPE_GAME)
				{
					delete getOwner();
				}
			}
			
			return false;
		}
	}

	//if (getOwner()->isNeedDelete()/* && mUpdateOption == 0*/)
	//{
	//	//Info("delete-mpw:"<<_fi("0x%08x", (ulong)getOwner())<<endl);
	//	//if (getOwner()->hasFlag(flagInMap))
	//	//	gGlobalClient->getSceneManager()->removeEntity(getOwner()->getTile(), getOwner());
	//	//delete getOwner(); // ������ɾ��ֻ�Ƿ���false�������ʾ�б�
	//	return false;
	//}

	if (getOwner()->hasFlag(flagInScreen))
	{
		Entity2DAniPack* pPack = getRes();
		if (pPack)
		{
			if (mUpdateOption && getOwner()->hasFlag(flagFade))
			{


				if (mUpdateOption & updateFadeIn)
				{
					mAlpha += FADE_ALPHA * deltaTick;
					if (mAlpha > 1.0f)
					{
						mAlpha = 1.0f;
						mUpdateOption &= ~updateFadeIn;
					}
				}

				if (mUpdateOption & updateFadeOut)
				{
					mAlpha -= FADE_ALPHA * deltaTick;
					if (mAlpha < 0.f)
					{
						mAlpha = 0.f;
						mUpdateOption &= ~updateFadeOut;
						releaseRes();
					}
				}
			}
		}
	}
	else
	{
		Entity2DAniPack* pPack = getRes();
		if (pPack)
		{
			if (mUpdateOption && getOwner()->hasFlag(flagFade))
			{

				if (mUpdateOption & updateFadeIn)
				{
					mAlpha += FADE_ALPHA * deltaTick;
					if (mAlpha > 1.0f)
					{
						mAlpha = 1.0f;
						mUpdateOption &= ~updateFadeIn;
					}
				}

				if (mUpdateOption & updateFadeOut)
				{
					mAlpha -= FADE_ALPHA * deltaTick;
					if (mAlpha < 0.f)
					{
						mAlpha = 0.f;
						mUpdateOption &= ~updateFadeOut;
						releaseRes();
					}
				}
			}
		}
	}

	return true;
}

// len + string ( no include '\0')
size_t VisualComponentMPW::onLoad(Stream* stream, size_t len)
{
	char name[256];
	uchar str_len;
	stream->read(&str_len, sizeof(uchar));
	stream->read(name, str_len);
	name[str_len] = 0;

	ulong id = MWPFileNameMap::getInstance().map(name);
	getOwner()->setResId(id);
	readMWD();
	return str_len + sizeof(uchar);
}

// len + string ( no include '\0')
size_t VisualComponentMPW::onSave(Stream* stream) const
{
	const std::string& resId = MWPFileNameMap::getInstance().find(getOwner()->getResId());
	Assert(resId.length() < 256);
	uchar str_len = (uchar)resId.length();
	stream->write(&str_len, sizeof(uchar));
	stream->write(resId.c_str(), str_len);
    uchar uPointLength = sizeof(xs::Point);
	xs::Point pointAnchorOffset = getOwner()->GetAnchorOffset();
    stream->write((const void *)&pointAnchorOffset, sizeof(xs::Point));

    return uPointLength + str_len + sizeof(uchar);
}

bool VisualComponentMPW::isTransparent(int x, int y)
{
	Entity2DAniPack* pPack = getRes();
	return pPack ? (*pPack->m_itlistImageRes).pMpwFrame->isTransparent(x - (*pPack->m_itlistImageRes).m_nOffsetX, y - (*pPack->m_itlistImageRes).m_nOffsetY) : true;
}

bool VisualComponentMPW::readMWD()
{
	std::string mwd = MWPFileNameMap::getInstance().find(getOwner()->getResId());
	StringHelper::replace(mwd, ".mpw", ".mwd");
	mMwdInfo = MwdInfoReader::getInstance().find(mwd);
	if (!mMwdInfo)
		return false;

	//if (!(mAniInfo = MWDLoader::getInstance().request(mwd)))
	//	return false;

	int x,y;
	x = mMwdInfo->anchorOffset.x;
	y = mMwdInfo->anchorOffset.y;
	//mAniInfo->GetAnchorOffset(x, y);
	mShowRect.left = -x/* + (*pPack->m_itlistImageRes).m_nOffsetX*/;
	mShowRect.top = -y /*+ (*pPack->m_itlistImageRes).m_nOffsetY*/;
	mShowRect.right = mMwdInfo->w/* - (*pPack->m_itlistImageRes).m_nOffsetX*//*->GetImageMaxWidth()*/ - x;
	mShowRect.bottom = mMwdInfo->h/* - (*pPack->m_itlistImageRes).m_nOffsetY*//*mAniInfo->GetImageMaxHeight()*/ - y;
	setOccupantInfo();
	return true;
}
/*
void VisualComponentMPW::setOccupantInfo()
{
	if (getOwner()->getOccupantValue() == 0) // ��ռλ
		return;

	// ռλ��Ϣ
	char buffer[4096];
	OccupantTileList *pOccupant = (OccupantTileList*)buffer;

	xs::Point ptTileOffset;
	int nSizeW = 0, nSizeH = 0;
	CAniInfoHeader *pInfo = mAniInfo;
	pInfo->GetTileOffset((int &)ptTileOffset.x, (int &)ptTileOffset.y);
	pInfo->GetTileSize(nSizeW, nSizeH);

	bool bOccupants = false;

	if (ptTileOffset.x == INVALID_COORDINATE || ptTileOffset.y == INVALID_COORDINATE || nSizeW == 0 || nSizeH == 0)
	{
		pOccupant->init(0);
		pOccupant->getParamData().nOffAnchorX = 0;
		pOccupant->getParamData().nOffAnchorY = 0;
		pOccupant->getParamData().wWidth = 0;
		pOccupant->getParamData().wHeight = 0;
	}
	else
	{
		DWORD * pTileFlag = pInfo->GetTileInfor();
		if (pTileFlag == NULL)
		{
			pOccupant->init(0);
			pOccupant->getParamData().nOffAnchorX = 0;
			pOccupant->getParamData().nOffAnchorY = 0;
			pOccupant->getParamData().wWidth = 0;
			pOccupant->getParamData().wHeight = 0;
		}
		else
		{
			pOccupant->init(nSizeW * nSizeH);
			pOccupant->getParamData().nOffAnchorX = ptTileOffset.x;
			pOccupant->getParamData().nOffAnchorY = ptTileOffset.y;
			pOccupant->getParamData().wWidth = nSizeW;
			pOccupant->getParamData().wHeight = nSizeH;

			for(int ny = 0; ny < nSizeH; ny++)
			{
				for(int nx = 0; nx < nSizeW; nx++)
				{
					short c = 0;
					DWORD dwFlags = pTileFlag[ny * nSizeW + nx];
					if(dwFlags & Tile::tGroundBlock_Surface)
					{
						c |= Tile::tGroundBlock_Entity;
					}

					if(dwFlags & Tile::tFlyBlock_Surface)
					{
						c |= Tile::tFlyBlock_Entity;
					}

					if(dwFlags & Tile::tSpreadBlock_Surface)
					{
						c |= Tile::tSpreadBlock_Entity;
					}
					char cc = c >> 8;

					pOccupant->add(cc);
				}
			}

			bOccupants = true;
		}
	}
	if (bOccupants)
		setOccupantTileList(pOccupant);
	else
	{
		getOwner()->setLayer(lvlSpecificBlock);
		getOwner()->setOccupantValue(0);
	}
}*/

void VisualComponentMPW::setOccupantInfo()
{
	//add by yhc,��Ҫ�����ռλ��Ϣ��,ֱ���ڱ༭������༭�赲
	//return;

	if (getOwner()->getOccupantValue() == 0) // ��ռλ
		return;

	// ռλ��Ϣ
	char buffer[4096];
	OccupantTileList *pOccupant = (OccupantTileList*)buffer;

	xs::Point ptTileOffset;
	ptTileOffset.x = mMwdInfo->tileOffset.x;
	ptTileOffset.y = mMwdInfo->tileOffset.y;
	int nSizeW = mMwdInfo->tileWidth;
	int nSizeH = mMwdInfo->tileHeight;
	
	//CAniInfoHeader* pInfo = mAniInfo;
	//pInfo->GetTileOffset((int &)ptTileOffset.x, (int &)ptTileOffset.y);
	//pInfo->GetTileSize(nSizeW, nSizeH);

	bool bOccupants = false;

	if (ptTileOffset.x == INVALID_COORDINATE || ptTileOffset.y == INVALID_COORDINATE || nSizeW == 0 || nSizeH == 0) // ?????? INVALID_COORDINATE
	{
		pOccupant->init(0);
		pOccupant->getParamData().nOffAnchorX = 0;
		pOccupant->getParamData().nOffAnchorY = 0;
		pOccupant->getParamData().wWidth = 0;
		pOccupant->getParamData().wHeight = 0;
	}
	else
	{
		uchar* tiles = (uchar*)mMwdInfo + sizeof(MwdInfo);
		/*DWORD * pTileFlag = pInfo->GetTileInfor();
		if (pTileFlag == NULL)
		{
			pOccupant->init(0);
			pOccupant->getParamData().nOffAnchorX = 0;
			pOccupant->getParamData().nOffAnchorY = 0;
			pOccupant->getParamData().wWidth = 0;
			pOccupant->getParamData().wHeight = 0;
		}
		else*/
		{
			pOccupant->init(nSizeW * nSizeH);
			pOccupant->getParamData().nOffAnchorX = ptTileOffset.x;
			pOccupant->getParamData().nOffAnchorY = ptTileOffset.y;
			pOccupant->getParamData().wWidth = nSizeW;
			pOccupant->getParamData().wHeight = nSizeH;

			for(int ny = 0; ny < nSizeH; ny++)
			{
				for(int nx = 0; nx < nSizeW; nx++)
				{
					short c = 0;
					uchar dwFlags = tiles[ny * nSizeW + nx];
					if(dwFlags & Tile::tGroundBlock_Surface)
					{
						c |= Tile::tGroundBlock_Entity;
					}

					if(dwFlags & Tile::tFlyBlock_Surface)
					{
						c |= Tile::tFlyBlock_Entity;
					}

					if(dwFlags & Tile::tSpreadBlock_Surface)
					{
						c |= Tile::tSpreadBlock_Entity;
					}
					char cc = c >> 8;

					pOccupant->add(cc);
				}
			}

			bOccupants = true;
		}
	}
	if (bOccupants)
		setOccupantTileList(pOccupant);
	else
	{
		getOwner()->setLayer(lvlSpecificBlock);
		getOwner()->setOccupantValue(0);
	}
}

void VisualComponentMPW::handleMessage(ulong msgId, ulong param1, ulong param2)
{
	switch (msgId)
	{
	case msgTileChanged:
		{
			xs::Rect rc;
			OccupantTileList* potl = getOwner()->getOccupantTileList();
			if (potl == NULL)
			{
				xs::Rect rcArea;
				rcArea.right = rcArea.left = getOwner()->getTile().x;
				rcArea.bottom = rcArea.top = getOwner()->getTile().y;	// �ǵ���������ϽǸ����½�һ��
				getOwner()->setArea(rcArea);
				CopyRect(&rc, &rcArea);
			}
			else
			{
				xs::Rect rcArea;
				COccupantTileListHeader& octh = potl->getParamData();
				rcArea.left = getOwner()->getTile().x + octh.nOffAnchorX;
				rcArea.top = getOwner()->getTile().y + octh.nOffAnchorY;
                //  �����right��bottom�ļ������֣�Ϊʲô������rcArea��left��top�����м����أ�
                //  getOwner()->getArea()����ȡ��ֵ��ǰֻ�ǽ����˳�ʼ��������Ϊempty�������������
                //  rcArea�϶��Ǳ����ˣ�
                //  �����޸�Ϊʹ��rcArea��left��top�����м��㣬���۲��޸ĺ��Ч����
#if 0
				rcArea.right = getOwner()->getArea().left + octh.wWidth - 1;
				rcArea.bottom = getOwner()->getArea().top + octh.wHeight - 1;
#endif
                rcArea.right = rcArea.left + octh.wWidth - 1;
                rcArea.bottom = rcArea.top + octh.wHeight - 1;

				getOwner()->setArea(rcArea);

				int x,y;
				x = mMwdInfo->sortOffset1.x;
				y = mMwdInfo->sortOffset1.y;
				//mAniInfo->GetSortPoint1(x, y);
				rc.left = getOwner()->getTile().x + x;
				rc.top = getOwner()->getTile().y + y;

				x = mMwdInfo->sortOffset2.x;
				y = mMwdInfo->sortOffset2.y;
				//mAniInfo->GetSortPoint2(x, y);
				rc.right = getOwner()->getTile().x + x;
				rc.bottom = getOwner()->getTile().y + y;
			}


			updateWorldCoord();

			xs::Point pt;
			gGlobalClient->getSceneManager()->tile2World((xs::Point&)rc, pt);
			getOwner()->setSortLeft(pt);

			xs::Point ptRightTile (rc.right, rc.bottom);
			gGlobalClient->getSceneManager()->tile2World(ptRightTile, pt);
			getOwner()->setSortRight(pt);

			Vector3 space;
			gGlobalClient->getSceneManager()->tile2Space(getOwner()->getTile(), space);
			getOwner()->setSpace(space);

			//mUpdateOption |= updatePosition;
		}
		break;
	}

	VisualComponent::handleMessage(msgId, param1, param2);
}