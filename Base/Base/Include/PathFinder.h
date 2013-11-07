/*******************************************************************
** �ļ���:	PathFinder.h
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	2008/04/17
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __PATH_FINDER_H__
#define __PATH_FINDER_H__

#include <assert.h>
#include <functional>
#include <vector>

/**
@name : ·������ģ��
@brief: ����:
			�ṩһ�ݵ�ͼ����,������ά���˵�ͼ������Tile����Ϣ��������ЩTile�ǿ�ͨ�еģ���ЩTile���赲�ġ�
			Ȼ���������յ�����,��ģ�鸺����������㵽�յ��·����
		�㷨:
			����·����õ��㷨��A*�㷨,���ǳ������ܿ���,�������һ�ָ��򵥵ķ���ʵ��,
			�÷����Ļ���˼·��,�������ǳ���ֱ�����յ�ƽ����������赲��Tileʱ�����赲Tile��ת��ֱ�����»ص�ֱ·��
			������������������ǿ����ҵ�����㵽�յ����Ч·������Ȼ����·��������̵�.
			���һ������������·�������Ż���ʹ֮����������Ȼ

		Function:
			Provide a map data, it maintains a table for the information of all tiles in it.
			The most important information is which tiles is passable and others is blocked.
			Then,Give the coordinate of the start-point and the coordinate of the end-point,
			This module can find the path from start-point to end-point and around tiles which is blocked.
		Algorithm:
			To implement this function, usually people used an algorithm called A STAR(A*).
			But now,for some performance reason,I will implement it with a more clever method. 
			In our method,I always try to approach to the end-point straightly,I call it straightway.
			And when meet blocked tiles, I around it try to find sideway until it come back to the straightway.
			After this process,the path from start-point to end-point can always be found,though,it not a shortest path.
			Finally, I optimize the snaky path that i found and let it seem more natural.
*/


// ��·ѡ��
enum
{
	SEARCH_OPTION_EMPTY      =0x00   , // ������·
	SEARCH_OPTION_OPTIMIZE   =0x01   , // �Ż�·��
	SEARCH_OPTION_NEAREST    =0x02   , // ������������յ����ƶ�������ĵ�
	SEARCH_OPTION_STRAIGHTWAY=0x04   , // ����ֱ·�ж�
};

//////////////////////////////////////////////////////////////////////////
/**
@name : ��·ģ��
@brief: ����·ģ����ڵ�ͼTileʵ��,����һ���жϵ�ͼTile�Ƿ��赲�ĺ���
        ʹ�÷���:
		class CMap
		{
		public:
		    bool IsBlock(POINT pt);   // ����ʵ��IsBlock����,������ֲ���IsBlock������SetMapInfoʱ�޸�
		....
		};

		CMap m_Map;
		PathFinder<CMap>  m_PathFinder;
		m_PathFinder.SetMapInfo(m_Map.GetWidth(),m_Map.GetHeight(),&m_Map,mem_fun1(&CMap::IsBlock));
		POINT * pPath = 0;
		int nPathLen  = 0;
		if ( m_PathFinder.FindPath(ptStart,ptEnd,pPath,nPathLen) )
*/
//////////////////////////////////////////////////////////////////////////

template
< 
	class    _Map,                                                  // ��ͼ 
	typename _BlockTestFunc = std::mem_fun1_t<bool,_Map,POINT> ,    // �赲�жϺ�������,��������bool IsBlock(POINT pt)
	int      MAX_PATH_LEN   = 1024 ,                                // ���·������
	int      MAX_SEARCH_AREA= 256                                   // ����������
>
class PathFinder
{
public:
	struct TILE_TAG
	{
		TILE_TAG  *      pParent;		// ��һ��Tileָ��
		unsigned short   nFindID;       // ��ǰ��·�Ǻ�,ÿ����·�Զ���1,�������Ա���ÿ�ζ���һ���ڴ�,����·Ƶ��ʱÿ�ζ�memsetһ���Ƿǳ���Ч������
		unsigned char    nMoveDir;      // �����õ�ʱ�ķ���
		bool             bAround;       // ��ʶ��ת��·��,���·�ߺ�����Ҫ�����Ż�
	};

	enum
	{
		DIR_EAST    =0 ,  // ������ : ��  (angle:0)
		DIR_EAST_NORTH ,  // ������ : ����(angle:45)
		DIR_NORTH      ,  // ������ : ��  (angle:90)
		DIR_WEST_NORTH ,  // ������ : ����(angle:135)
		DIR_WEST       ,  // ������ : ��  (angle:180)
		DIR_WEST_SOUTH ,  // ������ : ����(angle:225)
		DIR_SOUTH      ,  // ������ : ��  (angle:270)
		DIR_EAST_SOUTH ,  // ������ : ����(angle:315)
	};

	enum
	{
		CORNER_LEFT_TOP = 0,           // ���Ͻǹյ�
		CORNER_LEFT_BOTTOM ,           // ���½ǹյ�
		CORNER_RIGHT_TOP   ,           // ���Ͻǹյ�
		CORNER_RIGHT_BOTTOM,           // ���½ǹյ�
		CORNER_NUM         ,           // �յ����

		INVALID_CORNER_FLAG=0xFFFFFFFF,// ��Ч�յ��־
	};

	enum
	{
		TURN_CW    = 0,   // ˳ʱ����ת
		TURN_CCW      ,   // ��ʱ����ת
	};

	/**
	@name           : ���õ�ͼ��Ϣ 
	@brief          : ����FindPath֮ǰ�����õ�ͼ��Ϣ,�ú��������ظ�����,���Կ����ڶ����ͼ������·��
	@param nMapWidth: ��ͼ���
	@param nMapHeigh: ��ͼ�߶�
	@param pMap     : ��ͼ����ָ��
	@param isBlock  : �жϵر��Ƿ��赲�ĺ���,�����ͼ�����ж��赲�ĺ�����IsBlock��ò������ô�
	@return         : 
	*/
	bool SetMapInfo(unsigned long nMapWidth,unsigned long nMapHeight,_Map * pMap,_BlockTestFunc isBlock=std::mem_fun(&_Map::IsBlock));

	/**
	@name			: ����·��
	@brief			: 
	@param ptStart  : �������
	@param ptEnd    : �յ�����
	@param pPathRet : ���ص�·����
	@param nPathLen : ����·������
	@param nOption  : ��·ѡ��,�Ƿ��Ż�·��
	@param nMaxStep : ��������Ĳ���,���̫Զ�ͷ��� (����������������� 1.��ʱ��ֻ��Ҫ�ѳ����������·,����һ����Ҫ����Ŀ��� 2.Ĭ����Ϊ1024,��ֹ������ѭ��)
	@return         : ������·�Ƿ�ɹ� 
	*/
	bool FindPath(const POINT & ptStart,const POINT & ptEnd,POINT *& pPath,int & nPathLen,int nOption=SEARCH_OPTION_OPTIMIZE,int nMaxStep=MAX_PATH_LEN);

	// ���캯��
	PathFinder() : m_pMap(0),m_pNearestTile(0),m_nFind(0),m_BlockFunc(0),m_nSearchOption(0),m_nMaxStep(MAX_PATH_LEN),m_nStepCount(0)
	{
		m_TileTags = new TILE_TAG[MAX_SEARCH_AREA*MAX_SEARCH_AREA];
		memset(m_TileTags,0,sizeof(TILE_TAG)*MAX_SEARCH_AREA*MAX_SEARCH_AREA);
	}

	// �͹�����
	virtual ~PathFinder()
	{
		if ( m_TileTags ) { delete []m_TileTags;m_TileTags = 0;}
	}

protected:
	//////////////////////////////////////////////////////////////////////////
	// ��������·���ĺ���
	bool FindPathCore(const POINT & ptStart,const POINT & ptEnd);

	// ��ֱ·����Ŀ���
	bool Approach(const POINT & ptStart,const POINT & ptEnd);

	// ��ĳ�㿪ʼ��·
	bool Around(const POINT & ptTile,int nMoveDir,int nTurnDir,const POINT & ptStart,const POINT & ptEnd);

	// ������������ȥ�ĵ㳢��ֱ��������
	bool ConnectDirect(const POINT & ptStart,const POINT & ptEnd);

	// ��ȡTile��Ϣ
	inline TILE_TAG * GetTileTag(const POINT & ptTile);

	// ��TAG��ָ����Tile������
	inline void TileToPoint(TILE_TAG * pTag,POINT &ptTile);

	// �ж�ĳ��Tile�Ƿ񱻷��ʹ�
	inline bool IsTileVisited(TILE_TAG * pTag,int nDir);

	// ���ĳ��Tile�Ѿ������ʹ�
	inline void MarkTileVisited(TILE_TAG * pTag,int nDir,TILE_TAG * pParent);

	// ȡ��ĳ��������һ���������
	inline void MoveNext(const POINT & ptTile,int dir,POINT & ptNext);

	// ȡ��������֮��ķ��� 
	inline int GetDir(const POINT & ptCur,const POINT & ptNext);

	// ��ת����
	inline int  TurnDir(int nMoveDir,int nTurnDir);

	// ��¼�յ�
	inline void RecordCorner(const POINT & ptTile);

	// �������йյ�
	inline void ConnectCorners(const POINT & ptStart);

	// �Ƿ��������ϵĵ�
	inline bool IsOnStraightWay(const POINT & ptTile,const POINT & ptStart,const POINT & ptEnd);

	// �Ƿ����ֱ�ӱƽ�
	bool IsCanApproach(const POINT & ptTile,const POINT & ptEnd);

	// ������·��Tile,��˷����·��
	int BuildPath(POINT * pPathBuffer,int nBufSize,bool nReverse);

protected:
	////////////////////////////////////////////////////////////////////////
	

    

	struct AROUND_POINT
	{
		POINT            ptTile;
		int              nMoveDir;
		int              nTurnDir;
	};

	TILE_TAG       *     m_TileTags;								  // ������¼��·�������߹���Tile����Ϣ 
	POINT				 m_PathTemp[4][MAX_PATH_LEN];                 // �����洢���ص�·��
	POINT                m_ptStart;                                   // ������·����ʼ��
	POINT                m_ptEnd;                                     // ������·�Ľ�����
	TILE_TAG  *          m_pNearestTile;                              // ��ӽ��ĵ�s
	unsigned long        m_nMapWidth;                                 // ��ͼ���
	unsigned long        m_nMapHeight;                                // ��ͼ�߶�

	_Map      *          m_pMap;                                      // ��ͼָ��
	_BlockTestFunc       m_BlockFunc;                                 // �赲�жϺ���
	unsigned short       m_nFind;                                     // ��ǰ��·�ı�ʾ
	int                  m_nSearchOption;                             // ��·ѡ��
	int                  m_nMaxStep;                                  // �����·����
	int                  m_nStepCount;                                // ��ǰ�����Ĳ���

	std::vector<AROUND_POINT>   m_AroundQueue;                        // ��ת����
	POINT                       m_Corners[CORNER_NUM];                // �յ��б�
	DWORD                       m_nCornerFlag[CORNER_NUM];            // �յ��־
};


// ��ֱ·����Ŀ���
#define  TEMPLATE_DECLARE		template<class _Map,typename _BlockTestFunc,int MAX_PATH_LEN,int MAX_SEARCH_AREA>
#define  PATH_FINDER_DECLARE	PathFinder<_Map,_BlockTestFunc,MAX_PATH_LEN,MAX_SEARCH_AREA>

//////////////////////////////////////////////////////////////////////////
/**
@name           : ���õ�ͼ��Ϣ 
@brief          : ����FindPath֮ǰ�����õ�ͼ��Ϣ,�ú��������ظ�����,���Կ����ڶ����ͼ������·��
@param nMapWidth: ��ͼ���
@param nMapHeigh: ��ͼ�߶�
@param pMap     : ��ͼ����ָ��
@param isBlock  : �жϵر��Ƿ��赲�ĺ���,�����ͼ�����ж��赲�ĺ�����IsBlock��ò������ô�
@return         : 
*/
//////////////////////////////////////////////////////////////////////////
TEMPLATE_DECLARE
bool PATH_FINDER_DECLARE::SetMapInfo(unsigned long nMapWidth,unsigned long nMapHeight,_Map * pMap,_BlockTestFunc isBlock)
{
	m_nMapWidth = nMapWidth;
	m_nMapHeight= nMapHeight;

	m_pMap = pMap;
	m_BlockFunc = isBlock;
	
	return true;
}

//////////////////////////////////////////////////////////////////////////
/**
@name			: ����·��
@brief			: 
@param ptStart  : �������
@param ptEnd    : �յ�����
@param pPathRet : ���ص�·����
@param nPathLen : ����·������
@param nOption  : ��·ѡ��,�Ƿ��Ż�·��
@return         : ������·�Ƿ�ɹ� 
*/
//////////////////////////////////////////////////////////////////////////
TEMPLATE_DECLARE
bool PATH_FINDER_DECLARE::FindPath(const POINT & ptStart,const POINT & ptEnd,POINT *& pPath,int & nPathLen,int nOption,int nMaxStep)
{
	pPath = 0;
	nPathLen = 0;

	m_nSearchOption = nOption;
	m_nMaxStep      = nMaxStep;

	int  nPathLenTemp[4];
    POINT * pPathTemp[4];

	int  nShortest  = -1;
	bool bFindMore  = true;
	int  dx = abs(ptEnd.x-ptStart.x);
	int  dy = abs(ptEnd.y-ptStart.y);
    int  nPathLenLimit = min(dx,dy) + abs(dx-dy)+5;

	//////////////////////////////////////////////////////////////////////////
	// ����������
	if ( bFindMore && FindPathCore(ptStart,ptEnd) )
	{
		if (( m_nStepCount>nPathLenLimit) &&( nOption & SEARCH_OPTION_OPTIMIZE )) {ConnectCorners(ptStart);}

		nPathLenTemp[0] = BuildPath(m_PathTemp[0],MAX_PATH_LEN,true);
		pPathTemp[0]    = &(m_PathTemp[0][MAX_PATH_LEN-nPathLenTemp[0]]);
		
		if ( nShortest<0 || nPathLenTemp[0]<nPathLenTemp[nShortest] )
		{
			nShortest = 0;
			bFindMore = (nPathLenTemp[0] > nPathLenLimit) && ( nOption & SEARCH_OPTION_OPTIMIZE );
			m_nMaxStep      = nMaxStep;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// ������������ʱ,��������һ��,Ȼ��ѽ����ת
	if ( bFindMore && FindPathCore(ptEnd,ptStart) )
	{
		// ��Ϊ�Լ�������ռλ�飬���Կ���·����ʼ�����Լ�
		TILE_TAG * pTag = GetTileTag(ptStart);
		if ( m_pNearestTile!=0 && m_pNearestTile!=pTag)
		{
			pTag->pParent = m_pNearestTile;
			m_pNearestTile= pTag;
		}

		if (( m_nStepCount>nPathLenLimit) &&( nOption & SEARCH_OPTION_OPTIMIZE )) {ConnectCorners(ptEnd);}
		nPathLenTemp[1] = BuildPath(m_PathTemp[1],MAX_PATH_LEN,false);
		pPathTemp[1]    = m_PathTemp[1];
		if ( nShortest<0 || nPathLenTemp[1]<nPathLenTemp[nShortest] )
		{
			nShortest = 1;
			bFindMore = (nPathLenTemp[1] > nPathLenLimit) && ( nOption & SEARCH_OPTION_OPTIMIZE );
			m_nMaxStep      = nMaxStep;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// ������Ѳ��������IsStraightway�㷨
	if ( bFindMore )
	{
		if ( m_nSearchOption & SEARCH_OPTION_STRAIGHTWAY )
		{
			m_nSearchOption &= ~SEARCH_OPTION_STRAIGHTWAY;
		}
		else
		{
			m_nSearchOption |= SEARCH_OPTION_STRAIGHTWAY;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	if ( bFindMore && FindPathCore(ptStart,ptEnd) )
	{
		if (( m_nStepCount>nPathLenLimit) &&( nOption & SEARCH_OPTION_OPTIMIZE )) {ConnectCorners(ptStart);}
		nPathLenTemp[2] = BuildPath(m_PathTemp[2],MAX_PATH_LEN,true);
		pPathTemp[2]    = &(m_PathTemp[2][MAX_PATH_LEN-nPathLenTemp[2]]);
		if ( nShortest<0 || nPathLenTemp[2]<nPathLenTemp[nShortest] )
		{
			nShortest = 2;
			bFindMore = (nPathLenTemp[2] > nPathLenLimit) && ( nOption & SEARCH_OPTION_OPTIMIZE );
			m_nMaxStep      = nMaxStep;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// ������������ʱ,��������һ��,Ȼ��ѽ����ת
	if ( bFindMore && FindPathCore(ptEnd,ptStart) )
	{
		// ��Ϊ�Լ�������ռλ�飬���Կ���·����ʼ�����Լ�
		TILE_TAG * pTag = GetTileTag(ptStart);
		if ( m_pNearestTile!=0 && m_pNearestTile!=pTag)
		{
			pTag->pParent = m_pNearestTile;
			m_pNearestTile= pTag;
		}

		if (( m_nStepCount>nPathLenLimit) &&( nOption & SEARCH_OPTION_OPTIMIZE )) {ConnectCorners(ptEnd);}
		nPathLenTemp[3] = BuildPath(m_PathTemp[3],MAX_PATH_LEN,false);
		pPathTemp[3]    = m_PathTemp[3];
		if ( nShortest<0 || nPathLenTemp[3]<nPathLenTemp[nShortest] )
		{
			nShortest = 3;
			bFindMore = (nPathLenTemp[3] > nPathLenLimit) && ( nOption & SEARCH_OPTION_OPTIMIZE );
			m_nMaxStep      = nMaxStep;
		}
	}

	if ( nShortest<0 )
	{
		// ���û�����ɹ�,������������ĵ�
		if ( m_nSearchOption & SEARCH_OPTION_NEAREST )
		{
			FindPathCore(ptStart,ptEnd);
			nPathLen = BuildPath(m_PathTemp[0],MAX_PATH_LEN,true);
			pPath = &(m_PathTemp[0][MAX_PATH_LEN-nPathLen]);
			return nPathLen > 0;
		}

		return false;
	}else
	{
		nPathLen = nPathLenTemp[nShortest];
		pPath = pPathTemp[nShortest];
		return nPathLen>0;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
/**
@name         : ������·����
@brief        : 
@param        : 
@return       : 
*/
//////////////////////////////////////////////////////////////////////////
TEMPLATE_DECLARE
bool PATH_FINDER_DECLARE::FindPathCore(const POINT & ptStart,const POINT & ptEnd)
{
	++m_nFind;

	m_ptStart = ptStart;
	m_ptEnd   = ptEnd;

	m_pNearestTile = 0;
	m_nStepCount   = 0;

	POINT ptTile = ptStart;

	m_AroundQueue.clear();
	
	if ( m_nSearchOption & SEARCH_OPTION_OPTIMIZE )
	{
		memset(m_Corners,0,sizeof(m_Corners));
		memset(m_nCornerFlag,INVALID_CORNER_FLAG,sizeof(m_nCornerFlag));
	}

	while(1)
	{
		// ֱ�ӱƽ�
		if ( Approach(ptTile,ptEnd))
		{
			return true;
		}

		// ֱ�ӱƽ�ʧ�ܺ�ȡ����ת�������ת
		bool bAroundOK = false;
		while ( !m_AroundQueue.empty() )
		{
			AROUND_POINT around = m_AroundQueue.back();
			m_AroundQueue.pop_back();

			if ( Around(around.ptTile,around.nMoveDir,around.nTurnDir,m_ptStart,m_ptEnd))
			{
				assert ( m_pNearestTile );
		
				TileToPoint(m_pNearestTile,ptTile);
				bAroundOK = true;

				// ֻ�зֲ����������ϵĵ���ܼ���յ��б�
				if ( m_nSearchOption & SEARCH_OPTION_OPTIMIZE )
				{
					RecordCorner(ptTile);
				}

				break;
			}
		}

		// ��תȫ��ʧ����
		if( !bAroundOK )
		{
			return false;
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
/**
@name         : ��ֱ·����Ŀ���,��������赲,�򽫹յ�push���յ������
@brief        : ���ڶ���ֻ���ذ˷����ƶ�,���������ʼ���Ŀ��㲻�ڰ˷�������ʵ���ߵ�������
@param ptStart: ��ʼ��
@param ptEnd  : Ŀ���
@return       : �ɹ�����Ŀ����򷵻�true,���򷵻�false
*/
//////////////////////////////////////////////////////////////////////////
TEMPLATE_DECLARE
bool PATH_FINDER_DECLARE::Approach(const POINT & ptStart,const POINT & ptEnd)
{
	if ( ptStart.x==ptEnd.x && ptStart.y==ptEnd.y )
	{
		return true;
	}

	POINT ptTile = ptStart;
	POINT ptNext;

	TILE_TAG  * pParent = GetTileTag(ptStart);
	if ( pParent==0 )
	{
		return false;
	}

	if ( pParent->nFindID!=m_nFind )
	{
		pParent->pParent = 0;
		pParent->nMoveDir= 0;
		pParent->nFindID = m_nFind;
	}

	TILE_TAG  * pCurrent= 0;

	int   nCurDir = DIR_EAST;

	while(++m_nStepCount<=m_nMaxStep)
	{
		// ֱ����Ŀ���ƽ� approach to destination
		nCurDir = GetDir(ptTile,ptEnd);
		MoveNext(ptTile,nCurDir,ptNext);

		// ȡ��Tile��Ϣ
		pCurrent = GetTileTag(ptNext);

		if ( pCurrent==0 )
		{
			return false;
		}

		// ��ѭ����
		if ( IsTileVisited(pCurrent,nCurDir) )
		{
			return false;
		}

		// �����赲��ʼ��ת
		if ( m_BlockFunc(m_pMap,ptNext) )
		{
			// ���Ŀ������赲����ֱ���˳�
			if (ptNext.x==ptEnd.x && ptNext.y==ptEnd.y )
			{
				return true;
			}

			// ���յ�����Ž���ת����
			AROUND_POINT around;
			around.ptTile = ptTile;
			around.nMoveDir = TurnDir(nCurDir,TURN_CW);
			around.nTurnDir = TURN_CCW;
			
			m_AroundQueue.push_back(around);

			around.ptTile = ptTile;
			around.nMoveDir = TurnDir(nCurDir,TURN_CCW);
			around.nTurnDir = TURN_CW;

			m_AroundQueue.push_back(around);

			return false;
		}

		// ��¼·��
		MarkTileVisited(pCurrent,nCurDir,pParent);

		ptTile            = ptNext;
		m_pNearestTile    = pCurrent;
		pParent           = pCurrent;
		pCurrent->bAround = false;

		if (ptTile.x==ptEnd.x && ptTile.y==ptEnd.y )
		{
			return true;
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
/**
@name         : ���ϰ��￪ʼ����
@brief        : ���������赲,�������ڳ������赲���ƹ�ȥ,����ʵ�ֵ���һ����ռλ����ת�Ĵ���
@brief        : �ر�Ҫע�����: ���ϰ����㷨�Ƚϼ�,�鷳�����жϺ�ʱ��������
@brief        :                 �������Ƕ���һ��ֱ·�ĸ���,�ص�ֱ·���������,���Ǳ��㷨�ĺ���
@param  ptLoc : ��ʼ���е�λ��
@param nMoveDir:ǰ������
@param nTurnDir:��ת�ķ���,��˳ʱ���ƻ�����ʱ��
@return       : ����ɹ��ƹ��ϰ������»ص�ֱ·�򷵻�true,���򷵻�false
*/
//////////////////////////////////////////////////////////////////////////
TEMPLATE_DECLARE
bool PATH_FINDER_DECLARE::Around(const POINT & ptLoc,int nMoveDir,int nTurnDir,const POINT & ptStart,const POINT & ptEnd)
{
	POINT ptTile = ptLoc;
	POINT ptNext;
	POINT ptAround;

	TILE_TAG * pParent = GetTileTag(ptTile);
	TILE_TAG * pCurrent= 0;

	int   nContinueTurn = 0;

	while(++m_nStepCount<=m_nMaxStep)
	{
		MoveNext(ptTile,nMoveDir,ptNext);

		// ȡ��Tile��Ϣ
		pCurrent = GetTileTag(ptNext);

		if ( pCurrent==0 )
		{
			return false;
		}

		// ����Ƿ������ѭ��·��
		if ( IsTileVisited(pCurrent,nMoveDir) )
		{
			return false;
		}

		bool bNextBlock   = m_BlockFunc(m_pMap,ptNext);

		// �����һ���赲,����ͼ�򷴷���ת��
		if ( bNextBlock==true )
		{
			nMoveDir = TurnDir(nMoveDir,!nTurnDir);

			// ��¼ת���,��ֹ������ѭ��
			MarkTileVisited(pCurrent,nMoveDir,0);

			// ����ת��������
			if ( ++nContinueTurn > 2)
			{
				return false;
			}

			continue;
		}

		if ( nContinueTurn ) nContinueTurn = 0;

		// �н�����һ��
		MarkTileVisited(pCurrent,nMoveDir,pParent);

		ptTile         = ptNext;
		m_pNearestTile = pCurrent;
		pParent        = pCurrent;
        pCurrent->bAround = true;

		// ����Ѿ�����ֱ·�Ͼ�ֹͣ��ת
		bool bReturn = m_nSearchOption & SEARCH_OPTION_STRAIGHTWAY ? IsOnStraightWay(ptTile,ptLoc,ptEnd) : IsCanApproach(ptTile,ptEnd);
		if ( bReturn )
		{
			return true;
		}

		// ��������ŵ�Tile���赲,�������������ƻ�ȥ
		MoveNext(ptTile,TurnDir(nMoveDir,nTurnDir),ptAround);
		if (!m_BlockFunc(m_pMap,ptAround))
		{
			nMoveDir = TurnDir(nMoveDir,nTurnDir);
		}
	};

	return false;
}

//////////////////////////////////////////////////////////////////////////
/**
@name         : ��A�㵽B�㣬�м��п��ܽ�������ת�����ﳢ�Խ���������ֱ��������
@brief        : ·���Ż�����֮һ
@param ptStart: ��ʼ��
@param ptEnd  : Ŀ���
@return       : �ɹ�����Ŀ����򷵻�true,���򷵻�false
*/
//////////////////////////////////////////////////////////////////////////
TEMPLATE_DECLARE
bool PATH_FINDER_DECLARE::ConnectDirect(const POINT & ptStart,const POINT & ptEnd)
{
	if ( ptStart.x==ptEnd.x && ptStart.y==ptEnd.y )
	{
		return true;
	}

	POINT ptTile = ptStart;
	POINT ptNext;

	TILE_TAG  * pParent = GetTileTag(ptStart);
	if ( pParent==0 )
	{
		return false;
	}

	if ( pParent->nFindID!=m_nFind )
	{
		pParent->pParent = 0;
		pParent->nMoveDir= 0;
		pParent->nFindID = m_nFind;
	}

	TILE_TAG  * pCurrent= 0;

	int   nCurDir = DIR_EAST;

	while(++m_nStepCount<=m_nMaxStep)
	{
		// ֱ����Ŀ���ƽ� approach to destination
		nCurDir = GetDir(ptTile,ptEnd);
		MoveNext(ptTile,nCurDir,ptNext);

		// ȡ��Tile��Ϣ
		pCurrent = GetTileTag(ptNext);

		if ( pCurrent==0 )
		{
			return false;
		}

		// �����Ѿ����ڵ�·������
		if ( pCurrent->nFindID==m_nFind )
		{
			pCurrent->pParent = pParent;
		//	return true;
		}

		// �����赲����
		if ( m_BlockFunc(m_pMap,ptNext) )
		{
			return false;
		}

		// ��¼·��
		MarkTileVisited(pCurrent,nCurDir,pParent);

		ptTile            = ptNext;
		pParent           = pCurrent;
		pCurrent->bAround = false;
		
		if (ptTile.x==ptEnd.x && ptTile.y==ptEnd.y )
		{
			return true;
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
/**
@name         : ��¼�յ�
@brief        : �����Ż�·��,Ŀǰֻ��¼���������ĸ���
*/
//////////////////////////////////////////////////////////////////////////
TEMPLATE_DECLARE
void PATH_FINDER_DECLARE::RecordCorner(const POINT & ptTile)
{
	if (( ptTile.x <= m_Corners[CORNER_LEFT_TOP].x && ptTile.y <= m_Corners[CORNER_LEFT_TOP].y ) || m_nCornerFlag[CORNER_LEFT_TOP] == INVALID_CORNER_FLAG)
	{
		m_Corners[CORNER_LEFT_TOP] = ptTile;
		m_nCornerFlag[CORNER_LEFT_TOP] = m_nStepCount;
	}

	if (( ptTile.x <= m_Corners[CORNER_LEFT_BOTTOM].x && ptTile.y >= m_Corners[CORNER_LEFT_BOTTOM].y )|| m_nCornerFlag[CORNER_LEFT_BOTTOM] == INVALID_CORNER_FLAG)
	{
		m_Corners[CORNER_LEFT_BOTTOM] = ptTile;
		m_nCornerFlag[CORNER_LEFT_BOTTOM] = m_nStepCount;
	}

	if (( ptTile.x >= m_Corners[CORNER_RIGHT_TOP].x && ptTile.y <= m_Corners[CORNER_RIGHT_TOP].y ) || m_nCornerFlag[CORNER_RIGHT_TOP] == INVALID_CORNER_FLAG)
	{
		m_Corners[CORNER_RIGHT_TOP] = ptTile;
		m_nCornerFlag[CORNER_RIGHT_TOP] = m_nStepCount;
	}

	if (( ptTile.x >= m_Corners[CORNER_RIGHT_BOTTOM].x && ptTile.y >= m_Corners[CORNER_RIGHT_BOTTOM].y ) || m_nCornerFlag[CORNER_RIGHT_BOTTOM] == INVALID_CORNER_FLAG)
	{
		m_Corners[CORNER_RIGHT_BOTTOM] = ptTile;
		m_nCornerFlag[CORNER_RIGHT_BOTTOM] = m_nStepCount;
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@name         : ·����������Խ����йյ�����,���Եõ����Ż���·��
*/
//////////////////////////////////////////////////////////////////////////
TEMPLATE_DECLARE
void PATH_FINDER_DECLARE::ConnectCorners(const POINT & ptStart)
{
	DWORD dwMinCorner = INVALID_CORNER_FLAG;
	DWORD dwVisited   = 0;
	int   index = -1;
	POINT ptConnect = ptStart;

	while(1)
	{
		for ( int i=0;i<CORNER_NUM;++i )
		{
			if ( m_nCornerFlag[i]<dwMinCorner && m_nCornerFlag[i] > dwVisited )
			{
				dwMinCorner =  m_nCornerFlag[i];
				index = i;
			}
		}

		if ( index>=0 )
		{
			ConnectDirect(ptConnect,m_Corners[index]);
			ptConnect = m_Corners[index];
			index = -1;
			dwVisited = dwMinCorner;
			dwMinCorner = INVALID_CORNER_FLAG;
		}else
		{
			break;
		}
	};
}

//////////////////////////////////////////////////////////////////////////
/**
@name         : ��ȡTile��Ϣ
@brief        : ����Tile����Ϣ����ʱ������m_TileTags��,�ö�����ÿ����·�����ܸ�дһ��,����ȡ��ʱ��Ҫ����ӳ��
@brief        : �趨һ�������·��Χ�ĺô���: 
@brief        :     1.����ͼ�ǳ���ʱ(����1024*1024),���ά��һ���͵�ͼͬ����С�������������ڴ�
@brief        :     2.m_TileTags�Ĵ�С�͵�ͼ��С�޹�,�������еĵ�ͼ���Թ���һ����·��,���Ը���Ľ�ʡ�ڴ�
@return       : ����ǲ��Ϸ���Tile�����Ѿ�������������·��Χ�򷵻�0,���򷵻�Tile��Ϣָ��
*/
//////////////////////////////////////////////////////////////////////////
TEMPLATE_DECLARE
typename PATH_FINDER_DECLARE::TILE_TAG * PATH_FINDER_DECLARE::GetTileTag(const POINT & ptTile)
{
	// �Ƿ񳬳��߽�
	if ( ptTile.x < 0 || (unsigned long)ptTile.x >= m_nMapWidth )
	{
		return 0;
	}

	if ( ptTile.y < 0 || (unsigned long)ptTile.y >= m_nMapHeight )
	{
		return 0;
	}

	// ӳ�䵽Tag����
	int x = (ptTile.x - m_ptStart.x) + (MAX_SEARCH_AREA>>1);
	int y = (ptTile.y - m_ptStart.y) + (MAX_SEARCH_AREA>>1);

	if ( x<0 || y<0 || x>=MAX_SEARCH_AREA || y>=MAX_SEARCH_AREA )
	{
		return 0;
	}

	return &(m_TileTags[y*MAX_SEARCH_AREA+x]);
}

//////////////////////////////////////////////////////////////////////////
/**
@name         : ��TAG��ָ����Tile������ (GetTileTag�������)
@brief        : ��TAG��ָ��ת����Tile�������ֱ��ͨ��ָ�뵽m_TileTags[0]��ƫ���������
@param  pTag  : ����TILE_TAGָ��
@param ptTile : ���ظ�ָ���Ӧ��Tile����
@return       : 
*/
//////////////////////////////////////////////////////////////////////////
TEMPLATE_DECLARE
void PATH_FINDER_DECLARE::TileToPoint(TILE_TAG * pTag,POINT &ptTile)
{
	int offset = pTag - m_TileTags;

	// �����г�������,�����MAX_SEARCH_AREAȡֵ����,������������Ż�
	ptTile.x = m_ptStart.x - (MAX_SEARCH_AREA>>1) + (offset%MAX_SEARCH_AREA);
	ptTile.y = m_ptStart.y - (MAX_SEARCH_AREA>>1) + (offset/MAX_SEARCH_AREA);
}

//////////////////////////////////////////////////////////////////////////
/**
@name         : �ж�ĳ��Tile�Ƿ񱻷��ʹ�
@brief        : ���������Ҫ���ڹ����תʱ����ѭ��
@param  pTag  : Tile����Ϣָ�� 
@param  nDir  : ������ξ���ͬһ��Tile���Ǿ����ķ���ͬ��Ӧ������,����������Ҫ��������Եķ���
@return       : 
*/ 
//////////////////////////////////////////////////////////////////////////
TEMPLATE_DECLARE
bool PATH_FINDER_DECLARE::IsTileVisited(TILE_TAG * pTag,int nDir)
{
	return pTag->nFindID==m_nFind && (pTag->nMoveDir & (0x01 << nDir));
}

//////////////////////////////////////////////////////////////////////////
/**
@name         : ���ĳ��Tile�Ѿ������ʹ�
@brief        : ���������Ҫ���ڹ����תʱ����ѭ��
@param  pTag  : Tile����Ϣָ�� 
@param  nDir  : ������ξ���ͬһ��Tile���Ǿ����ķ���ͬ��Ӧ������,����������Ҫ��������Եķ���
@param pParent: ��¼���ڵ�ָ�룬���ڻ���·��
@return       : 
*/
//////////////////////////////////////////////////////////////////////////
TEMPLATE_DECLARE
void PATH_FINDER_DECLARE::MarkTileVisited(TILE_TAG * pTag,int nDir,TILE_TAG * pParent)
{
	if ( pTag->nFindID!=m_nFind )
	{
		pTag->pParent = pParent;
		pTag->nMoveDir= 0x01 << nDir;
		pTag->nFindID = m_nFind;
	}else
	{
		pTag->nMoveDir |= 0x01<< nDir;
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@name         : �ظ��������ƶ�һ��
@brief        : 
@param ptTile : ��ǰ����
@param dir    : ǰ������
@param ptNext : ������һ������
@return       : 
*/
//////////////////////////////////////////////////////////////////////////
TEMPLATE_DECLARE
void PATH_FINDER_DECLARE::MoveNext(const POINT & ptTile,int dir,POINT & ptNext)
{
	static int s_DirNextTable[8][2] =
	{
		{1,0},  // ������ : ��  (angle:0)
		{1,-1}, // ������ : ����(angle:45)
		{0,-1}, // ������ : ��  (angle:90)
		{-1,-1},// ������ : ����(angle:135)
		{-1,0}, // ������ : ��  (angle:180)
		{-1,1}, // ������ : ����(angle:225)
		{0,1},  // ������ : ��  (angle:270)
		{1,1},  // ������ : ����(angle:315)	
	};

	assert(dir>=0 && dir <8 );

	ptNext.x = ptTile.x + s_DirNextTable[dir][0];
	ptNext.y = ptTile.y + s_DirNextTable[dir][1];
}

//////////////////////////////////////////////////////////////////////////
/**
@name         : ȡ��������֮��ķ���
@brief        : ����ֻ����45���������İ˸�����
@return       : ����ֵ�����ǰ���ö��ֵ
*/
//////////////////////////////////////////////////////////////////////////
TEMPLATE_DECLARE
int PATH_FINDER_DECLARE::GetDir(const POINT & ptCur,const POINT & ptNext)
{
	static int s_DirTable[3][3] = {
		{DIR_WEST_NORTH,DIR_NORTH,DIR_EAST_NORTH},
		{DIR_WEST,-1,DIR_EAST},
		{DIR_WEST_SOUTH,DIR_SOUTH,DIR_EAST_SOUTH}
	};
 
	int x = ptNext.x > ptCur.x ? 2 : (ptNext.x == ptCur.x ? 1 : 0);
	int y = ptNext.y > ptCur.y ? 2 : (ptNext.y == ptCur.y ? 1 : 0);

	return s_DirTable[y][x];
}

//////////////////////////////////////////////////////////////////////////
/**
@name         : ��ת����
@brief        : ������ǰ����,������˳ʱ�����ʱ����ת��ķ���
@param        : 
@return       : ������ת��ķ���
*/
//////////////////////////////////////////////////////////////////////////
TEMPLATE_DECLARE
int  PATH_FINDER_DECLARE::TurnDir(int nMoveDir,int nTurnDir)
{
	// б����ֻת45��,��ֱˮƽ����ת90��,��������Ǹ��������������������
	int turn_angle = (nMoveDir & 0x01) ? 1 : 2;

	if ( nTurnDir==TURN_CW)
	{
		nMoveDir -= turn_angle;
		return nMoveDir >=0 ? nMoveDir : nMoveDir+8;
	}else
	{
		nMoveDir += turn_angle;
		return nMoveDir >=8 ? nMoveDir-8 : nMoveDir;
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@name         : �ж�ĳ���Ƿ���ֱ·��
@brief        : ������������,�����������Ҫ˼·���жϸ������Ƿ�����ʼ�㵽Ŀ��㹹�ɵ�ֱ�ߣ������ߣ���
@brief        : ʵ�����ж��Ƿ���������ʱ����һ���С����,���������ǽ����������жϺ�ʱ��������,�Ȿ������һ��ģ������,������ȫ��Ӱ����·���
@param ptTile : ��ǰ��
@param ptStart: ��·��ʼ��
@param ptEnd  : ��·������
@return       : 
*/
//////////////////////////////////////////////////////////////////////////
TEMPLATE_DECLARE
bool PATH_FINDER_DECLARE::IsOnStraightWay(const POINT & ptTile,const POINT & ptStart,const POINT & ptEnd)
{
	int dx = ptEnd.x - ptStart.x;
	int dy = ptEnd.y - ptStart.y;

	// ��90��������
	if ( dx==0 )
	{
		return (ptEnd.x == ptTile.x) && ((ptTile.y > ptStart.y) == (ptEnd.y>ptStart.y));
	}

	// ��0��������
	if ( dy==0 )
	{
		return (ptEnd.y == ptTile.y) && ((ptTile.x > ptStart.x) == (ptEnd.x>ptStart.x));
	}

	int abs_x = abs(dx);
	int abs_y = abs(dy);

	// ��45��������
	if ( abs_x==abs_y )
	{
		if ( abs(ptTile.x-ptStart.x)!=abs(ptTile.y-ptStart.y) )
			return false;
		return ((ptEnd.x>ptStart.x)==(ptTile.x>ptStart.x)) && ((ptEnd.y>ptStart.y)==(ptTile.y>ptStart.y));
	}
	
	// �۳������ٲ�
	POINT ptMiddle;

	if ( abs_x<abs_y )
	{
		ptMiddle.x = ptEnd.x;
		ptMiddle.y = ptStart.y + (dy > 0 ? abs_x : -abs_x);
	}else
	{
		ptMiddle.y = ptEnd.y;
		ptMiddle.x = ptStart.x + (dx > 0 ? abs_y : -abs_y);
	}
	
	if ( ptMiddle.x==ptTile.x && ptMiddle.y==ptTile.y )
	{
		return true;
	}

	return IsOnStraightWay(ptTile,ptStart,ptMiddle) || IsOnStraightWay(ptTile,ptMiddle,ptEnd);
}

//////////////////////////////////////////////////////////////////////////
/**
@name         : ��ʹ��ֱ·�ж�,�����жϿɲ�����Approach
@brief        : ��:ֻҪ��Ŀ�����һ���㲻��ռλ���ʾ���Խ�����ת
@param        : 
@return       : 
*/
//////////////////////////////////////////////////////////////////////////
TEMPLATE_DECLARE
bool PATH_FINDER_DECLARE::IsCanApproach(const POINT & ptTile,const POINT & ptEnd)
{
	int nDir = GetDir(ptTile,ptEnd);
	POINT ptNext;
	MoveNext(ptTile,nDir,ptNext);

	if ( m_BlockFunc(m_pMap,ptNext) )
	{
		return false;
	}

	TILE_TAG * pTag = GetTileTag(ptNext);
	if ( pTag==0 || pTag->nFindID==m_nFind )
	{
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
/**
@name         : �����߹���Tile,��˷����·��
@brief        : ��Ϊ��·ʱ���Ǿ���ĳЩTile,��ʱ����֪���Ƿ��ܵ���Ŀ�ĵ�,�޴Ӽ�¼,���Ե����Ҫ��������˷һ����ܰ�·���ҳ���
@param pPathBuffer : ������·���Ļ�����
@param nBufSize    : ��������С
@param nReverse    : �Ƿ��·����������,��Ϊ�ǻ���,����Ĭ��Ӧ�÷�������
@return       : 
*/ 
//////////////////////////////////////////////////////////////////////////
TEMPLATE_DECLARE
int PATH_FINDER_DECLARE::BuildPath(POINT * pPathBuffer,int nBufSize,bool nReverse)
{
	int   nBarrier = 0;
	int   nPathLen = 0; 
	POINT ptTile;

	while(m_pNearestTile && nPathLen<nBufSize)
	{
		TileToPoint(m_pNearestTile,ptTile);

		// ��ת��Tile�Ż�,��ҪƵ��ת��
		if ( m_pNearestTile->bAround && nPathLen>=2 )
		{
			POINT ptPreTile = nReverse ? pPathBuffer[nBufSize-1-nPathLen+2] : pPathBuffer[nPathLen-2];
			if ( abs(ptPreTile.x-ptTile.x)<=1 && abs(ptPreTile.y-ptTile.y)<=1 )
			{
				nPathLen-=1;
			}
		}

		// ��·��ŵ���������
		if ( nReverse )
		{
			pPathBuffer[nBufSize-1-nPathLen] = ptTile;
		}
		else
		{
			pPathBuffer[nPathLen] = ptTile;
		}

		m_pNearestTile = m_pNearestTile->pParent;
		++nPathLen;

		// �����ѭ��
		if ( ++nBarrier>=nBufSize)
		{
			assert("find path error! detected a closed-loop when buiding the path.");
			return 0;  
		}
	}

	return nPathLen;
}

#endif//__PATH_FINDER_H__