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


// the function to swap two values
