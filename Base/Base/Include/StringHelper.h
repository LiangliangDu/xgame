/**
* Created by pk 2008.01.04
*/

#ifndef RKT_STRINGHELPER_H
#define RKT_STRINGHELPER_H

#include "Common.h"
#include <string>
#include <algorithm>

namespace xs {
	/**
		�ַ��������࣬��Ҫ���ڶ�һЩ���õ��ַ����Ĳ���
		����������Ǿ�̬����
	*/
	class RKT_EXPORT StringHelper
	{
	public:
		/// �滻�ַ�
		static void replace(std::string& str, char _Old, char _New)
		{
			size_t _Pos = std::string::npos;
			while (str[++_Pos])
			{
				if (str[_Pos] == _Old)
					str[_Pos] = _New;
			}
		}

		/// �滻�ַ���
		static void replace(std::string& str, const std::string& _Old, const std::string& _New)
		{
			size_t _Oldlen = _Old.length();
			if (_Oldlen == 0)
				return;

			size_t _Newlen = _New.length();
			size_t _Pos = std::string::npos;
			_Pos = str.find(_Old.c_str(), _Pos + 1);
			while (_Pos != std::string::npos)
			{
				str.replace(_Pos, _Oldlen, _New.c_str(), _Newlen);
				_Pos += _Newlen - _Oldlen;
				_Pos = str.find(_Old.c_str(), _Pos + 1);
			}
		}

        //  �滻�ַ�����ֻ����һ���滻������
        static void ReplaceOnce(std::string& str, const std::string& _Old, const std::string& _New)
        {
            size_t _Oldlen = _Old.length();
            if (_Oldlen == 0)
            {
                ASSERT(false);
                return;
            }

            size_t _Newlen = _New.length();
            size_t _Pos = std::string::npos;
            _Pos = str.find(_Old.c_str(), _Pos + 1);
            if (_Pos != std::string::npos)
            {
                str.replace(_Pos, _Oldlen, _New.c_str(), _Newlen);
            }
        }

		/// ȥ��ͷβ�Ŀո�
		static void  trim(std::string& str,const std::string& val)
		{
			str.erase(0,str.find_first_not_of(val));
			str.erase(str.find_last_not_of(val)+val.size());
		}

		/// ��Сд�����е��ַ����Ƚ�
		static int casecmp(const std::string& str1, const std::string& str2)
		{
#if defined(_MSC_VER) && _MSC_VER >= 1400
			return ::_stricmp(str1.c_str(), str2.c_str());
#else
			return ::stricmp(str1.c_str(), str2.c_str());
#endif
		}

		/// ��ʽ��һ���ַ���
		static std::string& format(std::string& str, const char* _Format, ...)
		{
			va_list _Args;
			va_start(_Args, _Format);
			const size_t _Size = 1024;
			char _Tempbuf[_Size];
#if defined(_MSC_VER) && _MSC_VER >= 1400
			size_t _Ret = ::_vsnprintf_s(_Tempbuf, _Size - sizeof(char), 1024-1, _Format, _Args);
#else
			size_t _Ret = ::_vsnprintf(_Tempbuf, _Size - sizeof(char), _Format, _Args);
#endif
			if (_Ret == -1 || _Ret == _Size - sizeof(char))
			{
				_Tempbuf[_Size - sizeof(char)] = '\0';
			}
			va_end(_Args);
			str.assign(_Tempbuf);
			return str;
		}

		/// ת��������
		static int toInt(const std::string& str)
		{
			return ::atoi(str.c_str());
		}

		/// ת��������
		static long toLong(const std::string& str)
		{
			return ::atol(str.c_str());
		}

		/// ת����int64
		static int64 toInt64(const std::string& str)
		{
			return ::_atoi64(str.c_str());
		}

		/// ת���ɸ���
		static float toFloat(const std::string& str)
		{
			return (float)::atof(str.c_str());
		}

		/// ������ת�����ַ���
		static std::string& fromInt(std::string& str, int _Val, int _Radix = 10)
		{
			str.reserve(40);
#if defined(_MSC_VER) && _MSC_VER >= 1400
			::_itoa_s(_Val, (char*)str.c_str(), 40, _Radix);
#else
			str = _itoa(_Val, (char*)str.c_str(), _Radix);
#endif
			return str;
		}

		/// ������ת�����ַ���
		static std::string& fromLong(std::string& str, long _Val, int _Radix = 10)
		{
			str.reserve(40);
#if defined(_MSC_VER) && _MSC_VER >= 1400
			::_ltoa_s(_Val, (char*)str.c_str(), 40, _Radix);
#else
			str = _itoa(_Val, (char*)str.c_str(), _Radix);
#endif
			return str;
		}

		/// ��int64ת�����ַ���
		static std::string& fromInt64(std::string& str, int64 _Val, int _Radix = 10)
		{
			str.reserve(80);
#if defined(_MSC_VER) && _MSC_VER >= 1400
			::_i64toa_s(_Val, (char*)str.c_str(), 80, _Radix);
#else
			str = _i64toa(_Val, (char*)str.c_str(), _Radix);
#endif
			return str;
		}

		/// ��floatת�����ַ���
		static std::string& fromFloat(std::string& str, float _Val)
		{
			str.reserve(80);
#if defined(_MSC_VER) && _MSC_VER >= 1400
			::sprintf_s((char*)str.c_str(), 80, "%f", _Val);
#else
			::sprintf((char*)str.c_str(), "%f", _Val);
#endif
			return str;
		}

		/// ת����Сд
		static std::string& toLower(std::string& str)
		{
			std::transform(str.begin(), str.end(), str.begin(), ::tolower);
			return str;
		}

		/// ת���ɴ�д
		static std::string& toUpper(std::string& str)
		{
			std::transform(str.begin(), str.end(), str.begin(), ::toupper);
			return str;
		}
	};

/**��������
	std::string s1;
	StringHelper::format(s1, "ab����c%04d", 789);
	StringHelper::toUpper(s1);
	StringHelper::toLower(s1);

	int n = StringHelper::toInt("1234567890");
	int64 n64 = StringHelper::toInt64("1234567890123");
	float ff = StringHelper::toFloat("3.141592600");

	std::string sss;
	StringHelper::fromInt(sss, n);
	StringHelper::fromInt64(sss, n64);
	StringHelper::fromFloat(sss, ff);
	*/
}

#endif // RKT_STRINGHELPER_H