#include <iostream>
#include <iomanip>
#include "../headers/allheaders.h"
#include <chrono>

using namespace std;

void showMenu(int problem);
void readData(int p);
void generateGraph(int p);
void printGraph();
void runAlgorithm(int algo);

listElement ** graphList = nullptr;
int ** graphMatrix = nullptr;
int e,v,density;


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
        else if(action == 3)
        {
            Tester tester;
            tester.beginTest();
        }
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
            cout<< "1. Wczytaj dane z pliku\n2. Wygeneruj graf losowo\n3. Wyswietl graf listowo i macierzowo na ekranie\n4. Algorytm Prima\n5. Algorytm Kruskala"<< endl;
            cin >> action;
        }
        else if(problem == 2)
        {
            cout<< "1. Wczytaj dane z pliku\n2. Wygeneruj graf losowo\n3. Wyswietl graf listowo i macierzowo na ekranie\n4. Algorytm Dijkstry\n5. Algorytm Bellmana-Forda"<< endl;
            cin >> action;
            if(action > 3)
                action+=2;
        }
        else
            return;

        if(action > 2 && (graphMatrix == nullptr || graphList == nullptr))
            action = 8;




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
            case 8:
                cout<<"Brak danych ! Wygeneruj nowe dane!"<<endl;
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

    e = generator.getEdgeNumber();
//    cout<<"Edges after del: "<<e<<endl<<endl;

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
    {    cout<<setw(3)<<i<<" |";
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

    cout<<graphMatrix[0][e-1];
}


void runAlgorithm(int algo)
{

    switch (algo)
    {
        case 1:
        {
            PrimMST prim{};
            prim.runOnList(graphList,v,e,true);
            prim.runOnMatrix(graphMatrix,v,e,true);

        }
            break;
        case 2:
        {
            KruskalMST kruskal{};
            kruskal.runOnList(graphList,v,e,true);
            kruskal.runOnMatrix(graphMatrix,v,e,true);
        }
            break;
        case 3:
        {
            int start,end;
            while(true)
            {
                cout<<"Wierzcholek startowy: "<<endl;
                cin>> start;
                cout<<"Wierzcholek koncowy: "<<endl;
                cin >> end;
                if(start < 0 || end < 0 || start > v-1 || end > v-1)
                    cout<<"Bledny wierzcholek! Start i end powinny być z zakresu [0,"<<v-1<<"] ! "<<endl<<endl;
                else
                    break;
            }

            Dijkstra dijkstra;
            dijkstra.runOnList(graphList,v,e,start,end,true);
            dijkstra.runOnMatrix(graphMatrix,v,e,start,end,true);
        }
            break;

        case 4:
        {
            int start,end;
            while(true)
            {
                cout<<"Wierzcholek startowy: "<<endl;
                cin>> start;
                cout<<"Wierzcholek koncowy: "<<endl;
                cin >> end;
                if(start < 0 || end < 0 || start > v-1 || end > v-1)
                    cout<<"Bledny wierzcholek! Start i end powinny być z zakresu [0,"<<v-1<<"] ! "<<endl<<endl;
                else
                    break;
            }
            BellmanFord bellmanFord;
            bellmanFord.runOnList(graphList,v,e,start,end,true);
            bellmanFord.runOnMatrix(graphMatrix,v,e,start,end,true);
        }
            break;


    }

}


