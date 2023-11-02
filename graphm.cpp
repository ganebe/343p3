#include "graphm.h"

GraphM::GraphM()
{
    size = 0;
    for (int i = 1; i < MAXNODES; i++)
    {
        for (int j = 1; j < MAXNODES; j++)
        {
            C[i][j] = 0;
            T[i][j].visited = 0;
            T[i][j].dist = 0;
            T[i][j].path = 0;
        }
    }
}




