#include "CList.h"

#include <initializer_list>
#include <algorithm>

#ifndef _CLIST_HEADER_GUARD
#define _CLIST_HEADER_GUARD

template<typename T>
inline CList<T>::CList(const CList<T>& other) : CList()
{
	const CListNode* cur = other.cbegin();
	while (cur != other.cend())
	{
		PushBack(cur->value);
		cur = cur->next;
	}
}

template<typename T>
CList<T>::CList(CList<T>&& other) : CList()
{
	Swap(other);
}

template<typename T>
CList<T>::CList(std::initializer_list<T> IList) : CList()
{
	for (const T& value : IList)
		PushBack(value);
}

template<typename T>
CList<T>::~CList()
{
	while (!Empty())
		PopBack();
}

template<typename T>
void CList<T>::InsertAfter(CListNode* node, const T& value)
{
	size++;
	node->next = new CListNode(value, node, node->next);
	node->next->next->prev = node->next;
}

template<typename T>
void CList<T>::InsertBefore(CListNode* node, const T& value)
{
	size++;
	node->prev = new CListNode(value, node->prev, node);
	node->prev->prev->next = node->prev;
}

template<typename T>
void CList<T>::Erase(CListNode* node)
{
	size--;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	delete node;
}

template<typename T>
void CList<T>::PushFront(const T& value)
{
	InsertAfter(&root, value);
}

template<typename T>
void CList<T>::PopFront()
{
	Erase(root.next);
}

template<typename T>
void CList<T>::PushBack(const T& value)
{
	InsertBefore(&root, value);
}

template<typename T>
void CList<T>::PopBack()
{
	Erase(root.prev);
}

template<typename T>
void CList<T>::Swap(CList<T>& other)
{
	std::swap(root.next->prev, other.root.next->prev); // TODO: remove kostil by pointer to root
	std::swap(root.prev->next, other.root.prev->next);
	std::swap(root, other.root);
	std::swap(size, other.size);
}

#endif