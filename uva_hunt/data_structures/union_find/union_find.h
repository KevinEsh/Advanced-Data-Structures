#ifndef UNION_FIND
#define UNION_FIND
#define MAX_SIZE_UNION_FIND (1 << 30)

#include <iostream>

class UnionFind
{
public:
    UnionFind(int);
    ~UnionFind();
    void clear();
    int count();
    int root(int node);
    int find(int node);
    void set_union(int node1, int node2);
    bool are_connected(int node1, int node2);
    bool all_connected();
    int next(int node);

private:
    int size;
    int *parents;
    int *weights;
    int *maximus;
    int *minimus;
    int *successors;
};

UnionFind::UnionFind(int _size)
    : size(_size)
{
    if (size >= MAX_SIZE_UNION_FIND)
    {
        throw std::out_of_range("Given size is greater than maximum allowed size");
    }

    parents = new int[size];
    weights = new int[size];
    maximus = new int[size];
    minimus = new int[size];
    successors = new int[size];
    clear();
}

UnionFind::~UnionFind()
{
    delete[] parents;
    delete[] weights;
    delete[] maximus;
    delete[] minimus;
    delete[] successors;
}

int UnionFind::count()
{
    return size;
}

int UnionFind::root(int node)
{
    int r;

    //Finding the master parent of given node
    while (node != (r = parents[parents[node]]))
    {
        parents[node] = r; //Make my grantfather, my father
        node = parents[r]; //Next is grant-grant-father
    }
    return r;
}

void UnionFind::clear()
{

    for (int i = 0; i < size; i++)
    {
        parents[i] = i;
        weights[i] = 1;
        maximus[i] = i;
        minimus[i] = i;
        successors[i] = i;
    }
}

bool UnionFind::are_connected(int node1, int node2)
{
    return root(node1) == root(node2);
}

void UnionFind::set_union(int node1, int node2)
{
    // Getting identifiers of both nodes
    int r1 = root(node1);
    int r2 = root(node2);

    // Both sets are already merged
    if (r1 == r2)
    {
        return;
    }
    // Merging sets through making the parent of a node, the parent of the other node
    else if (weights[r1] > weights[r2])
    {
        parents[r2] = r1;
        weights[r1] += weights[r2];
        maximus[r1] = (maximus[r1] > maximus[r2] ? maximus[r1] : maximus[r2]);
        minimus[r1] = (minimus[r1] < minimus[r2] ? minimus[r1] : minimus[r2]);
        // Calculating successors for each node
        successors[r1] = successors[r2];
    }
    // In this case, the number of nodes in r2 is greater we should re-calculate successor
    else
    {
        parents[r1] = r2;
        weights[r2] += weights[r1];
        maximus[r2] = (maximus[r1] > maximus[r2] ? maximus[r1] : maximus[r2]);
        minimus[r2] = (minimus[r1] < minimus[r2] ? minimus[r1] : minimus[r2]);
    }

    return;
}

bool UnionFind::all_connected()
{
    // Getting the parent of whichever node
    int r = root(parents[0]);

    //If the weight of the parent is equal to the size of array, all nodes are connected
    if (weights[r] == size)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int UnionFind::find(int node)
{
    return maximus[root(node)];
}

int UnionFind::next(int node)
{
    return successors[node];
}

#endif