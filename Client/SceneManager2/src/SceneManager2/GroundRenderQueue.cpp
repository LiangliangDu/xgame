#include "StdAfx.h"
#include "GroundRenderQueue.h"
#include "GroundTile.h"

void GroundRenderQueue::reset()
{
	m_vTiles.clear();
}

void GroundRenderQueue::addTile(GroundTile*	pTile)
{
	m_vTiles.push_back(pTile);
}

bool GroundRenderQueue::RenderDistance(int nMapWidth, int nMapHeight, int nViewWidth, int nViewHeight, int nViewTopX,
                                       int nViewTopY, ITexture* pDistanceTexture)
{
    if (pDistanceTexture == NULL)
    {
        return FALSE;
    }

    IRenderSystem *pRenderSystem = getRenderEngine()->getRenderSystem();
    if (pRenderSystem == NULL)
    {
        ASSERT(FALSE);
        return false;
    }

	if( 0 ==m_pDistantVB || 0 == m_pDistantTexVB) 
	{
		ASSERT(FALSE);
		return false;
	}

	pRenderSystem->bindCurrentShaderProgram(m_pShaderPrograms[0],true);

    //  ����Զ��ͼ��ƫ�Ʊ��������ƫ�Ʊ����������㣬L(a, b)��ʾa��b֮��ľ��룺
    //
    /*     float fx = (float)(256 * 11 - m_nViewWidth) / (float)(m_nMapWidth - m_nViewWidth);
    float fy = (float)(256 * 11 - m_nViewHeight) / (float)(m_nMapHeight - m_nViewHeight);
    float fDistanceLeft = (nViewTopX * fx) / (256 * 11);
    float fDistanceTop = (nViewTopY * fy) / (256 * 11);
    float fDistanceRigh = (256 * 11 - (m_nMapWidth - nViewTopX - m_nViewWidth) * fx) / (256 * 11);
    float fDistanceBottom = (256 * 11 - (m_nMapHeight - nViewTopY - m_nViewHeight) * fy) / (256 * 11);
    VERIFY(m_groundRenderQueue.RenderDistance(fDistanceLeft, fDistanceTop, fDistanceRigh, fDistanceBottom));*/

    //  ��ȡԶ����ͼ�Ĵ�С��
    uint unTextureWidth = pDistanceTexture->width();
    uint unTextureHeight = pDistanceTexture->height();

    //  ����m_pVBTexcoord��ֵ������������ɺ���ʵ�ֵģ�
    //  ���ȸ�����ͼ����Ļ�Ĵ�С�����X�����Y�����ϵ������ʹ�ø�ϵ�����ݵ�ͼǰ��λ�ã���ͼ��С����Ļ��С�����
    //  m_pVBTexcoord��ֵ��
    float fXCoefficient = (float)(unTextureWidth - nViewWidth) / (float)(unTextureWidth);
    float fYCoefficient = (float)(unTextureHeight - nViewHeight) / (float)(unTextureHeight);
    float fDistanceLeft =(float) nViewTopX / (float)(nMapWidth - nViewWidth) * fXCoefficient ;
    float fDistanceTop = (float)nViewTopY / (float)(nMapHeight - nViewHeight) * fYCoefficient;
    float fDistanceRigh = fDistanceLeft + (float)nViewWidth / (float)(unTextureWidth);
    float fDistanceBottom = fDistanceTop + (float)nViewHeight / (float)(unTextureHeight);

    //  ������ʼ�㣻
	float texcoord[6][2] = 
	{
		{ fDistanceLeft, fDistanceTop },
		{fDistanceLeft, fDistanceBottom},
		{fDistanceRigh, fDistanceTop},
		{fDistanceRigh, fDistanceTop},
		{fDistanceRigh, fDistanceBottom},
		{fDistanceLeft, fDistanceBottom},
	};
	m_pDistantTexVB->writeData(0, sizeof(texcoord),texcoord,true);
	pRenderSystem->setTexcoordVertexBuffer(0, m_pDistantTexVB);

    //  ������������Ĵ�С������������Ļ��Сһ�£�
	float vertices[6][3] = 
	{
		{0,0,0},
		{0,nViewHeight,0},
		{nViewWidth,0,0},
		{nViewWidth,0,0},
		{nViewWidth,nViewHeight,0},
		{0,nViewHeight,0},
	};
	m_pDistantVB->writeData(0, sizeof(vertices), vertices,true);
    pRenderSystem->setVertexVertexBuffer(m_pDistantVB);

    //  ���ƴ��������ǽ�Զ����ͼ��Ϊ0����ͼ���õģ���Ϊ�����render()�����н��еĶ�tile�Ļ����У�û��������ͼ
    //  ��tile�ǲ�����л��Ƶģ������˻��Ƶ�tileҲ�ܱ�֤alphaͨ������Ч�ԣ����Զ��������ʾ������
    //  ������setWorldMatrix()�Ĵ�������Ϊ����ʵ��ʱ��������ƶ��������
    pRenderSystem->setTexture(0, pDistanceTexture);	
    //pRenderSystem->setWorldMatrix(mtxWorld * pTile->getWorldMatrix());
   // pRenderSystem->drawPrimitive(PT_QUADS, 0, 4);
	pRenderSystem->drawPrimitive(PT_TRIANGLES, 0, 6);

    pRenderSystem->setTexture(0, 0);	
    pRenderSystem->setTexcoordVertexBuffer(0, 0);
    pRenderSystem->setVertexVertexBuffer(0);

    return true;
}

void GroundRenderQueue::renderTileLine(int nViewTopX, int nViewTopY)
{
	IRenderSystem *pRenderSystem = getRenderEngine()->getRenderSystem();
	Matrix4 mtxWorld = pRenderSystem->getWorldMatrix();
	pRenderSystem->setVertexVertexBuffer(m_pTileLineVB);
	TileList::iterator begin = m_vTiles.begin();
	TileList::iterator end = m_vTiles.end();
	while(begin != end)
	{
		GroundTile *pTile = (*begin);
        if (pTile == NULL)
        {
            ASSERT(false);
            continue;
        }

        //  ����64 * 64�ľ���Ϊ��λ�����Ʊ߿��ߣ�
        //ColorValue c = pRenderSystem->getColor();
        //pRenderSystem->setColor(ColorValue(0.0f, 1.0f, 1.0f));
		pRenderSystem->setDiffuseVertexBuffer(m_pTileLineColorVB1);
        for (int nSubTileIndexX = 0; nSubTileIndexX < 4; nSubTileIndexX++)
        {
            for (int nSubTileIndexY = 0; nSubTileIndexY < 4; nSubTileIndexY++)
            {
                Matrix4 MatrixWorld;
                MatrixWorld.makeTrans((pTile->getX() * 256) + (nSubTileIndexX * 64) - nViewTopX,
                    (pTile->getY() * 256) + (nSubTileIndexY * 64) - nViewTopY,
                    0);
                pRenderSystem->setWorldMatrix(MatrixWorld);
                pRenderSystem->drawPrimitive(PT_LINE_STRIP,0,5);
            }
        }

        //  �ٻ���Tile�ı߿��ߣ�
		//pRenderSystem->setColor(ColorValue(1.0f,1.0f,0.0f));
		pRenderSystem->setDiffuseVertexBuffer(m_pTileLineColorVB2);
		pRenderSystem->setWorldMatrix(pTile->getWorldMatrix());
		pRenderSystem->drawPrimitive(PT_LINE_STRIP,0,5);

		if(m_pFont)
		{
			char str[256];
			sprintf(str,"%d,%d",pTile->getY(),pTile->getX());
			// ��ɫ
			m_pFont->render2d(0,0,0,ColorValue(1.0f,1.0f,0.f),str);
		}
		//pRenderSystem->setColor(c);

		++begin;
	}
	pRenderSystem->setDiffuseVertexBuffer(0);
	pRenderSystem->setVertexVertexBuffer(0);
	pRenderSystem->setWorldMatrix(mtxWorld);
}

void GroundRenderQueue::render()
{
	IRenderSystem *pRenderSystem = getRenderEngine()->getRenderSystem();
	Matrix4 mtxWorld = pRenderSystem->getWorldMatrix();

    if(pRenderSystem->getCapabilities()->hasCapability(RSC_HIGHLEVEL_SHADER))	
	{
		pRenderSystem->setTexcoordVertexBuffer(0,m_pVBTexcoord);
		pRenderSystem->setVertexVertexBuffer(m_pVB);
		xs::CullingMode cm = pRenderSystem->getCullingMode();
		bool li = pRenderSystem->isLightingEnabled();
		pRenderSystem->setLightingEnabled(false);
		pRenderSystem->setCullingMode(CULL_NONE);
		TileList::iterator begin = m_vTiles.begin();
		TileList::iterator end = m_vTiles.end();
		while(begin != end)
		{
			GroundTile *pTile = (*begin);
			if(pTile->m_textureLayerNum == 0 || !pTile->isLoaded())
			{
				++begin;
				continue;
			}
			pRenderSystem->setTexture(0,pTile->getTexture(0));
			pRenderSystem->setTexture(1,pTile->getShaderMapTexture());
			for(uint i = 1;i < pTile->m_textureLayerNum;i++)
			{		
				pRenderSystem->setTexture(i + 1,pTile->getTexture(i));	
			}
			
			IHighLevelShaderProgram* pProgram = static_cast<IHighLevelShaderProgram*>(m_pShaderPrograms[pTile->m_textureLayerNum - 1]);
			pRenderSystem->bindCurrentShaderProgram(pProgram);//pProgram->bind();
			pProgram->bindSampler( pTile->m_textureLayerNum);
			
			pRenderSystem->setWorldMatrix(mtxWorld * pTile->getWorldMatrix());
			pRenderSystem->drawPrimitive(PT_TRIANGLES,0,6);
			//pProgram->unbind();			
			for(uint i = 0;i < pTile->m_textureLayerNum + 1;i++)
			{		
				pRenderSystem->setTexture(i,0);				
			}
			++begin;
		}
		pRenderSystem->bindCurrentShaderProgram(0);
		pRenderSystem->setTexcoordVertexBuffer(0,0);
		pRenderSystem->setVertexVertexBuffer(0);
		pRenderSystem->setCullingMode(cm);
		pRenderSystem->setLightingEnabled(li);
	}			
	else if(pRenderSystem->getCapabilities()->hasCapability(RSC_LOWLEVEL_SHADER))				
	{
		pRenderSystem->setTexcoordVertexBuffer(0,m_pVBTexcoord);
		pRenderSystem->setVertexVertexBuffer(m_pVB);
		TileList::iterator begin = m_vTiles.begin();
		TileList::iterator end = m_vTiles.end();
		while(begin != end)
		{
			GroundTile *pTile = (*begin);
			if(pTile->m_textureLayerNum == 0 || !pTile->isLoaded())
			{
				++begin;
				continue;
			}

            pRenderSystem->setTexture(0,pTile->getTexture(0));
			pRenderSystem->setTexture(1,pTile->getShaderMapTexture());
			for(uint i = 1;i < pTile->m_textureLayerNum;i++)
			{
				pRenderSystem->setTexture(i + 1,pTile->getTexture(i));	
			}		

			IShaderProgram *pProgram = m_pShaderPrograms[pTile->m_textureLayerNum - 1];	
			pProgram->bind();
			pRenderSystem->setWorldMatrix(mtxWorld * pTile->getWorldMatrix());
			pRenderSystem->drawPrimitive(PT_TRIANGLES,0,6);
			pProgram->unbind();			
			for(uint i = 0;i < pTile->m_textureLayerNum + 1;i++)
			{		
				pRenderSystem->setTexture(i,0);
			}

			++begin;
		}
		pRenderSystem->setTexcoordVertexBuffer(0,0);
		pRenderSystem->setVertexVertexBuffer(0);
	}			
	else
	{
		pRenderSystem->setTexcoordVertexBuffer(0,m_pVBTexcoord);
		pRenderSystem->setTexcoordVertexBuffer(1,m_pVBTexcoord);
		pRenderSystem->setVertexVertexBuffer(m_pVB);
		SceneBlendFactor src,dst;
		pRenderSystem->getSceneBlending(src,dst);
		pRenderSystem->setSceneBlending(SBF_SOURCE_ALPHA,SBF_ONE_MINUS_SOURCE_ALPHA);
		TileList::iterator begin = m_vTiles.begin();
		TileList::iterator end = m_vTiles.end();
		while(begin != end)
		{
			GroundTile *pTile = (*begin);

			if(pTile->m_textureLayerNum == 0 || !pTile->isLoaded())
			{
				++begin;
				continue;
			}
			pRenderSystem->setTexture(0,pTile->getTexture(0));	
			pRenderSystem->setTexture(1,0);
			pRenderSystem->setWorldMatrix(pTile->getWorldMatrix());
			pRenderSystem->drawPrimitive(PT_TRIANGLES,0,6);

			for (uint i = 0;i < pTile->m_textureLayerNum - 1;i++)
			{
				pRenderSystem->setTexture(0,pTile->getTexture(i + 1));
				pRenderSystem->setTexture(1,pTile->getAlphaMapTexture(i));
				pRenderSystem->drawPrimitive(PT_QUADS,0,4);
			}

			++begin;
		}
		pRenderSystem->setSceneBlending(src,dst);
		pRenderSystem->setTexcoordVertexBuffer(0,0);
		pRenderSystem->setTexcoordVertexBuffer(1,0);
		pRenderSystem->setVertexVertexBuffer(0);
		pRenderSystem->setTexture(0,0);
		pRenderSystem->setTexture(1,0);
	}
	pRenderSystem->setWorldMatrix(mtxWorld);
}

void GroundRenderQueue::initialize()
{
	IRenderSystem *pRenderSystem = getRenderEngine()->getRenderSystem();
	IShaderProgramManager * pShaderProgamMgr = pRenderSystem->getShaderProgramManager();

	if(pRenderSystem->getCapabilities()->hasCapability(RSC_HIGHLEVEL_SHADER))
	{
		if( pRenderSystem->getRenderSystemType() == RS_D3D9 )
		{
			for(int i = 0;i < 4;i++)
			{
				char str[256];
				sprintf(str,"Shader\\D3D9\\terrain%d.hlsl",i + 1);
				m_pShaderPrograms[i] = pShaderProgamMgr->createShaderProgram(SPT_HIGHLEVEL);
				m_pShaderPrograms[i]->addShaderFromFile(ST_FRAGMENT_PROGRAM,str);
				m_pShaderPrograms[i]->link();
			}
		}
		else if(pRenderSystem->getRenderSystemType() == RS_OPENGLES2)
		{
			for(int i = 0;i < 4;i++)
			{
				char str[256];
				sprintf(str,"Shader/OGLES2/terrain%d.frag",i + 1);
				m_pShaderPrograms[i] = pShaderProgamMgr->createShaderProgram(SPT_HIGHLEVEL);
				m_pShaderPrograms[i]->addShaderFromFile(ST_VERTEX_PROGRAM,"Shader/OGLES2/terrain.vs");
				m_pShaderPrograms[i]->addShaderFromFile(ST_FRAGMENT_PROGRAM,str);
				m_pShaderPrograms[i]->link();
			}
		}
		else
		{
			for(int i = 0;i < 4;i++)
			{
				char str[256];
				sprintf(str,"Shader\\OGL\\terrain%d.frag",i + 1);
				m_pShaderPrograms[i] = pShaderProgamMgr->createShaderProgram(SPT_HIGHLEVEL);
				m_pShaderPrograms[i]->addShaderFromFile(ST_FRAGMENT_PROGRAM, str);
				m_pShaderPrograms[i]->link();
			}
		}

	}
	else if(pRenderSystem->getCapabilities()->hasCapability(RSC_LOWLEVEL_SHADER))
	{
		if( pRenderSystem->getRenderSystemType() == RS_D3D9 )
		{
			for(int i = 0;i < 4;i++)
			{
				char str[256];
				sprintf(str,"Shader\\D3D9\\terrain%d.asm",i + 1);
				m_pShaderPrograms[i] = pShaderProgamMgr->createShaderProgram(SPT_LOWLEVEL);
				m_pShaderPrograms[i]->addShaderFromFile(ST_FRAGMENT_PROGRAM, str);
				m_pShaderPrograms[i]->link();
			}	
		}
		else
		{
			for(int i = 0;i < 4;i++)
			{
				char str[256];
				sprintf(str,"Shader\\OGL\\terrain%d.fx",i + 1);
				m_pShaderPrograms[i] = pShaderProgamMgr->createShaderProgram(SPT_LOWLEVEL);
				m_pShaderPrograms[i]->addShaderFromFile(ST_FRAGMENT_PROGRAM, str);
				m_pShaderPrograms[i]->link();
			}
		}
	}

	Assert( 0 == m_pVB);
	m_pVB = pRenderSystem->getBufferManager()->createVertexBuffer(12,6,BU_STATIC_WRITE_ONLY);
	if(m_pVB)
	{
		float vectices[6][3] = 
		{
			{0,		0,		0,},
			{0,		256,	0,},
			{256,	0,		0,},
			{256,	0,		0,},
			{256,	256,	0,},
			{0,		256,	0,},
		};
		m_pVB->writeData(0, sizeof(vectices), vectices, true);
	}

	Assert( 0 == m_pVBTexcoord);
	m_pVBTexcoord = pRenderSystem->getBufferManager()->createVertexBuffer(8,6,BU_STATIC_WRITE_ONLY);
	if(m_pVBTexcoord)
	{
		float vectices[6][2] = 
		{
			{0,0}, {0,1}, {1,0},
			{1,0}, {1,1}, {0,1},
		};
		m_pVBTexcoord->writeData(0, sizeof(vectices), vectices, true);
	}

	Assert( 0 == m_pTileLineVB);
	m_pTileLineVB = pRenderSystem->getBufferManager()->createVertexBuffer(12,5,BU_STATIC_WRITE_ONLY);
	if(m_pTileLineVB)
	{
		float vertices[5][3] =
		{
			{0,0,0},
			{0,256,0},
			{256,256,0},
			{256,0,0},
			{0,0,0},
		};
		m_pTileLineVB->writeData(0,sizeof(vertices), vertices, true);
	}

	Assert( 0 == m_pTileLineColorVB1);
	m_pTileLineColorVB1 = pRenderSystem->getBufferManager()->createVertexBuffer(4,5,BU_STATIC_WRITE_ONLY);
	if( m_pTileLineColorVB1)
	{
		uint cyan = xs::ColorValue(0,1,1,1).getAsARGB();
		uint cyanArray[5] = { cyan, cyan, cyan, cyan, cyan,};
		m_pTileLineColorVB1->writeData(0, sizeof(cyanArray), cyanArray, true);
	}

	Assert( 0 == m_pTileLineColorVB2);
	m_pTileLineColorVB2 = pRenderSystem->getBufferManager()->createVertexBuffer(4,5,BU_STATIC_WRITE_ONLY);
	if(m_pTileLineColorVB2)
	{
		uint yellow = xs::ColorValue(1,1,0,1).getAsARGB();
		uint yellowArray[5] = {yellow,yellow,yellow,yellow,yellow};
		m_pTileLineColorVB2->writeData(0, sizeof(yellowArray), yellowArray, true);
	}

	Assert(m_pDistantVB == 0);
	Assert(m_pDistantTexVB == 0);
	//Assert(m_pFont == 0);
	m_pDistantVB = pRenderSystem->getBufferManager()->createVertexBuffer(12, 6, BU_DYNAMIC_WRITE_ONLY_DISCARDABLE);
	m_pDistantTexVB = pRenderSystem->getBufferManager()->createVertexBuffer(8, 6, BU_DYNAMIC_WRITE_ONLY_DISCARDABLE);
	m_pFont = getRenderEngine()->getFontManager()->getFontByName("Default");
}

void GroundRenderQueue::finalize()
{
	IRenderSystem *pRenderSystem = getRenderEngine()->getRenderSystem();
	for(int i = 0;i < 4;i++)
	{
		if(m_pShaderPrograms[i])
		{
			safeRelease(m_pShaderPrograms[i]);
		}
	}
	safeRelease(m_pVBTexcoord);
	safeRelease(m_pVB);
	//safeRelease(m_pFont);
	safeRelease(m_pDistantVB);
	safeRelease(m_pDistantTexVB);
	safeRelease(m_pTileLineVB);
	safeRelease(m_pTileLineColorVB1);
	safeRelease(m_pTileLineColorVB2);
}
