////
//// Created by Silver on 10.06.2024.
////
//
//#include "../headers/BellmanFord.h"
//
//#include <iostream>
//#include <vector>
//#include <list>
//#include <iomanip>
//#include <limits>
//
//using namespace std;
//
//
//
//
//struct Edge {
//    int from, to, weight;
//};
//
//
//
//void BellmanFord::runOnMatrix(int** graphMatrix, int v, int e, int start, int end) {
//    vector<int> cost(v, MAXINT);
//    vector<int> prev(v, -1);
//    vector<Edge> edges;
//
//    // Convert graph matrix to edge list
//    for (int i = 0; i < v; i++) {
//        for (int j = 0; j < e; j++) {
//            if (graphMatrix[i][j] != 0) {
//                Edge edge = {i, j, graphMatrix[i][j]};
//                edges.push_back(edge);
//            }
//        }
//    }
//
//    cost[start] = 0;
//
//    // Relax edges |V|-1 times
//    for (int i = 0; i < v - 1; i++) {
//        for (const Edge& edge : edges) {
//            if (cost[edge.from] != MAXINT && cost[edge.from] + edge.weight < cost[edge.to]) {
//                cost[edge.to] = cost[edge.from] + edge.weight;
//                prev[edge.to] = edge.from;
//            }
//        }
//    }
//
//    // Check for negative weight cycles
//    for (const Edge& edge : edges) {
//        if (cost[edge.from] != MAXINT && cost[edge.from] + edge.weight < cost[edge.to]) {
//            cerr << "Graph contains a negative weight cycle" << endl;
//            return;
//        }
//    }
//
//    // Print result
//    int current = end;
//    while (current != start && current != -1) {
//        cout << "From: " << prev[current] << " To: " << current << " Weight: " << cost[current] << endl;
//        current = prev[current];
//    }
//
//    cout << "Total weight from " << start << " to " << end << " is " << cost[end] << endl;
//
//    // Clean up
//    // (no dynamic allocation used in this version)
//}
//
//
//
//
//void BellmanFord::runOnList(listElement** graphList, int v, int e, int start, int end) {
//
//    int * cost = new int[v];
//    int * prev = new int[v];
//    vector<Edge> edges;
//
//    // Convert graph list to edge list
//    for (int i = 0; i < v; i++) {
//        listElement* next = graphList[i];
//        while (next) {
//            Edge edge = {i, next->v, next->wei};
//            edges.push_back(edge);
//            next = next->next;
//        }
//    }
//
//    cost[start] = 0;
//
//    // Relax edges |V|-1 times
//    for (int i = 0; i < v - 1; i++) {
//        for (const Edge& edge : edges) {
//            if (cost[edge.from] != MAXINT && cost[edge.from] + edge.weight < cost[edge.to]) {
//                cost[edge.to] = cost[edge.from] + edge.weight;
//                prev[edge.to] = edge.from;
//            }
//        }
//    }
//
//    // Check for negative weight cycles
//    for (const Edge& edge : edges) {
//        if (cost[edge.from] != MAXINT && cost[edge.from] + edge.weight < cost[edge.to]) {
//            cerr << "Graph contains a negative weight cycle" << endl;
//            return;
//        }
//    }
//
//    // Print result
//    int current = end;
//    while (current != start && current != -1) {
//        cout << "From: " << prev[current] << " To: " << current << " Weight: " << cost[current] << endl;
//        current = prev[current];
//    }
//
//    cout << "Total weight from " << start << " to " << end << " is " << cost[end] << endl;
//
//    // Clean up
//    // (no dynamic allocation used in this version)
//}
