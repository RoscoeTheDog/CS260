//
// Created by admin on 5/13/2021.
//

#include "PriorityQ.hpp"

PriorityQueue::PriorityQueue() {
	// nothing to be set. heap constructor takes care of this.
}

PriorityQueue::~PriorityQueue() {
	// nothing to destroy. just pass.
	;
}

void PriorityQueue::addItem(int value) {
	heap.addItem(value);
}

int PriorityQueue::getItem() {
	return heap.getItem();
}
