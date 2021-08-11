#include "CppUnitTest.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <functional>
#include "..//CustomContainers/CBinarySearchTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CustomContainersTests
{
	TEST_CLASS(CBinarySearchTreeTests)
	{
	public:
		void EqualToVector(const CBinarySearchTree<int>& tree, const std::vector<int>& v)
		{
			std::vector<int> tv;
			tree.InOrder([&tv](int value) {tv.push_back(value); });
			Assert::IsTrue(tv == v);
		}
		TEST_METHOD(GeneralTest1)
		{
			CBinarySearchTree<int> t;
			Assert::AreEqual((void*)nullptr, (void*)t.Find(5));
			t.Insert(5);
			Assert::AreEqual(5, t.Find(5)->value);
			t.Insert(8);
			t.Insert(6);
			Assert::AreEqual(6, t.Find(6)->value);
		}
		TEST_METHOD(GeneralTest2)
		{
			CBinarySearchTree<int> t;
			for (int i = 0; i < 10; i++)
			{
				t.Insert(5);
				t.Erase(5);
			}
			t.Insert(7);
			EqualToVector(t, { 7 });
		}
		TEST_METHOD(InsertTest1)
		{
			CBinarySearchTree<int> t{ 1,8,4,5 };
			t.Insert(7);
			EqualToVector(t, { 1,4,5,7,8 });
		}
		TEST_METHOD(InsertTest2)
		{
			CBinarySearchTree<int> t;
			t.Insert(7);
			t.Insert(5);
			t.Insert(9);
			t.Insert(1);
			t.Insert(1);
			t.Insert(-5);
			t.Insert(7);
			EqualToVector(t, { -5,1,1,5,7,7,9 });
		}
		TEST_METHOD(EraseTest1)
		{
			CBinarySearchTree<int> t{ 1,4,6,9,9 };
			Assert::IsTrue(t.Erase(4));
			Assert::IsTrue(t.Erase(9));
			Assert::IsFalse(t.Erase(10));
			EqualToVector(t, { 1,6,9 });
		}
		TEST_METHOD(EraseTest2)
		{
			CBinarySearchTree<int> t{ 1,1,1 };
			Assert::IsTrue(t.Erase(1));
			Assert::IsTrue(t.Erase(1));
			Assert::IsTrue(t.Erase(1));
			Assert::IsFalse(t.Erase(1));
			EqualToVector(t, {});
		}
		TEST_METHOD(EraseTest3)
		{
			CBinarySearchTree<int> t;
			t.Insert(5);
			t.Insert(3);
			// Root remove left
			Assert::IsTrue(t.Erase(5));
			EqualToVector(t, { 3 });
			// Root remove right
			t.Insert(7);
			Assert::IsTrue(t.Erase(3));
			EqualToVector(t, { 7 });
			// Root remove both
			t.Insert(1);
			t.Insert(10);
			t.Insert(0);
			t.Insert(2);
			t.Insert(9);
			t.Insert(11);
			Assert::IsTrue(t.Erase(7));
			EqualToVector(t, { 0,1,2,9,10,11 });
		}
		TEST_METHOD(EraseTest4)
		{
			CBinarySearchTree<int> t;
			t.Insert(10);
			t.Insert(5);
			t.Insert(15);
			t.Insert(12);
			// remove left
			Assert::IsTrue(t.Erase(15));
			EqualToVector(t, { 5,10,12 });
			// Root remove right
			t.Insert(14);
			Assert::IsTrue(t.Erase(12));
			EqualToVector(t, { 5,10,14 });
			// Root remove both
			t.Insert(12);
			t.Insert(11);
			t.Insert(13);
			t.Insert(16);
			t.Insert(15);
			t.Insert(17);
			Assert::IsTrue(t.Erase(14));
			EqualToVector(t, { 5,10,11,12,13,15,16,17 });
		}
		TEST_METHOD(EraseTest5)
		{
			CBinarySearchTree<int> t;
			t.Insert(10);
			t.Insert(5);
			t.Insert(15);
			Assert::IsTrue(t.Erase(10));
			EqualToVector(t, { 5,15 });
		}

		TEST_METHOD(CopyConstructor1)
		{
			CBinarySearchTree<int> t1;
			t1.Insert(8);
			t1.Insert(5);
			CBinarySearchTree<int> t2(t1);
			std::vector<int> v;
			t1.InOrder([&v](int value) {v.push_back(value); });
			EqualToVector(t2, v);
			t2.Insert(6);
			Assert::AreEqual((void*)nullptr, (void*)t1.Find(6));
			Assert::AreEqual(6, t2.Find(6)->value);
		}
		
		TEST_METHOD(InitializerList1)
		{
			CBinarySearchTree<int> t{ 5, 8, 9, 4, 6, 11 };
			std::vector<int> v{ 5, 8, 9, 4, 6, 11 };
			std::sort(v.begin(), v.end());
			EqualToVector(t, v);
		}
		TEST_METHOD(InitializerList2)
		{
			CBinarySearchTree<int> t{};
			std::vector<int> v{};
			EqualToVector(t, v);
		}
		TEST_METHOD(InitializerList3)
		{
			CBinarySearchTree<int> t{ 8 };
			std::vector<int> v{ 8 };
			EqualToVector(t, v);
		}

		TEST_METHOD(SwapTest1)
		{
			std::vector<int> v1 = { 8, 4, 9, 15, 22 };
			std::sort(v1.begin(), v1.end());
			CBinarySearchTree<int> t1{ 8, 4, 9, 15, 22 };
			std::vector<int> v2 = { 9, 15, 7, 21 };
			std::sort(v2.begin(), v2.end());
			CBinarySearchTree<int> t2{ 9, 15, 7, 21 };
			t1.Swap(t2);
			EqualToVector(t1, v2);
			EqualToVector(t2, v1);
		}
		/*
		TEST_METHOD(OstreamTest1)
		{
			std::stringstream str;
			CDeque<int> d{ 5, 4, 99, -1 };
			str << d;
			Assert::AreEqual(str.str(), std::string("5 4 99 -1"));
		}//*/
	};
}
