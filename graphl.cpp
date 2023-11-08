#include "graphl.h"

// ------------------------------------------------GraphL.cpp -------------------------------------------------------
// CSS 343 B Au 23
// Created on 11/6/2023
// Last Modified on 11/6/2023
// Created by Vince Nguyen and Lok Yin Wong 
// --------------------------------------------------------------------------------------------------------------------
// This file has the implementation of the different methods and functions from the header file. The methods and functions
// that have helper functions will be above each other to know that they are together. This class assumes the input file is 
// correctly formatted with valid data. When the input file is correctly formatted with valid data, this class
// should be able to build, display, and dfs the graph.
// --------------------------------------------------------------------------------------------------------------------
// The class should be able to build and display the graph from a file that has correct format and vaild input
// --------------------------------------------------------------------------------------------------------------------



//------------------------- GraphL ---------------------------------
// Default constructor to initialize variables and allocated memory for the graph nodes
//-------------------------------------------------------------------------

GraphL::GraphL(){
    arr_ = new GraphNode[MAXNODES];     //allocated memory for graph nodes
    for(int i = 1; i < MAXNODES; i++){  //clear garabage for all graph nodes in the array(expect 0)
        arr_[i].edgeHead = NULL;        //point edgeHead to null
        arr_[i].visited = false;        //set visted to false
        arr_[i].data = NULL;            //point data(name) to null
    }
    number_of_graph_node_ = 0;          //set the current number of graph node to zero
}

//------------------------- GraphL ---------------------------------
// Destructor to free all memory allocated
//-------------------------------------------------------------------------

GraphL::~GraphL(){
    makeEmpty();    //free the memory that was used for the edges
    delete [] arr_; //free the memory for the graph nodes
    arr_ = NULL;    //set arr_ to NULl to make sure it will not be used again
}

//------------------------- buildGraph ---------------------------------
// Stores the graph information that provided in the file,
// this function assume the file has correct format and vaild data
//-------------------------------------------------------------------------
void GraphL::buildGraph(ifstream & in_file)
{
    int pervious_number_of_graph = number_of_graph_node_;    //stores the pervious number of graph node


    number_of_graph_node_ = 0;  //set the current number of graph to zero

    
    in_file >> number_of_graph_node_;   //get the first int from the file

    if(number_of_graph_node_ <= 0){ //if file can't be open, empty file or the first int is 0
        number_of_graph_node_ = pervious_number_of_graph;   //set the number of graph nodes back to its pervious state
        makeEmpty();    //free the memory for the edge nodes and set all graph nodes to the initla states
        return; //exit this function
    }
    //need to test this
    if(number_of_graph_node_ > 100){    //if the first int from the file is >= 100
        number_of_graph_node_ = pervious_number_of_graph;   //set the number of graph nodes back to its pervious state
        cout << "build graph failed, The maximum edge node is 100" << endl; //tell the user why the graph didn't get build
        makeEmpty();    //free the memory for the edge nodes and set all graph nodes to the initla states
        return; //exit this function

    }


    if(pervious_number_of_graph > 0 ){  //other wise, we clear the graph nodes if we stored a graph before
        int temp = number_of_graph_node_;   //stores the current number of graph nodes
        number_of_graph_node_ = pervious_number_of_graph;   //set the number of graph nodes used back to pervious states to aid make empty function
        makeEmpty();   //free the memory for the edge nodes and set all graph nodes to the initla states
        number_of_graph_node_ = temp; // set the number of graph nodes to the first int from the file
    }
    
    char* node_name = new char[50]; //allocated memeory for a char array
    in_file.getline(node_name,50); // skip the blank after the line that states the number of nodes it contains
    for(int i = 1; i <= number_of_graph_node_; i ++){   //loop throught all the graph nodes we will use
        if(in_file.eof()){  //if file reached the end
            cout << "the input file doesn't have the data in correct format" << endl;   //states there is something wrong with the file format or data
        }
        in_file.getline(node_name,50);  //other wise, get the line for the node name with 50 character max

        arr_[i].data = new NodeData(node_name); //set the graph node's name to the name from the file
    }

    delete [] node_name; //free the memory for the character array
    int first, second;  //variables for the two int from the file
    bool all_zero = false;  //bool that check if we reached the end(0) of the file
    while(!all_zero){ // while we haven't finish the graph

        in_file >> first >> second; //get the next two ints from the file

        if(first == 0){ //if the first int is 0
            all_zero = true;    //end the while loop
            break;
        }

        EdgeNode * temp = arr_[first].edgeHead;     //point temp to the from node's edge head
        bool is_duplicated = false; //bool to check if we already that edge
        while(temp != NULL && is_duplicated == false){  //while temp is not null and we didn't find a duplicated
            if(temp == NULL){ // skip if temp is null

            }else if(temp->adjGraphNode == second){ //if we find a duplicated
                is_duplicated = true;   //we set the bool that check if there is a duplicated to true
            }

            temp = temp->nextEdge;  //move to next edge
        }

        if(is_duplicated == true){  //skip the insertion when there is a duplicated edge

        }else{
            temp = arr_[first].edgeHead;    //point temp to the edgehead of the graph node
            arr_[first].edgeHead = new EdgeNode;    //create a new edgenode
            arr_[first].edgeHead->nextEdge = temp;  //points the nextedge to the pervious edgehead
            arr_[first].edgeHead->adjGraphNode = second;    //set the edgenode value to the second int from the file
        }
    }


}

//------------------------- makeEmpty ---------------------------------
// free the memeory that was used for the graph name and the edge nodes
//-------------------------------------------------------------------------

void GraphL::makeEmpty(){
    for(int i = 1; i <= number_of_graph_node_; i++){    //for each graph node that was used
        if(arr_[i].edgeHead != NULL){   //if the edge head is not null
            makeEmptyHelper(arr_[i].edgeHead); //call a helper to free the memory the edge nodes
        }
        if(arr_[i].data != NULL){ //if the node name is not null
            delete arr_[i].data;  //free memory for the node node
            arr_[i].data = NULL;
        }
        arr_[i].visited = false; //set visted to flase
    }

    number_of_graph_node_ = 0; // set the number of graph node this graph has to zero
}

//------------------------- makeEmptyHelper ---------------------------------
// helper of makeEmpty, to free the memory for edge nodes
//-------------------------------------------------------------------------

void GraphL::makeEmptyHelper(EdgeNode *& delete_node){
    if(delete_node == NULL){    //do nothing if the edge node is null
        return;
    }
    makeEmptyHelper(delete_node->nextEdge);//call the helper to free the memeory of the next edge node
    delete_node->nextEdge = NULL; // set the pointer to the next edge node to null
    delete delete_node;// free the memeory of the current node
    delete_node = NULL; // point the current node to null

}

//------------------------- depthFirstSearch ---------------------------------
// print out the result of the dfs on the current graph
//-------------------------------------------------------------------------
void GraphL::depthFirstSearch()
{
    cout << "Depth-first ordering: ";
    for(int i = 1; i <= number_of_graph_node_; i ++){ // for each graph node on the graph
        if(arr_[i].visited == true){   //skip if it is visted
            
        }else{
            depthFirstSearchHelper(arr_[i], i); //call the helper to do dfs
        }
    }
    for(int i = 1; i <= number_of_graph_node_; i++){ //reset the visted for all graph nodes,so we can do dfs again if needed
        arr_[i].visited = false; 
    }
    cout << endl; // print an extra line
}

//------------------------- depthFirstSearchHelper ---------------------------------
// Helper for dfs
//-------------------------------------------------------------------------

void GraphL::depthFirstSearchHelper(GraphNode &  current_node, int node_number){
    cout << node_number << " "; 
    current_node.visited = true; // set the current node visited to true
    EdgeNode * temp = current_node.edgeHead; // point temp to current node edge node
    while(temp != NULL){ // while temp is not null
        if(arr_[temp->adjGraphNode].visited == false){ // if the adjgraphnode inside temp is not visted
            depthFirstSearchHelper(arr_[temp->adjGraphNode],temp->adjGraphNode); // we call dfs helper to visit it and print it
        }
        temp = temp->nextEdge; // point temp to the next edge node
    }
}

//------------------------- DisplayGraph ---------------------------------
// display the graph by it's values, with their name and edege that they have
//-------------------------------------------------------------------------
void GraphL::displayGraph()
{
    cout << "Graph: " << endl;
    for(int i = 1; i <= number_of_graph_node_; i++){ // for each graph node
        cout << "Node " << i << "     ";
        if(arr_[i].data != NULL){
            cout << *arr_[i].data << endl << endl; //print out the graph node name
        }
        if(arr_[i].edgeHead != NULL){ // if the graph node have any edges
            EdgeNode* temp = arr_[i].edgeHead; // set temp to point to the edge head
            while(temp != NULL){ // while temp is not null
                cout << "edge  " << i << " " << temp->adjGraphNode << endl; // print the edge
                temp = temp->nextEdge; // set temp to the next edge
            }
        }
    }
    cout << endl; // adds an extra line
}
