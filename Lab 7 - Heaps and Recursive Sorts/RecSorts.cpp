//
// Created by admin on 5/13/2021.
//

#include "RecSorts.hpp"


void heapSort(int arr[], int length) {

	if (length < 0) {
		throw std::out_of_range("length must be greater than 0");
	}

	// heapify the array. Array is 0 indexed but last parent is (length/2) - 1. Pass i - 1 here
	for (int i = (length / 2); i > 0; --i) {
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

//void vRecSort(int *arr, int length, int end) {
//	if (length > 1) {
//		return vRecSort(arr, length/2, end);
//	}
//	if (arr[length] > arr[end]) {
//		std::swap(arr[length], arr[end]);
//	}
//}

typedef struct tupple_t {
	int *arr_1 = nullptr;
	int *arr_2 = nullptr;
} tupple_t;

void mergeSort(int *arr, int length, int start_1, int start_2) {

	if (length < 0) {
		throw std::out_of_range("cannot sort an empty array");
	}

	vSplit(arr, length);
	//	xMerge(arr, length, start_1);

//	mergeSort(arr, length / 2, length / 2);



}

int *xMerge(int *bottom, int *top, int bottom_length, int top_length) {

//	int *_destination = new int[length_1 + length_2];
//	int _length = 0;
//	int index_1 = 0;
//	int index_2 = 0;


	int *destination = new int[bottom_length + top_length];
	int index_1 = 0;
	int index_2 = 0;

	// Snippit taken from 'MergeSort.pdf' by Jim Bailey.
	while (index_1 < bottom_length && index_2 < top_length) {

		if (bottom[index_1] < top[index_2]) {
			destination[index_1] = bottom[index_1];
			++index_1;
		}
		else {
			destination[index_2] = top[index_2];
			++index_2;
		}

	}

	return destination;
}

int *vSplit(int *source, int length, int start, int end) {

	int *bottom = nullptr;
	int *top = nullptr;
	int *chunk = nullptr;
	int *sorted = nullptr;

	// end should never be 0 unless it's the first call
	if (start == -1) {
		start = 0;
	}
	if (end == 0) {
		end = length - 1;
	}

	// after splitting down the the center.
	if (((start + end) / 2) != start) {
		bottom = vSplit(source, (length / 2) - 1, start, (length / 2));
		top = vSplit(source, length, (length / 2) + 1, end);
	}

	if (top && bottom) {
		sorted = xMerge(bottom, top);
		delete[]top;
		delete[]bottom;
		return sorted;
	}
	else {
		// if we reached here, we have hit the last chunk of the array that is of sizeof(int) * 2
		chunk = new int[2];                  // create new array

		// copy the values.
		chunk[start] = source[start];
		chunk[end] = source[end];

		if (chunk[start] < chunk[end]) {
			std::swap(chunk[start], chunk[end]);
		}

		// return the sorted smaller or larger chunk.
		return chunk;
	}


//	// chunk the two halves
//	for (int i = 0; i < length; ++i) {
//		// bottom half
//		if (i < length / 2) {
//			// chunk the bottom half
//			for (int k = 0; k < length / 2; ++k) {
//
//				if (arr[k] < arr[i]) {
//					std::swap(arr[k], arr[i]);
//				}
//			}
//
//		}
//		// top half
//		if (i > length / 2) {
//
//			// chunk the top half
//			for (int k = length / 2; k < length; ++k) {
//
//				if (arr[k] < arr[i]) {
//					std::swap(arr[k], arr[i]);
//				}
//			}
//
//		}
//
//	}

}
