#include<iostream>
#include<stdlib.h>
#include <vector>
#include<list>
#include <algorithm>
#include <cmath>
#include<climits>


using namespace std;



class Maxheap{

public:

    int heapsize;   // number in heap
    // vector<vertex> graph;
    int heapcapacity;

    vector<int> harr;
    // initialize
    void initMaxheap(vector<vertex> input_graph);

    int parent(int i) {
        int parent = (i-1)/2;
        if (parent < 0){
            parent = 0;
        }
        return parent;
    }

    // to get index of left child of node at index i
    int left(int i) {
        return (2*i + 1);
    }

    // to get index of right child of node at index i
    int right(int i) {
        return (2*i + 2);
    }

    // to extract the root which is the minimum element
    int extractMax(vector<vertex>& graph);


    int findIndex(int w);

    void insertKey(int k, vector<vertex>& graph);


    void printHeap(vector<vertex>& graph);

    void deleteKey(int k, vector<vertex>& graph);

    void swap(int x, int y);
};

void Maxheap::initMaxheap(vector<vertex> input_graph){
    // graph = input_graph;
    heapsize = 0;

    heapcapacity = input_graph.size();

    // harr = new int[heapcapacity];
    for (int i = 0; i<heapcapacity; i++){
        harr.push_back(-3);
    }
    // vector<int> harr(heapcapacity, 0);

}

void Maxheap::printHeap(vector<vertex>& graph){
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

// Inserts a new vertex
void Maxheap::insertKey(int k, vector<vertex>& graph)
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

    // update the new key's location
    graph[k].heapLoc = i;


    // heapify the newly inserted vertex upwards (compare with parents)
    while (i != 0 && graph[harr[parent(i)]].bw < graph[harr[i]].bw)
    {
        graph[harr[i]].heapLoc = parent(i);
        graph[harr[parent(i)]].heapLoc = i;
        swap(i, parent(i));

        i = parent(i);
    }


};

// delete the vertex v in tree
void Maxheap::deleteKey(int v, vector<vertex>& graph){
    // check if the heap is empty
    if (heapsize == 1){
        graph[v].heapLoc = -1;
        heapsize--;
    }
    else{

        // here v is the vertex name, first we need to find its index in heap
        int index = graph[v].heapLoc;
        if (index == -1){
            cout<<"error!!!!"<<endl;
        }


        graph[harr[heapsize - 1]].heapLoc = index;

        swap(index, heapsize - 1);
        harr[heapsize-1] = -3;
        heapsize--;


        // heapify the newly deleted vertex
        if (index > 0 && graph[harr[index]].bw > graph[harr[parent(index)]].bw){
            // a large number inserted, go up to swap with the parent
            while (index > 0 && graph[harr[index]].bw > graph[harr[parent(index)]].bw){

                graph[harr[index]].heapLoc = parent(index);
                graph[harr[parent(index)]].heapLoc = index;
                // swap(&harr[index], &harr[parent(index)]);
                swap(index, parent(index));
                index = parent(index);

            }
        }
        else{
            // a small number inserted, go up to swap with children
            while ((right(index) == heapsize && graph[harr[index]].bw < graph[harr[left(index)]].bw) || (right(index) < heapsize && graph[harr[index]].bw < max(graph[harr[left(index)]].bw, graph[harr[right(index)]].bw)) ){
                // when left or right children is larger than the vertex
                if (left(index) == heapsize - 1|| graph[harr[left(index)]].bw > graph[harr[right(index)]].bw){
                    // left children is larger

                    graph[harr[index]].heapLoc = left(index);
                    graph[harr[left(index)]].heapLoc = index;
                    swap(index, left(index));
                    index = left(index);
                }
                else{

                    // right children is larger
                    graph[harr[index]].heapLoc = right(index);
                    graph[harr[right(index)]].heapLoc = index;
                    swap(index, right(index));
                    index = right(index);
                }

            }
        }
        graph[v].heapLoc = -1;

    }



}

// remove the root
int Maxheap::extractMax(vector<vertex>& graph)
{

    if (heapsize <= 0){
        cout<<"No element in this heap!!!"<<endl;
        return INT_MAX;

    }
    // return the root vertex, and then delete this vertex
    int root = harr[0];

    deleteKey(root, graph);

    return root;
}

int Maxheap::findIndex(int w){
    for (int i = 0; i < heapsize; i++){
        if (harr[i] == w){
            return i;
        }
    }
    cout << "\nError: Could not find w's index!!!! w= "<<w<<endl;

    return -1;
}

void Maxheap::swap(int x, int y)
{
    //swap 2 vertices in the heap tree
    int temp = harr[x];
    harr[x] = harr[y];
    harr[y] = temp;
}
