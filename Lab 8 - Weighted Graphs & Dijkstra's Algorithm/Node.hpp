//
// Created by admin on 5/29/2021.
//

#ifndef LAB_8___WEIGHTED_GRAPHS___DIJKSTRA_S_ALGORITHM_NODE_HPP
#define LAB_8___WEIGHTED_GRAPHS___DIJKSTRA_S_ALGORITHM_NODE_HPP

#include "Edge.hpp"

class Node {
public:
	char value;
	bool visited = false;
	Edge *edge = nullptr;

	Node(char value);
};


#endif //LAB_8___WEIGHTED_GRAPHS___DIJKSTRA_S_ALGORITHM_NODE_HPP
