//
// Created by Silver on 04.06.2024.
//

#ifndef AIZO_GRAFY_PRIORITYQUEUE_H
#define AIZO_GRAFY_PRIORITYQUEUE_H

struct Edge
{
    int from=-1;
    int to=-1;
    int weight=-1;

};

class PriorityQueue {
public:
    PriorityQueue(int e);
    Edge * PriorityHeap;
    int position;
    Edge first();
    void push(Edge e);
    void pop();


    bool isEmpty();
};


#endif //AIZO_GRAFY_PRIORITYQUEUE_H
