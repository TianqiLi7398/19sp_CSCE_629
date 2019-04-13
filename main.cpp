#include "graph.h"
#include "heap_dijk.h"
#include "dijkstra.h"
#include "heap_krus.h"

#include<iostream>
#include<stdlib.h>
#include <vector>
#include<list>
#include <algorithm>
#include <cmath>
using namespace std;

// int i;



int main()
{
    int num_vertex = 500;
    int average_degree = 6;
    float percantage = 0.2;
    vector<edge> Edge;

    int s = 11;
    int t = 30;
    /* Problem 1, generate 2 graphs */
    vector<vertex> graph = G1(num_vertex,average_degree, Edge);
    // vector<vertex> graph = G2(num_vertex, percantage);
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
    cout<<"total edges are "<<num_degree<<" = "<<Edge.size();



    // Problem 2.a, use Dijkstra to find path of MB

    // printf("============================================");
    // cout<<endl;
    // printf("2.a path finding by using Dijkstra of array data structure's result: ");
    // vector<int> path1 = Dijkstra(s, t, graph1);
    //
    // printf("path found: ");
    // printVec(path1);
    // cout<<endl;
    //
    //
    // // Problem 2.b, applying heap data structure to decrase time complexity of
    // // Dijkstra ALG.
    // //
    // printf("============================================");
    // cout<<endl;
    //
    // cout<<"2.b path finding by using Dijkstra of heap data structure's result: ";
    // vector<int> path2 = Dijkstra_heap(s, t, graph2);
    // printf("path found: ");
    // printVec(path2);
    // cout<<endl;
    //
    // // Problem 2.c, applying Kruskal's algorithm to get MST and then find the path
    // //
    // printf("============================================");
    edgeMaxheap edgeHeap;
    edgeHeap.edgeMaxheapInit(Edge);
    edgeHeap.Heapsort();
    // for (i = 0; i < edgeHeap.edgeHeap.size(); i++){
    //     cout<<edgeHeap.edgeHeap[i].weight<<" ";
    // }
    cout<<endl;

    edgeHeap.Makeset(graph);
    vector<edge> mst;

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

    vector<vertex> graph_mst = Build_MST(mst);

    // find the path from s to t
    int bw = 100;
    int path_length = 0;
    vector<int> path(graph.size() + 1);
    path[0] = bw;
    cout<<"everything all right before calculation "<<path.size()<<" "<<endl;
    vector<int> pathKrus = DFS_findpath(graph_mst, s,t, path, path_length);
    cout<<"finish??"<<endl;
    printVec(pathKrus);






    return 0;
}
