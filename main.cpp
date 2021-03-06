#include "graph.h"
#include "heap_dijk.h"
#include "dijkstra.h"
#include "heap_krus.h"
#include <chrono>  // for timing
#include<iostream>
#include<stdlib.h>
#include <vector>
#include<list>
#include <algorithm>
#include <cmath>
#include<stack>
#include <ctime>


using namespace std;
using namespace std::chrono;



int main()
{
    int s,t;
    s = 5;
    t = 100;
    int num_vertex = 5000;
    int average_degree = 6;
    float percantage = 0.2;
    vector<int> source;
    vector<int> target;
    for (int i = 1; i < 6; i++){
        source.push_back(i*10);
        target.push_back(i*300);
    }




    vector<edge> Edge;


    /* Problem 1, generate 2 graphs */
    vector<vertex> graph = G1(num_vertex,average_degree, Edge);
    // vector<vertex> graph = G2(num_vertex, percantage, Edge);
    vector<vertex> graph1 = graph;
    vector<vertex> graph2 = graph;
    vector<vertex> graph3 = graph;
    // vector<vertex> graph = G2(num_vertex, percantage);
    // printGraph(graph2);
    cout<<"graph built!"<<endl;
    cout<<"edge size"<<Edge.size()<<endl;
    // check neighbor number
    int num_degree = 0;
    for (i = 0; i < num_vertex; i++){
        num_degree += graph3[i].neighbor.size();
    }


    // Problem 2.a, use Dijkstra to find path of MB

    printf("============================================");
    cout<<endl;
    printf("2.a path finding by using Dijkstra of array data structure's result: ");
    cout<<endl;
    auto start1 = high_resolution_clock::now();

    vector<int> path1 = Dijkstra(s, t, graph1);

    auto stop1 = high_resolution_clock::now();

    printf("path found: ");
    printVec(path1);
    cout<<endl;
    auto duration = duration_cast<microseconds>(stop1 - start1);
    cout<<"time spent on this method: "<<duration.count()<<endl;


    // Problem 2.b, applying heap data structure to decrase time complexity of
    // Dijkstra ALG.

    printf("============================================");
    cout<<endl;

    cout<<"2.b path finding by using Dijkstra of heap data structure's result: ";
    cout<<endl;

    auto start2 = high_resolution_clock::now();

    vector<int> path2 = Dijkstra_heap(s, t, graph2);

    auto stop2 = high_resolution_clock::now();

    printf("path found: ");
    printVec(path2);
    cout<<endl;

    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    cout<<"time spent on this method: "<<duration2.count()<<endl;




    // Problem 2.c, applying Kruskal's algorithm to get MST and then find the path
    printf("============================================");
    cout<<endl;

    cout<<"2.c path finding by using Kruskal MST result: ";

    auto start3 = high_resolution_clock::now();
    // initalize the heap and heapsort
    edgeMaxheap edgeHeap;
    edgeHeap.edgeMaxheapInit(Edge);
    edgeHeap.Heapsort();

    // save the selected edges
    edgeHeap.Makeset(graph);
    vector<edge> mst;

    // Kruskal's ALG
    for (i = edgeHeap.edgeHeap.size()-1; i >=0; i--){
        edge r12 = edgeHeap.edgeHeap[i];
        int v1 = edgeHeap.edgeHeap[i].nodes[0];
        int v2 = edgeHeap.edgeHeap[i].nodes[1];
        int r1 = find(v1, graph);
        int r2 = find(v2, graph);
        if (r1 != r2){
            Union(r1, r2, graph);
            mst.push_back(r12);
        }
    }
    cout<<"size of mst:"<<mst.size()<<endl;
    // get the max spanning tree

    vector<vertex*> graph_mst = Build_MST(mst);

    // find the path from s to t by a DFS
    int bw = 100;

    vector<int> path;
    path.push_back(bw);
    path.push_back(s);
    DFS_findpath(graph_mst, s,t, path);

    auto stop3 = high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(stop3 - start3);
    // printVec(path_vec);
    cout<<"time spent on this method: "<<duration3.count()<<endl;


    return 0;
}
