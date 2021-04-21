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
    std::list<std::string> *table;

    // having key be a class member is not necessary but makes code a bit easier to understand.
    int key; // key == the 'weight' of the string in ASCII
    int ind; // ind == the actual hashed table index of the key.

public:

    ChainedHash() {
        size = 11;
        length = 0;
        table = new std::list<std::string>[size];
    };

    ChainedHash(unsigned size) {
        this->size = size;
        length = 0;
        table = new std::list<std::string>[this->size];
    }

    ~ChainedHash() {
        delete[] table;
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
