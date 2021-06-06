//
// Created by admin on 5/29/2021.
//

#include "WGraph.hpp"

bool WGraph::addWEdge(int startIndex, int endIndex, int weight) {


	// guard against invalid edges
	if (vertex_start == vertex_end) {
		return false;
	}

	// return and save the position where the vertices are in the array
	int startIndex = findNode(vertex_start);
	int endIndex = findNode(vertex_end);

	// guard against invalid vertex entries.
	if (startIndex < 0 || endIndex < 0) {
		return false;
	}

	// update adjMatrix
	adjMatrix[indexMatrix(startIndex, endIndex)] = true;
	adjMatrix[indexMatrix(endIndex, startIndex)] = true;

	// create new edge at the from start node to end node
	Edge *e = new Edge(startIndex, endIndex);

	// insert if not exists
	if (!graph[startIndex]->edge) {
		graph[startIndex]->edge = e;
	}
		// push onto the head
	else {
		// get the starting head.
		Edge *head = graph[startIndex]->edge;
		// relink the links of Edges
		e->next = head;
		// now update next
		graph[startIndex]->edge = e;
	}

	return true;
}
