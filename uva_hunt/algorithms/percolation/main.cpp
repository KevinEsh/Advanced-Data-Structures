
#include <iostream>
#include <stdlib.h>
#include <bitset>
#include "../../data_structures/union_find/union_find.h"

using namespace std;

#define MAX_BIT_SET (1 << 20)

void print_image(bitset<MAX_BIT_SET> image, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << image[i * size + j];
        }
        cout << endl;
    }
}

int main()
{

    srand(time(NULL));

    int cell;
    int size = 100;
    int simulations = 10000;
    int top = size * size;
    int num_cells = top;
    int bottom = top + 1;
    double sum_prob = 0;

    UnionFind unionfind(num_cells + 2);
    bitset<MAX_BIT_SET> image;

    // Initializing montecarlo simulation
    for (int s = 0; s < simulations; s++)
    {
        unionfind.clear();
        image.reset();
        double prob = 0;
        //Two of this nodes will be virtual nodes connected to top and bottom respecticly
        for (int i = 0; i < size; i++)
        {
            // connecting first row (top) to virtual node N²
            unionfind.set_union(top, i);
            // connecting first row (top) to virtual node N²+1
            unionfind.set_union(bottom, size * (size - 1) + i);
        }

        while (!unionfind.are_connected(top, bottom))
        {
            cell = rand() % num_cells;
            if (image[cell])
            {
                continue;
            }
            image[cell] = 1;
            prob++;

            //Union cell with his neighbours
            if ((cell % size) != 0 && image[cell - 1])
            {
                unionfind.set_union(cell, cell - 1);
            }
            if (((cell + 1) % size) != 0 && image[cell + 1])
            {
                unionfind.set_union(cell, cell + 1);
            }
            if ((cell - size) > 0 && image[cell - size])
            {
                unionfind.set_union(cell, cell - size);
            }
            if ((cell + size) < num_cells && image[cell + size])
            {
                unionfind.set_union(cell, cell + size);
            }
        }
        prob /= num_cells;
        //cout << prob << endl;
        sum_prob += prob;
    }

    //print_image(image, size);

    cout << sum_prob / simulations << endl;
    return 0;
}