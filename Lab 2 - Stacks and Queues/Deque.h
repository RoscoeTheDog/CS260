//
// Created by admin on 4/6/2021.
//

#ifndef LAB_2___STACKS_AND_QUEUES_DEQUEUE_H
#define LAB_2___STACKS_AND_QUEUES_DEQUEUE_H
#include <cstdint>
#include <stdexcept>
#include <sstream>

class Deque
{
private:
     int32_t * arr;
    // Note: head/tail indices cannot be unsigned type.
    // Going from min to max inversely will not be caught properly without first checking for -1 index.
     int32_t head = 0;
     int32_t tail = 0;
     uint32_t length = 0;
     uint32_t size = 20;

public:

    Deque() { arr = new int32_t[size]; }

    Deque(uint32_t n) { arr = new int32_t[n < 1 ? size = 10 : size = n]; }

    ~Deque() { delete arr; }

    void addHead(int32_t val);

    void addTail(int32_t val);

    int removeHead();

    int removeTail();

    void resize(uint32_t size);

    bool isEmpty() const{ return length; };

    std::string listQueue();

    std::string dumpArray();

};


#endif //LAB_2___STACKS_AND_QUEUES_DEQUEUE_H
