#include "AStack.h"

#ifndef _AStack_HEADER_GUARD
#define _AStack_HEADER_GUARD
#include <algorithm>

template<typename T>
AStack<T>::AStack(const AStack<T>& other) : size(other.size), maxSize(other.maxSize)
{
	arr = new T[maxSize];
	std::copy(other.arr, other.arr + maxSize, arr);
}

template<typename T>
AStack<T>::AStack(AStack<T>&& other) noexcept : AStack()
{
	this->Swap(other);
}

template<typename T>
AStack<T>::AStack(std::initializer_list<T> IList) : AStack()
{
	for (const T& value : IList)
		Push(value);
}

template<typename T>
AStack<T>::~AStack()
{
	delete[] arr;
}

template<typename T>
void AStack<T>::Push(const T& value)
{
	if (IsFull())
		Resize(maxSize * 2);
	arr[size++] = value;
}

template<typename T>
void AStack<T>::Pop()
{
	--size;
}

template<typename T>
void AStack<T>::Clear()
{
	size = 0;
}

template<typename T>
void AStack<T>::Resize(size_t newSize)
{
	newSize = std::max(newSize, size);
	T* newArr = new T[newSize];
	std::move(arr, arr + maxSize, newArr);
	delete[] arr;
	arr = newArr;
	maxSize = newSize;
}

template<typename T>
void AStack<T>::Swap(AStack<T>& other)
{
	std::swap(this->arr, other.arr);
	std::swap(this->size, other.size);
	std::swap(this->maxSize, other.maxSize);
}

template<typename T>
AStack<T>& AStack<T>::operator=(const AStack<T>& other)
{
	if (this == &other)
		return *this;
	Clear();
	for (auto& x : other)
		Push(x);
	return *this;
}

template<typename T>
AStack<T>& AStack<T>::operator=(AStack<T>&& other) noexcept
{
	if (this == &other)
		return *this;
	Clear();
	Swap(other);
	return *this;
}

#endif