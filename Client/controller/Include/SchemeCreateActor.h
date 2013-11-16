/*******************************************************************
** �ļ���:	SchemeCreateActor.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2008/2/27  16:57
** ��  ��:	1.0
** ��  ��:	�������ﴴ������
** Ӧ  ��:  	
	
**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once

#include "ISchemeEngine.h"
#include <string>

//  ���Դ��룺�޸�Ϊֱ�Ӷ�ȡxml�ļ����Ա��ڹ۲������ļ��޸ĵ�Ч����
//���ﴴ���������ýű�
//#define CREATEACTOR_SCHEME_FILENAME			"Data\\Scp\\CreateActorConfig.xmc"
#define CREATEACTOR_SCHEME_FILENAME			"Data\\Scp\\CreateActorConfig.xml"

//�������ﴴ������
struct SCreateActorCongfig
{
	std::vector<int> actorFaceIds[6];
	std::vector<int> actorClothesIds[6];
	std::vector<double> actorClothesIdScale[6];

	///�ͻ�����ʾ���
	int	selectGenderPlatForm[PERSON_VOCATION_MAX][2];//ѡ���Ա�ʱƽ̨��Դid
	std::string selectGenderPlatFormPath[PERSON_VOCATION_MAX][2];;//��Ӧ�ļ���
	int selectGenderPlatFormEffect[PERSON_VOCATION_MAX][2];//ѡ���Ա�ʱƽ̨��Ч��Դid
	std::string selectGenderPlatFormEffectPath[PERSON_VOCATION_MAX][2];//��Ӧ�ļ���
	int	selectGenderPerson[PERSON_VOCATION_MAX][2];//ѡ���Ա�ʱ������Դid
	std::string selectGenderPersonPath[PERSON_VOCATION_MAX][2];//��Ӧ�ļ���
	int	selectGenderPersonEffect[PERSON_VOCATION_MAX][2];//ѡ���Ա�ʱ������Ч��Դid
	std::string selectGenderPersonEffectPath[PERSON_VOCATION_MAX][2];//��Ӧ�ļ���
	int selectGenderPersonWeapon[PERSON_VOCATION_MAX][2];//����������Դid
	std::string selectGenderPersonWeaponPath[PERSON_VOCATION_MAX][2];//����������Դid·��
	std::string selectGenderBg[PERSON_VOCATION_MAX];//����ͼƬ
	std::string selectProfessionVideoFile[PERSON_VOCATION_MAX];//ѡ��ְҵ����Ƶ�ļ���ַ

	std::string	createActorDetailBackgroundImage;//������ɫ�����һ���ı���ͼƬ

	void Clear();
};

class CSchemeCreateActor : public SingletonEx<CSchemeCreateActor>, public ISchemeUpdateSink
{	
	SCreateActorCongfig	m_config; //������������
public:
	///////////////////////////////ISchemeUpdateSink///////////////////	
	/** CSV��������ʱ֪ͨ
	@param   pCSVReader����ȡCSV�ķ��ؽӿ�
	@param   szFileName�������ļ���
	@param   
	@return  
	@note     
	@warning ��Ҫ�ڴ˷����ͷ�pCSVReader����pTiXmlDocument,��Ϊһ���ļ���Ӧ���sink
	@retval buffer 
	*/ 
	virtual bool			OnSchemeLoad(ICSVReader * pCSVReader,const char* szFileName);

	/** XML��������ʱ֪ͨ
	@param   pTiXmlDocument����ȡXML�ķ��ؽӿ�
	@param   szFileName�������ļ���
	@param   
	@return  
	@note     
	@warning ��Ҫ�ڴ˷����ͷ�pCSVReader����pTiXmlDocument,��Ϊһ���ļ���Ӧ���sink
	@retval buffer 
	*/
	virtual bool			OnSchemeLoad(TiXmlDocument * pTiXmlDocument,const char* szFileName);

	/** ���ö�̬����ʱ֪ͨ
	@param   pCSVReader����ȡCSV�ķ��ؽӿ�
	@param   szFileName�������ļ���
	@param   
	@return  
	@note     
	@warning ��Ҫ�ڴ˷����ͷ�pCSVReader����pTiXmlDocument,��Ϊһ���ļ���Ӧ���sink
	@retval buffer 
	*/
	virtual bool			OnSchemeUpdate(ICSVReader * pCSVReader, const char* szFileName);

	/** ���ö�̬����ʱ֪ͨ
	@param   pTiXmlDocument����ȡXML�ķ��ؽӿ�
	@param   szFileName�������ļ���
	@param   
	@return  
	@note     
	@warning ��Ҫ�ڴ˷����ͷ�pCSVReader����pTiXmlDocument,��Ϊһ���ļ���Ӧ���sink
	@retval buffer 
	*/
	virtual bool			OnSchemeUpdate(TiXmlDocument * pTiXmlDocument, const char* szFileName);

	///////////////////////////////CSchemeBuff//////////////////////////
	/** ����ű�
	@param   
	@param   
	@return  
	*/
	bool					LoadScheme(void);

	/** �ر�
	@param   
	@param   
	@return  
	*/
	void					Close(void);

	/** 
	@param   
	@param   
	@return  
	*/
	const SCreateActorCongfig &	GetCreateActorScheme();

	/** 
	@param   
	@param   
	@return  
	*/
	CSchemeCreateActor(void);

	/** 
	@param   
	@param   
	@return  
	*/
	virtual ~CSchemeCreateActor(void);
};
