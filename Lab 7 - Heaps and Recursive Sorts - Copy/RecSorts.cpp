//
// Created by admin on 5/13/2021.
//

#include "RecSorts.hpp"

void heapSort(int *arr, int length, int position) {

	// heapSort will basically be implemented using a combination of a recursive siftDown() and getItem().
	// These have already been described elsewhere in this pseudo part of the lab so see those for more details.
}

// These helpers will do the same thing that their corresponding methods from heap class does. The difference is that
// we have to do the implementation as base type 0, and the methods from heap class cannot be made static or used otherwise it
// ignores the constraints of the lab ("Does not use heap class").
int xGetLeft(int position) {

	return 2 * position + 1;
}

int xGetRight(int position) {

	return 2 * position + 2;
}

int xGetParent(int position) {

	if (position == 0) {
		return 0;
	}

	return (position - 1) * 2;
}
