//
// Created by admin on 4/14/2021.
//

#ifndef LAB_3___LINKED_LISTS_NODE_H
#define LAB_3___LINKED_LISTS_NODE_H

#endif //LAB_3___LINKED_LISTS_NODE_H
#include <optional>

class Node{
public:
    Node * head;
    Node * next;
    std::optional<char32_t> value;

    Node() { head = nullptr; next = nullptr; }

    ~Node() { delete head; delete next; }

};