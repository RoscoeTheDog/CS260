//
//  main.cpp
//  CS 260 Lab 8
//
//  Created by Jim Bailey on June 2, 2020.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//

#include <iostream>

#define TEST_CONNECT
//#define TEST_MINCOST

#ifdef TEST_CONNECT
#include "DGraph.hpp"
#endif

#ifdef TEST_MINCOST
#include "WGraph.hpp"
#endif

int main()
{
#ifdef TEST_CONNECT
	std::cout << "This test displays a connection table for a directed graph" << std::endl << std::endl;

	// create the graph
	DGraph tree1;

	//add nodes
	tree1.addNode('A');
	tree1.addNode('C');
	tree1.addNode('T');
	tree1.addNode('Z');
	tree1.addNode('X');
	tree1.addNode('K');
	tree1.addNode('Q');
	tree1.addNode('J');
	tree1.addNode('M');
	tree1.addNode('U');

	// add some edges
	tree1.addEdge('A', 'C');
	tree1.addEdge('A', 'T');
	tree1.addEdge('A', 'Z');
	tree1.addEdge('X', 'C');
	tree1.addEdge('C', 'X');
	tree1.addEdge('C', 'K');
	tree1.addEdge('T', 'Q');
	tree1.addEdge('K', 'Q');
	tree1.addEdge('Q', 'J');
	tree1.addEdge('J', 'M');
	tree1.addEdge('Z', 'X');
	tree1.addEdge('U', 'M');
	tree1.addEdge('K', 'X');

	std::cout << tree1.displayMatrix() << std::endl;

	// uncomment the next line to see your node list, edge list, and edge matrix
//#define Debug1
#ifdef Debug1
	std::cout << "The list of nodes is: " << std::endl;
    std::cout << tree1.listNodes() << std::endl << std::endl;
    
    std::cout << "The graph edgelist is: " << std::endl;
    std::cout << tree1.displayEdges() << std::endl << std::endl;
    
    std::cout << "The graph edge matrix is" << std::endl;
    std::cout << tree1.displayMatrix() << std::endl;
#endif // Debug1

	// If you wanted to do a depth first, uncomment out these lines
//	std::cout << "The depth first min graph from A should be: " << std::endl;
//	std::cout << " A-Z Z-X X-C C-K K-Q Q-J J-M A-T  with U unreachable" << std::endl;
//	std::cout << tree1.depthFirst('A') << std::endl << std::endl;

	std::cout << "The breadth first min graph from A should be: " << std::endl;
	std::cout << " A-Z A-T A-C Z-X T-Q C-K Q-J J-M  with U unreachable" << std::endl;
	std::cout << tree1.breadthFirst('A') << std::endl << std::endl;

	std::cout << "Note that the order of nodes in your output might differ" << std::endl;
	std::cout << "what is important which nodes are reached from each start" << std::endl;
	std::cout << "The graph connect table should be: " << std::endl;
	std::cout << "A: Z T C X Q K J M "<< std::endl;
	std::cout << "C: K X Q J M"<< std::endl;
	std::cout << "T: Q J M"<< std::endl;
	std::cout << "Z: X C K Q J M"<< std::endl;
	std::cout << "X: C K Q J M"<< std::endl;
	std::cout << "K: X Q C J M "<< std::endl;
	std::cout << "Q: J M"<< std::endl;
	std::cout << "J: M"<< std::endl;
	std::cout << "M:"<< std::endl;
	std::cout << "U: M "<< std::endl << std::endl;

	std::cout << "The graph connect table is: " << std::endl;
	std::cout << tree1.connectTable() << std::endl << std::endl;

	std::cout << "End of testing connection table" << std::endl << std::endl;
#endif

#ifdef TEST_MINCOST
	std::cout << "This test displays a minimum cost spanning graph for a weighted graph" << std::endl << std::endl;

	// create the graph
	WGraph tree2;

	// add nodes
	tree2.addNode('A');
	tree2.addNode('C');
	tree2.addNode('T');
	tree2.addNode('Z');
	tree2.addNode('X');
	tree2.addNode('K');
	tree2.addNode('Q');
	tree2.addNode('J');
	tree2.addNode('M');
	tree2.addNode('U');

	// add edges
	tree2.addWEdge('A', 'C', 3);
	tree2.addWEdge('A', 'T', 4);
	tree2.addWEdge('A', 'Z', 2);
	tree2.addWEdge('X', 'C', 4);
	tree2.addWEdge('C', 'K', 8);
	tree2.addWEdge('T', 'Q', 4);
	tree2.addWEdge('K', 'Q', 3);
	tree2.addWEdge('Q', 'J', 6);
	tree2.addWEdge('J', 'M', 5);
	tree2.addWEdge('Z', 'X', 6);

	// uncomment the next line to see your node list, edge list, and edge matrix
//#define Debug2
#ifdef Debug2
	std::cout << "The list of nodes is: " << std::endl;
    std::cout << tree2.listNodes() << std::endl << std::endl;
        
    std::cout << "The graph edgelist is: " << std::endl;
    std::cout << tree2.displayEdges() << std::endl << std::endl;
        
    std::cout << "The graph edge matrix is" << std::endl;
    std::cout << tree2.displayMatrix() << std::endl;
#endif // Debug1

	std::cout << "The min cost graph should be: " << std::endl;
	std::cout << "Q: Q-K Q-T T-A A-Z A-C C-X Q-J J-M " << std::endl;

	std::cout << "The min cost graph is: " << std::endl;
	std::cout << tree2.minCostTree('Q') << std::endl;

	std::cout << "Done with testing min cost spanning graph " << std::endl << std::endl;
#endif

	return 0;
}