//
// Created by admin on 5/29/2021.
//

#ifndef LAB_8___WEIGHTED_GRAPHS___DIJKSTRA_S_ALGORITHM_WGRAPH_HPP
#define LAB_8___WEIGHTED_GRAPHS___DIJKSTRA_S_ALGORITHM_WGRAPH_HPP

#include "DGraph.hpp"

class WGraph : public DGraph {

public:

	bool addWEdge(int startIndex, int endIndex, int weight);

	std::string minCostTree(char c);

};


#endif //LAB_8___WEIGHTED_GRAPHS___DIJKSTRA_S_ALGORITHM_WGRAPH_HPP
