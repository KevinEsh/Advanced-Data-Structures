#ifndef GRAPH
#define GRAPH

#include <bits/stdc++.h>
#include <vector>
#include <bitset>
#include <string>
#define MAX_BITS (1 << 20)

typedef std::vector<std::bitset<MAX_BITS>> vectorbit;
typedef std::vector<std::vector<int>> vvectorint;

class Graph
{
private:
    vectorbit marked;
    vvectorint adjlist;
    int size; //number of nodes
    bool directed;
    void raise_invalid_node(int);

public:
    Graph(bool);
    ~Graph();
    void add_node(int);
    void add_edge(int, int);
    std::vector<int> nodes();
    std::vector<int> edges(int);
}

Graph::Graph(bool _directed)
    : directed(_directed)
{
    size = 0;
}

Graph::~Graph()
{
}

void Graph::add_node(int node)
{
    std::vector<int> list;
    adjlist.push_back(list);
    size++;
}

void Graph::add_edge(int node1, int node2)
{
    raise_invalid_node(node1);
    raise_invalid_node(node2);

    // Adding undirected or directed edge
    adjlist[node1].push_back(node2);
    if (directed)
    {
        adjlist[node2].push_back(node1);
    }
}

std::vector<int> Graph::edges(int node)
{
    raise_invalid_node(node);
    return adjlist[node];
}

void Graph::raise_invalid_node(int node)
{
    if (node >= size)
    {
        std::string str_node = std::to_string(node);
        std::string message = "Node " + str_node + " does not exist in the graph";
        throw std::out_of_range(message);
    }
}

#endif