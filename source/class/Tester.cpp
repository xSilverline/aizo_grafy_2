

#include "../headers/allheaders.h"
int ** testMatrix = nullptr;
listElement ** testList = nullptr;
int numOfEdge = 0;
double timePrim=0;
double timeKruskal=0;
double timeDijkstra=0;
double timeBellmanFord=0;
double timePrimList=0;
double timeKruskalList=0;
double timeDijkstraList=0;
double timeBellmanFordList=0;
PrimMST prim{};
KruskalMST kruskal{};
Dijkstra dijkstra{};
BellmanFord bellmanFord{};

std::default_random_engine gen;

void Tester::beginTest()
{
    gen.seed(std::chrono::system_clock::now().time_since_epoch().count());
    bool mst = false;
    bool path = true;
    int runs = 50;

    string filename;

    int dens = 0;
    
    for(int i = 2; i<8;i++)
    {
        int v = 100*i;

        for(int d = 1; d<4; d++)
        {

            if(d == 1)
                dens = 25;
            else if (d == 2)
                dens = 50;
            else if ( d == 3)
                dens = 99;
            std::cerr<<"STARTING RUN  | DENSITY: "<<dens<<" | V = "<<v<<" |"<<endl;
            for(int run = 0; run<runs;run++)
            {
//                std::cerr<<"STARTING RUN "<<run<<" | DENSITY: "<<dens<<" | V = "<<v<<" |"<<endl;
                generateData(v,dens,mst);
//                cerr<<"MST GEN OK"<<endl;
                testMST(v);
                for(int x = 0; x<v;x++)
                {
                    delete[] testList[x];
                    delete[] testMatrix[x];
                }
                delete[] testList;
                delete[] testMatrix;
                generateData(v,dens,path);
//                cerr<<"PATH GEN OK"<<endl;
                testPath(v);

                for(int x = 0; x<v;x++)
                {
                    delete[] testList[x];
                    delete[] testMatrix[x];
                }
                delete[] testList;
                delete[] testMatrix;
            }

            filename ="v"+ to_string(v)+"_D"+ to_string(dens)+".txt";
            ofstream output(filename);

//            cout<<"PRIM - MATRIX : \t"<<timePrim/runs<<endl;
//            cout<<"PRIM - LIST : \t"<<timePrimList/runs<<endl;
//
//            cout<<"KRUSKAL - MATRIX : \t"<<timeKruskal/runs<<endl;
//            cout<<"KRUSKAL - LIST : \t"<<timeKruskalList/runs<<endl;
//
//            cout<<"DIJKSTRA - MATRIX : \t"<<timeDijkstra/runs<<endl;
//            cout<<"DIJKSTRA - LIST : \t"<<timeDijkstraList/runs<<endl;
//
//            cout<<"BELLMAN-FORD - MATRIX : \t"<<timeBellmanFord/runs<<endl;
//            cout<<"BELLMAN-FORD - LIST : \t"<<timeBellmanFordList/runs<<endl;

            output<<"PRIM - MATRIX\t"<<timePrim/runs<<endl;
            output<<"PRIM - LIST\t"<<timePrimList/runs<<endl;

            output<<"KRUSKAL - MATRIX\t"<<timeKruskal/runs<<endl;
            output<<"KRUSKAL - LIST\t"<<timeKruskalList/runs<<endl;

            output<<"DIJKSTRA - MATRIX\t"<<timeDijkstra/runs<<endl;
            output<<"DIJKSTRA - LIST\t"<<timeDijkstraList/runs<<endl;

            output<<"BELLMAN-FORD - MATRIX\t"<<timeBellmanFord/runs<<endl;
            output<<"BELLMAN-FORD - LIST\t"<<timeBellmanFordList/runs<<endl;

            output.flush();
            output.close();

            
        }
    }
}

void Tester::generateData(int v, int density, int direct)
{
    GraphGenerator generator{};

    testMatrix = generator.getMatrix(v,density,direct);
    testList = generator.getList(v,density,direct);
    numOfEdge = generator.getEdgeNumber();

}

void Tester::testMST(int v)
{
    timePrim+= prim.runOnMatrix(testMatrix, v, numOfEdge, false);
    timePrimList+= prim.runOnList(testList, v, numOfEdge, false);
    timeKruskal+= kruskal.runOnMatrix(testMatrix, v, numOfEdge, false);
    timeKruskalList+= kruskal.runOnList(testList, v, numOfEdge, false);
}

void Tester::testPath(int v)
{
    
    std::uniform_int_distribution<int> DestFromTo(0, v - 1);
    int from = DestFromTo(gen);
    int to = DestFromTo(gen);
    while(from == to)
    {
        to = DestFromTo(gen);
    }
    
    timeDijkstra+= dijkstra.runOnMatrix(testMatrix, v, numOfEdge, from, to, false);
    timeDijkstraList+= dijkstra.runOnList(testList, v, numOfEdge, from, to, false);
    timeBellmanFord+= bellmanFord.runOnMatrix(testMatrix, v, numOfEdge, from, to, false);
    timeBellmanFordList+= bellmanFord.runOnList(testList, v, numOfEdge, from, to, false);
    
    
}