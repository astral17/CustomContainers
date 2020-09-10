#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include "..//CustomContainers/AList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CustomContainersTests
{
	TEST_CLASS(AListTests)
	{
	public:
		template<typename T>
		void EqualToVector(const AList<T> &list, const std::vector<T>& v)
		{
			Assert::AreEqual(list.Size(), v.size());
			typename AList<T>::AListConstIterator cur = list.cbegin();
			for (const T& x : v)
			{
				Assert::AreEqual(x, *cur);
				++cur;
			}
		}
		TEST_METHOD(GeneralTest1)
		{
			AList<int> l;
			l.PushBack(8);
			Assert::AreEqual(8, l.Front());
			Assert::AreEqual(8, l.Back());
			l.PushBack(6);
			Assert::AreEqual(8, l.Front());
			Assert::AreEqual(6, l.Back());
			l.PushFront(1);
			Assert::AreEqual(1, l.Front());
			Assert::AreEqual(6, l.Back());
			l.PushBack(9);
			l.PushBack(4);
			l.PopBack();
			Assert::AreEqual(9, l.Back());
		}
		TEST_METHOD(GeneralTest2)
		{
			AList<int> l{ 1,8,4 };
			l.PushBack(8);
			l.PushFront(6);
			l.PushBack(4);
			l.PopBack();
			EqualToVector(l, { 6,1,8,4,8 });
		}
		TEST_METHOD(CopyConstructor1)
		{
			AList<int> l1{ 4,1,7,9 };
			AList<int> l2(l1);
			Assert::AreEqual(l2.Size(), l1.Size());
			l1.PushBack(1);
			EqualToVector(l2, { 4,1,7,9 });
		}
		TEST_METHOD(MoveConstructor1)
		{
			std::vector<int> v1 = { 1, 5, 4, 3, -8, 8 };
			AList<int> l1{ 1,5,4,3,-8 };
			l1.PushBack(8);
			AList<int> l2(std::move(l1));
			Assert::IsTrue(l1.Empty());
			EqualToVector(l2, v1);
		}
		TEST_METHOD(InitializerList1)
		{
			AList<int> l{ 5, 8, 9, 4, 6, 11 };
			std::vector<int> v{ 5, 8, 9, 4, 6, 11 };
			Assert::AreEqual((size_t)6, l.Size());
			EqualToVector(l, v);
		}
		TEST_METHOD(InitializerList2)
		{
			AList<int> l{ 7 };
			std::vector<int> v{ 7 };
			Assert::AreEqual((size_t)1, l.Size());
			Assert::AreEqual(7, l.Front());
			Assert::AreEqual(7, l.Back());
			EqualToVector(l, v);
		}
		TEST_METHOD(SwapTest1)
		{
			std::vector<int> v1 = { 8, 4, 9, 15, 22 };
			AList<int> l1{ 8, 4, 9, 15, 22 };
			std::vector<int> v2 = { 9, 15, 7, 21 };
			AList<int> l2{ 9, 15, 7, 21 };
			l1.Swap(l2);
			Assert::AreEqual((size_t)4, l1.Size());
			Assert::AreEqual((size_t)5, l2.Size());
			EqualToVector(l1, v2);
			EqualToVector(l2, v1);
		}
		TEST_METHOD(IteratorTest1)
		{
			AList<int> l{ 1, 5, 9 };
			std::vector<int> v{ 1, 5, 9 };
			typename std::vector<int>::iterator it = v.begin();
			for (auto x : l)
				Assert::AreEqual(*(it++), x);
		}
		TEST_METHOD(IteratorTest2)
		{
			AList<double> l{ 9.1, 3.2, 8.4 };
			std::vector<double> v{ 8.1, 2.2, 7.4 };
			for (auto& x : l)
				--x;
			EqualToVector(l, v);
		}
		TEST_METHOD(IteratorTest3)
		{
			AList<double> l{ 9.1, 3.2, 8.4 };
			const std::vector<double> v{ 9.1, 3.2, 8.4 };
			double sum = 0;
			for (auto x : l)
				sum += x;
			Assert::AreEqual(9.1 + 3.2 + 8.4, sum);
			EqualToVector(l, v);
		}
		TEST_METHOD(CompareTest1)
		{
			AList<std::string> l{ "hello", "to", "world" };
			AList<std::string> l2{ "hello", "to" };
			Assert::IsFalse(l == l2);
			l2.PushBack("world");
			Assert::IsTrue(l == l2);
			l2.PushBack("world");
			Assert::IsTrue(l != l2);
		}
		TEST_METHOD(ConcatTest1)
		{
			AList<double> l{ 8, 1.1, 9, 6.3 };
			AList<double> l2{ 4.11, 3.7 };
			std::vector<double> v{ 8, 1.1, 9, 6.3, 4.11, 3.7 };
			AList<double> l3 = l + l2;
			Assert::IsTrue((l += l2) == l3);
			EqualToVector(l, v);
			l += {8};
			Assert::IsFalse(l == l3);
		}
		TEST_METHOD(AssignTest1)
		{
			AList<int> l{ 4, 3, 8, 7 };
			AList<int> l2{ 11 };
			l2 = l;
			std::vector<int> v{ 4, 3, 8, 7 };
			EqualToVector(l2, v);
		}
		TEST_METHOD(MoveTest1)
		{
			AList<int> l{ 4, 3, 8, 7 };
			AList<int> l2{ 11 };
			l2 = std::move(l);
			std::vector<int> v{ 4, 3, 8, 7 };
			Assert::IsTrue(l.Empty());
			EqualToVector(l2, v);
		}
		/*
		TEST_METHOD(OstreamTest1)
		{
			std::stringstream str;
			AList<int> l{ 5, 4, 99, -1 };
			str << d;
			Assert::AreEqual(str.str(), std::string("5 4 99 -1"));
		}*/
	};
}
