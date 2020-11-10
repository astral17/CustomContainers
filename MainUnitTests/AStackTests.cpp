#include "CppUnitTest.h"
#include <vector>
#include <algorithm>
#include "..//CustomContainers/AStack.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CustomContainersTests
{
	TEST_CLASS(AStackTests)
	{
	public:
		template<typename T>
		void EqualToVector(AStack<T> stk, const std::vector<T>& v)
		{
			Assert::AreEqual(v.size(), stk.Size());
			for (const T& x : v)
			{
				Assert::AreEqual(x, stk.Top());
				stk.Pop();
			}
		}
		TEST_METHOD(GeneralTest1)
		{
			AStack<int> stk;
			stk.Push(5);
			stk.Push(8);
			stk.Pop();
			Assert::AreEqual(5, stk.Top());
			stk.Push(9);
			Assert::AreEqual(9, stk.Top());
			stk.Pop();
			stk.Pop();
			stk.Push(-29);
			Assert::AreEqual(-29, stk.Top());
		}
		TEST_METHOD(GeneralTest2)
		{
			AStack<std::string> stk;
			stk.Push("hello");
			stk.Pop();
			stk.Push("test");
			Assert::AreEqual((std::string)"test", stk.Top());
			stk.Push("!");
			Assert::IsFalse(stk.Empty());
			for (int i = 0; i < 100; i++)
				stk.Push(std::to_string(i));
			Assert::AreEqual((size_t)102, stk.Size());
		}
		TEST_METHOD(CopyConstructor1)
		{
			AStack<int> stk1;
			stk1.Push(8);
			stk1.Push(5);
			AStack<int> stk2(stk1);
			Assert::AreEqual(stk2.Size(), stk1.Size());
			Assert::AreEqual(5, stk2.Top());
			stk2.Pop();
			Assert::AreEqual(8, stk2.Top());
			stk2.Pop();
		}
		TEST_METHOD(MoveConstructor1)
		{
			std::vector<int> v1 = { 1, 5, 4, 3, -8, 8 };
			std::reverse(v1.begin(), v1.end());
			AStack<int> stk1{ 1,5,4,3,-8 };
			stk1.Push(8);
			AStack<int> stk2(std::move(stk1));
			Assert::IsTrue(stk1.Empty());
			EqualToVector(stk2, v1);
		}
		TEST_METHOD(InitializerList1)
		{
			AStack<int> stk{ 5, 8, 9, 4, 6, 11 };
			std::vector<int> v{ 5, 8, 9, 4, 6, 11 };
			reverse(v.begin(), v.end());
			Assert::AreEqual((size_t)6, stk.Size());
			EqualToVector(stk, v);
		}
		TEST_METHOD(SwapTest1)
		{
			std::vector<int> v1 = { 8, 4, 9, 15, 22 };
			std::reverse(v1.begin(), v1.end());
			AStack<int> stk1{ 8, 4, 9, 15, 22 };
			std::vector<int> v2 = { 9, 15, 7, 21 };
			std::reverse(v2.begin(), v2.end());
			AStack<int> stk2{ 9, 15, 7, 21 };
			stk1.Swap(stk2);
			Assert::AreEqual((size_t)4, stk1.Size());
			Assert::AreEqual((size_t)5, stk2.Size());
			EqualToVector(stk1, v2);
			EqualToVector(stk2, v1);
		}
	};
}
