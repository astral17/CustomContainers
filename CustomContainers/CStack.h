#pragma once
#include <initializer_list>

template<typename T>
class CStack
{
private:
	struct CStackNode
	{
		T value;
		CStackNode* next = nullptr;
		CStackNode() : value() {}
		CStackNode(const T& value, CStackNode* next = nullptr) : value(value), next(next) {}
	};
	CStackNode* first = nullptr;
	size_t size = 0;
public:
	CStack(){}
	CStack(const CStack<T>& other);
	CStack(CStack<T>&& other);
	CStack(std::initializer_list<T> IList);
	~CStack();
	void Push(const T& value);
	void Pop();
	T& Top()
	{
		return first->value;
	}
	const T& Top() const
	{
		return first->value;
	}
	void Swap(CStack<T>& other);
	size_t Size() const
	{
		return size;
	}
	bool Empty() const
	{
		return size == 0;
	}
};

#include "CStack.cpp"