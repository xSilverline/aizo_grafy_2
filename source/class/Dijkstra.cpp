//
// Created by Silver on 05.06.2024.
//

#include "../headers/Dijkstra.h"


void Dijkstra::runOnMatrix(int ** graphMatrix, int v, int e, int start, int end)
{

}

void Dijkstra::runOnList(listElement ** graphList, int v, int e, int start, int end)
{
    int * cost = new int[v];
    int * prev = new int[v];
    bool * QS = new bool[v];
    auto *  next = new listElement;
    auto ** resultList = new listElement * [v];

    for(int i = 0; i<v; i++)
    {
        cost[i] = MAXINT;
        prev[i] = -1;
        resultList[i] = nullptr;
        QS[i] = false;

    }

    cost[start] = 0;
    int j,k;
    for(int i = 0; i<v; i++)
    {
        for(j = 0; QS[j];j++){}

        for(k = j++; j<v;j++)
        {
            if(!QS[j] && (cost[j] < cost[k]))
                k = j;
        }
        QS[k] = true;

        next = graphList[k];
        while(next)
        {
            if(!QS[next->v] && (cost[next->v] > cost[k]+next->wei))
            {
                cost[next->v] = cost[k]+next->wei;
                prev[next->v] = k;
            }
            next = next->next;
        }
    }

    for(int i = 0; i<v;i++)
    {
        for(j=i; j>=0; j=prev[j])
        {
            resultList[i] =
        }
    }




    delete [] cost;
    delete[] prev;
    delete [] QS;
    delete [] resultList;
}