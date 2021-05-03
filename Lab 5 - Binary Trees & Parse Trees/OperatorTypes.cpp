//
// Created by admin on 4/28/2021.
//

#include "OperatorTypes.hpp"

operator_t xOperatorPriority(char c) {

	operator_t _op;

	if (c == '+') {
		_op = ePLUS;
	}
	if (c == '-') {
		_op = eMINUS;
	}
	if (c == '*') {
		_op = eMULT;
	}
	if (c == '/') {
		_op = eDIV;
	}
	if (c == '^') {
		_op = eEXPO;
	}
	if (c == '(') {
		_op = ePARENTH_L;
	}
	if (c == ')') {
		_op = ePARENTH_R;
	}
	if (c == ' ') {
		_op = eSPACE;
	}

	return _op;
}
