//
// Created by admin on 5/13/2021.
//

#include "RecSorts.hpp"


void heapSort(int arr[], int length, int position) {

	int parent = xGetParent(position);
	int left = xGetLeft(position);
	int right = xGetRight(position);

	if (length < 0) {
		throw std::out_of_range("length must be greater than 0");
	}

	int items[length];
	memcpy(items, arr, sizeof(int) * length);

	// heapify the array. Array is 0 indexed but last parent is (length/2) - 1. Pass i - 1 here
	for (int i = (length/2); i > 0; --i) {
		vSiftDownMax(arr, length, i - 1);
	}

	memcpy(items, arr, sizeof(int) * length);

	int _l = length;

	for (int i = length - 1; i > 0; --i) {
		std::swap(items[0], items[i]);
		// trickleDown/heapify the new root.
		vSiftDownMin(items, length, 0);
		// the next call will now swap/sort the last position.
	}


	while(1) {};

}

void vSiftDownMax(int arr[], int length, int position) {

	int left = xGetLeft(position);
	int right = xGetRight(position);

	// exit if reached bottom of tree
	if (position > length || left > length || right > length) {
		return;
	}

	// exit if parent/current node is less than child.
	if (arr[position] > arr[left] && arr[position] > arr[right]) {
		return;
	}

	// Compare the left and right children. Swap with the largest.
	if (arr[left] > arr[right] && arr[left] > arr[position]) {
		std::swap(arr[position], arr[left]);
		return vSiftDownMax(arr, length, left);
	}
	if (arr[right] > arr[left] && arr[right] > arr[position]) {
		std::swap(arr[position], arr[right]);
		return vSiftDownMax(arr, length, right);
	}

}

void vSiftDownMin(int arr[], int length, int position) {

	int left = xGetLeft(position);
	int right = xGetRight(position);

	// exit if reached bottom of tree
	if (position > length || left > length || right > length) {
		return;
	}

	// exit if parent/current node is less than child.
	if (arr[position] < arr[left] && arr[position] < arr[right]) {
		return;
	}

	// Compare the left and right children. Swap with the largest.
	if (arr[left] < arr[right] && arr[left] < arr[position]) {
		std::swap(arr[position], arr[left]);
		return vSiftDownMax(arr, length, left);
	}
	if (arr[right] < arr[left] && arr[right] < arr[position]) {
		std::swap(arr[position], arr[right]);
		return vSiftDownMax(arr, length, right);
	}

}

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

void vDumpArray(int arr[], int length) {

	std::cout << std::endl;

	std::cout << "Dumping array: " << std::endl;

	for (int i = 1; i < length; ++i) {
		std::cout << arr[i] << " ";
	}

	std::cout << std::endl;
}
