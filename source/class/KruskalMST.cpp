
#include "../headers/KruskalMST.h"
#include "../headers/PriorityQueue.h"
#include <iostream>
#include <iomanip>

using namespace std;

void KruskalMST::runOnMatrix(int **graphMatrix, int v, int e)
{
    PriorityQueue priorityQueue{e};
    int visited[v];
    int setNumber[v];
    int sumVisit = 0;
    int sumWeight=0;
    mstMatrix = new int * [v];


    for(int i = 0; i < v; i++)
    {
        mstMatrix[i] = new int [v-1];
        for(int j = 0; j<v-1;j++)
        {
            mstMatrix[i][j] = 0;
        }
        visited[i] = 0;
        setNumber[i] = 0;
    }


    int value = 0;
    for(int i =0; i<v;i++)
    {
        for(int j = 0; j<e; j++)
        {
            value = graphMatrix[i][j];
            if(value > 0)
            {
                Edge edge{};
                edge.from = i;
                edge.weight = value;
                for(int k = 0; k<v;k++)
                {
                    int toEdge = graphMatrix[k][j];
                    if(toEdge == -value)
                    {
                        edge.to = k;
                        break;
                    }
                }
                priorityQueue.push(edge);

            }
        }
    }
//    visited[0] = 1;

//    sumVisit++;
    Edge nextEdge{};
    int n = 0;
    int max = 1;
    while(true)
    {
        nextEdge = priorityQueue.first();
        priorityQueue.pop();
        int from = nextEdge.from;
        int to = nextEdge.to;
        int weight = nextEdge.weight;

        if(!visited[from] || !visited[to])
        {

            if(setNumber[from] == 0 && setNumber[to] == 0)
            {
                setNumber[from] = max;
                setNumber[to] = max;
            }
            else if(setNumber[from] == 0)
                setNumber[from] = setNumber[to];
            else
                setNumber[to] = setNumber[from];


            mstMatrix[from][n] = weight;
            mstMatrix[to][n] = -weight;
            n++;
            sumWeight+=weight;

            if(!visited[from] && !visited[to])
            {
                sumVisit+=2;
                max++;
            }
            else
                sumVisit++;

            visited[to] = 1;
            visited[from] = 1;

        }
        else if(visited[from] && visited[to])
        {
           if(setNumber[from] != setNumber[to])
           {
               int fromSet;
               int targetSet;
               mstMatrix[from][n] = weight;
               mstMatrix[to][n] = weight;
               n++;
               sumWeight+=weight;
               if(setNumber[from] < setNumber[to])
               {
                   targetSet = setNumber[from];
                   fromSet = setNumber[to];

               }
               else
               {
                   targetSet = setNumber[to];
                   fromSet = setNumber[from];

               }

               for(int i = 0;i<v;i++)
               {
                   if(setNumber[i] == fromSet)
                       setNumber[i] = targetSet;
               }

           }
        }



        int totalSet = 0;
        for(int i = 0;i<v;i++)
        {
            if(setNumber[i] > totalSet)
                totalSet = setNumber[i];
        }

        if(sumVisit == v && totalSet == 1)
            break;


    }

    for(int i = 0;i<v;i++)
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

void KruskalMST::runOnList(listElement **graphList, int v, int e) {
    PriorityQueue priorityQueue{e};
    int visited[v];
    int setNumber[v];
    int sumVisit = 0;
    int sumWeight = 0;
    int addVisit[v];
    auto **mstList = new listElement *[v];
    listElement *  nextElement;

    for (int i = 0; i < v; i++) {
        addVisit[i] = 0;
        visited[i] = 0;
        setNumber[i] = 0;
        mstList[i] = nullptr;
    }

    for (int i = 0; i < v; i++)
    {
        addVisit[i] = 1;
        nextElement = graphList[i];
        Edge edge{};
        while(nextElement)
        {
            if(!addVisit[nextElement->v])
            {
                edge.from = i;
                edge.to = nextElement->v;
                edge.weight = nextElement->wei;
                priorityQueue.push(edge);

            }
            nextElement = nextElement->next;
        }
    }

    Edge nextEdge{};
    int max = 1;
    while (true)
    {
        nextEdge = priorityQueue.first();
        priorityQueue.pop();
        int from = nextEdge.from;
        int to = nextEdge.to;
        int weight = nextEdge.weight;

        if(!visited[from] || !visited[to])
        {
            if(setNumber[from] == 0 && setNumber[to] == 0)
            {
                setNumber[from] = max;
                setNumber[to] = max;
            }else if(setNumber[from] == 0)
            {
                setNumber[from] = setNumber[to];
            }else
            {
                setNumber[to] = setNumber[from];
            }

            nextElement = new listElement;
            nextElement->v = to;
            nextElement->wei = weight;
            nextElement->next = mstList[from];
            mstList[from] = nextElement;

            nextElement = new listElement;
            nextElement->v = from;
            nextElement->wei = weight;
            nextElement->next = mstList[to];
            mstList[to] = nextElement;

            sumWeight+=weight;

            if(!visited[from] && !visited[to])
            {
                sumVisit+=2;
                max++;
            }
            else
                sumVisit++;

            visited[from] = 1;
            visited[to] = 1;

        }
        else if(visited[from] && visited[to])
        {
            if(setNumber[from] != setNumber[to])
            {
                int fromSet;
                int toSet;
                nextElement = new listElement;
                nextElement->v = to;
                nextElement->wei = weight;
                nextElement->next = mstList[from];
                mstList[from] = nextElement;

                nextElement = new listElement;
                nextElement->v = from;
                nextElement->wei = weight;
                nextElement->next = mstList[to];
                mstList[to] = nextElement;


                sumWeight+=weight;
                if(setNumber[from]<setNumber[to])
                {
                    toSet = setNumber[from];
                    fromSet = setNumber[to];
                }
                else
                {
                    toSet = setNumber[to];
                    fromSet = setNumber[from];
                }

                for(int i = 0;i<v;i++)
                {
                    if(setNumber[i] == fromSet)
                        setNumber[i] = toSet;
                }
            }
        }

        int totalSet = 0;
        for(int i = 0;i<v;i++)
        {
            if(setNumber[i] > totalSet)
                totalSet = setNumber[i];
        }

        if(sumVisit == v && totalSet == 1)
            break;
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
