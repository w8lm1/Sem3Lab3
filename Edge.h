#pragma once
#include "Vertex.h"

class Vertex;
class Edge {
private:
    int weight;
    Vertex* first;
    Vertex* second;
public:
	Edge(Vertex* _first, Vertex* _second, int _weight) {
		first = _first;
		second = _second;
		weight = _weight;
	}

	~Edge() {
		first = nullptr;
		second = nullptr;
	}
	int GetWeight() { return weight; }
	Vertex* GetFirst() { return first; }
	Vertex* GetSecond() { return second; }

	void SetWeight(int _weight) { weight = _weight; }
};