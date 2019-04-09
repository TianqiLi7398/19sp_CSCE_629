#include "graph.h"
#include "heap.h"
#include "dijkstra.h"


#include<iostream>
#include<stdlib.h>
#include <vector>
#include<list>
#include <algorithm>
#include <cmath>
using namespace std;



int main()
{
    int num_vertex = 5000;
    int average_degree = 6;
    float percantage = 0.2;

    int s = 11;
    int t = 3;
    /* Problem 1, generate 2 graphs */
    vector<vertex> graph = G1(num_vertex,average_degree);
    vector<vertex> graph2 = graph;
    vector<vertex> graph1 = graph;
    // vector<vertex> graph = G2(num_vertex, percantage);
    // printGraph(graph2);

    // check neighbor number
    int num_degree = 0;
    for (i = 0; i < num_vertex; i++){
        num_degree += graph[i].neighbor.size();
    }
    cout<<"average degree is "<<num_degree / num_vertex<<endl;



    // Problem 2.a, use Dijkstra to find path of MB

    printf("============================================");
    cout<<endl;
    printf("2.a path finding by using Dijkstra of array data structure's result: ");
    vector<int> path1 = Dijkstra(s, t, graph1);

    printf("path found: ");
    printVec(path1);
    cout<<endl;


    // Problem 2.b, applying heap data structure to decrase time complexity of
    // Dijkstra ALG.
    //
    printf("============================================");
    cout<<endl;
    printf("2.b path finding by using Dijkstra of heap data structure's result: ");
    vector<int> path2 = Dijkstra_heap(s, t, graph2);
    printf("path found: ");
    printVec(path2);
    cout<<endl;




    return 0;
}
