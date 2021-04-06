//
// Created by admin on 4/6/2021.
//

#include "FIFO.h"

void FIFO::addHead(int32_t val)
{

}

void FIFO::addTail(uint32_t val)
{
    if (length == size)
        throw std::out_of_range("Queue is Full");
    if (tail > size)
        tail = 0;

    arr[tail++] = val;
}

int FIFO::removeHead()
{
    if (!length)
        throw std::out_of_range("IndexError");

    return arr[head++];
}
