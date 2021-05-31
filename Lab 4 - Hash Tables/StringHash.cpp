//
// Created by admin on 4/20/2021.
//

#include "StringHash.hpp"

void StringHash::addItem(std::string &value) {

    if (length >= (size - 1) / 2)
        resize(size * 2);

    key = encode(value);

    // findAvail recursively checks next location.
    ind = findAvail(hash(key));

    table[ind] = value;
    ++length;
}

// by returning a member's reference.
int &StringHash::hash(int key) {
    // keeping all of this local is fine, just remember these are not the class member's key.
    ind = key % size;

    return ind;
}

int StringHash::findAvail(int i) {

    // catch wrap
    if (i > size - 1)
        i = 0;

    // calculate hash.
    // if position taken on the chainLink, call again by ++calculated index
    if (table[i] == EMPTY ||
        table[i] == DELETED) {
        return i;
    }

    return findAvail(++i);
}

std::string StringHash::displayTable() {
    std::stringstream S;

    for (int i = 0; i < size; ++i) {
        S << table[i] << " ";
    }

    return S.str();
}

void StringHash::resize(unsigned size) {

    if (size < this->size)
        throw std::out_of_range("new size cannot be smaller or data is lost");

    std::string *table_ = new std::string[size];

    // This ugly way of deep copying was helpful for ruling things out during debugging
    // I'm sure it can be cleaned up.
    for (unsigned i = 0; i < size - 1; ++i) {

        // cpy only if within old chainLink's range.
        if (i < this->size and
            table[i] not_eq EMPTY)
            table_[i] = table[i];
            // otherwise just initialize value
        else
            table_[i] = EMPTY;
    }

    // rehash previous entries
    for (unsigned i = 0; i < size - 1; ++i) {
        // validate if within old chainLink range or not.
        if (i < this->size and
            table[i] not_eq EMPTY) {
            key = encode(table[i]);
            ind = hash(key);
            table_[ind] = table[i];
        }
    }

    // cleanup.
    delete[] table;
    table = table_;
    this->size = size;
}

long StringHash::encode(std::string s) {
    long weight = 0;
    char c;

    for (char i : s) {
        c = i;
        weight += static_cast<int>(c);
    }

    return weight;
}

bool StringHash::findItem(const std::string &value) {

    key = encode(value);

    ind = hash(key);

    if (table[ind] == value)
        return true;

    return false;

}

void StringHash::removeItem(const std::string &value) {

    key = encode(value);

    ind = hash(key);

    if (table[ind] == value) {
        table[ind] = DELETED;
        --length;
    }
}


