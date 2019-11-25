#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include "..//CustomContainers/CDeque.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CustomContainersTests
{
	TEST_CLASS(CDequeTests)
	{
	public:

		TEST_METHOD(GeneralTest1)
		{
			CDeque<int> d;
			d.PushBack(8);
			Assert::AreEqual(d.Front(), 8);
			Assert::AreEqual(d.Back(), 8);
			d.PushBack(6);
			Assert::AreEqual(d.Front(), 8);
			Assert::AreEqual(d.Back(), 6);
			d.PushFront(1);
			Assert::AreEqual(d.Front(), 1);
			Assert::AreEqual(d.Back(), 6);
			d.PushBack(9);
			d.PushBack(4);
			d.PopBack();
			Assert::AreEqual(d.Back(), 9);
		}
		TEST_METHOD(GeneralTest2)
		{
			CDeque<int> d{ 1,8,4 };
			d.PushBack(8);
			d.PushFront(6);
			d.PushBack(4);
			d.PopBack();
			EqualToVector(d, { 6,1,8,4,8 });
		}
		TEST_METHOD(CopyConstructor1)
		{
			CDeque<int> d1;
			d1.PushBack(8);
			d1.PushBack(5);
			CDeque<int> d2(d1);
			Assert::AreEqual(d2.Size(), d1.Size());
			Assert::AreEqual(d2.Back(), 5);
			d2.PopBack();
			Assert::AreEqual(d2.Back(), 8);
		}
		template<typename T>
		void EqualToVector(CDeque<T> stk, const std::vector<T> & v)
		{
			for (const T& x : v)
			{
				Assert::AreEqual(stk.Front(), x);
				stk.PopFront();
			}
		}
		TEST_METHOD(InitializerList1)
		{
			CDeque<int> d{ 5, 8, 9, 4, 6, 11 };
			std::vector<int> v{ 5, 8, 9, 4, 6, 11 };
			Assert::AreEqual(d.Size(), (size_t)6);
			EqualToVector(d, v);
		}
		TEST_METHOD(InitializerList2)
		{
			CDeque<int> d{ 7 };
			std::vector<int> v{ 7 };
			Assert::AreEqual(d.Size(), (size_t)1);
			Assert::AreEqual(d.Front(), 7);
			Assert::AreEqual(d.Back(), 7);
			EqualToVector(d, v);
		}
		TEST_METHOD(SwapTest1)
		{
			std::vector<int> v1 = { 8, 4, 9, 15, 22 };
			CDeque<int> d1{ 8, 4, 9, 15, 22 };
			std::vector<int> v2 = { 9, 15, 7, 21 };
			CDeque<int> d2{ 9, 15, 7, 21 };
			d1.Swap(d2);
			Assert::AreEqual(d1.Size(), (size_t)4);
			Assert::AreEqual(d2.Size(), (size_t)5);
			EqualToVector(d1, v2);
			EqualToVector(d2, v1);
		}
		TEST_METHOD(OstreamTest1)
		{
			std::stringstream str;
			CDeque<int> d{ 5, 4, 99, -1 };
			str << d;
			Assert::AreEqual(str.str(), std::string("5 4 99 -1"));
		}
	};
}
