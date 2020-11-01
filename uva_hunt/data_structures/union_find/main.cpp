#include <iostream>
#include <stdlib.h>
#include "union_find.h"

using namespace std;

int main()
{
    srand(time(NULL));
    char query;
    int size, a, b;
    cin >> size;

    UnionFind *uf;

    try
    {
        uf = new UnionFind(size);
    }
    catch (const std::exception &error)
    {
        cout << error.what() << endl;
        return 0;
    }

    while (cin >> query >> a >> b)
    {

        if (query == 'u')
        {
            uf->set_union(a, b);
        }
        else
        {

            if (uf->are_connected(a, b))
            {
                cout << a << " and " << b << " are connected" << endl;
            }
            else
            {
                cout << a << " and " << b << " not connected" << endl;
            }
        }
    }

    delete uf;
    return 0;
}