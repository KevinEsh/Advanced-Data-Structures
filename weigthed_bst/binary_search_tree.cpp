#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

class Node
{
public:
    int weight;
    string key;

    Node *left;
    Node *right;

    Node(string, int);
    ~Node();
};

Node::Node(string _key, int _weight)
: key(_key), weight(_weight), left(NULL), right(NULL)
{
}

Node::~Node()
{
}

typedef pair<string, int> datum;
typedef vector<datum> Table;

class WeightedBinarySearchTree
{
private:
    Node *root;
    Node *rec_search(Node *, string);
    
public:
    WeightedBinarySearchTree(Table);
    ~WeightedBinarySearchTree();
    Node *search(string);
};

WeightedBinarySearchTree::WeightedBinarySearchTree(Table table)
{
    int size = table.size();
    int dpTable[100][100];
    Node* dpNodes[100][100];
    for (int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++){
            if (i == j){
                dpTable[i][i] = table[i].second;
                dpNodes[i][i] = new Node(table[i].first, table[i].second);
            }
            else
            {
                dpTable[i][j] = 0;
                dpNodes[i][j] = NULL;
            }
            
        }
    }

    int cache = 0, weight;
    for (int diag = 1; diag < size; diag++)
    {
        cache += table[diag-1].second;
        weight = cache;
        for (int i = 0, j = diag; j < size; i++, j++)
        {   
            weight += table[j].second;
            int value = 1 << 30;
            int arg, left, right;
            for (int r = i; r <= j; r++)
            {
                if (r == i) left = 0;
                else left = dpTable[i][r - 1];
                if (r == j) right = 0;
                else right = dpTable[r + 1][j];

                if (value > left + right){
                    value = left + right;
                    arg = r;
                }
            }
            dpTable[i][j] = value + weight;
            weight -= table[i].second;
            
            // Actualizando tabla de nodos
            Node* node = new Node(table[arg].first, table[arg].second);
            if (arg != i) node->left = dpNodes[i][arg-1];
            if (arg != j) node->right = dpNodes[arg+1][j];
            dpNodes[i][j] = node;
            cout << node->key << " ";
            if (node->left != NULL)
                cout << node->left->key << " ";
            else
                cout << node->left << " ";
            if (node->right != NULL)
                cout << node->right->key << " ";
            else
                cout << node->right << " ";
            cout << endl;
        }
    }

    root = dpNodes[0][size - 1];
}

WeightedBinarySearchTree::~WeightedBinarySearchTree()
{
}

Node *WeightedBinarySearchTree::search(string key){
    return rec_search(this->root, key);
}

Node *WeightedBinarySearchTree::rec_search(Node* node, string key) 
{ 
    // Base Cases: node is null or key is present at node 
    if (node == NULL || node->key == key) 
       return node; 
     
    // Key is greater than node's key
    if (node->key < key) 
       return rec_search(node->right, key); 
  
    // Key is smaller than node's key 
    return rec_search(node->left, key); 
}

int main(){
    Table words;
    words.push_back(datum("a", 1));
    words.push_back(datum("b", 9));
    words.push_back(datum("c", 8));
    words.push_back(datum("d", 8));
    words.push_back(datum("e", 1));
    words.push_back(datum("f", 3));
    words.push_back(datum("g", 2));
    words.push_back(datum("h", 1));
    words.push_back(datum("i", 7));
    words.push_back(datum("j", 5));
    words.push_back(datum("k", 10));
    words.push_back(datum("l", 7));
    WeightedBinarySearchTree wbst(words);
    Node *node = wbst.search("k");
    cout << node->key << " " << node->weight << endl;
}