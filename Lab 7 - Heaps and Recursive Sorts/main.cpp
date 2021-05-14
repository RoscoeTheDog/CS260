//
//  main.cpp
//  SortingLab
//
//  Created by jim bailey on 11/15/19.
//  Copyright © 2019 jim bailey. All rights reserved.
//

#include <iostream>
#include <stdexcept>

// TESTHEAP and TESTPRIORITYQ are Base Lab
#define TESTHEAP
//#define TESTPRIORITYQ


#ifdef TESTHEAP

#include "Heap.hpp"

#endif

#ifdef TESTPRIORITYQ
#include "PriorityQ.hpp"
#endif

#include "RecSorts.hpp"


using std::cout;
using std::endl;


int main() {

	const int NUM_VALUES = 15;

#ifdef TESTHEAP
	int heapVals[NUM_VALUES] = {10, 5, 30, 15, 20, 40, 60, 25, 50, 35, 45, 65, 70, 75, 55};

	cout << "Creating heap of default size (10)" << endl;
	Heap pile;

	// load the heap with values
	cout << "Now filling it with 15 values, should cause doubling of size" << endl << endl;
	for (int i = 0; i < NUM_VALUES; i++) {
		pile.addItem(heapVals[i]);
	}

	cout << "Now testing heapsort: " << std::endl;
	heapSort(heapVals, NUM_VALUES);
	for (int i = 0; i < NUM_VALUES; i++) {
		cout << heapVals[i] << " ";
	}
	cout << endl;

	// remove values, should be in ascending order
	cout << "Now removing values to see if properly ordered" << endl;
	cout << " In order s/b: 5 10 15 20 25 30 35 40 45 50 55 60 65 70 75" << endl;
	cout << " Actual order: ";
	for (int i = 0; i < NUM_VALUES; i++) {
		cout << pile.getItem() << " ";
	}

	cout << endl << endl;

	// now test for taking one too many
	cout << "Now testing for exception on removing" << endl;
	try {
		pile.getItem();
		cout << "Should have failed, but did not" << endl;
	}
	catch (std::exception &ex) {
		cout << "Caught error message: " << ex.what() << endl;
	}

	cout << endl << "Done with testing heap" << endl << endl;

#endif // TESTHEAP

#ifdef TESTPRIORITYQ
	int pqVals[NUM_VALUES] = {2, 4, 6, 8, 10, 1, 3, 5, 7, 9, 11, 15, 12, 14, 13};

	cout << "Creating priority queue of default size (10)" << endl;
	PriorityQueue pList;

	// load the heap with values
	cout << "Now filling it with 15 values, should cause doubling of size" << endl << endl;
	for(int i = 0; i < NUM_VALUES; i++)
		pList.addItem(pqVals[i]);

	// remove values, should be in ascending order
	cout << "Now removing values to see if properly ordered" << endl;
	cout << " In order s/b: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15" << endl;
	cout << " Actual order: ";
	for(int i = 0; i < NUM_VALUES; i++)
		cout << pList.getItem() << " " ;
	cout << endl << endl;

	// now test for taking one too many
	cout << "Now testing for exception on removing" << endl;
	try {
		pList.getItem();
		cout << "Should have failed, but did not" << endl;
	}
	catch (std::exception &ex) {
		cout << "Caught error message: " << ex.what() << endl;
	}

	cout << endl << "Done with testing priority queue" << endl << endl;

#endif // TESTPRIORITYQ


	return 0;
}