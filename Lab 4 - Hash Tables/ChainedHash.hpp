//
// Created by admin on 4/20/2021.
//

#ifndef LAB_4___HASH_TABLES_CHAINEDHASH_HPP
#define LAB_4___HASH_TABLES_CHAINEDHASH_HPP


#include <cstring>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <list>

class ChainedHash {
private:
    unsigned size;
    unsigned length;

	typedef struct Node {

		Node(std::string value) {
			this->value = value;
		}

		Node * prev = nullptr;
		Node * next = nullptr;
		std::string value;
	} Node;

    Node **table = nullptr;

    // having key be a class member is not necessary but makes code a bit easier to understand.
    int key; // key == the 'weight' of the string in ASCII
    int index; // index == the actual hashed table index of the key.

public:

    ChainedHash() {
        size = 11;
        length = 0;
	    table = new Node*[size];

	    for (int i = 0; i < size; ++i) {
	    	table[i] = nullptr;
	    }
    };

    ChainedHash(unsigned size) {
        this->size = size;
        length = 0;
	    table = new Node*[size];

	    for (int i = 0; i < size; ++i) {
		    table[i] = nullptr;
	    }
    }

    //TODO: resolve endless next links
    ~ChainedHash() {

    	for (int i = 0; i < size; ++i) {

    		Node *head = table[i];

    		// while head
    		while (head) {

    			// copy pointer so we can iterate through easier
    			Node *n = head;

    			// go to last node
    			while (n->next) {
				    n = n->next;
    			}
    			// clear link from prev
    			if (n->prev) {
    				n->prev = nullptr;
    			}
    			// delete tail
    			delete n;
    		}

    	}
        delete[]table;
    }

    void addItem(std::string &value);

    void removeItem(const std::string &value);

    bool findItem(const std::string &value);

    std::string displayTable();

    void resize(unsigned size);

    int &hash(int value);

    long encode(std::string s);
};

#endif //LAB_4___HASH_TABLES_CHAINEDHASH_HPP
