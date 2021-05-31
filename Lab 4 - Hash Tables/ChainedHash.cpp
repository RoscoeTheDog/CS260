//
// Created by admin on 4/20/2021.
//

#include "ChainedHash.hpp"

void ChainedHash::addItem(std::string &value) {

	if (length >= (size - 1) / 2) {
		resize(size * 2);
	}

	key = encode(value);
	index = hash(key);

	// get the node at the table
	Node *n = table[index];

	// create new node, passing in value.
	Node *_new = new Node(value);

	// check if a link exists at the table
	if (n) {
		// if it does, traverse to tail
		while (n->next) {
			n = n->next;
		}

		// link together old tail to new tail.
		n->next = _new;
		_new->prev = n;
	}
		// if table doesn't have a valid node, just copy new one into table.
	else {
		table[index] = _new;
	}

	// update table length.
	length++;
}


void ChainedHash::removeItem(const std::string &value) {

	key = encode(value);

	index = hash(key);

	Node *n = table[index];
	Node *previous = nullptr;
	Node *next = nullptr;

	while (n) {

		if (n->value == value) {

			if (n->prev) {
				previous = n->prev;
			}

			if (n->next) {
				next = n->next;
			}

			delete n;

			if (previous) {
				previous->next = next;
			}
			if (next) {
				next->prev = previous;
			}

			break;
		}

		n = n->next;
	}

	// reset old index to null.
	table[index] = nullptr;

	// update table length
	length--;
}

bool ChainedHash::findItem(const std::string &value) {

	key = encode(value);

	index = hash(key);

	Node *n = table[index];

	while (n) {

		if (n->value == value) {
			return true;
		}

		// continue until value is found or tail is hit
		if (n->next) {
			n = n->next;
		}

	}

	return false;
}

std::string ChainedHash::displayTable() {

	std::stringstream S;

	Node *n = nullptr;
	for (int i = 0; i < size; ++i) {

		n = table[i];

		// iterate through links and push to string buffer
		while (n) {
			S << n->value << " ";
			n = n->next;
		}

	}
	return S.str();
}

void ChainedHash::resize(unsigned size) {

	if (size < this->size) {
		throw std::out_of_range("new size cannot be made smaller or data will be lost");
	}

	// create new table
	Node **extended;
	extended = new Node*[size];
	// initialize all Node * to null
	for (int i = 0; i < size; ++i) {
		extended[i] = nullptr;
	}

	// save old size since rehashing requires updating over it.
	int oldSize = this->size;
	// update size before rehashing.
	this->size = size;

	// iterate through the array
	for (int i = 0; i < oldSize; ++i) {

		// check if table has a valid pointer.
		if (table[i]) {

			// get ptr from table
			Node *copyNode = table[i];

			// rehash each link from head of pointer
			while (copyNode) {

				key = encode(copyNode->value);
				index = hash(key);

				// see if any entry exists on the new table index or not.
				if (extended[index]) {

					// get the head from the new index
					Node *n = extended[index];

					// find tail
					while (n) {
						n = n->next;
					}

					// copy at the tail
					n = copyNode;
				}
					// if no node exists @ new index beforehand, simply copy to table.
				else {
					extended[index] = copyNode;
				}

				copyNode = copyNode->next;
			}

		}

	}

	delete[]table;
	table = extended;
	this->size = size;

}

int &ChainedHash::hash(int s) {
	// keeping all of this local is fine, just remember these are not the class member's key.
	index = key % size;

	return index;
}

long ChainedHash::encode(std::string s) {

	long weight = 0;
	char c;

	for (char i : s) {
		c = i;
		weight += static_cast<int>(c);
	}

	return weight;
}
