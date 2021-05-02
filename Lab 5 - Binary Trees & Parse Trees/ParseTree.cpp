//
// Created by admin on 4/28/2021.
//

#include "ParseTree.hpp"

ParseTree::ParseTree(const std::string &str) {
	// pass in the string to the input buffer
	xInput << str;

	// This is just a safety net: checks for infix expressions
	for (unsigned i = 0; i < str.length(); ++i) {
		if (str[i] == PARENTH_L || str[i] == PARENTH_R) {
			throw std::invalid_argument("constructor expects post-fix expression");
		}
	}

	// Check if string pass was empty. If it is, do not do anything.
	if (str != "") {
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

	// Extra guard in case somehow xRoot is null.
	if (xRoot) {

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

		// return to root
		return vDestroyTree(xRoot);
	}


//
//	// traverse left
//	if (n->left) {
//		return vDestroyTree(n->left);
//	}
//
//	// traverse right
//	if (n->right) {
//		return vDestroyTree(n->right);
//	}
//
//	// if root set null
//	if (n == xRoot) {
//		xRoot = nullptr;
//	}
//	else {
//		if (n->head->left == n) {
//			n->head->left = nullptr;
//		}
//		if (n->head->right == n) {
//			n->head->right = nullptr;
//		}
//	}
//
//	// If we are at a leaf, delete it.
//	delete n;
//
//	// If root still exists, continue traversing
//	if (xRoot) {
//		return vDestroyTree(xRoot);
//	}
//	// otherwise, everything is deleted
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
			return vBuildStackPreorder(n->left);
		}

		if (n->right) {
			return vBuildStackPreorder(n->right);
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
			return vBuildStackPreorder(xRoot);
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
	if (xRoot) {

		// Traverse until we hit a leaf
		if (n->left) {
			return vBuildStackPostorder(n->left);
		}
		if (n->right) {
			return vBuildStackPostorder(n->right);
		}
		// Add value to the stack.
		xStr.push_back(n->value);

		// clean up references and delete node.
		if (n == xRoot) {
			xRoot = nullptr;
		}
		else {
			if (n == n->head->left) {
				n->head->left = nullptr;
			}
			if (n == n->head->right) {
				n->head->right = nullptr;
			}
		}
		delete n;

		if (xRoot) {
			return vBuildStackPostorder(xRoot);
		}
	}
	//exit
}

void ParseTree::vBuildStackInorder(Node *n) {

	// Copying the variable may save time from calling deque methods each time. Not sure.
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


	if (exprType == INFIX) {
		return xInput.str();
	}
	else {
		throw std::logic_error("Cannot return expression from incompatible input type");
	}

//	// Provide a clean tree.
//	vDestroyTree(xRoot);
//
//	// Rebuild the tree after ensuring there is no existing data
//	vConstructTree();
//
//	/*
//	*   The inOrder algorithm is a bit different from the others in that it builds the tree and output string at the same time
//	*   Do not call vClearOutStream() or pop off the stack here!
//	*/
//	vBuildStackInorder(xRoot);
//
//	// xOutput buffer will contain the parsed expression
//	return xOutput.str();
}

std::string ParseTree::postOrder() {

	// Ensure the stack is empty.
	if (!xStr.empty()) {
		xStr.clear();
	}

	// Delete the tree, if previously existing.
	// This should not be necessary, but ensures we have a clean slate.
	vDestroyTree(xRoot);

	// Reconstruct the tree after traversing and building the stack.
	vConstructTree();

	// Ensure the output stream is cleared before parsing.
	vClearOutStream();

	//Build the stack for a post order expression
	vBuildStackPostorder(xRoot);

	// Parse the stack to build the output stream. FIFO for post-order.
	while (!xStr.empty()) {
		xOutput << *xStr.front(); // Note: xStr holds std::optional container. It must be de-referenced for the value.
		xStr.pop_front();
	}

	return xOutput.str();
}

std::string ParseTree::preOrder() {

	// Ensure the string stack is empty.
	if (!xStr.empty()) {
		xStr.clear();
	}

	vDestroyTree(xRoot);

	// Construct the tree from input string (this->xInput).
	vConstructTree();

	// Ensure the output buffer is empty before parsing stack. This cannot be done within the recursive function.
	vClearOutStream();

	// Recursively build the stack in preOrder notation
	vBuildStackPreorder(xRoot);

	// Pop off the stack and create the output string (this->xOutput). FIFO for pre-order.
	while (!xStr.empty()) {
		xOutput << *xStr.front(); // Note: std::optional must be de-referenced
		xStr.pop_front();
	}

	return xOutput.str();
}

void ParseTree::parseInOrder(std::string str) {

	// check validate args (since only the constructor accepts post-order specific only)
	if (str == "") {
		throw std::invalid_argument("Cannot parse empty string");
	}

	// If nothing was passed to the constructor prior, save nothing as input
	if (xInput.str() == "") {
		xInput << str;
	}
	else {  // clear and set if pre-existing
		vClearInStream();
		xInput << str;
	}

	// Ensure the output buffer is empty for use.
	vClearOutStream();

	// Build a stack from the input to an inOrder expression.
	// This will eventually convert the string into a post-order tree.
	vBuildStackInorder();

	// Pop and add all elements to output buffer.
	while (!xStr.empty()) {
		xOutput << *xStr.back();
		xStr.pop_back();
	}

	// Use the output buffer which includes parenthesis to build the tree as a post-fix expression.
	parsePostFix(xOutput.str());

	// Flag the expression type.
	// This is performed everytime a corresponding parser is called to track the input.
	exprType = INFIX;
}

void ParseTree::parsePostFix(std::string str) {

	if (str == "") {
		throw std::invalid_argument("cannot parse an empty string");
	}

	// Make sure the stack is empty before populating
	if (!xStack.empty()) {
		xStack.empty();
	}

	// Destroy the tree if it exists.
	if (xRoot) {
		vDestroyTree(xRoot);
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

	// Flag the expression type.
	// This is performed everytime a corresponding parser is called to track the input.
	exprType = POSTFIX;
}