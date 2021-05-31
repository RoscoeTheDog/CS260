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

    ~ChainedHash() {
		// iterate through the table
    	for (int i = 0; i < size; ++i) {
			// fetch the head link from position
    		Node *head = table[i];

    		// iterate through the links and delete each node.
    		while (head) {

    			// create another pointer representing the iterating link
    			Node *n = head;

    			// go to very last node (*not* tail)
    			while (n->next) {
				    n = n->next;
    			}
    			// terminate the next link from last node
    			if (n->prev) {
    				n->prev->next = nullptr;
    			}
    			else {
				    // delete the head, if no previous
				    delete n;
				    table[i] = nullptr;
				    break;
    			}

			    // delete the tail node
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
