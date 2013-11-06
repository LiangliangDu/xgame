#pragma once
#include "SceneMgr.h"
#include <set>
#include <map> 
#include <iostream> 


using namespace std;
class CPathFindAStar
{
public:
	/* ·����
	*/
	struct stPathPoint
	{
		POINT  pt;
		bool   bPass;
		bool   bIsObs;
		long   value;    // ����ֵ
		stPathPoint*  pParent;
	};

	/* ����ֵ�Ƚ�
	*/
	struct stInPP
	{
		stPathPoint*	ppp;
		stInPP(stPathPoint* p) : ppp(p) {}
		bool operator < (const stInPP& pp) const
		{
			return ppp->value < pp.ppp->value;
		}
	};

	/* 
	*/ 
	typedef std::multiset<stInPP> aSearch;

	/* 
	*/
	typedef aSearch::iterator itSearch;

	/* 
	*/
	typedef std::vector<POINT> aPoint;

	/* 
	*/
	typedef aPoint::iterator itPoint;
public:

	/* Ѱ·��ͼ��С
	*/
	bool SetMapInfo(SceneMgr& nMap);

	/** ��ʼ��·��ֵ
	*/
	void New();

	/** �õ������ֵ
	*/
	void GetPosDirPos(long& rx, long& ry, int x, int y, int dir);

	/** �õ��÷����ϵ�·��
	*/
	stPathPoint* GetPathPosDirPathPos(int x, int y, int dir, long& rx, long& ry);

	/** Ѱ·
	*/
	bool  FindPath(const POINT& ptFrom, const POINT& ptTo ,bool bChangeEnd,SceneMgr & mSceneMgr,bool isNoBlcok = false);

	/** ���㷽��
	*/
	int  ComputDir(const POINT& pForm, const POINT& pTo);

	/** ��Ҫ�Ż�ȡ����������
	*/
	bool QueryResult();
	/* 
	*/
	CPathFindAStar(void);

	/* 
	*/
	~CPathFindAStar(void);

	/* ���ؽ��·��ֵ
	*/
	static aPoint		s_aResult;

	static aPoint		s_aResultAStar;

protected:
	/* 
	*/
	aSearch             m_aSearch;

	//SceneMgr*           m_pSceneMgr;

	/*��ͼ��Ϣ
	*/
	Size		        m_szMap;
	/* 
	*/
	ulong				m_ulMapCount;

	/* ·��
	*/
	stPathPoint*		m_pPathPoint;

	/* ���ؽ��·��ֵ
	*/
	//static aPoint		s_aResult;

	/* ��ʶ���
	*/
	int					m_iResultCount;

	/* 
	*/
	POINT               m_aPoint[8];
};
