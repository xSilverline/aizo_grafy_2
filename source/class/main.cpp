#include <iostream>
#include <iomanip>
#include "../headers/GraphGenerator.h"
#include "../headers/GraphReader.h"
#include "../headers/Structures.h"
#include "../headers/PrimMST.h"
#include "../headers/Dijkstra.h"
#include "../headers/KruskalMST.h"
#include "../headers/BellmanFord.h"
#include <chrono>
#include <windows.h>
using namespace std;

void showMenu(int problem);
void readData(int p);
void generateGraph(int p);
void printGraph();
void runAlgorithm(int algo);

listElement ** graphList;
int ** graphMatrix;
int e,v,density;
double freq;
long long int counterStart;

void startCounter() // FUNKCJA STARTUJĄCA LICZNIK DO POMIARU CZASU
{
    LARGE_INTEGER largeInteger;
    if(!QueryPerformanceFrequency(& largeInteger))
        cout<<"Blad zliczania czasu"<<endl;

    freq = double(largeInteger.QuadPart) / 1000.0;

    QueryPerformanceCounter(& largeInteger);
    counterStart = largeInteger.QuadPart;
}

double getCounter() // FUNKCJA ZWRACAJĄCA OBECNY STAN LICZNIKA
{
    LARGE_INTEGER largeInteger;
    QueryPerformanceCounter(& largeInteger);
    return double(largeInteger.QuadPart-counterStart)/freq;
}

int main()
{
    int action;
    while(true)
    {
        cout<< "1. MST\n2. Najkrotsza sciezka"<< endl;
        cin >> action;

        if(action == 1)
            showMenu(1);
        else if(action == 2)
            showMenu(2);
        else
            cout<<"Nie ma takiego elementu menu"<<endl;
    }

}

void showMenu(int problem)
{
    int action;

    while(true) {

        if(problem == 1)
        {
            cout<< "1. Wczytaj dane z pliku\n2. Wygeneruj graf losowo\n3. Wyswietl graf listowo i macierzowo na ekranie\n4. Algorytm 1\n5. Algorytm 2"<< endl;
            cin >> action;
        }
        else if(problem == 2)
        {
            cout<< "1. Wczytaj dane z pliku\n2. Wygeneruj graf losowo\n3. Wyswietl graf listowo i macierzowo na ekranie\n4. Algorytm 1\n5. Algorytm 2"<< endl;
            cin >> action;
            if(action > 3)
                action+=2;
        }
        else
            return;



        switch (action) {
            case 1:
                readData(problem);
                break;

            case 2:
                generateGraph(problem);
                break;
            case 3:
                printGraph();
                break;
            case 4:
                runAlgorithm(1);
                break;
            case 5:
                runAlgorithm(2);
                break;
            case 6:
                runAlgorithm(3);
                break;
            case 7:
                runAlgorithm(4);
                break;
            case 0:
                return ;

        }

    }
}

void generateGraph(int p)
{
    int opt;
    bool direct;
    if(p == 1)
        direct = false;
    else
        direct = true;
    cout<<"Podaj liczbe wierzcholkow: "<<endl;
    cin >> v;
    cout<<"Podaj gestosc grafu:\n 1. 25%\n 2. 50%\n 3. 99% "<<endl;
    cin >> opt;
    if(opt == 1)
        density = 25;
    else if(opt == 2)
        density = 50;
    else
        density = 99;
    GraphGenerator generator{};



    graphMatrix = generator.getMatrix(v,density,direct);
    graphList = generator.getList(v,density,direct);

    e = ((v*(v-1))/2)*density/100;
    if(e < v-1)
    {
        e = v-1;
    }

}

void readData(int p)
{
    GraphReader reader{};

    graphList = reader.readList(p);
    graphMatrix = reader.readMatrix(p);
    e=reader.e;
    v=reader.v;
}

void printGraph()
{
    for(int i = 0;i<v;i++)
    {    cout<<setw(3)<<"|";
        for(int j = 0; j<e;j++)
        {
            cout<<setw(4)<<graphMatrix[i][j];
        }
        cout<<setw(3)<<"|"<<endl;
    }

    listElement *  nextElement;

    cout<<endl;
    cout<<endl;

    for(int i = 0; i < v; i++)
    {
        cout << "V [" << i << "] =";
        nextElement = graphList [i];
        while(nextElement)
        {
            cout <<setw(3)<< nextElement->v<<":"<<nextElement->wei;
            nextElement = nextElement->next;
        }
        cout<<endl;
    }
}


void runAlgorithm(int algo)
{

    switch (algo)
    {
        case 1:
        {
            PrimMST prim{};

            startCounter();
            prim.runOnList(graphList,v,e);
            cout<<"Czas dzialania: "<<getCounter()<<endl<<endl;
            startCounter();
            prim.runOnMatrix(graphMatrix,v,e);
            cout<<"Czas dzialania: "<<getCounter()<<endl<<endl;
        }
            break;
        case 2:
        {
            KruskalMST kruskal{};

            startCounter();
            kruskal.runOnList(graphList,v,e);
            cout<<"Czas dzialania: "<<getCounter()<<endl<<endl;
            startCounter();
            kruskal.runOnMatrix(graphMatrix,v,e);
            cout<<"Czas dzialania: "<<getCounter()<<endl<<endl;
        }
            break;
        case 3:
        {
            int start,end;
            cout<<"Wierzcholek startowy: "<<endl;
            cin>> start;
            cout<<"Wierzcholek koncowy: "<<endl;
            cin >> end;
            Dijkstra dijkstra;
            startCounter();
            dijkstra.runOnList(graphList,v,e,start,end);
            cout<<"Czas dzialania: "<<getCounter()<<endl<<endl;
            startCounter();
            dijkstra.runOnMatrix(graphMatrix,v,e,start,end);
            cout<<"Czas dzialania: "<<getCounter()<<endl<<endl;
        }
            break;

        case 4:
        {
            int start,end;
            cout<<"Wierzcholek startowy: "<<endl;
            cin>> start;
            cout<<"Wierzcholek koncowy: "<<endl;
            cin >> end;
            BellmanFord bellmanFord;
            startCounter();
            bellmanFord.runOnList(graphList,v,e,start,end);
            cout<<"Czas dzialania: "<<getCounter()<<endl<<endl;
            startCounter();
            bellmanFord.runOnMatrix(graphMatrix,v,e,start,end);
            cout<<"Czas dzialania: "<<getCounter()<<endl<<endl;
        }
            break;


    }

}


