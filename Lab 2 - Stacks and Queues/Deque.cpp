//
// Created by admin on 4/6/2021.
//

#include "Deque.h"

void Deque::addHead(int32_t val)
{
    if (length == size)
        resize(size*2);
    if (head > static_cast<int32_t>(size) - 1)
        head = 0;
    if (head < 0)
        head = size - 1;

    arr[head--] = val;

    /*
     *  For Post increment implementation, check special case where
     *  cursors are initialized at aligned index (0) but length is null.
     *
     *  Both cursors would have to move on the initial insert to avoid overwriting.
     *
    */
    if (head + 1 == tail && length == 0)
        tail++;

    length++;
}

void Deque::addTail(int32_t val)
{
    if (length == size)
        resize(size*2);
    if (tail > static_cast<int32_t>(size) - 1)
        tail = 0;

    arr[tail++] = val;

    /*
     *  For Post increment implementation, check special case where
     *  cursors are initialized at aligned index (0) but length is null.
     *
     *  Both cursors would have to be move upon the initial insert to avoid overwriting data
     *
    */

    if (head == tail - 1 && length == 0)
        head--;

    length++;
}

int Deque::removeHead()
{
    if (!length)
        throw std::out_of_range("Deque is Empty");
    // Pre-validate and check for wraps.
    if (head > static_cast<int32_t>(size) - 1 )    // unwrap
        head = 0;
    if (head < 0)           // wrap
        head = size - 1;

    int32_t v;

    // This essentially does a 'look ahead'. I have to do this in order for 'post-increment' to actually work.
    // doing return[++head] is 5 less lines of code so pre-increment works so much better here.
    if (head + 1 > static_cast<int32_t>(size) - 1)  // also this cast is dumb, but necessary.
        v = arr[0];
    else
        v = arr[head + 1];

    length--;
    head++;
    return v;
}

int Deque::removeTail()
{
    if (!length)
        throw std::out_of_range("Deque is Empty");
    if (tail > static_cast<int32_t>(size) - 1)
        tail = 0;
    if (tail < 0)
        tail = size - 1;

    int32_t v;

    // This essentially does a 'look ahead'. I have to do this in order for 'post-increment' to actually work.
    // doing return[++head] is 5 less lines of code so pre-increment works so much better here.
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

    /*
     *  For this I stuck with Post-incrementation since that was what I had started with at the beginning of this lab.
     *  It has been discussed during lectures that using a mix of pre/post incrementation makes the indexing a little easier.     *
     *
     *  I spent time brainstorming with David (student) on this issue for a few hours. Ultimately, Jim's (instructor)
     *  method of calling removeHead() was probably the cleanest and most preferred way of copying data which he revealed later.
     *
     *  See included screenshot for other method concepts. Note that this is just to show that
     *  the work had been done prior and that there were thoughts put into our own solutions.
     *
     *  The best performing final solution would probably be using a combination of pre/post increments and the memcpy() function.
     *  Otherwise you are left with using iterative deep copy, awkward pointer arithmetic, or a combination of both.
     *
     */
    int32_t * temp;
    temp = new int32_t[size];

    uint32_t l = length; // removeHead() modifies length so save it ahead of time.
    // Jim's way. Clean, easy to read. re-uses code. I like this method most.
    for (int i = 0; i < this->size; ++i) {
        temp[i] = removeHead();
    }

    // Restore length after removing head elements.
    length = l;

    /// removeHead() OR memcpy()  ///
    /*
     * might be a little faster if not wrapped just to copy since it is non-interative.
     *
     * first check if array is wrapped or not.
     *
     * arr will be wrapped if head is larger than tail in most cases.
     * When using post-increment for head/tail, they actually cross indexes when the array is full so this becomes untrue.
     */
    int j = 0;

    // David came up with this other unwrapping solution while we were brainstorming.
    // Seemed really solid but breaks when copying unwrapped arrays so I added a little logic check for that.
    if (head <= tail && length != 0 ||
        head > tail && length == this->size - 1) {

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

        head = size - 1;    // this becomes 0 if doing pre-increment method for head. I am not in this case.
        tail = length;
    }
    else
        // we can just do a 1:1 copy for the array's length if not wrapped.
        memcpy(temp, arr, sizeof(int32_t) * static_cast<int32_t>(length));

    // cleanup after resize is done.
    delete arr;
    arr = temp;

    // finally update the size before exit.
    this->size = size;
}

std::string Deque::listQueue()
{
    std::stringstream S;
    int32_t * copy;
    copy = new int32_t[size];

    /*
     *
     *  No matter what it will always be O(n) to return a list of all elements in order.
     *
     *  So I might as well just copy the array 1:1 and then pop it off one at a time, deleting copy after.
     *  However, you could also iter through head : size and 0 : tail-1 to do the same thing.
     *
     *  Copying/popping temporarily duplicates memory but saves a lot of code.
     *  Peaking elements and adding logic checks for bounds adds a lot of code, but saves memory.
     *
     *  It's a tradeoff.
     *
     *  See resize for the more 'fun' ways of doing this :)
     *
     */

    memcpy(copy, arr, sizeof(int32_t) * size); // just assume it's wrapped (i.e copy all bytes).

    // Save these ahead of time
    uint32_t l = length;
    int32_t h = head;
    int32_t t = tail;

    for (uint32_t i = 0; i < l; ++i)
        S << removeHead() << " ";

    // Restore these
    length = l;
    tail = t;
    head = h;

    delete arr;
    arr = copy;

    return S.str();
}

std::string Deque::dumpArray()
{
    std::stringstream S;

    for (uint32_t i = 0; i < size; ++i)
        S << arr[i] << ' ';

    return S.str();
}

