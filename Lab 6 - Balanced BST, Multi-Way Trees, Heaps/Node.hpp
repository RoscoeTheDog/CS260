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
	std::optional<int> value;
	bool DELETED = false;

	Node(){};

	explicit Node(int value) {

		this->value = value;
		DELETED = false;
	}
};

#endif //LAB_6___BALANCED_BST__MULTI_WAY_TREES__HEAPS_NODE_HPP
