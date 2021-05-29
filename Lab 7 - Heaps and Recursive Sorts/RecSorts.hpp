//
// Created by admin on 5/13/2021.
//

#ifndef LAB_7___HEAPS_AND_RECURSIVE_SORTS_RECSORTS_HPP
#define LAB_7___HEAPS_AND_RECURSIVE_SORTS_RECSORTS_HPP

#include <stdexcept>
#include <stdio.h>
#include <algorithm>
#include "stdexcept"
#include <iostream>

typedef struct tupple_t tupple_t;

void heapSort(int arr[], int length);

// getter returning indice position of target node. Follows base 1.
int xGetLeft(int position);

// getter returning indice position of target node. Follows base 1.
int xGetRight(int position);

// getter returning indice position of target node. Follows base 1.
int xGetParent(int position);

void vSiftDownMax(int arr[], int length, int position);

void vSiftDownMin(int arr[], int length, int position);

void mergeSort(int *source, int length);

int *xRecursiveMergeSort(int *source, int length, int start = -1, int end = 0);

int *xMerge(int bottom[], int top[], int bottom_length, int top_length);

void quickSort(int arr[], int length);

void vDumpArray(int arr[], int length);


#endif //LAB_7___HEAPS_AND_RECURSIVE_SORTS_RECSORTS_HPP
