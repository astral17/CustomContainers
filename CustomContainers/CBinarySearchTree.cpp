#include "CBinarySearchTree.h"

#ifndef _CBINARY_SEARCH_TREE_HEADER_GUARD
#define _CBINARY_SEARCH_TREE_HEADER_GUARD

template<typename T, typename Compare>
CBinarySearchTree<T, Compare>::~CBinarySearchTree()
{
	RecursiveDestroy(root);
}

template<typename T, typename Compare>
CBinarySearchTree<T, Compare>::CBinarySearchTree(const CBinarySearchTree& other)
{
	/*
	RecursiveDestroy(root);
	root = RecursiveCopy(other.root);*/
	CBinarySearchTree<T, Compare> tmp;
	tmp.root = RecursiveCopy(other.root);
	Swap(tmp);
}

template<typename T, typename Compare>
CBinarySearchTree<T, Compare>::CBinarySearchTree(CBinarySearchTree&& other)
{
	Swap(other);
}

template<typename T, typename Compare>
CBinarySearchTree<T, Compare>::CBinarySearchTree(std::initializer_list<T> IList)
{
	for (const T& value : IList)
	{
		Insert(value);
	}
}

template<typename T, typename Compare>
inline void CBinarySearchTree<T, Compare>::Insert(const T& value)
{
	Node* cur = root;
	Node** from = &root;
	while (cur)
	{
		if (value < cur->value)
		{
			from = &cur->left;
			cur = cur->left;
		}
		else
		{
			from = &cur->right;
			cur = cur->right;
		}
	}
	*from = new Node(value);
}

template<typename T, typename Compare>
typename CBinarySearchTree<T, Compare>::Node* CBinarySearchTree<T, Compare>::Find(const T& value) const
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

template<typename T, typename Compare>
bool CBinarySearchTree<T, Compare>::Erase(const T& value)
{
	Node* cur = Find(value);
	if (!cur)
		return false;
	if (!cur->left)

	return true;
}

template<typename T, typename Compare>
void CBinarySearchTree<T, Compare>::Swap(CBinarySearchTree& other)
{
	std::swap(root, other.root);
}

template<typename T, typename Compare>
typename CBinarySearchTree<T, Compare>::Node* CBinarySearchTree<T, Compare>::RecursiveCopy(Node* node)
{
	if (node == nullptr)
		return nullptr;
	return new Node(node->value, RecursiveCopy(node->left), RecursiveCopy(node->right));
}

template<typename T, typename Compare>
void CBinarySearchTree<T, Compare>::RecursiveDestroy(Node* node)
{
	if (node)
	{
		RecursiveDestroy(node->left);
		RecursiveDestroy(node->right);
		delete node;
	}
}

#endif _CBINARY_SEARCH_TREE_HEADER_GUARD