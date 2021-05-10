//
// Created by admin on 5/6/2021.
//

#ifndef LAB_6___BALANCED_BST__MULTI_WAY_TREES__HEAPS_NODE_HPP
#define LAB_6___BALANCED_BST__MULTI_WAY_TREES__HEAPS_NODE_HPP

#include <optional>

class Node {
public:
	Node *head = nullptr;
	Node *left = nullptr;
	Node *right = nullptr;
	int value;
	bool DELETED = false;

	explicit Node(int value) {

		this->value = value;
	}
};

#endif //LAB_6___BALANCED_BST__MULTI_WAY_TREES__HEAPS_NODE_HPP
