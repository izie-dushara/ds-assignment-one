#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class LinkedListCustom
{
private:
	struct LLNode
	{
		T data;
		LLNode *nextAddress = nullptr;
	};

	LLNode *head;
	LLNode *tail;
	int size;

public:
	LinkedListCustom();
	~LinkedListCustom();

	void add(const T &data);
	T get(int index) const;
	int getSize() const;
	void clear();
};

template <typename T>
LinkedListCustom<T>::LinkedListCustom() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
LinkedListCustom<T>::~LinkedListCustom()
{
	clear();
}

template <typename T>
void LinkedListCustom<T>::add(const T &data)
{
	LLNode *newNode = new LLNode();
	newNode->data = data;
	newNode->nextAddress = nullptr;

	if (!head)
	{
		head = tail = newNode;
	}
	else
	{
		tail->nextAddress = newNode;
		tail = newNode;
	}
	size++;
}

template <typename T>
T LinkedListCustom<T>::get(int index) const
{
	if (index < 0 || index >= size)
		throw std::out_of_range("Index is outside the range given");

	LLNode *current = head;
	for (size_t i = 0; i < index; i++)
		current = current->nextAddress;
	
	return current->data;
}

template <typename T>
int LinkedListCustom<T>::getSize() const
{
	return size;
}

template <typename T>
void LinkedListCustom<T>::clear()
{
	LLNode *current = head;
	while (current)
	{
		LLNode *next = current->nextAddress;
		delete current;
		current = next;
	}
	head = tail = nullptr;
	size = 0;
}