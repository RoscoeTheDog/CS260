//
// Created by admin on 4/6/2021.
//

#include "Deque.h"

#define RESIZE1
//#define RESIZE2
//#define RESIZE3

void Deque::addHead(int32_t val)
{
    // catch full queue
    if (length == size)
        resize(size*2);
    // catch wraps
    if (head > static_cast<int32_t>(size) - 1)          // unwrap
    {
        head = 0;
        WRAPPED = false;
    }
    if (head < 0)                                       // wrap
    {
        head = size - 1;
        WRAPPED = true;
    }

    /*
     *  For Post increment implementation, check special case where
     *  cursors are initialized at aligned index (0) but length is null.
     *
     *  Both cursors would have to be move upon the first insert to avoid overwriting data
     *
    */
    arr[head--] = val;

    if (head + 1 == tail && length == 0)
        tail++;

    length++;
}

void Deque::addTail(int32_t val)
{
    if (head < 0)
    {
        head = size - 1;
        WRAPPED = true;
    }
    if (length == size)
        resize(size*2);
    if (tail > static_cast<int32_t>(size) - 1)
        tail = 0;

    /*
     *  For Post increment implementation, check special case where
     *  cursors are initialized at aligned index (0) but length is null.
     *
     *  Both cursors would have to be move upon the first insert to avoid overwriting data
     *
    */
    arr[tail++] = val;

    if (head == tail - 1 && length == 0)
        head--;

    length++;
}

int Deque::removeHead()
{
    // validate
    if (!length)
        throw std::out_of_range("Deque is Empty");
    // catch wraps
    if (head > static_cast<int32_t>(size) - 1 )     // unwrap
        head = 0;
    if (head < 0)                                   // wrap
        head = size - 1;

    // This essentially performs a 'look ahead'. I have to do this in order to keep the 'post-increment' behavior.
    // doing return[++head] is 5 less lines of code, so pre-increment really works much better here.
    int32_t v;

    if (head + 1 > static_cast<int32_t>(size) - 1)
        v = arr[0];
    else
        v = arr[head + 1];

    length--;
    head++;

    return v;
}

int Deque::removeTail()
{
    // validate
    if (!length)
        throw std::out_of_range("Deque is Empty");
    // catch wraps
    if (tail > static_cast<int32_t>(size) - 1)          // wrap
        tail = 0;
    if (tail < 0)                                       // unwrap
        tail = size - 1;


    // This essentially performs a 'look ahead'. I have to do this in order to keep the 'post-increment' behavior.
    // doing return[--tail] is 5 less lines of code, so pre-increment really works much better here.
    int32_t v;

    if (tail - 1 < 0)
        v = arr[size - 1];
    else
        v = arr[tail - 1];

    length--;
    tail--;

    return v;
}

void Deque::resize(uint32_t size)
{
    int32_t * temp;
    temp = new int32_t[size];

#ifdef RESIZE1
    // Algo 1 - Jim's (instructor) method. Clean, easy to read. re-uses code. Works when wrapped or unwrapped. I like the simplicity.
    // calling removeHead() modifies length so save it ahead of time.
    uint32_t l = length;
    for (unsigned i = 0; i < l; ++i) {
        temp[i] = removeHead();
    }
    // Restore length count after removing head elements.
    length = l;
    head = -1;
    tail = length;
#endif

#ifdef RESIZE2
    // Algo 2 - Copy Head to end of array then copy 0 : tail.
    // David came up with this while we were discussing stuff
    // Solid but breaks when copying unwrapped arrays so I added a little logic check for that.
    if (WRAPPED) {

        int j = 0;

        // unwrap starting from head to end.
        for (int i = head + 1; i < this->size; ++i){
            temp[j] = arr[i];
            ++j;
        }

        // append 0 to tail after.
        for (int i = 0; i < tail; ++i) {
            temp[j] = arr[i];
            ++j;
        }

        head = size - 1;    // this becomes 0 if doing pre-increment method for the head. I am not in this scenario.
        tail = length;
    }
    else{
        // we can just do a quick deep copy if not wrapped (assuming it starts from 0)
        memcpy(temp, arr, sizeof(int32_t) * static_cast<int32_t>(length));

        head = size - 1;
        tail = this->size;
    }

#endif

#ifdef RESIZE3
    // Algo #3 -- a new way I came up with after thinking of a fastest-possible solution. Simple deep copy, then append missing 0 : tail.
    if (WRAPPED) {

        // copy wrapped arr
        memcpy(temp, arr, sizeof(int32_t) * static_cast<int32_t>(this->size));

        // always start up to tail.
        int k = 0;

        // this will be the new location af the tail (i.e head + length as if it weren't 0 indexed)
        tail = (head + 1) + length;

        // append the missing 0 - tail to the end of the copied array.
        for(unsigned i = this->size; i < tail; ++i) {
            temp[i] = arr[k];
            k++;
        }
    }
    else    // Don't move head/tail and simple deep copy if not wrapped.
        memcpy(temp, arr, sizeof(int32_t) * static_cast<int32_t>(this->size));
#endif

    // cleanup
    delete arr;
    arr = temp;

    // finally update size before exit.
    this->size = size;
}

std::string Deque::listQueue()
{
    std::stringstream S;
    int32_t * copy;
    copy = new int32_t[size];

    /*
     *
     *  No matter what, this will always be O(n) to return a list of all elements in order.
     *
     *  So I might as well just copy the array 1:1 and then pop it off one at a time, deleting the copy after.
     *  Alternatively, could  iterate through head : size and 0 : tail to do the same thing but that's more code.
     *
     *  simple copy/pop duplicates the memory used temporarily, but doesn't require as much code.
     *  Peaking elements and adding logic checks for bounds adds a lot of code, but saves memory from the simpler method.
     *
     *  So it is a tradeoff.
     *
     *  See Deque::resize(). I added basically included all other methods of doing this there.
     *
     */

    // just assume this is wrapped (i.e copy full size bytes instead of just length).
    memcpy(copy, arr, sizeof(int32_t) * size);

    // Save these ahead of time
    uint32_t l = length;
    int32_t h = head;
    int32_t t = tail;

    for (uint32_t i = 0; i < l; ++i)
        S << removeHead() << " ";

    // Restore these after popping.
    length = l;
    tail = t;
    head = h;

    // Cleanup
    delete arr;
    arr = copy;

    return S.str();
}

std::string Deque::dumpArray()
{
    // Depending on the algo used, dumpArray may not reflect the results from the driver correctly.
    // --but the Deque will still be behaving as it should relative to the head/tail.
    std::stringstream S;

    for (uint32_t i = 0; i < size; ++i)
        S << arr[i] << ' ';

    return S.str();
}

