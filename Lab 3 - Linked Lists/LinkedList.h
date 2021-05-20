//
// Created by admin on 4/14/2021.
//

#ifndef LAB_3___LINKED_LISTS_LINKEDLIST_H
#define LAB_3___LINKED_LISTS_LINKEDLIST_H

#include <cstdint>
#include "Node.h"
#include <stdexcept>
#include <sstream>

#define LinkedList TextClass

class LinkedList {
private:
	Node *head;
	Node *tail;
	// lastFound holds a reference to the last node that is not cleared after invoking findNext.
	Node *lastFound;

public:

	LinkedList() {

		head = nullptr;
		tail = nullptr;
		lastFound = nullptr;
	}

	~LinkedList() {

		while (head) {
			removeHead();
		}
	}

	void addHead(char value);

	void addTail(char value);

	char getHead();;

	char getTail();;

	void removeHead();

	void removeTail();

	bool find(char value);

	bool findRemove(char value);

	std::string displayList();

	void append(LinkedList List);

	bool findNext(char value, Node *n = nullptr);

	void removeLast();

	void insertLast(char value);

};


#endif //LAB_3___LINKED_LISTS_LINKEDLIST_H
