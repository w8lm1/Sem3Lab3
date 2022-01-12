#pragma once

#include <vector>
#include <iostream>
#include "Graph.h"

using namespace std;

class GraphWrapper{
private:
	int colorTime;
	Graph* graph;

	int GenInt();
	double GenDouble();
public:
	~GraphWrapper();
	GraphWrapper(int vertsCount, int edgeCount);

	double GetColorTime();
	int ColorGraph();
	int AddVertex(int num);
	int AddEdge(int num1, int num2, int weight);
	int RemoveVertex(int num);
	int RemoveEdge(int num1, int num2);

	int OutputGraph();
	int OutputColorGraph();

	void GenerateGraph(int vertsCount, int edgeCount);
};


class Console {
private:
	GraphWrapper* buffer = nullptr;
	vector<string> messages = {
		"0) Exit",
		"1) Generate graph",
		"2) Output graph",
		"3) Add vertex",
		"4) Add edge",
		"5) Delete vertex",					//5
		"6) Delete edge",
		"7) Color graph",
		"8) Output coloring time",
		"Incorrect integer number",
		"Choose menu option",				//10
		"Set element count",
		"Generate graph first",
		"Color graph first",
		"Time elapsed for coloring is ",
		"Programm finished",				//15
		"Graph generated",
		"Enter vertex number",
		"Enter first vertex number",
		"Enter second vertex number",
		"Enter edge weight",				//20
		"Error - not integer number",
		"Vertex placed",
		"Vertex was already placed",
		"Edge placed",
		"Edge was already placed",			//25
		"Set vertex count",
		"Set edges count",
		"There was not such vertex",
		"There was not such edge",
		"Vertex removed",					//30
		"Edge removed",
	};

	void OutCharMessage(string msg, bool isMoved);
	int IntInMessage(int min, int max, int ErrorMesNum);

	void ClearTester();

public:
	
	string GetString(int index);
	int ProcessOption(int opt);

	void OutputMenu(int first, int last);

	int PickOption();
	int SetEdgesCount();
	int SetVertexCount();

	int OutputColorTime(GraphWrapper* GW);
	int OutputGraph(GraphWrapper* GW);
	int OutputColorGraph(GraphWrapper* GW);

	int AddVertex(GraphWrapper* GW);
	int AddEdge(GraphWrapper* GW);
	int DeleteVertex(GraphWrapper* GW);
	int DeleteEdge(GraphWrapper* GW);
};