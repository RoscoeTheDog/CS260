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

	int left = xGetLeft(root);
	int right = xGetRight(root);

	if (length == root) {
		heap[root] = value;
		length++;
		return;
	}

	// insert item into the array. Then invoke helper that sifts/trickles down.
	if (open == LEAF_LEFT) {

		// insert value
		heap[left] = value;
		// increment num elements
		length++;
		// bubble/sift. will exit if !valid
		vSiftUp(length);

		// toggle available position.
		open = !open;
		// exit
		return;
	}

	if (open == LEAF_RIGHT) {
		// insert right position.
		heap[right] = value;
		// increment num elements
		length++;
		// bubble/sift up and heapify.
		vSiftUp(length);

		// toggle available position.
		open = !open;
		return;
	}

}

int Heap::getItem() {

	int _v = heap[root];

	// overwrite the root with the last inserted item && decriment.
	heap[root] = heap[length--];
	// trickleDown/heapify the new root.
	vSiftDown(root);
	// toggle the open position so we overwrite the extra node at tail (L/R).
	open = !open;
	// the next insert will now overwrite the last position.

	return _v;
}

void Heap::vSiftUp(int position) {

	int parent = xGetParent(position);

	// exit if @ root.
	if (position == root) {
		return;
	}

	// exit if parent less than current node
	if (heap[position] > heap[parent]) {
		return;
	}

	// go up the tree if current is less than parent
	if (heap[position] < heap[parent]) {
		// Swap the parent and the leaf.
		std::swap(heap[position], heap[parent]);
		// traverse to the parent
		return vSiftUp(heap[parent]);
	}

}

void Heap::vSiftDown(int position) {

	int left = xGetLeft(position);
	int right = xGetRight(position);

	// exit if parent is less than child.
	if (heap[position] < heap[left] && heap[position < heap[right]]) {
		return;
	}

	// compare left
	if (heap[position] > heap[left]) {
		std::swap(heap[position], heap[left]);
		return vSiftDown(heap[position]);
	}

	// compare right
	if (heap[position] > heap[right]) {
		std::swap(heap[position], heap[right]);
		return vSiftDown(position);
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

int Heap::xGetParent(int position) {

	if (root == BASE_0) {
		return position / 2;
	}
	if (root == BASE_1) {
		return (position - 1) / 2;
	}

	return -1;
}


int Heap::xGetLeft(int position) {

	if (root == BASE_0) {
		return 2 * position;
	}
	if (root == BASE_1) {
		return 2 * position + 1;
	}

	return -1;

}


int Heap::xGetRight(int position) {

	if (root == BASE_0) {
		return 2 * position + 1;
	}
	if (root == BASE_1) {
		return 2 * position + 2;
	}

	return -1;
}