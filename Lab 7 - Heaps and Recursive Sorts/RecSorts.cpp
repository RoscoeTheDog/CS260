//
// Created by admin on 5/13/2021.
//

#include "RecSorts.hpp"

int last = 0;

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

void mergeSort(int *source, int length) {
	// I tried like a million different syntaxes trying to just modify the original passed in reference
	// but I was not getting anywhere with it. I could not change the reference address with a pointer either.
	// I resorted just to doing a quick deep copy of the values and then deleting the extra array.
	int *sorted = xRecursiveMergeSort(source, length);
	memcpy(source, sorted, sizeof(int) * length);
	delete[]sorted;
}

int *xRecursiveMergeSort(int *source, int length, int start, int end) {

	int *bottom = nullptr;      // bottom half of split array.
	int *top = nullptr;         // top half of split array.
	int *chunk = nullptr;       // the 'working' chunk (bot/top) to be returned recursively.
	int *sorted = nullptr;      // the final array after it's been sorted.

	// check for default param values.
	// initialize them to start and end of array length if we are at the bottom of the callstack.
	if (start == -1) {
		start = 0;
	}
	if (end == 0) {
		end = length - 1;
	}

	// Split down the center of the passed array. Then recursively call the bottom/top chunks.
	// When the mean of the start/end equals the start value, we have a length of <= 1 and we can exit.
	if (((start + end) / 2) != start) {
		// move the end position to the left side of the latest middle slice.
		bottom = xRecursiveMergeSort(source, (length / 2) - 1, start, (start + end) / 2);
		// increase start by last chunk length. (end - start) + 1
		start += ((start + end) / 2) - start + 1;
		// move the start position to the right side of the latest middle slice.
		top = xRecursiveMergeSort(source, length, start, end);
	}

	// if we have both a valid bottom and top chunk initialized,
	// then we know we are returning down the call stack and we can begin merging the sorted chunks.
	if (top && bottom) {
		// some chunks after merged may be >= 2, so we have calculate how large they are.
		// Note: using sizeof(chunk) / sizeof(int) was giving me strange results, so I will do they pointer arithmetic thing I did before.
		sorted = xMerge(bottom, top, end - start + 1, end - start + 1);
		// clean up the old chunks after merged and new arr is created.
		delete[]top;
		delete[]bottom;
		return sorted;  // return the new sorted and merged chunk of memory.
	}
		// Keep splitting if we don't have the 2 smallest halves yet.
	else {
		// If the length is not an even number, then we will have a chunk leftover of length 1.
		// Validate and catch this.
		if (start == end) {             // chunk length of 1
			chunk = new int[1];
			chunk[0] = source[start];
		}
		else {                          // chunk length of 2
			chunk = new int[2];
			chunk[0] = source[start];
			chunk[1] = source[end];

			// if we know there are two values in a chunk, sort with a quick swap.
			if (chunk[1] < chunk[0]) {
				std::swap(chunk[0], chunk[1]);
			}

		}

		// return the sorted smaller chunk to the last recursive call.
		return chunk;
	}

}

int *xMerge(int bottom[], int top[], int bottom_length, int top_length) {
	// bottom length should never be an odd number.
	// if a chunk of length 1 is remaining, it should always be the top chunk.
	// ex: last chunk has length of 3, and bottom will have length of 4 but only reflect as 3.
	if (bottom_length % 2) {
		bottom_length = top_length + 1;
	}

	// iterators.
	int index_0 = 0;
	int index_1 = 0;
	int index_2 = 0;
	// new array.
	int *destination = new int[bottom_length + top_length];

	int test1[bottom_length];
	int test2[top_length];

	memcpy(test1, bottom, sizeof(int) * bottom_length);
	memcpy(test2, top, sizeof(int) * top_length);

	while (index_0 < bottom_length + top_length) {

		if (index_1 < bottom_length) {

			if (bottom[index_1] < top[index_2]) {
				destination[index_0] = bottom[index_1++];
				index_0++;
			}
			else {
				if (top[index_2] < bottom[index_1]) {
					destination[index_0] = top[index_2++];
					index_0++;
				}
			}

		}
		// if > then we know the bottom chunk was the only thing inserted
		// we need to do this check to avoid deadlock
		if (index_1 >= bottom_length) {
			// do not assume the chunk size is always going to be of length 2.
			while (index_2 < top_length) {
				destination[index_0++] = top[index_2++];
			}
			break;
		}
		if (index_2 < top_length) {
			if (top[index_2] < bottom[index_1]) {
				destination[index_0] = top[index_2++];
				index_0++;
			} else {
				if (bottom[index_1] < top[index_2]) {
					destination[index_0] = bottom[index_1++];
					index_0++;
				}
			}

		}
		// if > then we know the top chunk was the only thing inserted
		// we need to do this check to avoid deadlock
		if (index_2 >= top_length) {
			// do not assume the chunk size is always going to be of length 2.
			while (index_1 < bottom_length) {
				destination[index_0++] = bottom[index_1++];
			}
			break;
		}

		// on the very last iteration, no matter the value, append it to the end.
		// this will exit any occurring deadlock in our loop.
		if (bottom_length + top_length - index_0 == 1) {
			if (index_1 < bottom_length) {
				destination[index_0++] = bottom[index_1++];
			}
			if (index_2 < top_length) {
				destination[index_0++] = top[index_2++];
			}
		}

	}

	int test[16];
	memcpy(test, destination, sizeof(int) * 16);
	int i;

	return destination;
}