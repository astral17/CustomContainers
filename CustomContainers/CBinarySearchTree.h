#pragma once
#include <initializer_list>
#include <functional>

template <typename T>
struct CBinarySearchTreeNode
{
	T value;
	CBinarySearchTreeNode* left, * right;
	CBinarySearchTreeNode(const T& value, CBinarySearchTreeNode* left = nullptr, CBinarySearchTreeNode* right = nullptr) : value(value), left(left), right(right){}
};

template <typename T>
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
	template<typename F>
	void PreOrder(F func) const;
	template<typename F>
	void InOrder(F func) const;
	template<typename F>
	void PostOrder(F func) const;
private:
	template<typename F>
	void PreOrder(Node* node, F func) const;
	template<typename F>
	void InOrder(Node* node, F func) const;
	template<typename F>
	void PostOrder(Node* node, F func) const;
	Node* RecursiveCopy(Node* node) const;
	void RecursiveDestroy(Node* node);
	Node* root = nullptr;
};

#include "CBinarySearchTree.cpp"