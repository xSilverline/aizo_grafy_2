
#include <iostream>
#include <iomanip>
#include "../headers/GraphReader.h"
#include "../headers/Structures.h"
using namespace std;
int ** GraphReader::readMatrix(int direct)
{
    if(graphMatrix != nullptr)
        return graphMatrix;
    else
    {
        readGraph(direct);
        return graphMatrix;
    }
}

listElement ** GraphReader::readList(int direct)
{
    if(graphList != nullptr)
        return graphList;
    else
    {
        readGraph(direct);
        return graphList;
    }
}


void GraphReader::readGraph(int direct)
{

    int from, to, weight;
    string filename;
    cout<<"Nazwa pliku: "<<endl;
    cin>>filename;
    fstream inputFile;
    inputFile.open(filename);
    inputFile >> e;
    inputFile >> v;

    graphMatrix = new int * [v];
    graphList = new listElement * [v];
    listElement * newNode;
    for(int i = 0; i<v; i++)
    {
        graphMatrix[i] = new int [e];
        graphList[i] = nullptr;
    }
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < e; j++) {
            graphMatrix[i][j] = 0;
        }

    }
    int tempE=0;
    while(inputFile >> from >> to >> weight)
    {
//        cout<<from<<" "<<to<<" "<<weight<<endl;


        newNode = new listElement;
        newNode->v = to;
        newNode->wei = weight;
        newNode->next = graphList[from];
        graphList[from] = newNode;

        if(direct == 2)
        {
            graphMatrix[from][tempE] = weight;
            graphMatrix[to][tempE] = -1;
        }
        else
        {
            newNode = new listElement;
            newNode->v = from;
            newNode->wei = weight;
            newNode->next = graphList[to];
            graphList[to] = newNode;

            graphMatrix[from][tempE] = weight;
            graphMatrix[to][tempE] = -weight;
        }

        tempE++;


    }

    inputFile.close();

//    for(int i = 0;i<v;i++)
//    {    cout<<setw(3)<<"|";
//        for(int j = 0; j<e;j++)
//        {
//            cout<<setw(4)<<graphMatrix[i][j];
//        }
//        cout<<setw(3)<<"|"<<endl;
//    }
//
//    listElement *  nextElement;
//
//    cout<<endl;
//    cout<<endl;
//
//    for(int i = 0; i < v; i++)
//    {
//        cout << "V [" << i << "] =";
//        nextElement = graphList [i];
//        while(nextElement)
//        {
//            cout <<setw(3)<< nextElement->v<<":"<<nextElement->wei;
//            nextElement = nextElement->next;
//        }
//        cout<<endl;
//    }


}
