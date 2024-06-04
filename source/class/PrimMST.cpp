//
// Created by Silver on 04.06.2024.
//

#include <iostream>
#include <iomanip>
#include "../headers/PrimMST.h"
#include "../headers/Structures.h"
#include "../headers/PriorityQueue.h"



listElement *  nextElement;
listElement *  currentNode;
listElement ** mstList;
listElement ** toVisit;

void PrimMST::runOnMatrix(int ** graphMatrix,int v,int e)
{
    PriorityQueue priorityQueue(e);
    int visited[v];
    int sumVisit = 0;
    int sumWeight=0;


    for(int i = 0; i < v; i++)
    {
        visited[i] = 0;
    }

    visited[0] = 1;
    sumVisit++;
    int n = 0;


    for(int i = 0; i<v;i++)
    {
        for()

    }








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






}

void PrimMST::runOnList(listElement ** graphList,int v, int e)
{
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

}
