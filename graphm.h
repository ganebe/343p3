#ifndef GRAPHM_H
#define GRAPHM_H
#include "nodedata.h"
#include <limits.h>
#include <iostream>
#include <fstream>

class GraphM{

public:
//constructors and destructor
GraphM();
//functions
void buildGraph(ifstream& file);
bool insertEdge(int, int, int);
bool removeEdge(int, int);
void findShortestPath();
void displayAll() const;
void display(const int, const int) const;
private:

    struct TableType {
        bool visited; // whether node has been visited
        int dist; // shortest distance from source known so far
        int path; // previous node in path of min dist
        };
    static const int MAXNODES = 101;
    NodeData data[MAXNODES]; // data for graph nodes
    int C[MAXNODES][MAXNODES]; // Cost array, the adjacency matrix
    int size; // number of nodes in the graph
    TableType T[MAXNODES][MAXNODES]; // stores visited, distance, path
    void printPathHelper(int, int) const;
    void printValueHelper(int, int) const;
};

#endif