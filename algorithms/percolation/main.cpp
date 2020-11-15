
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <bitset>
#include "../../data_structures/union_find/union_find.h"
#include "../../tools/progress_bar.h"

using namespace std;

#define MAX_BIT_SET (1 << 20)
bitset<MAX_BIT_SET> image;

void print_image(int size)
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

double simulation_percolation(double prob_cell, int simulations, int size, UnionFind &unionfind)
{
    int num_cells = size * size;
    int top = num_cells;
    int bottom = num_cells + 1;
    double percolates = 0;

    for (int s = 0; s < simulations; s++)
    {
        unionfind.clear();
        image.reset();

        // Generation of a random image with probability 'p' of open cell
        for (int cell = 0; cell < num_cells; cell++)
        {

            if (double(rand()) / double(RAND_MAX) <= prob_cell)
            {
                image[cell] = 1;
                // Union cell with his neighbours
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
        }

        // Two of this nodes will be virtual nodes connected to top and bottom respecticly
        for (int i = 0; i < size; i++)
        {
            // connecting first row (top) to virtual node N²
            if (image[i])
            {
                unionfind.set_union(top, i);
            }
            // connecting first row (top) to virtual node N²+1
            if (image[size * (size - 1) + i])
            {
                unionfind.set_union(bottom, size * (size - 1) + i);
            }
        }

        // Does this image percolate?
        if (unionfind.are_connected(top, bottom))
        {
            percolates++;
        }
    }

    return percolates / simulations;
}

int main(int argc, char *argv[])
{
    // Random seed
    srand(time(NULL));

    int size = 20;
    int bins = 100;
    int simulations = 10000;

    double prob_cell;
    double prob_percolation;

    UnionFind unionfind(size * size + 2);
    ofstream myfile;

    // In case user set evironment variables
    if (argc > 1)
        size = atoi(argv[1]);
    if (argc > 2)
        bins = atoi(argv[2]);
    if (argc > 3)
        simulations = atoi(argv[3]);

    myfile.open("simulation_percolation.csv");
    cout << "Montecarlo simulation" << endl;
    for (int b = 1; b <= bins; b++)
    {
        // Begin simulation
        prob_cell = double(b) / double(bins);
        prob_percolation = simulation_percolation(prob_cell, simulations, size, unionfind);

        // Report simulation
        print_progress(b, bins, 50);
        myfile << prob_cell << "," << prob_percolation << "\n";
    }
    cout << "Simulation terminated successfully" << endl;

    myfile.close();
    return 0;
}
