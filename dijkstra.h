#include<iostream>
#include<stdlib.h>
#include <vector>
#include<list>
#include <algorithm>
#include <cmath>
#ifndef HEAP_DIJK_H
#define HEAP_DIJK_H
#endif
#ifndef GRAPH_H
#define GRAPH_H
#endif

int findMax(vector<int> queue){
    int index = 0;
    int max = queue[0];
    for (int i = 1; i < queue.size(); i++){
        if (max < queue[i]){
            max = queue[i];
            index = i;
        }
    }
    return index;
}


using namespace std;
int i;

vector<int> Dijkstra(int s, int t, vector<vertex>& graph){
    // initalize the Dijkstra

    vector<int> Queue_nodes;
    vector<int> Queue_bw;
    for (int i = 0; i< graph.size(); i++){
        graph[i].parent = -1;
        graph[i].bw = -1;
        graph[i].status = "unseen";
    }
    graph[s].status = "intree";
    graph[s].bw = 100; // a very large num

    // expand from s vertex;
    for (i = 0; i < graph[s].neighbor.size(); i ++){
        graph[graph[s].neighbor[i]].status = "fringe";
        graph[graph[s].neighbor[i]].bw = graph[s].weight[i];
        graph[graph[s].neighbor[i]].parent = s;
        Queue_nodes.push_back(graph[s].neighbor[i]);
        Queue_bw.push_back(graph[graph[s].neighbor[i]].bw);
    }

    // loop the answer
    while(Queue_nodes.size() > 0){
        // printVec(Queue_nodes);
        // find maxium Q and delete Q

        // int maxElementIndex = max_element(Queue_bw.begin(),Queue_bw.end()) - Queue_bw.begin(); // index of the the queue
        // int maxElement = *max_element(Queue_bw.begin(), Queue_bw.end()); // the max BW in the priority queue

        int maxElementIndex = findMax(Queue_bw);
        int v = Queue_nodes[maxElementIndex];

        graph[v].status = "intree";
        Queue_nodes.erase(Queue_nodes.begin() + maxElementIndex);
        Queue_bw.erase(Queue_bw.begin() + maxElementIndex);

        for (i = 0; i < graph[v].neighbor.size(); i++){
            int w = graph[v].neighbor[i];
            if (graph[w].status == "unseen"){
                graph[w].status = "fringe";
                graph[w].bw = min(graph[v].bw, graph[v].weight[i]);
                graph[w].parent = v;
                Queue_nodes.push_back(w);
                Queue_bw.push_back(graph[w].bw);
            }
            else if (graph[w].status == "fringe" && graph[w].bw < min(graph[v].bw, graph[v].weight[i])){
                graph[w].bw = min(graph[v].bw, graph[v].weight[i]);
                graph[w].parent = v;

            }
        }

        // update Queue_bw
        for (i = 0; i < Queue_nodes.size(); i++){
            Queue_bw[i] = graph[Queue_nodes[i]].bw;
        }


    }
    // output the result when finish updating the graph
    cout<<"The max bandwidth is "<<graph[t].bw<<endl;
    // find the path
    std::vector<int> path;
    path.push_back(t);
    path.insert(path.begin(), graph[t].parent);
    int ancestor = graph[t].parent;
    while(ancestor != s){
        ancestor = graph[ancestor].parent;
        path.insert(path.begin(), ancestor);
    }

    return  path;
}



vector<int> Dijkstra_heap(int s, int t, vector<vertex>& graph){
    for (int i = 0; i< graph.size(); i++){

        graph[i].parent = -1;
        graph[i].bw = -2;
        graph[i].status = "unseen";
    }

    graph[s].bw = 100; // a very large num
    graph[s].status = "intree";
    graph[s].heapLoc = -1;
    Maxheap Queue_nodes;
    Queue_nodes.initMaxheap(graph);

    // expand from s vertex;
    for (i = 0; i < graph[s].neighbor.size(); i++){

        graph[graph[s].neighbor[i]].bw = graph[s].weight[i];
        graph[graph[s].neighbor[i]].parent = s;
        graph[graph[s].neighbor[i]].status = "fringe";

        Queue_nodes.insertKey(graph[s].neighbor[i], graph);

    }


    // loop the answer
    while(Queue_nodes.heapsize > 0){
        // find maxium number in heap and delete

        int v = Queue_nodes.extractMax(graph);
        graph[v].status = "intree";

        for (i = 0; i < graph[v].neighbor.size(); i++){
            int w = graph[v].neighbor[i];
            if (graph[w].status == "unseen"){
                graph[w].status = "fringe";
                graph[w].bw = min(graph[v].bw, graph[v].weight[i]);
                graph[w].parent = v;

                // insert vertex to maxheap
                Queue_nodes.insertKey(w,graph);

            }
            else if (graph[w].status == "fringe" && graph[w].bw < min(graph[v].bw, graph[v].weight[i])){
                // find w index in the heaps needs to be update
                Queue_nodes.deleteKey(w, graph);
                graph[w].bw = min(graph[v].bw, graph[v].weight[i]);
                graph[w].parent = v;
                Queue_nodes.insertKey(w, graph);

            }
        }

    }


    // output the result when finish updating the graph

    cout<<"The max bandwidth is "<<graph[t].bw<<endl;
    // find the path
    std::vector<int> path;
    path.push_back(t);
    path.insert(path.begin(), graph[t].parent);
    int ancestor = graph[t].parent;
    while(ancestor != s){
        ancestor = graph[ancestor].parent;

        path.insert(path.begin(), ancestor);
    }

    return path;

}
