#pragma once
#include <initializer_list>

template<typename T>
class AList
{
public:
	struct AListNode
	{
		T value;
		size_t prev = -1;
		size_t next = -1;
		//AListNode() {}
		//		AListNode(const T& value, size_t prev = -1, size_t next = -1) : value(value), prev(prev), next(next) {}
		void Init(const T& value, size_t prev = -1, size_t next = -1)
		{
			this->value = value;
			this->prev = prev;
			this->next = next;
		}
	};

	struct AListConstIterator
	{
		size_t cur;
		const AList& list;
		//AListConstIterator() {}
		AListConstIterator(const AListConstIterator& other) : list(other.list), cur(other.cur) {}
		AListConstIterator(const AList<T>& list) : list(list), cur(list.arr[list.root].next) {}
		AListConstIterator(const AList<T>& list, size_t cur) : list(list), cur(cur) {}
		const T& operator*() const
		{
			return list.arr[cur].value;
		}
		const T* operator->() const
		{
			return &list.arr[cur].value;
		}
		AListConstIterator& operator++()
		{
			cur = list.arr[cur].next;
			return *this;
		}
		AListConstIterator& operator++(int)
		{
			AListConstIterator it(*this);
			operator++();
			return it;
		}
		AListConstIterator& operator--()
		{
			cur = list.arr[cur].prev;
			return *this;
		}
		AListConstIterator& operator--(int)
		{
			AListConstIterator it(*this);
			operator--();
			return it;
		}
		bool operator==(const AListConstIterator& other) const
		{
			return &list == &other.list && cur == other.cur;
		}
		bool operator!=(const AListConstIterator& other) const
		{
			return !operator==(other);
		}
	};

	struct AListIterator
	{
		size_t cur;
		const AList& list;
		//AListIterator() {}
		AListIterator(const AListIterator& other) : list(other.list), cur(other.cur) {}
		AListIterator(const AList<T>& list) : list(list), cur(list.arr[list.root].next) {}
		AListIterator(const AList<T>& list, size_t cur) : list(list), cur(cur) {}
		T& operator*() const
		{
			return list.arr[cur].value;
		}
		T* operator->() const
		{
			return &list.arr[cur].value;
		}
		AListIterator& operator++()
		{
			cur = list.arr[cur].next;
			return *this;
		}
		AListIterator& operator++(int)
		{
			AListIterator it(*this);
			operator++();
			return it;
		}
		AListIterator& operator--()
		{
			cur = list.arr[cur].prev;
			return *this;
		}
		AListIterator& operator--(int)
		{
			AListIterator it(*this);
			operator--();
			return it;
		}
		bool operator==(const AListIterator& other) const
		{
			return &list == &other.list && cur == other.cur;
		}
		bool operator!=(const AListIterator& other) const
		{
			return !operator==(other);
		}
		operator AListConstIterator() const
		{
			return AListConstIterator(list, cur);
		}
	};
	typedef AListIterator iterator;
	typedef AListConstIterator const_iterator;
	//	friend struct AListIterator;
private:
	AListNode* arr;
	size_t size = 0, maxSize, freeRoot;
	constexpr static size_t root = 0;

	void PushFree(size_t id)
	{
		arr[id].next = freeRoot;
		freeRoot = id;
	}
	size_t PopFree(const T& value, size_t prev, size_t next)
	{
		size_t result = freeRoot;
		freeRoot = arr[freeRoot].next;
		arr[result].Init(value, prev, next);
		return result;
	}
	void InsertAfter(size_t id, const T& value);
	void InsertBefore(size_t id, const T& value);
	void Erase(size_t id);
public:
	explicit AList(size_t size) : maxSize(size), freeRoot(1)
	{
		arr = new AListNode[size];
		arr[root].prev = arr[root].next = root;
		for (size_t i = 1; i < maxSize; i++)
			arr[i].next = i + 1;
	}
	AList() : AList(16) {}
	AList(const AList<T>& other);
	AList(AList<T>&& other) noexcept;
	AList(std::initializer_list<T> IList);
	~AList();
	void InsertAfter(AListIterator it, const T& value);
	void InsertBefore(AListIterator it, const T& value);
	void Erase(AListIterator it);
	void PushFront(const T& value);
	void PopFront();
	void PushBack(const T& value);
	void PopBack();
	void Clear();
	void Resize(size_t newSize);
	AListIterator begin()
	{
		return AListIterator(*this, arr[root].next);
	}
	AListIterator end()
	{
		return AListIterator(*this, root);
	}
	AListConstIterator begin() const
	{
		return AListConstIterator(*this, arr[root].next);
	}
	AListConstIterator end() const
	{
		return AListConstIterator(*this, root);
	}
	AListConstIterator cbegin() const
	{
		return AListConstIterator(*this, arr[root].next);
	}
	AListConstIterator cend() const
	{
		return AListConstIterator(*this, root);
	}
	T& Front()
	{
		return arr[arr[root].next].value;
	}
	const T& Front() const
	{
		return arr[arr[root].next].value;
	}
	T& Back()
	{
		return arr[arr[root].prev].value;
	}
	const T& Back() const
	{
		return arr[arr[root].prev].value;
	}
	void Swap(AList<T>& other);
	size_t Size() const
	{
		return size;
	}
	bool Empty() const
	{
		return size == 0;
	}
	bool IsFull() const
	{
		return size == maxSize - 1;
	}
	AList<T>& operator+=(const AList<T>& other);
	AList<T> operator+(const AList<T>& other) const;
	AList<T>& operator=(const AList<T>& other);
	AList<T>& operator=(AList<T>&& other);
	bool operator==(const AList<T>& other) const;
	bool operator!=(const AList<T>& other) const;
};

#include "AList.cpp"
