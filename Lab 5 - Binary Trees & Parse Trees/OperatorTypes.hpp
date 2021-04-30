//
// Created by admin on 4/28/2021.
//

#ifndef LAB_5___BINARY_TREES___PARSE_TREES_OPERATORTYPES_HPP
#define LAB_5___BINARY_TREES___PARSE_TREES_OPERATORTYPES_HPP

#define PLUS '+'
#define MINUS '-'
#define MULT '*'
#define DIVIDE '/'
#define EXPO '^'
#define PARENTH_L '('
#define PARENTH_R ')'
#define SPACE ' '

typedef enum {
    ePLUS,
    eMINUS,
    eMULT,
    eDIV,
    eEXPO,
    ePARENTH_L,
    ePARENTH_R,
    eSPACE,
} operator_t;

operator_t xOperatorPriority(char c);

#endif //LAB_5___BINARY_TREES___PARSE_TREES_OPERATORTYPES_HPP
