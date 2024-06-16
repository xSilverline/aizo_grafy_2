//
// Created by Silver on 09.06.2024.
//

#ifndef AIZO_GRAFY_KRUSKALMST_H
#define AIZO_GRAFY_KRUSKALMST_H

#include "Structures.h"

class KruskalMST {

public:
    double runOnMatrix(int **graphMatrix,int v,int e,bool print);
    double runOnList(listElement **graphList,int v,int e,bool print);
private:
    int ** mstMatrix;

};


#endif //AIZO_GRAFY_KRUSKALMST_H
