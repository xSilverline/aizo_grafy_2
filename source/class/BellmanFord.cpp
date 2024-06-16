
#include "../headers/BellmanFord.h"
#include "../headers/Counters.h"

#include <iostream>
#include <vector>
#include <list>
#include <iomanip>
#include <limits>

using namespace std;




struct Edge {
    int from, to, weight;
};



double BellmanFord::runOnMatrix(int** graphMatrix, int v, int e, int start, int end,bool print) {
    startCounter();

    int * cost = new int[v];
    int * prev = new int[v];
    int ** resultMatrix = new int * [v];


    for(int i = 0; i<v; i++)
    {
        cost[i] = MAXINT;
        prev[i] = -1;
        resultMatrix[i] = new int [e]{0};
    }

    cost[start] = 0;
    int from;
    int to;
    int weight;


    // Relax edges |V|-1 times
    for (int i = 0; i < v - 1; i++)
    {

        for(int j = 0; j<e;j++)
        {
            from = -1;
            to = -1;
            weight = 0;
            for(int k = 0; k<v;k++)
            {
                if(graphMatrix[k][j] >0)
                {
                    from = k;
                    weight = graphMatrix[k][j];
                }
                if(graphMatrix[k][j] == -1)
                    to = k;

            }
            if(from != -1 && to != -1 && cost[to] > cost[from]+weight && cost[from] != MAXINT)
            {
                cost[to] = cost[from] + weight;
                prev[to] = from;
            }

        }


    }

    // Print result
    int current = end;
    int edgeIndex=0;
    while (current != start && current != -1) {
        if (current >= 0 && current < v && prev[current] >= 0 && prev[current] < v && edgeIndex < e) {
            resultMatrix[current][edgeIndex] = -1;
            resultMatrix[prev[current]][edgeIndex] = cost[current];
        }
//        cout << "From: " << prev[current] << " To: " << current << " Weight: " << cost[current] << endl;
        current = prev[current];
        edgeIndex++;
    }


    double time = getCounter();

    if(print)
    {
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
        cout<<"Czas dzialania: "<<time<<endl<<endl;
    }


    delete[] cost;
    delete[] prev;
    for(int i = 0; i < v; i++) {
        delete[] resultMatrix[i];
    }
    delete[] resultMatrix;

    return time;

}

double BellmanFord::runOnList(listElement** graphList, int v, int e, int start, int end,bool print) {

    startCounter();
    int * cost = new int[v];
    int * prev = new int[v];
    auto ** resultList = new listElement * [v];


    for (int i = 0; i < v; i++) {
        resultList[i] = nullptr;
        cost[i] = MAXINT;
        prev[i] = -1;
    }

    cost[start] = 0;

    // Relax edges |V|-1 times
    for (int i = 0; i < v - 1; i++)
    {
        for(int j = 0; j<v; j++)
        {
            listElement* nextElement = graphList[j];
            while(nextElement)
            {
                if(cost[j] != MAXINT && cost[nextElement->v] > cost[j]+nextElement->wei)
                {
                    cost[nextElement->v] = cost[j]+nextElement->wei;
                    prev[nextElement->v] = j;
                }
                nextElement = nextElement->next;
            }
        }

    }




    // Print result
    int current = end;
    listElement * result;
    while (current != start && current != -1)
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

    if(print)

    {
        cout<<endl;
        for (int i = 0; i < v; i++) {
            std::cout << "V [" << i << "] =";
            result = resultList[i];
            while (result) {
                std::cout << std::setw(3) << result->v << ":" << result->wei;
                result = result->next;
            }
            std::cout << std::endl;

        }

        cout << endl << "Waga calkowita od " << start << " do " << end << " wynosi " << cost[end] << endl << endl;
        cout << "Czas dzialania: " << time << endl << endl;
    }

//    delete[] result;
    delete[] cost;
    delete[] prev;
    for(int i = 0 ; i<v; i++)
    {
        if(resultList[i] != nullptr)
            delete[] resultList[i];
    }
    delete[] resultList;

    return time;
}
