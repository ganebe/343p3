#include "graphm.h"

// ------------------------------------------------GraphM.cpp -------------------------------------------------------
// CSS 343 B Au 23
// Created on 11/6/2023
// Last Modified on 11/6/2023
// Created by Vince Nguyen and Lok Yin Wong 
// --------------------------------------------------------------------------------------------------------------------
// This file has the implementation of the different methods and functions from the header file. The methods and functions
// that have helper functions will be above each other to know that they are together. This class assumes the input file is 
// correctly formatted with valid data. When the input file is correctly formatted with valid data, this class
// should be able to build, display, and find the shortest path between any two nodes.
// --------------------------------------------------------------------------------------------------------------------
// The class should be able to find the shoretest path between any two nodes and display the total wiehgt and the path correctly.
// --------------------------------------------------------------------------------------------------------------------

//------------------------- GraphM ---------------------------------
// Default constructor to initialize variables and set the adjacency matrix
//-------------------------------------------------------------------------

GraphM::GraphM(){
    size = 0;  // Initialize the number of nodes in the graph to zero
    for (int i = 1; i < MAXNODES; i++){
        for (int j = 1; j < MAXNODES; j++){
            C[i][j] = INT_MAX; // Set the cost array elements to INT_MAX
            T[i][j].visited = false; // Set the visited flag to false
            T[i][j].dist = INT_MAX; // Set the distance to INT_MAX
            T[i][j].path = 0; // Set the path to 0
        }
    }
}

//------------------------- buildGraph ---------------------------------
// Reads data from the input file to build the graph represented by this class.
//-------------------------------------------------------------------------

void GraphM::buildGraph(std::ifstream &file)
{
   file >> size; // Read the number of nodes in the graph
   char* name = new char[50]; // Allocate memory for a character array to hold node names

   file.getline(name, 50); // Consume the newline character

   for (int i = 1; i <= size; i++)
   {
        data[i].setData(file); // Read and set data for each node in the graph
   }

   delete [] name; // Deallocate the character array

   int fromEdge, toEdge, weight;

   while(file >> fromEdge >> toEdge >> weight)
   {
        if(fromEdge == 0)
        {
            break; // Exit the loop if the source node is 0
        }

        C[fromEdge][toEdge] = weight; // Set the edge weight in the adjacency matrix
   }
}



//------------------------- insertEdge ---------------------------------
// Inserts an edge between two nodes with the specified weight.
//-------------------------------------------------------------------------

bool GraphM::insertEdge(int fromEdge, int toEdge, int weight)
{
    if (fromEdge < 1 || fromEdge > size)
    {
        return false; // Invalid source node, cannot insert the edge
    }

    if (toEdge < 1 || toEdge > size)
    {
        return false; // Invalid target node, cannot insert the edge
    }

    if (fromEdge == toEdge && weight != 0)
    {
        return false; // Self-loop with non-zero weight is not allowed
    }

    if (weight < 0)
    {
        return false; // Negative weight is not allowed
    }

    C[fromEdge][toEdge] = weight; // Set the edge weight in the adjacency matrix
    return true; // Edge successfully inserted
}



//------------------------- removeEdge ---------------------------------
// Removes an edge between two nodes by setting the edge weight to INT_MAX.
//-------------------------------------------------------------------------

bool GraphM::removeEdge(int fromEdge, int toEdge)
{
    if (fromEdge < 1 || fromEdge > size)
    {
        return false; // Invalid source node, cannot remove the edge
    }

    if (toEdge < 1 || toEdge > size)
    {
        return false; // Invalid target node, cannot remove the edge
    }

    C[fromEdge][toEdge] = INT_MAX; // Set the edge weight to INT_MAX to remove the edge
    return true; // Edge successfully removed
}


//------------------------- findShortestPath ---------------------------------
// Finds the shortest path from each node to all other nodes in the graph using
// Dijkstra's algorithm. The result is stored in the TableType T.
//-------------------------------------------------------------------------

void GraphM::findShortestPath()
{
    // Loop through each node as the source
    for (int source = 1; source <= size; source++)
    {
        // Initialize the distance and visited status for the source node
        T[source][source].dist = 0;
        T[source][source].visited = true;

        // Initialize distances and paths for direct edges from the source
        for (int node = 1; node <= size; node++)
        {
            if (C[source][node] != INT_MAX)
            {
                T[source][node].dist = C[source][node];
                T[source][node].path = source;
            }
        }

        // Perform Dijkstra's algorithm to find the shortest paths
        for (int j = 1; j <= size - 1; j++)
        {
            int v = 0;
            int minDistance = INT_MAX;

            // Find the unvisited node with the shortest distance
            for (int i = 1; i <= size; i++)
            {
                if (T[source][i].visited == false && T[source][i].dist < minDistance)
                {
                    v = i;
                    minDistance = T[source][i].dist;
                }
            }

            if (v == 0)
            {
                break; // No unvisited nodes with finite distances
            }

            T[source][v].visited = true;

            // Update distances and paths to neighboring nodes
            for(int w = 1; w <= size; w++)
            {
                if (T[source][w].visited == false)
                {
                    if (C[v][w] == INT_MAX)
                    {
                        continue; // Skip unreachable nodes
                    }
                    if (T[source][v].dist + C[v][w] < T[source][w].dist)
                    {
                        T[source][w].dist = T[source][v].dist + C[v][w];
                        T[source][w].path = v;
                    }
                }
            }
        }
    }
}

//------------------------- displayAll ---------------------------------
// Displays information about all nodes in the graph and their shortest paths
// as computed by Dijkstra's algorithm.
//-------------------------------------------------------------------------

void GraphM::displayAll() const
{
    cout << "Description            From node     To node     Dijkstra's       Path" << endl;

    // Iterate through all nodes in the graph
    for (int i = 1; i <= size; i++)
    {
        cout << data[i] << endl;    //print the node name

        for (int j = 1; j <= size; j++)
        {
            if (i == j)
            {
                // Skip the diagonal (same node to itself)
            }
            else
            {
                cout << "                           ";
                cout << i << "            " << j << "           "; //print from node and to node
                
                if (T[i][j].dist == INT_MAX)
                {
                    cout << "---" << endl; // No path exists between nodes
                }
                else
                {
                    cout << T[i][j].dist << "              "; // print shortest distance
                    printPathHelper(i, j); // Print the shortest path
                    cout << endl;
                }
            }
        }
    }
}

//------------------------- display ---------------------------------
// Displays information about the shortest path from one node to another
// in the graph, as computed by Dijkstra's algorithm.
//-------------------------------------------------------------------------

void GraphM::display(int fromEdge, int toEdge) const
{
    if (fromEdge > size || fromEdge < 1 || toEdge > size || toEdge < 1) 
    {
        // Nodes are out of range, or one of them doesn't exist
        cout << "       " << fromEdge << "         " << toEdge << "           " << "----" << endl;
    } 
    else 
    {
        cout << "       " << fromEdge <<  "         " << toEdge << "           ";

        if (T[fromEdge][toEdge].dist != INT_MAX) 
        {
            // Shortest path exists between the nodes
            cout << T[fromEdge][toEdge].dist << "               ";
            printPathHelper(fromEdge, toEdge); // Print the shortest path
            cout << endl;
            printValueHelper(fromEdge, toEdge); // Print the path with node name
        } 
        else 
        {
            // No path exists between the nodes
            cout << "----" << endl;
        }
    }
    cout << endl;
}

//------------------------- printPathHelper ---------------------------------
// Hepler that Recursively prints the path from one node to another, as computed by
// Dijkstra's algorithm, using the TableType T.
//-------------------------------------------------------------------------

void GraphM::printPathHelper(int fromEdge, int toEdge) const
{
    if (T[fromEdge][toEdge].dist == INT_MAX)
    {
        return; // No path exists between the nodes
    }

    if (fromEdge == toEdge)
    {
        cout << toEdge << " "; // Print the node itself when source and target are the same
        return;
    }

    int path = toEdge;
    int previousEdge = T[fromEdge][toEdge].path;
    printPathHelper(fromEdge, previousEdge); // Recursively print the path
    cout << path << " ";
}

//------------------------- printValueHelper ---------------------------------
// Helper that Recursively prints the node name along the path from one node to another,
// as computed by Dijkstra's algorithm, using the TableType T.
//-------------------------------------------------------------------------

void GraphM::printValueHelper(int fromEdge, int toEdge) const
{
    if (T[fromEdge][toEdge].dist == INT_MAX)
    {
        return; // No path exists between the nodes
    }

    if (fromEdge == toEdge)
    {
        cout << data[toEdge] << endl; // Print the value of the target node when source and target are the same
        return;
    }

    int value = toEdge;
    int previousEdge = T[fromEdge][toEdge].path;
    printValueHelper(fromEdge, previousEdge); // Recursively print the values along the path
    cout << data[value] << endl << endl;    // prints the node name
}