#pragma once
#include <initializer_list>
#include <iostream>

template<typename T>
class ADeque
{
public:
	struct ADequeIterator
	{
		size_t pos;
		const ADeque& deq;
		ADequeIterator() {}
		ADequeIterator(const ADequeIterator& other) : deq(other.deq), pos(other.pos) {}
		ADequeIterator(const ADeque<T>& deq) : deq(deq), pos(0) {}
		ADequeIterator(const ADeque<T>& deq, size_t pos) : deq(deq), pos(pos) {}
		T& operator*() const
		{
			return deq.arr[pos];
		}
		T* operator->() const
		{
			return &deq.arr[pos];
		}
		ADequeIterator& operator++()
		{
			pos = deq.NextTo(pos);
			return *this;
		}
		ADequeIterator& operator++(int)
		{
			ADequeIterator it(*this);
			operator++();
			return it;
		}
		ADequeIterator& operator--()
		{
			pos = deq.PrevTo(pos);
			return *this;
		}
		ADequeIterator& operator--(int)
		{
			ADequeIterator it(*this);
			operator--();
			return it;
		}
		bool operator==(const ADequeIterator& other) const
		{
			return &deq == &other.deq && pos == other.pos;
		}
		bool operator!=(const ADequeIterator& other) const
		{
			return !operator==(other);
		}
	};

	struct ADequeConstIterator
	{
		size_t pos;
		const ADeque& deq;
		ADequeConstIterator() {}
		ADequeConstIterator(const ADequeConstIterator& other) : deq(other.deq), pos(other.pos) {}
		ADequeConstIterator(const ADeque<T>& deq) : deq(deq), pos(0) {}
		ADequeConstIterator(const ADeque<T>& deq, size_t pos) : deq(deq), pos(pos) {}
		const T& operator*() const
		{
			return deq.arr[pos];
		}
		const T* operator->() const
		{
			return &deq.arr[pos];
		}
		ADequeConstIterator& operator++()
		{
			pos = deq.NextTo(pos);
			return *this;
		}
		ADequeConstIterator& operator++(int)
		{
			ADequeConstIterator it(*this);
			operator++();
			return it;
		}
		ADequeConstIterator& operator--()
		{
			pos = deq.PrevTo(pos);
			return *this;
		}
		ADequeConstIterator& operator--(int)
		{
			ADequeConstIterator it(*this);
			operator--();
			return it;
		}
		bool operator==(const ADequeConstIterator& other) const
		{
			return &deq == &other.deq && pos == other.pos;
		}
		bool operator!=(const ADequeConstIterator& other) const
		{
			return !operator==(other);
		}
	};
	typedef ADequeIterator iterator;
	typedef ADequeConstIterator const_iterator;
private:
	T* arr;
	size_t first = 0, last = 0;
	size_t maxSize; // TODO: size calc runtime
	size_t NextTo(size_t pos) const
	{
		return (pos + 1) % maxSize;
	}
	size_t PrevTo(size_t pos) const
	{
		return (pos - 1 + maxSize) % maxSize;
	}
public:
	ADeque(size_t size) : maxSize(size)
	{
		arr = new T[size];
	}
	ADeque() : ADeque(16) {}
	ADeque(const ADeque<T>& other);
	ADeque(ADeque<T>&& other);
	ADeque(std::initializer_list<T> IList);
	~ADeque();
	void PushFront(const T& value);
	void PopFront();
	void PushBack(const T& value);
	void PopBack();
	void Clear();
	void Resize(size_t newSize);
	iterator begin()
	{
		return iterator(*this, first);
	}
	iterator end()
	{
		return iterator(*this, last);
	}
	const_iterator begin() const
	{
		return const_iterator(*this, first);
	}
	const_iterator end() const
	{
		return const_iterator(*this, last);
	}
	const_iterator cbegin() const
	{
		return const_iterator(*this, first);
	}
	const_iterator cend() const
	{
		return const_iterator(*this, last);
	}
	T& Front()
	{
		return arr[first];
	}
	const T& Front() const
	{
		return arr[first];
	}
	T& Back()
	{
		return arr[PrevTo(last)];
	}
	const T& Back() const
	{
		return arr[PrevTo(last)];
	}
	void Swap(ADeque<T>& other);
	size_t Size() const
	{
		return (last - first + maxSize) % maxSize;
	}
	bool Empty() const
	{
		return first == last;
	}
	bool IsFull() const
	{
		return NextTo(last) == first;
	}
	friend std::ostream& operator<<(std::ostream& out, const ADeque<T>& self) // TODO: Move to .cpp
	{
		for (auto it = self.begin(); it != self.end(); ++it)
		{
			if (it != self.begin())
				out << " ";
			out << *it;
		}
		return out;
	}
};

#include "ADeque.cpp"
