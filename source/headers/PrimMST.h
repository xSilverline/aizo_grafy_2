//
// Created by Silver on 04.06.2024.
//

#ifndef AIZO_GRAFY_PRIMMST_H
#define AIZO_GRAFY_PRIMMST_H


#include "Structures.h"

class PrimMST {

public:
    double runOnMatrix(int **graphMatrix,int v,int e,bool print);
    double runOnList(listElement **graphList,int v,int e,bool print);
private:
//    static int ** mstMatrix;

//    static void buildMatrix(int v, int e);
};


#endif //AIZO_GRAFY_PRIMMST_H
