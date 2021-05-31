//
// Created by admin on 5/13/2021.
//

#ifndef LAB_7___HEAPS_AND_RECURSIVE_SORTS_PRIORITYQ_HPP
#define LAB_7___HEAPS_AND_RECURSIVE_SORTS_PRIORITYQ_HPP

#include "Heap.hpp"

class PriorityQueue {
private:
	Heap heap;

public:

	PriorityQueue();

	~PriorityQueue();

	void addItem(int value);

	int getItem();

};


#endif //LAB_7___HEAPS_AND_RECURSIVE_SORTS_PRIORITYQ_HPP
