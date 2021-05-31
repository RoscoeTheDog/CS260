//
// Created by admin on 5/13/2021.
//

#ifndef LAB_7___HEAPS_AND_RECURSIVE_SORTS_HEAP_HPP
#define LAB_7___HEAPS_AND_RECURSIVE_SORTS_HEAP_HPP

#include <algorithm>
#include <stdexcept>
#include <iostream>

typedef enum {
	BASE_1 = 0,
	BASE_0 = 1,
} HeapBase_t;

class Heap {
private:
	// Note: our heap will be implemented as base 1 to simplify indices expressions
	int *heap = nullptr;
	int size;
	int length;
	HeapBase_t root;

	// "Sift Up": Identical to bubble up. Brings the smallest value element to the top of the tree from the bottom up.
	void vSiftUp(int position);

	// "Sift Down" Identical to 'trickle down'. Brings the largest values from root to a deeper height in the tree.
	void vSiftDown(int position);

	// Helper that makes code syntax cleaner. If using base 0, then it is 2*i
	int xGetLeft(int position);

	// Helper that makes code syntax cleaner. If using base 0, then it is 2*i + 1
	int xGetRight(int position);

	// Helper that makes code syntax cleaner. If using base 0, then it is i/2;
	int xGetParent(int position);

	// Helper that resizes the array for when it fills.
	void vResizeArray(int size);

public:
	// Constructor. Can specify the size or what baseType to use.
	explicit Heap(int size = 10, HeapBase_t baseType = BASE_0);

	// Destructor. Cleans up the dynamic array.
	~Heap();

	// adds a new item to the heap
	void addItem(int value);

	// removes and returns the smallest item from the heap
	int getItem();

	// Dumps the array, helpful for debugging.
	void vDumpArray();

};


#endif //LAB_7___HEAPS_AND_RECURSIVE_SORTS_HEAP_HPP
