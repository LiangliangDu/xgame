/**
	Created 2007.6.7 by pk
	Email: pk163@163.com
*/

#ifndef RKT_OSTRBUF_H
#define RKT_OSTRBUF_H

#include <stdlib.h>
#include <utility>
#include <string>

namespace xs {

/** 
	ʾ��
	
	@code

	int dosomething(char* dest_buf, int max_size)
	{
		char buf[] = "some thing some thing some thing some thing ";
		int actualCpySize = max_size / 2 + 1;
		memcpy(dest_buf, buf, actualCpySize);
		return actualCpySize;
	}

	void test_ostrbuf()
	{
		ostrbuf osb;

		// ����»�������������ֱ������һ��
		//osb.reserve(1024);

		// ��Щ��������ostream�Ĺ���
		osb<<(uint)0xffffffff<<","<<(int)0x80000001<<endl;// endl�����з�
		osb<<99<<","<<(short)14<<","<<-15<<endl;
		osb<<(int64)0x8000000000000001<<","<<(uint64)0xffffffffffffffff<<endl;
		osb<<15.1367891024f<<","<<9999.123456789<<endl;

		 // ��һ���ַ������Ӵ�д��
		osb<<ostrbuf::substr("������������abcdefg", 12)<<endl;

		// ���Ƶĸ�ʽ��
		osb<<ostrbuf::formatf("%02.6f", 3.1415926f)<<endl;
		osb<<_fi("%04d", 25)<<endl; // ����д�������
		osb<<_fi("%X", 255)<<endl;


		// ֱ�Ӳ���������ʾ�����ڲ�֪�������²��Ƽ�����������֪�������£�Ҳ�����ܷ��㣬���������ַ�������������
		osb.grow(64);	// ������Ҫ128�ֽڿռ䣬�����ֵ������ȷ���ܷ�ֹ����Խ��
		int off = dosomething(osb.cur(), 64); // dosomething �Ѿ���ȫ�׿��� ostrbuf �࣬�����κξ�����Σ�գ�
		osb.seek(off);	// �ֶ���λ��seek����ȷλ��
		osb<<ends;		// ������� dosomething û���ڻ�����������'\0'�����ﲻ�����ǣ������� dosomething ����ֱ�ӶԻ���������д�⣬�����Ĳ��������Զ���'\0'

		std::cout<<osb.c_str();
	}

	//���:
	4294967295,-2147483647
	99,14,-15
	-9223372036854775807,18446744073709551615
	15.136789,9999.123457
	������������
	3.141593
	0025
	FF
	some thing some thing some thing 

	@endcode
*/

/**
	�ַ���������壬��������ostream�������Ӽ��

	@param _GrowBytes �������ĵ�����С
	@param _ArrSize �ڲ����ַ�����Ĵ�С�������ַ�������������ʱ����new�������Ļ�����
*/
template <int _GrowBytes, int _ArrSize = 64>
class basic_ostrbuf
{
private:
	enum {_MyGrowBytes = _GrowBytes > 0 ? ((_GrowBytes + 7) & ~7) : 256};
	enum {_MyArrSize = _ArrSize > 0 ? ((_ArrSize + 7) & ~7) : 64};
	enum {_LongMaxLength = 16-1, _Int64MaxLength = 24-1, _DoubleMaxLength = 48-1}; // 8*n-1

	char*	_buf;				/// ������
	size_t	_pos;				/// ��ǰд��λ��
	size_t	_cap;				/// ����������
	char	_arr[_MyArrSize];	/// �ַ����飬������С������ʱ��������������������û��Ҫnew�ڴ�


	/// �����û��Զ���ĸ�ʽ��������sprintf�����ĸ�ʽ������
public:
	template<class T>
	struct format 
	{
		const char* _f;
		T _v;
		format(const char* f, const T& v) : _f(f), _v(v) { }
	};

	typedef format<float>					formatf;
	typedef format<double>					formatd;
	typedef format<int>						formati;
	typedef format<__int64>					formati64;
	typedef std::pair<const char*, size_t>	substr;

	// ���죨������
public:
	basic_ostrbuf() : _buf(_arr), _pos(0), _cap(_MyArrSize)
	{
		_arr[0] = 0;
	}
	~basic_ostrbuf()
	{
		if (_buf != _arr) delete[] _buf;
	}

	// ��������
public:
	void clear()
	{
		grow(1);
		_pos = 0;
		_buf[_pos] = 0;
	}

	char* str() const				{ return _buf; }
	const char* c_str() const		{ return _buf; }
	size_t length() const			{ return _pos; }
	size_t capacity() const			{ return _cap; }
	char* cur() const				{ return _buf + _pos;}
	basic_ostrbuf& seek(int offset)
	{
		int new_pos = (int)_pos + offset;
		if (new_pos >= (int)_cap) new_pos = (int)_cap - 1;
		if (new_pos < 0) new_pos = 0;
		_pos = (size_t)new_pos;
		return (*this);
	}

	/// Ԥ��һ���û��趨�Ļ����С�����ڴ󻺳����֪��С�Ļ��壬�����ַ������Լ���new/delete�Ĵ�����
	void reserve(size_t length)
	{
		if (length >= _cap)
			grow(length - _pos);
	}

	// operator<<
public:
	/// ����endl��ends
	basic_ostrbuf& operator<<(basic_ostrbuf& (__cdecl * fn)(basic_ostrbuf&)) 
	{
		return ((*fn)(*this));
	}

	/// ������һ������
	basic_ostrbuf& operator<<(const basic_ostrbuf& other)
	{
		return push(other.c_str(), other.length());
	}


	/// �����ַ���
	basic_ostrbuf& operator<<(const char* str)
	{
		return (str ? push(str, strlen(str)) : (*this));
	}
	/// ����һ���Ӵ�
	basic_ostrbuf& operator<<(const substr& str)
	{
		return push(str.first, str.second);
	}
	/// ����std::string����
	basic_ostrbuf& operator<<(const std::string& str)
	{
		return push(str.c_str(), str.length());
	}
	/// ����һ���ַ�
	/// ע������c���ַ���������0-255�����ִ���0-255�����֣���Ҫת��Ϊshort,int,long�Ƚ��д���
	basic_ostrbuf& operator<<(char c)
	{
		return put(c);
	}

	/// ��������
	basic_ostrbuf& operator<<(short int si)
	{
		return operator<<(long(si));
	}
	basic_ostrbuf& operator<<(unsigned short int usi)
	{
		return operator<<(unsigned long(usi));
	}
	basic_ostrbuf& operator<<(int __w64 i)
	{
#ifdef INT_64_BITS
		return operator<<(__int64(i));
#else
		return operator<<(long(i));
#endif
	}
	basic_ostrbuf& operator<<(unsigned int __w64 ui)
	{
#ifdef INT_64_BITS
		return operator<<(unsigned __int64(ui));
#else
		return operator<<(unsigned long(ui));
#endif
	}
	basic_ostrbuf& operator<<(long l)
	{
		grow(_LongMaxLength);
		_ltoa_s(l, cur(), _LongMaxLength, 10);
		_pos += strlen(cur());
		return (*this);
	}
	basic_ostrbuf& operator<<(unsigned long ul)
	{
		grow(_LongMaxLength);
		_ultoa_s(ul, cur(), _LongMaxLength, 10);
		_pos += strlen(cur());
		return (*this);
	}
	basic_ostrbuf& operator<<(__int64 i64)
	{
		grow(_Int64MaxLength);
		_i64toa_s(i64, cur(), _Int64MaxLength, 10);
		_pos += strlen(cur());
		return (*this);
	}
	basic_ostrbuf& operator<<(unsigned __int64 ui64)
	{
		grow(_Int64MaxLength);
		_ui64toa_s(ui64, cur(), _Int64MaxLength, 10);
		_pos += strlen(cur());
		return (*this);
	}
	basic_ostrbuf& operator<<(float f)
	{
		grow(_DoubleMaxLength);
		sprintf_s(cur(), _DoubleMaxLength, "%f", f);
		_pos += strlen(cur());
		return (*this);
	}
	basic_ostrbuf& operator<<(double d)
	{
		grow(_DoubleMaxLength);
		sprintf_s(cur(), _DoubleMaxLength, "%f", d);
		_pos += strlen(cur());
		return (*this);
	}

	/// ���Ƶĸ�ʽ��
	template<class T>
	basic_ostrbuf& operator<<(const format<T>& val)
	{
		grow(_DoubleMaxLength);
		sprintf_s(cur(), _DoubleMaxLength, val._f, val._v);
		_pos += strlen(cur());
		return (*this);
	}
public:
	void grow(size_t len)
	{
		if (_pos + len >= _cap)
		{
			// �����µĳߴ磬��8�ֽڶ���
			size_t new_size = _pos + len + 1;
			size_t new_cap = _cap ? _cap : _MyGrowBytes;
			while (new_cap < new_size)
				new_cap += _MyGrowBytes;
			new_cap = (new_cap + 7) & ~7;

			char* new_buf = new char[new_cap];
			if (_pos > 0)
			{
				memcpy(new_buf, _buf, _pos + 1);
				if (_buf != _arr)
					delete[] _buf;
			}
			else
				new_buf[0] = 0;

			_buf = new_buf;
			_cap = new_cap;
		}
	}
	basic_ostrbuf& put(char c)
	{
		grow(1);
		_buf[_pos] = c;
		if (c != 0)
			_buf[++_pos] = 0;
		return (*this);
	}
	basic_ostrbuf& push(const char* str, size_t len) // �ⲿ��֤ len <= strlen(str)
	{
		if (str && len > 0)
		{
			grow(len);
			memcpy(_buf + _pos, str, len);
			_buf[_pos += len] = 0;
		}
		return (*this);
	}
};



/// �ַ�����ֹ
template<int _GrowBytes, int _ArrSize>
inline basic_ostrbuf<_GrowBytes, _ArrSize>& _cdecl ends(basic_ostrbuf<_GrowBytes, _ArrSize>& osb)
{
	return osb.put('\0');
}

/// ����
template<int _GrowBytes, int _ArrSize>
inline basic_ostrbuf<_GrowBytes, _ArrSize>& _cdecl endl(basic_ostrbuf<_GrowBytes, _ArrSize>& osb)
{
	return osb.put('\n');
}

#if 0
/** 
	ʾ�����û��Զ������͵Ķ��Ʒ�������������������������Զ������ͣ�
	YourType  yt;
	ostrbuf<<yt;
*/
template<int _GrowBytes, int _ArrSize>
inline basic_ostrbuf<_GrowBytes, _ArrSize>& _cdecl operator<<(basic_ostrbuf<_GrowBytes, _ArrSize>& osb, const YourType& val)
{
	if (val.c_str())
		osb.push(val.c_str(), val.length());
	return osb;
}
#endif


typedef basic_ostrbuf<256, 256>		ostrbuf;


// Ϊ�˷���ʹ�ã��������� typedef
typedef ostrbuf::formatf	_ff;
typedef ostrbuf::formatd	_fd;
typedef ostrbuf::formati	_fi;
typedef ostrbuf::formati64	_fi64;
typedef ostrbuf::substr		_ss;

}

#endif // RKT_OSTRBUF_H