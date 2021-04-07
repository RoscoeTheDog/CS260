//
// Created by admin on 4/6/2021.
//

#include "Queue.h"

void Queue::addHead(int32_t val)
{
    if (length > size - 1)
        throw std::out_of_range("Queue is Full");
    if (head > size - 1)
        head = 0;

    arr[head++] = val;
    length++;
}

void Queue::addTail(int32_t val)
{
    if (length > size - 1)
        throw std::out_of_range("Queue is Full");
    if (tail > size - 1)
        tail = 0;

    arr[tail++] = val;
    length++;
}

int Queue::removeHead()
{
    // throws if empty
    if (!length)
        throw std::out_of_range("Queue is Empty");
    if (head > size - 1)
        head = 0;
    if (head < 0)
        head = size - 1;

    length--;
    return arr[head++];
}

int Queue::removeTail()
{
    if (!length)
        throw std::out_of_range("Queue is Empty");
    if (tail > size - 1)
        tail = 0;
    if (tail < 0)
        tail = size - 1;

    length--;
    return arr[tail--];
}

void Queue::resize(uint32_t size)
{
    int32_t * temp;
    temp = new int32_t[size];

    // Deep copy
    memcpy(temp, arr, sizeof(int32_t) * this->size);

    delete arr;
    arr = temp;
}

std::string Queue::listQueue()
{
    std::stringstream S;

    uint32_t iterHead = head;

    while(iterHead != tail)
        S << arr[iterHead > (size - 1) ? iterHead++ : iterHead = 0];

    return S.str();
}

std::string Queue::dumpArray()
{
    std::stringstream S;

    for (uint32_t i = 0; i < size; ++i)
        S << arr[i] << ' ';

    return S.str();
}

