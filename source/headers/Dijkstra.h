//
// Created by Silver on 05.06.2024.
//

#ifndef AIZO_GRAFY_DIJKSTRA_H
#define AIZO_GRAFY_DIJKSTRA_H
#include "Structures.h"

class Dijkstra {

public:
    void runOnList(listElement **graphList, int v, int e,int start,int end);

    void runOnMatrix(int **graphMatrix, int v, int e,int start,int end);

private:
    const int MAXINT = 2147483647;
};


#endif //AIZO_GRAFY_DIJKSTRA_H
