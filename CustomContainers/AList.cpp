#include "AList.h"

#ifndef _ALIST_HEADER_GUARD
#define _ALIST_HEADER_GUARD
#include <algorithm>

template<typename T>
inline AList<T>::AList(const AList<T>& other) : AList()
{
	AListConstIterator cur = other.cbegin();
	while (cur != other.cend())
	{
		PushBack(cur->value);
		++cur;
	}
}

template<typename T>
AList<T>::AList(AList<T>&& other) : AList()
{
	Swap(other);
}

template<typename T>
AList<T>::AList(std::initializer_list<T> IList) : AList()
{
	for (const T& value : IList)
		PushBack(value);
}

template<typename T>
AList<T>::~AList()
{
	delete[] arr;
}

template<typename T>
void AList<T>::Clear()
{
	while (!Empty())
		PopBack();
}

template<typename T>
void AList<T>::Resize(size_t newSize)
{
	newSize = std::max(newSize, size);
	AListNode* newArr = new AListNode[newSize];
	std::copy(arr, arr + maxSize, newArr);
	delete[] arr;
	arr = newArr;
	for (size_t i = maxSize; i < newSize; ++i)
		PushFree(i);
	maxSize = newSize;
}

template<typename T>
void AList<T>::InsertAfter(size_t id, const T& value)
{
	if (IsFull())
		Resize(maxSize * 2);
	size++;
	size_t result = PopFree(value, id, arr[id].next);
	arr[arr[id].next].prev = result;
	arr[id].next = result;
}

template<typename T>
void AList<T>::InsertAfter(AList<T>::AListIterator it, const T& value)
{
	InsertAfter(it.cur, value);
}

template<typename T>
void AList<T>::InsertBefore(size_t id, const T& value)
{
	if (IsFull())
		Resize(maxSize * 2);
	size++;
	size_t result = PopFree(value, arr[id].prev, id);
	arr[arr[id].prev].next = result;
	arr[id].prev = result;
}

template<typename T>
void AList<T>::InsertBefore(AList<T>::AListIterator it, const T& value)
{
	InsertBefore(it.cur, value);
}

template<typename T>
void AList<T>::Erase(size_t id)
{
	size--;
	arr[arr[id].prev].next = arr[id].next;
	arr[arr[id].next].prev = arr[id].prev;
	PushFree(id);
}

template<typename T>
void AList<T>::Erase(AList<T>::AListIterator it)
{
	Erase(it.cur);
}

template<typename T>
void AList<T>::PushFront(const T& value)
{
	InsertAfter(root, value);
}

template<typename T>
void AList<T>::PopFront()
{
	Erase(arr[root].next);
}

template<typename T>
void AList<T>::PushBack(const T& value)
{
	InsertBefore(root, value);
}

template<typename T>
void AList<T>::PopBack()
{
	Erase(arr[root].prev);
}

template<typename T>
void AList<T>::Swap(AList<T>& other)
{
	std::swap(arr, other.arr);
	std::swap(freeRoot, other.freeRoot);
	std::swap(size, other.size);
	std::swap(maxSize, other.maxSize);
}

#endif
