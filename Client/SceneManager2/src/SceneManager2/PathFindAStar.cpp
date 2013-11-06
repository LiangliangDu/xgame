#include "StdAfx.h"
#include "PathFindAStar.h"
#include "SceneBlock.h"
CPathFindAStar::aPoint CPathFindAStar::s_aResult;
CPathFindAStar::aPoint CPathFindAStar::s_aResultAStar;

CPathFindAStar::CPathFindAStar(void):m_pPathPoint(0), m_iResultCount(0)
{
	m_aPoint[0].x = 0;
	m_aPoint[0].y = -1;
	m_aPoint[1].x = 1;
	m_aPoint[1].y = -1;
	m_aPoint[2].x = 1;
	m_aPoint[2].y = 0;
	m_aPoint[3].x = 1;
	m_aPoint[3].y = 1;
	m_aPoint[4].x = 0;
	m_aPoint[4].y = 1;
	m_aPoint[5].x = -1;
	m_aPoint[5].y = 1;
	m_aPoint[6].x = -1;
	m_aPoint[6].y = 0;
	m_aPoint[7].x = -1;
	m_aPoint[7].y = -1;
}

CPathFindAStar::~CPathFindAStar(void)
{
	delete[]m_pPathPoint;
	//delete m_pSceneMgr;
}

/* Ѱ·��ͼ��С
*/
bool CPathFindAStar::SetMapInfo(SceneMgr & nMap)
{
	delete[] m_pPathPoint;
	//m_pSceneMgr = &nMap;
	m_szMap.cx = nMap.GetSceneCoordNormal().getMatrixWidth();
	m_szMap.cy = nMap.GetSceneCoordNormal().getMatrixHeight();
	m_ulMapCount = m_szMap.cx * m_szMap.cy;
	m_pPathPoint = new stPathPoint[m_ulMapCount];
	memset(m_pPathPoint, 0, sizeof(stPathPoint) * m_ulMapCount);
	for (int y = 0; y < m_szMap.cy; y++) 
	{
		for (int x = 0; x < m_szMap.cx; x++) 
		{
			m_pPathPoint[ y * m_szMap.cx + x ].pt.x = x;
			m_pPathPoint[ y * m_szMap.cx + x ].pt.y = y;
		}
	}
	return true;
}

/** ��ʼ��·��ֵ
*/
void CPathFindAStar::New()
{
	for (int y = 0; y < m_szMap.cy; y++) 
	{
		for (int x = 0; x < m_szMap.cx; x++) 
		{
			stPathPoint& rp = m_pPathPoint[ y * m_szMap.cx + x ];
			rp.pParent = 0;
			rp.bIsObs = false;
			rp.bPass = false;
			rp.value = 0;
		}
	}
}

/** �õ������ֵ
*/
void CPathFindAStar::GetPosDirPos(long& rx, long& ry, int x, int y, int dir)
{
	rx = x + m_aPoint[dir].x;
	ry = y + m_aPoint[dir].y;
}

/** �õ��÷����ϵ�·��
*/
CPathFindAStar::stPathPoint* CPathFindAStar::GetPathPosDirPathPos(int x, int y, int dir, long& rx, long& ry)
{
	GetPosDirPos(rx, ry, x, y, dir);

	// ���������ͼ
	if (rx < 0 || rx > m_szMap.cx||  ry < 0|| ry > m_szMap.cy)
	{
		return 0;
	}
	 // ��ֹ����Խ�磻
	if ((ry * m_szMap.cx + rx) > (m_szMap.cx * m_szMap.cy))
	{
		return 0;
	}

	return &m_pPathPoint[ry * m_szMap.cx + rx];
}

/** ���㷽��
*/
int CPathFindAStar::ComputDir(const POINT& pForm, const POINT& pTo)
{
	if (pForm.x == pTo.x && pForm.y >= pTo.y)
		return 0;
	else if (pForm.x == pTo.x && pForm.y < pTo.y)
		return 4;
	else if (pForm.x < pTo.x && pForm.y == pTo.y)
		return 2;
	else if (pForm.x < pTo.x && pForm.y > pTo.y)
		return 1;
	else if (pForm.x < pTo.x && pForm.y < pTo.y)
		return 3;
	else if (pForm.x > pTo.x && pForm.y < pTo.y)
		return 5;
	else if (pForm.x > pTo.x && pForm.y == pTo.y)
		return 6;
	else
		return 7;
}

/** Ѱ·
*/
bool  CPathFindAStar::FindPath(const POINT& ptFrom, const POINT& ptTo ,bool bChangeEnd,SceneMgr & mSceneMgr,bool isNoBlcok)
{
	m_iResultCount = 0;
	if (mSceneMgr.IsAllBlock(ptTo))
	{
		ErrorLn("�Զ�Ѱ·Ŀ������X = "<<ptTo.x <<" Y = "<<ptTo.y);
		return false;
	}
	int begindir = ComputDir(ptTo, ptFrom);
	New();
	m_aSearch.clear();
	stPathPoint* pp = &m_pPathPoint[ptFrom.y * m_szMap.cx + ptFrom.x];
	pp->bPass = true;
	pp->bIsObs = false;
	pp->value = 0;
	m_aSearch.insert(stInPP(pp));
	bool bFind = false;
	int realdir = 0;
	itSearch it;
	stPathPoint* ppEx;
	//POINT pt;
	int offset = 0;
	int j = 0;
	bool bIsObs = false;
	size_t searchNum = 0;
	size_t maxSearch = 0, loopTimes = 0;
	ulong tm1max = 0, tm1 = 0, tm1Times = 0;
	POINT ppPoint, *ppExPoint;
	size_t nPP = sizeof(stPathPoint);
	while (!m_pPathPoint[ptTo.y * m_szMap.cx + ptTo.x].bPass)
	{
		if (searchNum >= m_ulMapCount)
			break;
		if (m_aSearch.empty())
			break;
		it = m_aSearch.begin();
		ppEx = (*it).ppp;
		ppExPoint = &ppEx->pt;
		for (j = 0; j < 8; j++)
		{
			if ( j % 2 == 0 )
				realdir = begindir + ( j + 1 ) / 2;
			else
				realdir = begindir - ( j + 1 ) / 2;
			if ( realdir < 0 )
				realdir += 8;
			else if ( realdir >= 8 )
				realdir -= 8;
			pp = GetPathPosDirPathPos(ppExPoint->x, ppExPoint->y, realdir, ppPoint.x, ppPoint.y);
			if (pp == NULL) 
			{
				continue;
			}
			if (!pp->bPass)
			{
				//��������赲��
				if (isNoBlcok && !mSceneMgr.IsInValidTile(ppPoint))
				{
					pp->bIsObs = false;
				}
				else
				{
					pp->bIsObs = mSceneMgr.IsAllBlock(ppPoint);
				}

				if (pp->bIsObs) 
				{
					pp->bPass = true;
					searchNum++;
				}
			}
			if (!pp->bPass && !pp->bIsObs) 
			{
				pp->bPass = true;
				searchNum++;
				pp->value = ppEx->value + (ComputDir(ppPoint, *ppExPoint)%2?3:2);
				pp->pParent = ppEx;
				m_aSearch.insert(stInPP(pp));
				if (ppPoint.x == ptTo.x && ppPoint.y == ptTo.y) 
				{
					bFind = true;
					goto Found;
				}
			} 
			else if (pp->bPass && !pp->bIsObs) 
			{
				if (ppEx->value + 1 < pp->value) 
				{
					pp->value = ppEx->value + (ComputDir(ppPoint, *ppExPoint)%2?3:2);
					pp->pParent = ppEx;
				}
			}
			loopTimes++;
		}
		m_aSearch.erase(it);
	}
	if (bFind)
	{
Found:
		stPathPoint* pFrom = &m_pPathPoint[ptFrom.y * m_szMap.cx + ptFrom.x];
		stPathPoint* pTo = &m_pPathPoint[ptTo.y * m_szMap.cx + ptTo.x];
		stPathPoint* pNext = pTo;
		//POINT t;
		int i = 0;
		while (pNext != pFrom) 
		{
			i++;
			pNext = pNext->pParent;
		}
		m_iResultCount = i+1;
		if (m_iResultCount > (int)s_aResult.size())
		{
			s_aResult.resize(m_iResultCount);
		}
		i = 0;
		pNext = pTo;
		while (pNext != pFrom) 
		{
			s_aResult[i++] = pNext->pt;
			pNext = pNext->pParent;
		}

		if(pNext == pFrom)
		{
			s_aResult[i++] = pFrom->pt;
		}
		m_iResultCount = i;
	}
	m_aSearch.clear();
	return true;
}
//<?> ��Ҫ�Ż�ȡ����������
bool CPathFindAStar::QueryResult()
{

	int n = m_iResultCount;
	s_aResultAStar.clear();
	//count = n;
	//if (lstPoint) 
	//{
	//	POINT* pSrc = &s_aResult.front();
	//	for (int i = 0; i < n; i++) 
	//	{
	//		lstPoint[i] = pSrc[n-i-1];
	//	}
	//}
	if (s_aResult.size() == 0)
	{
		return false;
	}
	POINT* pSrc = &s_aResult.front();
	for (int i = 0; i < n; i++)
	{
		POINT pt = pSrc[n-i-1];
		s_aResultAStar.push_back(pt);
	}
	//s_aResult = ptemp;
	return true;
}