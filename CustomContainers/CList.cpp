#include "CList.h"

#ifndef _CLIST_HEADER_GUARD
#define _CLIST_HEADER_GUARD

template<typename T>
inline CList<T>::CList(const CList<T>& other)
{
}

template<typename T>
CList<T>::CList(CList<T>&& other)
{
}

template<typename T>
CList<T>::CList(std::initializer_list<T> IList)
{
}

template<typename T>
CList<T>::~CList()
{
}

template<typename T>
void CList<T>::PushFront(const T& value)
{
}

template<typename T>
void CList<T>::PopFront()
{
}

template<typename T>
void CList<T>::PushBack(const T& value)
{
}

template<typename T>
void CList<T>::PopBack()
{
}

template<typename T>
void CList<T>::Swap(CList<T>& other)
{
}

#endif