//
// Created by admin on 4/1/2021.
//

#include "ArrayInt.h"

ArrayInt::ArrayInt()
{
    arr = new int32_t[this->size = defaultLength];
}

ArrayInt::ArrayInt(uint32_t size)
{
    if (size > 0)
        this->size = size;
    else
        this->size = defaultLength;

    this->arr = new int32_t[this->size];
}

uint32_t ArrayInt::getSize() const
{
    return this->size;
}

void ArrayInt::resize(uint32_t s)
{
    if (s > this->size){
        int32_t * arrNew;

        arrNew = new int32_t[s];

        // Copy.
        for (int i = 0; i < this->size; ++i){
            arrNew[i] = this->arr[i];
        }

        delete [] this->arr;
        this->arr = arrNew;

        this->size = s;
    }

}

void ArrayInt::append(int32_t v)
{
    // do we need to extend?
    if (this->length + 1 > this->size){
        resize(this->size * 2);
    }
    // insert.
    arr[this->length] = v;

    this->length++;
}

int32_t ArrayInt::getLast()
{
    if (this->length < 1)
        throw std::out_of_range
        ("IndexError");
    else
        return this->arr[this->length - 1];

}

void ArrayInt::deleteLast()
{
    if (this->length < 1)
        throw std::out_of_range
        ("IndexError");
    this->length -= 1;
}

std::string ArrayInt::listElements()
{
    std::stringstream S;

    if (this->length == 0)
        return "Empty Array";

    for (int i = 0; i < this->length; ++i) {
        S << this->arr[i] << ", ";
    }

    return S.str();
}

void ArrayInt::insertAt(int ind, int val)
{
    if (ind < 0 || ind > this->length || ind > this->size){
        throw std::out_of_range("IndexError");
    }
    if (this->length >= this->size) {
        resize(this->size * 2);
    }

    int32_t * temp;
    temp = new int32_t[this->size];
    // deep copy arr
    memcpy(temp, this->arr, sizeof(int32_t) * this->size);

    // shift everything else up relative to +1 right of the insert location
    for (int i = ind + 1; i < static_cast<int32_t>(this->length) + 1; ++i)
        temp[i] = this->arr[i - 1];

    // perform the insert
    temp[ind] = val;

    delete[] this->arr;
    this->arr = temp;

    this->length++;
}

void ArrayInt::removeAt(int ind)
{
    if (ind < 0 || ind > this->length || ind > this->size){
        throw std::out_of_range
        ("IndexError");
        return;
    }

    // shift everything else down relative to -1 left of the insert location
    for (int i = ind + 1; i < this->length; ++i) {
        this->arr[i - 1] = this->arr[i];
    }

    this->length--;

}

bool ArrayInt::find(int val)
{
    for (int i = 0; i < this->size; ++i) {
        if (arr[i] == val)
            return true;
    }

    return false;
}

bool ArrayInt::findRemove(int val)
{
    // assume -1 means 'no match', since indices are unsigned.
    int32_t ind = -1;

    // find index
    for (int i = 0; i < this->size; ++i) {
        if (arr[i] == val)
            ind = i;
    }

    // perform remove
    if (ind != -1){
        removeAt(ind);
        return true;
    }

    return false;
}

int ArrayInt::findLargest()
{
    int32_t largest = std::numeric_limits<int32_t>::min();

    if (this->length < 1)
        throw std::out_of_range
        ("IndexError");

    for (unsigned i = 0; i < this->length; ++i) {
        if (this->arr[i] > largest)
            largest = this->arr[i];
    }

    return largest;
}

void ArrayInt::removeLargest()
{
    // findLargest and findRemove already perform indexing validation.
    // Nested call works here.
    findRemove(findLargest());
}

void ArrayInt::setAt(int32_t ind, int val)
{
    if (ind > this->size)
        throw std::out_of_range
        ("IndexError");

    // overwrite a previous value. this is a destructive set. do not insert or expand.
    this->arr[ind] = val;

    /*
     *  The driver indicates that fragmented setting is permissible here.
     *
     *  So other code does not break (like append), we need to update the variable
     *  responsible for tracking the furthest positioned index if the set position is greater than a single increment.
     *
     */

    // note: this->length is the array range that is *non-zero* indexed
    if (ind > this->length)
        this->length = ind;
    if (ind == this->length)
        this->length++;
}

int ArrayInt::getAt(uint32_t ind)
{
    if (ind > this->length)
        throw std::out_of_range
        ("IndexError");

    return this->arr[ind];
}
