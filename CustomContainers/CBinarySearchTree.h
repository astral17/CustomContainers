#pragma once
#include <functional>
#include <initializer_list>

template <typename T>
struct CBinarySearchTreeNode
{
	T value;
	CBinarySearchTreeNode* left, * right;
	CBinarySearchTreeNode(const T& value, CBinarySearchTreeNode* left = nullptr, CBinarySearchTreeNode* right = nullptr) : value(value), left(left), right(right){}
};

template <typename T, typename Compare = std::less<T>>
class CBinarySearchTree
{
public:
	typedef CBinarySearchTreeNode<T> Node;
	CBinarySearchTree(){}
	~CBinarySearchTree();
	CBinarySearchTree(const CBinarySearchTree& other);
	CBinarySearchTree(CBinarySearchTree&& other);
	CBinarySearchTree(std::initializer_list<T> IList);
	void Insert(const T& value);
	Node* Find(const T& value) const;
	bool Erase(const T& value);
	void Swap(CBinarySearchTree& other);
	const Node* CRoot() const
	{
		return root;
	}
private:
	Node* RecursiveCopy(Node* node);
	void RecursiveDestroy(Node* node);
	Node* root = nullptr;
	//Compare less = Compare();
};

#include "CBinarySearchTree.cpp"