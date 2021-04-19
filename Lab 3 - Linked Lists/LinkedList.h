//
// Created by admin on 4/14/2021.
//

#ifndef LAB_3___LINKED_LISTS_LINKEDLIST_H
#define LAB_3___LINKED_LISTS_LINKEDLIST_H

#include <cstdint>
#include "Node.h"
#include <stdexcept>
#include <sstream>

#define LinkedList TextClass

class LinkedList
{
private:
    Node *head;
    Node *tail;
    Node *lastNode;

public:

    LinkedList()
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->lastNode = nullptr;
    }

    ~LinkedList()
    {
        while (this->head)
            removeHead();
    }

    void addHead(char32_t value);

    void addTail(char32_t value);

    char32_t getHead();;

    char32_t getTail();;

    void removeHead();

    void removeTail();

    bool find(char32_t value);

    bool findRemove(char32_t value);

    std::string displayList();

    void append(LinkedList List);

    bool findNext(char32_t value);

    void removeLast();

    void insertLast(char32_t value);

};


#endif //LAB_3___LINKED_LISTS_LINKEDLIST_H
