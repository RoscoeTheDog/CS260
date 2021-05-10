//
//  main.cpp
//  getNext_search_tree
//
//  Created by Jim Bailey on 4/25/20.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//

#include <iostream>
#include "Tree.hpp"

// basic lab requirements
#define TEST_INSERT_INORDER
//#define TEST_FIND
//#define TEST_DELETE
//// advanced lab requirements
//#define TEST_FIND_LARGER
//#define TEST_DELETE_LARGER

int main()
{

#ifdef TEST_INSERT_INORDER
	Tree fir;
	int int_values[]=  {16, 8, 24, 4, 12, 20, 28, 2, 6, 10, 14, 18, 22, 26, 30};
	const int NUM_EVENS = 15;

	std::cout << std::endl << "Testing insertValue and inOrder traversal " << std::endl;

	// build a nice noble fir that is balanced
	std::cout << " Insert and display 15 even integers " << std::endl;
	for(int i = 0; i < NUM_EVENS; i++)
		fir.insertValue(int_values[i]);

	// display the tree, should be even integers in order
	std::cout << " InOrder expected 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30" << std::endl;
	std::cout << "  and it is " << fir.inOrder() << std::endl;
	std::cout << " PreOrder expected 16 8 4 2 6 12 10 14 24 20 18 22 28 26 30" << std::endl;
	std::cout << "  and it is " << fir.preOrder() << std::endl;
	std::cout << " PostOrder expected 2 6 4 10 14 12 8 18 22 20 26 30 28 24 16" << std::endl;
	std::cout << "  and it is " << fir.postOrder() << std::endl;

	std::cout << "\nEnd test insertValue and displayTree\n" << std::endl;

#endif //TEST_INSERT_INORDER

#ifdef TEST_FIND
	Tree oak;
	int primes[]=  {19, 11, 29, 5, 3, 7, 13, 17, 23, 31, 37};
	const int NUM_PRIMES = 11;

	std::cout << std::endl << "Testing findValue " << std::endl;

	// build a nice prime oak
	std::cout << " Insert and display 11 primes " << std::endl;
	for(int i = 0; i < NUM_PRIMES; i++)
		oak.insertValue(primes[i]);

	std::cout << "  " << oak.inOrder() << std::endl;

	// check find
	std::cout << std::endl << " Should find 5 and 23, not find 21 or 2: " << std::endl;
	std::cout << "  Looking for 5 " << (oak.findValue(5)?"found":"not found") << std::endl;
	std::cout << "  Looking for 23 " << (oak.findValue(23)?"found":"not found") << std::endl;
	std::cout << "  Looking for 21 " << (oak.findValue(21)?"found":"not found") << std::endl;
	std::cout << "  Looking for 2 " << (oak.findValue(2)?"found":"not found") << std::endl;

	std::cout << "\nEnd of test findValue\n" << std::endl;

#endif //TEST_FIND

#ifdef TEST_DELETE
	Tree plum;
	int odds[]=  {15, 7, 23, 3, 11, 19, 27, 1, 5, 9, 13, 17, 21, 25, 29};
	const int NUM_ODDS = 15;

	std::cout << std::endl << "Testing deleteValue " << std::endl;

	// build a nice odd plum
	std::cout << " Insert and display 15 odd integers " << std::endl;
	for(int i = 0; i < NUM_ODDS; i++)
		plum.insertValue(odds[i]);

	std::cout << "  " << plum.inOrder() << std::endl;

	// delete23 and see if still there
	std::cout << std::endl << " Now testing delete, 23 should be there and then gone" << std::endl;
	std::cout << "  Looking for 23 " << (plum.findValue(23)?"found":"not found") << std::endl;
	plum.removeValue(23);
	std::cout << "  Looking for 23 " << (plum.findValue(23)?"found":"not found") << std::endl;
	// Now add 23 back
	std::cout << std::endl << " Now seeing if adding 23 back works" << std::endl;
	plum.insertValue(23);
	std::cout << "  Looking for 23 " << (plum.findValue(23)?"found":"not found") << std::endl;



	std::cout << "\nEnd of test deleteValue \n" << std::endl;

#endif //TEST_DELETE

#ifdef TEST_FIND_LARGER
	Tree apple;
	int nums[]=  {30, 15, 45, 7, 23, 3, 10, 18, 24, 36, 52, 33, 40, 48, 64};
	const int NUM_NUMS = 15;
	std::cout << std::endl << "Testing findLarger " << std::endl;

	// build a nice random apple
	std::cout << " Insert and display 15 integers " << std::endl;
	for(int i = 0; i < NUM_NUMS; i++)
		apple.insertValue(nums[i]);



	std::cout << "\n Values in order for findLarger test" << std::endl;
	std::cout << "  " << apple.inOrder() << std::endl;
	std::cout << "\n Now testing findLarger" << std::endl;
	std::cout << "  1 should return 3 and returns " << apple.findLarger(1) << std::endl;
	std::cout << "  4 should return 7 and returns " << apple.findLarger(4) << std::endl;
	std::cout << "  9 should return 10 and returns " << apple.findLarger(9) << std::endl;
	std::cout << "  12 should return 15 and returns " << apple.findLarger(12) << std::endl;
	std::cout << "  16 should return 18 and returns " << apple.findLarger(16) << std::endl;
	std::cout << "  30 should return 30 and returns " << apple.findLarger(30) << std::endl;
	std::cout << "  34 should return 36 and returns " << apple.findLarger(34) << std::endl;
	std::cout << "  40 should return 40 and returns " << apple.findLarger(40) << std::endl;
	std::cout << "  43 should return 45 and returns " << apple.findLarger(43) << std::endl;
	std::cout << "  47 should return 48 and returns " << apple.findLarger(47) << std::endl;
	std::cout << "  62 should return 64 and returns " << apple.findLarger(62) << std::endl;
	std::cout << "  90 should return -1 and returns " << apple.findLarger(90) << std::endl;

	std::cout << "\nEnd of testing findLarger\n" << std::endl;

#endif //TEST_FIND_LARGER

#ifdef TEST_DELETE_LARGER
	Tree pear;
	int vals[]=  {15, 8, 24, 4, 11, 19, 30, 2, 7, 10, 13, 16, 22, 28, 34};
	const int NUM_VALS = 15;

	std::cout << std::endl << "Testing deleteLarger " << std::endl;

	// build a nice random apple
	std::cout << " Insert and display 15 integers " << std::endl;
	for(int i = 0; i < NUM_VALS; i++)
		pear.insertValue(vals[i]);
	std::cout << "\nStarting values for deleteLarger" << std::endl;
	std::cout << "  " << pear.inOrder() << std::endl;
	std::cout << "\n Now testing deleteLarger" << std::endl;
	std::cout << "  5 should return 7 and returns " << pear.deleteLarger(5) << std::endl;
	std::cout << "   7 should be gone and is " << (pear.findValue(7)?"found":"not found") << std::endl;
	std::cout << "  19 should return 19 and returns " << pear.deleteLarger(19) << std::endl;
	std::cout << "   19 should be gone and is " << (pear.findValue(19)?"found":"not found") << std::endl;
	std::cout << "\nSame as above values, but without 7 and 19 " << std::endl;
	std::cout << " " << pear.inOrder() << std::endl;

	std::cout << "\nEnd of testing deleteLarger\n" << std::endl;
#endif //TEST_DELETE_LARGER

	return 0;
}