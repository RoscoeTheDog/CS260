//
// Created by admin on 5/13/2021.
//

#include "Heap.hpp"


Heap::Heap(int size, HeapBase_t baseType) {

	root = baseType;
	this->size = size;
	length = baseType;  // starting length depends on the baseType of the heap implemented
	height = baseType;
	open = LEAF_LEFT;
	// allocate array.
	heap = new int[size];
}

Heap::~Heap() {

	delete[] heap;
}


void Heap::addItem(int value) {

	if (length > size - 1) {
		vResizeArray(this->size * 2);
	}

	if (length == root) {
		heap[root] = value;
		length++;
		return;
	}

	int left = xGetLeft(length);
	int right = xGetRight(length);

	// insert item into the array. Then invoke helper that sifts/trickles down.
	if (open == LEAF_LEFT) {

		// insert value
		heap[length] = value;
		// increment num elements
		length++;
		// bubble/sift. will exit if !valid
		vSiftUp(length - 1);
		// toggle available position.
		open = !open;
		// exit
		return;
	}

	if (open == LEAF_RIGHT) {
		// insert right position.
		heap[length] = value;
		// increment num elements
		length++;
		// bubble/sift up and heapify.
		vSiftUp(length - 1);

		// toggle available position.
		open = !open;
		return;
	}

}

int Heap::getItem() {

	if (length == root) {
		throw std::out_of_range("Heap is empty");
	}

	// save before writing over
	int _v = heap[root];
	// write over the root with the last inserted item && decrement length.
	heap[root] = heap[--length];
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
		return vSiftUp(parent);
	}

}

void Heap::vSiftDown(int position) {
	int left = xGetLeft(position);
	int right = xGetRight(position);

	// exit if reached bottom of tree
	if (position > length || left > length || right > length) {
		return;
	}

	// exit if parent/current node is less than child.
	if (heap[position] < heap[left] && heap[position] < heap[right]) {
		return;
	}

	// Compare the left and right children. Swap with the smallest.
	if (heap[left] < heap[right] && heap[left] < heap[position]) {
		std::swap(heap[position], heap[left]);
		return vSiftDown(left);
	}
	if (heap[right] < heap[left] && heap[right] < heap[position]) {
		std::swap(heap[position], heap[right]);
		return vSiftDown(right);
	}

}

void Heap::vReplaceDown(int position) {

	int parent = xGetParent(position);
	int left = xGetLeft(position);
	int right = xGetRight(position);

	// Check for duplicates on the left
	if (heap[position] == heap[left]) {
		return vReplaceDown(left);
	}

	// Check for duplicates on the right
	if (heap[position] == heap[right]) {
		return vReplaceDown(right);
	}

	// check if left subtree/leaf is less than right
	if (heap[left] < heap[right]) {

		// if we hit the bottom of the tree, rearrange the leafs.
		if (left > length) {

			// Overwrite everything from duplicate onward by the +1 the right relative.
			for (int i = position; i < length; ++i) {
				heap[i] = heap[i + 1];
			}

			// SiftDown/Heapify the array after.
			vSiftDown(root);

			// Toggle available leaf positions so we overwrite.
			open = !open;

			// decrement the length-- should overwrite the last remaining node.
			length--;
		}
		else {
			// overwrite the current position (parent).
			heap[position] = heap[left];
			// go to left node.
			return vSiftDown(left);
		}

	}

	// check if left subtree/leaf is less than right
	if (heap[left] > heap[right]) {

		// if we hit the bottom of the tree, rearrange the leafs.
		if (right > length) {

			// Overwrite everything from duplicate onward by the +1 the right relative.
			for (int i = position; i < length; ++i) {
				heap[i] = heap[i + 1];
			}

			// SiftDown/Heapify the array after.
			vSiftDown(root);

			// Toggle available leaf positions so we overwrite.
			open = !open;

			// decrement the length-- should overwrite the last remaining node.
			length--;
		}
		else {
			// overwrite the current position (parent).
			heap[position] = heap[right];
			// go to right node.
			return vSiftDown(right);
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

void Heap::vResizeArray(int size) {
	// catch if we are losing data.
	if (length > size) {
		throw std::out_of_range("Cannot shrink heap with existing elements!");
	}
	// allocate new array
	int *_tmp = new int[size];
	// deep copy
	memcpy(_tmp, heap, sizeof(int) * this->size);
	// delete old
	delete[] heap;
	// update new
	heap = _tmp;
	// update size
	this->size = size;
}

void Heap::vDumpArray() {

	std::cout << std::endl;

	std::cout << "Dumping array: " << std::endl;

	for (int i = 1; i < length; ++i) {
		std::cout << heap[i] << " ";
	}

	std::cout << std::endl;
}
