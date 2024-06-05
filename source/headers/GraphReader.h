//
// Created by Silver on 04.06.2024.
//

#ifndef AIZO_GRAFY_GRAPHREADER_H
#define AIZO_GRAFY_GRAPHREADER_H

#include <fstream>
#include "Structures.h"

class GraphReader {
public:
    int **readMatrix(int direct);
    int e,v;
    listElement **readList(int direct);

private:
    int ** graphMatrix;
    listElement ** graphList;
    void readGraph(int direct);

};


#endif //AIZO_GRAFY_GRAPHREADER_H
