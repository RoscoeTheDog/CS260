//
// Created by admin on 4/6/2021.
//

#ifndef LAB_2___STACKS_AND_QUEUES_FIFO_H
#define LAB_2___STACKS_AND_QUEUES_FIFO_H
#include <cstdint>
#include <stdexcept>

class FIFO
{
private:
     int32_t * arr;
     uint32_t head = 0;
     uint32_t tail = 0;
     uint32_t length = 0;
     uint32_t size = 20;


public:

    FIFO() { arr = new int32_t[size]; }

    FIFO(uint32_t n) { arr = new int32_t[n < 1 ? size = 10 : size = n]; }

    void addHead(int32_t val);

    void addTail(uint32_t val);

    int removeHead();

    void removeTail();

    void resize();

    void listQueue();



};


#endif //LAB_2___STACKS_AND_QUEUES_FIFO_H
