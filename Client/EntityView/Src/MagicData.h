//==========================================================================
/**
* @file	  : MagicData.h
* @author : 
* created : 2008-3-13   16:45
* purpose : ��Ч�����ݽű�����
*/
//==========================================================================

#ifndef __MAGICDATA_H__
#define __MAGICDATA_H__

#include "MagicDef.h"

typedef RecordSet<MAX_SUBMAGIC_COUNT>	MagicData;

/// ��Ч���ݹ�����
class MagicDataManager : public SingletonEx<MagicDataManager>, public ISchemeUpdateSink
{
	MagicData*			mMagicDataArray[MAX_MAGIC_COUNT];

	//���ܱ༭ʹ��,add wangtao
	std::vector<std::string> mCsvFiledName;
	std::vector<int>         mCsvFiledType;

public:
	MagicDataManager();
	virtual ~MagicDataManager();

	// ISchemeUpdateSink
public:
	virtual bool OnSchemeLoad(ICSVReader * pCSVReader,const char* szFileName);
	virtual bool OnSchemeUpdate(ICSVReader * pCSVReader, const char* szFileName);
	virtual bool OnSchemeLoad(TiXmlDocument * pTiXmlDocument,const char* szFileName){return false;}
	virtual bool OnSchemeUpdate(TiXmlDocument * pTiXmlDocument, const char* szFileName){return false;}

	bool read(ICSVReader* csv);

	const MagicData* getMagicData(ulong index) const;
	const XlsValue& getValue(ulong id, ulong field) const;

	//Skill�༭, add wangtao
	uint getMagicDataId(uint array, uint set);
	const std::string& getMagicDataName(uint id);
	bool getMagicDataArrayIsValid(uint array);
	bool getMagicDataRowIsValid(uint array, uint set);
	void SetMagicData(uint id, float aniSpeed, uint aniTrans, std::string aniOffset, float aniScale, uint resId);
	const XlsRecord* getRecord(ulong id) const;
	void SaveMagicDataToCsv(const char* szFileName);

private:
	bool innerRead(ICSVReader* csv, MagicData** arr);
	void clearArray(MagicData** arr);
};

#endif // __MAGICDATA_H__