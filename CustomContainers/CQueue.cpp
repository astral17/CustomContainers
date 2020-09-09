#include "CQueue.h"

#ifndef _CQUEUE_HEADER_GUARD
#define _CQUEUE_HEADER_GUARD
#include <algorithm>

template<typename T>
inline CQueue<T>::CQueue(const CQueue<T>& other)
{
	CQueueNode* cur = other.first;
	while (cur)
	{
		Push(cur->value);
		cur = cur->next;
	}
}

template<typename T>
CQueue<T>::CQueue(CQueue<T>&& other)
{
	Swap(other);
}

template<typename T>
CQueue<T>::CQueue(std::initializer_list<T> IList)
{
	for (const T& value : IList)
		Push(value);
}

template<typename T>
CQueue<T>::~CQueue()
{
	while (!Empty())
		Pop();
}

template<typename T>
void CQueue<T>::Push(const T& value)
{
	size++;
	if (first == nullptr)
	{
		first = new CQueueNode(value);
		last = &first->next;
		return;
	}
	last = &(*last = new CQueueNode(value))->next;
}

template<typename T>
void CQueue<T>::Pop()
{
	size--;
	CQueueNode* next = first->next;
	delete first->next;
	first = next;
}

template<typename T>
T& CQueue<T>::Front()
{
	return first->value;
}

template<typename T>
const T& CQueue<T>::Front() const
{
	return first->value;
}

template<typename T>
void CQueue<T>::Swap(CQueue<T>& other)
{
	std::swap(first, other.first);
	std::swap(last, other.last);
	std::swap(size, other.size);
}

#endif