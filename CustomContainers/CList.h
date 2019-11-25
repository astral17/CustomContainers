#pragma once
#include <initializer_list>

template<typename T>
class CList
{
private:
	struct CListNode
	{
		T* value = nullptr;
		CListNode* prev = nullptr;
		CListNode* next = nullptr;
		CListNode() {}
		CListNode(const T& value, CListNode* prev = nullptr, CListNode* next = nullptr) : value(new T(value)), prev(prev), next(next) {}
	};
	CListNode root;
	size_t size = 0;
public:
	CList()
	{
		root.prev = root.next = &root;
	}
	CList(const CList<T>& other);
	CList(CList<T>&& other);
	CList(std::initializer_list<T> IList);
	~CList();
	void PushFront(const T& value);
	void PopFront();
	void PushBack(const T& value);
	void PopBack();
	T& Front()
	{
		return *root->next->value;
	}
	const T& Front() const
	{
		return *root.next->value;
	}
	T& Back()
	{
		return *root.prev->value;
	}
	const T& Back() const
	{
		return *root->prev->value;
	}
	void Swap(CList<T>& other);
	size_t Size() const
	{
		return size;
	}
	bool Empty() const
	{
		return size == 0;
	}
};

#include "CList.cpp"