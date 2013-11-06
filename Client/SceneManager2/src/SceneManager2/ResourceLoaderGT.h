#ifndef __ResourceLoaderGT_H__
#define __ResourceLoaderGT_H__

#include "IResourceManager.h"

class ResourceLoaderGT : public IResourceLoader
{
public:
	ResourceLoaderGT(){}
public:
	//IResourceLoader
	virtual IResource* loadResource(const ulong uResID);
	virtual void  release();

	// ���صر���Դʱ��ͼID��Ϊ������һ���֣����ﲻ��Ҫ��ͼ�ļ�����hashֵ
	//ulong _hash;
};

#endif