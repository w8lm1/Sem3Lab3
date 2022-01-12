#include "pch.h"
#include "gtest/gtest.h"
#include "../Lab3Main/Graph.h"
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;
TEST(Single, Vertex) {

	Vertex* vert = new Vertex(3);

	ASSERT_EQ(vert->GetNumber(), 3);
	ASSERT_EQ(vert->GetColor(), -1);
	vert->SetColor(1);
	ASSERT_EQ(vert->GetColor(), 1);

	delete vert;
}

TEST(Single, Edge) {

	Vertex* first = new Vertex(3);
	Vertex* second = new Vertex(5);

	Edge* edge = new Edge(first, second, 7);

	ASSERT_EQ(edge->GetFirst()->GetNumber(), 3);
	ASSERT_EQ(edge->GetSecond()->GetNumber(), 5);
	edge->GetSecond()->SetColor(1);
	ASSERT_EQ(edge->GetSecond()->GetColor(), 1);
	ASSERT_EQ(edge->GetWeight(), 7);
	edge->SetWeight(2);
	ASSERT_EQ(edge->GetWeight(), 2);

	delete edge;
	delete first;
	delete second;
}

TEST(Both, EdgeNVertex) {

	Vertex* first = new Vertex(1);
	Vertex* second = new Vertex(2);
	Vertex* third = new Vertex(3);
	Vertex* fourth = new Vertex(4);
	Vertex* fifth = new Vertex(5);

	Edge* edge13 = new Edge(first, third, 4);
	Edge* edge31 = new Edge(third, first, 4);
	Edge* edge21 = new Edge(second, first, 4);
	Edge* edge45 = new Edge(fourth, fifth, 4);

	first->pushBackAdj(edge13);
	third->pushBackAdj(edge31);
	second->pushBackAdj(edge21);
	fourth->pushBackAdj(edge45);

	third->pushBackInp(edge13);
	first->pushBackInp(edge31);
	first->pushBackInp(edge21);
	fifth->pushBackInp(edge45);

	ASSERT_EQ(second->GetAdjacent().back()->GetSecond()->GetNumber(), 1);
	fifth->SetColor(17);
	ASSERT_EQ(fourth->GetAdjacent().back()->GetSecond()->GetColor(), 17);
	ASSERT_EQ(first->GetAdjacent().back()->GetSecond()->GetNumber(), 3);
	ASSERT_EQ(third->GetAdjacent().back()->GetSecond()->GetNumber(), 1);

	delete edge13;
	delete edge31;
	delete edge21;
	delete edge45;
	delete first;
	delete second;
	delete third;
	delete fourth;
	delete fifth;
}

TEST(Graph, EdgeNVertex) {

	Vertex* first = new Vertex(1);
	Vertex* second = new Vertex(2);
	Vertex* third = new Vertex(3);
	Vertex* fourth = new Vertex(4);
	Vertex* fifth = new Vertex(5);

	Edge* edge13 = new Edge(first, third, 4);
	Edge* edge31 = new Edge(third, first, 4);
	Edge* edge21 = new Edge(second, first, 4);
	Edge* edge45 = new Edge(fourth, fifth, 4);

	first->pushBackAdj(edge13);
	third->pushBackAdj(edge31);
	second->pushBackAdj(edge21);
	fourth->pushBackAdj(edge45);

	third->pushBackInp(edge13);
	first->pushBackInp(edge31);
	first->pushBackInp(edge21);
	fifth->pushBackInp(edge45);

	vector<Vertex*> verts;

	verts.push_back(first);
	verts.push_back(second);
	verts.push_back(third);
	verts.push_back(fourth);
	verts.push_back(fifth);

	Graph* graph = new Graph(verts);


	ASSERT_EQ(graph->GetVertex(2)->GetNumber(), 2);
	ASSERT_EQ(graph->GetEdge(3, 1)->GetSecond()->GetNumber(), 1);
	ASSERT_EQ(graph->GetEdge(1, 3)->GetSecond()->GetNumber(), 3);
	ASSERT_EQ(graph->GetEdge(5, 4), nullptr);
	ASSERT_EQ(graph->GetVertex(6), nullptr);

	graph->AddVertex();
	ASSERT_EQ(graph->GetVertex(6)->GetNumber(), 6);

	
	ASSERT_EQ(graph->AddVertex(15), 0);
	ASSERT_EQ(graph->GetVertex(15)->GetNumber(), 15);
	ASSERT_EQ(graph->AddVertex(15), 1);
	ASSERT_EQ(graph->GetVertex(15)->GetNumber(), 15);

	Vertex* seventh = new Vertex(7);
	Vertex* _seventh = new Vertex(7);
	ASSERT_EQ(graph->AddVertex(seventh), 0);
	ASSERT_EQ(graph->GetVertex(7)->GetNumber(), 7);
	ASSERT_EQ(graph->AddVertex(_seventh), 1);
	ASSERT_EQ(graph->GetVertex(7)->GetNumber(), 7);

	Edge* edge27 = new Edge(second, seventh, 4);
	ASSERT_EQ(graph->AddEdge(edge27), 0);
	ASSERT_EQ(graph->GetEdge(2, 7)->GetSecond()->GetNumber(), 7);

	ASSERT_EQ(graph->DeleteEdge(5, 4), 1);
	ASSERT_EQ(graph->DeleteEdge(5, 444), 2);
	ASSERT_EQ(graph->DeleteEdge(444, 5), 2);
	
	ASSERT_EQ(graph->DeleteEdge(4, 5), 0);
	ASSERT_EQ(graph->GetEdge(4, 5), nullptr);



	ASSERT_EQ(graph->DeleteVertex(7), 0);
	ASSERT_EQ(graph->DeleteVertex(7), 1);
	ASSERT_EQ(graph->DeleteVertex(3123), 1);
	ASSERT_EQ(graph->DeleteVertex(3), 0);
	ASSERT_EQ(graph->DeleteVertex(3), 1);
	ASSERT_EQ(graph->GetVertex(1)->adj.size(), 0);
	ASSERT_EQ(graph->GetEdge(3, 1), nullptr);
	ASSERT_EQ(graph->GetEdge(1, 3), nullptr);
	ASSERT_EQ(graph->DeleteVertex(1), 0);

	graph->Coloring();
		
	delete _seventh;
	delete graph;
}

TEST(Graph, VectorConstructor) {
	vector<vector<int>> gra = { {0, 0, 0, 1}, { 0, 0, 1, 1}, {0, 1, 0, 1}, {1, 1, 1, 0} };
	Graph* graph = new Graph(gra);

	ASSERT_EQ(graph->verts[0]->adj.size(), 1);
	ASSERT_EQ(graph->verts[0]->inp.size(), 1);
	ASSERT_EQ(graph->verts[1]->adj.size(), 2);
	ASSERT_EQ(graph->verts[1]->inp.size(), 2);
	ASSERT_EQ(graph->verts[2]->adj.size(), 2);
	ASSERT_EQ(graph->verts[2]->inp.size(), 2);
	ASSERT_EQ(graph->verts[3]->adj.size(), 3);
	ASSERT_EQ(graph->verts[3]->inp.size(), 3);
	graph->Coloring();


	delete graph;
}