//
// Created by admin on 5/29/2021.
//

#include "DGraph.hpp"

void DGraph::addNode(char val) {

	Node *n = new Node(val);
	graph[numVertices++] = n;
}

bool DGraph::addEdge(char vertex_start, char vertex_end) {

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

std::string DGraph::breadthFirst(char vertex) {

	std::string output;

	// reinitialize all visited values to false.
	for (int i = 0; i < numVertices; ++i) {
		visited[i] = false;
	}

	// get the index value of the starting vertex
	int index = findNode(vertex);
	// push the vertex onto the queue.
	FIFO.push_back(graph[index]);
	// flag the node as visited
	visited[index] = true;

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

int DGraph::findNode(const char c) {

	for (int i = 0; i < numVertices; ++i) {

		if (graph[i]->value == c) {
			return i;
		}
	}

	return -1;
}

std::string DGraph::connectTable() {

	bool *table = new bool[SIZE*SIZE];
	warshallsAlgorithm(table);

	return displayMatrix(table);
}

int DGraph::indexMatrix(int x, int y) {

	return x + numVertices * y;
}

std::string DGraph::displayMatrix(bool *table) {

	std::string s;

	if (!table) {
		table = adjMatrix;
	}

	// row y
	for (int i = 0; i < numVertices + 1; ++i) {

		if (!i) {
			s += "  ";
		}
		else {
			s += graph[i - 1]->value;
			s += " ";
		}

		// row x
		for (int k = 0; k < numVertices; ++k) {

			if (!i) {
				s += graph[k]->value;
				s += " ";
				continue;
			}

			int ind = indexMatrix(k, i - 1);
			s += std::to_string(table[ind]);
			s += " ";
		}
		s += "\n";
	}

	return s;
}

std::string DGraph::listNodes() {

	std::string s;

	for (int i = 0; i < numVertices; ++i) {
		s += graph[i]->value;
		s += " ";
	}

	return s;
}

std::string DGraph::displayEdges() {
	std::string s;
	Node *n = nullptr;

	for (int i = 0; i < numVertices; ++i) {

		n = graph[i];
		Edge *e = n->edge;

		while (e) {

			s += e->startIndex;
			s += "-";
			s += e->endIndex;
			s += " ";

			e = e->next;
		}

	}

	return s;
}

void DGraph::warshallsAlgorithm(bool *table) {

	memcpy(table, adjMatrix, SIZE*SIZE);

	// y
	for (int i = 0; i < numVertices; ++i) {

		// x
		for (int k = 0; k < numVertices; ++k) {

			// look for 1s in row (x)
			if (adjMatrix[indexMatrix(k, i)]){

				// consider row from the matched column value
				for (int l = 0; l < numVertices; ++l) {

					if (adjMatrix[indexMatrix(l, k)]) {
						table[indexMatrix(l, i)] = true;
					}

				}

			}
		}


	}

}