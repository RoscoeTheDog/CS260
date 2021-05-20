//
// Created by admin on 4/14/2021.
//

#include "LinkedList.h"

void LinkedList::addHead(char value) {

	Node *tmp_h = new Node;
	tmp_h->value = value;

	if (!head) {
		head = tmp_h;
		tail = tmp_h;
	}
	else {
		head->prev = tmp_h;
		tmp_h->next = head;
		head = tmp_h;
	}

}

bool LinkedList::findNext(char value, Node *n) {
	// check for passed in args. start from last saved node
	if (n == nullptr) {
		// if find/findNext never invoked, lastFound will be nullptr. start from head
		if (lastFound == nullptr) {
			n = head;
		}
		else {
			n = lastFound;
		}

	}

	// look for next entry of value.
	if (n->value == value && n != lastFound) {
		// update saved node.
		lastFound = n;
		return true;
	}

	// lookahead to see if we reached tail of list.
	if (n->next == nullptr) {
		// wrap to head
		return findNext(value, head);
	}

	// if wrapped around all the way back to last found node, exit.
	if (n->next == lastFound) {
		return false;
	}

	// go to next node.
	return findNext(value, n->next);
}

void LinkedList::addTail(char value) {

	Node *_temp = new Node;
	_temp->value = value;

	if (!tail) {
		tail = _temp;
		if (!head) {
			head = _temp;
		}
	}
	else {
		tail->next = _temp;
		_temp->prev = tail;
		tail = _temp;
	}

}

void LinkedList::removeHead() {

	if (!head) {
		throw std::out_of_range("Linked list is empty");
	}
	// validate there actually is a next node to visit
	if (head->next) {
		Node *_temp = head->next;
		// delete the current head.
		delete head;
		// restore the head to next
		head = _temp;
		// clear next's prev link
		if (head) {
			head->prev = nullptr;
		}
	}
	else {
		delete head;
		head = nullptr;
		tail = nullptr;
	}

}

void LinkedList::removeTail() {
	// throw error if empty
	if (!tail) {
		throw std::out_of_range("Linked list is empty");
	}

	// fetch the prev node from the tail.
	Node *_temp = tail->prev;
	// delete the tail
	delete tail;
	// update
	tail = _temp;

	// ensure that prev was not nullptr.
	if (tail) {
		// update next if so
		tail->next = nullptr;
	}
	else {
		// otherwise, we know the list is completely empty.
		tail = nullptr;
		head = nullptr;
	}
}

bool LinkedList::find(char value) {

	Node *workingNode = head;

	while (workingNode) {

		if (workingNode->value == value) {
			return true;
		}

		workingNode = workingNode->next;
	}

	return false;
}

bool LinkedList::findRemove(char value) {

	Node *workingNode = head;
	Node *workingHead = nullptr;
	Node *workingNext = nullptr;

	while (workingNode) {

		if (workingNode->value == value) {
			workingHead = workingNode->prev;
			workingNext = workingNode->next;
			if (head == workingNode) {
				head = workingNext;
			}
			if (tail == workingNode) {
				tail = workingHead;
			}
			delete workingNode;
			if (workingHead) {
				workingHead->next = workingNext;
			}
			if (workingNext) {
				workingNext->prev = workingHead;
			}
			return true;
		}

		workingNode = workingNode->next;
	}

	return false;
}

std::string LinkedList::displayList() {

	std::stringstream S;
	Node *workingNode = head;

	while (workingNode) {

		if (workingNode->value) {
			S << *workingNode->value << " "; // note: a cast is required when using optional
		}

		workingNode = workingNode->next;
	}

	return S.str();
}

void LinkedList::removeLast() {

	if (this->lastFound) {

		if (head == this->lastFound) {
			head = head->next;
			head->prev = nullptr;
		}

		if (tail == this->lastFound) {
			tail = tail->prev;
			tail->next = nullptr;
		}

		if (this->lastFound->prev && this->lastFound->next) {
			this->lastFound->prev->next = this->lastFound->next;
			this->lastFound->next->prev = this->lastFound->prev;
		}

		delete this->lastFound;
		this->lastFound = nullptr;
	}

}

void LinkedList::insertLast(char value) {

	if (this->lastFound) {
		Node *_temp = new Node;
		_temp->value = value;

		if (head == this->lastFound) {
			head->prev = _temp;
			_temp->next = _temp;
			head = _temp;
		}
		if (tail == this->lastFound) {
			tail->prev = _temp;
			_temp->next = tail;
			tail = _temp;
		}
		if (this->lastFound->prev && this->lastFound->next) {
			_temp->prev = this->lastFound->prev;
			_temp->next = this->lastFound;
			this->lastFound->prev->next = _temp;
			this->lastFound->prev = _temp;
		}
	}
}

char TextClass::getHead() {

	if (!head) {
		throw std::out_of_range("List is empty");
	}

	return *head->value;
}

char TextClass::getTail() {

	if (!tail) {
		throw std::out_of_range("List is empty");
	}

	return *tail->value;
}

void TextClass::append(TextClass List) {

	while (List.head) {
		Node *_temp = new Node;
		_temp->prev = tail;
		tail->next = _temp;
		_temp->value = List.getHead();
		tail = _temp;
		List.removeHead();
	}
}
