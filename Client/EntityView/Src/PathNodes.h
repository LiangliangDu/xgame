//==========================================================================
/**
* @file	  : PathNodes.h
* @author : 
* created : 2008-1-31   16:16
* purpose : ����·���ڵ�
*/
//==========================================================================

#ifndef __PATHNODES_H__
#define __PATHNODES_H__

/// ר�õ�·���ڵ�ģ�壬������ͨ��ģ�壬���ƶ����ר��
template <class T>
class PathNodes
{
	T*		_nodes;		/// �ڵ�����
	size_t	_current;	/// ��ǰ�ڵ�λ��
	size_t	_count;		/// �ڵ���Ŀ
	size_t	_capacity;	/// ���ڵ�����

public:
	PathNodes() 
		: _nodes(0), _count(0), _capacity(0), _current(0)
	{}

	~PathNodes()
	{ safeDeleteArray(_nodes); }

	void clear()	{ _count = _current = 0; }

	/// Ԥ�ÿռ�
	void reserve(size_t count)
	{
		grow(count - _count);
	}

	/// ����һ���ڵ��ں���
	void add(const T& node)
	{
		grow(1);
		_nodes[_count++] = node;
	}

	/// ���һ���ڵ�����
	void add(const T* nodes, size_t count)
	{
		if (nodes && count > 0)
		{
			grow(count);
			memcpy(_nodes+_count, nodes, count*sizeof(T));
			_count += count;
		}
	}

	const T& front() const	{ return _nodes[0]; }
	const T& cur() const	{ return _nodes[_current]; }
	const T& next() const	{ return _nodes[_current+1]; }
	const T& back() const	{ return _nodes[_count-1]; }

	void operator++()		{ ++_current; }
	bool isLast() const		{ return _current + 1 == _count; }
	bool empty() const		{ return size() == 0; }
	void trimRight(size_t pos)	{ _nodes[0] = _nodes[_current]; _count = 1;_current=0; }

	size_t size() const		{ return _count; }
	size_t capacity() const { return _capacity; }
	size_t current() const	{ return _current; }

private:
	inline void grow(size_t count)
	{
		if (_count + count > _capacity)
		{
			_capacity = _count + count;
			T* new_nodes = new T[_capacity];
			if (_count > 0)
				memcpy(new_nodes, _nodes, _count * sizeof(T));
			if (_nodes) delete[] _nodes;
			_nodes = new_nodes;
		}
	}
};

#endif // __PATHNODES_H__