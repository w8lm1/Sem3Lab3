#include <iostream>
#include <stdlib.h>
#include <crtdbg.h>
#include <ctime>
#include <set>
#include "Interface.h"

using namespace std;

GraphWrapper::~GraphWrapper() {
    delete graph;
}
GraphWrapper::GraphWrapper(int vertsCount, int edgeCount) {
    GenerateGraph(vertsCount, edgeCount);
}

int GraphWrapper::GenInt() {
    return rand();
}
double GraphWrapper::GenDouble() {
    return (double)rand() / (((double)(rand()) / 100) + 1);
}

double GraphWrapper::GetColorTime() {
    return colorTime;
}
int GraphWrapper::OutputGraph() {
    if (graph == nullptr || graph->verts.size() < 0)
        return 1;
    
    cout << "\ndigraph G {" << endl;
    for (vector<Vertex*>::iterator vi = graph->verts.begin(); vi != graph->verts.end(); vi++) {
        if ((*vi)->adj.size() == 0) {
            cout << "\"" << (*vi)->GetNumber() << "\";" << endl;
        }
        else {
            for (list<Edge*>::iterator ei = (*vi)->adj.begin(); ei != (*vi)->adj.end(); ei++) {
                cout << "\"" << (*vi)->GetNumber() << "\" -> \"" << (*ei)->GetSecond()->GetNumber() <<
                    "\"[label = " << (*ei)->GetWeight() << " ];" << endl;
            }
        }
    }

    cout << "}" << endl;
    return 0;
}
int GraphWrapper::ColorGraph() {
    if (graph != nullptr) {
        int t0 = clock();
        graph->Coloring();
        int t1 = clock();
        colorTime = t1 - t0;
        return 0;
    }
    else
        return 1;
}
int GraphWrapper::OutputColorGraph() {
    if (graph == nullptr || graph->verts.size() < 0)
        return 1;

    ColorGraph();

    cout << "\ndigraph G {" << endl;
    for (vector<Vertex*>::iterator vi = graph->verts.begin(); vi != graph->verts.end(); vi++) {
        if ((*vi)->adj.size() == 0) {
            cout << "\"" << (*vi)->GetNumber() << " : " << (*vi)->GetColor() << "\";" << endl;
        }
        else {
            for (list<Edge*>::iterator ei = (*vi)->adj.begin(); ei != (*vi)->adj.end(); ei++) {
                cout << "\"" << (*vi)->GetNumber() << " : " << (*vi)->GetColor() << 
                    "\" -> \"" << (*ei)->GetSecond()->GetNumber() << " : " << (*ei)->GetSecond()->GetColor() <<
                    "\"[label = " << (*ei)->GetWeight() << " ];" << endl;
            }
        }
    }

    cout << "}" << endl;
    return 0;
}

int GraphWrapper::AddVertex(int num) {
    if (graph != nullptr) {
        int res = graph->AddVertex(num);
        return res;
    }
    else
        return 2;   
}
int GraphWrapper::AddEdge(int num1, int num2, int weight) {
    if (graph != nullptr) {
        int res = graph->AddEdge(num1, num2, weight);
        return res;
    }
    else
        return 3;   
}
int GraphWrapper::RemoveVertex(int num) {
    if (graph != nullptr) {
        int res = graph->DeleteVertex(num);
        return res;
    }
    else
        return 2;   
}
int GraphWrapper::RemoveEdge(int num1, int num2) {
    if (graph != nullptr) {
        int res = graph->DeleteEdge(num1, num2);
        return res;
    }
    else
        return 2;   
}

void GraphWrapper::GenerateGraph(int vertsCount, int edgeCount) {
    vector<Vertex*> verts;
    set<int> helpSet;
    if (edgeCount > vertsCount * vertsCount) edgeCount = vertsCount * vertsCount;

    for (int i = 0; i < vertsCount; i++) {
        Vertex* vert = new Vertex(i);
        verts.push_back(vert);
        helpSet.insert(i);
    }

    graph = new Graph(verts);

    int tmpVert = 0;
    int startPoint = rand() % helpSet.size();

    while (edgeCount > 0) {
        if (tmpVert >= vertsCount) {
            tmpVert = 0;
            helpSet.erase(helpSet.find(startPoint));
            int pos = rand() % helpSet.size();

            int a = 0;
            for (auto si = helpSet.begin(); si != helpSet.end(); si++) {
                if (a == pos) {
                    startPoint = (*si);
                    break;
                }
                a++;
            }
        }

        graph->AddEdge(startPoint, tmpVert, rand() % 100);
        tmpVert++;
        edgeCount--;
    }
}



void Console::OutCharMessage(string msg, bool isMoved) {
    cout << msg << " ";
    if (isMoved) cout << endl;
}
int Console::IntInMessage(int min, int max, int ErrorMesNum) {
    int result;

    do {
        cin >> result;
        if (!cin.good()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            this->OutCharMessage(this->GetString(21), true);
        }
        else if (result > max || result < min)
            this->OutCharMessage(this->GetString(ErrorMesNum), true);
        else
            break;
    } while (true);

    return result;
}
string Console::GetString(int index) {
    return this->messages[index];
}
void Console::ClearTester() {
    delete buffer;
    buffer = nullptr;
}

int Console::PickOption() {
    OutCharMessage(GetString(10), true);
    int in = IntInMessage(0, 8, 9);
    if (in == 0) {
        ClearTester();
        OutCharMessage(GetString(15), true);
        return 0;
    }
    else return in;
}
int Console::SetVertexCount() {
    OutCharMessage(GetString(26), true);
    return IntInMessage(0, INT_MAX, 9);
}
int Console::SetEdgesCount() {
    OutCharMessage(GetString(27), true);
    return IntInMessage(0, INT_MAX, 9);
}
void Console::OutputMenu(int first, int last) {
    for (int i = first; i <= last; i++)
        OutCharMessage(GetString(i), true);
}

int Console::OutputColorTime(GraphWrapper* GW) {
    int sortTime = -1;

    if(GW != nullptr) sortTime = GW->GetColorTime();
    else {
        OutCharMessage(GetString(12), true);
        return 0;
    }

    if (sortTime != -1) {
        OutCharMessage(GetString(14), false);
        cout << sortTime << endl;
        return 0;
    }
    else
    {
        OutCharMessage(GetString(13), true);
        return 1;
    }
}
int Console::OutputGraph(GraphWrapper* GW) {
    int res;
    if (GW != nullptr) res = GW->OutputGraph();
    else {
        OutCharMessage(GetString(12), true);
        return 0;
    }

    if (res == 0) {
        return 0;
    }
    else
    {
        OutCharMessage(GetString(12), true);
        return 1;
    }
}
int Console::OutputColorGraph(GraphWrapper* GW) {
    int res;
    if (GW != nullptr) res = GW->OutputColorGraph();
    else {
        OutCharMessage(GetString(12), true);
        return 0;
    }

    if (res == 0) {
        return 0;
    }
    else
    {
        OutCharMessage(GetString(12), true);
        return 1;
    }
}

int Console::AddVertex(GraphWrapper* GW) {
    if (GW == nullptr) {
        OutCharMessage(GetString(12), true);
        return 0;
    }

    OutCharMessage(GetString(17), true);
    int num = IntInMessage(0, INT_MAX, 9);

    int res = GW->AddVertex(num);

    if(res == 2)
        OutCharMessage(GetString(12), true);
    else if(res == 1)
        OutCharMessage(GetString(23), true);
    else if(res == 0)
        OutCharMessage(GetString(22), true);
    return 0;
}
int Console::AddEdge(GraphWrapper* GW) {
    if (GW == nullptr) {
        OutCharMessage(GetString(12), true);
        return 0;
    }

    OutCharMessage(GetString(18), true);
    int num1 = IntInMessage(0, INT_MAX, 9);
    OutCharMessage(GetString(19), true);
    int num2 = IntInMessage(0, INT_MAX, 9);
    OutCharMessage(GetString(20), true);
    int weight = IntInMessage(0, INT_MAX, 9);

    int res = GW->AddEdge(num1, num2, weight);

    if (res == 3)
        OutCharMessage(GetString(12), true);
    else if (res == 2)
        OutCharMessage(GetString(25), true);
    else if (res == 1)
        OutCharMessage(GetString(28), true);
    else if (res == 0)
        OutCharMessage(GetString(24), true);
    return 0;
}
int Console::DeleteVertex(GraphWrapper* GW) {
    if (GW == nullptr) {
        OutCharMessage(GetString(12), true);
        return 0;
    }

    OutCharMessage(GetString(17), true);
    int num = IntInMessage(0, INT_MAX, 9);

    int res = GW->RemoveVertex(num);

    if (res == 2)
        OutCharMessage(GetString(12), true);
    else if (res == 1)
        OutCharMessage(GetString(28), true);
    else if (res == 0)
        OutCharMessage(GetString(30), true);
    return 0;
}
int Console::DeleteEdge(GraphWrapper* GW) {
    if (GW == nullptr) {
        OutCharMessage(GetString(12), true);
        return 0;
    }

    OutCharMessage(GetString(18), true);
    int num1 = IntInMessage(0, INT_MAX, 9);
    OutCharMessage(GetString(19), true);
    int num2 = IntInMessage(0, INT_MAX, 9);

    int res = GW->RemoveEdge(num1, num2);

    if (res == 2)
        OutCharMessage(GetString(12), true);
    else if (res == 1)
        OutCharMessage(GetString(29), true);
    else if (res == 0)
        OutCharMessage(GetString(31), true);
    return 0;
}

int Console::ProcessOption(int opt) {
    int pickedOption, count, res1, res2;
    switch (opt) {
    case 9: {
        OutputMenu(0, 8);
        pickedOption = PickOption();
        return pickedOption;
        break;
    }
    case 1: {
        ClearTester();

        int verts = SetVertexCount();
        int edges = SetEdgesCount();

        buffer = new GraphWrapper(verts, edges);

        OutCharMessage(GetString(16), true);

        OutputMenu(0, 8);
        pickedOption = PickOption();
        return pickedOption;
        break;
    }
    case 2: {
        OutputGraph(buffer);

        OutputMenu(0, 8);
        pickedOption = PickOption();
        return pickedOption;
        break;
    }
    case 3: {
        AddVertex(buffer);

        OutputMenu(0, 8);
        pickedOption = PickOption();
        return pickedOption;
        break;
    }
    case 4: {
        AddEdge(buffer);

        OutputMenu(0, 8);
        pickedOption = PickOption();
        return pickedOption;
        break;
    }
    case 5: {
        DeleteVertex(buffer);

        OutputMenu(0, 8);
        pickedOption = PickOption();
        return pickedOption;
        break;
    }
    case 6: {
        DeleteEdge(buffer);

        OutputMenu(0, 8);
        pickedOption = PickOption();
        return pickedOption;
        break;
    }
    case 7: {
        OutputColorGraph(buffer);

        OutputMenu(0, 8);
        pickedOption = PickOption();
        return pickedOption;
        break;
    }
    case 8: {
        OutputColorTime(buffer);

        OutputMenu(0, 8);
        pickedOption = PickOption();
        return pickedOption;
        break;
    }
    default: {
        OutputMenu(0, 8);
        pickedOption = PickOption();
        return pickedOption;
        break;
    }
    }
}




int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    srand(time(nullptr));
    Console* console = new Console();

    int option = 9;

    while (option) {
        option = console->ProcessOption(option);
    }

    delete console;

    return 0;
}