#include "CPriorityQueue.h"

#ifndef _CPRIORITY_QUEUE_HEADER_GUARD
#define _CPRIORITY_QUEUE_HEADER_GUARD
#include <algorithm>

template<typename T>
inline CPriorityQueue<T>::CPriorityQueue(const CPriorityQueue<T>& other) : sorted(other.sorted)
{
}

template<typename T>
CPriorityQueue<T>::CPriorityQueue(CPriorityQueue<T>&& other) : sorted()
{
	Swap(other);
}

template<typename T>
CPriorityQueue<T>::CPriorityQueue(std::initializer_list<T> IList) : sorted()
{
	for (const T& value : IList)
		Push(value);
}

template<typename T>
CPriorityQueue<T>::~CPriorityQueue()
{
}

template<typename T>
void CPriorityQueue<T>::Push(const T& value)
{
	sorted.end()->value = value;
	auto cur = sorted.begin();
	while (cur->value < value)
		cur = cur->next;
	sorted.InsertBefore(cur, value);
}

template<typename T>
void CPriorityQueue<T>::Pop()
{
	sorted.PopFront();
}

template<typename T>
void CPriorityQueue<T>::Swap(CPriorityQueue<T>& other)
{
	sorted.Swap(other.sorted);
}

#endif