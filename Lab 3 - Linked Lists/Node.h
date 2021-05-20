//
// Created by admin on 4/14/2021.
//

#ifndef LAB_3___LINKED_LISTS_NODE_H
#define LAB_3___LINKED_LISTS_NODE_H

#endif //LAB_3___LINKED_LISTS_NODE_H
#include <optional>

class Node{
public:
    Node * prev;
    Node * next;
    std::optional<char> value;

    Node() { prev = nullptr; next = nullptr; }

    ~Node()= default;

};