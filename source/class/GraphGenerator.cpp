//
// Created by Silver on 04.06.2024.
//


#include <chrono>
#include <random>
#include <iostream>
#include "../headers/GraphGenerator.h"
#include "../headers/Structures.h"


std::default_random_engine generator;

bool checkIfInside(listElement * check, int dest);
void ** GraphGenerator::generateGraph(int v, int density, bool direct)
{
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> destination(0,v-1);
    std::uniform_int_distribution<int> edgeWeightDist(1,100);

    int weight;
    graphMatrix = new int *[v];
    graphList = new listElement * [v];
    listElement *  nextElement;

//    int * fromV= new int [v];
    int toV[v];
    int e;
    int limit;
    if(density==99)
    {
        e = (v*(v-1))/2;
    }
    else
    {
        float edges =  float(float(v * (v - 1)) / 2) * float(density) / 100;
        e = int(edges);
        if(e < v-1)
        {
            e = v-1;
        }
    }





    for(int i = 0; i<v;i++)
    {
        graphMatrix[i] = new int [e];
        graphList[i] = nullptr;
//        fromV[i] = 1;
        toV[i] = 1;
    }
    for(int i = 0;i<v;i++)
    {
        for(int j = 0; j<e;j++)
        {
            graphMatrix[i][j] = 0;
        }

    }
    int tempE=0;

    if(density==99)
    {

        for(int i = 0; i<v;i++)
        {
            for(int j = i+1;j<v;j++)
            {

                weight = edgeWeightDist(generator);
                nextElement = new listElement;
                nextElement->v = j;
                nextElement->wei = weight;
                nextElement->next = graphList[i];
                graphList[i] = nextElement;

                if(!direct)
                {
                    nextElement = new listElement;
                    nextElement->v = i;
                    nextElement->wei = weight;
                    nextElement->next = graphList[j];
                    graphList[j] = nextElement;

                    graphMatrix[i][tempE] = weight;
                    graphMatrix[j][tempE] = -weight;
                    tempE++;

                }
                else
                {
                    graphMatrix[i][tempE] = weight;
                    graphMatrix[j][tempE] = -1;
                    tempE++;
                }


            }
        }



    }
    else
    {


        for(int i = 0; i<v-1;i++)
        {
            int destFrom = i;
            int destTo = destination(generator);
            weight = edgeWeightDist(generator);

            while(destTo == destFrom || toV[destTo] == 0)
                destTo = destination(generator);

            toV[destTo] = 0;
            nextElement = new listElement;
            nextElement->v = destTo;
            nextElement->wei = weight;
            nextElement->next = graphList[i];
            graphList[i] = nextElement;

            if(!direct)
            {
                nextElement = new listElement;
                nextElement->v = destFrom;
                nextElement->wei = weight;
                nextElement->next = graphList[destTo];
                graphList[destTo] = nextElement;

                graphMatrix[i][tempE] = weight;
                graphMatrix[destTo][tempE] = -weight;
                tempE++;

            }
            else
            {
                graphMatrix[i][tempE] = weight;
                graphMatrix[destTo][tempE] = -1;
                tempE++;
            }




        }
        if(e>v-1)
        {
            for(int i = v-1;i<e;i++)
            {
                int destFrom = destination(generator);
                int destTo = destination(generator);
                weight = edgeWeightDist(generator);
                listElement * check = graphList[destFrom];
                while(destTo == destFrom  || checkIfInside(check,destTo))
                    destTo = destination(generator);

                nextElement = new listElement;
                nextElement->v = destTo;
                nextElement->wei = weight;
                nextElement->next = graphList[destFrom];
                graphList[destFrom] = nextElement;

                if(!direct)
                {
                    nextElement = new listElement;
                    nextElement->v = destFrom;
                    nextElement->wei = weight;
                    nextElement->next = graphList[destTo];
                    graphList[destTo] = nextElement;
                    graphMatrix[destFrom][i] = weight;
                    graphMatrix[destTo][i] = -weight;
                }
                else
                {
                    graphMatrix[destFrom][i] = weight;
                    graphMatrix[destTo][i] = -1;
                }




            }
        }
    }
}

listElement **GraphGenerator::getList(int v, int density,bool direct)
{
    if(graphList != nullptr)
        return graphList;
    else
    {
        generateGraph(v,density,direct);
        return graphList;
    }
}

int **GraphGenerator::getMatrix(int v, int density,bool direct)
{
    if(graphMatrix != nullptr)
        return graphMatrix;
    else
    {
        generateGraph(v,density,direct);
        return graphMatrix;
    }
}

bool checkIfInside(listElement * check, int dest)
{
    while(check)
    {
        if(check->v == dest)
        {
            return true;
        }
        else
            check = check->next;
    }

    return false;
}
