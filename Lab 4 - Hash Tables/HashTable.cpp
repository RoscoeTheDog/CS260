//
// Created by admin on 4/20/2021.
//

#include "HashTable.hpp"

void HashTable::addItem(int value) {

    // update member 'index' which will check first the hashed value.
    ind = value;

    // findAvail recursively checks next location.
    ind = findAvail(ind);

    int * store = new int;
    store = &ind;

    table[hash(value)] = &ind;

}

// by returning a member's reference.
int &HashTable::hash(int key) {
    ind = key % size;

    return ind;
}

int HashTable::findAvail(int i) {
    // calculate hash.
    // if position taken on the table, call again by ++calculated index
    if (table[hash(i)])
        return findAvail(++ind);

    return ind;
}
