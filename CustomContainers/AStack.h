#pragma once
#include <initializer_list>

template<typename T>
class AStack
{
public:
	struct AStackIterator
	{
		size_t pos;
		const AStack& stk;
		AStackIterator() {}
		AStackIterator(const AStackIterator& other) : stk(other.stk), pos(other.pos) {}
		AStackIterator(const AStack<T>& stk) : stk(stk), pos(0) {}
		AStackIterator(const AStack<T>& stk, size_t pos) : stk(stk), pos(pos) {}
		T& operator*() const
		{
			return stk.arr[pos];
		}
		T* operator->() const
		{
			return &stk.arr[pos];
		}
		AStackIterator& operator++()
		{
			++pos;
			return *this;
		}
		AStackIterator& operator++(int)
		{
			AStackIterator it(*this);
			operator++();
			return it;
		}
		AStackIterator& operator--()
		{
			--pos;
			return *this;
		}
		AStackIterator& operator--(int)
		{
			AStackIterator it(*this);
			operator--();
			return it;
		}
		bool operator==(const AStackIterator& other) const
		{
			return &stk == &other.stk && pos == other.pos;
		}
		bool operator!=(const AStackIterator& other) const
		{
			return !operator==(other);
		}
	};

	struct AStackConstIterator
	{
		size_t pos;
		const AStack& stk;
		AStackConstIterator() {}
		AStackConstIterator(const AStackConstIterator& other) : stk(other.stk), pos(other.pos) {}
		AStackConstIterator(const AStack<T>& stk) : stk(stk), pos(0) {}
		AStackConstIterator(const AStack<T>& stk, size_t pos) : stk(stk), pos(pos) {}
		const T& operator*() const
		{
			return stk.arr[pos];
		}
		const T* operator->() const
		{
			return &stk.arr[pos];
		}
		AStackConstIterator& operator++()
		{
			++pos;
			return *this;
		}
		AStackConstIterator& operator++(int)
		{
			AStackConstIterator it(*this);
			operator++();
			return it;
		}
		AStackConstIterator& operator--()
		{
			--pos;
			return *this;
		}
		AStackConstIterator& operator--(int)
		{
			AStackConstIterator it(*this);
			operator--();
			return it;
		}
		bool operator==(const AStackConstIterator& other) const
		{
			return &stk == &other.stk && pos == other.pos;
		}
		bool operator!=(const AStackConstIterator& other) const
		{
			return !operator==(other);
		}
	};
private:
	//struct AStackNode
	//{
	//	T value;
	//	AStackNode() : value() {}
	//	AStackNode(const T& value, AStackNode* next = nullptr) : value(value), next(next) {}
	//};
	T* arr;
	size_t size = 0, maxSize;
public:
	explicit AStack(size_t size) : maxSize(size)
	{
		arr = new T[size];
	}
	AStack() : AStack(16) {}
	AStack(const AStack<T>& other);
	AStack(AStack<T>&& other) noexcept;
	AStack(std::initializer_list<T> IList);
	~AStack();
	void Push(const T& value);
	void Pop();
	void Clear();
	void Resize(size_t newSize);
	AStackIterator begin()
	{
		return AStackIterator(*this, 0);
	}
	AStackIterator end()
	{
		return AStackIterator(*this, size);
	}
	AStackConstIterator cbegin() const
	{
		return AStackConstIterator(*this, 0);
	}
	AStackConstIterator cend() const
	{
		return AStackConstIterator(*this, size);
	}
	T& Top()
	{
		return arr[size - 1];
	}
	const T& Top() const
	{
		return arr[size - 1];
	}
	void Swap(AStack<T>& other);
	size_t Size() const
	{
		return size;
	}
	bool IsFull() const
	{
		return size == maxSize;
	}
	bool Empty() const
	{
		return size == 0;
	}
};

#include "AStack.cpp"