#ifndef GRAPHM_H
#define GRAPHM_H
#include "nodedata.h"
#include <limits.h>
#include <iostream>
#include <fstream>

class GraphM {

// ------------------------------------------------GraphM.h -------------------------------------------------------
// CSS 343 B Au 23
// Created on 11/6/2023
// Last Modified on 11/6/2023
// Created by Vince Nguyen and Lok Yin Wong 
// --------------------------------------------------------------------------------------------------------------------
// This header file contains the class GraphM. The class has a function that reads a file to build a graph using adjacency
// matrix. Once the graph is builed, the user can use displayGraph and depth firstSearch to display the graph differently. 
// Furthermore, the user can also call findshortestpath to find all shortest path between two nodes.
// --------------------------------------------------------------------------------------------------------------------
// The class should be able to find the shoretest path between any two nodes and display the total wiehgt and the path correctly.
// --------------------------------------------------------------------------------------------------------------------

public:
    // Constructor
    GraphM(); // Default constructor

    // Functions
    void buildGraph(std::ifstream& file); // Build the graph from a file
    bool insertEdge(int, int, int); // Insert an edge between nodes with a weight
    bool removeEdge(int, int); // Remove an edge between nodes
    void findShortestPath(); // Find the shortest path in the graph
    void displayAll() const; // Display all nodes and their distances
    void display(const int, const int) const; // Display a specific path

private:
    struct TableType {
        bool visited; // Whether the node has been visited
        int dist; // Shortest distance from the source known so far
        int path; // Previous node in the path of minimum distance
    };

    static const int MAXNODES = 101;
    NodeData data[MAXNODES]; // Data for graph nodes
    int C[MAXNODES][MAXNODES]; // Cost array, the adjacency matrix
    int size; // Number of nodes in the graph
    TableType T[MAXNODES][MAXNODES]; // Stores visited, distance, path

    void printPathHelper(int, int) const; // Helper function to print the path
    void printValueHelper(int, int) const; // Helper function to print values of nodes
};

#endif