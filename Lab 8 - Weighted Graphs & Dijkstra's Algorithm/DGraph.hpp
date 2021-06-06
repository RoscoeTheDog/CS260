//
// Created by admin on 5/29/2021.
//

#ifndef LAB_8___WEIGHTED_GRAPHS___DIJKSTRA_S_ALGORITHM_DGRAPH_HPP
#define LAB_8___WEIGHTED_GRAPHS___DIJKSTRA_S_ALGORITHM_DGRAPH_HPP

#include <set>
#include <deque>
#include <string>
#include "Node.hpp"
#include <stdexcept>
#include <iostream>

class DGraph {

protected:
	int SIZE = 20;
	int numVertices;
	std::deque<Node *> FIFO;
	std::deque<Node *> STACK;
	Node **graph;
	bool *visited;
	// solution to 2d arrays:
	// https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
	bool *adjMatrix;
	bool *connectivityTable;

	int findNode(char c);

	// helper function that returns an index for a flattened 2d matrix
	int indexMatrix(int x, int y);

public:

	DGraph() {
		this->numVertices = 0;
		graph = new Node*[SIZE]{nullptr};
		visited = new bool[SIZE]{false};
		adjMatrix = new bool[SIZE*SIZE];
		connectivityTable = new bool[SIZE*SIZE];


		for (int i = 0; i < SIZE*SIZE; ++i) {
			adjMatrix[i] = false;
			connectivityTable[i] = false;
		}

	}

	void addNode(char val);

	bool addEdge(char vertex_1, char vertex_2);

	std::string breadthFirst(char val);

	void depthFirst(char val);

	std::string listNodes();

	std::string displayEdges();

	std::string displayMatrix(bool *table = nullptr);

	void warshallsAlgorithm(bool *table);

	// Once the class is working properly,
	// create a new method named connectTable that returns a string.
	// This method should show what nodes can be reached from node in turn.
	std::string connectTable();

};


#endif //LAB_8___WEIGHTED_GRAPHS___DIJKSTRA_S_ALGORITHM_DGRAPH_HPP
