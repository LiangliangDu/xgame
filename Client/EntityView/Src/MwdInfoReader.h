//==========================================================================
/**
* @file	  : MwdInfoReader.h
* @author : 
* created : 2008-6-11   13:21
* purpose : MWD��Ϣ�ļ�������
*/
//==========================================================================

#ifndef __MWDINFOREADER_H__
#define __MWDINFOREADER_H__

#include "MwdInfo.h"

class MwdInfoReader : public SingletonEx<MwdInfoReader>
{
	typedef HashMap<ulong, TableItem>	InfoMap;
	InfoMap	mInfoMap;
	uchar*	mData;
public:
	MwdInfoReader() : mData(0) { }
	~MwdInfoReader()
	{
		safeDelete(mData);
	}

	bool load(const char* filename)
	{
		if (!filename || *filename == 0)
			return false;

		// ���ܵ��������
		if (mData)
			safeDelete(mData);
		if (mInfoMap.size())
			mInfoMap.clear();

		// ��������
		Stream* stream = getFileSystem()->open(filename);
		if (!stream)
			return false;

		// ���ļ�ͷ
		MwdInfoHeader header;
		if (!stream->read(&header, sizeof(header)))
			goto ReadErr;

		// У���ļ�ͷ
		if (header.mask != 'OFNI' || header.version != 1)
			goto ReadErr;
		if (stream->getLength() - header.tableOff != header.itemCount * (sizeof(ulong) + sizeof(TableItem)))
			goto ReadErr;

		// ��ȡ��������
		size_t dataLen = header.tableOff - sizeof(header);
		mData = new uchar[dataLen];
		if (!stream->read(mData, dataLen))
			goto ReadErr;

		// ��ȡӳ���
		for (ulong i=0; i<header.itemCount; i++)
		{
			ulong id;
			if (!stream->read(&id, sizeof(id)))
				goto ReadErr;

			TableItem item;
			if (!stream->read(&item, sizeof(item)))
				goto ReadErr;

			mInfoMap[id] = item;
		}

		stream->close();
		stream->release();
		return true;

ReadErr:
		safeDelete(mData);
		if (stream)
		{
			stream->close();
			stream->release();
		}
			
		return false;
	}

	const MwdInfo* find(const std::string& mwdFile) const
	{
		ulong id = STR2ID(mwdFile.c_str());
		InfoMap::const_iterator it = mInfoMap.find(id);
		if (it != mInfoMap.end()) // found
		{
			const TableItem& item = (*it).second;
			return (const MwdInfo*)&mData[item.offset];
		}

		return NULL;
	}
};

#endif // __MWDINFOREADER_H__