#include<iostream>
#include<stdlib.h>
#include <vector>
#include<list>
#include <algorithm>
#include <cmath>
#include<climits>


using namespace std;

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

class Maxheap{
    int *harr;  // pointer to array of elements in heap



public:
    int heapsize;   // number in heap
    // vector<vertex> graph;
    int heapcapacity;

    // initialize
    Maxheap(vector<vertex> input_graph);

    void Heapify(int i, vector<vertex> graph);

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

    void decreaseKey(int i, int new_val, vector<vertex> graph);

    int findIndex(int w);

    void insertKey(int k, vector<vertex> graph);

    void deleteKey(int k, vector<vertex> graph);

    void printHeap(vector<vertex> graph);
};

Maxheap::Maxheap(vector<vertex> input_graph){
    // graph = input_graph;
    heapsize = 0;

    heapcapacity = input_graph.size();
    harr = new int[heapcapacity];
    // cout<<"vector size"<<graph->size()<<endl;
}

void Maxheap::printHeap(vector<vertex> graph){
    cout<<"print heap!!! size="<<heapsize<<endl;
    for (int i = 0; i < heapsize; i++){
        cout<<graph[harr[i]].bw<<" ";
    }
    cout<<"vertex num: ";
    for (int i = 0; i < heapsize; i++){
        cout<<harr[i]<<" ";
    }
    cout<<endl;
}

// Inserts a new key 'k'
void Maxheap::insertKey(int k, vector<vertex> graph)
{


    if (heapsize == heapcapacity)
    {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }

    // First insert the new key at the end
    heapsize++;
    int i = heapsize - 1;
    harr[i] = k;
    graph[k].heapLoc = i; // for loca


    // cout<<"insert "<<graph[harr[parent(i)]].bw<<"> "<<graph[harr[i]].bw<<endl;
    while (i != 0 && graph[harr[parent(i)]].bw < graph[harr[i]].bw)
    {
        graph[harr[i]].heapLoc = parent(i);
        graph[harr[parent(i)]].heapLoc = i;
       swap(&harr[i], &harr[parent(i)]);

       i = parent(i);
    }
    // cout<<"～～～～～～insert "<<graph[harr[parent(i)]].bw<<"> "<<graph[harr[i]].bw<<endl;

};

// remove the root
int Maxheap::extractMax(vector<vertex> graph)
{
    if (heapsize <= 0){
        cout<<"No element in this heap!!!"<<endl;
        return INT_MAX;

    }

    if (heapsize == 1)
    {
        heapsize--;
        graph[harr[0]].heapLoc = -1;
        return harr[0];
    }

    // Store the max value, and remove it from heap
    int root = harr[0];
    graph[root].heapLoc = -1;
    harr[0] = harr[heapsize-1];
    graph[harr[0]].heapLoc = 0;
    heapsize--;
    Heapify(0, graph);

    return root;
}

void Maxheap::deleteKey(int i, vector<vertex> graph)
{
    decreaseKey(i, INT_MAX, graph);
    extractMax(graph);
}

void Maxheap::decreaseKey(int i, int new_val, vector<vertex> graph)
{
    // harr[i] = new_val;

    // int real_bw = graph[i].bw;
    // graph[i].bw = new_val;
    // while (i != 0 && harr[graph[parent(i)].bw] > harr[graph[i].bw])
    // {
    //    swap(&harr[i], &harr[parent(i)]);
    //    i = parent(i);
    // }
    // graph[i].bw = real_bw;

    while (i != 0)
    {
        graph[harr[i]].heapLoc = parent(i);
        graph[harr[parent(i)]].heapLoc = i;
       swap(&harr[i], &harr[parent(i)]);
       i = parent(i);
    }
}

void Maxheap::Heapify(int i, vector<vertex> graph){
    int l = left(i);
    int r = right(i);
    int largest = i;
    if (l < heapsize && graph[harr[l]].bw > graph[harr[i]].bw){
        largest = l;
    }
    if (r < heapsize && graph[harr[r]].bw > graph[harr[i]].bw){
        largest = r;
    }
    if (largest != i){
        graph[harr[i]].heapLoc = largest;
        graph[harr[largest]].heapLoc = i;
        swap(&harr[i], &harr[largest]);
        Heapify(largest, graph);
    }
}

int Maxheap::findIndex(int w){
    for (int i = 0; i < heapsize; i++){
        // cout<<"check "<<w<<" with "<<harr[i]<<endl;
        // cout<<(harr[i] == w)<<endl;
        if (harr[i] == w){
            return i;
        }
    }
    cout << "\nError: Could not find w's index!!!! w= "<<w<<endl;

    return -1;
}


// the function to swap two values
