#include "graphl.h"

GraphL::GraphL(){
    arr_ = new GraphNode[MAXNODES];
    for(int i = 1; i < MAXNODES; i++){
        arr_[i].edgeHead = NULL;
        arr_[i].visited = false;
        arr_[i].data = NULL;
    }
    number_of_edge_node_ = 0;
}

GraphL::~GraphL(){
    makeEmpty();
    delete arr_;
    arr_ = NULL;
}

void GraphL::buildGraph(ifstream & in_file)
{
    int pervious_number_of_edge = number_of_edge_node_;

    in_file >> number_of_edge_node_;

    if(number_of_edge_node_ <= 0){
        return;
    }

    if(number_of_edge_node_ > 100){
        cout << "The maximum edge node is 100" << endl;
        return;

    }

    if(pervious_number_of_edge > 0 ){
        makeEmpty();
    }
    
    char* node_name = new char[50];
    in_file.getline(node_name,50); // skip the blank after the line that states the number of nodes it contains
    for(int i = 1; i <= number_of_edge_node_; i ++){
        if(in_file.eof()){
            cout << "the input file doesn't have the data in correct format" << endl;
        }
        in_file.getline(node_name,50);

        arr_[i].data = new NodeData(node_name);
    }
    delete node_name;
    int first, second;
    bool all_zero = false;
    while(!all_zero){

        in_file >> first >> second;

        if(first == 0 && second == 0){
            all_zero = true;
            break;
        }

        if(first <= 0 || second <= 0){
            cout << "can't have node number that smaller than 0" << endl;
            break;
        }else if(first > number_of_edge_node_ || second > number_of_edge_node_) {
            cout << "can't have node number that greater that the total nodes" << endl;
            break;
        }else{
            EdgeNode * temp = arr_[first].edgeHead;
            arr_[first].edgeHead = new EdgeNode;
            arr_[first].edgeHead->nextEdge = temp;
            arr_[first].edgeHead->adjGraphNode = second;
        }
    }


}

void GraphL::makeEmpty(){
    for(int i = 1; i <= number_of_edge_node_; i++){
        if(arr_[i].edgeHead != NULL){
            makeEmptyHelper(arr_[i].edgeHead);
        }
        if(arr_[i].data != NULL){
            delete arr_[i].data;
            arr_[i].data = NULL;
        }
        arr_[i].visited = false;
    }

    number_of_edge_node_ = 0;
}

void GraphL::makeEmptyHelper(EdgeNode *& delete_node){
    if(delete_node == NULL){
        return;
    }
    makeEmptyHelper(delete_node->nextEdge);
    delete_node->nextEdge = NULL;
    delete delete_node;
    delete_node = NULL;

}

void GraphL::depthFirstSearch()
{
    cout << "Depth-first ordering: " << endl;
    for(int i = 1; i <= number_of_edge_node_; i ++){
        if(arr_[i].visited == true){
            //skip
        }else{
            depthFirstSearchHelper(arr_[i], i);
        }
    }
    for(int i = 1; i <= number_of_edge_node_; i++){
        arr_[i].visited = false;
    }
    cout << endl;
}

void GraphL::depthFirstSearchHelper(GraphNode &  current_node, int node_number){
    cout << node_number << " ";
    current_node.visited = true;
    EdgeNode * temp = current_node.edgeHead;
    while(temp != NULL){
        if(arr_[temp->adjGraphNode].visited == false){
            depthFirstSearchHelper(arr_[temp->adjGraphNode],temp->adjGraphNode);
        }
        temp = temp->nextEdge;
    }
}

void GraphL::displayGraph()
{
    cout << "Graph: " << endl;
    for(int i = 1; i <= number_of_edge_node_; i++){
        cout << "Node " << i << "     ";
        if(arr_[i].data != NULL){
            cout << *arr_[i].data << endl << endl;
        }
        if(arr_[i].edgeHead != NULL){
            EdgeNode* temp = arr_[i].edgeHead;
            while(temp != NULL){
                cout << "edge  " << i << " " << temp->adjGraphNode << endl;
                temp = temp->nextEdge;
            }
        }
    }
    cout << endl;
}
