//
// Created by admin on 5/13/2021.
//

#include "RecSorts.hpp"


void heapSort(int arr[], int length) {

	if (length < 0) {
		throw std::out_of_range("length must be greater than 0");
	}

	// heapify the array. Array is 0 indexed but last parent is (length/2) - 1. Pass i - 1 here
	for (int i = (length/2); i > 0; --i) {
		vSiftDownMax(arr, length, i - 1);
	}

	for (int i = length - 1; i > 0; --i) {
		std::swap(arr[0], arr[i]);
		// trickleDown/heapify the new root.
		vSiftDownMax(arr, i - 1, 0);
		// the next call will now swap/sort the last position.
	}

}

void vSiftDownMax(int arr[], int length, int position) {

	int left = xGetLeft(position);
	int right = xGetRight(position);

	// exit if reached bottom of tree
	if (position > length || left > length || right > length) {
		return;
	}

	// exit if parent/current node is greater than child.
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
		return vSiftDownMin(arr, length, left);
	}
	if (arr[right] < arr[left] && arr[right] < arr[position]) {
		std::swap(arr[position], arr[right]);
		return vSiftDownMin(arr, length, right);
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
