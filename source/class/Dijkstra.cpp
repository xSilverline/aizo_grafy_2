
#include <iostream>
#include <iomanip>
#include "../headers/Dijkstra.h"

using namespace std;
void Dijkstra::runOnMatrix(int ** graphMatrix, int v, int e, int start, int end)
{
    int * cost = new int[v];
    int * prev = new int[v];
    bool * QS = new bool[v];
    int ** resultMatrix = new int*[v];
    int from;
    int to;
    int weight;



    for(int i = 0; i<v; i++) //inicjalizacja
    {
        cost[i] = MAXINT;
        prev[i] = -1;
        QS[i] = false;
        resultMatrix[i] = new int [e];
        for(int j=0;j<e;j++)
        {
            resultMatrix[i][j] = 0;
        }

    }


    cost[start] = 0;
    int j,k,result;
    for(int i = 0; i<v; i++)
    {
        for(j = 0; QS[j];j++){}

        for(k = j++; j<v;j++)
        {
            if(!QS[j] && (cost[j] < cost[k]))
                k = j;
        }
        QS[k] = true;

        for(int c = 0; c<e;c++)
        {
            from = k;
            result = graphMatrix[k][c];

            if(result > 0)
            {
                int find=0;
                int x = 0;
                while(find != -1)
                {

                    find = graphMatrix[x][c];
                    x++;
                }
                to = x-1;
                weight = result;
            }

            if(!QS[to] && (cost[to] > cost[k]+weight))
            {
                cost[to] = cost[k]+weight;
                prev[to] = k;
            }
        }

    }

    int current = end;
    int edgeIndex=0;
    while(current != start)
    {
        resultMatrix[current][edgeIndex] = -1;
        resultMatrix[prev[current]][edgeIndex] = cost[current];
        cout << "From: " << prev[current] << " To: " << current << " Weight: " << cost[current] << endl;
        current = prev[current];
        edgeIndex++;
    }

    cout<<endl;
    for(int i = 0;i<v;i++)
    {    std::cout<<std::setw(3)<<i<<" |";
        for(int l = 0; l<edgeIndex;l++)
        {
            std::cout<<std::setw(4)<<resultMatrix[i][l];
        }
        std::cout<<std::setw(3)<<"|"<<std::endl;
    }


    cout <<endl<< "Waga calkowita od " << start << " do " << end << " wynosi " << cost[end] << endl<<endl;




    delete []resultMatrix;
    delete [] cost;
    delete[] prev;
    delete [] QS;

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



    auto * result = new listElement;
//    for(int i = 0; i<v;i++)
//    {
//        for(j=end; j>=0; j=prev[j])
//        {
//            result->wei = cost[j];
//            result->v = j;
//            resultList[j] = result;
//        }
//    }
    int current = end;
    while(current != start)
    {
        result = new listElement;
        result->v = current;
        result->wei = cost[current];
        result->next = resultList[prev[current]];
        resultList[prev[current]] = result;
        cout << "From: " << prev[current] << " To: " << current << " Weight: " << cost[current] << endl;
        current = prev[current];
    }
    cout<<endl;
    for(int i = 0; i < v; i++)
    {
        std::cout << "V [" << i << "] =";
        result = resultList [i];
        while(result)
        {
            std::cout <<std::setw(3)<< result->v<<":"<<result->wei;
            result = result->next;
        }
        std::cout<<std::endl;

    }

    cout <<endl<< "Waga calkowita od " << start << " do " << end << " wynosi " << cost[end] << endl<<endl;




    delete [] cost;
    delete[] prev;
    delete [] QS;
    delete [] resultList;
    delete result;
}