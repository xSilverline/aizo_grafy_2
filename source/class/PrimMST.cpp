
#include <iostream>
#include <iomanip>
#include "../headers/PrimMST.h"
#include "../headers/PriorityQueue.h"


using namespace std;





void PrimMST::runOnMatrix(int ** graphMatrix,int v,int e)
{

//    int ** mstMatrix;

    PriorityQueue priorityQueue{e};
    int visited[v];
    int sumVisit = 0;
    int sumWeight=0;
    int **mstMatrix = nullptr;
    mstMatrix = new int * [v];

    for(size_t i =0;i<v;i++)
    {
        mstMatrix[i] = new int [v-1];
    }



    for(int i = 0; i < v; i++)
    {
        for(int j = 0; j<v-1;j++)
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
          Edge edge{};
           for(int j = 0; j<e;j++)
           {
               if(graphMatrix[i][j] != 0)
               {
                   int found = graphMatrix[i][j];

                   for(int k = 0; k<v;k++)
                   {
                       if(graphMatrix[k][j] == 0-found && !visited[k])
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

           if (priorityQueue.isEmpty())
           {
               std::cerr << "Priority queue is empty, something went wrong!" << std::endl;
               break;
           }

           edge = priorityQueue.first();
           int to = edge.to;
           priorityQueue.pop();


           while(visited[to])
           {

               if (priorityQueue.isEmpty())
               {
                   std::cerr << "Priority queue is empty, no more edges to process!" << std::endl;
                   break;
               }
               edge = priorityQueue.first();
               to = edge.to;
               priorityQueue.pop();

           }
           int from = edge.from;

           int weight = edge.weight;
           sumWeight+=weight;

           if (from < 0 || from >= v || to < 0 || to >= v || n >= v - 1)
           {
               std::cerr << "Index out of bounds: from=" << from << ", to=" << to << ", n=" << n << std::endl;
               break;
           }

           mstMatrix[from][n] = weight;  // SIGSEGV - Randomowo, dla większych tablic. Sprawdzono alokacje pamięci, wygląda okej. Przyczyna nieznana.
           mstMatrix[to][n] = -weight;
           i=to;
           n++;
           if(n>v-1)
               return;

           visited[to] = 1;
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



    for (int d = 0; d < v; d++)
    {
        delete[] mstMatrix[d];
    }


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
        Edge edge{};
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
