//
// Created by Silver on 04.06.2024.
//

#include <iostream>
#include "../headers/PriorityQueue.h"

int edges;
PriorityQueue::PriorityQueue(int e)
{
    PriorityHeap = new Edge[e];
    capacity = e;
    position = 0;
    edges = e;
}
PriorityQueue::~PriorityQueue()
{
//    PriorityHeap = nullptr;
//    for(int i=0;i<edges;i++)
//    {
//        delete PriorityHeap[i];
//    }
//    std::cerr << position << std::endl;
    delete [] PriorityHeap;

}

Edge PriorityQueue::first()
{
    if (isEmpty()) {
//        std::cerr << "PriorityQueue is empty, cannot fetch first element!" << std::endl;
        return Edge{};
    }
    return PriorityHeap[0];
}

bool PriorityQueue::isEmpty()
{
    return position == 0;
}

void PriorityQueue::resize() {
    int newCapacity = capacity * 2;
    Edge* newHeap = new Edge[newCapacity];
    for (int i = 0; i < position; i++) {
        newHeap[i] = PriorityHeap[i];
    }
    delete[] PriorityHeap;
    PriorityHeap = newHeap;
    capacity = newCapacity;
}

void PriorityQueue::push(Edge e)
{
    if (position >= capacity) {
//        std::cerr << "PriorityQueue overflow, cannot push new element! - "<<position << std::endl;
//        return;
        resize();
    }

    PriorityHeap[position] = e;
    position++;

    for(int i = position/2 -1; i>=0;i--)
        heapify(PriorityHeap,position,i);

//    std::cout<<"_____________"<<std::endl;
//    for(int i = 0; i< position;i++)
//    {
//        std::cout<<PriorityHeap[i].weight<<std::endl;
//    }
//    std::cout<<"_____________"<<std::endl;



}

void PriorityQueue::pop()
{
    if (isEmpty()) {
//        std::cerr << "PriorityQueue is empty, cannot pop element!" << std::endl;
        return;
    }
        position--;
        PriorityHeap[0] = PriorityHeap[position];
        heapify(PriorityHeap,position,0);

//    std::cout<<"_____________"<<std::endl;
//    for(int i = 0; i< position;i++)
//    {
//        std::cout<<PriorityHeap[i].weight<<std::endl;
//    }
//    std::cout<<"_____________"<<std::endl;
}



void PriorityQueue::heapify(Edge *tab, int size, int i) //left 2i , right 2i+1 , parent i/2
{
    int l = 1+2*i; // index od 0
    int r = 2+2*i;
    int smallest = i;

    if(l < size && tab[l].weight < tab[smallest].weight)
        smallest = l;
    if(r < size && tab[r].weight < tab[smallest].weight)
        smallest = r;

    if(smallest != i)
    {
        Edge temp = tab[i];
        tab[i] = tab[smallest];
        tab[smallest] = temp;
        PriorityQueue::heapify(tab,size,smallest);
    }


}

