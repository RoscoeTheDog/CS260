//
// Created by admin on 4/28/2021.
//

#ifndef LAB_5___BINARY_TREES___PARSE_TREES_NODE_HPP
#define LAB_5___BINARY_TREES___PARSE_TREES_NODE_HPP

#include <optional>

class Node {
public:
	Node *head = nullptr;
	Node *right = nullptr;
	Node *left = nullptr;
	std::optional<char> value;

	explicit Node(char c) {

		value = c;
	}
};


#endif //LAB_5___BINARY_TREES___PARSE_TREES_NODE_HPP
