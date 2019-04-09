#include<iostream>
#include<stdlib.h>
#include <vector>
#include<list>
#include <algorithm>
#include <cmath>


using namespace std;


class vertex{
public:
    std::vector<int> neighbor;
    std::vector<int> weight;
    int bw;
    int parent;
    string status;
    int heapLoc;
};

void printVec(std::vector<int> const &input)
{
    for (int i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << ' ';
    }
};

void printGraph(vector<vertex> graph){
    for (int i = 0; i < graph.size(); i++){
        cout<< "vertex" <<i<<"  neighbors:";
        printVec(graph[i].neighbor);
        cout<< "   weights:";
        printVec(graph[i].weight);
        cout<<endl;
    }
}

void makeEdge(vector<vertex>& graph, int a, int b){
    graph[a].neighbor.push_back(b);
    graph[b].neighbor.push_back(a);
    int weight = random()%10;
    graph[a].weight.push_back(weight);
    graph[b].weight.push_back(weight);

}

// generate the sparse graph
vector<vertex> G1(int nov, int average_degree){
    std::vector<vertex> graph;
    // initialize the vertices and make a circle
    vertex Avertex;
    graph.push_back(Avertex);
    for (int i = 1; i < nov; i++){
        vertex Avertex;
        graph.push_back(Avertex);
        // make edge for i-1 and i
        makeEdge(graph, i-1, i);

    }
    makeEdge(graph, 0, nov-1);

    // after a circle is generated, the # of rest edges to create is
    int num_edges = (average_degree - 2) * nov / 2;
    while(num_edges != 0){
        // randomly selected 2 vertices to create edges
        int a = random()%nov;
        int b = random()%nov;
        if (a == b){
            if(a == 0){
                b = 1;
            }
            else{
                b = a - 1;
            }
        }
        if (find(graph[a].neighbor.begin(), graph[a].neighbor.end(), b) != graph[a].neighbor.end()){
            // contains b, means this edges are added
            continue;
        }
        else{
            makeEdge(graph, a, b);
            num_edges--;
        }

    }
    return graph;
};

vector<vertex> G2(int nov, float percantage){
    std::vector<vertex> graph;
    // initialize the vertices and make a circle
    vertex Avertex;
    graph.push_back(Avertex);
    for (int i = 1; i < nov; i++){
        vertex Avertex;
        graph.push_back(Avertex);
        // make edge for i-1 and i
        makeEdge(graph, i-1, i);

    }
    makeEdge(graph, 0, nov-1);

    // after the circle is generated, for each vertex it should have percantage% * nov neighbors
    int edge_num = floor(percantage * nov);
    for (int i = 0; i < nov; i++){
        int edge_num = floor(percantage * nov);
        while (edge_num - graph[i].neighbor.size() != 0){
            int a = random()%nov;

            if (a == i){
                if(a == 0){
                    a = 1;
                }
                else{
                    a = i - 1;
                }
            }
            if (find(graph[a].neighbor.begin(), graph[a].neighbor.end(), i) != graph[a].neighbor.end()){
                // contains b, means this edges are added
                continue;
            }
            else if (graph[a].neighbor.size() > floor((percantage + 0.1) * nov)){
                continue;
            }
            else{
                makeEdge(graph, a, i);
                // edge_num--;
            }
        }
    }


    return graph;
};
