#include <iostream>
using namespace std;

struct LinkedList
{
    int value;
    LinkedList *child;

    LinkedList(int _value)
    : value(_value), child(NULL){}
};

int main(){
    LinkedList *head, *next, *prev, *current;
    LinkedList *parent = new LinkedList(0);
    head = parent;
    for (int i = 1; i < 100; i++)
    {
        parent->child = new LinkedList(i);
        parent = parent->child;
    }

    // // Imprime lista ligada en orden original
    // while (head != NULL)
    // {
    //     cout << head->value << endl;
    //     head = head->child;
    // }

    //Revertir la lista ligada
    current = head;
    prev = NULL;
    next = head;
    while (current != NULL)
    {
        next = current->child;
        current->child = prev;
        prev = current;
        current = next;
    }
    head = prev;

    // Imprime lista ligada en reversa
    while (head != NULL)
    {
        cout << head->value << endl;
        head = head->child;
    }
}