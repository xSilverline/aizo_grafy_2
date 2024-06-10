//
// Created by Silver on 09.06.2024.
//

#ifndef AIZO_GRAFY_KRUSKALMST_H
#define AIZO_GRAFY_KRUSKALMST_H

#include "Structures.h"

class KruskalMST {

public:
    void runOnMatrix(int **graphMatrix,int v,int e);
    void runOnList(listElement **graphList,int v,int e);
private:
    int ** mstMatrix;

};


#endif //AIZO_GRAFY_KRUSKALMST_H
