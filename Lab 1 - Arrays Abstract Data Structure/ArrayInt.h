//
// Created by admin on 4/1/2021.
//

#ifndef LAB_1_ARRAYINT_H
#define LAB_1_ARRAYINT_H

#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>

class ArrayInt
{

private:
    int32_t * arr;
    uint32_t size;
    uint32_t length = 0;
    const uint8_t defaultLength = 10;

public:

    ArrayInt();

    explicit ArrayInt(uint32_t size);

    ~ArrayInt() { delete arr; };

    uint32_t getSize() const;

    void resize(uint32_t s);

    void append(int32_t v);

    int32_t getLast();

    void deleteLast();

    std::string listElements();

    void insertAt(int ind, int val);

    void removeAt(int ind);

    bool find(int val);

    bool findRemove(int val);

    int findLargest();

    void removeLargest();

    int getAt(uint32_t ind);

    void setAt(int ind, int val);

};


#endif //LAB_1_ARRAYINT_H
