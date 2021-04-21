//
// Created by admin on 4/20/2021.
//

#include "ChainedHash.hpp"

void ChainedHash::addItem(std::string &value) {
    if (length >= (size - 1) / 2)
        resize(size * 2);

    key = encode(value);
    ind = hash(key);

    // pre increment and then push link.
    if (table[ind].empty())
        ++length;

    table[ind].push_front(value);
}


void ChainedHash::removeItem(const std::string &value) {

    key = encode(value);

    ind = hash(key);

    if (!table[ind].empty())
        for (std::list<std::string>::iterator it = table[ind].begin(); it != table[ind].end(); ++it) {
            if (*it == value) {
                table[ind].erase(it);
                break;  // needed to escape from endless loop if deleted == last node.
            }

        }
    else {
        table[ind].push_front(value);
        --length;
    }

}

bool ChainedHash::findItem(const std::string &value) {

    key = encode(value);

    ind = hash(key);

    if (!table[ind].empty())
        for (std::list<std::string>::iterator it = table[ind].begin(); it != table[ind].end(); ++it) {
            if (*it == value)
                return true;
        }

    return false;
}

std::string ChainedHash::displayTable() {
    std::stringstream S;

    for (unsigned i = 0; i < size; ++i) {
        if (!table[i].empty()) {
            for (std::list<std::string>::iterator it = table[i].begin(); it != table[i].end(); ++it) {
                S << *it << " ";
            }
        }
    }

    return S.str();
}

void ChainedHash::resize(unsigned size) {

    if (size < this->size)
        throw std::out_of_range("new size cannot be made smaller or data will be lost");

    std::list<std::string> *table_ = new std::list<std::string>[size];

    // begin rehashing/deep copying
    for (unsigned i = 0; i < size - 1; ++i) {
        // validate if in old table range or not.
        if (i < this->size) {
            // is empty??
            if (not table[i].empty()) {
                // iter through all nodes
                for (std::list<std::string>::iterator it = table[i].begin(); it != table[i].end(); ++it) {
                    // rehash values
                    key = encode(*it);
                    ind = hash(key);
                    // I've been doing push front, pop back (FIFO). Here I'll push back to maintain order since Iter starts at front.
                    table_[ind].push_back(*it);
                }
            }
        }
    }

    delete[] table;
    table = table_;
    this->size = size;
}

int &ChainedHash::hash(int s) {
    // keeping all of this local is fine, just remember these are not the class member's key.
    ind = key % size;

    return ind;
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
