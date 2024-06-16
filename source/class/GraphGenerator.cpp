
#include <chrono>
#include <random>
#include <iostream>
#include "../headers/GraphGenerator.h"
#include "../headers/Structures.h"


std::default_random_engine generator;
int edgeNumber = 0;

bool checkIfInside(listElement * check, int dest);
int GraphGenerator::getEdgeNumber()
{
    return edgeNumber;
}
void GraphGenerator::generateGraph(int v, int density, bool direct) {

    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> destination(0, v - 1);
    std::uniform_int_distribution<int> edgeWeightDist(1, 100);

    int weight;
    int *numOfIndex;
    graphMatrix = new int *[v];
    graphList = new listElement *[v];
    listElement *nextElement;

//    int * fromV= new int [v];
    int toV[v];
    int e;
    int limit;
    if (density == 99) {
        e = (v * (v - 1)) / 2;
    } else {

        e = ((v * (v - 1)) / 2) * (density) / 100;
        if (e < v - 1) {
            e = v - 1;
        }
        edgeNumber = e;
    }


    for (int i = 0; i < v; i++) {
        graphMatrix[i] = new int[e];
        graphList[i] = nullptr;
//        fromV[i] = 1;
        toV[i] = 1;
    }
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < e; j++) {
            graphMatrix[i][j] = 0;
        }

    }
    int tempE = 0;

    if (density == 99)
    {
        numOfIndex = new int[v]{0};
        std::uniform_int_distribution<int> turn(0, 20);
        int from,to;
        for (int i = 0; i < v; i++) {

            for (int j = i + 1; j < v; j++)
            {
                int path = turn(generator);
                if(path%2 == 0)
                {
                    from = i;
                    to = j;
                }
                else
                {
                    from = j;
                    to = i;
                }

                weight = edgeWeightDist(generator);
                nextElement = new listElement;
                nextElement->v = to;
                nextElement->wei = weight;
                nextElement->next = graphList[from];
                graphList[from] = nextElement;

                if (!direct) {
                    nextElement = new listElement;
                    nextElement->v = from;
                    nextElement->wei = weight;
                    nextElement->next = graphList[to];
                    graphList[to] = nextElement;

                    graphMatrix[from][tempE] = weight;
                    graphMatrix[to][tempE] = -weight;
                    tempE++;

                } else {
                    graphMatrix[from][tempE] = weight;
                    graphMatrix[to][tempE] = -1;
                    tempE++;
                }
                numOfIndex[i]++;

            }
        }

        if(e/100)
        {
            int numToDel = e/100;
//            std::cout<<"E = "<<e<<std::endl;
            int vortex = 0;
            int edges = e;

            while(numToDel)
            {
                std::uniform_int_distribution<int> index(0, edges-1);
                int idx = index(generator);
                int found =0;
                int delTo=0;
                int delFrom=0;
                bool flag = false;

                for(int i = 0; i<v;i++)
                {
                    listElement* toDelete = graphList[i];
                    listElement* toDelprev = nullptr;

                    listElement* directDel = nullptr;
                    listElement* directPrev = nullptr;

                    while(toDelete)
                    {
                        if(found == idx)
                        {
                            delFrom = i;
                            delTo = toDelete->v;
                            if(!toDelprev)
                            {
                                graphList[i] = toDelete->next;
                            }
                            else
                            {
                                toDelprev->next = toDelete->next;
                            }

                            if(!direct)
                            {
                                directDel = graphList[delTo];
                                while(directDel->v != i)
                                {   directPrev = directDel;
                                    directDel= directDel->next;
                                }
                                if(!directPrev)
                                {
                                    graphList[delTo] = directDel->next;
                                }
                                else
                                {
                                    directPrev->next = directDel->next;
                                }


                            }
                            flag = true;
                            break;

                        }
                        found++;
                        toDelprev = toDelete;
                        toDelete = toDelete->next;
                    }

                    if(flag)
                    {
                        break;
                    }

                }

                for(int i = 0; i<e; i++)
                {
                    if(graphMatrix[delFrom][i] != 0 && graphMatrix[delTo][i] != 0)
                    {
                        int swapFrom = 0;
                        int swapTo = 0;
                        int swapWeight = 0;
                        if(i != e-1)
                        {
                            for (int x = 0; x < v; x++) {
                                if (graphMatrix[x][e - 1] > 0) {
                                    swapFrom = x;
                                    swapWeight = graphMatrix[x][e - 1];
                                }
                                if (graphMatrix[x][e - 1] < 0)
                                    swapTo = x;

                                if (swapWeight != 0 && swapTo != 0 && swapFrom != 0)
                                    break;
                            }

                            graphMatrix[delFrom][i] = 0;
                            graphMatrix[delTo][i] = 0;
                            graphMatrix[swapFrom][i] = swapWeight;
                            graphMatrix[swapTo][i] = -1;


                        }

                        e--;

                        break;
                    }
                }



                numOfIndex[vortex]--;
                numToDel--;

            }
            int ** tempMatrix = new int* [v];

            for(int i = 0; i<v;i++)
            {
                tempMatrix[i] = new int[e];
                std::copy(graphMatrix[i],graphMatrix[i]+e,tempMatrix[i]);
                delete[] graphMatrix[i];
            }

            graphMatrix = new int * [v];

            for(int i = 0;i<v;i++)
            {
                graphMatrix[i] = new int [e];
                std::copy(tempMatrix[i],tempMatrix[i]+e,graphMatrix[i]);
                delete[] tempMatrix[i];
            }

            delete[] tempMatrix;


        }
        edgeNumber = e;

        delete[] numOfIndex;

    } else {


        for (int i = 0; i < v - 1; i++) {
            int destFrom = i;
            int destTo = destination(generator);
            weight = edgeWeightDist(generator);

            while (destTo == destFrom || toV[destTo] == 0)
                destTo = destination(generator);

            toV[destTo] = 0;
            nextElement = new listElement;
            nextElement->v = destTo;
            nextElement->wei = weight;
            nextElement->next = graphList[i];
            graphList[i] = nextElement;

            if (!direct) {
                nextElement = new listElement;
                nextElement->v = destFrom;
                nextElement->wei = weight;
                nextElement->next = graphList[destTo];
                graphList[destTo] = nextElement;

                graphMatrix[i][tempE] = weight;
                graphMatrix[destTo][tempE] = -weight;
                tempE++;

            } else {
                graphMatrix[i][tempE] = weight;
                graphMatrix[destTo][tempE] = -1;
                tempE++;
            }


        }


        if ((int) e > v - 1) {
            for (int i = v - 1; i < e; i++) {
                int destFrom = destination(generator);
                int destTo = destination(generator);
                weight = edgeWeightDist(generator);
                listElement *check = graphList[destFrom];
                while (destTo == destFrom || checkIfInside(check, destTo))
                    destTo = destination(generator);

                nextElement = new listElement;
                nextElement->v = destTo;
                nextElement->wei = weight;
                nextElement->next = graphList[destFrom];
                graphList[destFrom] = nextElement;

                if (!direct) {
                    nextElement = new listElement;
                    nextElement->v = destFrom;
                    nextElement->wei = weight;
                    nextElement->next = graphList[destTo];
                    graphList[destTo] = nextElement;
                    graphMatrix[destFrom][i] = weight;
                    graphMatrix[destTo][i] = -weight;
                } else {
                    graphMatrix[destFrom][i] = weight;
                    graphMatrix[destTo][i] = -1;
                }


            }
        }
//        edgeNumber = e;
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
