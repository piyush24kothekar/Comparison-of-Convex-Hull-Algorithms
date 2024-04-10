#include <iostream>
#include<graphics.h>
#include <unistd.h>
using namespace std;
typedef struct {
    int x, y;
} Point;

void swap(Point* points, int i, int j) {
    Point temp = points[i];
    points[i] = points[j];
    points[j] = temp;
}

int findSide(Point p1, Point p2, Point p) {
    int val = (p.y - p1.y) * (p2.x - p1.x) - (p.x - p1.x) * (p2.y - p1.y);
    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}

int findDistance(Point p1, Point p2, Point p) {
    return abs((p.y - p1.y) * (p2.x - p1.x) - (p.x - p1.x) * (p2.y - p1.y));
}

void quickHull(Point* points, int n, Point p1, Point p2, int side) {
    int index = -1;
    int maxDistance = 0;

    for (int i = 0; i < n; i++) {
        int currentDistance = findDistance(p1, p2, points[i]);
        if (findSide(p1, p2, points[i]) == side && currentDistance > maxDistance) {
            setcolor(0);
            line((p1.x*100+50 +p2.x*100+50)/2,(450 - p1.y*100+450 - p2.y*100)/2, 50+ points[index].x*100, 450 - 100*points[index].y);
            putpixel(points[index].x*100 + 50, 450 - points[index].y*100, WHITE);
            sleep(1);
            setcolor(14);
            line((p1.x*100+50 +p2.x*100+50)/2,(450 - p1.y*100+450 - p2.y*100)/2, 50+ points[i].x*100, 450 - 100*points[i].y);
            sleep(1);
            index = i;
            maxDistance = currentDistance;
        }
    }

    if (index == -1) {
        //printf("(%d, %d)\n", p1.x, p1.y);
        //printf("(%d, %d)\n", p2.x, p2.y);
        return;
    }
    else{
            line(p1.x*100+50, 450 - p1.y*100, 50+ points[index].x*100, 450 - 100*points[index].y);
            sleep(1);
            line(p2.x*100+50, 450 - p2.y*100, 50+ points[index].x*100, 450 - 100*points[index].y);
            sleep(1);
            setcolor(0);
            line((p1.x*100+50 +p2.x*100+50)/2,(450 - p1.y*100+450 - p2.y*100)/2, 50+ points[index].x*100, 450 - 100*points[index].y);
            sleep(1);
            line(p1.x*100+50, 450 - p1.y*100, 50+ p2.x*100, 450 - 100*p2.y);
            putpixel(p1.x*100 + 50, 450 - p1.y*100, WHITE);
            putpixel(p2.x*100 + 50, 450 - p2.y*100, WHITE);
            putpixel(points[index].x*100 + 50, 450 - points[index].y*100, WHITE);
            sleep(1);
            setcolor(14);
    }
    for(int i = 0; i<n; i++){
        putpixel(points[i].x*100 + 50, 450 - points[i].y*100, WHITE);
    }
    quickHull(points, n, points[index], p1, -findSide(points[index], p1, p2));
    quickHull(points, n, points[index], p2, -findSide(points[index], p2, p1));
   // setcolor(0);
    //line(p1.x*100+50, 450 - p1.y*100, 50+ points[index].x*100, 450 - 100*points[index].y);
    //sleep(1);
    //line(p2.x*100+50, 450 - p2.y*100, 50+ points[index].x*100, 450 - 100*points[index].y);
    //sleep(1);
    //setcolor(14);
}

void convexHull(Point* points, int n) {
    sleep(1);
    setcolor(14);
    if (n < 3) {
        printf("Convex hull not possible with less than 3 points.\n");
        return;
    }

    int minX = 0, maxX = 0;

    for (int i = 1; i < n; i++) {
        if (points[i].x < points[minX].x)
            minX = i;
        if (points[i].x > points[maxX].x)
            maxX = i;
    }
    line(points[minX].x*100+50, 450 - points[minX].y*100, 50+ points[maxX].x*100, 450 - 100*points[maxX].y);
    sleep(1);
    quickHull(points, n, points[minX], points[maxX], 1);
    line(points[minX].x*100+50, 450 - points[minX].y*100, 50+ points[maxX].x*100, 450 - 100*points[maxX].y);
    sleep(1);
    quickHull(points, n, points[minX], points[maxX], -1);
}
int main()
{
    int gd=DETECT, gm; // Detect is constant value of graphics driver and is assigned to gd , gm will hold the value of graphics mode
    initgraph(&gd,&gm, ""); //(graphic driver, graphic mode,path)
    line(50,100,50,450);
    line(51, 450,600, 450);
    int n;
    Point points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 3},{3,1}};
    n = sizeof(points) / sizeof(points[0]);
    for(int i = 0; i<n; i++){
        putpixel(points[i].x*100 + 50, 450 - points[i].y*100, WHITE);
    }
    convexHull(points, n);
    setcolor(4);
    getch();
    closegraph();
    return 0;
}
