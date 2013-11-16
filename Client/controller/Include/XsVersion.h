#include "cini.h"
namespace xs
{
	//��ȡversion.ini�ļ������ؿͻ��˵İ汾��
	const std::string& GetClientExeCurVersion(void)
	{
		static std::string s_strVersion;
		if (!s_strVersion.empty())
		{
			return s_strVersion;
		}

		std::string strMajor = "1";
		std::string strMinor = "0";
#define UPDATE_VERSON_FILE		("version.ini")

		cIni ini;
		if (ini.Load(UPDATE_VERSON_FILE))
		{
			ini.GetValue("version_major",strMajor);
			ini.GetValue("version_minor",strMinor);
		}

		s_strVersion = strMajor;
		s_strVersion += ".";
		s_strVersion += strMinor;
		return s_strVersion;

	};
};