#include <iostream>
#include <fstream>
#include <QImage>
#include <QColor>
#include <cmath>
#include "silhouettes.h"

using namespace std;
/*
 * The method is loading the image from the specified file and
 * returns the graph of the image pixels, in which pixel dim
 * corresponds to 1, and bright - 0
 *
 * @param fileName The specified file(*.jpg, *.png, *.bmp) to be read
 * @return The graph of the image pixels
*/
MyVector<MyVector<int>> createGraphFromImage(char *fileName){
    QImage img(fileName);
    MyVector<MyVector<int>> graph;
    for (int col = 0; col < img.height(); col++){
        MyVector<int> line;
        for (int row = 0; row < img.width(); row++){
            QColor clr(img.pixel(row, col));
            //int brightness = round(clr.red() * 0.299 + clr.green() * 0.587 + clr.blue() * 0.114);
            int brightness = clr.lightness();
            brightness < BRIGHTNESS_INTENSITY ? line.push_back(1) : line.push_back(0);
        }
        graph.push_back(line);
    }
    return graph;
}
/*
 * The method goes all the points of the graph and counts the number of silhouettes
 *
 * @param graph The graph of the image pixels
 * @return The number of silhouettes
*/
int searchSilhouettes(MyVector<MyVector<int>> &graph){
    MyList<int> listNumPixels;
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].size(); j++){
            if (graph[i][j] == 1){ //brightness < BRIGHTNESS_INTENSITY

                Pixel px(i, j);
                MyQueue<Pixel> pixels;
                pixels.push(px);
                int numPixelsInSilhouette = 1;

                while (!pixels.empty()){
                    px = pixels.front();
                    graph[px.y][px.x] = 5;
                    pixels.pop();
                    checkNeighboringPixels(graph, px.y, px.x, &pixels);
                    numPixelsInSilhouette++;
                }
                listNumPixels.push_back(numPixelsInSilhouette);
            }
        }
    }
    if (listNumPixels.empty()){
        return 0;
    }
    return selectSilhouettes(&listNumPixels);
}
/*
 * The method filters the list of amounts of pixels and returns the probable number of silhouettes
 *
 * @param listNumPixels The list of the amounts pixels in the silhouettes
 * @return The number of silhouettes
*/
int selectSilhouettes(MyList<int> *listNumPixels){
    listNumPixels->sort();
    int max = listNumPixels->back();
    int probabilityPercentage = max * 0.1;
    int silhouettes = 0;
    for (auto it = listNumPixels->begin(); it <= listNumPixels->end(); it++){
        if (*it > probabilityPercentage){
            silhouettes++;
        }
    }
    return silhouettes;
}
/*
 * The method checks the neighboring pixels for a visit
 *
 * @param graph The graph of the image pixels
 * @param y The coordinate y
 * @param x The coordinate x
 * @param pixels The pixels that need to be visited
 */
void checkNeighboringPixels(MyVector<MyVector<int>> &graph, int y, int x, MyQueue<Pixel> *pixels){

    //right
    if ((graph[0].size() > x + 1) && graph[y][x + 1] == 1)
        addPixelToQueue(graph, y, x + 1, *&pixels);
    //right-down
    if ((graph.size() > y + 1) && (graph[0].size() > x + 1) && graph[y + 1][x + 1] == 1)
        addPixelToQueue(graph, y + 1, x + 1, *&pixels);
    //down
    if ((graph.size() > y + 1) && graph[y + 1][x] == 1)
        addPixelToQueue(graph, y + 1, x, *&pixels);
    //left-down
    if ((graph.size() > y + 1) && (x != 0) && graph[y + 1][x - 1] == 1)
        addPixelToQueue(graph, y + 1, x - 1, *&pixels);
    //left
    if ((x != 0) && graph[y][x - 1] == 1)
        addPixelToQueue(graph, y, x - 1, *&pixels);
    //left-up
    if ((y != 0) && (x != 0) && graph[y - 1][x - 1] == 1)
        addPixelToQueue(graph, y - 1, x - 1, *&pixels);
    //up
    if ((y != 0) && graph[y - 1][x] == 1)
        addPixelToQueue(graph, y - 1, x, *&pixels);
    //right-up
    if ((y != 0) && (graph[0].size() > x + 1) && graph[y - 1][x + 1] == 1)
        addPixelToQueue(graph, y - 1, x + 1, *&pixels);
}
/*
 * The method adds pixel to queue visit
 *
 * @param graph The graph of the image pixels
 * @param y The coordinate y
 * @param x The coordinate x
 * @param pixels The pixels that need to be visited
*/
void addPixelToQueue(MyVector<MyVector<int>> &graph, int y, int x, MyQueue<Pixel> *pixels){
    Pixel px(y, x);
    pixels->push(px);
    graph[y][x] = 2;
}
/*
 * The method writes graph to file(was used to Debag)
 *
 * @param fileName The file to which we write graph
 * @param graph The graph of the image pixels
*/
void writeGraphToFile(string fileName, MyVector<MyVector<int>> &graph){
    ofstream file(fileName, ios_base::out);
    if (file.is_open()) {
        for (int i = 0; i < graph.size(); ++i) {
            for (int j = 0; j < graph[i].size(); j++){
                file << graph[i][j];
            }
            file << endl;
        }
        file.close();
    }
    else{
        cout << "ERROR!!! The file " << fileName << " can't be created";
        exit(0);
    }
}
