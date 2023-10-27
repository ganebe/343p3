#ifndef GRAPHM_H
#define GRAPHM_H
#include "nodedata.h"

const int MAXNODES = 100;


class GraphM{

public:

private:

    struct TableType {
        bool visited; // whether node has been visited
        int dist; // shortest distance from source known so far
        int path; // previous node in path of min dist
        };

    NodeData data[MAXNODES]; // data for graph nodes
    int C[MAXNODES][MAXNODES]; // Cost array, the adjacency matrix
    int size; // number of nodes in the graph
    TableType T[MAXNODES][MAXNODES]; // stores visited, distance, path
};

#endif