#pragma once
#include <initializer_list>

template<typename T>
class CQueue
{
private:
	struct CQueueNode
	{
		T value;
		CQueueNode* next = nullptr;
		CQueueNode() : value() {}
		CQueueNode(const T& value, CQueueNode* next = nullptr) : value(value), next(next) {}
	};
	CQueueNode* first;
	CQueueNode** last;
	size_t size = 0;
public:
	CQueue() {}
	CQueue(const CQueue<T>& other);
	CQueue(CQueue<T>&& other);
	CQueue(std::initializer_list<T> l);
	~CQueue();
	void Push(const T& value);
	void Pop();
	T& Front();
	const T& Front() const;
	void Swap(CQueue<T>& other);
	size_t Size() const
	{
		return size;
	}
	bool Empty() const
	{
		return size == 0;
	}
};

#include "CQueue.cpp"