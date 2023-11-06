#include "graphl.h"
#include "iostream"
#include "fstream"
using namespace std;


int main(){
    GraphL g;
    ifstream in_file;
    in_file.open("test.txt");
    g.buildGraph(in_file);
    g.depthFirstSearch();
    g.displayGraph(); 
    in_file.close();
    in_file.open("data32.txt");
    g.buildGraph(in_file);
    g.depthFirstSearch();
    g.displayGraph(); 
    return 0;
}