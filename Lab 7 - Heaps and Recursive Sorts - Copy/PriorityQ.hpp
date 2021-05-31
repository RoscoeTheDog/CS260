//
// Created by admin on 5/13/2021.
//

#ifndef LAB_7___HEAPS_AND_RECURSIVE_SORTS_PRIORITYQ_HPP
#define LAB_7___HEAPS_AND_RECURSIVE_SORTS_PRIORITYQ_HPP

#include "Heap.hpp"

class PriorityQueue {
private:
	// Use class composition from heap class to create a priority queue.
	Heap heap;

public:

	// Constructor. Doesn't do anything since heap constructor handles resources.
	PriorityQueue();

	// Destructor. Doesn't do anything since heap constructor handles resources.
	~PriorityQueue();

	// Add an item to the Queue. This wraps the heap class addItem() method.
	void addItem(int value);

	// Return and remove the smallest item from the Queue (i.e, highest priority). This wraps heap class getItem() method.
	int getItem();

};


#endif //LAB_7___HEAPS_AND_RECURSIVE_SORTS_PRIORITYQ_HPP
