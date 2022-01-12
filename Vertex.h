#pragma once
#include <list>
#include "Edge.h"

using namespace std;

class Edge;
class Vertex {
private:
    int number;
    int color;  
public:
    list<Edge*> adj;
    list<Edge*> inp;
    Vertex(int num) {
        number = num;
        color = -1;
    }
    void SetColor(int newColor) { color = newColor; }
    int GetColor() { return color; }
    int GetNumber() { return number; }
    list<Edge*> GetAdjacent() { return adj; }
    void pushBackAdj(Edge* edge) { adj.push_back(edge); }
    void pushBackInp(Edge* edge) { inp.push_back(edge); }
};