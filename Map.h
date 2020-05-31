#pragma once

#include <iostream>
#include <Windows.h>
#include <C:\Users\user\Desktop\lab2\lab2\List.h>


#define RED 0
#define BLACK 1



using namespace std;

template <typename T0, typename T1>
class Map
{
public:
	Map();
	~Map();

	unsigned int GetSize()
	{
		return size;
	}

	void insert(T0 key, T1 value);
	void remove(T0 key);
	T1 find(T0 key);
	bool change(T0 key, T1 NewValue);
	void clear();
	void printTree();
	void printList();

	void SetColor(int text, int background)
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
	}

	void get_keys(List<T0>& map)
	{
		map.clear();
		if (size == 0)
			return;
		keyFill(map, root);
	}
	void get_values(List<T1>& map)
	{
		map.clear();
		if (size == 0)
			return;
		valueFill(map, root);
	}

private:

	template <typename T0, typename T1>
	class Node
	{
	public:
		Node* parent;
		Node* left;
		Node* right;
		bool color;
		T0 key;
		T1 value;

		Node(T0 key = T0(), T1 value = T1(), Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr, bool color = RED)
		{
			this->key = key;
			this->value = value;
			this->parent = parent;
			this->left = left;
			this->right = right;
			this->color = color;
		}
	};

	void printTree(int index, int spaces, Node<T0, T1>* q);
	void printList(Node<T0, T1>* current);

	void insert(Node<T0, T1>* parent, T0 key, T1 value);
	void uncleCheck(Node<T0, T1>* node);

	void remove(Node<T0, T1>* node);
	void removeFIX(Node<T0, T1>* node, bool leafs);

	void clear(Node<T0, T1>* node);

	void keyFill(List<T0>& lst, Node<T0, T1>* current);
	void valueFill(List<T1>& lst, Node<T0, T1>* current);


	Node<T0, T1>* root;
	Node<T0, T1>* leaf;
	unsigned int size;
};

template <typename T0, typename T1>
Map<T0, T1>::Map()
{
	size = 0;
	root = nullptr;
	leaf = new Node<T0, T1>(NULL, NULL, nullptr, nullptr, nullptr, BLACK);
}

template <typename T0, typename T1>
Map<T0, T1>::~Map()
{
	clear();
}



template <typename T0, typename T1>
void Map<T0, T1>::insert(T0 key, T1 value)
{
	if (size == 0)
	{
		root = new Node<T0, T1>(key, value, nullptr, leaf, leaf, BLACK);
		size++;
		return;
	}
	insert(root, key, value);
}



template <typename T0, typename T1>
void Map<T0, T1>::printTree()
{
	int index = 0;
	int spaces = 0;

	if (index < size)
	{
		printTree(index, spaces + 4, root->right);
		SetColor(15, 0);
		cout << root->key;
		SetColor(0, 15);

		cout << endl;
		SetColor(15, 0);
		cout << root->value;
		SetColor(0, 15);
		cout << endl;
		printTree(index, spaces + 4, root->left);
		index++;
	}
}

template<typename T0, typename T1>
void Map<T0, T1>::printList()
{
	if (size == 0)
		return;
	printList(root->left);

	cout << root->key << " - " << root->value << endl;

	printList(root->right);
}

template <typename T0, typename T1>
void Map<T0, T1>::remove(T0 key)
{
	Node<T0, T1>* node = root;
	while (node != leaf)
	{
		if (node->key == key)
		{
			remove(node);
			node = root;
		}
		else if (node->key > key)
			node = node->left;
		else
			node = node->right;
	}
}

template <typename T0, typename T1>
T1 Map<T0, T1>::find(T0 key)
{
	if (size == 0)
		return NULL;
	Node<T0, T1>* current = root;
	while (current != leaf)
	{
		if (key == current->key)
			return current->value;
		else if (key < current->key)
			current = current->left;
		else
			current = current->right;
	}
	return NULL;
}

template<typename T0, typename T1>
bool Map<T0, T1>::change(T0 key, T1 NewValue)
{
	if (size == 0)
		return false;
	Node<T0, T1>* current = root;
	while (current != leaf)
	{
		if (key == current->key)
		{
			current->value = NewValue;
			return true;
		}

		else if (key < current->key)
			current = current->left;
		else
			current = current->right;
	}
	return false;
}

template <typename T0, typename T1>
void Map<T0, T1>::clear()
{
	if (size == 0)
		return;
	clear(root->left);
	clear(root->right);
	delete root;
	size--;
}




template <typename T0, typename T1>
void Map<T0, T1>::printTree(int index, int spaces, Node<T0, T1>* q)
{
	if (index < size)
	{
		if (q != leaf)
			printTree(index, spaces + 4, q->right);
		for (int i = 0; i < spaces; i++) {
			SetColor(0, 15);
			cout << ' ';
		}
		if (q->color == BLACK)
		{
			SetColor(15, 0);
			if (q == leaf)
				cout << "leaf";
			else
			{
				SetColor(15, 0);
				cout << q->key;
				SetColor(0, 15);
				cout << endl;
				for (int i = 0; i < spaces; i++) {
					SetColor(0, 15);
					cout << ' ';
				}
				SetColor(15, 0);
				cout << q->value;
				SetColor(0, 15);
			}
			SetColor(0, 15);
			cout << endl;
		}
		else
		{
			SetColor(15, 4);
			cout << q->key;
			SetColor(0, 15);
			cout << endl;
			for (int i = 0; i < spaces; i++) {
				SetColor(0, 15);
				cout << ' ';
			}
			SetColor(15, 4);
			cout << q->value;
			SetColor(0, 15);
			cout << endl;
		}


		if (q != leaf)
			printTree(index, spaces + 4, q->left);
		if (q != leaf)
			index++;
	}
}

template<typename T0, typename T1>
void Map<T0, T1>::printList(Node<T0, T1>* current)
{
	if (current == leaf)
		return;
	printList(current->left);

	cout << current->key << " - " << current->value << endl;

	printList(current->right);
}

template <typename T0, typename T1>
void Map<T0, T1>::insert(Node<T0, T1>* parent, T0 key, T1 value)
{
	if (key == parent->key)
		throw exception("attempt to add an existant key into map");
	else if (key < parent->key)
	{
		if (parent->left != leaf)
			insert(parent->left, key, value);
		else
		{
			parent->left = new Node<T0, T1>(key, value, parent, leaf, leaf);
			size++;
			if (parent->color == RED)
				uncleCheck(parent->left);
		}
	}
	else
	{
		if (parent->right != leaf)
			insert(parent->right, key, value);
		else
		{
			parent->right = new Node<T0, T1>(key, value, parent, leaf, leaf);
			size++;
			if (parent->color == RED)
				uncleCheck(parent->right);
		}
	}
}


template <typename T0, typename T1>
void Map<T0, T1>::uncleCheck(Node<T0, T1>* node)
{
	Node<T0, T1>* parent = node->parent;
	Node<T0, T1>* grandparent = parent->parent;

	if (grandparent->left == parent)
	{
		Node<T0, T1>* uncle = grandparent->right;

		if (uncle->color == RED)
		{
			parent->color = BLACK;
			uncle->color = BLACK;
			if (grandparent == root)
				return;
			grandparent->color = RED;
			if (grandparent->parent->color == RED)
				uncleCheck(grandparent);
		}
		else
		{


			if (parent->right == node)
			{
				parent->right = node->left;
				parent->right->parent = parent;
				parent->parent = node;
				node->parent = grandparent;
				node->left = parent;
				grandparent->left = node;

				node = parent;
				parent = parent->parent;
			}


			grandparent->left = parent->right;
			if (grandparent->left != leaf)
				grandparent->left->parent = grandparent;
			grandparent->left->parent = grandparent;
			parent->right = grandparent;

			parent->parent = grandparent->parent;

			if (grandparent != root)
			{
				if (grandparent->parent->left == grandparent)
					grandparent->parent->left = parent;
				else
					grandparent->parent->right = parent;
			}
			else
				root = parent;

			grandparent->parent = parent;

			parent->color = BLACK;
			grandparent->color = RED;


		}
	}
	else
	{


		Node<T0, T1>* uncle = grandparent->left;

		if (uncle->color == RED)
		{
			parent->color = BLACK;
			uncle->color = BLACK;
			if (grandparent == root)
				return;
			grandparent->color = RED;
			if (grandparent->parent->color == RED)
				uncleCheck(grandparent);
		}
		else
		{
			if (parent->left == node)
			{
				parent->left = node->right;
				parent->left->parent = parent;
				parent->parent = node;
				node->parent = grandparent;
				node->right = parent;
				grandparent->right = node;

				node = parent;
				parent = parent->parent;
			}

			Node<T0, T1>* sibling = parent->left;

			grandparent->right = parent->left;
			if (grandparent->right != leaf)
				grandparent->right->parent = grandparent;
			parent->left = grandparent;

			parent->parent = grandparent->parent;

			if (grandparent != root)
			{
				if (grandparent->parent->right == grandparent)
				{
					grandparent->parent->right = parent;
				}
				else
					grandparent->parent->left = parent;
			}
			else
				root = parent;

			grandparent->parent = parent;

			parent->color = BLACK;
			grandparent->color = RED;


		}
	}
}

template <typename T0, typename T1>
void Map<T0, T1>::remove(Node<T0, T1>* node)
{
	if (node->left == leaf && node->right == leaf)
	{
		if (node == root)
		{
			root = nullptr;
			delete node;
			size--;
		}
		else if (node->color == RED)
		{
			if (node->parent->left == node)
				node->parent->left = leaf;
			else
				node->parent->right = leaf;
			delete node;
			size--;
		}
		else
			removeFIX(node, true);
	}
	else if ((node->left != leaf) && (node->right == leaf))
	{
		if (node == root)
		{
			root = node->left;
			node->left->parent = nullptr;
			node->left->color = BLACK;
			delete node;
			size--;
		}
		else if (node->color == RED)
		{
			if (node->parent->left == node)
			{
				node->parent->left = node->left;
				node->left->parent = node->parent;
			}
			else
			{
				node->parent->right = node->left;
				node->left->parent = node->parent;
			}
			delete node;
			size--;
		}
		else
			removeFIX(node, true);

	}
	else if ((node->right != leaf) && (node->left == leaf))
	{
		if (node == root)
		{
			root = node->right;
			node->right->parent = nullptr;
			node->right->color = BLACK;
			delete node;
			size--;
		}
		else if (node->color == RED)
		{
			if (node->parent->left == node)
			{
				node->parent->left = node->right;
				node->right->parent = node->parent;
			}
			else
			{
				node->parent->right = node->right;
				node->right->parent = node->parent;
			}
			delete node;
			size--;
		}
		else
			removeFIX(node, true);
	}
	else
	{
		Node<T0, T1>* current = node->right;
		while (current->left != leaf)
			current = current->left;
		node->key = current->key;
		node->value = current->value;
		remove(current);
	}
}

template <typename T0, typename T1>
void Map<T0, T1>::removeFIX(Node<T0, T1>* node, bool leafs)
{


	Node<T0, T1>* parent = node->parent;
	bool nodeLeft;

	if (leafs == true)
	{
		if (node->left != leaf)
		{
			node->left->parent = parent;
			node->left->color = BLACK;
			if (node == parent->left)
				parent->left = node->left;
			else
				parent->right = node->left;
			delete node;
			size--;
			return;
		}
		else if (node->right != leaf)
		{
			node->right->parent = parent;
			node->right->color = BLACK;
			if (node == parent->left)
				parent->left = node->right;
			else
				parent->right = node->right;
			delete node;
			size--;
			return;
		}
		else
		{
			if (node == parent->left)
			{
				nodeLeft = true;
				parent->left = leaf;
			}
			else
			{
				nodeLeft = false;
				parent->right = leaf;
			}
			delete node;
			size--;
		}
	}


	Node<T0, T1>* grandparent = parent->parent;
	Node<T0, T1>* sibling;
	if (leafs == true)
	{
		if (nodeLeft)
			sibling = parent->right;
		else
			sibling = parent->left;
	}
	else
	{
		if (node == parent->left)
		{
			nodeLeft = true;
			sibling = parent->right;
		}

		else
		{
			nodeLeft = false;
			sibling = parent->left;
		}
	}

	Node<T0, T1>* SL = sibling->left;
	Node<T0, T1>* SR = sibling->right;


	if (sibling->color == RED)
	{
		parent->parent = sibling;
		SL->parent = parent;


		if (root == parent)
		{
			root = sibling;
			sibling->parent = nullptr;
		}
		else
		{
			if (grandparent->left == parent)
				grandparent->left = sibling;
			else
				grandparent->right = sibling;
			sibling->parent = grandparent;
		}

		if (nodeLeft == true)
		{
			parent->right = SL;
			sibling->left = parent;
		}
		else
		{
			parent->left = SL;
			sibling->right = parent;
		}

		parent->color = RED;
		sibling->color = BLACK;

		sibling = SL;
		SL = sibling->left;
		SR = sibling->right;
	}

	if (parent->color == BLACK && sibling->color == BLACK && SL->color == BLACK && SR->color == BLACK) 
	{
		sibling->color = RED;
		removeFIX(parent, false);
		return;
	}

	if (sibling->color == BLACK && SL->color == BLACK && SR->color == BLACK && parent->color == RED)
	{
		parent->color = BLACK;
		sibling->color = RED;
		return;
	}

	if (nodeLeft == true)
	{
		if (SL->color == RED && SR->color == BLACK)
		{
			SL->parent = parent;
			parent->right = SL;
			SL->right->parent = sibling;
			sibling->left = SL->right;
			SL->right = sibling;
			sibling->parent = SL;
			SL->color = BLACK;
			sibling->color = RED;
			sibling = SL;
			SL = SL->left;
			SR = sibling;
		}

		if (SR->color == RED)
		{
			sibling->color = parent->color;
			parent->color = BLACK;
			SR->color = BLACK;
			parent->right = SL;
			SL->parent = parent;
			sibling->left = parent;
			parent->parent = sibling;
			if (root == parent)
			{
				root = sibling;
				sibling->parent = nullptr;
			}
			else
			{
				sibling->parent = grandparent;
				if (grandparent->left == parent)
					grandparent->left = sibling;
				else
					grandparent->right = sibling;
			}
		}
	}
	else
	{
		if (SR->color == RED && SL->color == BLACK)
		{
			SR->parent = parent;
			parent->left = SR;
			SR->left->parent = sibling;
			sibling->right = SR->left;
			SR->left = sibling;
			sibling->parent = SR;
			SR->color = BLACK;
			sibling->color = RED;
			sibling = SR;
			SL = sibling;
			SR = SR->right;
		}

		if (SL->color == RED)
		{
			sibling->color = parent->color;
			parent->color = BLACK;
			SL->color = BLACK;
			parent->left = SR;
			SR->parent = parent;
			sibling->right = parent;
			parent->parent = sibling;
			if (root == parent)
			{
				root = sibling;
				sibling->parent = nullptr;
			}
			else
			{
				sibling->parent = grandparent;
				if (grandparent->left == parent)
					grandparent->left = sibling;
				else
					grandparent->right = sibling;
			}
		}
	}

	leaf->color = BLACK;
	leaf->parent = nullptr;
	leaf->left = nullptr;
	leaf->right = nullptr;
}

template <typename T0, typename T1>
void Map<T0, T1>::clear(Node<T0, T1>* node)
{
	if (node == leaf)
		return;
	clear(node->left);
	clear(node->right);
	delete node;
	size--;
}

template <typename T0, typename T1>
void Map<T0, T1>::keyFill(List<T0>& lst, Node<T0, T1>* current)
{
	if (current == leaf)
		return;
	keyFill(lst, current->left);
	lst.push_back(current->key);
	keyFill(lst, current->right);
}

template <typename T0, typename T1>
void Map<T0, T1>::valueFill(List<T1>& lst, Node<T0, T1>* current)
{
	if (current == leaf)
		return;
	valueFill(lst, current->left);
	lst.push_back(current->value);
	valueFill(lst, current->right);
}