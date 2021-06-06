//
// Created by admin on 5/29/2021.
//

#ifndef LAB_8___WEIGHTED_GRAPHS___DIJKSTRA_S_ALGORITHM_EDGE_HPP
#define LAB_8___WEIGHTED_GRAPHS___DIJKSTRA_S_ALGORITHM_EDGE_HPP

#include <climits>

class Edge {
public:
	int startIndex = -1;
	int endIndex = -1;
	Edge* next = nullptr;
	int weight = INT_MAX;

	Edge(int startIndex, int endIndex);

	Edge(int startIndex, int endIndex, int weight);
};


#endif //LAB_8___WEIGHTED_GRAPHS___DIJKSTRA_S_ALGORITHM_EDGE_HPP
