
#include <iostream>
#include <iomanip>
#include "../headers/Dijkstra.h"
#include "../headers/Counters.h"

using namespace std;
double Dijkstra::runOnMatrix(int ** graphMatrix, int v, int e, int start, int end,bool print)
{
    startCounter();
    int * cost = new int[v];
    int * prev = new int[v];
    bool * QS = new bool[v];
    int ** resultMatrix = new int*[v];






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
//    int j,result;
    for(int i = 0; i<v; i++)
    {
        int k = -1;

//        for(j = 0; QS[j];j++){}

        for(int j=0; j<v;j++)
        {
            if(!QS[j] && (k == -1 || cost[j] < cost[k]))
                k = j;
        }

        if(k == -1 || cost[k] == MAXINT)
            break;

        QS[k] = true;

        for(int c = 0; c<e;c++)
        {
            if(graphMatrix[k][c] > 0)
            {
                int from = k;
                int to = -1;
                int weight  = graphMatrix[k][c];

                for(int x = 0; x<v;x++)
                {
                    if(graphMatrix[x][c] == -1)
                    {
                        to = x;
                        break;
                    }
                }




                if(to != -1 && !QS[to] && (cost[to] > cost[k]+weight))
                {
                    cost[to] = cost[from]+weight;
                    prev[to] = from;
                }
            }


        }

    }

    int current = end;
    int edgeIndex=0;
    while(current != start && current != -1)
    {

        int cst = cost[current];
        int prv = prev[current];

        resultMatrix[current][edgeIndex] = -1;
        resultMatrix[prev[current]][edgeIndex] = cost[current];
//        cout << "From: " << prev[current] << " To: " << current << " Weight: " << cost[current] << endl;
        current = prev[current];
        edgeIndex++;
    }

    double time = getCounter();

    if(print) {
        cout << endl;
        for (int i = 0; i < v; i++) {
            std::cout << std::setw(3) << i << " |";
            for (int l = 0; l < edgeIndex; l++) {
                std::cout << std::setw(4) << resultMatrix[i][l];
            }
            std::cout << std::setw(3) << "|" << std::endl;
        }


        cout << endl << "Waga calkowita od " << start << " do " << end << " wynosi " << cost[end] << endl << endl;

        cout << "Czas dzialania: " << time << endl << endl;
    }

    for(int i = 0; i < v; i++) {
        delete[] resultMatrix[i];
    }
    delete []resultMatrix;
    delete [] cost;
    delete[] prev;
    delete [] QS;

    return time;
}

double Dijkstra::runOnList(listElement ** graphList, int v, int e, int start, int end,bool print)
{
    startCounter();
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

    int current = end;

    while(current != start && current != -1)
    {
        result = new listElement;
        result->v = current;
        result->wei = cost[current];
        result->next = resultList[prev[current]];
        resultList[prev[current]] = result;
//        cout << "From: " << prev[current] << " To: " << current << " Weight: " << cost[current] << endl;
        current = prev[current];
    }
    double time = getCounter();

    if(print) {
        cout << endl;
        for (int i = 0; i < v; i++) {
            std::cout << "V [" << i << "] =";
            result = resultList[i];
            while (result) {
                std::cout << std::setw(3) << result->v << ":" << result->wei;
                result = result->next;
            }
            std::cout << std::endl;

        }

        int c = cost[end];

        cout << endl << "Waga calkowita od " << start << " do " << end << " wynosi " << c << endl << endl;

        cout << "Czas dzialania: " << time << endl << endl;
    }


    delete [] cost;
    delete[] prev;
    delete [] QS;
    for(int i = 0 ; i<v; i++)
    {
        if(resultList[i] != nullptr)
            delete[] resultList[i];
    }

    delete [] resultList;



    return time;
}