//
// Created by admin on 4/28/2021.
//

#include "ParseTree.hpp"

ParseTree::ParseTree(const std::string &str) {

	xInput << str;

	// This is just a safety net: checks for infix expressions
	for (unsigned i = 0; i < str.length(); ++i) {
		if (str[i] == PARENTH_L || str[i] == PARENTH_R) {
			throw std::invalid_argument("constructor expects post-fix expression");
		}
	}

	// Check if string pass was empty. If it is, do not do anything.
	if (str != "") {
		// Flag it's type. It is presumed a post-fix expression when passed to the
		// constructor.
		exprType = POSTFIX;
		// build a tree passing in the copied string. This way we can preserve the
		// original string in the input buffer.
		parsePostFix(str);
	}
}

ParseTree::~ParseTree() {
	// helper function. recursively destroys nodes.
	vDestroyTree(xRoot);
}

void ParseTree::vDestroyTree(Node *n) {

	// traverse left
	if (n->left) {
		return vDestroyTree(n->left);
	}

	// traverse right
	if (n->right) {
		return vDestroyTree(n->right);
	}

	// if root set null
	if (n == xRoot) {
		xRoot = nullptr;
	}
	else {
		if (n->head->left == n) {
			n->head->left = nullptr;
		}
		if (n->head->right == n) {
			n->head->right = nullptr;
		}
	}

	// If we are at a leaf, delete it.
	delete n;

	// If root still exists, continue traversing
	if (xRoot) {
		return vDestroyTree(xRoot);
	}
	// otherwise, everything is deleted
}

bool ParseTree::vConstructTree() {

	// validate input
	if (xInput.str() == "") {
		throw std::logic_error(
				"input expression does not exist or has been erased");
	}

	// pre/post expressions are built as the same type of tree
	if (exprType == PREFIX) {
		parsePostFix(this->xInput.str());
	}
	// pre/post expressions are built as the same type of tree
	if (exprType == POSTFIX) {
		parsePostFix(this->xInput.str());
	}
	// infix is the only one that requires a unique parser.
	if (exprType == INFIX) {
		parseInOrder(this->xInput.str());
	}

	return true;
}

void ParseTree::vClearOutStream() {

	xOutput.str("");
}

void ParseTree::vClearInStream() {

	xInput.str("");
}

bool ParseTree::xIsOperator(char c) {

	if (c == PLUS) {
		return true;
	}
	if (c == MINUS) {
		return true;
	}
	if (c == MULT) {
		return true;
	}
	if (c == DIVIDE) {
		return true;
	}
	if (c == EXPO) {
		return true;
	}
	if (c == PARENTH_L) {
		return true;
	}
	if (c == PARENTH_R) {
		return true;
	}

	return false;
}

void ParseTree::vBuildStackPreorder(Node *n) {
	// If root still has its value, we can deduce that the function is being
	// called for the first time. If the user did not pass in the root from a
	// higher level, then we can set it for them.
	if (xRoot->value) {
		n = xRoot;
	}

	if (n) {

		if (n->value) {
			xStr.push_back(n->value);
			n->value = std::nullopt; // std::optional lets us set a typedef to id
			// whether the node has been visited.
		}

		if (n->left) {
			vBuildStackPreorder(n->left);
			return;
		}

		if (n->right) {
			vBuildStackPreorder(n->right);
			return;
		}

		// Set parent links to nullptr, depending on child's position.
		// There is a special case where the current node could be root to watch
		// for.
		if (n == xRoot) {
			xRoot = nullptr;
		}
		else {
			if (n == n->head->left) { // This would mem fault if we were at root.
				n->head->left = nullptr;
			}

			if (n == n->head->right) {
				n->head->right = nullptr;
			}
		}

		delete n;
		if (xRoot) {
			vBuildStackPreorder(xRoot);
		}
	}
	// exit
}

void ParseTree::vBuildStackPostorder(Node *n) {

	/*
	 *  Recursively go through and add values to the stack from the tree.
	 *  Then, pop off the stack to construct the post order.
	 *  Finally-- use the xInput str to reconstruct the tree we deleted during
	 * traversal.
	 */
	if (n) {
		xStr.push_back(n->value);

		if (n->left) {
			vBuildStackPostorder(n->left);
		}

		if (n->right) {
			vBuildStackPostorder(n->right);
		}

		if (n == n->head->left) {
			n->head->left = nullptr;
		}
		if (n == n->head->right) {
			n->head->right = nullptr;
		}

		if (n == xRoot) {
			xRoot = nullptr;
		}

		delete n;
	}
}

void ParseTree::vBuildStackInorder(Node *n) {

	std::string str = xInput.str();

	// Iterate through all characters.
	for (unsigned i = 0; i < str.length(); ++i) {

		// if space, continue.
		if (str[i] == SPACE) {
			continue;
		}

		// "if operand.. add to output string
		if (!xIsOperator(str[i])) {
			xOutput << str[i];
			continue;
		}

		// "if L paren.."
		if (str[i] == PARENTH_L) {
			// "push on the stack"
			xStr.push_back(str[i]);
			continue;
		}

		// "if R paren.."
		if (str[i] == PARENTH_R) {

			// "pop top item (continue until get L paren)"
			while (!xStr.empty()) {

				char xChar = *xStr.back(); // Note: back() returns but does not pop!

				// "if L paren, push back on stack, stop popping"
				if (xChar != PARENTH_L) {
					xOutput << xChar;
					xStr.pop_back(); // removes the actual item
					continue;
				}
				else {
					// else discard and end popping
					xStr.pop_back();
					break;
				}
			}
			continue;
		}

		// "if operator..."
		if (xIsOperator(str[i])) {

			while (!xStr.empty()) {

				char xChar = *xStr.back(); // Note: back() returns but does not pop!

				// "if L paren, push back on stack, stop popping"
				if (xChar == PARENTH_L) {
					break;
				}

				// "if not operator with higher precedence, push back on stack,
				//  stop popping"
				if (xOperatorPriority(xChar) < xOperatorPriority(str[i])) {
					break;
				}
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
}

std::string ParseTree::inOrder() {
	// We don't know that a in/out/pre string has been entered prior.
	// Best to destroy and recreate the tree based on the new input.
	vDestroyTree(xRoot);

	// Rebuild the tree after ensuring there is no existing data
	vConstructTree();

	// Build the stack for an inOrder expression
	vBuildStackInorder(xRoot);

	// Ensure the output stream contains no data
	vClearOutStream();

	// Pop off the stack and build the tree. (LIFO)
	while (!xStr.empty()) {
		xOutput << *xStr.back();
		xStr.pop_back();
	}

	// // // Rebuild tree and output string.
	// parseInOrder(xInput.str());

	// xOutput buffer will contain the parsed expression
	return xOutput.str();
}

std::string ParseTree::postOrder(Node *n) {

	// Ensure the stack is empty.
	if (!xStr.empty()) {
		xStr.clear();
	}

	// Build the stack for a post order expression
	vBuildStackPostorder();

	// Reconstruct the tree after traversing and building the stack.
	vConstructTree();

	// Ensure the output stream is cleared before parsing.
	vClearOutStream();

	// Parse the stack to build the output stream. LIFO for post-order.
	while (!xStr.empty()) {
		xOutput << *xStr.back(); // Note: xStr holds std::optional container. It
		// must be de-referenced for the value.
		xStr.pop_back();
	}

	return xOutput.str();
}

std::string ParseTree::preOrder() {

	// Ensure the string stack is empty.
	if (!xStr.empty()) {
		xStr.clear();
	}

	// Use recursive helper to build the stack holding values in preOrder
	vBuildStackPreorder(xRoot);

	// Reconstruct the tree from input string (this->xInput).
	vConstructTree();

	// Ensure the output buffer is empty before parsing stack.
	vClearOutStream();

	// Pop off and create the output string (this->xOutput). FIFO for pre-order
	// expression.
	while (!xStr.empty()) {
		xOutput << *xStr.front(); // Note: xStr holds std::optional container. It
		// must be de-referenced for the value.
		xStr.pop_front();
	}

	return xOutput.str();
}

void ParseTree::parseInOrder(std::string str) {

	// validate args
	if (str == "") {
		throw std::invalid_argument("Cannot parse empty string");
	}

	// If nothing was past to the constructor prior, save the passed in argument
	if (xInput.str() == "") {
		xInput << str;
	}

	// Flag the expression type. This is performed everytime a new input string is
	// parsed.
	exprType = INFIX;

	// Ensure the output buffer is empty for use.
	vClearOutStream();

	// Note: build-stack in order also builds the tree.
	vBuildStackInorder();

	// "At end of expression, pop and add to buffer"
	while (!xStr.empty()) {
		xOutput << *xStr.back();
		xStr.pop_back();
	}

	// Call string parser method to build tree as infix to postfix
	parsePostFix(xOutput.str());
}

void ParseTree::parsePostFix(std::string str) {

	if (str == "") {
		throw std::invalid_argument("cannot parse an empty string");
	}

	// "Look at each character in the string in order"
	for (unsigned i = 0; i < str.length(); ++i) {

		// "Skip if space"
		if (str[i] == SPACE) {
			continue;
		}

		// "If an operand"
		if (!xIsOperator(str[i])) {
			// "create a new node for the operand"
			Node *N = new Node(str[i]);
			// "push it on the stack"
			xStack.push_back(N);
			continue;
		}

		// "If an operator"
		if (xIsOperator(str[i])) {

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
				N->left->head = N; // Link to parent
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
}
