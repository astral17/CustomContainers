#include "CppUnitTest.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include "..//CustomContainers/CPriorityQueue.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CustomContainersTests
{
	TEST_CLASS(CPriorityQueueTests)
	{
	public:

		TEST_METHOD(GeneralTest1)
		{
			CPriorityQueue<int> q;
			q.Push(8);
			Assert::AreEqual(q.Top(), 8);
			q.Push(6);
			Assert::AreEqual(q.Top(), 6);
			q.Push(7);
			Assert::AreEqual(q.Top(), 6);
			q.Pop();
			Assert::AreEqual(q.Top(), 7);
			q.Pop();
			q.Pop();
			q.Push(4);
			Assert::AreEqual(q.Top(), 4);
		}
		TEST_METHOD(GeneralTest2)
		{
			CPriorityQueue<int> q{ 1,8,4 };
			q.Push(8);
			q.Push(6);
			EqualToVector(q, { 1,4,6,8,8 });
		}
		TEST_METHOD(CopyConstructor1)
		{
			CPriorityQueue<int> q1{ 4,1,7,9 };
			CPriorityQueue<int> q2(q1);
			Assert::AreEqual(q2.Size(), q1.Size());
			q1.Push(1);
			EqualToVector(q2, { 1,4,7,9 });
		}
		template<typename T>
		void EqualToVector(CPriorityQueue<T> q, const std::vector<T> & v)
		{
			Assert::AreEqual(q.Size(), v.size());
			for (const T& x : v)
			{
				Assert::AreEqual(q.Top(), x);
				q.Pop();
			}
		}
		TEST_METHOD(InitializerList1)
		{
			CPriorityQueue<int> q{ 5, 8, 9, 4, 6, 11 };
			std::vector<int> v{ 5, 8, 9, 4, 6, 11 };
			std::sort(v.begin(), v.end());
			Assert::AreEqual(q.Size(), (size_t)6);
			EqualToVector(q, v);
		}
		TEST_METHOD(InitializerList2)
		{
			CPriorityQueue<int> q{ 7 };
			Assert::AreEqual(q.Size(), (size_t)1);
			Assert::AreEqual(q.Top(), 7);
		}
		TEST_METHOD(SwapTest1)
		{
			std::vector<int> v1 = { 8, 4, 9, 15, 22 };
			std::sort(v1.begin(), v1.end());
			CPriorityQueue<int> q1{ 8, 4, 9, 15, 22 };
			std::vector<int> v2 = { 9, 15, 7, 21 };
			std::sort(v2.begin(), v2.end());
			CPriorityQueue<int> q2{ 9, 15, 7, 21 };
			q1.Swap(q2);
			Assert::AreEqual(q1.Size(), (size_t)4);
			Assert::AreEqual(q2.Size(), (size_t)5);
			EqualToVector(q1, v2);
			EqualToVector(q2, v1);
		}
		/*
		TEST_METHOD(OstreamTest1)
		{
			std::stringstream str;
			CList<int> l{ 5, 4, 99, -1 };
			str << d;
			Assert::AreEqual(str.str(), std::string("5 4 99 -1"));
		}*/
	};
}
