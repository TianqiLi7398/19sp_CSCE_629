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

    int num_vertex = 5000;
    int average_degree = 6;
    float percantage = 0.2;
    vector<int> source;
    vector<int> target;

    for (int i = 1; i < 6; i++){
        source.push_back(i*10);
        target.push_back(i*3);
    }

    for (int j = 0; j < 11; j++){


    vector<edge> Edge;

    vector<vertex> graph_;
    /* Problem 1, generate 2 graphs */
    vector<vertex> graph = G1(num_vertex,average_degree, Edge);
    // vector<vertex> graph = G2(num_vertex, percantage, Edge);

    vector<vertex> graph3 = graph;
    cout<<j<<endl;

    printf("============================================");
    cout<<endl;
    printf("2.a path finding by using Dijkstra of array data structure's result: ");
    cout<<endl;
    auto start1 = high_resolution_clock::now();

    for (int k = 0; k < 5; k++ ){
        graph_ = graph;
        vector<int> path1 = Dijkstra(source[k], target[k], graph_);
    }
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1)/1000;
    cout<<"time spent on this method: "<<duration1.count()<<endl;


    printf("============================================");
    cout<<endl;

    cout<<"2.b path finding by using Dijkstra of heap data structure's result: ";
    cout<<endl;

    auto start2 = high_resolution_clock::now();
    for (int k = 0; k < 5; k++ ){
        graph_ = graph;
        vector<int> path1 = Dijkstra_heap(source[k], target[k], graph_);
    }

    auto stop2 = high_resolution_clock::now();

    auto duration2 = duration_cast<microseconds>(stop2 - start2)/1000;
    cout<<"time spent on this method: "<<duration2.count()<<endl;


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
    // get the max spanning tree




    // vector<vertex*> graph_mst = Build_MST(mst);
    // find the path from s to t by a DFS
    int bw = 100;
    vector<int> path_, path;
    for (int k = 0; k < 5; k++){
        vector<edge>mst_ = mst;
        vector<vertex*> graph_mst = Build_MST(mst_);
        path = path_;
        path.push_back(bw);
        path.push_back(source[k]);
        DFS_findpath(graph_mst, source[k],target[k], path);
    }


    auto stop3 = high_resolution_clock::now();
    // printVec(path_vec);
    auto duration3 = duration_cast<microseconds>(stop3 - start3)/1000;
    cout<<"time spent on this method: "<<duration3.count()<<endl;


}
    return 0;
}
