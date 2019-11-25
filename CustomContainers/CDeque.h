#pragma once
#include <initializer_list>
#include <iostream>

template<typename T>
class CDeque
{
public:
	struct CDequeNode
	{
		T value;
		CDequeNode* prev = nullptr;
		CDequeNode* next = nullptr;
		CDequeNode() {}
		CDequeNode(const T& value, CDequeNode* prev = nullptr, CDequeNode* next = nullptr) : value(value), prev(prev), next(next) {}
	};
private:
	CDequeNode root;
	size_t size = 0;
public:
	CDeque()
	{
		root.prev = root.next = &root;
	}
	CDeque(const CDeque<T>& other);
	CDeque(CDeque<T>&& other);
	CDeque(std::initializer_list<T> IList);
	~CDeque();
	void PushFront(const T& value);
	void PopFront();
	void PushBack(const T& value);
	void PopBack();
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
	void Swap(CDeque<T>& other);
	size_t Size() const
	{
		return size;
	}
	bool Empty() const
	{
		return size == 0;
	}
	friend std::ostream& operator<<(std::ostream& out, const CDeque<T>& self) // TODO: Move to .cpp
	{
		CDequeNode* cur = self.root.next;
		while (cur != &self.root)
		{
			if (cur != self.root.next)
				out << " ";
			out << cur->value;
			cur = cur->next;
		}
		return out;
	}
};

#include "CDeque.cpp"
