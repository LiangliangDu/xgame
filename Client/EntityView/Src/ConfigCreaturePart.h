#ifndef __ConfigCreaturePart_H__
#define __ConfigCreaturePart_H__

enum
{
	PT_TEXTURE = 1,
	PT_MODEL = 2
};

struct CreaturePart
{
	std::string partType;	//�ϰ���
	int attachType;			//1=��ͼ,2=ģ��
	std::string name;		//���������߲�������
};

class ConfigCreaturePart : public ISchemeUpdateSink
{
public:
	// ISchemeUpdateSink
	virtual bool			OnSchemeLoad(ICSVReader * pCSVReader,const char* szFileName);
	virtual bool			OnSchemeLoad(TiXmlDocument * pTiXmlDocument,const char* szFileName);
	virtual bool			OnSchemeUpdate(ICSVReader * pCSVReader, const char* szFileName);
	virtual bool			OnSchemeUpdate(TiXmlDocument * pTiXmlDocument, const char* szFileName);
public:
	bool load(const char* fileName);
	CreaturePart *getByType(const std::string& partType);
protected:
	ConfigCreaturePart()
	{
	}
public:
	static ConfigCreaturePart*	Instance();
private:
	typedef HASH_MAP_NAMESPACE::hash_map<std::string,CreaturePart> CreaturePartMap;
	CreaturePartMap	m_cp;
};

#endif