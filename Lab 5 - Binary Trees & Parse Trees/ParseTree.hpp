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
#include <stdexcept>

class ParseTree {
private:
    typedef enum {
        PREFIX = 1,
        INFIX,
        POSTFIX,

    } expression_t;

    Node *xRoot = nullptr;
    std::deque<Node *> xStack;
    std::deque<std::optional<char>> xStr;
    expression_t exprType;
    std::stringstream xInput;

    std::stringstream xOutput;

    /*
     *  checks macro to determine type attribute.
        better than using local.h due to limited support of encoded char types
        (I considered both ways).
    */
    static bool xIsOperator(char c);

    /*
     *  Helper destructor method.
     *  Traverses through nodes and deletes them recursively
    */
    void vDestroyTree(Node *n = nullptr);

    // Helper that erases the contents of the output stream.
    // It does NOT clear flags like in the normal STD library.
    void vClearOutStream();

    // Helper that erases the contents of the input stream.
    // It does NOT clear flags like in the normal STD library.
    void vClearInStream();

    void vConstructTree();

public:
    explicit ParseTree(const std::string &str = "");

    ~ParseTree();

    // Recursively go through each Node starting from root to build post-fix string.
    // Traverse through the nodes like a normal binary parse tree head->left etc.
    std::string preOrder(Node * n = nullptr);

    std::string inOrder();

    std::string postOrder(Node * n = nullptr);

    void parseInOrder(std::string str = "");

    void parsePostFix(std::string str = "");
};


#endif //LAB_5___BINARY_TREES___PARSE_TREES_PARSETREE_HPP
