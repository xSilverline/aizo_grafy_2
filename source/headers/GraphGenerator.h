//
// Created by Silver on 04.06.2024.
//

#ifndef AIZO_GRAFY_GRAPHGENERATOR_H
#define AIZO_GRAFY_GRAPHGENERATOR_H


#include "Structures.h"

class GraphGenerator
        {

        public:
            listElement ** getList(int v,int density,bool direct);
            int ** getMatrix(int v, int density,bool direct);
            int getEdgeNumber();

        private:
            int ** graphMatrix;
            listElement ** graphList;
            void generateGraph(int v, int density,bool direct);
};


#endif //AIZO_GRAFY_GRAPHGENERATOR_H
