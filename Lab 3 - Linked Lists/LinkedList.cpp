//
// Created by admin on 4/14/2021.
//

#include "LinkedList.h"

void LinkedList::addHead(char32_t value)
{
    Node *tmp_h = new Node;
    tmp_h->value = value;

    if (!this->head)
    {
        this->head = tmp_h;
        this->tail = tmp_h;
    }
    else
    {
        this->head->head = tmp_h;
        tmp_h->next = this->head;
        this->head = tmp_h;
    }

}

bool LinkedList::findNext(char32_t value)
{
    Node *workingNode = this->lastNode;

    if (workingNode)
        workingNode = workingNode->next;
    else
        workingNode = this->head;

    while (workingNode)
    {

        if (workingNode->value.value() == value)
        {
            this->lastNode = workingNode;
            return true;
        }

        workingNode = workingNode->next;

    }

    this->lastNode = nullptr;

    return false;
}

void LinkedList::addTail(char32_t value)
{
    Node *tmp_n = new Node;
    tmp_n->value = value;

    if (!tail)
    {
        this->tail = tmp_n;
        if (!head)
            this->head = tmp_n;
    }
    else
    {
        if (tail)
            this->tail->next = tmp_n;
        tmp_n->head = this->tail;
        this->tail = tmp_n;
    }

}

void LinkedList::removeHead()
{
    if (!this->head)
        throw std::out_of_range("Linked list is empty");

    Node *tmp_n = this->head->next;

    delete this->head;
    this->head = tmp_n;
    if (this->head)
        this->head->head = nullptr;
}

void LinkedList::removeTail()
{
    if (!this->tail)
        throw std::out_of_range("Linked list is empty");

    Node *tmp_n = this->tail->head;

    delete this->tail;
    this->tail = tmp_n;
    if (tail)
        this->tail->next = nullptr;
}

bool LinkedList::find(char32_t value)
{
    Node *workingNode = this->head;

    while (workingNode)
    {

        if (workingNode->value == value)
            return true;

        workingNode = workingNode->next;
    }

    return false;
}

bool LinkedList::findRemove(char32_t value)
{
    Node *workingNode = this->head;
    Node *workingHead = nullptr;
    Node *workingNext = nullptr;

    while (workingNode)
    {

        if (workingNode->value.value() == value)
        {
            workingHead = workingNode->head;
            workingNext = workingNode->next;
            if (this->head == workingNode)
                this->head = workingNext;
            if (this->tail == workingNode)
                this->tail = workingHead;
            delete workingNode;
            if (workingHead)
                workingHead->next = workingNext;
            if (workingNext)
                workingNext->head = workingHead;
            return true;
        }

        workingNode = workingNode->next;
    }

    return false;
}

std::string LinkedList::displayList()
{
    std::stringstream S;
    Node *workingNode = this->head;

    while (workingNode)
    {

        if (workingNode->value.value())
        {
            S << static_cast<char>(workingNode->value.value());
        }

        workingNode = workingNode->next;
    }

    return S.str();
}

void LinkedList::removeLast()
{
    if (this->lastNode)
    {

        if (this->head == this->lastNode)
        {
            this->head = this->head->next;
            this->head->head = nullptr;
        }

        if (this->tail == this->lastNode)
        {
            this->tail = this->tail->head;
            this->tail->next = nullptr;
        }

        if (this->lastNode->head && this->lastNode->next)
        {
            this->lastNode->head->next = this->lastNode->next;
            this->lastNode->next->head = this->lastNode->head;
        }

        delete this->lastNode;
        this->lastNode = nullptr;
    }

}

void LinkedList::insertLast(char32_t value)
{
    if (this->lastNode)
    {
        Node *tmp_n = new Node;
        tmp_n->value = value;

        if (this->head == this->lastNode)
        {
            this->head->head = tmp_n;
            tmp_n->next = tmp_n;
            this->head = tmp_n;
        }
        if (this->tail == this->lastNode)
        {
            this->tail->head = tmp_n;
            tmp_n->next = this->tail;
            this->tail = tmp_n;
        }
        if (this->lastNode->head && this->lastNode->next)
        {
            tmp_n->head = this->lastNode->head;
            tmp_n->next = this->lastNode;
            this->lastNode->head->next = tmp_n;
            this->lastNode->head = tmp_n;
        }
    }
}

char32_t TextClass::getHead()
{
    if (!this->head)
        throw std::out_of_range("List is empty");

    return this->head->value.value();
}

char32_t TextClass::getTail()
{
    if (!this->tail)
        throw std::out_of_range("List is empty");

    return this->tail->value.value();
}

void TextClass::append(TextClass List)
{
    while (List.head)
    {
        Node *tmp_n = new Node;
        tmp_n->head = this->tail;
        this->tail->next = tmp_n;
        tmp_n->value = List.getHead();
        this->tail = tmp_n;
        List.removeHead();
    }
}
