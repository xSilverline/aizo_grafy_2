//
// Created by Silver on 10.06.2024.
//

#ifndef AIZO_GRAFY_BELLMANFORD_H
#define AIZO_GRAFY_BELLMANFORD_H

#include "Structures.h"

class BellmanFord {
public:
    double runOnList(listElement** graphList, int v, int e, int start, int end,bool print);
    double runOnMatrix(int** graphMatrix, int v, int e, int start, int end,bool print);
private:
    const int MAXINT = 2147483647;
};


#endif //AIZO_GRAFY_BELLMANFORD_H
