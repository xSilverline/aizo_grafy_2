//
// Created by Silver on 04.06.2024.
//

#include <iostream>
#include <iomanip>
#include "../headers/PrimMST.h"
#include "../headers/PriorityQueue.h"

using namespace std;




void PrimMST::runOnMatrix(int ** graphMatrix,int v,int e)
{
    int ** mstMatrix;

    PriorityQueue priorityQueue(e);
    int visited[v];
    int sumVisit = 0;
    int sumWeight=0;
    mstMatrix = new int * [v];


    for(int i = 0; i < v; i++)
    {
        mstMatrix[i] = new int [e];
        for(int j = 0; j<e;j++)
        {
            mstMatrix[i][j] = 0;
        }
        visited[i] = 0;
    }

    visited[0] = 1;
    sumVisit++;
    int n = 0;
    int i = 0;



      while(sumVisit<v)
       {
          Edge edge;
           for(int j = 0; j<e;j++)
           {
               if(graphMatrix[i][j] != 0)
               {
                   int found = graphMatrix[i][j];

                   for(int k = 0; k<v;k++)
                   {
                       if(graphMatrix[k][j] == 0-found)
                       {
                           if(found < 0)
                           {
                               found = 0-found;
                           }
                           edge.to = k;
                           edge.from = i;
                           edge.weight = found;
                           priorityQueue.push(edge);
                           break;
                       }
                   }
               }
           }
           edge = priorityQueue.first();
           priorityQueue.pop();

           while(visited[edge.to])
           {
               edge = priorityQueue.first();
               priorityQueue.pop();
           }
           sumWeight+=edge.weight;

           mstMatrix[edge.from][n] = edge.weight;
           mstMatrix[edge.to][n] = 0-edge.weight;
           i=edge.to;
           n++;

           visited[edge.to] = 1;
           sumVisit++;


       }



    for(i = 0;i<v;i++)
    {    cout<<setw(3)<<"|";
        for(int j = 0; j<n;j++)
        {
            cout<<setw(4)<<mstMatrix[i][j];
        }
        cout<<setw(3)<<"|"<<endl;
    }



    std::cout<<std::endl;
    std::cout<<"Waga: "<<sumWeight<<std::endl;
    std::cout<<std::endl;





    delete[] mstMatrix;
}

void PrimMST::runOnList(listElement ** graphList,int v, int e)
{
    listElement *  nextElement;
    listElement *  currentNode;
    listElement ** mstList;
    PriorityQueue priorityQueue(e);
    mstList = new listElement * [v];

    int visited[v];
    int sumVisit = 0;
    int sumWeight=0;

    for(int i = 0; i < v; i++)
    {
        visited[i] = 0;
        mstList[i] = nullptr;
    }

    visited[0] = 1;
    sumVisit++;
    int n = 0;




    while(sumVisit<v)
    {
        nextElement = graphList[n];
        Edge edge;
        while(nextElement)
        {
            if(!visited[nextElement->v])
            {
                edge.weight = nextElement->wei;
                edge.from = n;
                edge.to = nextElement -> v;
                priorityQueue.push(edge);
            }
            nextElement = nextElement->next;
        }

        edge = priorityQueue.first();
        priorityQueue.pop();

        while(visited[edge.to])
        {
            edge = priorityQueue.first();
            priorityQueue.pop();
        }
        sumWeight+=edge.weight;

        currentNode = new listElement;
        currentNode->wei = edge.weight;
        currentNode->v = edge.to;
        currentNode->next = mstList[edge.from];
        mstList[edge.from] = currentNode;

        currentNode = new listElement;
        currentNode->wei = edge.weight;
        currentNode->v = edge.from;
        currentNode->next = mstList[edge.to];
        mstList[edge.to] = currentNode;

        visited[edge.to] = 1;

        sumVisit++;
        n=edge.to;


    }




    for(int i = 0; i < v; i++)
    {
        std::cout << "V [" << i << "] =";
        nextElement = mstList [i];
        while(nextElement)
        {
            std::cout <<std::setw(3)<< nextElement->v<<":"<<nextElement->wei;
            nextElement = nextElement->next;
        }
        std::cout<<std::endl;

    }

    std::cout<<std::endl;
    std::cout<<"Waga: "<<sumWeight<<std::endl;
    std::cout<<std::endl;

    delete[]mstList;
}
