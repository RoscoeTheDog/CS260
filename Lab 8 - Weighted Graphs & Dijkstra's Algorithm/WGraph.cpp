//
// Created by admin on 5/29/2021.
//

#include "WGraph.hpp"

bool WGraph::addWEdge(char vertex_start, char vertex_end, int weight) {

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

	// pre-increment num edges
	numEdges++;

	// extend PQ size if needed.
	if (numEdges > PQSize) {
		PQExtend(numEdges * 2);
	}

	// update member adjMatrix
	adjMatrix[indexMatrix(startIndex, endIndex)] = true;
	adjMatrix[indexMatrix(endIndex, startIndex)] = true;

	// create new edge at the from start node to end node
	Edge *e = new Edge(startIndex, endIndex, weight);

	// attach edge to node if not exist
	if (!graph[startIndex]->edge) {
		graph[startIndex]->edge = e;
	}
		// push to head of Node's edge list if already exists.
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

std::string WGraph::minCostTree(char vertex) {

	std::string output;
	Edge *adjEdges;

	// reinitialize all visited values to false.
	for (int i = 0; i < numVertices; ++i) {
		visited[i] = false;
	}

	// get the index value of the starting vertex
	int index = findNode(vertex);
	// flag the node as visited
	visited[index] = true;

	// check for edges
	if (graph[index]->edge){
		adjEdges = graph[index]->edge;
	}
	// throw if none
	else {
		throw std::out_of_range("This vertex does not have any adjacent vertices");
	}

	// add all edges to PQ
	while (adjEdges) {
		PQPush(adjEdges);
		adjEdges = adjEdges->next;
	}


	while (!PQisEmpty()) {

	}



	while (!FIFO.empty()) {
		// pop off front
		Node *n = FIFO.front();
		FIFO.pop_front();

		// check neighboring edges for the target vertex.
		Edge *e = n->edge;
		while (e) {

			if (!visited[e->endIndex]) {
				output += graph[e->startIndex]->value;
				output += "-";
				output += graph[e->endIndex]->value;
				output += " ";

				FIFO.push_back(graph[e->endIndex]);
				visited[e->endIndex] = true;
			}

			e = e->next;
		}

	}

	return output;
}


void WGraph::PQPush(Edge *e) {

	// flag to see if found after linear search.
	bool found = false;

	// search through all edges in the PQ.
	for (int i = 0; i < this->numEdges; ++i) {

		// see if there is already an edge in the PQ
		// which ends at the same node as the starting edge to be inserted
		if (graph[PQ[i]->endIndex] == graph[e->startIndex]) {

			found = true;

			// compare the weights of the two edges if found and keep the smaller
			if (e->weight > PQ[i]->weight) {
				PQ[i] = e;  // replace if new is smaller weight.
			}

		}

	}

	// if there are no other edge in the priority queue with this ending node,
	// then add the new edge to the priority queue.
	if (!found) {
		// pre increment
		PQLength++;
		// check if PQ needs extended
		if (PQLength > PQSize) {
			PQExtend(PQSize * 2);
		}
		// insert
		PQ[PQLength] = e;
	}

}

void WGraph::PQExtend(int size) {
	// create new extended array.
	Edge **__new = new Edge *[size];

	// deep copy
	for (int i = 0; i < numEdges; ++i) {
		__new[i] = PQ[i];
	}

	// update PQ size
	this->PQSize = size;

	// cleanup and re-assign
	delete PQ;
	PQ = __new;
}

Edge *WGraph::PQPop() {
	return PQ[PQLength--];
}

bool WGraph::PQisEmpty() {
	return PQLength <= 0;
}