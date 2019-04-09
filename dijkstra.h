#include<iostream>
#include<stdlib.h>
#include <vector>
#include<list>
#include <algorithm>
#include <cmath>
#ifndef HEAP_H
#define HEAP_H
#endif
#ifndef GRAPH_H
#define GRAPH_H
#endif



using namespace std;
int i;

vector<int> Dijkstra(int s, int t, vector<vertex> graph){
    // initalize the Dijkstra
    // vector<int> parent;
    // vector<string> status;
    // vector<int> bw;
    vector<int> Queue_nodes;
    vector<int> Queue_bw;
    for (int i = 0; i< graph.size(); i++){
        // status.push_back("unseen");
        // parent.push_back(-1);
        // bw.push_back(-1);
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
        // find maxium Q and delete Q

        // printVec(Queue_bw);
        // cout<<endl;
        // printVec(Queue_nodes);
        // cout<<endl;

        int maxElementIndex = max_element(Queue_bw.begin(),Queue_bw.end()) - Queue_bw.begin(); // index of the the queue
        int maxElement = *max_element(Queue_bw.begin(), Queue_bw.end()); // the max BW in the priority queue

        int v = Queue_nodes[maxElementIndex];
        // cout<<"selected vertex "<<v<<" with bw: "<<graph[v].bw<<endl;

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

                // TODO how to update bw value in priority Queue???
            }
        }

        // update Queue_bw
        for (i = 0; i < Queue_nodes.size(); i++){
            Queue_bw[i] = graph[Queue_nodes[i]].bw;
        }


    }

    // find the path
    cout<<"The max bandwidth is "<<graph[t].bw<<endl;
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


vector<int> Dijkstra_heap(int s, int t, vector<vertex> graph){
    // initalize the Dijkstra


    for (int i = 0; i< graph.size(); i++){

        graph[i].parent = -1;
        graph[i].bw = -1;
        graph[i].status = "unseen";
    }

    graph[s].bw = 100; // a very large num
    graph[s].status = "intree";
    Maxheap Queue_nodes(graph);

    // expand from s vertex;
    for (i = 0; i < graph[s].neighbor.size(); i++){

        graph[graph[s].neighbor[i]].bw = graph[s].weight[i];
        graph[graph[s].neighbor[i]].parent = s;
        graph[graph[s].neighbor[i]].status = "fringe";
        Queue_nodes.insertKey(graph[s].neighbor[i], graph);
        // Queue_bw.push_back(bw[graph[s].neighbor[i]]);
    }

    // test the bw after initialization
    // Queue_nodes.printHeap(graph);
    // cout<<"capacity: "<<Queue_nodes.heapcapacity<<", size = "<<Queue_nodes.heapsize<<endl;

    // loop the answer
    while(Queue_nodes.heapsize > 0){
        // find maxium Q and delete Q

        int v = Queue_nodes.extractMax(graph);
        // cout<<"select the biggest bw: "<<v<<endl;
        // Queue_nodes.deleteKey(0, graph);
        graph[v].status = "intree";
        // cout<<"capacity: "<<Queue_nodes.heapcapacity<<", size = "<<Queue_nodes.heapsize<<endl;


        for (i = 0; i < graph[v].neighbor.size(); i++){
            int w = graph[v].neighbor[i];
            if (graph[w].status == "unseen"){
                graph[w].status = "fringe";
                graph[w].bw = min(graph[v].bw, graph[v].weight[i]);
                graph[w].parent = v;

                // insert vertex to maxheap
                Queue_nodes.insertKey(w,graph);
                // cout<<"====insert "<<w<<"from unseen"<<endl;
                // cout<<"capacity: "<<Queue_nodes.heapcapacity<<", size = "<<Queue_nodes.heapsize<<endl;

            }
            else if (graph[w].status == "fringe" && graph[w].bw < min(graph[v].bw, graph[v].weight[i])){
                // find w index in the heaps
                int index_ = Queue_nodes.findIndex(w);
                Queue_nodes.deleteKey(index_, graph);//TODO
                graph[w].bw = min(graph[v].bw, graph[v].weight[i]);
                graph[w].parent = v;
                Queue_nodes.insertKey(w, graph);
                // TODO how to update bw value in priority Queue???
                // cout<<"====reinsert "<<w<<"from fringe"<<endl;
                // cout<<"capacity: "<<Queue_nodes.heapcapacity<<", size = "<<Queue_nodes.heapsize<<endl;

            }
        }

        // update Queue_bw
        // Queue_nodes.printHeap(graph);


    }




    // find the path
    cout<<"The max bandwidth is "<<graph[t].bw<<endl;
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


vector<int> Dijkstra_heap_rev(int s, int t, vector<vertex> graph){
    // initalize the Dijkstra


    for (int i = 0; i< graph.size(); i++){

        graph[i].parent = -1;
        graph[i].bw = -1;
        graph[i].status = "unseen";
    }

    graph[s].bw = 100; // a very large num
    graph[s].status = "intree";
    Maxheap Queue_nodes(graph);

    // expand from s vertex;
    for (i = 0; i < graph[s].neighbor.size(); i++){

        graph[graph[s].neighbor[i]].bw = graph[s].weight[i];
        graph[graph[s].neighbor[i]].parent = s;
        graph[graph[s].neighbor[i]].status = "fringe";
        graph[graph[s].neighbor[i]].heapLoc = i;
        Queue_nodes.insertKey(graph[s].neighbor[i], graph);
        // Queue_bw.push_back(bw[graph[s].neighbor[i]]);
    }

    // test the bw after initialization
    // Queue_nodes.printHeap(graph);
    // cout<<"capacity: "<<Queue_nodes.heapcapacity<<", size = "<<Queue_nodes.heapsize<<endl;

    // loop the answer
    while(Queue_nodes.heapsize > 0){
        // find maxium Q and delete Q

        int v = Queue_nodes.extractMax(graph);
        // cout<<"select the biggest bw: "<<v<<endl;
        // Queue_nodes.deleteKey(0, graph);
        graph[v].status = "intree";
        // cout<<"capacity: "<<Queue_nodes.heapcapacity<<", size = "<<Queue_nodes.heapsize<<endl;


        for (i = 0; i < graph[v].neighbor.size(); i++){
            int w = graph[v].neighbor[i];
            if (graph[w].status == "unseen"){
                graph[w].status = "fringe";
                graph[w].bw = min(graph[v].bw, graph[v].weight[i]);
                graph[w].parent = v;

                // insert vertex to maxheap
                Queue_nodes.insertKey(w,graph);
                // cout<<"====insert "<<w<<"from unseen"<<endl;
                // cout<<"capacity: "<<Queue_nodes.heapcapacity<<", size = "<<Queue_nodes.heapsize<<endl;

            }
            else if (graph[w].status == "fringe" && graph[w].bw < min(graph[v].bw, graph[v].weight[i])){
                // find w index in the heaps
                // int index_ = Queue_nodes.findIndex(w);
                int index_ = graph[w].heapLoc;
                
                Queue_nodes.deleteKey(index_, graph);//TODO
                graph[w].bw = min(graph[v].bw, graph[v].weight[i]);
                graph[w].parent = v;
                Queue_nodes.insertKey(w, graph);
                // TODO how to update bw value in priority Queue???
                // cout<<"====reinsert "<<w<<"from fringe"<<endl;
                // cout<<"capacity: "<<Queue_nodes.heapcapacity<<", size = "<<Queue_nodes.heapsize<<endl;

            }
        }

        // update Queue_bw
        // Queue_nodes.printHeap(graph);


    }




    // find the path
    cout<<"The max bandwidth is "<<graph[t].bw<<endl;
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
