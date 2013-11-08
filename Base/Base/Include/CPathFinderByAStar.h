/*******************************************************************
** �ļ���:	CPathFinderByAStar.h
** ��  Ȩ:	(C)  2010 - All Rights Reserved
** 
** ��  ��:	2010/07/28
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: ��־��
** ��  ��: 2010/07/28
** ��  ��: ���һ���޸Ĺ���A* �㷨���滻�������Դ���Ѱ·�㷨���������
           �ƶ������ڿ���ȥ����Ȼ
********************************************************************/
#ifndef __CPATH_FINDERBYASTAR_H__
#define __CPATH_FINDERBYASTAR_H__

#include <assert.h>
#include <functional>
#include <vector>
#include <set>
#include <map> 
#include <iostream> 
using namespace std;



template
< 
	    class    _Map,                                                  // ��ͼ 
		typename _BlockTestFunc = std::mem_fun1_t<bool,_Map,xs::Point> ,    // �赲�жϺ�������,��������bool IsBlock(xs::Point pt)
		int      MAX_PATH_LEN   = 1024 ,                                // ���·������
		int      MAX_SEARCH_AREA= 256                                   // ����������
>

class CPathFinderByAStar
{
	//struct stPathNode;
public:
    
	struct stPathNode 		  //���,Ҳ����ÿ������
	{
		xs::Point m_PointPos;
		bool bIsObs;
		int m_nGvalue;            // Gֵ
		int m_nPointvalue;        // �������ֵ 
		stPathNode *pParent;	  // �����ָ��
	} ;	
    
	typedef std::multimap<int, int>  OpenTempList;   //open list 	�ڶ���int��ID�� ��һ���ǹ������ֵ
	typedef std::set<int>            OpenList;      // //open list 	    ��һ��int��ID�� �ڶ����ǹ������ֵ
	typedef std::set<int>            CloseList;      //close list 

	OpenTempList::iterator itTempOpen1;
	OpenTempList::iterator itTempOpen2;	
public:
	//iFindPathCallback*	m_pCallback;
	_Map*                m_pMap;                                      // ��ͼָ��
	_BlockTestFunc       m_BlockFunc;                                 // �赲�жϺ���
	unsigned long        m_nMapWidth;                                 // ��ͼ���
	unsigned long        m_nMapHeight;                                // ��ͼ�߶�
	stPathNode*          stAStarPoint;
	xs::Point				 m_PathTemp[MAX_PATH_LEN];                    // �����洢���ص�·��������
	xs::Point				 m_PathResult[MAX_PATH_LEN];                  // �����洢���ص�·��(����·��)

	//cSize			m_szMap;	
	xs::Point mapNearPoint;		
public:
	CPathFinderByAStar( ) : m_pMap(0),m_BlockFunc(0),stAStarPoint(0),m_nPathCount(0)
	{
		m_mOpenTempList.clear(); //clean tempopen   list 
		m_mOpenList.clear(); 	 //clean open   list 
		m_mCloseList.clear();    //clean close  list 
	}

	~CPathFinderByAStar( )
	{  
		delete[] stAStarPoint;  
	}

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
	bool FindPathByASatr(const xs::Point & ptStart,const xs::Point & ptEnd,xs::Point *& pPath,int & nPathLen,int nOption=SEARCH_OPTION_OPTIMIZE,int nMaxStep=MAX_PATH_LEN);
	/**
	@name			: �Ƿ������ֱ��
	@brief			: 
	@param ptStart  : �������
	@param ptEnd    : �յ�����
	@return         : ������·�Ƿ�ɹ� 
	*/
	bool CanWalkDirect(const xs::Point& ptFrom, const xs::Point& ptTo);
	/**
	@name			: Ѱ�����·��(����Ѱ·����)
	@brief			: 
	@param ptStart  : �������
	@param ptEnd    : �յ�����
	@param bChangeEnd : �Ƿ�Ѱ�������
	@return         : ������·�Ƿ�ɹ� 
	*/
	bool FindPathAStar(const xs::Point& ptFrom, const xs::Point& ptTo ,bool bChangeEnd );
	/**
	@name			: ��ȡHֵ
	@brief			: 
	@param m_nH  : �������
	@return         : ����Hֵ
	*/
	int GetHValue( int nH);

	/**
	@name			: m_bDir�����ж��Ƿ�Ϊ�Խ���,��m_bDir==trueʱ��Ϊб�򣬷���Ϊ����
	@brief			: 
	@param m_nH  : �������
	@return         : ����Hֵ
	*/
	int GetGGValue( int m_nG,bool m_bDir);
	/**
	@name			: 
	@brief			: 
	*/
	inline  void SearchPos(int m_nIdPos ,int m_nIdPrePos,bool m_b);
	/**
	@name			: 
	@brief			: 
	*/
	void DoInsert(int nfromPre,int ntoNow,bool b);
	/**
	@name			: 
	@brief			: 
	*/
	bool FindResult(int nEndId,int nEndPreId);

	/**
	@name			: 
	@brief			: 
	*/
	bool QueryResult(xs::Point*& lstPoint, int& count);
public:
	OpenTempList m_mOpenTempList;
	OpenList     m_mOpenList;       
	CloseList    m_mCloseList;
	int m_nwidth;      //��ͼ����
	int m_nlength;     //��ͼ����
	int m_nPathCount;   //�߹��ĸ�����
	int	m_nMapCount;
	int m_nStart;    //�������
	int m_nEnd;      //�յ�����	
	int m_nxEnd;//
	int m_nyEnd;//

};
// ��ֱ·����Ŀ���
#define  TEMPLATEMAP_DECLARE		template<class _Map,typename _BlockTestFunc,int MAX_PATH_LEN,int MAX_SEARCH_AREA>
#define  PATH_FINDERASTAR_DECLARE	CPathFinderByAStar<_Map,_BlockTestFunc,MAX_PATH_LEN,MAX_SEARCH_AREA>
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////*AѰ·�㷨*/////////////////////////////////////////////////////
/**
@name           : ���õ�ͼ��Ϣ 
@brief          : ����FindPath֮ǰ�����õ�ͼ��Ϣ,�ú��������ظ�����,���Կ����ڶ����ͼ������·��
@param nMapWidth: ��ͼ���
@param nMapHeigh: ��ͼ�߶�
@param pMap     : ��ͼ����ָ��
@param isBlock  : �жϵر��Ƿ��赲�ĺ���,�����ͼ�����ж��赲�ĺ�����IsBlock��ò������ô�
@return         : 
*/
TEMPLATEMAP_DECLARE
bool PATH_FINDERASTAR_DECLARE::SetMapInfo(unsigned long nMapWidth,unsigned long nMapHeight,_Map * pMap,_BlockTestFunc isBlock)
{

	delete[] stAStarPoint;
	m_nMapWidth = nMapWidth;
	m_nMapHeight= nMapHeight;

	m_pMap = pMap;
	m_BlockFunc = isBlock;
	m_mOpenTempList.clear(); //clean tempopen   list 
	m_mOpenList.clear(); 	//clean open   list 
	m_mCloseList.clear();   //clean close  list
	m_nwidth = nMapWidth;    //��ͼ����  
	m_nlength = nMapHeight;   //��ͼ����  
	m_nMapCount = m_nwidth * m_nlength;	

	m_nPathCount = 0;//
	stAStarPoint = new stPathNode[m_nMapCount];
	memset(stAStarPoint, 0, sizeof(stPathNode) * m_nMapCount);
	for (int y = 0; y < m_nlength; y++) 
	{	 
		int numtemp=y * m_nwidth;
		for (int x = 0; x < m_nwidth; x++)	 				
		{
			stAStarPoint[numtemp + x ].m_PointPos.x = x;
			stAStarPoint[numtemp + x ].m_PointPos.y = y;	
		}	
	}
	return true;
}
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
TEMPLATEMAP_DECLARE
bool PATH_FINDERASTAR_DECLARE::FindPathByASatr(const xs::Point & ptStart,const xs::Point & ptEnd,xs::Point *& pPath,int & nPathLen,int nOption,int nMaxStep)
{
	if(FindPathAStar(ptStart, ptEnd ,true))
	{
		QueryResult(pPath,nPathLen);
		return true;
	}
	return false;
}

/**
@name			: �Ƿ������ֱ��
@brief			: 
@param ptStart  : �������
@param ptEnd    : �յ�����
@return         : ������·�Ƿ�ɹ� 
*/
TEMPLATEMAP_DECLARE
bool PATH_FINDERASTAR_DECLARE::CanWalkDirect(const xs::Point& ptFrom, const xs::Point& ptTo)
{
	int dx = ptTo.x - ptFrom.x;
	int dy = ptTo.y - ptFrom.y;

	if (dx == 0 || dy == 0 || abs(dx) == abs(dy))
	{
		xs::Point ptStep = ptTo - ptFrom;
		if (ptStep.x != 0)
			ptStep.x /= abs(ptStep.x);
		if (ptStep.y != 0)
			ptStep.y /= abs(ptStep.y);
		for (xs::Point temp = ptFrom; temp != ptTo; temp += ptStep)
		{
			bool bBlock =  m_BlockFunc(m_pMap,temp);
			if (bBlock)
			{
				return false;
			}
		}
		return true;
	}

	xs::Point ptReFr, ptReTo;   //ptReFr���������ĶԽǵ㣬ptReTo���յ�����ĶԽǵ�
	unsigned int uiadx = abs(dx), uiady = abs(dy);
	int signedDx = (dx > 0) ? 1 : -1;
	int signedDy = (dy > 0) ? 1 : -1;
	if (uiadx > uiady)
	{
		ptReFr.y = ptTo.y;
		ptReFr.x = ptFrom.x + uiady*signedDx;
		ptReTo.y = ptFrom.y;
		ptReTo.x = ptTo.x - uiady*signedDx;
	}
	else
	{
		ptReFr.x = ptTo.x;
		ptReFr.y = ptFrom.y + uiadx*signedDy;
		ptReTo.x = ptFrom.x;
		ptReTo.y = ptTo.y - uiadx*signedDy;
	}

	xs::Point ptStepCro = ptReFr - ptFrom;    //�ԽǾ���
	xs::Point ptStepVer = ptReTo - ptFrom;    //��ֱ����
	ptStepCro /= abs(ptStepCro.x);
	if (ptStepVer.x != 0)
		ptStepVer /= abs(ptStepVer.x);
	else
		ptStepVer /= abs(ptStepVer.y);

	xs::Point ptStart = ptFrom, ptEnd = ptReTo, ptCur;
	for (; ptStart != ptReFr + ptStepCro; ptStart += ptStepCro, ptEnd += ptStepCro)
	{
		for (ptCur = ptStart; ptCur != ptEnd + ptStepVer; ptCur += ptStepVer)
		{
			bool bBlock =  m_BlockFunc(m_pMap,ptCur);
			if (bBlock)
			{
				return false;
			}
		}
	}
	return true;
}
/**
@name			: Ѱ�����·��(����Ѱ·����)
@brief			: 
@param ptStart  : �������
@param ptEnd    : �յ�����
@param bChangeEnd : �Ƿ�Ѱ�������
@return         : ������·�Ƿ�ɹ� 
*/
TEMPLATEMAP_DECLARE
bool PATH_FINDERASTAR_DECLARE::FindPathAStar(const xs::Point& ptFrom, const xs::Point& ptTo ,bool bChangeEnd )
{
	m_mOpenList.clear(); 	//clean open   list 
	m_mCloseList.clear();   //clean close  list 
	m_mOpenTempList.clear();		

	m_nStart = ptFrom.y*m_nwidth+ptFrom.x;
	m_nEnd = ptTo.y*m_nwidth+ptTo.x;
	m_nPathCount = 0;			

	if(!bChangeEnd)
	{
		if(!m_BlockFunc(m_pMap,ptTo))  //˵���յ��ǲ����ߵ� �Ҹ��ͽ��� �������ϰ���û��ã���ʱ������������
		{			
			int findrang=1;	
			bool bfind=false;						
			while(findrang<=36) //������Χ6���ڵ�ֵ	
			{
				for(int i=-findrang;abs(i)<=findrang;i++)
				{					
					for(int j=-findrang;abs(j)<=findrang;j++)
					{
						if((abs(i)<findrang)&&(abs(j)<findrang))
						{
							continue;
						}
						else
						{
							mapNearPoint.x=ptTo.x+i;
							mapNearPoint.y=ptTo.y+j;
							
							// ������ͼ��Χ
							if(mapNearPoint.x > m_nwidth || mapNearPoint.y > m_nlength || mapNearPoint.x < 0 || mapNearPoint.y < 0)
							{
								continue;
							}
							m_nEnd=mapNearPoint.y*m_nwidth+mapNearPoint.x;	
							if(!m_BlockFunc(m_pMap,ptTo)) //�ҵ�
							{
								bfind=true; 
								break;
							}
						}
					}
					if(bfind) 
					{
						break;
					}
				}
				if(bfind)
				{
					break;
				}
				findrang++;
			}
			if(!bfind)
			{
				return false;	
			}
		}
	}
	else 	
	{
		if(m_BlockFunc(m_pMap,ptTo)) 
		{
			return false; //�յ��ǲ����ߵ�
		}
	}

	if(m_nStart == m_nEnd) 
	{
		return false;
	}
	m_nxEnd = m_nEnd%m_nwidth;//
	m_nyEnd = m_nEnd/m_nwidth;//

	//for(int i=0;i<m_nMapCount;i++) 
	//{
	//	stAStarPoint[i].pParent=NULL;
	//}

	if(m_mCloseList.empty())//add the first nod to the open list 
	{			
		stAStarPoint[m_nStart].pParent=NULL;
		stAStarPoint[m_nStart].m_nGvalue=0;			
		stAStarPoint[m_nStart].m_nPointvalue=GetHValue(m_nStart);			
		m_mOpenList.insert(m_nStart); 	//
		m_mOpenTempList.insert(OpenTempList::value_type(stAStarPoint[m_nStart].m_nPointvalue,m_nStart)); 
	}

	////////////////////////////start:�����Ƿ����ֱ�ߵ�Ŀ��//////////////////////////////////////////
	//if (CanWalkDirect(ptFrom, ptTo))
	//{
	//	m_nPathCount = 1;
	//	stAStarPoint[m_nEnd].pParent = &stAStarPoint[m_nStart];
	//	return true;
	//}
	//////////////////////////end:�����Ƿ����ֱ�ߵ�Ŀ��//////////////////////////////////////////

	//������A*�㷨�ľ���ʵ�ֹ���	
	while(m_mOpenList.size())
	{
		int CurrentMinValuePosId;	

		itTempOpen1 = m_mOpenTempList.begin(); 
		CurrentMinValuePosId = itTempOpen1->second; 

		itTempOpen2 = itTempOpen1;
		itTempOpen2++;
		m_mOpenTempList.erase(itTempOpen1,itTempOpen2);

		int MinX,MinY;
		MinX=stAStarPoint[CurrentMinValuePosId].m_PointPos.x;
		MinY=stAStarPoint[CurrentMinValuePosId].m_PointPos.y;

		//���������������������ĵ�ΪĿ��㣬�������
		//���°벿����ɢ
		if(MinY != m_nlength-1) 
		{					
			if(CurrentMinValuePosId+m_nwidth == m_nEnd)
				return FindResult(m_nEnd, CurrentMinValuePosId);					
			SearchPos(CurrentMinValuePosId+m_nwidth,CurrentMinValuePosId,false);
			//���·�
			if(MinX != 0)               
			{
				if(CurrentMinValuePosId+m_nwidth-1 == m_nEnd) 
					return FindResult(m_nEnd, CurrentMinValuePosId); 				
				SearchPos(CurrentMinValuePosId+m_nwidth-1,CurrentMinValuePosId,true);		
			}
			//���·�
			if(MinX != (m_nwidth-1))    
			{
				if(CurrentMinValuePosId+m_nwidth+1 == m_nEnd) 
					return FindResult(m_nEnd, CurrentMinValuePosId);//�����·��ҵ�				
				SearchPos(CurrentMinValuePosId+m_nwidth+1,CurrentMinValuePosId,true);	
			}
		}

		//������ɢ	
		if(MinY > 0 )
		{
			//���Ϸ�
			if(CurrentMinValuePosId-m_nwidth == m_nEnd)  
				return FindResult(m_nEnd, CurrentMinValuePosId); 			
			SearchPos(CurrentMinValuePosId-m_nwidth,CurrentMinValuePosId,false);
			//���Ϸ�
			if(MinX!=0)              
			{		
				if(CurrentMinValuePosId-m_nwidth-1 == m_nEnd) 
					return FindResult(m_nEnd, CurrentMinValuePosId);  			
				SearchPos(CurrentMinValuePosId-m_nwidth-1,CurrentMinValuePosId,true);							
			}
			//���Ϸ�
			if(MinX != (m_nwidth-1))   
			{
				if(CurrentMinValuePosId-m_nwidth+1 == m_nEnd)  
					return FindResult(m_nEnd, CurrentMinValuePosId); //���Ϸ��ҵ�				
				SearchPos(CurrentMinValuePosId-m_nwidth+1,CurrentMinValuePosId,true);	
			}
		}
		//������ɢ
		if(MinX != (m_nwidth-1))	
		{
			if(CurrentMinValuePosId+1 == m_nEnd)
				return FindResult(m_nEnd, CurrentMinValuePosId);			
			SearchPos(CurrentMinValuePosId+1,CurrentMinValuePosId,false);						
		}
		//������ɢ
		if(MinX > 0)   
		{
			if(CurrentMinValuePosId-1 == m_nEnd) 
				return FindResult(m_nEnd, CurrentMinValuePosId);			
			SearchPos(CurrentMinValuePosId-1,CurrentMinValuePosId,false);						
		}	
		//���˴���ֵΪ��͵�����Ƶ�close���� ����open����ɾȥ
		m_mCloseList.insert(CurrentMinValuePosId); //
		m_mOpenList.erase(CurrentMinValuePosId);//itOpenTemp			
	}
	m_mOpenList.clear(); 	//clean open   list 
	m_mCloseList.clear();   //clean close  list 
	m_mOpenTempList.clear();
	return false; //open��Ϊ�գ��������������·��
}
/**
@name			: ��ȡHֵ
@brief			: 
@param m_nH  : �������
@return         : ����Hֵ
*/
TEMPLATEMAP_DECLARE
int  PATH_FINDERASTAR_DECLARE::GetHValue( int nH)
{
	int dx,dy;		
	dx=m_nxEnd - nH%m_nwidth;	//
	dy=m_nyEnd - nH/m_nwidth;	
	return dx*dx+dy*dy;	
}

/**
@name			: m_bDir�����ж��Ƿ�Ϊ�Խ���,��m_bDir==trueʱ��Ϊб�򣬷���Ϊ����
@brief			: 
@param m_nH  : �������
@return         : ����Hֵ
*/
TEMPLATEMAP_DECLARE
int  PATH_FINDERASTAR_DECLARE::GetGGValue( int nG,bool bDir)
{
	if(bDir)
		return  stAStarPoint[nG].pParent->m_nGvalue+14;
	else 		
		return  stAStarPoint[nG].pParent->m_nGvalue+10;
}
/**
@name			: 
@brief			: 
*/
TEMPLATEMAP_DECLARE
void  PATH_FINDERASTAR_DECLARE::SearchPos(int m_nIdPos ,int m_nIdPrePos,bool m_b)
{
	bool bBlock =  m_BlockFunc(m_pMap,stAStarPoint[m_nIdPos].m_PointPos);
	if(!bBlock)//�ж�Ŀ���Ƿ���ߣ���������
	{ 
		if(m_mCloseList.find(m_nIdPos)==m_mCloseList.end())   //close���Ҳ���			
		{
			if(m_mOpenList.find(m_nIdPos)!=m_mOpenList.end()) //����open����  �ж������㣬�ĸ�����ֵ����					
			{
				int k=10;
				if(m_b) k=14;
				if(stAStarPoint[m_nIdPrePos].m_nGvalue + k < stAStarPoint[m_nIdPos].m_nGvalue)
				{
					///////////////////////////////////////////////////////////////////////////////
					itTempOpen1 = m_mOpenTempList.find(stAStarPoint[m_nIdPos].m_nPointvalue);
					while(m_nIdPos != itTempOpen1->second)
					{
						itTempOpen1++;
					}
					itTempOpen2 = itTempOpen1;
					itTempOpen2++;
					m_mOpenTempList.erase(itTempOpen1,itTempOpen2);
					///////////////���ϴ��벻Ҫ������ҵ��ӽ������·��////////////////////////////

					stAStarPoint[m_nIdPos].pParent = &stAStarPoint[m_nIdPrePos];
					stAStarPoint[m_nIdPos].m_nGvalue =stAStarPoint[m_nIdPrePos].m_nGvalue + k;//С��
					stAStarPoint[m_nIdPos].m_nPointvalue=stAStarPoint[m_nIdPos].m_nGvalue+GetHValue(m_nIdPos);

					///////////////////////////////////////////////////////////////////////////////
					m_mOpenTempList.insert(OpenTempList::value_type(stAStarPoint[m_nIdPos].m_nPointvalue,m_nIdPos)); 	
					///////////////���ϴ��벻Ҫ������ҵ��ӽ������·��////////////////////////////
				}
			}	
			else
			{ 
				DoInsert(m_nIdPrePos,m_nIdPos,m_b);//����open����,�������
			}
		}
	}
}
/**
@name			: 
@brief			: 
*/
TEMPLATEMAP_DECLARE
void  PATH_FINDERASTAR_DECLARE::DoInsert(int nfromPre,int ntoNow,bool b)
{
	stAStarPoint[ntoNow].pParent = &stAStarPoint[nfromPre];
	stAStarPoint[ntoNow].m_nGvalue = GetGGValue(ntoNow,b);
	stAStarPoint[ntoNow].m_nPointvalue=stAStarPoint[ntoNow].m_nGvalue+GetHValue(ntoNow);
	m_mOpenList.insert(ntoNow);
	m_mOpenTempList.insert(OpenTempList::value_type(stAStarPoint[ntoNow].m_nPointvalue,ntoNow)); 
}
/**
@name			: 
@brief			: 
*/
TEMPLATEMAP_DECLARE
bool  PATH_FINDERASTAR_DECLARE::FindResult(int nEndId,int nEndPreId)
{
	stAStarPoint[m_nEnd].pParent = &stAStarPoint[nEndPreId];
	m_nPathCount=0;
	stPathNode  *pp = &stAStarPoint[m_nEnd];		
	while(pp) 
	{	
		m_PathTemp[m_nPathCount] = pp->m_PointPos;
		m_nPathCount++;
		pp = pp->pParent;	
	}
	//m_nPathCount--;			
	return true;
}

/**
@name			: 
@brief			: 
*/
TEMPLATEMAP_DECLARE
bool  PATH_FINDERASTAR_DECLARE::QueryResult(xs::Point*& lstPoint, int& count)
{
	lstPoint = 0;
	count = 0;
	count = m_nPathCount;
	for (int i = 0;i < m_nPathCount;i++)
	{
		m_PathResult[i] = m_PathTemp[m_nPathCount - i - 1];
	}
     lstPoint = &m_PathResult[0];
	//if (lstPoint)
	//{
	//	int n = m_nPathCount;
	//	stPathNode  *ppp = &stAStarPoint[m_nEnd];			
	//	while(ppp)
	//	{	
	//		n--;
	//		if( n<0 ) 
	//			break;
	//		lstPoint[n]=ppp->m_PointPos;
	//		ppp=ppp->pParent;				
	//	}
	//}
	return true;
}
#endif//__CPATH_FINDERBYASTAR_H__