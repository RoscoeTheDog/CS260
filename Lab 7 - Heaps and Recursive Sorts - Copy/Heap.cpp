//
// Created by admin on 5/13/2021.
//

#include "Heap.hpp"


Heap::Heap(int size, HeapBase_t baseType) {
	// Here we can initialize the size of the arrau and set up our resources,
}

Heap::~Heap() {
	// delete the heap when object is destroyed.
}


void Heap::addItem(int value) {

	// Resize if the array is to large.

	// Insert at root if empty.

	// insert item into the array. Then invoke helper that sifts/trickles down.

	// increment the num elements

	// bubble/sift up. exit if !valid

	// exit
	return;
}

int Heap::getItem() {

	// throw exception if heap is empty

	// first save value before writing over it's position.

	// then write over the root with the last inserted item && decrement the heap length.

	// trickleDown the new root value so it is balanced.

	// the next insert will overwrite the lastly inserted position in the heap.

	// return the temporary variable holding the value.
	;
}

void Heap::vSiftUp(int position) {

	// Get the parent of this node, according to it's position.

	// exit if @ root.

	// exit if parent is less than visiting node's value

	// if visiting node is less than parent

	// Swap the parent and the leaf.

	// traverse to the parent

}

void Heap::vSiftDown(int position) {

	// Get the left and right positions in relation to the visiting node.

	// exit if reached bottom of tree

	// exit if parent/current node is less than child.

	// Compare the left and right children. Swap visiting node with the smaller of the two.

	// Traverse to the node that was swapped.

}

int Heap::xGetParent(int position) {

	// Get the parent index value, based on which base-type is being used.

	return -1;
}


int Heap::xGetLeft(int position) {

	// Get the left index value, based on which base-type is being used.

	return -1;

}


int Heap::xGetRight(int position) {

	// Get the right index value, based on which base-type is being used.

	return -1;
}

void Heap::vResizeArray(int size) {
	// except if the user is trying to destroy data

	// allocate a new array

	// memcpy

	// delete old array

	// update new heap member

	// update size member
}

void Heap::vDumpArray() {

	// Helper function that will dump the array to the console. Useful for debugging.
}
