//
// Created by admin on 4/14/2021.
//

#ifndef LAB_3___LINKED_LISTS_LINKEDLIST_H
#define LAB_3___LINKED_LISTS_LINKEDLIST_H
#include <cstdint>
#include "Node.h"
#include <stdexcept>
#include <sstream>

class LinkedList
{
private:
    Node * head;
    Node * tail;
    Node * lastNode;

public:

    LinkedList(){ this->head = nullptr; this->tail = nullptr;}

    void addHead(char32_t value);

    void addTail(char32_t value);

    Node * getHead(){ return this->head; };

    Node * getTail() { return this->tail; };

    void removeHead();

    void removeTail();

    bool find(char32_t value);

    bool findRemove(char32_t value);

    std::string displayList(char32_t c);

    void append(LinkedList * List);

    void findNext(char32_t value);

    void removeLast();

    void insertLast(char32_t value);

};


#endif //LAB_3___LINKED_LISTS_LINKEDLIST_H
