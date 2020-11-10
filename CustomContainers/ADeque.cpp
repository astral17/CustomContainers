#include "ADeque.h"

#ifndef _ADeque_HEADER_GUARD
#define _ADeque_HEADER_GUARD

template<typename T>
ADeque<T>::ADeque(const ADeque<T>& other) : ADeque()
{
	for (const T& x : other)
		PushBack(x);
}

template<typename T>
ADeque<T>::ADeque(ADeque<T>&& other) : ADeque()
{
	Clear();
	Swap(other);
}

template<typename T>
ADeque<T>::ADeque(std::initializer_list<T> IList) : ADeque()
{
	for (const T& value : IList)
		PushBack(value);
}

template<typename T>
ADeque<T>::~ADeque()
{
	delete[] arr;
}

template<typename T>
void ADeque<T>::PushFront(const T& value)
{
	if (IsFull())
		Resize(maxSize * 2);
	first = PrevTo(first);
	arr[first] = value;
}

template<typename T>
void ADeque<T>::PopFront()
{
	first = NextTo(first);
}

template<typename T>
void ADeque<T>::PushBack(const T& value)
{
	if (IsFull())
		Resize(maxSize * 2);
	arr[last] = value;
	last = NextTo(last);
}

template<typename T>
void ADeque<T>::PopBack()
{
	last = PrevTo(last);
}

template<typename T>
void ADeque<T>::Clear()
{
	first = last = 0;
}

template<typename T>
void ADeque<T>::Resize(size_t newSize)
{
	newSize = std::max(newSize, Size() + 1);
	T* newArr = new T[newSize];
	if (first <= last)
		std::move(arr + first, arr + last, newArr + first);
	else
	{
		std::move(arr, arr + last, newArr);
		std::move(arr + first, arr + maxSize, newArr + newSize - (maxSize - first));
		first = newSize - (maxSize - first);
	}
	delete[] arr;
	arr = newArr;
	maxSize = newSize;
}

template<typename T>
void ADeque<T>::Swap(ADeque<T>& other)
{
	std::swap(arr, other.arr);
	std::swap(first, other.first);
	std::swap(last, other.last);
	std::swap(maxSize, other.maxSize);
}

#endif