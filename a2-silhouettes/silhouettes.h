#ifndef SILHOUETTES_H
#define SILHOUETTES_H

#include <string>
#include "myvector.h"
#include "myqueue.h"
#include "mylist.h"

const short brightnessIntensity = 50;

class Pixel{
public:
    int x;// x coordinate
    int y;// y coordinate
    Pixel (){}
    Pixel (int y, int x){
        this->x = x;
        this->y = y;
    }
};

//The method checks the neighboring pixels for a visit
void checkNeighboringPixels(MyVector<MyVector<int>> &graph, int y, int x, MyQueue<Pixel> *pixels);

//The method adds pixel to queue visit
void addPixelToQueue(MyVector<MyVector<int>> &graph, int y, int x, MyQueue<Pixel> *pixels);

//The method writes graph to file(was used to Debag)
void writeGraphToFile(std::string fileName, MyVector<MyVector<int>> &graph);

//The method creates a graph from image
MyVector<MyVector<int>> createGraphFromImage(char *fileName);

//The method goes all the points of the graph and counts the number of silhouettes
int searchSilhouettes(MyVector<MyVector<int>> &graph);

//The method filters the list of amounts of pixels
int selectSilhouettes(MyList<int> *listNumPixels);

#endif // SILHOUETTES_H
