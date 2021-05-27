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

void mergeSort(int arr[], int length, int start_1 = 0, int start_2 = -1);

int* xMerge(int bottom[], int top[]);

int* vSplit(int *source, int length, int index_1 = -1, int index_2 = 0);

void quickSort(int arr[], int length);

void vDumpArray(int arr[], int length);


#endif //LAB_7___HEAPS_AND_RECURSIVE_SORTS_RECSORTS_HPP
