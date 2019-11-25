#include "CDeque.h"

#ifndef _CDEQUE_HEADER_GUARD
#define _CDEQUE_HEADER_GUARD

template<typename T>
CDeque<T>::CDeque(const CDeque<T>& other) : CDeque()
{
	CDequeNode* cur = other.root.next;
	while (cur != &other.root)
	{
		PushBack(cur->value);
		cur = cur->next;
	}

}

template<typename T>
CDeque<T>::CDeque(CDeque<T>&& other) : CDeque()
{
	Swap(other);
}

template<typename T>
CDeque<T>::CDeque(std::initializer_list<T> IList) : CDeque()
{
	for (const T& value : IList)
		PushBack(value);
}

template<typename T>
CDeque<T>::~CDeque()
{
	while (!Empty())
		PopBack();
}

template<typename T>
void CDeque<T>::PushFront(const T& value)
{
	size++;
	root.next = new CDequeNode(value, &root, root.next);
	root.next->next->prev = root.next;
}

template<typename T>
void CDeque<T>::PopFront()
{
	size--;
	CDequeNode* del = root.next;
	root.next = root.next->next;
	root.next->prev = &root;
	delete del;
}

template<typename T>
void CDeque<T>::PushBack(const T& value)
{
	size++;
	root.prev = new CDequeNode(value, root.prev, &root);
	root.prev->prev->next = root.prev;
}

template<typename T>
void CDeque<T>::PopBack()
{
	size--;
	CDequeNode* del = root.prev;
	root.prev = root.prev->prev;
	root.prev->next = &root;
	delete del;
}

template<typename T>
void CDeque<T>::Swap(CDeque<T>& other)
{
	std::swap(root.next->prev, other.root.next->prev);
	std::swap(root.prev->next, other.root.prev->next);
	std::swap(root, other.root);
	std::swap(size, other.size);
}

#endif