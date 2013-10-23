#ifndef __Manager_H__
#define __Manager_H__

#include <string>
#include <map>
/**
modified by  xxh 20091012
�޸����ݣ�Managerģ�洦���ַ���ʱ�����ַ��Ĵ�Сд���С���������һ��bug��������ú���del(pModel)������pModel���ļ���ΪTEST.MZ������ʱ
ManagedItem������Ϊtest.mz,��ʱ��ɾ����ʱ��ֻ��ɾ��items�����ݣ�ȴû��ɾ��names�����ݣ����manager�����ݵĲ�һ�¡�ԭ����������manager�ⲿ
��ΪTEST.MZ��test.mz��ָͬһ���ļ�����Managerȥ����Ϊ�������޸�Manager��ʹ�������ַ���Сд�����С�
�޸ķ�������wrapper��ManagerHelper_LowerStringMapȡ��std::map<std::string , IDTYPE>��ManagerHelper_LowerStringMap�����ڲ�ת��ΪСд��
������ʹ��manager���ַ����Ĵ�Сд�������ˡ�

*/

namespace xs
{
	/*! \addtogroup RenderEngine
	*  ��Ⱦ����
	*  @{
	*/

	/** added by xxh,
	һ��ģ��ʹ��std::map<std::string, class T> �Ĺؼ��ֶԴ�Сд�����С�
	����ʹ��manager�����ִ�Сд������
	*/
	template <class IDTYPE>
	class _RenderEngineExport ManagerHelper_LowerStringMap
	{
	private:
		std::map<std::string, IDTYPE> m_realMap;
	public:
		ManagerHelper_LowerStringMap() {}
		IDTYPE & operator[] ( const std::string  & key )
		{
			std::string _str(key);
			StringHelper::toLower( _str);
			return m_realMap[_str];
		}

		typename std::map<std::string , IDTYPE>::iterator end() { return m_realMap.end(); }

		typename std::map<std::string, IDTYPE>::const_iterator end() const { return m_realMap.end(); }

		typename std::map<std::string, IDTYPE>::const_iterator find( const std::string & str) const
		{
			std::string _str( str );
			StringHelper::toLower(_str );
			return m_realMap.find( _str );
		}

		typename std::map<std::string, IDTYPE>::iterator find ( const  std::string & str)
		{
			std::string _str( str );
			StringHelper::toLower(_str );
			return m_realMap.find(_str);
		}

		typename std::map<std::string, IDTYPE>::iterator erase( typename  std::map<std::string , IDTYPE>::const_iterator it)
		{
			return m_realMap.erase(it);
		}

		void clear() { m_realMap.clear(); }

	};

	/** �����ü����Ķ������λ����
	*/
	class _RenderEngineExport ManagedItem 
	{
	private:
		int m_i32Refcount;
	public:
		std::string m_strName;
		ManagedItem(const std::string& name);
		virtual ~ManagedItem();

		void  addRef();
		bool delRef();
	};

	/** �����ü����Ķ��������
	*/
	template <class IDTYPE>
	class _RenderEngineExport Manager 
	{
	protected: 
		//modified by xxh 20091012 , ��ManagerHelper_LowerStringMapȡ��std::map<std::string,IDTYPE>,ʵ��ȫ���ַ�ת��ΪСд��
		//std::map<std::string,IDTYPE>			names; 
		ManagerHelper_LowerStringMap<IDTYPE> names;

		std::map<IDTYPE,ManagedItem*>	items; 
		xs::Mutex	m_mutex; 

	public:
		Manager(){ }

		/** ɾ��һ������
		@param id ���������
		*/
		virtual void  del(IDTYPE id)
		{
			m_mutex.Lock();
			if (items.find(id) == items.end())
			{
				m_mutex.Unlock();
				return;
			}
			if (items[id]->delRef()) 
			{
				ManagedItem *i = items[id];
				std::string name = i->m_strName;
				doDelete(id);
				std::map<std::string,IDTYPE>::iterator it = names.find(name);
				if(it != names.end())names.erase(it);

				std::map<IDTYPE,ManagedItem*>::iterator it1 = items.find(id);
				if(it1 != items.end())items.erase(it1);
			}
			m_mutex.Unlock();
		}

		/** ��������ɾ������
		@param name ��������
		*/
		void  delByName(const std::string& name)
		{
			m_mutex.Lock();
			if (has(name)) del(get(name)); 
			m_mutex.Unlock();
		}

		/** ʵ�ʵ�ɾ������
		@param id Ҫɾ���Ķ���
		@remarks ��Ҫʵ�ִ˺�������������ɾ��
		*/
		virtual void  doDelete(IDTYPE id)
		{
		}

		/** �Ƿ����ĳ�����ƵĶ���
		@param name ����
		@return �Ƿ����
		*/
		bool has(const std::string& name)
		{
			m_mutex.Lock();
			bool ok = (names.find(name) != names.end());
			m_mutex.Unlock();
			return ok;
		}

		/** ��ö���
		@param name ����
		@return ����
		*/
		IDTYPE get(const std::string& name)
		{
			m_mutex.Lock();
			IDTYPE t = names[name];
			m_mutex.Unlock();
			return t;
		}

	protected:
		void  do_add(const std::string& name,IDTYPE id,ManagedItem* item)
		{
			m_mutex.Lock();
			names[name] = id;
			item->addRef();
			items[id] = item;
			m_mutex.Unlock();
		}
	};
	/** @} */
}

#endif

