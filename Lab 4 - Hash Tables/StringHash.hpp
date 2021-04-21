//
// Created by admin on 4/20/2021.
//


#ifndef LAB_4___HASH_TABLES_STRINGHASH_HPP
#define LAB_4___HASH_TABLES_STRINGHASH_HPP

#include <cstring>
#include <sstream>
#include <cstdio>
#include <iostream>


class StringHash {
private:
    unsigned size;
    unsigned length;
    std::string *table;
    std::string EMPTY = "_empty_";
    std::string DELETED = "_deleted_";

    // having key be a class member is not necessary but makes code a bit easier to understand.
    int key; // key == the 'weight' of the string in ASCII
    int ind; // ind == the actual hashed table index of the key.

public:

    StringHash() {
        size = 11;
        length = 0;
        table = new std::string[size];

        for (unsigned i = 0; i < size; ++i) {
            table[i] = EMPTY;
        }

    };

    StringHash(unsigned size) {
        this->size = size;
        length = 0;
        table = new std::string[this->size];

        for (unsigned i = 0; i < this->size; ++i) {
            table[i] = EMPTY;
        }
    }

    ~StringHash() {
        delete[] table;
    }

    void addItem(std::string &value);

    bool findItem(const std::string &value);

    int findAvail(int value);

    void removeItem(const std::string &value);

    std::string displayTable();

    void resize(unsigned size);

    int &hash(int value);

    long encode(std::string s);
};

#endif //LAB_4___HASH_TABLES_STRINGHASH.HPP