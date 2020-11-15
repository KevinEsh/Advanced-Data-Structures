#include <iostream>

void print_progress(int iter, int total, int bar_width)
{
    if (iter > total)
        throw std::logic_error("progress is larger than total");

    float progress = float(iter) / float(total);
    int pos = bar_width * progress;

    std::cout.flush();
    std::cout << "[";
    for (int i = 0; i < bar_width; ++i)
    {
        if (i < pos)
            std::cout << "=";
        else if (i == pos)
            std::cout << ">";
        else
            std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";

    if (iter >= total)
    {
        std::cout << "[" << std::endl;
        std::cout.flush();
    }
}
