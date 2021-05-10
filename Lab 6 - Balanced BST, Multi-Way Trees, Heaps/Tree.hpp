//
// Created by admin on 5/6/2021.
//

#ifndef LAB_6___BALANCED_BST__MULTI_WAY_TREES__HEAPS_TREE_HPP
#define LAB_6___BALANCED_BST__MULTI_WAY_TREES__HEAPS_TREE_HPP


#include <string>
//#include <sstream>
//#include <optional>
#include <stdexcept>
#include "Node.hpp"

class Tree {

private:
	Node *root = nullptr;
	Node *tail = nullptr;  // tail is representative of an arbitrary cursor position. Sometimes considered the 'last' successful push.
	bool removeFound = false;
	std::string S = "";

public:

//	Tree();
//
//	~Tree();

	// add a new node containing value to the tree
	void insertValue(int val, Node *n = nullptr);

	// return true if there is a node containing value, false otherwise
	bool findValue(int val, Node *n = nullptr);

	//	if there is a node in the tree containing value, remove it and return
	//	true. If there is not such a node, return false. For this implementation, you should mark it as
	//	removed, not actually remove the node.
	bool deleteValue(int val);

	//	return a string containing a prefix listing of the tree’s contents. If a node was
	//  deleted, add a D to its value.
	std::string preOrder(Node *n = nullptr);

	// – return a string containing an infix listing of the tree’s contents. If a node was
	//deleted, add a D to its value.
	std::string inOrder(Node *n = nullptr);

	// return a string containing a postfix listing of the tree’s contents. If a node was
	//  deleted, add a D to its value.
	std::string postOrder(Node *n = nullptr);

	// search for a node containing value and return value if such a node is
	//  found. If no such node is found, return the next larger value in the tree. If there are no larger
	//  values in the tree, return -1.
	std::optional<int> findLarger(int val, Node *n = nullptr);

	// similar to findLarger but deletes the node before returning
	std::optional<int> deleteLarger(int val);

	// Implement a delete node method that uses the inorder successor as described in the Moodle
	// documentation.
	bool deleteNodeInOrder();

};


#endif //LAB_6___BALANCED_BST__MULTI_WAY_TREES__HEAPS_TREE_HPP
