//
// Created by admin on 5/13/2021.
//

#include "Heap.hpp"


Heap::Heap(int size, HeapBase_t baseType) {

	root = baseType;
	length = baseType;  // starting length depends on the baseType of the heap implemented
	this->size = size;
	open = LEAF_LEFT;
	// allocate array.
	heap = new int[length];
}

Heap::~Heap() {

	delete[] heap;
}


void Heap::addItem(int value) {

	if (length == root) {
		heap[root] = value;
		length++;
		return;
	}

	// insert item into the array. Then invoke helper that sifts/trickles down.
	if (open == LEAF_LEFT) {

		if (root == BASE_0) {
			// insert value
			heap[length++] = value;
			// bubble/sift. will exit if !valid
			vSiftUp(length);

		}

		if (root == BASE_1) {
			heap[2 * length + 1] = value;
			length++;
			vSiftUp(length);
		}

		// toggle leaf available position
		open = LEAF_RIGHT;
		return;
	}

	if (open == LEAF_RIGHT) {

		if (root == BASE_0) {
			heap[2 * length + 1] = value;
			length++;
			vSiftUp(length);
		}

		if (root == BASE_1) {
			heap[2 * length + 2] = value;
			length++;
			vSiftUp(length);
		}

		// toggle leaf available position
		open = LEAF_LEFT;
		return;
	}

}

int Heap::getItem() {

	int _v = heap[root];

	if (root == BASE_0) {

		if (length > 2) {

			if (heap[2] < heap[3]) {
				heap[1] = heap[2];
				vReplaceDown(root);
			}

			if (heap[2] > heap[3]) {
				heap[1] = heap[3];
				vReplaceDown(root);
			}

		}
		else if (length > 1) {

			if (heap[2] < heap[1]) {
				heap[1] = heap[2];
				vReplaceDown(root);
			}
		}

	}

	return _v;
}

void Heap::vSiftUp(int position) {

	// if we sifted to the root, exit.
	if (position == root) {
		return;
	}

	if (root == BASE_0) {
		// exit if parent is less than iterated position.
		if (heap[position] >= heap[position / 2]) {
			return;
		}

		if (heap[position] < heap[position / 2]) {
			// Swap the parent and the leaf.
			std::swap(heap[position], heap[position / 2]);
			// traverse to the parent
			return vSiftUp(heap[position / 2]);
		}
	}

	if (root == BASE_1) {
		// exit if parent is less than iterated position.
		if (heap[position + 1] >= heap[(position - 1) / 2]) {
			return;
		}

		if (heap[position + 1] < heap[(position - 1) / 2]) {
			// Swap the parent and the leaf.
			std::swap(heap[position + 1], heap[(position - 1) / 2]);
			// traverse to the parent
			return vSiftUp(heap[(position - 1) / 2]);
		}
	}


}

void Heap::vSiftDown(int position) {

	if (root == BASE_0) {

		// exit if parent is less than child.
		if (heap[position] < heap[2 * position] && heap[position < heap[2 * position + 1]]) {
			return;
		}

		// compare left
		if (heap[position] > heap[2 * position]) {
			std::swap(heap[position], heap[2 * position]);
			return vSiftDown(heap[position]);
		}

		// compare right
		if (heap[position] > heap[2 * position + 1]) {
			std::swap(heap[position], heap[2 * position + 1]);
		}
	}

	if (root == BASE_1) {

		// exit if parent is less than child.
		if (heap[position] < heap[2 * position + 1] && heap[position < heap[2 * position + 2]]) {
			return;
		}

		// compare left
		if (heap[position] > heap[2 * position + 1]) {
			std::swap(heap[position], heap[2 * position + 1]);
			return vSiftDown(heap[position]);
		}

		// compare right
		if (heap[position] > heap[2 * position + 2]) {
			std::swap(heap[position], heap[2 * position + 2]);
		}
	}
}

void Heap::vReplaceDown(int position) {

	if (root == BASE_0) {

		// Check for duplicates on the left
		if (heap[position] == heap[2 * position]) {
			return vReplaceDown(2 * position);
		}

		// Check for duplicates on the left
		if (heap[position] == heap[2 * position + 1]) {
			return vReplaceDown(2 * position + 1);
		}

		// check if left subtree/leaf is less than right
		if (heap[2 * position] < heap[2 * position + 1]) {

			// if we hit the bottom of the tree, rearrange the leafs.
			if (2 * position > length) {

				// Overwrite everything from duplicate onward by the +1 the right relative.
				for (int i = position; i < length; ++i) {
					heap[i] = heap[i + 1];
				}

				// SiftDown/Heapify the array after.
				vSiftDown(root);

				// Toggle available leaf positions so we overwrite.
				if (open == LEAF_LEFT) {
					open = LEAF_RIGHT;
				}
				if (open == LEAF_RIGHT) {
					open = LEAF_LEFT;
				}

				// decrement the length-- should overwrite the last remaining node.
				length--;
			}
			else {
				// overwrite the current position (parent).
				heap[position] = heap[2 * position];
				// go to left node.
				return vSiftDown(2 * position);
			}

		}

		// check if left subtree/leaf is less than right
		if (heap[2 * position] > heap[2 * position + 1]) {

			// if we hit the bottom of the tree, rearrange the leafs.
			if (2 * position + 1 > length) {

				// Overwrite everything from duplicate onward by the +1 the right relative.
				for (int i = position; i < length; ++i) {
					heap[i] = heap[i + 1];
				}

				// SiftDown/Heapify the array after.
				vSiftDown(root);

				// Toggle available leaf positions so we overwrite.
				if (open == LEAF_LEFT) {
					open = LEAF_RIGHT;
				}
				if (open == LEAF_RIGHT) {
					open = LEAF_LEFT;
				}

				// decrement the length-- should overwrite the last remaining node.
				length--;
			}
			else {
				// overwrite the current position (parent).
				heap[position] = heap[2 * position + 1];
				// go to right node.
				return vSiftDown(2 * position + 1);
			}

		}
	}
}

