/******************************************************************
** �ļ���:	TooltipHelper.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008-4-16
** ��  ��:	1.0
** ��  ��:	tooltip helper			
** Ӧ  ��:  
******************************************************************/
#pragma once

struct SEquipmentViewInfo;
struct SMsgTeamViewTeamMemberData_SC;
struct SEventTeamViewMemberData_C;

enum ShopType
{
	NonShop = 0,	// �����̵�
	ShopCommon,		// �̵�ͨ��
	ShopReclaim,	// �̵�ع�
	ShopMax,		
};

//��ɫ����
#define TT_COLOR_WHITE      "#FFFFFF"
//#define TT_COLOR_RED		"#FF0000"
//#define TT_COLOR_GREEN		"#00FF00"
//#define TT_COLOR_BLUE		"#0000FF"
//#define TT_COLOR_PURPLE		"#8080FF"
//#define TT_COLOR_ORANGE		"#FFFF00"
#define TT_COLOR_GOLDYELLOW "#FFFF80"
#define TT_COLOR_YELLOW		"#FFFF80"
#define TT_COLOR_SMALT		"#0080FF"
#define TT_COLOR_HOAR		"#EEEEEE"

//����װ����ʾ��Ҫ����ɫ
#define TT_COLOR_CYAN			"#00FF89"
#define TT_COLOR_BLUE			"#0056FF"
#define TT_COLOR_GOLDEN			"#FFDE03"
#define TT_COLOR_DARK_GLODEN	"#B5973B"
#define TT_COLOR_ORANGE			"#FF7100"
#define TT_COLOR_FRESH_GREEN	"#00FF00"
#define TT_COLOR_GREEN			"#96E24C"
#define TT_COLOR_RED			"#FF001E"
#define TT_COLOR_PINK			"#FF69FF"
#define TT_COLOR_PURPLE			"#D300ED"
#define TT_COLOR_GRAY			"#A09F92"

class TooltipHelper
{
public:
	static const std::string HtmlStart;
	static const std::string HtmlEnd;
	static const std::string strVocation[PERSON_VOCATION_MAX+1];
	static const std::string strEquipClass[EQUIPMENT_SUBCLASS_MAX];
	static const std::string strEquipBrandColor[GOODS_BRAND_LEVEL_MAX_LEVEL];
	static const std::string strEquipBrandName[GOODS_BRAND_LEVEL_MAX_LEVEL];
	static const std::string strEquipSmeltSoulMilesStoneName[EQUIP_SMELT_SOUL_ATTRIB_MAX_NUM];
	static const std::string strPetPropType[2]; // սʿ����ʦ�ͣ�
	static const std::string strPetType[2]; // սʿ����ʦ�ͣ�
	static const std::string strPetGradeType[5]; // һ���嵵�Σ�
	

	// �ⲿͨ�ýӿ�
	static std::string getTooltip(IEntity *pEntity,ShopType isShop = NonShop,bool isCooling = false);

	//buff tool tip
	static std::string getBuffTooltip(IBuff *pBuf);

	/************************************************************************/
	/* ��װ����Ʒ����ʾ														*/
	/************************************************************************/
	static std::string getGoodsTooltip(IGoods *pEntity,ShopType isShop = NonShop,bool isCooling = false);

    //  ��ȡָ��ID����Ʒ����ʾ��Ϣ��
    //  ע�⣺����һ����ʱʵ�֣���Ϊ�˲���������ϵͳ����ؽ����У��ܷ�������ʾ������Ʒ����ʾ��Ϣ��
    //  ���ƵĴ������Ʒϵͳ��������ȷ���ٽ���ʵ�֣�
	static std::string getGoodsTooltip(long lGoodsID,DWORD flag = 0);

	//��Ҫ��ʾ�Ķ�����TooltipHelper::getGoodsTooltip ����ȫ��ͬ
	//���������Ҫ�Լ�����
	//NOTE����������iOnlineShopGoodsID ���̳ǵ���ƷID
	static std::string getOnlineShopGoodsTooltip(int iOnlineShopGoodsID);

	//��ȡ�򻯵���ʾ��Ϣ
	//NOTE����������iOnlineShopGoodsID ���̳ǵ���ƷID
	static std::string getOnlineShopGoodsShortCutTooltip(int iOnlineShopGoodsID, float fhtmlTableWidth);

	// �����Ʒ����ʾ��Ϣ
	static std::string getRidePetGoodsTooltip(IGoods *pEntity);

	/************************************************************************/
	/* װ����Ʒ����ʾ														*/
	/************************************************************************/
	static std::string getEquipTooltip(SEquipmentSchemeInfo* pEquipInfo);

	static std::string getEquipTooltip(IEquipment *pEntity,ShopType isShop = NonShop,bool isCooling = false);

	// ���ҵ���ʾ��Ϣ����������װ��������������Ϣ��Ҫ���¶���
	static std::string getBagTooltip(IEquipment *pEntity,ShopType isShop,bool isCooling);

	//normal equipment tooltip
	static std::string getCommonEquipTooltip(IEquipment *pEntity,ShopType isShop,bool isCooling);

	/************************************************************************/
	/* ���������ʾ															*/
	/************************************************************************/
	static std::string getPetSkillBookToolTip(IGoods *pEntity,ShopType isShop = NonShop,bool isCooling = false);

	static std::string getPetSkillBookToolTip(long lGoodsID);
    
	static std::string getPetToolTip(long lPetID);

	static std::string getPetTooltip(IPet *pEntity,bool isRelease = false);

	static std::string getPetTooltipRelease(IPet *pEntity,bool bRelease,int nTime,int nTimeLeaving);

	static std::string getRidePetTooltip(IPet* pEntity);

	static std::string getPetinIntensifyToolTip(IPet* pEntify, int increaSanctify, int nowStart);

	/************************************************************************/
	/* ����ģ��															*/
	/************************************************************************/
	// ��ȡָ��ID��������ʾ��Ϣ��
	static std::string getPriseToolTip(long lGoodsID,DWORD flag = 0);

	/************************************************************************/
	/* ����ģ�������tooltip												*/
	/************************************************************************/
	static std::string getEquipTooltipInChatList(IEquipment *pEntity,ShopType isShop = NonShop,bool isCooling = false);

	static std::string getGoodsTooltipInChatList(IGoods *pEntity,ShopType isShop = NonShop,bool isCooling = false);

	/************************************************************************/
	/* ����ģ���tooltip													*/
	/************************************************************************/
	// ��ȡָ���ȼ���Tip,ģ����츳ʱ��û��ȷ��ǰ����ɫ��ʵ��û��ѧ����Ӧ�ȼ��ļ���
	// ���lv������ָҪ��ȡ�ĵȼ���Ϣ
	static std::string getSkillTooltip(const SkillId& id, int lv=0, int tempGeniusPoint=0);

	// �ȼ�С��10��ʱ���츳��ҳ��tip����
	static std::string GetGeniusPageTooltipText();
	
	// ���ܷ��ڿ����ʱ����ʾ
	static std::string getSkillShortcutTip(const SkillId& id);

	static std::string getPetSkillToolTip(IPet *pEntity,const SkillId& id);
	static std::string getPetSkillShortCutTip(IPet *pEntity,const SkillId& id);

	// �󷨼��ܵ���ʾ
	static std::string getPosSkillToolTip(int nID);
	/************************************************************************/
	/* pkģ���tooltip                                                      */
	/************************************************************************/
	static std::string getPKModeToolTip(int nMode, bool isActive);

	/************************************************************************/
	/* html�����ⶨ��														*/
	/************************************************************************/
	static std::string GetEquipToolTipByLinkInfo(const std::string & linkinfo);

	static std::string getGoodsTooltipByLinkInfo(const std::string & linkinfo);

	static std::string parseDesc(const char* pDesc);

	static std::string FormatHtmlEquipInfo(SEquipmentViewInfo *pInfo);

	/************************************************************************/
	/* �ڲ����ܺ���															*/
	/************************************************************************/
	static std::string getProfessionName(int nProfession);	

	static bool getGemsDamageProp(long gemsid, long & propid, long val);

	static std::string GetCombatHtmlInfo(SMsgActionPropInfo *pViewInfo);

public:
	static int s_fontWidth;	
	
	static const string s_imageGold,s_imageSilver,s_imageCopper;

private:
	static float GetPkNameColorBase();

	static std::string	 GetBindDescribe(IEntity* pEntity);

	static std::string   GetBindDescribebyID(int goodid,int blandflag);

	static bool  HasBindFlage(int blandflag,int flag);

	static bool  HasGoodsFlag(int goodflag,int flag);

	static std::string GetGoodSubClass(int nSubClass);

	static std::string  GetUseTerm(long lTime);

public:
	static std::string  GetGoodPrice(long lPrice);
};