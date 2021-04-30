//
// Created by admin on 4/28/2021.
//

#include "ParseTree.hpp"


ParseTree::ParseTree(std::string str) {
    xInput << str;

    if (str != "") {
        // build a tree passing in the copied string. This way we can preserve the original string in the input buffer.
        parsePostFix(str);
    }
}

bool ParseTree::isoperator(char c) {

    if (c == PLUS)
        return true;
    if (c == MINUS)
        return true;
    if (c == MULT)
        return true;
    if (c == DIVIDE)
        return true;
    if (c == EXPO)
        return true;
    if (c == PARENTH_L)
        return true;
    if (c == PARENTH_R)
        return true;

    return false;
}

void ParseTree::parsePostFix(std::string str) {

    if (str == "") {
        throw std::invalid_argument("cannot parse an empty string");
    }

    // "Look at each character in the string in order"
    for (unsigned i = 0; i < str.length(); ++i) {

        // "Skip if space"
        if (str[i] == SPACE)
            continue;

        // "If an operand"
        if (!isoperator(str[i])) {
            // "create a new node for the operand"
            Node *N = new Node(str[i]);
            // "push it on the stack"
            xStack.push_back(N);
            continue;
        }

        // "If an operator"
        if (isoperator(str[i])) {

            // "create a new node for the operator"
            Node *N = new Node(str[i]);

            // "pop the top of the stack and attach it on the right of the new node"
            if (!xStack.empty()) {
                N->right = xStack.back();
                N->right->head = N; // Link to parent
                xStack.pop_back();
            }

            // "pop the top of the stack and attach it on the left of the new node
            if (!xStack.empty()) {
                N->left = xStack.back();
                N->left->head = N;  // Link to parent
                xStack.pop_back();
            }

            // "push new node and its subtree on the stack"
            xStack.push_back(N);
            continue;
        }

    }

    // "If end of expression"
    // "Pop the top of the stack and save the node as root of the tree"
    xRoot = xStack.back();
    xStack.pop_back();

//    // extra: iterate through the stack (back->front) to construct the output string
//    xOutput.clear(); // ensure the buffer is emptied first.
//    for (auto i = xStack.back(); i>xStack.front(); --i) {
//        xOutput << i->value;
//    }
}

std::string ParseTree::inOrder() {

    // Convert infix expression to build postfix tree.
    this->parseInOrder(xInput.str());
    // xOutput buffer will contain the parsed expression in order.
    return xOutput.str();

//    std::string S = xInput.str();
//
//    for (unsigned i = 0; i < S.length(); ++i) {
//        // if space, continue.
//        if (std::isspace(S[i]))
//            continue;
//
//        // "if operand.. add to output string
//        if (std::isalpha(S[i]) or std::isdigit(S[i]))
//            xOutput << S[i];
//
//        // "if L paren.."
//        if (S[i] == PARENTH_L)
//            // "push on the stack"
//            xStr.push_back(S[i]);
//
//        // "if R paren.."
//        if (S[i] == PARENTH_R) {
//
//            // "pop top item (continue until get L paren)"
//            while (not xStr.empty()) {
//
//                char xChar = xStr.back(); // Note: back() returns but does not pop!
//
//                // "if L paren, push back on stack, stop popping"
//                if (xChar not_eq PARENTH_L) {
//                    xOutput << xChar;
//                    xStr.pop_back(); // removes the actual item
//                }
//                else {
//                    // else discard and end popping
//                    break;
//                }
//            }
//
//        }
//
//        // "if operator..."
//        if (isoperator(S[i])) {
//
//            while (not xStr.empty()) {
//
//                char xChar = xStr.back(); // Note: back() returns but does not pop!
//
//                // "if L paren, push back on stack, stop popping"
//                if (xChar == PARENTH_L)
//                    break;
//
//                // "if not operator with higher precedence, push back on stack,
//                //  stop popping"
//                if (oppriority(xChar) < oppriority(S[i]))
//                    break;
//                else
//                    xOutput << xChar;
//            }
//            // "push operator"
//            xStr.push_back(S[i]);
//        }
//
//    }
//
//    // "At end of expression, pop and add to buffer"
//    while (not xStr.empty()) {
//        xOutput << xStr.back();
//        xStr.pop_back();
//    }
//
//    return xOutput.str();

}


std::string ParseTree::postOrder() {

    std::stringstream _s;

    // in case of infix expression, filter parenthesis
    for (unsigned i = 0; i < xOutput.str().length(); ++i) {

        if (xOutput.str()[i] != PARENTH_L &&
            xOutput.str()[i] != PARENTH_R) {
            _s << xOutput.str()[i];
        }
    }

    /*
     *  return the filtered string.
     *  do not overwrite the member
     *  if it was initially parsed as inOrder, we should keep it that way
     */
    return _s.str();
}

std::string ParseTree::preOrder() {
    return xOutput.str();
}

void ParseTree::parseInOrder(std::string str) {

    if (str == "") {
        throw std::invalid_argument("Cannot parse empty string");
    }

    // Ensure the output buffer is empty for use.
    xOutput.clear();

    // Iterate through all characters.
    for (unsigned i = 0; i < str.length(); ++i) {

        // if space, continue.
        if (str[i] == SPACE)
            continue;

        // "if operand.. add to output string
        if (!isoperator(str[i])) {
            xOutput << str[i];
            continue;
        }

        // "if L paren.."
        if (str[i] == PARENTH_L){
            // "push on the stack"
            xStr.push_back(str[i]);
            continue;
        }

        // "if R paren.."
        if (str[i] == PARENTH_R) {

            // "pop top item (continue until get L paren)"
            while (!xStr.empty()) {

                char xChar = xStr.back(); // Note: back() returns but does not pop!

                // "if L paren, push back on stack, stop popping"
                if (xChar != PARENTH_L) {
                    xOutput << xChar;
                    xStr.pop_back(); // removes the actual item
                    continue;
                }
                else {
                    // else discard and end popping
                    break;
                }
            }
            continue;
        }

        // "if operator..."
        if (isoperator(str[i])) {

            while (!xStr.empty()) {

                char xChar = xStr.back(); // Note: back() returns but does not pop!

                // "if L paren, push back on stack, stop popping"
                if (xChar == PARENTH_L) {
                    break;
                }

                // "if not operator with higher precedence, push back on stack,
                //  stop popping"
                if (oppriority(xChar) < oppriority(str[i]))
                    break;
                else {
                    xOutput << xChar;
                    xStr.pop_back();
                    continue;
                }

            }
            // "push operator"
            xStr.push_back(str[i]);
        }

    }

    // "At end of expression, pop and add to buffer"
    while (!xStr.empty()) {
        xOutput << xStr.back();
        xStr.pop_back();
    }

    // Invoke parser method to build postfix tree.
    parsePostFix(xOutput.str());

}

ParseTree::~ParseTree() {
    delete xRoot;
}

void ParseTree::destroyTree(Node *n) {

    // traverse left
    if (n->left)
        return destroyTree(n->left);

    // traverse right
    if (n->right)
        return destroyTree(n->right);

    if (!n->left && !n->right) {
        // reset root to null
        if (n == xRoot)
            xRoot = nullptr;
        // If we are at a leaf, delete it.
        delete n;
    }

    if (xRoot)
        return destroyTree(xRoot);
}
