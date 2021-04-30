//
// Created by admin on 4/28/2021.
//

#ifndef LAB_5___BINARY_TREES___PARSE_TREES_NODE_HPP
#define LAB_5___BINARY_TREES___PARSE_TREES_NODE_HPP

class Node {
public:
    Node * head = nullptr;
    Node * right = nullptr;
    Node * left = nullptr;
    char value;

    Node(char c = 0) {value = c;}
};


#endif //LAB_5___BINARY_TREES___PARSE_TREES_NODE_HPP
