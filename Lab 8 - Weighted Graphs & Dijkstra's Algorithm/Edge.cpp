//
// Created by admin on 5/29/2021.
//

#include "Edge.hpp"

Edge::Edge(int startIndex, int endIndex) {
	this->startIndex = startIndex;
	this->endIndex = endIndex;
}

Edge::Edge(int startIndex, int endIndex, int weight) {
	this->startIndex = startIndex;
	this->endIndex = endIndex;
	this->weight = weight;
}
