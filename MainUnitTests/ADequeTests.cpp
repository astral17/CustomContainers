#include "CppUnitTest.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include "..//CustomContainers/ADeque.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CustomContainersTests
{
	TEST_CLASS(ADequeTests)
	{
	public:

		TEST_METHOD(GeneralTest1)
		{
			ADeque<int> d;
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
			ADeque<int> d{ 1,8,4 };
			d.PushBack(8);
			d.PushFront(6);
			d.PushBack(4);
			d.PopBack();
			EqualToVector(d, { 6,1,8,4,8 });
		}
		TEST_METHOD(CopyConstructor1)
		{
			ADeque<int> d1;
			d1.PushBack(8);
			d1.PushBack(5);
			ADeque<int> d2(d1);
			Assert::AreEqual(d2.Size(), d1.Size());
			Assert::AreEqual(d2.Back(), 5);
			d2.PopBack();
			Assert::AreEqual(d2.Back(), 8);
		}
		template<typename T>
		void EqualToVector(const ADeque<T> &d, const std::vector<T>& v)
		{
			Assert::AreEqual(d.Size(), v.size());
			auto it = d.begin();
			for (const T& x : v)
			{
				Assert::AreEqual(x, *it);
				++it;
			}
		}
		TEST_METHOD(BoundsTest1)
		{
			ADeque<int> d(4);
			d.PushBack(1);
			d.PushBack(2);
			d.PushBack(3);
			d.PopFront();
			d.PopFront();
			d.PushBack(4);
			d.PushBack(5);
			EqualToVector(d, { 3,4,5 });
		}
		TEST_METHOD(BoundsTest2)
		{
			ADeque<int> d(4);
			d.PushBack(1);
			d.PushBack(2);
			d.PushBack(3);
			d.PopFront();
			d.PopFront();
			d.PushBack(4);
			Assert::AreEqual(4, d.Back());
			d.PushBack(5);
			d.PushBack(6);
			Assert::AreEqual(3, d.Front());
			EqualToVector(d, { 3,4,5,6 });
		}
		TEST_METHOD(ResizeTest1)
		{
			ADeque<int> d(4);
			d.Resize(1);
			d.PushBack(5);
			Assert::AreEqual(5, d.Back());
			Assert::AreEqual(5, d.Front());
			d.PushBack(4);
			Assert::AreEqual(4, d.Back());
			Assert::AreEqual(5, d.Front());
			d.Clear();
			d.Resize(0);
		}
		TEST_METHOD(ResizeTest2)
		{
			ADeque<int> d(4);
			d.PushBack(1);
			d.PushBack(2);
			d.PushBack(3);
			d.PopFront();
			d.Resize(8);
			EqualToVector(d, { 2,3 });
		}
		TEST_METHOD(InitializerList1)
		{
			ADeque<int> d{ 5, 8, 9, 4, 6, 11 };
			std::vector<int> v{ 5, 8, 9, 4, 6, 11 };
			Assert::AreEqual(d.Size(), (size_t)6);
			EqualToVector(d, v);
		}
		TEST_METHOD(InitializerList2)
		{
			ADeque<int> d{ 7 };
			std::vector<int> v{ 7 };
			Assert::AreEqual(d.Size(), (size_t)1);
			Assert::AreEqual(d.Front(), 7);
			Assert::AreEqual(d.Back(), 7);
			EqualToVector(d, v);
		}
		TEST_METHOD(SwapTest1)
		{
			std::vector<int> v1 = { 8, 4, 9, 15, 22 };
			ADeque<int> d1{ 8, 4, 9, 15, 22 };
			std::vector<int> v2 = { 9, 15, 7, 21 };
			ADeque<int> d2{ 9, 15, 7, 21 };
			d1.Swap(d2);
			Assert::AreEqual(d1.Size(), (size_t)4);
			Assert::AreEqual(d2.Size(), (size_t)5);
			/*
			{
				std::stringstream str;
				str << d1;
				std::string s1 = str.str();
				str.clear();
				str.str("");
				str << d2;
				std::string s2 = str.str();
			}//*/
			EqualToVector(d1, v2);
			EqualToVector(d2, v1);
		}
		TEST_METHOD(ClearTest1)
		{
			ADeque<int> d{ 5, 8, 9, 4, 6, 11 };
			d.Clear();
			Assert::IsTrue(d.Empty());
		}
		TEST_METHOD(ClearTest2)
		{
			ADeque<int> d{ 5, 8, 9, 4, 6, 11 };
			d.PushFront(5);
			d.Clear();
			d.PushFront(4);
			EqualToVector(d, { 4 });
		}
		TEST_METHOD(IteratorTest1)
		{
			ADeque<int> d{ 1, 5, 9 };
			std::vector<int> v{ 1, 5, 9 };
			typename std::vector<int>::iterator it = v.begin();
			for (auto x : d)
				Assert::AreEqual(*(it++), x);
		}
		TEST_METHOD(IteratorTest2)
		{
			ADeque<double> d{ 9.1, 3.2, 8.4 };
			std::vector<double> v{ 8.1, 2.2, 7.4 };
			for (auto& x : d)
				--x;
			EqualToVector(d, v);
		}
		TEST_METHOD(IteratorTest3)
		{
			ADeque<int> d(4);
			const std::vector<int> v{ 1,2,3,4 };
			int sum = 0;
			d.PushBack(3);
			d.PushBack(4);
			d.PushBack(5);
			d.PushFront(2);
			d.PushFront(1);
			d.PopBack();
			for (auto x : d)
				sum += x;
			Assert::AreEqual(1 + 2 + 3 + 4, sum);
			EqualToVector(d, v);
		}
		TEST_METHOD(OstreamTest1)
		{
			std::stringstream str;
			ADeque<int> d{ 5, 4, 99, -1 };
			str << d;
			Assert::AreEqual(str.str(), std::string("5 4 99 -1"));
		}
	};
}
