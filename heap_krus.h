#include<iostream>
#include<stdlib.h>
#include <vector>
#include<list>
#include <algorithm>
#include <cmath>
#include<climits>


using namespace std;



class edgeMaxheap{

public:
    int heapsize;   // number in heap
    // vector<vertex> graph;

    vector<edge> edgeHeap;

    // initialize
    void edgeMaxheapInit(vector<edge>& Edge);

    int parent(int i) {
        int parent = (i-1)/2;
        if (parent < 0){
            parent = 0;
        }
        return parent;
    }

    // to get index of left child of node at index i
    int left(int i) { return (2*i + 1); }

    // to get index of right child of node at index i
    int right(int i) { return (2*i + 2); }

    // to extract the root which is the minimum element
    int extractMax(vector<vertex> graph);


    void BuildMaxHeap();

    void MaxHeapify(int i);

    void Heapsort();

    void swap(int a, int b);

    void Makeset(vector<vertex>&);

};

void edgeMaxheap::edgeMaxheapInit(vector<edge>& Edge){
    heapsize = Edge.size();
    edgeHeap = Edge;

}

void edgeMaxheap::BuildMaxHeap(){
    cout<<"the volum of edges: "<<edgeHeap.size()<<endl;
    for (int i = heapsize/2 - 1; i >= 0; i --){
        MaxHeapify(i);
    }
}

void edgeMaxheap::MaxHeapify(int i){
    int l = left(i);
    int r = right(i);
    int largest;
    if (l <= heapsize && edgeHeap[l].weight > edgeHeap[i].weight){
        largest = l;
    }
    else{
        largest = i;
    }

    if (r <= heapsize && edgeHeap[r].weight > edgeHeap[largest].weight){
        largest = r;
    }

    if (largest != i){
        swap(i, largest);
        MaxHeapify(largest);
    }
}

void edgeMaxheap::Heapsort(){
    BuildMaxHeap();

    for (int i = edgeHeap.size() - 1; i > 0; i--){
        swap(0, i);
        heapsize--;
        MaxHeapify(0);
    }
}

void edgeMaxheap::swap(int a, int b){
    edge temp = edgeHeap[b];
    edgeHeap[b] = edgeHeap[a];
    edgeHeap[a] = temp;
}

void edgeMaxheap::Makeset(vector<vertex>& graph){
    for (i = 0; i < graph.size(); i++){
        graph[i].parent = -1;
        graph[i].level = 0;
    }
}

int find(int v, vector<vertex>& graph){
    int w = v;
    while (graph[w].parent != -1){
        w = graph[w].parent;
    }
    return w;
}

void Union(int r1, int r2, vector<vertex>& graph){
    if (graph[r1].level > graph[r2].level){
        graph[r2].parent = r1;
    }
    else if (graph[r1].level < graph[r2].level){
        graph[r1].parent = r2;
    }
    else{
        graph[r1].parent = r2;
        graph[r2].level++;
    }

}

vector<int> DFS_findpath(vector<vertex>& mst, int s, int t, const vector<int> path, const int path_length){

    int copy_path_length = path_length;
    copy_path_length++;
    vector<int> copy_path = path;

    int bw = copy_path[0];
    cout<<"dfs in "<<copy_path_length<<" const "<<path_length<<endl;
    for (int i = 0; i < mst[s].neighbor.size(); i++){
        // wait
        int w = mst[s].neighbor[i];
        copy_path[0] = min(mst[s].weight[i], bw);
        copy_path[copy_path_length] = w;
        if (w == t){
            return copy_path;
        }

        DFS_findpath(mst, w, t, copy_path, copy_path_length);
    }
};

vector<vertex> Build_MST(vector<edge>& mst){
    vector<vertex> graph_mst;
    for (int i = 0; i < 2 * mst.size(); i++){
        vertex node;
        graph_mst.push_back(node);
    }

    for (i = 0; i < mst.size(); i++){
        edge newedge = mst[i];
        graph_mst[newedge.nodes[0]].weight.push_back(newedge.weight);
        graph_mst[newedge.nodes[0]].neighbor.push_back(newedge.nodes[1]);
        graph_mst[newedge.nodes[1]].weight.push_back(newedge.weight);
        graph_mst[newedge.nodes[1]].neighbor.push_back(newedge.nodes[0]);
    }

    return graph_mst;
}
// the function to swap two values
