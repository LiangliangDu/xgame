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
		xs::Point  pt;
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
	typedef std::vector<xs::Point> aPoint;

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
	bool  FindPath(const xs::Point& ptFrom, const xs::Point& ptTo ,bool bChangeEnd,SceneMgr & mSceneMgr,bool isNoBlcok = false);

	/** ���㷽��
	*/
	int  ComputDir(const xs::Point& pForm, const xs::Point& pTo);

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
	SIZE		        m_szMap;
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
	xs::Point               m_aPoint[8];
};
