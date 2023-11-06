
#ifndef GRAPHL_H
#define GRAPHL_H
#include "nodedata.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;



class GraphL{

public:
GraphL();
~GraphL();

void buildGraph(ifstream &);
void displayGraph();
void depthFirstSearch();

private:
static const int MAXNODES = 101;
struct EdgeNode {
    int adjGraphNode; // subscript of the adjacent graph node
    EdgeNode* nextEdge;
};

struct GraphNode { // structs used for simplicity, use classes if desired
    EdgeNode* edgeHead; // head of the list of edges
    NodeData* data; // data information about each node
    bool visited;
};

GraphNode* arr_;
int number_of_edge_node_;
void makeEmpty();
void makeEmptyHelper(EdgeNode *&);
void depthFirstSearchHelper(GraphNode &, int);
};

#endif