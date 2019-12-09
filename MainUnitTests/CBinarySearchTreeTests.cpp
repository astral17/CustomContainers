#include "pch.h"
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
		void TreeToVector(const CBinarySearchTree<int>::Node * node, std::vector<int> & v)
		{
			if (node)
			{
				TreeToVector(node->left, v);
				v.push_back(node->value);
				TreeToVector(node->right, v);
			}
		}
		void EqualToVector(const CBinarySearchTree<int>& tree, const std::vector<int>& v)
		{
			std::vector<int> tv;
			TreeToVector(tree.CRoot(), tv);
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
			CBinarySearchTree<int> t{ 1,8,4,5 };
			t.Insert(7);
			EqualToVector(t, { 1,4,5,7,8 });
		}

		TEST_METHOD(CopyConstructor1)
		{
			CBinarySearchTree<int> t1;
			t1.Insert(8);
			t1.Insert(5);
			CBinarySearchTree<int> t2(t1);
			std::vector<int> v;
			TreeToVector(t1.CRoot(), v);
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
