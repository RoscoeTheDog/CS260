//
// Created by admin on 4/28/2021.
//

#ifndef LAB_5___BINARY_TREES___PARSE_TREES_PARSETREE_HPP
#define LAB_5___BINARY_TREES___PARSE_TREES_PARSETREE_HPP
#include <string>
#include "Node.hpp"
#include "OperatorTypes.hpp"
#include <stack>
#include <sstream>
#include <locale>

class ParseTree {
private:
    Node * xRoot = nullptr;
    std::deque<Node*> xStack;
    std::deque<char> xStr;
    std::stringstream xInput;
    std::stringstream xOutput;

    // checks macro to determine type attribute. better than using local.h due to limited support of encoding types.
    bool isop(char c);

    /*  constructor-type helper.
     *  Generates a corresponding tree in xStack to subsequently be parsed into an ouptut string.
     */
    void vMakePrefix();

    /*  constructor-type helper.
     *  Generates a corresponding tree in xStack to subsequently be parsed into an ouptut string.
     */
    void vMakeInfix();

    /*  constructor-type helper.
     *  Generates a corresponding tree in xStack to subsequently be parsed into an ouptut string.
     */
    void vMakePostfix();

public:
    explicit ParseTree(std::string str = "");

    ~ParseTree();

    std::string preOrder();

    std::string inOrder();

    std::string postOrder();

    void parseInOrder();

};


#endif //LAB_5___BINARY_TREES___PARSE_TREES_PARSETREE_HPP
