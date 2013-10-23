/**
* Created by pk 2008.01.04
*/

#ifndef RKT_AUTOSTRING_H
#define RKT_AUTOSTRING_H

#include "Common.h"
#include <string>


#ifdef _MSC_VER
#	pragma warning(push)
#	pragma warning(disable:4267 4275 4251)
#endif

namespace xs {

	/*
	*	��������:
	*  1.�̳���std::string��ӵ�и�������й��ܣ�
	*  2.����c_wstr()������ʹ֮�Զ�ת���ʹ洢ת����Ľ����
	*  3.�Ƽ���ת��ǰ������ַ����ı༭������������Ҫ��ʽ���� clear_wstr ����Ѿ�ת����wchar����
	*  4.Ϊ�˼򵥺��ã�û�а�wstr��ԭʼ�ַ�������ͬ�����£�һ�㶼���ڻ��Ƶ�ʱ��ת��һ�¼���
	*/
	class RKT_EXPORT autostring : public std::string
	{
	public:
		typedef std::string::size_type size_type;

	private:
		const wchar_t* wstr;	/// ���ڼ�¼����ת����ĵ�ַ


		// ���죨������
	public:
		autostring();
		autostring(const autostring& _Right);
		autostring(const autostring& _Right, size_type _Roff, size_type _Count = std::string::npos);
		autostring(const std::string& _Right);
		autostring(const std::string& _Right, size_type _Roff, size_type _Count = std::string::npos);
		autostring(const char* _Ptr);
		autostring(const char* _Ptr, size_type _Count);
		autostring(const char* _Ptr, size_type _Roff, size_type _Count);
		autostring(char _Ch);
		autostring(size_type _Count, char _Ch);

		~autostring();

/*
		// ����
	public:
		autostring& operator=(const autostring& _Right);
		autostring& operator=(const std::string& _Right);
		autostring& operator=(const char* _Ptr);
		autostring& operator=(char _Ch);
		autostring& operator+=(const autostring& _Right);
		autostring& operator+=(const std::string& _Right);
		autostring& operator+=(const char *_Ptr);
		autostring& operator+=(char _Ch);*/

		// ת��
	public:
		const wchar_t* c_wstr();
		void clear_wstr();

	public:
		static const wchar_t* to_wchar(const char* str);

	private:
		void convert();
	};

} // namespace xs

/********************** ����ת���� ***********************************/
/*
////////////////////////////////////////////////////////////////////////////////
// �ַ�����ϣ����,����Ը�д
#if defined(RKT_COMPILER_MSVC) && RKT_COMPILER_VER >= 1300
namespace stdext
{
	inline size_t hash_value(const xs::autostring& _Str)
	{
		#define _HASH_SEED	(size_t)0xdeadbeef

		size_t _Val = _HASH_SEED;
		size_t _Size = _Str.size();
		if (0 < _Size)
		{	// add one or more elements
			size_t _Stride = (_Size / 16) + 1;
			_Size -= _Stride;	// protect against _Size near _Str.max_size()
			for(size_t _Idx = 0; _Idx <= _Size; _Idx += _Stride)
				_Val += (size_t)_Str[_Idx];
		}
		return (_Val);
	};
}
#elif defined(RKT_COMPILER_GNUC) && RKT_COMPILER_VER >= 310
#include <ext/hash_map>
namespace __gnu_cxx
//namespace std
{
	template <> struct hash< const xs::autostring& >
	{
		size_t operator()( const xs::autostring& _Str ) const
		{
			#define _HASH_SEED	(size_t)0xdeadbeef

			size_t _Val = _HASH_SEED;
			size_t _Size = _Str.size();
			if (0 < _Size)
			{	// add one or more elements
				size_t _Stride = (_Size / 16) + 1;
				_Size -= _Stride;	// protect against _Size near _Str.max_size()
				for(size_t _Idx = 0; _Idx <= _Size; _Idx += _Stride)
					_Val += (size_t)_Str[_Idx];
			}
			return (_Val);
		}
	};

	template<>
	struct hash<std::string>
	{
		size_t operator()(std::string __s) const
		{ return __stl_hash_string(__s.c_str()); }
	};	
}
#endif
*/
#ifdef _MSC_VER
#	pragma warning(pop)
#endif


#endif