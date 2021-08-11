#include "CBinarySearchTree.h"

#ifndef _CBINARY_SEARCH_TREE_HEADER_GUARD
#define _CBINARY_SEARCH_TREE_HEADER_GUARD

template<typename T>
CBinarySearchTree<T>::~CBinarySearchTree()
{
	RecursiveDestroy(root);
}

template<typename T>
CBinarySearchTree<T>::CBinarySearchTree(const CBinarySearchTree& other)
{
	/*
	RecursiveDestroy(root);
	root = RecursiveCopy(other.root);*/
	CBinarySearchTree<T> tmp;
	tmp.root = RecursiveCopy(other.root);
	Swap(tmp);
}

template<typename T>
CBinarySearchTree<T>::CBinarySearchTree(CBinarySearchTree&& other)
{
	Swap(other);
}

template<typename T>
CBinarySearchTree<T>::CBinarySearchTree(std::initializer_list<T> IList)
{
	for (const T& value : IList)
	{
		Insert(value);
	}
}

template<typename T>
inline void CBinarySearchTree<T>::Insert(const T& value)
{
	Node* cur = root;
	Node** from = &root;
	while (cur)
	{
		if (value < cur->value)
			from = &cur->left;
		else
			from = &cur->right;
		cur = *from;
	}
	*from = new Node(value);
}

template<typename T>
typename CBinarySearchTree<T>::Node* CBinarySearchTree<T>::Find(const T& value) const
{
	Node* cur = root;
	while (cur)
	{
		if (value == cur->value)
			return cur;
		if (value < cur->value)
			cur = cur->left;
		else
			cur = cur->right;
	}
	return nullptr;
}

template<typename T>
bool CBinarySearchTree<T>::Erase(const T& value)
{
	Node* cur = root;
	Node** from = &root;
	while (cur && cur->value != value)
	{
		if (value < cur->value)
			from = &cur->left;
		else
			from = &cur->right;
		cur = *from;
	}
	if (!cur)
		return false;
	if (!cur->left)
	{
		*from = cur->right;
		delete cur;
	}
	else if (!cur->right)
	{
		*from = cur->left;
		delete cur;
	}
	else
	{
		Node** miFrom = &cur->right, * mi = cur->right;
		while (mi->left)
		{
			miFrom = &mi->left;
			mi = *miFrom;
		}
		*miFrom = mi->right;
		// TODO: for simple types better move value then move node
		//cur->value = mi->value;
		//delete mi;
		mi->left = cur->left;
		mi->right = cur->right;
		*from = mi;
		delete cur;
	}

	return true;
}

template<typename T>
void CBinarySearchTree<T>::Swap(CBinarySearchTree& other)
{
	std::swap(root, other.root);
}

template<typename T>
template<typename F>
inline void CBinarySearchTree<T>::PreOrder(F func) const
{
	PreOrder(root, func);
}

template<typename T>
template<typename F>
inline void CBinarySearchTree<T>::InOrder(F func) const
{
	InOrder(root, func);
}

template<typename T>
template<typename F>
inline void CBinarySearchTree<T>::PostOrder(F func) const
{
	PostOrder(root, func);
}

template<typename T>
template<typename F>
void CBinarySearchTree<T>::PreOrder(Node* node, F func) const
{
	if (node)
	{
		func(node->value);
		PreOrder(node->left, func);
		PreOrder(node->right, func);
	}
}

template<typename T>
template<typename F>
void CBinarySearchTree<T>::InOrder(Node* node, F func) const
{
	if (node)
	{
		InOrder(node->left, func);
		func(node->value);
		InOrder(node->right, func);
	}
}

template<typename T>
template<typename F>
void CBinarySearchTree<T>::PostOrder(Node* node, F func) const
{
	if (node)
	{
		PostOrder(node->left, func);
		PostOrder(node->right, func);
		func(node->value);
	}
}

template<typename T>
typename CBinarySearchTree<T>::Node* CBinarySearchTree<T>::RecursiveCopy(Node* node) const
{
	if (node == nullptr)
		return nullptr;
	return new Node(node->value, RecursiveCopy(node->left), RecursiveCopy(node->right));
}

template<typename T>
void CBinarySearchTree<T>::RecursiveDestroy(Node* node)
{
	if (node)
	{
		RecursiveDestroy(node->left);
		RecursiveDestroy(node->right);
		delete node;
	}
}

#endif _CBINARY_SEARCH_TREE_HEADER_GUARD