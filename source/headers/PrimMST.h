//
// Created by Silver on 04.06.2024.
//

#ifndef AIZO_GRAFY_PRIMMST_H
#define AIZO_GRAFY_PRIMMST_H


#include "Structures.h"

class PrimMST {

public:
    void runOnMatrix(int **graphMatrix,int v,int e);
    void runOnList(listElement **graphList,int v,int e);


};


#endif //AIZO_GRAFY_PRIMMST_H
