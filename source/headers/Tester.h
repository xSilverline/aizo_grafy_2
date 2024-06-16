

#ifndef AIZO_GRAFY_TESTER_H
#define AIZO_GRAFY_TESTER_H

#include <random>
#include <chrono>
#include "Structures.h."
#include "Counters.h"
#include <fstream>

class Tester
        {
        public:
            void beginTest();
private:
    void generateData(int v, int density, int direct);
    void testMST(int v);


    void testPath( int v);
};


#endif //AIZO_GRAFY_TESTER_H
