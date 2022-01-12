#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <vector>
#include <list>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

class Graph {
public:
    vector<Vertex*> verts;
    Graph(vector<Vertex*> _verts) {
        verts = _verts;
    }
    Graph(vector<vector<int>> _graph) {
        int size = _graph.size();

        for (int i = 0; i < size; i++) {
            verts.push_back(new Vertex(i));
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (_graph[i][j] > 0) {
                    Edge* edge = new Edge(verts[i], verts[j], _graph[i][j]);
                    verts[i]->adj.push_back(edge);
                    verts[j]->inp.push_back(edge);
                }
            }
        }
    }
    ~Graph() {
        for (vector<Vertex*>::iterator vi = verts.begin(); vi != verts.end();) {
            for (list<Edge*>::iterator ei = (*vi)->adj.begin(); ei != (*vi)->adj.end();) {
                Edge* tmp = (*ei);
                ei = (*vi)->adj.erase(ei);
                tmp->GetSecond()->inp.remove(tmp);
                delete tmp;
            }

            for (list<Edge*>::iterator ei = (*vi)->inp.begin(); ei != (*vi)->inp.end();) {
                Edge* tmp = (*ei);
                ei = (*vi)->inp.erase(ei);
                tmp->GetFirst()->adj.remove(tmp);
                delete tmp;
            }

            Vertex* vert = (*vi);
            vi = verts.erase(vi);
            delete vert;
        }
    }


    void AddVertex() {
        verts.push_back(new Vertex(verts.back()->GetNumber() + 1));
    }
    int AddVertex(int num) {
        if (GetVertex(num) == nullptr) {
            verts.push_back(new Vertex(num));
            return 0;
        }
        else
            return 1;
    }
    int AddVertex(Vertex* vertex) {
        if (GetVertex(vertex->GetNumber()) == nullptr) {
            verts.push_back(vertex);
            return 0;
        }
        else
            return 1;
    }

    int DeleteVertex(int num) {
        for (vector<Vertex*>::iterator vi = verts.begin(); vi != verts.end(); vi++) {
            if ((*vi)->GetNumber() == num) {
                for (list<Edge*>::iterator ei = (*vi)->adj.begin(); ei != (*vi)->adj.end();) {
                    Edge* tmp = (*ei);
                    ei = (*vi)->adj.erase(ei);
                    tmp->GetSecond()->inp.remove(tmp);
                    delete tmp;
                }

                for (list<Edge*>::iterator ei = (*vi)->inp.begin(); ei != (*vi)->inp.end();) {
                    Edge* tmp = (*ei);
                    ei = (*vi)->inp.erase(ei);
                    tmp->GetFirst()->adj.remove(tmp);
                    delete tmp;
                }

                Vertex* vert = (*vi);
                vi = verts.erase(vi);
                delete vert;

                return 0;
            }
        }
        return 1;
    }
    int DeleteEdge(int num1, int num2) {
        Vertex* vert = GetVertex(num1);
        if (vert == nullptr || GetVertex(num2) == nullptr) return 2;  

        for (list<Edge*>::iterator ei = vert->adj.begin(); ei != vert->adj.end(); ei++) {
            if ((*ei)->GetSecond()->GetNumber() == num2) {
                Edge* tmp = (*ei);
                ei = vert->adj.erase(ei);
                tmp->GetSecond()->inp.remove(tmp);
                delete tmp;

                return 0;  
            }
        }
        return 1;  
    }

    int AddEdge(Edge* edge) {
        AddEdge(edge->GetFirst()->GetNumber(), edge->GetSecond()->GetNumber(), edge->GetWeight());
        delete edge;
        return 0;
    }
    int AddEdge(int num1, int num2, int _weight) {
        Vertex* first = nullptr;
        Vertex* second = nullptr;

        for (vector<Vertex*>::iterator vi = verts.begin(); vi != verts.end() && (first == nullptr || second == nullptr); vi++) {
            if ((*vi)->GetNumber() == num1) {
                first = (*vi);
                for (list<Edge*>::iterator ei = (*vi)->adj.begin(); ei != (*vi)->adj.end(); ei++) {
                    if ((*ei)->GetSecond()->GetNumber() == num2) {
                        return 2;
                    }
                }
            }
            if ((*vi)->GetNumber() == num2) {
                second = (*vi);
            }
        }

        if (first && second) {
            Edge* edge = new Edge(first, second, _weight);
            first->adj.push_back(edge);
            second->inp.push_back(edge);
            return 0;
        }
        else
            return 1;
    }

    Vertex* GetVertex(int num) {
        for (vector<Vertex*>::iterator vi = verts.begin(); vi != verts.end(); vi++) {
            if ((*vi)->GetNumber() == num) {
                return (*vi);
            }
        }
        return nullptr;
    }
    Edge* GetEdge(int num1, int num2) {
        for (vector<Vertex*>::iterator vi = verts.begin(); vi != verts.end(); vi++) {
            if ((*vi)->GetNumber() == num1) {
                for (list<Edge*>::iterator ei = (*vi)->adj.begin(); ei != (*vi)->adj.end(); ei++) {
                    if ((*ei)->GetSecond()->GetNumber() == num2) {
                        return (*ei);
                    }
                }
                return nullptr;
            }
        }
        return nullptr;
    }

    vector<Vertex*> GetNeighbours(Vertex* n) {
        vector<Vertex*> neighbours;

        for (vector<Vertex*>::iterator vi = verts.begin(); vi != verts.end(); vi++) {
            for (list<Edge*>::iterator ei = (*vi)->adj.begin(); ei != (*vi)->adj.end(); ei++) {
                if ((*ei)->GetFirst() == n) {
                    neighbours.push_back((*ei)->GetSecond());
                }
                else if ((*ei)->GetSecond() == n) {
                    neighbours.push_back((*ei)->GetFirst());
                }
            }
        }
        return neighbours;
    }

    void Coloring() {
        int maxColorAssign = 10;
        for (vector<Vertex*>::iterator vi = verts.begin(); vi < verts.end(); ++vi) {
            int futureColor = 0;
            vector<Vertex*> neighbours = GetNeighbours(*vi);

            for (vector<Vertex*>::iterator ni = neighbours.begin(); ni < neighbours.end(); ++ni) {
                if ((*ni)->GetColor() == futureColor) {
                    futureColor++;
                }
                else if (futureColor >= maxColorAssign) {
                    futureColor = -1;
                    break;
                }
            }

            (*vi)->SetColor(futureColor);
        }
    }
};