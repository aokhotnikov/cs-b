#include <QApplication>
#include <QPicture>
#include <QPainter>
#include <QLabel>

//The method draws a triangle
void drawTriangle(QPainter *brush, double x1, double y1, double x2, double y2, double x3, double y3);
//The method draws the Sierpinski triangle
void drawSierpinskiTriangle(QPainter *brush, double x1, double y1, double x2, double y2, double x3, double y3, int rank);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int rankTriangle = (argc > 1) ? atoi(argv[1]) : 6;

    QPicture canvas;
    QPainter brush(&canvas);

    drawTriangle(&brush, 0, 700, 350, 0, 700, 700);
    drawSierpinskiTriangle(&brush, 0, 700, 350, 0, 700, 700, rankTriangle);
    brush.end();// Finish the drawing

    QLabel widget;
    widget.setPicture(canvas);
    widget.show();

    return a.exec();
}
/**
 * The method draws a triangle
 *
 * @param brush The implement for draw
 * @param x1 The x-coordinate of the left corner of the triangle
 * @param y1 The y-coordinate of the left corner of the triangle
 * @param x2 The x-coordinate of the top corner of the triangle
 * @param y2 The y-coordinate of the top corner of the triangle
 * @param x3 The x-coordinate of the right corner of the triangle
 * @param y3 The y-coordinate of the right corner of the triangle
*/
void drawTriangle(QPainter *brush, double x1, double y1, double x2, double y2, double x3, double y3){
    brush->drawLine(x1, y1, x2, y2); // left side of the triangle
    brush->drawLine(x1, y1, x3, y3); // base of the triangle
    brush->drawLine(x3, y3, x2, y2); // right side of the triangle
}
/**
 * The method draws the Sierpinski triangle
 *
 * @param brush The implement for draw
 * @param x1 The x-coordinate of the left corner of the triangle
 * @param y1 The y-coordinate of the left corner of the triangle
 * @param x2 The x-coordinate of the top corner of the triangle
 * @param y2 The y-coordinate of the top corner of the triangle
 * @param x3 The x-coordinate of the right corner of the triangle
 * @param y3 The y-coordinate of the right corner of the triangle
 * @param rank The rank of triangle
*/
void drawSierpinskiTriangle(QPainter *brush, double x1, double y1, double x2, double y2, double x3, double y3, int rank){

    double xx1 = (x2 + x1) / 2; //x-coordinate of the left corner
    double yy1 = (y2 + y1) / 2; //y-coordinate of the left corner
    double xx2 = (x1 + x3) / 2; //x-coordinate of the bottom corner
    double yy2 = (y1 + y3) / 2; //y-coordinate of the bottom corner
    double xx3 = (x3 + x2) / 2; //x-coordinate of the right corner
    double yy3 = (y3 + y2) / 2; //y-coordinate of the right corner
    drawTriangle(*&brush, xx1, yy1, xx2, yy2, xx3, yy3);
    while (rank > 0) {
        rank--;
        drawSierpinskiTriangle(*&brush, xx1, yy1, x2, y2, xx3, yy3, rank); // triangle top
        drawSierpinskiTriangle(*&brush, x1, y1, xx1, yy1, xx2, yy2, rank); // triangle left
        drawSierpinskiTriangle(*&brush, xx2, yy2, xx3, yy3, x3, y3, rank); // triangle right
    }
}
