#include "graphm.h"

GraphM::GraphM()
{
    size = 0;
    for (int i = 1; i < MAXNODES; i++)
    {
        for (int j = 1; j < MAXNODES; j++)
        {
            C[i][j] = std::numeric_limits<int>::max();
            T[i][j].visited = false;
            T[i][j].dist = std::numeric_limits<int>::max();
            T[i][j].path = 0;
        }
    }
}

void GraphM::buildGraph(ifstream &file)
{
   file >> size;
   char* name = new char[50];
   file.getline(name, 50);

   for (int i = 1; i <= size; i++)
   {
        data[i].setData(file);
   }

   int fromEdge, toEdge, weight;

   while(file >> fromEdge >> toEdge >> weight)
   {
        if(fromEdge == 0)
        {
            break;
        }

        C[fromEdge][toEdge] = weight;
   }
}

bool GraphM::insertEdge(int fromEdge, int toEdge, int weight)
{
    if (fromEdge < 1 || fromEdge > size)
    {
        return false;
    }

    if (toEdge < 1 || toEdge > size)
    {
        return false;
    }

    if (fromEdge == toEdge && weight != 0)
    {
        return false;
    }

    if (weight < 0)
    {
        return false;
    }

    C[fromEdge][toEdge] = weight;
    return true;
}

bool GraphM::removeEdge(int fromEdge, int toEdge)
{
    if (fromEdge < 1 || fromEdge > size)
    {
        return false;
    }

    if (toEdge < 1 || toEdge > size)
    {
        return false;
    }

    C[fromEdge][toEdge] = std::numeric_limits<int>::max();
    return true;
}

void GraphM::findShortestPath()
{
    for (int source = 1; source <= size; source++)
    {
        T[source][source].dist = 0;
        T[source][source].visited = true;

        for (int node = 1; node <= size; node++)
        {
            if (C[source][node] != std::numeric_limits<int>::max())
            {
                T[source][node].dist = C[source][node];
                T[source][node].path = source;
            }
        }

        for (int j = 1; j <= size - 1; j++)
        {
            int v = 1;
            int minDistance = std::numeric_limits<int>::max();

            for (int i = 1; i <= size; i++)
            {
                if ((T[source][i].visited == false && T[source][i].dist < minDistance))
                {
                    v = i;
                    minDistance = T[source][i].dist;
                }
            }

            T[source][v].visited = true;

            for(int w = 1; w <= size; w++)
            {
                if(T[source][w].visited == false)
                {
                    if(C[v][w] == std::numeric_limits<int>::max())
                    {
                        continue;
                    }
                    if(T[source][v].dist + C[v][w] < T[source][w].dist)
                    {
                        T[source][w].dist = T[source][v].dist + C[v][w];
                        T[source][w].path = v;
                    }
                }
            }
        }
    }
}

void GraphM::displayAll()
{
    cout << "Description            From node     To node     Dijkstra's Path" << endl;
    for(int i = 1 ; i <= size; i++){
        cout << data[i] << endl;
        for(int j = 1; j <= size; j++){
            if(i == j ){
                
            }else{
                cout << "                                      ";
                cout << i << "       " << j << "      ";
                if(T[i][j].dist == std::numeric_limits<int>::max()){
                    cout << "---" << endl;
                }    
                else{
                    cout << T[i][j].dist << "    "; 
                    //printValueHelper(i, j);
                    printPathHelper(i, j);
                    cout << endl;
                }
            }
        }

    }
}

void GraphM::display(int fromEdge, int toEdge)
{
    cout << "       " << fromEdge << "         " << toEdge;

    if (fromEdge < 1 || fromEdge > size || toEdge < 1 || toEdge > size)
    {
        cout << "           " << "-----" << endl;
    }
    if (T[fromEdge][toEdge].dist != std::numeric_limits<int>::max())
    {
        cout << "           " << T[fromEdge][toEdge].dist << "               ";
        printPathHelper(fromEdge,toEdge);
        printValueHelper(fromEdge,toEdge);
        
    }
    else
    {
        cout << "           " << "-----" << endl;
    }
}

void GraphM::printPathHelper(int fromEdge, int toEdge)
{
    if (T[fromEdge][toEdge].dist == std::numeric_limits<int>::max())
    {
        return;
    }

    if (fromEdge == toEdge)
    {
        cout << toEdge;
        return;
    }

    int path = toEdge;
    printPathHelper(fromEdge, toEdge = T[fromEdge][toEdge].path);
    cout << path << " ";
}

void GraphM::printValueHelper(int fromEdge, int toEdge)
{
    if (T[fromEdge][toEdge].dist == std::numeric_limits<int>::max())
    {
        return;
    }

    if (fromEdge == toEdge)
    {
        cout << data[toEdge];
        return;
    }
    int value = toEdge;
    printValueHelper(fromEdge, toEdge = T[fromEdge][toEdge].path);
    cout << data[value];
}
