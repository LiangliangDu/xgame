#ifndef __I_ConfigManager_H__
#define __I_ConfigManager_H__
#include "UserInfoDef.h"
struct IConfigManager
{

	/** �����¼�ķ���������n
	@param  	@param  
	*/
	virtual int GetLastLoginServerCount() = 0;

	/** ���������¼�ķ���������n��ʹ���±�0��n-1��ȡ���Ӧ�ķ�������
	��Ϊͬʱ���ص������ͷ��������е��鷳���ʲ����±������ȡ ��������GetNext��ʵ�ַ�ʽ
	@param  iIndex�� �±�
	@param  
	*/
	virtual const std::string&  GetLastLoginAreaName(int iIndex) = 0;


	/** ���������¼�ķ���������n��ʹ���±�0��n-1��ȡ���Ӧ�ķ�����������
	@param  iIndex�� �±�
	@param  
	*/
	virtual const std::string&  GetLastLoginServerName(int iIndex) = 0;

	//�������������������
	virtual void saveLastLoginAreaServer(const std::string& strArea, const std::string& strServer) = 0;

	///�Ƿ񱣴��û���
	virtual bool isSaveUserName() = 0;

	///��ñ�����û���
	virtual const std::string& getUserName() = 0;

	///���ñ����û���
	virtual void setSaveUserName(bool save) = 0;

	///���ñ�����û���
	virtual void setUserName(const std::string& username) = 0;

	///��ȡ��Ⱦϵͳ����
	virtual RenderSystemType getRenderSystemType() = 0;

	//������Ⱦϵͳ����
	virtual void setRenderSystemType(RenderSystemType type) = 0;

	//���ñ���ȫ��ģʽ
	virtual void setSystemSetFullScreen(bool bSet) = 0;

	//���ñ��洰��ģʽ
	virtual void setSystemSetWindowType(bool bSet) = 0;

	//���ñ��洰��ģʽ����ֵ
	virtual void setSystemSetWindowTypeValue(int nTypeValue_x,int nTypeValue_y) = 0;

	//���ñ�����Ӱ
	virtual void setSystemSetShadow(bool bSet) = 0;

	//���ñ��洹ֱͬ��
	virtual void setSystemSetSynchronization(bool bSet) = 0;

	//���ñ�������Ч��
	virtual void setSystemSetWeather(bool bSet) = 0;

	//���ñ�����ʾ�ܱ����
	virtual void setSystemSetShowAllPerson(bool bSet) = 0;

	//���ñ��汳������
	virtual void setSystemSetBackGMusic(bool bSet) = 0;

	//���ñ�����Ϸ��Ч
	virtual void setSystemSetGameSound(bool bSet) = 0;

	// ���þ���
	virtual void setSystemSetMulte(bool bSet) = 0;

	//���ñ��汳������ֵ
	virtual void setSystemSetBackGMusicValue(int nValue) = 0;

	//���ñ�����Ϸ��Чֵ
	virtual void setSystemSetGameSoundValue(int nValue) = 0;

	//��ȡ����ȫ��ģʽ
	virtual bool getSystemSetFullScreen() = 0;

	//��ȡ���洰��ģʽ
	virtual bool getSystemSetWindowType() = 0;

	//��ȡ���洰��ģʽ����ֵx
	virtual int  getSystemSetWindowTypeValue_x() = 0;

	//��ȡ���洰��ģʽ����ֵy
	virtual int  getSystemSetWindowTypeValue_y() = 0;

	//��ȡ������Ӱ
	virtual bool getSystemSetShadow() = 0;

	//��ȡ���洹ֱͬ��
	virtual bool getSystemSetSynchronization() = 0;

	//��ȡ��������
	virtual bool getSystemSetWeather() = 0;

	//��ȡ������ʾ�ܱ����
	virtual bool getSystemSetShowAllPerson() = 0;

	//��ȡ���汳������
	virtual bool getSystemSetBackGMusic() = 0;

	//��ȡ������Ϸ��Ч
	virtual bool getSystemSetGameSound() = 0;

	// ��ȡ����
	virtual bool getSystemSetMulte() = 0;

	//��ȡ���汳������ֵ
	virtual int getSystemSetBackGMusicValue() = 0;

	//��ȡ������Ϸ��Чֵ
	virtual int getSystemSetGameSoundValue() = 0;

	//���õ�ǰ�����
	virtual void setUserRidePlace(dbid dbidPerson, int nPlace) = 0;

	//��ȡ��ǰ�����
	virtual int  getUserRidePlace(dbid dbidPerson) = 0;

};

struct IServerListConfig
{
	/** ��ȡ��������
	@param   
	@param  
	*/
	virtual int GetAreaCount(void) = NULL;

	/** ���ݷ�������n��ʹ���±�0��n-1��ȡĳ��������
	@param  iAreaIndex�� �����±�
	@param  
	*/
	virtual const std::string&  GetAreaName(int iAreaIndex) = NULL;

	/** ���ݷ�������n��ʹ���±�0��n-1��ȡĳ�������������������
	@param  iAreaIndex�� �����±�
	@param  
	*/
	virtual int GetServerCount(int iAreaIndex) = NULL;


	/** ʹ���±��ȡ ĳ�������� ĳ������������
	@param  iAreaIndex�� �����±�
	@param  iServerIndex ���������±�
	*/
	virtual const std::string&  GetServerName(int iAreaIndex, int iServerIndex) = NULL;


	//////////////////////////////////////////////////////////////////////////////////
	/** ���Ƽ��ķ���������n
	@param  	@param  
	*/
	virtual int GetRecommendedServerCount() = NULL;

	/** ���ݱ��Ƽ��ķ���������n��ʹ���±�0��n-1��ȡ���Ӧ�ķ�������
	@param  iIndex�� �����±�
	@param  
	*/
	virtual const std::string&  GetRecommendedAreaName(int iIndex) = NULL;


	/** ���ݱ��Ƽ��ķ���������n��ʹ���±�0��n-1��ȡ���Ӧ�ķ�����������
	@param  iIndex�� �±�
	@param  
	*/
	virtual const std::string&  GetRecommendedServerName(int iIndex) = NULL;
	////////////////////////////////////////////////////////////////////////////////////

	/** ���ݷ������֣������������֣���λ��ĳ����ķ���������ȡ�������������������ip���˿���ֵ��С���Ǹ�
	@param  strAreaName�� ��������
	@param  strServerName ������������
	@param  strIpOut�� ����Ͳ�����������������IP
	@param  iPortOut �����������ƣ�������������Port
	*/
	virtual bool FindMinHost(const std::string& strAreaName, const std::string &strServerName, std::string &strIpOut, int &iPortOut) = NULL;


	/** ���ݷ������֣������������֣���λ��ĳ����ķ���������ȡ�����������ip���˿�,�����ص�ʱ���������һ��
	@param  strAreaName�� ��������
	@param  strServerName ������������
	@param  strIpOut�� ����Ͳ�����������������IP
	@param  iPortOut �����������ƣ�������������Port
	*/
	virtual bool FindHost(const std::string& strAreaName, const std::string &strServerName, std::string &strIpOut, int &iPortOut) = NULL;


	//////////////////////////////////////////////////////////////////////////////
	//��ȡ���õĳ�������ip/port
	virtual void GetSuperCenterHost(std::string &strIpOut, int &iPortOut) = NULL;

	/** ����ĳ������������������
	@param  dwServerAddr�� ��������ַ
	@param  wServerPort ���������˿�
	@param  dwOnlineNum�� ��������
	*/
	virtual bool UpdateOnlineNum(DWORD dwServerAddr, WORD wServerPort, DWORD dwOnlineNum) = NULL;


	/** ���÷������б����������Ѿ�����
	@param  bFlag�� ��������ַ
	*/
	virtual void SetServerListStatusUpdated(bool bFlag= true) = NULL;

	/** ʹ���±��ȡ ĳ�������� ĳ������������
	@param  iAreaIndex�� �����±�
	@param  iServerIndex ���������±�
	*/
	virtual DWORD   GetServerOnlineNum(int iAreaIndex, int iServerIndex) = NULL;

	/** ͨ�������� ���÷������������������ ����ȡĳ����������������
	@param strArea��	�������������"����һ��"
	@param strServer��  ���������ĳ���������Ʊ���"������"
	*/
	virtual DWORD   GetServerOnlineNumByName(const std::string& strArea, const std::string & strServer) = NULL;

	/** ͨ�������� ���÷������������������ ���жϸ÷������Ƿ��Ƽ�
	@param strArea��	�������������"����һ��"
	@param strServer��  ���������ĳ���������Ʊ���"������"
	*/
	virtual int   CheckServerRecommendedByName(const std::string& strArea, const std::string & strServer) = NULL;
	///////////////////////////////////////////////////////////////////////////////

	//ɾ���Լ�
	virtual void release(void) = NULL;
};
#endif