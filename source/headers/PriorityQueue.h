//
// Created by Silver on 04.06.2024.
//

#ifndef AIZO_GRAFY_PRIORITYQUEUE_H
#define AIZO_GRAFY_PRIORITYQUEUE_H

struct Edge
{
    int from;
    int to;
    int weight;

};

class PriorityQueue {
    Edge * PriorityHeap;
    int position;
    int capacity;
public:
    explicit PriorityQueue(int e);
    ~PriorityQueue();


    Edge first();
    void push(Edge e);
    void pop();
    void heapify(Edge *tab, int size, int i);


    bool isEmpty();

    void resize();
};


#endif //AIZO_GRAFY_PRIORITYQUEUE_H
