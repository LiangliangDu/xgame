//==========================================================================
/**
* @file	  : Occupant.h
* @author : 
* created : 2008-1-21   10:32
* purpose : ռλ�����
*/
//==========================================================================

#ifndef __OCCUPANT_H__
#define __OCCUPANT_H__

#include "VariableLengthArray.h"


/**���վλ���б��ͷ��Ϣ
*/
struct COccupantTileListHeader
{
	/// ê��X
	short nOffAnchorX;

	/// ê��Y
	short nOffAnchorY;

	/// ռλ���б�Ŀ��
	ushort wWidth;

	/// ռλ���б�ĸ߶�
	ushort wHeight;
};


typedef VariableLengthArray<COccupantTileListHeader, uchar>			OccupantTileList;


/**ռλ����
*/
class Occupant
{
protected:
	OccupantTileList*			m_pOccupantTileList;

public:
	Occupant(void) : m_pOccupantTileList(0)
	{ }

	virtual ~Occupant(void)
	{
		setOccupantTileList(0);
	}


	/**���ռλ���б�
	@return ռλ���б�
	*/
	virtual OccupantTileList* getOccupantTileList(void) const 
	{ return m_pOccupantTileList;  }

	/**����ռλ���б�
	@param pList ռλ���б�ָ��
	@return �Ƿ�ɹ�
	*/
	virtual bool setOccupantTileList(const OccupantTileList* pList)
	{
		if (pList && !pList->isValid())
			return false;

		safeRelease(m_pOccupantTileList);

		if (pList == 0)
			return true;

		if (0 == (m_pOccupantTileList = OccupantTileList::create(pList->getArraySize())))
			return false;

		int nSize = pList->getMemSize();
		memcpy(m_pOccupantTileList, pList, nSize);

		return true;
	}
};


#endif // __OCCUPANT_H__