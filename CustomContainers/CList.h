#pragma once
#include <initializer_list>

template<typename T>
class CList
{
public:
	struct CListNode
	{
		T value;
		CListNode* prev = nullptr;
		CListNode* next = nullptr;
		CListNode() {}
		CListNode(const T& value, CListNode* prev = nullptr, CListNode* next = nullptr) : value(value), prev(prev), next(next) {}
	};
private:
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
	void InsertAfter(CListNode* node, const T& value);
	void InsertBefore(CListNode* node, const T& value);
	void Erase(CListNode* node);
	void PushFront(const T& value);
	void PopFront();
	void PushBack(const T& value);
	void PopBack();
	CListNode* begin()
	{
		return root.next;
	}
	CListNode* end()
	{
		return &root;
	}
	const CListNode* cbegin() const
	{
		return root.next;
	}
	const CListNode* cend() const
	{
		return &root;
	}
	T& Front()
	{
		return root.next->value;
	}
	const T& Front() const
	{
		return root.next->value;
	}
	T& Back()
	{
		return root.prev->value;
	}
	const T& Back() const
	{
		return root->prev->value;
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