/**
* Created by pk 2008.01.08
*/

#ifndef RKT_OBJECT_H
#define RKT_OBJECT_H

#include "Common.h"
#include "Trace.h"
#include <string>
#include <vector>


/**
	�������л�����
	
	@code

	// Foo.h
	#pragma once

	#include "Object.h"

	namespace xs {

		class Foo : public Object
		{
		public:
			DECL_SERIAL(Foo)

			int k;

			virtual void serialize(Archive& ar);
		};

	}

	// Foo.cpp
	#include "stdafx.h"
	#include "Foo.h"

	namespace xs {

		IMPL_SERIAL(Foo, Object)

		void Foo::serialize(Archive& ar)
		{
			Object::serialize(ar);

			if (ar.isStoring())
				ar<<k;
			else
				ar>>k;
		}
	}

	@endcode
*/



namespace xs {

	class Object;
	class Archive;

	/// ����ʱ��
	struct RKT_EXPORT RuntimeClass
	{
		std::string		className;		/// ����
		int				objSize;		/// ���С
		Object* (RKT_STDCALL* procCreateObject)(); /// ����������������ʱΪNULL

		/// ��̬��������
		Object* createObject();

		/// ��������ȡ����ʱ��
		static RuntimeClass* RKT_STDCALL fromName(const std::string& className);

		/// ͨ��������̬��������
		static Object* RKT_STDCALL createObject(const std::string& className);

		/// �洢����ʱ��
		void store(Archive& ar) const;

		/// ��������ʱ��
		static RuntimeClass* RKT_STDCALL load(Archive& ar);
	};

	/// ����ʱ����Զ�ע�����
	RKT_API void regClass(RuntimeClass* newClass);
	struct SRegClass
	{ SRegClass(RuntimeClass* newClass) { regClass(newClass); } };


	/// ������
	class RKT_EXPORT Object
	{
	public:
		static const RuntimeClass classObject;
	public:
		virtual RuntimeClass* getRuntimeClass() const
		{ return (RuntimeClass*)(&Object::classObject); }
		virtual ~Object() {}
		virtual void serialize(Archive& ar) {}

#pragma push_macro("new")
#undef new

		void* RKT_STDCALL operator new(size_t nSize)
		{ return ::operator new(nSize); }
		void* RKT_STDCALL operator new(size_t, void* p)
		{ return p; }
		void RKT_STDCALL operator delete(void* p)
		{ ::operator delete(p); };
		void RKT_STDCALL operator delete(void* p, void* pPlace)
		{ ::operator delete(p);	}
#pragma pop_macro("new")

	protected:
		Object() {}
	private:
		Object(const Object& objectSrc) {}
		void operator=(const Object& objectSrc) {}
	};


	// һЩ������
	#define GET_RUNTIME_CLASS(class_name) ((RuntimeClass*)(&class_name::class##class_name))

	#define DECL_DYNAMIC(class_name) \
	public: \
		static const RuntimeClass class##class_name; \
		virtual RuntimeClass* getRuntimeClass() const; \

	#define DECL_DYNCREATE(class_name) \
		DECL_DYNAMIC(class_name) \
		static Object* RKT_STDCALL createObject();

	#define DECL_SERIAL(class_name) \
		DECL_DYNCREATE(class_name) \
		friend Archive& operator<<(Archive& ar, const class_name*& obj);\
		friend Archive& operator>>(Archive& ar, class_name*& obj);

	#define IMPL_RUNTIMECLASS(class_name, base_class_name, pfnNew, class_init) \
		const RuntimeClass class_name::class##class_name = \
		{ #class_name, sizeof(class class_name), pfnNew/*, NULL */}; \
		RuntimeClass* class_name::getRuntimeClass() const \
		{ return GET_RUNTIME_CLASS(class_name); } \

	#define IMPL_DYNAMIC(class_name, base_class_name) \
		IMPL_RUNTIMECLASS(class_name, base_class_name, NULL, NULL)

	#define IMPL_DYNCREATE(class_name, base_class_name) \
		Object* RKT_STDCALL class_name::createObject() { return new class_name; } \
		IMPL_RUNTIMECLASS(class_name, base_class_name, class_name::createObject, NULL)

	#define IMPL_SERIAL(class_name, base_class_name) \
		IMPL_DYNCREATE(class_name, base_class_name)\
		SRegClass _reg_##class_name(GET_RUNTIME_CLASS(class_name)); \
		Archive& operator<<(Archive& ar, const class_name*& obj)\
		{ ar.writeObject(obj); return ar; }\
		Archive& operator>>(Archive& ar, class_name*& obj) \
		{ obj = (class_name*)ar.readObject(); return ar; } \


	/// �ĵ�
	/// ��������ֻ��Ҫ�ڴ��ĵ�������Ҫ�ļ��ĵ����ڴ��ĵ����Ա���Ϊ�ļ��ĵ�
	class RKT_EXPORT Archive
	{
	public:
		enum EMode {modeStore=0, modeLoad=1};	/// �ĵ�ģʽ
	private:
		enum LoadArrayObjType{ typeUndefined = 0, typeRuntimeClass = 1, typeObject = 2 };
		enum { NewClassTag = (int)0xffffffff };

		struct SLoadInfo
		{
			void* ptr;
			LoadArrayObjType type;

			SLoadInfo(void* p, LoadArrayObjType t) : ptr(p), type(t) {}
		};
		typedef HashMap<void*, int>					StoreMap;
		typedef std::vector<SLoadInfo>				LoadArray;

	protected:
		int			mMode;		/// �ĵ�ģʽ���洢���Ǽ��أ���
		uchar*		mBegin;		/// ��������ʼλ��
		uchar*		mCur;		/// ��������ǰλ��
		uchar*		mEnd;		/// ����������λ��

		union
		{
			LoadArray*	m_pLoadArray;	/// ���ڱ�����غ�Ķ���<���������ʱ��>
			StoreMap*	m_pStoreMap;	/// �洢�Ķ���ӳ��<���������ʱ��, ����>
		};

		
	public:
		Archive();
		Archive(uchar* buf, size_t bytes);
		~Archive();

		bool isLoading() const		{ return  (mMode & Archive::modeLoad) != 0; }
		bool isStoring() const		{ return  (mMode & Archive::modeLoad) == 0; }

		/// �ĵ��Ļ���
		uchar* data() const			{ return mBegin; }

		/// �ĵ�����Ч��С
		size_t size() const			{ return mCur - mBegin; }

		/// �ĵ����������
		size_t capacity() const		{ return mEnd - mBegin; }


		/// ����ĵ�����
		void clear();

		/// Ԥ���ĵ���С
		void reserve(size_t bytes);

		/// ������
		size_t read(void* buf, size_t bytes);

		/// д����
		void write(const void* buf, size_t bytes);

		/// ��λ��ǰ�α�
		void seek(int offset);

		
		/// ��ȡ����
		Object* readObject();

		/// д�����
		void writeObject(const Object* obj);


		/// ��ȡ����ʱ��
		RuntimeClass* readClass(int* objIndex = NULL);

		/// д������ʱ��
		void writeClass(const RuntimeClass* runtimeClass);
		//void serializeClass(const RuntimeClass* runtimeClass);

		friend Archive& RKT_STDCALL operator<<(Archive& ar, const Object* pOb);
		friend Archive& RKT_STDCALL operator>>(Archive& ar, Object*& pOb);
		friend Archive& RKT_STDCALL operator>>(Archive& ar, const Object*& pOb);

		// �����͵������������
		Archive& operator<<(bool v)
		{ return Archive::operator<<((uchar)(v ? 1 : 0)); }
		Archive& operator<<(char v)
		{ return Archive::operator<<((uchar)v); }
#ifdef _NATIVE_WCHAR_T_DEFINED
		Archive& operator<<(wchar_t v)
		{ return Archive::operator<<((ushort)v); }
#endif
		Archive& operator<<(short v)
		{ return Archive::operator<<((ushort)v); }
		Archive& operator<<(long v)
		{ return Archive::operator<<((ulong)v); }
		Archive& operator<<(int v)
		{ return Archive::operator<<((uint)v); }
		Archive& operator<<(int64 v)
		{ return Archive::operator<<((uint64)v); }
		Archive& operator<<(float v)
		{ Assert(isStoring()); grow(sizeof(float)); *(float*)mCur = v; mCur += sizeof(float); return *this; }
		Archive& operator<<(double v)
		{ Assert(isStoring()); grow(sizeof(double)); *(double*)mCur = v; mCur += sizeof(double); return *this; }
		Archive& operator<<(uchar v)
		{ Assert(isStoring()); grow(sizeof(uchar)); *(uchar*)mCur = v; mCur += sizeof(uchar); return *this; }
		Archive& operator<<(ushort v)
		{ Assert(isStoring()); grow(sizeof(ushort)); *(ushort*)mCur = v; mCur += sizeof(ushort); return *this; }
		Archive& operator<<(ulong v)
		{ Assert(isStoring()); grow(sizeof(ulong)); *(ulong*)mCur = v; mCur += sizeof(ulong); return *this; }
		Archive& operator<<(uint  v)
		{ Assert(isStoring()); grow(sizeof(uint)); *(uint *)mCur = v; mCur += sizeof(uint); return *this; }
		Archive& operator<<(uint64 v)
		{ Assert(isStoring()); grow(sizeof(int64)); *(int64*)mCur = v; mCur += sizeof(int64); return *this; }
		Archive& operator<<(const std::string& v)
		{ Assert(isStoring()); Archive::operator<<(v.length()); write(v.c_str(), v.length()); return *this; }

		Archive& operator>>(bool& v)
		{ uchar by; Archive& ar = Archive::operator>>(by); v = (by ? true : false); return ar; }
		Archive& operator>>(char& v)
		{ return Archive::operator>>((uchar&)v); }
#ifdef _NATIVE_WCHAR_T_DEFINED
		Archive& operator>>(wchar_t& v)
		{ return Archive::operator>>((ushort&)v); }
#endif
		Archive& operator>>(short& v)
		{ return Archive::operator>>((ushort&)v); }
		Archive& operator>>(long& v)
		{ return Archive::operator>>((ulong&)v); }
		Archive& operator>>(int& v)
		{ return Archive::operator>>((uint&)v); }
		Archive& operator>>(int64& v)
		{ return Archive::operator>>((uint64&)v); }
		Archive& operator>>(float& v)
		{ Assert(isLoading()); if (mCur+sizeof(float) <= mEnd) {v = *(float*)mCur; mCur += sizeof(float);} return *this; }
		Archive& operator>>(double& v)
		{ Assert(isLoading()); if (mCur+sizeof(double) <= mEnd) {v = *(double*)mCur; mCur += sizeof(double);} return *this; }
		Archive& operator>>(uchar& v)
		{ Assert(isLoading()); if (mCur+sizeof(uchar) <= mEnd) {v = *(uchar*)mCur; mCur += sizeof(uchar);} return *this; }
		Archive& operator>>(ushort& v)
		{ Assert(isLoading()); if (mCur+sizeof(ushort) <= mEnd) {v = *(ushort*)mCur; mCur += sizeof(ushort);} return *this; }
		Archive& operator>>(ulong& v)
		{ Assert(isLoading()); if (mCur+sizeof(ulong) <= mEnd) {v = *(ulong*)mCur; mCur += sizeof(ulong);} return *this; }
		Archive& operator>>(uint& v)
		{ Assert(isLoading()); if (mCur+sizeof(uint) <= mEnd) {v = *(uint*)mCur; mCur += sizeof(uint);} return *this; }
		Archive& operator>>(uint64& v)
		{ Assert(isLoading()); if (mCur+sizeof(int64) <= mEnd) {v = *(int64*)mCur; mCur += sizeof(int64);} return *this; }
		Archive& operator>>(std::string& v)
		{
			Assert(isLoading()); 
			size_t len;
			*this >> len;
			v.reserve(len);
			if (mCur + len > mEnd)
				len = mEnd - mCur;
			v.assign((const char*)mCur, len);
			mCur += len;
			return *this;
		}

	private:
		void grow(size_t n);
		void initContainer();
	};
}

#endif // RKT_OBJECT_H