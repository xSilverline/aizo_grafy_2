//
// Created by Silver on 04.06.2024.
//

#include <iostream>
#include "../headers/PriorityQueue.h"
void heapify(Edge *tab, int size, int i);
PriorityQueue::PriorityQueue(int e)
{
    PriorityHeap = new Edge[e];
    position = 0;
}

Edge PriorityQueue::first() {
    return PriorityHeap[0];
}

bool PriorityQueue::isEmpty()
{
    if(position == 0)
    {
        return true;
    }
    else
        return false;
}

void PriorityQueue::push(Edge e)
{
    if(position == 0)
    {
        PriorityHeap[0] = e;
        position++;
        return;
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
    if(position)
    {
        position--;
        PriorityHeap[0] = PriorityHeap[position];
        heapify(PriorityHeap,position,0);
    }

//    std::cout<<"_____________"<<std::endl;
//    for(int i = 0; i< position;i++)
//    {
//        std::cout<<PriorityHeap[i].weight<<std::endl;
//    }
//    std::cout<<"_____________"<<std::endl;
}


void heapify(Edge *tab, int size, int i) //left 2i , right 2i+1 , parent i/2
{
    int l = 1+2*i; // index od 0
    int r = 2+2*i;
    int largest = i;

    if(l < size && tab[l].weight < tab[largest].weight)
        largest = l;
    if(r < size && tab[r].weight < tab[largest].weight)
        largest = r;

    if(largest != i)
    {
        Edge temp = tab[i];
        tab[i] = tab[largest];
        tab[largest] = temp;
        heapify(tab,size,largest);
    }


}

