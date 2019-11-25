#pragma once
#include "CList.h"
#include <initializer_list>

template<typename T>
class CPriorityQueue // TODO: Remove stupid O(n) naive realization
{
private:
	CList<T> sorted;

public:
	CPriorityQueue() {}
	CPriorityQueue(const CPriorityQueue<T>& other);
	CPriorityQueue(CPriorityQueue<T>&& other);
	CPriorityQueue(std::initializer_list<T> IList);
	~CPriorityQueue();
	void Push(const T& value);
	void Pop();
	T& Top()
	{
		return sorted.Front();
	}
	const T& Top() const
	{
		return sorted.Front();
	}
	void Swap(CPriorityQueue<T>& other);
	size_t Size() const
	{
		return sorted.Size();
	}
	bool Empty() const
	{
		return sorted.Size() == 0;
	}
};

#include "CPriorityQueue.cpp"