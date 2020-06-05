#pragma once

using namespace std;

#include <iostream>

template<typename T>
class List
{
public:
	List();
	~List();

	void pop_front(); 
	void pop_back(); 
	void push_back(T data);
	void push_front(T data); 
	void insert(T value, int index); 
	void clear(); 
	void removeAt(int index); 
	unsigned int GetSize() 
	{
		return Size;
	}
	T& operator[] (const int index); 
	void print_to_console(); 
	void set(T value, int index); 
	bool isEmpty(); 


	int search_lastest(List<T>& search);         // Compare 2 lists. Get first element (bigger list, not in ()) index where Comparison starts, or get -1 if there is no Comparison. 
private:


	template<typename T>
	class Node
	{
	public:
		Node* pNext;                        // Next element 
		Node* pPrev;                    // pPrev element 
		T data;

		Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr)               // By default
		{
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
	};
	int Size;                           
	Node<T>* head;                       
	Node<T>* tail;                       
};


template<typename T>
List<T>::List()                // Constructor
{
	Size = 0;                  // when just created, list size is always 0
	head = nullptr;            // by default, next and prev pointers are nullptr
	tail = nullptr;
}


template<typename T>
List<T>::~List()                // Destructor
{
	clear();
}


template<typename T>
void List<T>::pop_front()
{
	if (Size == 0)
		throw exception("List is empty, pop_front() didn't work");
	Node<T>* temp = head;
	head = head->pNext;
	delete temp;
	Size--;
}


template<typename T>
void List<T>::pop_back()
{
	if (Size == 0)
		throw exception("List is empty, pop_back() didn't work");
	removeAt(Size - 1);
}

template<typename T>
void List<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
		tail = head;
	}
	else
	{
		Node<T>* temp = new Node<T>(data);
		temp->pNext = nullptr;
		temp->pPrev = tail;
		tail->pNext = temp;
		tail = temp;
	}
	Size++;
}


template<typename T>
void List<T>::push_front(T data)
{
	head = new Node<T>(data, head);
	Size++;
	if (Size == 1)
		tail = head;
}


template<typename T>
void List<T>::insert(T data, int index)
{
	if (index == 0)
		push_front(data);
	else
	{
		if (index < 0)
			throw exception("Index (insert(data, index)) is negative");
		if (index > Size)
			throw exception("Index (insert(data, index)) is bigger than list size + 1");
		Node<T>* pPrev = this->head;
		Node<T>* nex = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			pPrev = pPrev->pNext;
			nex = nex->pNext;
		}
		Node<T>* newNode = new Node<T>(data, pPrev->pNext);
		pPrev->pNext = newNode;

		nex = nex->pNext;
		nex->pPrev = pPrev;
		if (index != Size)
		{
			pPrev = pPrev->pNext;
			nex = nex->pNext;
			nex->pPrev = pPrev;
		}
		else
			tail = nex;

		Size++;
	}
}


template<typename T>
void List<T>::clear()
{
	while (Size)
		pop_front();
}


template<typename T>
void List<T>::removeAt(int index)
{
	if (index == 0)
		pop_front();
	else
	{
		if (index < 0)
			throw exception("Index (removeAt(index)) is negative");
		if (index >= Size)
			throw exception("Index (removeAt(index)) is bigger than list size");
		Node<T>* pPrev = this->head;
		for (int i = 0; i < index - 1; i++)
			pPrev = pPrev->pNext;
		Node<T>* toDelete = pPrev->pNext;
		if (index != Size - 1)
		{
			Node<T>* nex = toDelete->pNext;
			nex->pPrev = pPrev;
		}
		else
			tail = pPrev;
		pPrev->pNext = toDelete->pNext;
		delete toDelete;
		Size--;
	}
}


template<typename T>
T& List<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* current = this->head;
	while (current != nullptr)
	{
		if (counter == index)
			return current->data;
		current = current->pNext;
		counter++;
	}
}

template<typename T>
void List<T>::print_to_console()
{
	Node<T>* current = this->head;
	if (Size == 0)
		cout << "List is empty";
	else
		while (current != nullptr)
		{
			cout << current->data << endl;
			current = current->pNext;
		}
}

template<typename T>
void List<T>::set(T data, int index)
{
	if (index < 0)
		throw exception("Index (set(data, index)) is negative");
	if (index >= Size)
		throw exception("Index (set(data, index)) is bigger than list size");
	int counter = 0;
	Node<T>* current = this->head;
	while (current != nullptr)
	{
		if (counter == index)
			break;
		current = current->pNext;
		counter++;
	}

	current->data = data;

}

template<typename T>
bool List<T>::isEmpty()
{
	if (Size == 0)
		return true;
	else
		return false;
}

template<typename T>
int List<T>::search_lastest(List<T>& search)
{
	if (Size == 0)
		throw exception("Main list contains 0 items, findlast() didn't work");
	if (search.GetSize() > Size)
		throw exception("Included list is bigger than main one, findlast() didn't work");
	if (search.GetSize() == 0)
		throw exception("Included list contains 0 items, findlast() didn't work");
	Node<T>* field = this->tail;
	int Count_step = 0;
	bool Comparison = false;
	for (int i = Size - 1; i >= 0; i--)
	{
		if (field->data == search[search.GetSize() - 1])
		{
			Count_step = 0;
			for (int j = search.GetSize() - 2; j >= 0; j--)
			{
				Count_step++;
				field = field->pPrev;
				if (field->data != search[j])
				{
					Comparison = false;
					for (int k = 0; k < Count_step; k++)
						field = field->pNext;
					Count_step = 0;
					break;
				}
				if (j == 0)
					Comparison = true;
			}
			if ((Comparison == true) || (search.GetSize() == 1))
			{
				return (i - Count_step);
			}
		}
		field = field->pPrev;
	}
	return -1;
}