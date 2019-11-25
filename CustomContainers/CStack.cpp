#include "CStack.h"
#include <algorithm>

#ifndef _CSTACK_HEADER_GUARD
#define _CSTACK_HEADER_GUARD

template<typename T>
CStack<T>::CStack(const CStack<T>& other) : first(nullptr)
{
	CStackNode* cur = other.first;
	CStack<T> rStack;
	while (cur != nullptr)
	{
		rStack.Push(cur->value);
		cur = cur->next;
	}
	cur = rStack.first;
	while (cur != nullptr)
	{
		this->Push(cur->value);
		cur = cur->next;
	}
}

template<typename T>
CStack<T>::CStack(CStack<T>&& other) : first(nullptr)
{
	this->Swap(other);
}

template<typename T>
CStack<T>::CStack(std::initializer_list<T> IList) : first(nullptr)
{
	for (const T& value : IList)
	{
		Push(value);
	}
}

template<typename T>
CStack<T>::~CStack()
{
	CStackNode* next;
	while (first)
	{
		next = first->next;
		delete first;
		first = next;
	}
}

template<typename T>
void CStack<T>::Push(const T& value)
{
	size++;
	first = new CStackNode(value, first);
}

template<typename T>
void CStack<T>::Pop()
{
	size--;
	CStackNode* next = first->next;
	delete first;
	first = next;
}

template<typename T>
void CStack<T>::Swap(CStack<T>& other)
{
	std::swap(this->first, other.first);
	std::swap(this->size, other.size);
}

#endif