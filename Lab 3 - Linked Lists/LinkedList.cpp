//
// Created by admin on 4/14/2021.
//

#include "LinkedList.h"

void LinkedList::addHead(char32_t value)
{
    Node * tmp_h = new Node;

    if (!this->head){
        this->head = tmp_h;
        this->tail = tmp_h;
    }
    else{
        this->head->head = tmp_h;
        tmp_h->next = this->head;
    }

}

void LinkedList::findNext(char32_t value)
{
    Node * workingNode = this->lastNode;

    while(workingNode){

        if(workingNode->value.value() == value) {
            this->lastNode = workingNode;
            break;
        }

        workingNode = workingNode->next;
    }
}

void LinkedList::addTail(char32_t value)
{
    Node * tmp_n = new Node;

    if(!tail){
        this->tail = tmp_n;
        this->head = tmp_n;
    }
    else{
        this->tail->next = tmp_n;
        tmp_n->head = this->tail;
        this->tail = tmp_n;
    }

}

void LinkedList::removeHead()
{
    if (!this->head)
        throw std::out_of_range("Linked list is empty");

    Node * tmp_n = this->head->next;

    delete this->head;
    this->head = tmp_n;
    this->head->head = nullptr;
}

void LinkedList::removeTail()
{
    if(!this->tail)
        throw std::out_of_range("Linked list is empty");

    Node * tmp_n = this->tail->head;

    delete this->tail;
    this->tail = tmp_n;
    this->tail->next = nullptr;
}

bool LinkedList::find(char32_t value)
{
    Node * workingNode = this->head;

    while(workingNode){

        if(workingNode->value.value() == value)
            return true;

        workingNode = workingNode->next;
    }

    return false;
}

bool LinkedList::findRemove(char32_t value)
{
    Node * workingNode = this->head;
    Node * workingHead;
    Node * workingNext;

    while(workingNode){

        if(workingNode->value.value() == value){
            workingHead = workingNode->head;
            workingNext = workingNode->next;
            if(this->head == workingNode)
                this->head = workingNext;
            if(this->tail == workingNode)
                this->tail = workingHead;
            delete workingNode;
            workingHead->next = workingNext;
            workingNext->head = workingHead;
            return true;
        }

        workingNode = workingNode->next;
    }

    return false;
}

std::string LinkedList::displayList(char32_t c)
{
    std::stringstream S;
    Node * workingNode = this->head;

    while(workingNode){

        if(workingNode->value){
            S << workingNode->value.value();
        }

        workingNode = workingNode->next;
    }

    return S.str();
}

void LinkedList::removeLast()
{
    Node * workingHead;
    Node * workingNext;

    if(this->lastNode) {
        workingHead = this->lastNode->head;
        workingNext = this->lastNode->next;
        if (this->head == workingHead)
            this->head = workingNext;
        if (this->tail == workingNext)
            this->tail = workingHead;
        delete this->lastNode;
        this->lastNode = nullptr;
    }

}

void LinkedList::insertLast(char32_t value)
{
    if(this->lastNode){
        Node * tmp_n = new Node;

        tmp_n->head = this->lastNode->head;
        tmp_n->next = this->lastNode;
        this->lastNode->head = tmp_n;
    }
}
