//
// Created by admin on 4/28/2021.
//

#include "ParseTree.hpp"


ParseTree::ParseTree(std::string str) {
    this->xInput << str;
}

bool ParseTree::isop(char c) {

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

std::string ParseTree::inOrder() {

    std::string S = xInput.str();

    for (unsigned i = 0; i < S.length(); ++i) {
        // if space, continue.
        if (std::isspace(S[i]))
            continue;

        // "if operand.. add to output string
        if (std::isalpha(S[i]) or std::isdigit(S[i]))
            xOutput << S[i];

        // "if L paren.."
        if (S[i] == PARENTH_L)
            // "push on the stack"
            xStr.push_back(S[i]);

        // "if R paren.."
        if (S[i] == PARENTH_R) {

            // "pop top item (continue until get L paren)"
            while (not xStr.empty()) {

                char xChar = xStr.back(); // Note: back() returns but does not pop!

                // "if L paren, push back on stack, stop popping"
                if (xChar not_eq PARENTH_L) {
                    xOutput << xChar;
                    xStr.pop_back(); // removes the actual item
                }
                else {
                    // else discard and end popping
                    break;
                }
            }

        }

        // "if operator..."
        if (isop(S[i])) {

            while (not xStr.empty()) {

                char xChar = xStr.back(); // Note: back() returns but does not pop!

                // "if L paren, push back on stack, stop popping"
                if (xChar == PARENTH_L)
                    break;

                // "if not operator with higher precedence, push back on stack,
                //  stop popping"
                if (oppriority(xChar) < oppriority(S[i]))
                    break;
                else
                    xOutput << xChar;
            }
            // "push operator"
            xStr.push_back(S[i]);
        }

    }

    // "At end of expression, pop and add to buffer"
    while (not xStr.empty()) {
        xOutput << xStr.back();
        xStr.pop_back();
    }

    return xOutput.str();

}



std::string ParseTree::postOrder() {

    std::string S = xInput.str();

    // "Look at each character in the string in order"
    for (unsigned i = 0; i < S.length(); ++i) {

        if (S[i] == SPACE)
            continue;
        // "If an operand"
        if (!isop(S[i])){
            // "create a new node for the operand"
            Node * N = new Node;
            N->c = S[i];
            // "push it on the stack"
            xStack.push_back(N);
            continue;
        }
        // "If an operator"
        if (isop(S[i])) {
            // "create a new node for the operator"
            Node * N = new Node;
            // "pop the top of the stack and attach it on the right of the new node"
            N->right = xStack.back();
            xStack.pop_back();
            // "pop the top of the stack and attach it on the left of the new node
            N->left = xStack.back();
            xStack.pop_back();
            // "push new node and its subtree on the stack"
            xStack.push_back(N);
            continue;
        }

    }

    // "If end of expression"
    // "Pop the top of the stack and save the node as root of the tree"
    xRoot = xStack.back();
    xStack.pop_back();

}

std::string ParseTree::preOrder() {

}

void ParseTree::vMakePostfix() {

    std::string S = xInput.str();

    // "Look at each character in the string in order"
    for (unsigned i = 0; i < S.length(); ++i) {

        if (S[i] == SPACE)
            continue;
        // "If an operand"
        if (!isop(S[i])){
            // "create a new node for the operand"
            Node * N = new Node;
            N->c = S[i];
            // "push it on the stack"
            xStack.push_back(N);
            continue;
        }
        // "If an operator"
        if (isop(S[i])) {
            // "create a new node for the operator"
            Node * N = new Node;
            // "pop the top of the stack and attach it on the right of the new node"
            N->right = xStack.back();
            xStack.pop_back();
            // "pop the top of the stack and attach it on the left of the new node
            N->left = xStack.back();
            xStack.pop_back();
            // "push new node and its subtree on the stack"
            xStack.push_back(N);
            continue;
        }

    }

    // "If end of expression"
    // "Pop the top of the stack and save the node as root of the tree"
    xRoot = xStack.back();
    xStack.pop_back();
}

void ParseTree::vMakeInfix() {

    std::string S = xInput.str();

    for (unsigned i = 0; i < S.length(); ++i) {
        // if space, continue.
        if (std::isspace(S[i]))
            continue;

        // "if operand.. add to output string
        if (std::isalpha(S[i]) or std::isdigit(S[i]))
            xOutput << S[i];

        // "if L paren.."
        if (S[i] == PARENTH_L)
            // "push on the stack"
            xStr.push_back(S[i]);

        // "if R paren.."
        if (S[i] == PARENTH_R) {

            // "pop top item (continue until get L paren)"
            while (not xStr.empty()) {

                char xChar = xStr.back(); // Note: back() returns but does not pop!

                // "if L paren, push back on stack, stop popping"
                if (xChar not_eq PARENTH_L) {
                    xOutput << xChar;
                    xStr.pop_back(); // removes the actual item
                }
                else {
                    // else discard and end popping
                    break;
                }
            }

        }

        // "if operator..."
        if (isop(S[i])) {

            while (not xStr.empty()) {

                char xChar = xStr.back(); // Note: back() returns but does not pop!

                // "if L paren, push back on stack, stop popping"
                if (xChar == PARENTH_L)
                    break;

                // "if not operator with higher precedence, push back on stack,
                //  stop popping"
                if (oppriority(xChar) < oppriority(S[i]))
                    break;
                else
                    xOutput << xChar;
            }
            // "push operator"
            xStr.push_back(S[i]);
        }

    }

    // "At end of expression, pop and add to buffer"
    while (not xStr.empty()) {
        xOutput << xStr.back();
        xStr.pop_back();
    }

    return xOutput.str();
}

void ParseTree::vMakePrefix() {
    // tree is the same for pre/post
    vMakePostFix();
}
