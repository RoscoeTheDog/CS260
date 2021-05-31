//
//  main.cpp
//  HashTables
//
//  Created by jim bailey on 4/19/21.
//

#include <iostream>
#include "StringHash.hpp"
//#define TEST_BASE // always define this if testing any base
//#define TEST_BASE_FIND
//#define TEST_BASE_REMOVE
//#define TEST_BASE_DISPLAY
//#define TEST_BASE_GROW

#define TEST_ADV // always define this if testing any advanced
#define TEST_ADV_FIND
#define TEST_ADV_REMOVE
#define TEST_ADV_DISPLAY
#define TEST_THINK // test adv grow

#ifdef TEST_BASE
#include "StringHash.hpp"
#endif
#ifdef TEST_ADV
#include "ChainedHash.hpp"
#endif

int main()
{

#ifdef TEST_BASE
    const int BASE_SIZE = 5;
    std::string baseWords[BASE_SIZE] = {"apple", "pear", "oak", "pine", "peach"};
    
    std::cout << "StringHash tests\n" << std::endl;
#ifdef TEST_BASE_FIND
    std::cout << "Testing addItem and findItem\n" << std::endl;
    StringHash baseFind;

    for (int i = 0; i < BASE_SIZE; i++)
    {
        baseFind.addItem(baseWords[i]);
    }
    std::cout << "Should find apple and not maple" << std::endl;
    std::cout << "apple" << (baseFind.findItem("apple")?" ":" not ") << "found" << std::endl;
    std::cout << "maple" << (baseFind.findItem("maple")?" ":" not ") << "found" << std::endl;
    
    std::cout << "\nDone testing addItem and findItem\n" << std::endl;
#endif // TEST_BASE_FIND
#ifdef TEST_BASE_REMOVE
    std::cout << "Testing addItem, findItem, and removeItem\n" << std::endl;
    StringHash baseRemove;

    for (int i = 0; i < BASE_SIZE; i++)
    {
        baseRemove.addItem(baseWords[i]);
    }
    std::cout << "Should find apple and then not find apple" << std::endl;
    std::cout << "apple" << (baseRemove.findItem("apple")?" ":" not ") << "found" << std::endl;
    baseRemove.removeItem("apple");
    std::cout << "apple" << (baseRemove.findItem("apple")?" ":" not ") << "found" << std::endl;
    
    std::cout << "\nDone testing addItem, findItem, and removeItem\n" << std::endl;
#endif // TEST_BASE_REMOVE
#ifdef TEST_BASE_DISPLAY
    std::cout << "Testing addItem, findItem, removeItem, and display\n" << std::endl;
    StringHash baseList;

    for (int i = 0; i < BASE_SIZE; i++)
    {
        baseList.addItem(baseWords[i]);
    }
    baseList.removeItem("apple");
    std::cout << "Should be _empty_ _empty_ _empty_ pine"
                << " pear peach _empty_ _deleted_ _empty_ _empty_ oak" << std::endl;
    std::cout << "The order might differ, but contents should not\n" << std::endl;
    std::cout << baseList.displayTable();
    
    std::cout << "\nDone testing addItem, findItem, removeItem, and display\n" << std::endl;
#endif // TEST_BASE_DISPLAY
#ifdef TEST_BASE_GROW
    std::cout << "Testing growing StringHash\n" << std::endl;
    const int BASE_EXTRA = 3;
    std::string baseExtraWords[BASE_EXTRA] = {"bear", "pony", "cow"};
    
    StringHash baseGrow;

    for (int i = 0; i < BASE_SIZE; i++)
    {
        baseGrow.addItem(baseWords[i]);
    }
    std::cout << "Should be _empty_ _empty_ _empty_ pine"
                << " pear peach _empty_ _apple_ _empty_ _empty_ oak" << std::endl;
    std::cout << "The order might differ, but contents should not\n" << std::endl;
    std::cout << baseGrow.displayTable();
    
    for (int i = 0; i < BASE_EXTRA; i++)
    {
        baseGrow.addItem(baseExtraWords[i]);
    }
    std::cout << "\nAfter growing the list should be " << std::endl;
    std::cout << "_empty_ _empty _empty_ pine pear cow _empty_ "
              << "_apple_ _empty_ _pony_ _empty_ _empty_ _empty_ _empty_"
              << "_empty_ _empty_ peach _empty_ _empty_ _empty_ bear oak" << std::endl;
    std::cout << "The order might differ, but contents should not\n" << std::endl;
    std::cout << baseGrow.displayTable();
    
    std::cout << "\nDone testing growing StringHash\n" << std::endl;
#endif // TEST_BASE_GROW
#endif // TEST_BASE

#ifdef TEST_ADV
    const int ADV_SIZE = 10;
    std::string advWords[ADV_SIZE] = {"dog", "cat", "ape", "cow", "frog", "fish", "goat", "bear", "deer", "elk"};
    
    std::cout << "\nChainedHash tests\n" << std::endl;
#ifdef TEST_ADV_FIND
    std::cout << "Testing addItem and findItem\n" << std::endl;
    ChainedHash advFind;

    for (int i = 0; i < ADV_SIZE; i++)
    {
        advFind.addItem(advWords[i]);
    }
    std::cout << "Should find goat and not horse" << std::endl;
    std::cout << "goat" << (advFind.findItem("goat")?" ":" not ") << "found" << std::endl;
    std::cout << "horse" << (advFind.findItem("horse")?" ":" not ") << "found" << std::endl;
    
    std::cout << "\nDone testing addItem and findItem\n" << std::endl;
#endif // TEST_ADV_FIND
    
#ifdef TEST_ADV_REMOVE
    std::cout << "Testing addItem, findItem, and removeItem\n" << std::endl;
    ChainedHash advRemove;

    for (int i = 0; i < ADV_SIZE; i++)
    {
        advRemove.addItem(advWords[i]);
    }
    std::cout << "Should find goat and then not find goat" << std::endl;
    std::cout << "goat" << (advRemove.findItem("goat")?" ":" not ") << "found" << std::endl;
    advRemove.removeItem("goat");
    std::cout << "goat" << (advRemove.findItem("goat")?" ":" not ") << "found" << std::endl;
    
    std::cout << "\nDone testing addItem, findItem, and removeItem\n" << std::endl;
#endif // TEST_ADV_REMOVE
    
#ifdef TEST_ADV_DISPLAY
    std::cout << "Testing addItem, findItem, removeItem, and display\n" << std::endl;
    ChainedHash advList;

    for (int i = 0; i < ADV_SIZE; i++)
    {
        advList.addItem(advWords[i]);
    }

    advList.removeItem("goat");
    std::cout << "Should be: \n_empty_\ndeer frog\nfish cow\n"
                << "goat\ndog\nbear\nelk ape cat" << std::endl;
    std::cout << "The order might differ, but contents should not\n" << std::endl;
    std::cout << advList.displayTable();
    
    std::cout << "\nDone testing addItem, findItem, removeItem, and display\n" << std::endl;
#endif // TEST_ADV_DISPLAY
    
#ifdef TEST_THINK
    std::cout << "Testing thinking problem (growing ChainedHash)\n" << std::endl;
    const int ADV_EXTRA = 6;
    std::string advExtraWords[ADV_EXTRA] = {"apple", "pine", "fir", "oak", "maple", "fig"};
    
    ChainedHash advGrow;

    for (int i = 0; i < ADV_SIZE; i++)
    {
        advGrow.addItem(advWords[i]);
    }
    for (int i = 0; i < ADV_EXTRA; i++)
    {
        advGrow.addItem(advExtraWords[i]);
    }
    std::cout << "\nAfter growing the list should have 13 rows " << std::endl;
    std::cout << "and include apple, pine, fir, oak, maple, fig, dog," << std::endl;
    std::cout << "cat, ape, cow, frog, fish, goat, bear, deer, elk \n" << std::endl;
    std::cout << advGrow.displayTable();
    
    std::cout << "\nDone testing growing StringHash\n" << std::endl;
#endif // TEST_THINK
#endif // TEST_ADV

    return 0;
}