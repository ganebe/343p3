
#ifndef GRAPHL_H
#define GRAPHL_H
#include "nodedata.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


// ------------------------------------------------GraphL.h -------------------------------------------------------
// CSS 343 B Au 23
// Created on 11/6/2023
// Last Modified on 11/6/2023
// Created by Vince Nguyen and Lok Yin Wong 
// --------------------------------------------------------------------------------------------------------------------
// This header file contains the class GraphL. The class has a function that reads a file to build a graph using adjacency
// list. Once the graph is builed, the user can use displayGraph and depth firstSearch to display the graph differently. 
// --------------------------------------------------------------------------------------------------------------------
// The class should be able to build and display the graph from a file that has correct format and vaild input
// --------------------------------------------------------------------------------------------------------------------


class GraphL{

public:
//constructors and destructor
GraphL();   //deafult constructor to initialize all variables
~GraphL();  //destructor to free memroy that was used

//class functions
void buildGraph(ifstream &);    //builds a graph using the information provided in the file
void displayGraph();            //display the graph alphabetically
void depthFirstSearch();        //display the order of dfs result of the graph

private:
static const int MAXNODES = 101;    //Maxmium of nodes this class can handles
struct EdgeNode {
    int adjGraphNode; // subscript of the adjacent graph node
    EdgeNode* nextEdge; //pointer to the next edge node
};

struct GraphNode { // structs used for simplicity
    EdgeNode* edgeHead; // head of the list of edges
    NodeData* data; // data information about each node
    bool visited;
};

GraphNode* arr_;    //array that contains all the GraphNode
int number_of_graph_node_; //number of nodes in the graph
//helper functions
void makeEmpty();   //reset the graph and free memeory
void makeEmptyHelper(EdgeNode *&);  //helper for makeEmpty()
void depthFirstSearchHelper(GraphNode &, int);  //helper for dfs
};

#endif