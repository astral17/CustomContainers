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

		TEST_METHOD(GeneralTest1)
		{
			AList<int> l;
			l.PushBack(8);
			Assert::AreEqual(l.Front(), 8);
			Assert::AreEqual(l.Back(), 8);
			l.PushBack(6);
			Assert::AreEqual(l.Front(), 8);
			Assert::AreEqual(l.Back(), 6);
			l.PushFront(1);
			Assert::AreEqual(l.Front(), 1);
			Assert::AreEqual(l.Back(), 6);
			l.PushBack(9);
			l.PushBack(4);
			l.PopBack();
			Assert::AreEqual(l.Back(), 9);
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
		template<typename T>
		void EqualToVector(AList<T> list, const std::vector<T>& v)
		{
			Assert::AreEqual(list.Size(), v.size());
			typename AList<T>::AListConstIterator cur = list.cbegin();
			for (const T& x : v)
			{
				Assert::AreEqual(cur->value, x);
				++cur;
			}
		}
		TEST_METHOD(InitializerList1)
		{
			AList<int> l{ 5, 8, 9, 4, 6, 11 };
			std::vector<int> v{ 5, 8, 9, 4, 6, 11 };
			Assert::AreEqual(l.Size(), (size_t)6);
			EqualToVector(l, v);
		}
		TEST_METHOD(InitializerList2)
		{
			AList<int> l{ 7 };
			std::vector<int> v{ 7 };
			Assert::AreEqual(l.Size(), (size_t)1);
			Assert::AreEqual(l.Front(), 7);
			Assert::AreEqual(l.Back(), 7);
			EqualToVector(l, v);
		}
		TEST_METHOD(SwapTest1)
		{
			std::vector<int> v1 = { 8, 4, 9, 15, 22 };
			AList<int> l1{ 8, 4, 9, 15, 22 };
			std::vector<int> v2 = { 9, 15, 7, 21 };
			AList<int> l2{ 9, 15, 7, 21 };
			l1.Swap(l2);
			Assert::AreEqual(l1.Size(), (size_t)4);
			Assert::AreEqual(l2.Size(), (size_t)5);
			EqualToVector(l1, v2);
			EqualToVector(l2, v1);
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
