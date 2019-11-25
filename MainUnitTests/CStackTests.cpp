#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <algorithm>
#include "..//CustomContainers/CStack.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CustomContainersTests
{
	TEST_CLASS(CStackTests)
	{
	public:

		TEST_METHOD(GeneralTest1)
		{
			CStack<int> stk;
			stk.Push(5);
			stk.Push(8);
			stk.Pop();
			Assert::AreEqual(stk.Top(), 5);
			stk.Push(9);
			Assert::AreEqual(stk.Top(), 9);
			stk.Pop();
			stk.Pop();
			stk.Push(-29);
			Assert::AreEqual(stk.Top(), -29);
		}
		TEST_METHOD(CopyConstructor1)
		{
			CStack<int> stk1;
			stk1.Push(8);
			stk1.Push(5);
			CStack<int> stk2(stk1);
			Assert::AreEqual(stk2.Size(), stk1.Size());
			Assert::AreEqual(stk2.Top(), 5);
			stk2.Pop();
			Assert::AreEqual(stk2.Top(), 8);
			stk2.Pop();
		}
		template<typename T>
		void EqualToVector(CStack<T> stk, const std::vector<T>& v)
		{
			Assert::AreEqual(stk.Size(), v.size());
			for (const T& x : v)
			{
				Assert::AreEqual(stk.Top(), x);
				stk.Pop();
			}
		}
		TEST_METHOD(InitializerList1)
		{
			CStack<int> stk{ 5, 8, 9, 4, 6, 11 };
			std::vector<int> v{ 5, 8, 9, 4, 6, 11 };
			reverse(v.begin(), v.end());
			Assert::AreEqual(stk.Size(), (size_t)6);
			EqualToVector(stk, v);
		}
		TEST_METHOD(SwapTest1)
		{
			std::vector<int> v1 = { 8, 4, 9, 15, 22 };
			std::reverse(v1.begin(), v1.end());
			CStack<int> stk1{ 8, 4, 9, 15, 22 };
			std::vector<int> v2 = { 9, 15, 7, 21 };
			std::reverse(v2.begin(), v2.end());
			CStack<int> stk2{ 9, 15, 7, 21 };
			stk1.Swap(stk2);
			Assert::AreEqual(stk1.Size(), (size_t)4);
			Assert::AreEqual(stk2.Size(), (size_t)5);
			EqualToVector(stk1, v2);
			EqualToVector(stk2, v1);
		}
	};
}
