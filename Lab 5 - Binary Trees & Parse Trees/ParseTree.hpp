//
// Created by admin on 4/28/2021.
//

#ifndef LAB_5___BINARY_TREES___PARSE_TREES_PARSETREE_HPP
#define LAB_5___BINARY_TREES___PARSE_TREES_PARSETREE_HPP

#include "Node.hpp"
#include "OperatorTypes.hpp"
#include <locale>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

class ParseTree {
private:
	typedef enum {
		PREFIX = 1,
		INFIX,
		POSTFIX,
	} expression_t;

	Node *xRoot = nullptr;
	std::stringstream xInput;
	std::stringstream xOutput;
	std::deque<Node *> xStack;
	std::deque<std::optional<char>> xStr;
	expression_t exprType;

	/*
		checks macro to determine type attribute.
		better than using local.h due to limited support of encoded char types
		(I considered both ways).
	*/
	static bool xIsOperator(char c);

	// Helper destructor method.
	// Traverses through nodes and deletes them recursively
	void vDestroyTree(Node *n = nullptr);

	// Helper that builds the tree using whatever is stored in xInput.
	// Useful for reconstructing the tree after it has been parsed into an
	// expression.
	bool vConstructTree();

	// Helper that erases the contents of the output stream.
	// It does NOT clear flags like in the normal STD library.
	void vClearOutStream();

	// Helper that erases the contents of the input stream.
	// It does NOT clear flags like in the normal STD library.
	void vClearInStream();

	// Builds the container stack in prefix notation. It can then be popped and
	// returned by preOrder();
	void vBuildStackPreorder(Node *n = nullptr);

	// Builds the container stack in postOrder notation. It can then be popped and
	// returned by postOrder();
	void vBuildStackPostorder(Node *n = nullptr);

	// Builds the container stack in inOrder notation. It can then be popped and
	// returned by inOrder();
	void vBuildStackInorder(Node *n = nullptr);

public:
	explicit ParseTree(const std::string &str = "");

	~ParseTree();

	// Returns the input string as a preOrder expression.
	std::string preOrder();

	// Returns the input string as a inOrder expression.
	std::string inOrder();

	// Returns the input string as a postOrder expression.
	std::string postOrder();

	void parseInOrder(std::string str = "");

	void parsePostFix(std::string str = "");
};

#endif // LAB_5___BINARY_TREES___PARSE_TREES_PARSETREE_HPP
