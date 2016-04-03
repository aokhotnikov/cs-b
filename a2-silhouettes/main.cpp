#include <iostream>
#include <time.h>
#include "silhouettes.h"

int main(int argc, char *argv[])
{
    if (argc > 1){
        clock_t t = clock();
        MyVector<MyVector<int>> graph = createGraphFromImage(*&argv[1]);

        //writeGraphToFile("graph.txt", graph);// for Debag

        int silhouettes = searchSilhouettes(graph);

        //writeGraphToFile("graph.txt", graph);// for Debag

        double time = (clock() * 1.0 - t)/CLOCKS_PER_SEC;
        std::cout << std::fixed <<  "found " << silhouettes
                  << " silhouettes for " << time << " second";
    }
    else {
        std::cout << "you should enter from the console: filename" << std::endl;
    }

    return 0;
}
