//
//  main.cpp
//  queue
//
//  Created by jim bailey on 4/6/21.
//

#include <iostream>
#include <stdexcept>
#include "Queue.h"

#define BASIC_TEST
#define WRAP_TEST
#define TEST_EXCEPT

int main()
{
#ifdef BASIC_TEST
    const int NUM_BASIC = 5;
    Queue basic;

    std::cout << "Adding five odd integers to Queue" << std::endl;
    for (int i = 0; i < NUM_BASIC; i++)
    {
        basic.addTail(2 * i + 1);
    }

    std::cout << "Expected 1 3 5 7 9" << std::endl;
    std::cout << "Actually ";
    for (int i = 0; i < NUM_BASIC; i++)
    {
        std::cout << basic.removeHead() << " ";
    }
    std::cout << std::endl;

    std::cout << "Done with basic test" << std::endl << std::endl;
#endif //BASIC_TEST

#ifdef WRAP_TEST
    const int NUM_WRAP = 10;
    Queue wrap(NUM_WRAP);
    const int NUM_ADDED = 5;

    std::cout << "Adding 10 even integers to Queue" << std::endl;
    for (int i = 0; i < NUM_WRAP; i++)
    {
        wrap.addTail(2 * i);
    }

    std::cout << "Removing 5" << std::endl;
    std::cout << "Expected 0 2 4 6 8" << std::endl;
    std::cout << "Actually ";
    for (int i = 0; i < NUM_ADDED; i++)
    {
        std::cout << wrap.removeHead() << " ";
    }
    std::cout << std::endl << std::endl;

    std::cout << "Adding five more, should wrap" << std::endl;
    for (int i = 0; i < NUM_ADDED; i++)
    {
        wrap.addTail(2 * (i+NUM_WRAP));
    }

    std::cout << "Callling dumpArray to display the contents " << std::endl;
    std::cout << "Expected 20 22 24 26 28 10 12 14 16 18" << std::endl;
    std::cout << "Actually " << wrap.dumpArray() << std::endl << std::endl;

    std::cout << "Removing 10 " << std::endl;
    std::cout << "Expected 10 12 14 16 18 20 22 24 26 28" << std::endl;
    std::cout << "Actually ";
    for (int i = 0; i < NUM_WRAP; i++)
    {
        std::cout << wrap.removeHead() << " ";
    }
    std::cout << std::endl << std::endl;

    std::cout << "Done with wrapping test" << std::endl << std::endl;
#endif //WRAP_TEST

#ifdef TEST_EXCEPT
    const int NUM_EXCEPT = 5;
    Queue except(NUM_EXCEPT);

    std::cout << "Removing from empty Queue, should throw exception" << std::endl;
    try {
        except.removeHead();
        std::cout << "Failed to throw exception" << std::endl;
    }
    catch (std::out_of_range &ex) {
        std::cout << "Caught out_of_range with message " << ex.what() << std::endl;
    }
    catch ( ... ) {
        std::cout << "Caught something else " << std::endl;
    }

    std::cout << "Adding too many values, should throw exception" << std::endl;
    try {
        for (int i = 0; i <= NUM_EXCEPT; i++)
        {
            except.addTail(i);
        }
        std::cout << "Failed to throw exception" << std::endl;
    }
    catch (std::out_of_range &ex) {
        std::cout << "Caught out_of_range with message " << ex.what() << std::endl;
    }
    catch ( ... ) {
        std::cout << "Caught something else " << std::endl;
    }

#endif //TEST_EXCEPT
    return 0;
}