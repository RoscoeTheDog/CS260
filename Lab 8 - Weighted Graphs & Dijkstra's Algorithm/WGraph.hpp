//
// Created by admin on 5/29/2021.
//

#ifndef LAB_8___WEIGHTED_GRAPHS___DIJKSTRA_S_ALGORITHM_WGRAPH_HPP
#define LAB_8___WEIGHTED_GRAPHS___DIJKSTRA_S_ALGORITHM_WGRAPH_HPP

#include "DGraph.hpp"
#include <queue>

class WGraph : public DGraph {

protected:
	int *distance = nullptr;
	Edge **PQ = nullptr;
	int numEdges;
	int PQSize;
	int PQLength;

public:

	WGraph () {
		distance = new int[this->SIZE];
		numEdges = 0;
		// set PQ size to max num of vertices. This may need to be extended later.
		PQSize = this->SIZE;
		PQLength = 0;
		PQ = new Edge*[PQSize];
	}

	void PQPush(Edge *e);

	void PQExtend(int size);

	bool addWEdge(char vertex_start, char vertex_end, int weight);

	std::string minCostTree(char vertex);

	bool PQisEmpty();

	Edge* PQPop();
};


#endif //LAB_8___WEIGHTED_GRAPHS___DIJKSTRA_S_ALGORITHM_WGRAPH_HPP
